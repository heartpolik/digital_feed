#include <avr/pgmspace.h>
#include <util/delay.h>
#include "CONFIG.h"                               //Параметры "ЖЕЛЕЗА" и конфигурационные параметры
#include "LiquidCrystal_1602_RUS.h"               //Библиотека LCD1602 ENG-TO-RUS для возможности вывода русских букв на обычные дисплеи

#ifndef __AVR_ATmega2560__  // Mega2560
#error Неправильно выбрана плата или модель процессора! Нужно задать ATMega2560
#endif

volatile bool MotorX_NeedClear = false;
volatile bool MotorZ_NeedClear = false;
//WDT
volatile bool _WDT_TIMER_FLAG = false;
//Для замеров времени
unsigned long _time;

//Многопроходный КОНУС
byte Cone_qStep = 0;
bool Complete_flag = false;
byte SpeedMode = MANUAL;          //Скоростной режим для обработчика OCR4
//Многопроходный aFeed
int w = 0;

//int debug1 = 0;

//Делилка
//volatile bool INT_0 = false;
//volatile bool INT_1 = false;

//ПЕРЕМЕННЫЕ
int ENC_LINE_PER_REV     = _ENC_LINE_PER_REV;           // Кол-во линий энкодера на 1 оборот шпинделя [SETUP: 0...16382, 2 байта]
int MOTOR_Z_STEP_PER_REV = _MOTOR_Z_STEP_PER_REV;       // Кол-во шагов на оборот винта Z, продольная [SETUP: 0...32767, 2 байта]
int SCREW_Z              = _SCREW_Z;                    // Шаг продольного винта Z в сотках, 1.5мм [SETUP: 0...32767, 2 байта]
int McSTEP_Z             = _McSTEP_Z;                   // Микрошаг, ось Z, продольная [SETUP: SETUP: 0...32767, 2 байта]
int MOTOR_X_STEP_PER_REV = _MOTOR_X_STEP_PER_REV;       // Кол-во шагов на оборот винта X, поперечная [SETUP: SETUP: 0...32767, 2 байта]
int SCREW_X              = _SCREW_X;                    // Шаг поперечного винта X в сотках, 1.0мм [SETUP: SETUP: 0...32767, 2 байта]
int REBOUND_X            = _REBOUND_X;                  // Отскок резца в микрошагах, для авторезьбы, должен быть больше люфта поперечки [SETUP: 0...32767, 2 байта]
int REBOUND_Z            = _REBOUND_Z;                  // [SETUP: 0...32767, 2 байта]
int McSTEP_X             = _McSTEP_X;                   // Микрошаг, ось X, поперечная [SETUP: 0...32767, 2 байта]
//
byte THRD_ACCEL          = _THRD_ACCEL;                 // К.деления с которого будем ускоряться на Резьбах, Accel+Ks должен быть < 255 [SETUP: 0...255, 1 байта]
int FEED_ACCEL           = _FEED_ACCEL;                 // Жесткость разгона на подачах, бОльше значение - короче разгон. [SETUP: 0...32767, 2 байта]
//
int MIN_FEED             = _MIN_FEED;                   // Желаемая минимальная подача  в сотках/оборот, 0.02мм/об [SETUP: 0...32767, 2 байта]
int MAX_FEED             = _MAX_FEED;                   // Желаемая максимальная подача в сотках/оборот, 0.25мм/об [SETUP: 0...32767, 2 байта]
int MIN_aFEED            = _MIN_aFEED;                  // Желаемая минимальная подача  в mm/минуту, 20мм/мин [SETUP: 0...32767, 2 байта]
int MAX_aFEED            = _MAX_aFEED;                  // Желаемая максимальная подача в mm/минуту, 400мм/мин [SETUP: 0...32767, 2 байта]
// Ускоренные перемещения
int MAX_RAPID_MOTION     = _MAX_RAPID_MOTION;           // Меньше - бОльшая конечная скорость           //16000000/32/((25+1)*2)/800*60=721rpm
int MIN_RAPID_MOTION     = _MIN_RAPID_MOTION;           // Больше - мЕньшая начальная скорость, max 255 //16000000/32/((150+25+1)*2)/800*60=107rpm
int REPEAt               = _REPEAt;                     // Кол-во повторов для постоянной скорости в пределах полного шага
// Длительность разгона = 150/2*REPEAT(4)/Microstep(4) = 75 полных шагов цикл ускорения
// Ручной энкодер (100 линий)
int HC_SCALE_1           = _HC_SCALE_1;                 // 1-e положение, масштаб = 1сотка/тик = 1мм/ на 1 оборот ручки энкодера [SETUP: 0...32767, 2 байта]
int HC_SCALE_10          = _HC_SCALE_10;                // 2-e положение, масштаб = 10соток/тик = 10мм/ на 1 оборот ручки энкодера [SETUP: 0...32767, 2 байта]
int HC_START_SPEED_1     = _HC_START_SPEED_1;           // старт РГИ, 250000/(250+1)/800*60/2 = 37rpm [SETUP: 0...32767, 2 байта]
int HC_MAX_SPEED_1       = _HC_MAX_SPEED_1;             // максимум скорости РГИ, 250000/(150+1)/800*60/2 = 62rpm [SETUP: 0...32767, 2 байта]
int HC_START_SPEED_10    = _HC_START_SPEED_10;          // старт РГИ, 250000/(150+1)/800*60/2 = 62rpm [SETUP: 0...32767, 2 байта]
int HC_MAX_SPEED_10      = _HC_MAX_SPEED_10;            // максимум скорости РГИ, 250000/(23+1)/800*60/2 = 391rpm [SETUP: 0...32767, 2 байта]
byte HC_X_DIR            = _HC_X_DIR;                   // 1-поперечка по часовой, 0-против [SETUP: 0...32767, 1 байта]

int ENC_TICK;                                           // Encoder Рабочее кол-во импульсов       //Правка для Atmel Studio, не забудь потом проинициализировать переменную в аналоге setup() ENC_TICK = (ENC_LINE_PER_REV * 2)
byte Hand_Axis_Old = 0;
byte Hand_Scale_Old = 0;
byte Limit_Button_Old = 0;
byte Button_Old = 0;
byte Button_Sel_Old = 0;
bool key_sel_flag = false;
byte Joy_Old = 0;
byte Submode_Old = 0;
byte Mode_Old = 0;

enum Mode
{
  Mode_Thread = 1,
  Mode_Feed,
  Mode_aFeed,
  Mode_Cone_L,
  Mode_Cone_R,
  Mode_Reserve,
  Mode_Sphere,
  Mode_Divider
};

enum Sub_Mode_Thread
{
  Sub_Mode_Thread_Int = 1,
  Sub_Mode_Thread_Man,
  Sub_Mode_Thread_Ext,
};

enum Sub_Mode_Feed
{
  Sub_Mode_Feed_Int = 1,
  Sub_Mode_Feed_Man,
  Sub_Mode_Feed_Ext,
};

enum Sub_Mode_aFeed
{
  Sub_Mode_aFeed_Int = 1,
  Sub_Mode_aFeed_Man,
  Sub_Mode_aFeed_Ext,
};

enum Sub_Mode_Cone
{
  Sub_Mode_Cone_Int = 1,
  Sub_Mode_Cone_Man,
  Sub_Mode_Cone_Ext,
};

enum Sub_Mode_Sphere
{
  Sub_Mode_Sphere_Int = 1,
  Sub_Mode_Sphere_Man,
  Sub_Mode_Sphere_Ext,
};


bool spindle_flag = OFF;
//Командные флаги
bool Z_NEED_RUN_FEED_FLAG = OFF;
bool X_NEED_RUN_FEED_FLAG = OFF;
bool Z_NEED_RUN_RAPID_FLAG = OFF;
bool X_NEED_RUN_RAPID_FLAG = OFF;
//Флаги работы
//Z_WORKING_FEED_FLAG -> Z_WORKING_FEED_FLAG
//X_WORKING_FEED_FLAG -> X_WORKING_FEED_FLAG
bool Z_WORKING_RAPID_FLAG = OFF;
bool X_WORKING_RAPID_FLAG = OFF;


bool limit_Left_flag = OFF;
bool limit_Right_flag = OFF;
bool limit_Front_flag = OFF;
bool limit_Rear_flag = OFF;

bool limit_button_flag = OFF;
bool button_flag = OFF;

bool a_flag = false;
bool b_flag = false;
bool c_flag = false;
bool d_flag = false;
bool cycle_flag = false;

bool err_1_flag = false;
bool err_2_flag = false;
bool err_3_flag = false;          //NEW

bool hand_X = OFF;
bool hand_Z = OFF;
bool flag_hand_X = OFF;
bool flag_hand_Z = OFF;
bool X_flag = OFF;                                // временный
bool Z_flag = OFF;                                // временный
bool flag_Scale_x1 = OFF;                         // возможно только для отладки
bool flag_Scale_x10 = OFF;                        // возможно только для отладки
bool control_flag = OFF;
bool flag_j = OFF;

int Tacho_Count = 0;
int Tacho_Count_Old = 0;

int Spindle_Count = 0;

//Fix: переменная изменяется в обработчике INT0 - поэтому Volatile
volatile int Enc_Pos = 0;

//NEW Divider x2
volatile int Enc_Pos_Divider = 0;


volatile long Hand_Count = 0;
long Hand_Count_Old = 0;
long Hand_Count_New = 0;
long Hand_Z_Pos = 0;
long Hand_X_Pos = 0;

byte Scale;                                       //Правка, не забудь потом проинициализировать переменную в аналоге setup() Scale = HC_SCALE_1

byte Ks_Count = 0;
int Km_Count = 0;
byte Ks_Divisor = 0;
byte tmp_Ks_Divisor;                              //Правка, не забудь потом проинициализировать переменную в аналоге setup() tmp_Ks_Divisor = THRD_ACCEL
int Km_Divisor = 0;
uint16_t Feed_Divisor = 0;
uint16_t aFeed_Divisor = 0;

byte Cs_Count = 0;
int Cm_Count = 0;
byte Cs_Divisor = 0;
int Cm_Divisor = 0;
//NEW
byte XZ_Divisor = (byte)0;

byte tmp_Accel;                                   //Правка, не забудь потом проинициализировать переменную в аналоге setup() tmp_Accel = THRD_ACCEL
byte Repeat_Count = 0;

int Brake_Compens = 0;

byte Mode = Mode_Feed;
byte Sub_Mode_Thread = Sub_Mode_Thread_Man;
byte Sub_Mode_Feed = Sub_Mode_Feed_Man;
byte Sub_Mode_aFeed = Sub_Mode_aFeed_Man;
byte Sub_Mode_Cone = Sub_Mode_Cone_Man;
byte Sub_Mode_Sphere = Sub_Mode_Sphere_Man;
byte Thread_Step = 11;
byte Cone_Step = 0;

long Motor_Z_Pos = 0;
long Motor_X_Pos = 0;

long Limit_Pos_Left = Limit_Pos_Max;
long Limit_Pos_Right = Limit_Pos_Min;
long Limit_Pos_Front = Limit_Pos_Max;
long Limit_Pos_Rear = Limit_Pos_Min;
volatile long Limit_Pos = 0;
volatile long Limit_Pos_HC = 0;

uint16_t Feed_mm = 0;
uint16_t aFeed_mm = 0;

//OLD
//uint16_t Start_Speed = ENC_LINE_PER_REV / ((uint32_t)MOTOR_Z_STEP_PER_REV * McSTEP_Z * MIN_FEED / SCREW_Z) / FEED_ACCEL;
//uint16_t max_OCR5A = ENC_LINE_PER_REV / ((uint32_t)MOTOR_Z_STEP_PER_REV * McSTEP_Z * MIN_FEED / SCREW_Z) / FEED_ACCEL;              // Начальная скорость подачи при разгоне/торможении
//uint16_t max_OCR4A = (250000 / ((uint32_t)MIN_aFEED * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1) / FEED_ACCEL;
uint16_t Start_Speed, max_OCR5A, max_OCR4A;    //Правка, не забудь потом проинициализировать переменные в аналоге setup()


byte Total_Tooth = 1;
byte Current_Tooth = 1;

byte Pass_Total = 1;
byte Pass_Nr = 1;
long Null_X_Pos = 0;
long Null_Z_Pos = 0;
int Ap = 0;

//Переменные используемые в ADC.ino
int ADC_Feed = 0;
long Sum_ADC = 0;
int ADC_Array[20];              //Используется в новом ADC.ino 20 ячеек вместо 16 прежних
byte x = 0;

long Control_Count = 0;

// Sphere
const int Cutter_Width_array[] = {100, 150, 200, 250, 300};
#define TOTAL_CUTTER_WIDTH (sizeof(Cutter_Width_array) / sizeof(Cutter_Width_array[0]))
byte Cutter_Step = 2;
int Cutter_Width;                 //Правка, не забудь потом проинициализировать переменную в аналоге setup() Cutter_Width = Cutter_Width_array[Cutter_Step]

const int Cutting_Width_array[] = {10, 25, 50, 100};
#define TOTAL_CUTTING_STEP (sizeof(Cutting_Width_array) / sizeof(Cutting_Width_array[0]))
byte Cutting_Step = 1;
int Cutting_Width;                //Правка, не забудь потом проинициализировать переменную в аналоге setup() Cutting_Width = Cutting_Width_array[Cutting_Step]

long Sph_R_mm = 1000;
long Sph_R = 0;
long R_Quad;                      //Правка, не забудь потом проинициализировать переменную в аналоге setup() R_Quad = Sph_R_mm * Sph_R_mm
long Bar_R_mm = 0;
long Bar_R = 0;

uint16_t min_OCR3A, max_OCR3A;    //Правка, не забудь потом проинициализировать переменную в аналоге setup() max_OCR3A = HC_START_SPEED_1, min_OCR3A = HC_MAX_SPEED_1

//NEW Для тахометра
volatile unsigned long  TachoCount = 0;      //Импульсы от энкодера для тахометра
volatile byte TachoCycle = 0;
volatile unsigned int CurrentRPM = 0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  int main() {
  //#if defined(USBCON)
  //   USBDevice.attach();
  //#endif
  // наш личный "setup"
  setup();
  for (;;) {
    // наш личный "loop"
    loop();
  }
  return 0;
  }
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  //Инициализация LCD-дисплея
  Print_LCD_Init();
  //Загрузка параметров из EEPROM и заполнение массивов резьб, конусов, и стартовая инициализация других переменных
  Load_EEPROM();
  //Отображение заставки логотипа при включении
  Print_LCD_Logo();
  //Пока горит заставка небольшая задержка для восприятия и возможности входа в SETUP
  _delay_ms(2000);    //1 секунды мало, не успеваешь сообразить

  DDRG = B11111111;
  TIMSK0 = 0;
  // ***** Timer0 ***** // ***** Тахометр *****
  //  TCCR0A = (1<<COM0B0)|(1<<WGM01); // Toggle OC0B on Compare Match // CTC Mode2
  //  TCCR0B = (1<<CS00);     // No Prescaler
  //  OCR0A = 89; // 1800/10(выходных пульсов)/2-1 = 89
  //  TIMSK0 = (1<<OCIE0B);
  Encoder_Init();       //Настройка выводов для энкодера
  Hand_Init();          //Настройка выводов РГИ
  Motor_Init();         //Настройка выводов моторов
  Limit_Init();
  Limit_Left_LED_Off();
  Limit_Right_LED_Off();
  Limit_Front_LED_Off();
  Limit_Rear_LED_Off();
  Menu_Buttons_Init();
  Beeper_Init();
  Beeper_Off();
  //============= SETUP ================================================
  Loop_Setup_Menu();
  //====================================================================
  Joy_Init();
  Mode_Switch_Init();
  //----------------------------------------------------------------------------------------------------------------------------------------------
  setup_ADC();  //Запускать после исполнения макроса Menu_Buttons_Init()
  //----------------------------------------------------------------------------------------------------------------------------------------------
  INT0_Init();

  //NEW
  INT1_Init();
  //---

  INT2_Init();        //Для РУЧНОЙ ЭНКОДЕР ГЕНЕРАТОР ИМПУЛЬСОВ

  //OLD
  //Timer2_Init();
  //OCR2A = MIN_RAPID_MOTION;

  Timer3_Init();
  OCR3A = max_OCR3A;
  Timer4_Init();
  OCR4A = max_OCR4A;
  Timer5_Init();
  OCR5A = max_OCR5A;

  //OLD
  //Ena_INT_Z_Feed();       //Это для чего???

  Spindle_Dir = CW;
  Motor_Z_Dir = CW;
  Joy_Z_flag = OFF;
  Z_WORKING_FEED_FLAG = OFF;
  Motor_X_Dir = CW;
  Joy_X_flag = OFF;
  X_WORKING_FEED_FLAG = OFF;

  //OLD
  /*
    //16MHz/1024 = 15625Hz (1 импульс счётчика таймера за 0,000064с)
    //OCR1A = 625 -> 0,000064 * 625 = 0,04c = 40ms
    TCCR1A = 0;
    TCCR1B = 0
             | (0 << ICNC1) | (0 << ICES1)
             | (0 << WGM13) | (1 << WGM12)
             | (1 << CS12) | (0 << CS11) | (1 << CS10); //Prescaler 1:1024
    OCR1A = 625;
  */
  //NEW
  //-----  watchdog  -----
  WDTCSR = (1 << WDCE) | (1 << WDE);  //WDT генерирует только прерывание "WDT_vect"
  //WDTCSR = 0x00 | (1<<WDIE) | (1<<WDP2) | (1<<WDP0);      //0.5s
  //WDTCSR = 0x00 | (1<<WDIE) | (1<<WDP1) | (1<<WDP0);      //0.125s
  WDTCSR = 0x00 | (1 << WDIE) | (1 << WDP1);                //64ms
  //WDTCSR = 0x00 | (1<<WDIE) | (1<<WDP0);                    //32ms
  //---

  //Для ДЕЛИЛКИх2
  get_Enc_Pos_Divider();
  //---

  Motor_Z_RemovePulse();
  Motor_X_RemovePulse();

#ifdef _DEBUG_UART
  Serial.begin(500000);
#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//unsigned int DBG4 = 0;

void loop()
{
  for (;;)
  { //Наш личный Loop
    Spindle();

    Read_ADC_Feed();
    //OLD
    //if (KEYB_TIMER_FLAG != 0) Menu();
    //WDT
    if (KEYB_TIMER_FLAG)
    {
      Menu();
    }
    //---
    if (Mode == Mode_Divider) Print();  // пока для теста !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //DEBUG--------------------------------------------------------------------------------------------------------------------------------
    /*
      if (++DBG4 > 5000)
      {
      DBG4 = 0;
      Serial.print("Motor_Z_Pos="); Serial.print(Motor_Z_Pos); Serial.print("\n\r");
      Serial.print("Limit_Pos="); Serial.print(Limit_Pos); Serial.print(" ");
      Serial.print("Motor_Z_Pos="); Serial.print(Motor_Z_Pos); Serial.print("\n\r");

      Serial.print("Limit_Pos_Left="); Serial.print(Limit_Pos_Left); Serial.print(" Limit_Pos_Right="); Serial.print(Limit_Pos_Right); Serial.print(" ");
      Serial.print("Brake_Compens="); Serial.print(Brake_Compens); Serial.print("\n\r");

      Serial.print("Z_WORKING_FEED_FLAG="); Serial.print(Z_WORKING_FEED_FLAG); Serial.print("\n\r");
      Serial.print("Z_NEED_RUN_FEED_FLAG="); Serial.print(Z_NEED_RUN_FEED_FLAG); Serial.print("\n\r");
      Serial.print("Z_NEED_RUN_RAPID_FLAG="); Serial.print(Z_NEED_RUN_RAPID_FLAG); Serial.print("\n\r");
      Serial.print("Z_WORKING_RAPID_FLAG="); Serial.print(Z_WORKING_RAPID_FLAG); Serial.print("\n\r");

      Serial.print("SpeedMode="); Serial.print(SpeedMode); Serial.print("\n\r");

      Serial.print("\n\r");

      }
    */
    //-------------------------------------------------------------------------------------------------------------------------------------
  }
}

//Для ДЕЛИЛКИх2
void get_Enc_Pos_Divider()
{
  //NEW2
  if (!Enc_Ch_A)
  {
    if (!Enc_Ch_B)                                //прямое вращение
    {
      Enc_Pos_Divider = 0;
    } else {                                      //вращение в обратную сторону
      Enc_Pos_Divider = 1;
    }
  } else {
    if (!Enc_Ch_B)                                //вращение в обратную сторону
    {
      Enc_Pos_Divider = 1;
    } else {                                      //прямое вращение
      Enc_Pos_Divider = 0;
    }
  }
}
//---
