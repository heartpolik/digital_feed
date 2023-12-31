#ifndef CONFIG_h
#define CONFIG_h
#include "DEFINE.h"                               //Макросы
//==================================================================================================================================
//ОТЛАДКА
//#define _DEBUG_UART            1
//#define _DEBUG_INTERRUPT       1
//#define _DEBUG_MENU            1
//#define _DEBUG_HANDCODER       1
//#define _DEBUG_CONE            1
//#define _DEBUG_ADC             1
//#define _DEBUG_DIVIDER         1
//==================================================================================================================================
// ***** ДЕФОЛТНЫЕ ПАРАМЕТРЫ ЖЕЛЕЗА (НОВАЯ СЕКЦИЯ ПОД SETUP ***** //
#define _VERSION              38       //Версия программы для записи в EEPROM, 2 байта типа uint16_t, диапазон 0...65534
//
#define _ENC_LINE_PER_REV     1800     // Кол-во линий энкодера на 1 оборот шпинделя (0...16382)
#define _MOTOR_Z_STEP_PER_REV 200      // Кол-во шагов на оборот винта Z, продольная
#define _SCREW_Z              200      // Шаг продольного винта Z в сотках, 2.0мм
#define _McSTEP_Z             4        // Микрошаг, ось Z, продольная
#define _MOTOR_X_STEP_PER_REV 200      // Кол-во шагов на оборот винта X, поперечная
#define _SCREW_X              200      // Шаг поперечного винта X в сотках, 2.0мм
#define _REBOUND_X            400      //Отскок резца в микрошагах, для авторезьбы, должен быть больше люфта поперечки
#define _REBOUND_Z            400      //
#define _McSTEP_X             4        // Микрошаг, ось X, поперечная
//
#define _THRD_ACCEL           25       // К.деления с которого будем ускоряться на Резьбах, Accel+Ks должен быть < 255
#define _FEED_ACCEL           3        // Жесткость разгона на подачах, бОльше значение - короче разгон.
// Синхронная подача
#define _MIN_FEED             2        // Желаемая минимальная подача  в сотках/оборот, 0.02мм/об
#define _MAX_FEED             25       // Желаемая максимальная подача в сотках/оборот, 0.25мм/об
// Асинхронная подача
#define _MIN_aFEED            20       // Желаемая минимальная подача  в mm/минуту, 20мм/мин
#define _MAX_aFEED            400      // Желаемая максимальная подача в mm/минуту, 400мм/мин
// Ускоренные перемещения
#define _MAX_RAPID_MOTION     25                        // Меньше - бОльшая конечная скорость
#define _MIN_RAPID_MOTION    (_MAX_RAPID_MOTION + 150)  // Больше - мЕньшая начальная скорость, max 255
#define _REPEAt              (_McSTEP_Z * 1)            // Кол-во повторов для постоянной скорости в пределах полного шага
// Ручной энкодер (100 линий)
#define _HC_SCALE_1           1        // 1-e положение, масштаб = 1сотка/тик = 1мм/ на 1 оборот ручки энкодера
#define _HC_SCALE_10          10       // 2-e положение, масштаб = 10соток/тик = 10мм/ на 1 оборот ручки энкодера
#define _HC_START_SPEED_1     370      //was 250      // старт РГИ, 250000/(250+1)/800*60/2 = 37rpm
#define _HC_MAX_SPEED_1       185      //was 150      // максимум скорости РГИ, 250000/(150+1)/800*60/2 = 62rpm
#define _HC_START_SPEED_10    370      //was 150      // старт РГИ, 250000/(150+1)/800*60/2 = 62rpm
#define _HC_MAX_SPEED_10      54       //was 23       // максимум скорости РГИ, 250000/(23+1)/800*60/2 = 391rpm
#define _HC_X_DIR             1        // 1-поперечка по часовой, 0-против
//----------------------------------------------------------------------------------------------------------------------------------
//Поправленный блок проверок при компиляции
#define a  (uint32_t)(_ENC_LINE_PER_REV / ((float)_MOTOR_Z_STEP_PER_REV * _McSTEP_Z * _MIN_FEED / _SCREW_Z) /2 +0.5)
static_assert(a <= 255, "Неверно задано значение _MIN_FEED");
#define b  (uint32_t)(_ENC_LINE_PER_REV / ((float)_MOTOR_Z_STEP_PER_REV * _McSTEP_Z * _MAX_FEED / _SCREW_Z) /2 +0.5)
static_assert(b > 1, "Неверно задано значение _MAX_FEED");
#define c  250000 / ((uint32_t)_MIN_aFEED * _MOTOR_Z_STEP_PER_REV * _McSTEP_Z / ((uint32_t)60 * _SCREW_Z / 100) * 2) -1
static_assert(c <= 65535, "Неверно задано значение _MIN_aFEED");
#define d  250000 / ((uint32_t)_MAX_aFEED * _MOTOR_Z_STEP_PER_REV * _McSTEP_Z / ((uint32_t)60 * _SCREW_Z / 100) * 2) -1
static_assert(d > 1, "Неверно задано значение _MAX_aFEED");
#define e  (uint32_t)(_ENC_LINE_PER_REV / ((float)_MOTOR_X_STEP_PER_REV * _McSTEP_X * _MIN_FEED / _SCREW_X) /2 +0.5)
static_assert(e <= 255, "Неверно задано значение _MIN_FEED");
#define f  (uint32_t)(_ENC_LINE_PER_REV / ((float)_MOTOR_X_STEP_PER_REV * _McSTEP_X * _MAX_FEED / _SCREW_X) /2 +0.5)
static_assert(f > 1, "Неверно задано значение _MAX_FEED");
#define g  250000 / ((uint32_t)_MIN_aFEED * _MOTOR_X_STEP_PER_REV * _McSTEP_X / ((uint32_t)60 * _SCREW_X / 100) * 2) -1
static_assert(g <= 65535, "Неверно задано значение _MIN_aFEED");
#define h  250000 / ((uint32_t)_MAX_aFEED * _MOTOR_X_STEP_PER_REV * _McSTEP_X / ((uint32_t)60 * _SCREW_X / 100) * 2) -1
static_assert(h > 1, "Неверно задано значение _MAX_aFEED");
//==================================================================================================================================
//РЕЗЬБЫ
//Поправленная структура для SETUP
typedef struct
{
  byte Cs_Div;
  int  Cm_Div;
  char Cone_Print[6];
  byte Type;            //для SETUP. Тип формулы для расчёта параметров конуса "TYPE_AB" - СООТНОШЕНИЕ A:B, или "TYPE_DEG" - ГРАДУСЫ
  float C1;             //для SETUP. Для формулы СООТНОШЕНИЕ параметр A. Для формулы ГРАДУСЫ - градусы
  float C2;             //для SETUP. Для формулы СООТНОШЕНИЕ параметр B. Для формулы ГРАДУСЫ - не используется, заполняется нулём 0.0f
  byte XZ;              //Автоматически заполняемая переменная (в формулах Setup) с помощью неё выбирается формула тактования Z->X или X->Z
} cone_info_type;

//Новый Массив Конусов для SETUP + LCD1602 ENG-TO-RUS
cone_info_type Cone_Info[] =
{
  {  0,  0,  " 45\x00DF" ,  TYPE_DEG, 45.0f,  0.0f    ,0},      //УГОЛ 45°
  {  0,  0,  " 40\x00DF" ,  TYPE_DEG, 40.0f,  0.0f    ,0},      //УГОЛ 45°
  {  0,  0,  " 60\x00DF" ,  TYPE_DEG, 60.0f,  0.0f    ,0},      //УГОЛ 60° !!! 
  {  0,  0,  " 70\x00DF" ,  TYPE_DEG, 70.0f,  0.0f    ,0},      //УГОЛ 70° !!!
  {  0,  0,  " 80\x00DF" ,  TYPE_DEG, 80.0f,  0.0f    ,0},      //УГОЛ 80° !!!
  {  0,  0,  " KM0" ,       TYPE_AB,  1.0f,   19.212f ,0},      //Конус Морзе KM0 1:19,212 [ГОСТ 25557-2006]
  {  0,  0,  " KM1" ,       TYPE_AB,  1.0f,   20.047f ,0},      //Конус Морзе KM1 1:20,047 [ГОСТ 25557-2006]
  {  0,  0,  " KM2" ,       TYPE_AB,  1.0f,   20.020f ,0},      //Конус Морзе KM2 1:20,020 [ГОСТ 25557-2006]
  {  0,  0,  " KM3" ,       TYPE_AB,  1.0f,   19.922f ,0},      //Конус Морзе KM3 1:19,922 [ГОСТ 25557-82]
  {  0,  0,  " KM4" ,       TYPE_AB,  1.0f,   19.254f ,0},      //Конус Морзе KM4 1:19,254 [ГОСТ 25557-2006]
  {  0,  0,  " KM5" ,       TYPE_AB,  1.0f,   19.002f ,0},      //Конус Морзе KM5 1:19,002 [ГОСТ 25557-2006]
  {  0,  0,  " KM6" ,       TYPE_AB,  1.0f,   19.180f ,0},      //Конус Морзе KM6 1:19,180 [ГОСТ 25557-2006]
  {  0,  0,  " KM7" ,       TYPE_AB,  1.0f,   19.231f ,0},      //Конус Морзе KM7 1:19,231 [Устаревший, отсутствует в ГОСТ 25557-2006]
  {  0,  0,  " B&S" ,       TYPE_AB,  1.0f,   23.904f ,0},      //Конус Браун и Шарп №0, №1, №2 Brown & Sharpe [ГОСТ 25557-2006]
  {  0,  0,  "0652" ,       TYPE_AB,  1.0f,   0.652f ,0},       //
  {  0,  0,  "0866" ,       TYPE_AB,  1.0f,   0.866f ,0},       //
  {  0,  0,  "1866" ,       TYPE_AB,  1.0f,   1.866f ,0},       //
  {  0,  0,  " 1:4" ,       TYPE_AB,  1.0f,   4.0f    ,0},
  {  0,  0,  " 1:5" ,       TYPE_AB,  1.0f,   5.0f    ,0},
  {  0,  0,  " 1:7" ,       TYPE_AB,  1.0f,   7.0f    ,0},
  {  0,  0,  "1:10" ,       TYPE_AB,  1.0f,   10.0f   ,0},      //1:10 HSK-конус и другие
  {  0,  0,  "1:16" ,       TYPE_AB,  1.0f,   16.0f   ,0},
  {  0,  0,  "1:20" ,       TYPE_AB,  1.0f,   20.0f   ,0},      //1:20 Метрические конуса №4, №6, №80, №100, №120, №160, №200  [ГОСТ 25557-2006]
  {  0,  0,  "1:24" ,       TYPE_AB,  1.0f,   24.0f   ,0},
  {  0,  0,  "1:30" ,       TYPE_AB,  1.0f,   30.0f   ,0},
  {  0,  0,  "1:50" ,       TYPE_AB,  1.0f,   50.0f   ,0},
  {  0,  0,  "7:24" ,       TYPE_AB,  7.0f,   24.0f   ,0},
  {  0,  0,  "7:64" ,       TYPE_AB,  7.0f,   64.0f   ,0},
  {  0,  0,  "  8\x00DF" ,  TYPE_DEG, 8.0f,   0.0f    ,0},      //УГОЛ 8°
  {  0,  0,  " 10\x00DF" ,  TYPE_DEG, 10.0f,  0.0f    ,0},      //УГОЛ 10°
  {  0,  0,  " 15\x00DF" ,  TYPE_DEG, 15.0f,  0.0f    ,0},      //УГОЛ 15°
  {  0,  0,  " 30\x00DF" ,  TYPE_DEG, 30.0f,  0.0f    ,0},      //УГОЛ 30°
  {  0,  0,  " A:B" ,       TYPE_AB,  1.0f,   7.0f   ,0},      //Пользовательский конус по соотношению сторон (нужно сохранять в EEPROM и загружать после инициализации массива резьб)
  {  0,  0,  "  A\x00DF" ,  TYPE_DEG, 8.0f,   0.0f   ,0}       //Пользовательская конус в градусах (нужно сохранять в EEPROM и загружать после инициализации массива резьб)
  
};
#define TOTAL_CONE (sizeof(Cone_Info) / sizeof(Cone_Info[0]))
//==================================================================================================================================
//КОНУСА
// ***** Threads *****
typedef struct
{
  byte Ks_Div_Z;
  int  Km_Div_Z;
  byte Ks_Div_X;
  int  Km_Div_X;
  char Thread_Print[7];
  float Step;
  byte Pass;
  char Limit_Print[8];
} thread_info_type;

//NEW (LCD + SETUP)
thread_info_type Thread_Info[] =
{
  //мм
  //  { 0,  0,  0,  0,  "0.075", 0.075, 4, "750" },           //по ГОСТ 24705-2004
  //  { 0,  0,  0,  0,  "0.08", 0.080,  4, "750" },           //по ГОСТ 24705-2004
  //  { 0,  0,  0,  0,  "0.09", 0.090,  4, "750" },           //по ГОСТ 24705-2004
  //  { 0,  0,  0,  0,  "0.10", 0.100,  4, "750" },           //по ГОСТ 24705-2004
  //  { 0,  0,  0,  0,  "0.125", 0.125, 4, "750" },           //по ГОСТ 24705-2004
  //  { 0,  0,  0,  0,  "0.15", 0.150,  4, "750" },           //по ГОСТ 24705-2004
  //  { 0,  0,  0,  0,  "0.175", 0.175, 4, "750" },           //по ГОСТ 24705-2004
  //  { 0,  0,  0,  0,  "0.20", 0.200,  4, "750" },           //по ГОСТ 24705-2004

  { 0,  0,  0,  0,  "0.25", 0.250,  4, "750" },
  { 0,  0,  0,  0,  "0.30", 0.300,  4, "750" },
  { 0,  0,  0,  0,  "0.35", 0.350,  4, "750" },
  { 0,  0,  0,  0,  "0.40", 0.400,  4, "750" },
  { 0,  0,  0,  0,  "0.50", 0.500,  4, "750" },
  { 0,  0,  0,  0,  "0.60", 0.600,  4, "750" },
  { 0,  0,  0,  0,  "0.70", 0.700,  4, "750" },
  { 0,  0,  0,  0,  "0.75", 0.750,  5, "750" },
  { 0,  0,  0,  0,  "0.80", 0.800,  5, "700" },
  { 0,  0,  0,  0,  "1.00", 1.000,  6, "560" },
  { 0,  0,  0,  0,  "1.25", 1.250,  7, "460" },
  { 0,  0,  0,  0,  "1.50", 1.500,  7, "380" },
  { 0,  0,  0,  0,  "1.75", 1.750,  8, "320" },
  { 0,  0,  0,  0,  "2.00", 2.000,  9, "280" },
  { 0,  0,  0,  0,  "2.50", 2.500, 11, "220" },
  { 0,  0,  0,  0,  "3.00", 3.000, 15, "190" },
  { 0,  0,  0,  0,  "4.00", 4.000, 22, "140" },

  { 0,  0,  0,  0,  "4.50", 4.500, 22, "140" },           //по ГОСТ 24705-2004
  { 0,  0,  0,  0,  "5.00", 5.000, 22, "140" },           //по ГОСТ 24705-2004
  { 0,  0,  0,  0,  "5.50", 5.500, 22, "140" },           //по ГОСТ 24705-2004
  { 0,  0,  0,  0,  "6.00", 6.000, 22, "140" },           //по ГОСТ 24705-2004
  { 0,  0,  0,  0,  "8.00", 8.000, 22, " 70" },           //по ГОСТ 24705-2004

  //tpi
  { 0,  0,  0,  0,  " 80", (25.4 / 80.0),  4, "750" },    //Было 0.318
  { 0,  0,  0,  0,  " 72", (25.4 / 72.0),  4, "750" },    //Было 0.353
  { 0,  0,  0,  0,  " 64", (25.4 / 64.0),  4, "750" },    //Было 0.397
  { 0,  0,  0,  0,  " 60", (25.4 / 60.0),  4, "750" },    //Было 0.423
  { 0,  0,  0,  0,  " 56", (25.4 / 56.0),  4, "750" },    //Было 0.454
  { 0,  0,  0,  0,  " 48", (25.4 / 48.0),  4, "750" },    //Было 0.529
  { 0,  0,  0,  0,  " 44", (25.4 / 44.0),  4, "750" },    //Было 0.577
  { 0,  0,  0,  0,  " 40", (25.4 / 40.0),  4, "750" },    //Было 0.635
  { 0,  0,  0,  0,  " 36", (25.4 / 36.0),  5, "750" },    //Было 0.706
  { 0,  0,  0,  0,  " 32", (25.4 / 32.0),  5, "710" },    //Было 0.794
  { 0,  0,  0,  0,  " 28", (25.4 / 28.0),  5, "650" },    //Было 0.907 [ГОСТ 6357-81 Резьба трубная цилиндрическая Шаг 0,907 мм]
  { 0,  0,  0,  0,  " 27", (25.4 / 27.0),  5, "600" },    //Было 0.941
  { 0,  0,  0,  0,  " 26", (25.4 / 26.0),  6, "570" },    //Было 0.977
  { 0,  0,  0,  0,  " 24", (25.4 / 24.0),  6, "500" },    //Было 1.058
  { 0,  0,  0,  0,  " 22", (25.4 / 22.0),  6, "450" },    //Было 1.155
  { 0,  0,  0,  0,  " 20", (25.4 / 20.0),  7, "440" },    //Было 1.270
  { 0,  0,  0,  0,  " 19", (25.4 / 19.0),  7, "420" },    //Было 1.337 [ГОСТ 6357-81 Резьба трубная цилиндрическая Шаг 1,337 мм]
  { 0,  0,  0,  0,  " 18", (25.4 / 18.0),  7, "380" },    //Было 1.411
  { 0,  0,  0,  0,  " 16", (25.4 / 16.0),  8, "350" },    //Было 1.588
  { 0,  0,  0,  0,  " 14", (25.4 / 14.0),  9, "320" },    //Было 1.814 [ГОСТ 6357-81 Резьба трубная цилиндрическая Шаг 1,814 мм]
  { 0,  0,  0,  0,  " 13", (25.4 / 13.0), 10, "280" },    //
  { 0,  0,  0,  0,  " 12", (25.4 / 12.0), 10, "270" },    //Было 2.117
  { 0,  0,  0,  0,  " 11", (25.4 / 11.0), 11, "230" },    //           [ГОСТ 6357-81 Резьба трубная цилиндрическая Шаг 2,309 мм]
  { 0,  0,  0,  0,  " 10", (25.4 / 10.0), 11, "220" },    //Было 2.540
  { 0,  0,  0,  0,  "  9", (25.4 / 9.0),  14, "190" },    //Было 2.822
  { 0,  0,  0,  0,  "  8", (25.4 / 8.0),  16, "170" },    //Было 3.175
  { 0,  0,  0,  0,  "  7", (25.4 / 7.0),  19, "150" },    //Было 3.629
  { 0,  0,  0,  0,  "  6", (25.4 / 6.0),  24, "140" },    //Было 4.233
  { 0,  0,  0,  0,  "Custom", 1.000f,  6, "usr" }         //Пользовательская резьба (её нужно сохранять в EEPROM и загружать после инициализации массива резьб)
};
#define TOTAL_THREADS (sizeof(Thread_Info) / sizeof(Thread_Info[0]))
#define Thrd_Accel_Err Thread_Info[0].Ks_Div_Z                 // неверно задано ускорение
//static_assert(Thrd_Accel_Err + THRD_ACCEL <= 255, "Неверно задано значение THRD_ACCEL");
//static_assert(Ks_Div_Z_0250 + THRD_ACCEL <= 255, "Неверно задано значение THRD_ACCEL");
//==================================================================================================================================
#endif
