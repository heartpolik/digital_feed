//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ***** Setup ***** ///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <avr/eeprom.h>
#include "CONFIG.h"

#define RUS
#define USER_THREAD_MIN 0.075f
#define USER_THREAD_MAX 8.000f
#define USER_THREAD_STEP 0.0001f
#define USER_THREAD_CHANGE_SPEED 20

#define USER_CONEAB_MIN           1.0f
//#define USER_CONEAB_MAX           100.0f
#define USER_CONEAB_MAX           254.0f
#define USER_CONEAB_STEP          0.0001f
#define USER_CONEAB_CHANGE_SPEED  20

#define USER_CONEDEG_MIN           0.1f
//#define USER_CONEDEG_MAX           75.0f
#define USER_CONEDEG_MAX           89.9f
#define USER_CONEDEG_STEP          0.01f
#define USER_CONEDEG_CHANGE_SPEED  5

const char EMPTY16[]              = "                ";           //16 знакомест, из них 0 русских знаков
const char EMPTY16Blink[]         = "ÿ               ";           //16 знакомест, первый символ char 255
const char FAILURE[]              = "!!!!!!!!!!!!!!!!";           //16 знакомест
const char MAYBEFAILURE[]         = "????????????????";           //16 знакомест
#ifdef RUS
const char PARAM1[]               = "  KOHФИГУPAЦИЯ  ";           //16 знакомест, из них 6 русских знака "Ф И Г У Ц Я"
const char PARAM2[]               = "   ПAPAMETPOB   ";           //16 знакомест, из них 1 русский знак "П"
const char THREAD1[]              = "  KOЭФФИЦИEHTЫ  ";           //16 знакомест, из них 5 русских знаков "Э Ф И Ц Ы"
const char THREAD2[]              = "     PEЗЬБ      ";           //16 знакомест, из них 3 русских знака "З Ь Б"
const char CONE1[]                = "  KOЭФФИЦИEHTЫ  ";           //16 знакомест, из них 5 русских знаков "Э Ф И Ц Ы"
const char CONE2[]                = "     KOHУCOB    ";           //16 знакомест, из них 1 русский знак "У"
const char RESET_TO_DEFAULTS1[]   = " CБPOC HACTPOEK ";           //16 знакомест, из них 1 русский знак "Б"
const char RESET_TO_DEFAULTS2[]   = "  HA ДEФOЛTHЫE  ";           //16 знакомест, из них 4 русских знака "Д Ф Л Ы"
const char EXIT_SAVING1[]         = "   COXPAHИTЬ    ";           //16 знакомест, из них 2 русских знака "И Ь"
const char EXIT_SAVING2[]         = "    И BЫЙTИ     ";           //16 знакомест, из них 3 русских знака "И Ы Й"
const char EXIT_NOTSAVING1[]      = "  HE COXPAHЯTЬ  ";           //16 знакомест, из них 2 русских знака "Я Ь"
const char EXIT_NOTSAVING2[]      = "    И BЫЙTИ     ";           //16 знакомест, из них 3 русских знака "И Ы Й"
const char THREAD3[]              = "PEЗЬБA:   ";                 //10 знакомест, из них 3 русских знака "З Ь Б"
const char CONE3[]                = "KOHУC: ";                    //7 знакомест, из них 1 русский знак "У"
const char DONE1[]                = " CБPOC HACTPOEK ";           //16 знакомест, из них 1 русский знак "Б"
const char DONE2[]                = "    BЫПOЛHEH    ";           //16 знакомест, из них 3 русских знака "Ы П Л"
const char YES_NO1[]              = "   BЫ УBEPEHЫ?  ";           //16 знакомест, из них 2 русских знака "Ы У"
const char YES_NO2[]              = "<-- HET    ДA-OK";           //16 знакомест, из них 2 русских знака "Т Д"
const char STEP[]                 = "ШAГ:  ";                     //6  знакомест, из них 2 русских знака "Ш Г"
const char PASS[]                 = "Пp.:  ";                     //6  знакомест, из них 1 русский знак "П"
const char RESET_USER_THREAD[]    = "PEЗЬБA  'Custom'";           //16 знакомест, из них 3 русских знака "З Ь Б"
const char RESET_USER_MSG1[]      = "    CБPOШEHA    ";           //16 знакомест, из них 2 русских знака "Б Ш"
const char RESET_USER_CONEAB[]    = "   KOHУC 'A:B'  ";           //16 знакомест, из них 1 русский знак "У"
const char RESET_USER_CONEDEG[]   = "   KOHУC 'A\x00DF'   ";      //16 знакомест, из них 1 русский знак "У"
const char RESET_USER_MSG2[]      = "    CБPOШEH     ";           //16 знакомест, из них 2 русских знака "Б Ш"
const char ERROR_CONE1[]          = " OШИБKA KOHУCA: ";           //16 знакомест, из них 4 русских знака "Ш И Б У"
#else
const char PARAM1[]               = "   SHOW & EDIT  ";           //16 знакомест
const char PARAM2[]               = "    FEATURES    ";           //16 знакомест
const char THREAD1[]              = "   SHOW Ks/Km   ";           //16 знакомест
const char THREAD2[]              = "     THREAD     ";           //16 знакомест
const char CONE1[]                = "   SHOW Ks/Km   ";           //16 знакомест
const char CONE2[]                = "      CONE      ";           //16 знакомест
const char RESET_TO_DEFAULTS1[]   = "    LOAD  TO    ";           //16 знакомест
const char RESET_TO_DEFAULTS2[]   = "    DEFAULTS    ";           //16 знакомест
const char EXIT_SAVING1[]         = "  SAVE & EXIT   ";           //16 знакомест
const char EXIT_SAVING2[]         = "     SETUP      ";           //16 знакомест
const char EXIT_NOTSAVING1[]      = "  EXIT WITHOUT  ";           //16 знакомест
const char EXIT_NOTSAVING2[]      = "     SAVING     ";           //16 знакомест
const char THREAD3[]              = "THREAD:   ";                 //10 знакомест
const char CONE3[]                = "CONE:  ";                    //7  знакомест
const char DONE1[]                = "     RESET      ";           //16 знакомест
const char DONE2[]                = "   COMPLETED    ";           //16 знакомест
const char YES_NO1[]              = "  ARE YOU SURE? ";           //16 знакомест
const char YES_NO2[]              = "<-- NO    YES-OK";           //16 знакомест
const char STEP[]                 = "Step: ";                     //6  знакомест
const char PASS[]                 = "Pass: ";                     //6  знакомест
const char RESET_USER_THREAD[]    = "Thread  'Custom'";           //16 знакомест
const char RESET_USER_MSG1[]      = "     Reset      ";           //16 знакомест
const char RESET_USER_CONEAB[]    = "   Cone 'A:B'   ";           //16 знакомест
const char RESET_USER_CONEDEG[]   = "    Cone 'A\x00DF'   ";      //16 знакомест
const char RESET_USER_MSG2[]      = "     Reset      ";           //16 знакомест
const char ERROR_CONE1[]          = "   ERROR CONE:  ";           //16 знакомест
#endif

//Для кнопок
#define DELAY_SETUP_ENTER_KEYCYCLE 4    //Задержка для входа в режим автонажатия. Значения от 1 до разумного максимума. По умолчанию 4.
#define DELAY_SETUP_INTO_KEYCYCLE 1     //Интервал срабатывания автонажатия. Значения от 1 до DELAY_SETUP_ENTER_KEYCYCLE. По умолчанию 1.
byte Setup_KeyCycle = 0;                //Это глобальная переменная счётчик циклов обработчика клавиш стрелок. Размерность byte, наверное хватит.
byte CURRENT_THREAD = 0;
byte CURRENT_CONE = 0;

//Список режимов при входе в меню SETUP
enum SETUP_Mode
{
  MODE_PARAMETERS = 1,            //ПРОСМОТР И РЕДАКТИРОВАНИЕ ОСНОВНЫХ ПАРАМЕТРОВ "ЖЕЛЕЗА"
  MODE_READ_THREAD,               //ПРОСМОТР КОЭФФИЦИЕНТОВ РЕЗЬБ + РЕДАКТИРОВАНИЕ 1 ПОЛЬЗОВАТЕЛЬСКОЙ РЕЗЬБЫ
  MODE_READ_CONE,                 //ПРОСМОТР КОЭФФИЦИЕНТОВ КОНУСОВ + РЕДАКТИРОВАНИЕ 2 ПОЛЬЗОВАТЕЛЬСКИХ КОНУСОВ (A:B и DEG)
  MODE_RESET_TO_DEFAULTS,         //СБРОС НАСТРОЕК НА ДЕФОЛТНЫЕ (Требует последующего сохранения перед выходом)
  MODE_EXIT_AND_SAVING,           //ВЫХОД И СОХРАНЕНИЕ ИЗМЕНЕНИЙ
  MODE_EXIT_WITHOUT_SAVING        //ВЫХОД БЕЗ СОХРАНЕНИЯ
};
//В LAST_SETUP_Mode значение последнего элемента списка
#define LAST_SETUP_Mode MODE_EXIT_WITHOUT_SAVING
byte SETUP_MODE = MODE_PARAMETERS;

bool bModeParameters = false;     //Признак нахождения внутри меню MODE_PARAMETERS для просмотра или редактирования параметров
bool bModeThread = false;         //Признак нахождения внутри меню MODE_READ_THREAD для просмотра коэффициентов Резьб
bool bModeCone = false;           //Признак нахождения внутри меню MODE_READ_CONE для просмотра коэффициентов Конусов
bool bModeResetToDefaults = false;//Признак нахождения внутри меню MODE_RESET_TO_DEFAULTS
bool bModeSaveAndExit = false;    //Признак нахождения внутри меню MODE_EXIT_AND_SAVING
bool bModeWithoutExit = false;    //Признак нахождения внутри меню MODE_EXIT_WITHOUT_SAVING

bool bEditParameters = false;     //Признак нахождения внутри меню MODE_PARAMETERS в режиме редактирования параметра
bool bEditUserThread = false;     //Признак нахождения внутри меню MODE_READ_THREAD в режиме редактирования параметра пользовательской резьбы
bool bEditUserConeAB = false;     //Признак нахождения внутри меню MODE_READ_CONE в режиме редактирования параметра пользовательского конуса по соотношению сторон A:B
bool bEditUserConeDEG = false;    //Признак нахождения внутри меню MODE_READ_CONE в режиме редактирования параметра пользовательского конуса заданного в градусах
unsigned int scaleFloat = 1;      //Множитель для режима правки пользовательской резьбы.

//Список переменных, которые можно изменить через этот Setup
enum SETUP_id
{
  ID_ENC_LINE_PER_REV = 1,
  ID_MOTOR_Z_STEP_PER_REV,
  ID_SCREW_Z,
  ID_McSTEP_Z,
  ID_REBOUND_Z,
  ID_MOTOR_X_STEP_PER_REV,
  ID_SCREW_X,
  ID_McSTEP_X,
  ID_REBOUND_X,

  ID_THRD_ACCEL,                //Fix Отсутствовали
  ID_FEED_ACCEL,                //Fix Отсутствовали

  ID_MIN_FEED,
  ID_MAX_FEED,
  ID_MIN_aFEED,
  ID_MAX_aFEED,
  ID_MAX_RAPID_MOTION,
  ID_MIN_RAPID_MOTION,
  ID_REPEAt,
  ID_HC_SCALE_1,
  ID_HC_SCALE_10,
  ID_HC_START_SPEED_1,
  ID_HC_MAX_SPEED_1,
  ID_HC_START_SPEED_10,
  ID_HC_MAX_SPEED_10,
  ID_HC_X_DIR
  //,
  //ID_DELAY_MOTOR_Z_ENABLE,
  //ID_DELAY_MOTOR_X_ENABLE
};
//В LAST_SETUP_id значение последнего элемента списка
#define LAST_SETUP_id ID_HC_X_DIR
byte SETUP_ID = ID_ENC_LINE_PER_REV;

//==============================================================================================================================================================================================================
//====================================================     ФОРМУЛЫ ДЛЯ РЕЗЬБ И КОНУСОВ     =====================================================================================================================
//==============================================================================================================================================================================================================
unsigned int _round(float A, byte* B)
{
  unsigned int AA = (unsigned int)A;
  if (A - AA >= 0.5f)
  {
    AA = AA + 1;
  }
  if (AA >= 10000)         //Если round округлил 9999.ххх до 10000, то второй коэффициент делаем 0, а первому добавляем 1
  {
    AA = 0;
    *B = *B + 1;
  }
  return AA;
}

//Формулы для Резьб
//При вызове передаётся float-ШАГ РЕЗЬБЫ и два указателя на переменные, в которые положим результат вычисления
void Calc_K_Z(float x, byte* Ks_Div_Z, int* Km_Div_Z)
//float Calc_K_Z(float x, byte* Ks_Div_Z, int* Km_Div_Z)
{
  float Kz = (ENC_LINE_PER_REV * 200.0 * SCREW_Z  / (10000.0 * MOTOR_Z_STEP_PER_REV * McSTEP_Z * (float)x)  );
  *Ks_Div_Z = (byte)(Kz);
  //Более сложная формула с округлением по математическим правиламм. Не используя библиотеку <math.h>
  *Km_Div_Z = _round(10000.0 * (Kz - (byte)(Kz)), Ks_Div_Z);
  //return Kz;
}

float MinimumStepZ(float Divider)
{
  return (float)((float)(ENC_LINE_PER_REV * 200.0f * SCREW_Z  / (10000.0f * MOTOR_Z_STEP_PER_REV * McSTEP_Z) / (float)Divider) );
}

//При вызове передаётся float-ШАГ РЕЗЬБЫ и два указателя на переменные, в которые положим результат вычисления
void Calc_K_X(float x, byte *Ks_Div_X, int *Km_Div_X)
//float Calc_K_X(float x, byte *Ks_Div_X, int *Km_Div_X)
{
  float Kx = (ENC_LINE_PER_REV * 200.0 * SCREW_X  / (10000.0 * MOTOR_X_STEP_PER_REV * McSTEP_X * (float)x)  );
  *Ks_Div_X = (byte)(Kx);
  //Более сложная формула с округлением по математическим правиламм. Не используя библиотеку <math.h>
  *Km_Div_X = _round(10000.0 * (Kx - (byte)(Kx)), Ks_Div_X);
  //return Kx;
}

float MinimumStepX(float Divider)
{
  return (float)((float)(ENC_LINE_PER_REV * 200.0f * SCREW_X  / (10000.0f * MOTOR_X_STEP_PER_REV * McSTEP_X) / (float)Divider) );
}

//ФОРМУЛЫ ДЛЯ КОНУСОВ
//КОНУС по соотношению сторон
//При вызове передаётся две float переменные СООТНОШЕНИЕ СТОРОН и два указателя на переменные, в которые положим результат вычисления
//void Calc_C_AB(float x, float y, byte *Cs_Div, int *Cm_Div)
//float Calc_C_AB(float x, float y, byte *Cs_Div, int *Cm_Div)
//void Calc_C_AB(float x, float y, byte *Cs_Div, int *Cm_Div, byte *XZ)

bool Calc_C_AB(float x, float y, byte *Cs_Div, int *Cm_Div, byte *XZ)
{
  //Проверка исходных данных (чтобы не было деления на 0 или отрицательных чисел)
  if (x <= 0.0f || y <= 0.0f)
  {
    *Cs_Div = (byte)0;
    *Cm_Div = (int)0;
    *XZ = (byte)0;
    return false;
  }
  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  float Cs = (  ((SCREW_X * 0.01) / (MOTOR_X_STEP_PER_REV * McSTEP_X) * ((float)y) * 2.0) / ((SCREW_Z * 0.01) / (MOTOR_Z_STEP_PER_REV * McSTEP_Z) * (((float)x) * 0.5) )  );
  //*Cs_Div = (byte)(Cs);
  //Более сложная формула с округлением по математическим правиламм. Не используя библиотеку <math.h>
  //*Cm_Div = _round(10000.0 * (Cs - (byte)(Cs)), Cs_Div);
  //return Cs;

  //Новый код для конусов с разным типом тактования Z->X или X->Z
  if (Cs >= 1.0f)           //тактование Z->X
  {
    //Проверка от переполнения *Cs_Div (ограничение типа byte 255)
    if (Cs > 254.99f)     //Есть переполнение: сбрасываем в 0 и возвращаем false
    {
      *Cs_Div = (byte)0;
      *Cm_Div = (int)0;
      *XZ = (byte)0;
      return false;
    } else {              //Переполнения нет...
      *Cs_Div = (byte)(Cs);
      *Cm_Div = _round(10000.0 * (Cs - (byte)(Cs)), Cs_Div);    //Более сложная формула с округлением по математическим правиламм. Не используя библиотеку <math.h>
      *XZ = (byte)0;       //Возврат byte 0 для тактования Z->X (Обычное тактование как использовал Олег, Cs_Div >= 1)
    }
  } else {                //тактование X->Z
    Cs = 1.0f / Cs;
    //Проверка от переполнения *Cs_Div (ограничение типа byte 255)
    if (Cs > 254.99f)     //Есть переполнение: сбрасываем в 0 и возвращаем false
    {
      *Cs_Div = (byte)0;
      *Cm_Div = (int)0;
      *XZ = (byte)0;
      return false;
    } else {              //Переполнения нет...
      *Cs_Div = (byte)(Cs);
      *Cm_Div = _round(10000.0 * (Cs - (byte)(Cs)), Cs_Div);    //Более сложная формула с округлением по математическим правиламм. Не используя библиотеку <math.h>
      *XZ = (byte)1;       //Возврат byte 1 для тактования X->Z (Новое тактование для конусов с соотношением Cs_Div < 1)
    }
  }
  return true;
}

//"Обратная" функция к Calc_C_AB
//float Get_A_AB(float B, float Divider)
//{
//  float tmp = (float)(4.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z) / (float)((float)Divider * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X);
//  return (float)(B * tmp);
//}

//"Обратная" функция к Calc_C_AB с учётом типа тактования конуса
float Get_A_AB(float B, float Divider, byte XZ)
{
  float tmp;
  if (XZ == (byte)0)
  {
    tmp = (float)(4.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z) / (float)((float)Divider * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X);
  } else {
    float DividerXZ = 1.0f / Divider;
    tmp = (float)(4.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z) / (float)((float)DividerXZ * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X);
  }
  return (float)(B * tmp);
}


//"Обратная" функция к Calc_C_AB
//float Get_B_AB(float A, float Divider)
//{
//  float tmp = (float)(4.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z) / (float)((float)Divider * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X);
//  return (float)(A / tmp);
//}

//"Обратная" функция к Calc_C_AB с учётом типа тактования конуса
float Get_B_AB(float A, float Divider, byte XZ)
{
  float tmp;
  if (XZ == (byte)0)
  {
    tmp = (float)(4.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z) / (float)((float)Divider * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X);
  } else {
    float DividerXZ = 1.0f / Divider;
    tmp = (float)(4.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z) / (float)((float)DividerXZ * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X);
  }
  return (float)(A / tmp);
}

//КОНУС по углу
//При вызове передаётся float переменная УГОЛ КОНУС В ГРАДУСАХ и два указателя на переменные, в которые положим результат вычисления
//void Calc_C_DEG(float x, byte *Cs_Div, int *Cm_Div)
//float Calc_C_DEG(float x, byte *Cs_Div, int *Cm_Div)
//void Calc_C_DEG(float x, byte *Cs_Div, int *Cm_Div, byte *XZ)

bool Calc_C_DEG(float x, byte *Cs_Div, int *Cm_Div, byte *XZ)
{
  //Проверка допустимого диапазона угла x (ограничения функции тангенса от 0 не включительно до 90 не включительно) ---------------------------------------------------------------------------------------------------
  if (x <= 0.0f || x >= 90.0f)
  {
    //Есть переполнение: сбрасываем в 0 и возвращаем false
    *Cs_Div = (byte)0;
    *Cm_Div = (int)0;
    *XZ = (byte)0;
    return false;
  }
  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  float Cs = (  ((SCREW_X * 0.01) / (MOTOR_X_STEP_PER_REV * McSTEP_X) * 2.0) / ((SCREW_Z * 0.01) / (MOTOR_Z_STEP_PER_REV * McSTEP_Z) * ( tan( ((M_PI / 180.0) * x ) ) ) ) );
  //*Cs_Div = (byte)(Cs);
  //Более сложная формула с округлением по математическим правиламм. Не используя библиотеку <math.h>
  //*Cm_Div = _round(10000.0 * (Cs - (byte)(Cs)), Cs_Div);
  //return Cs;

  //Новый код для конусов с разным типом тактования Z->X или X->Z
  if (Cs >= 1.0f)           //тактование Z->X
  {
    //Проверка от переполнения *Cs_Div (ограничение типа byte 255)
    if (Cs > 254.99f)     //Есть переполнение: сбрасываем в 0 и возвращаем false
    {
      *Cs_Div = (byte)0;
      *Cm_Div = (int)0;
      *XZ = (byte)0;
      return false;
    } else {              //Переполнения нет...
      *Cs_Div = (byte)(Cs);
      *Cm_Div = _round(10000.0 * (Cs - (byte)(Cs)), Cs_Div);    //Более сложная формула с округлением по математическим правиламм. Не используя библиотеку <math.h>
      *XZ = (byte)0;       //Возврат byte 0 для тактования Z->X (Обычное тактование как использовал Олег, Cs_Div >= 1)
      //return true;
    }
  } else {                //тактование X->Z
    //DEBUG
    //Serial.print("Cone  ");Serial.print(int(x));Serial.print(" orig=");Serial.print(String(Cs, 4));
    Cs = 1.0f / Cs;       //Cs при правильных коэффициентах 0 быть не может - так что деления на 0 не будет.
    //Проверка от переполнения *Cs_Div (ограничение типа byte 255)
    if (Cs > 254.99f)     //Есть переполнение: сбрасываем в 0 и возвращаем false
    {
      *Cs_Div = (byte)0;
      *Cm_Div = (int)0;
      *XZ = (byte)0;
      return false;
    } else {              //Переполнения нет...
      *Cs_Div = (byte)(Cs);
      *Cm_Div = _round(10000.0 * (Cs - (byte)(Cs)), Cs_Div);    //Более сложная формула с округлением по математическим правиламм. Не используя библиотеку <math.h>
      *XZ = (byte)1;       //Возврат byte 1 для тактования X->Z (Новое тактование для конусов с соотношением Cs_Div < 1)
      //return true;
    }
  }
  //DEBUG
  //Serial.print(" new=");Serial.print(String(Cs, 4));Serial.print(" XZ=1\n\r");
  return true;
}

//"Обратная" функция - по делителю определить угол конуса
//float Get_deg_DEG(float Divider)
//{
//  //float Cs = (  ((SCREW_X * 0.01) / (MOTOR_X_STEP_PER_REV * McSTEP_X) * 2.0) / ((SCREW_Z * 0.01) / (MOTOR_Z_STEP_PER_REV * McSTEP_Z) * ( tan( ((M_PI / 180.0) * x ) ) ) ) );
//  float x = (180.0f / M_PI) * atan( 2.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z / (float(Divider) * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X) );
//  return x;
//}

//"Обратная" функция - по делителю определить угол конуса с учётом типа тактования
float Get_deg_DEG(float Divider, byte XZ)
{
  //  float x = (180.0f / M_PI) * atan( 2.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z / (float(Divider) * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X) );
  //  return x;

  float x;
  if (XZ == (byte)0)     //XZ == 0 Тип тактования ZX
  {
    x = (180.0f / M_PI) * atan( 2.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z / (float(Divider) * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X) );
  } else {              //XZ == 1 Тип тактования XZ
    float DividerXZ = 1.0f / Divider;
    x = (180.0f / M_PI) * atan( 2.0f * SCREW_X * MOTOR_Z_STEP_PER_REV * McSTEP_Z / (float(DividerXZ) * SCREW_Z * MOTOR_X_STEP_PER_REV * McSTEP_X) );
  }
  return x;
}

void Setup_Print_LCD_MSG(const char message_1[] , const char message_2[])
{
  lcd.setCursor(0, 0);
  lcd.print(message_1);
  lcd.setCursor(0, 1);
  lcd.print(message_2);
  _delay_ms(1000);
}

//Заполнение массива РЕЗЬБ коэффициентами
void Init_All_Thread()
{
  float MinThreadStep_Z  = MinimumStepZ(254.99f);     //Шаг дающий коэффициент Ks_Z = 254.99 (Максимальное значение 255)
  float MinThreadStep_X  = MinimumStepX(254.99f);     //Шаг дающий коэффициент Ks_X = 254.99 (Максимальное значение 255)
  //float MaxThreadStep_Z  = MinimumStepZ(2.0f);         //Шаг дающий коэффициент Ks_Z = 2 (Минимально устойчивая работа)
  //float MaxThreadStep_X  = MinimumStepX(2.0f);         //Шаг дающий коэффициент Ks_X = 2 (Минимально устойчивая работа)

  float MaxThreadStep_Z  = MinimumStepZ(1.0f);         //Шаг дающий коэффициент Ks_Z = 1 (Минимально устойчивая работа с новым алгоритмом в INT0)
  float MaxThreadStep_X  = MinimumStepX(1.0f);         //Шаг дающий коэффициент Ks_X = 1 (Минимально устойчивая работа с новым алгоритмом в INT0)
  
  float MinStep = MinThreadStep_Z;
  if (MinThreadStep_X > MinStep) MinStep = MinThreadStep_X;
  float MaxStep = MaxThreadStep_Z;
  if (MaxThreadStep_X < MaxStep) MaxStep = MaxThreadStep_X;

  for (uint16_t i = 0; i < (sizeof(Thread_Info) / sizeof(Thread_Info[0])); i++)
  {
    Calc_K_Z(Thread_Info[i].Step, &Thread_Info[i].Ks_Div_Z, &Thread_Info[i].Km_Div_Z);
    Calc_K_X(Thread_Info[i].Step, &Thread_Info[i].Ks_Div_X, &Thread_Info[i].Km_Div_X);
    //---------------   Проверка пользовательской резьбы   ----------------------------
    if (i == ((sizeof(Thread_Info) / sizeof(Thread_Info[0])) - 1))
    {
      if (Thread_Info[i].Step < MinStep || Thread_Info[i].Step > MaxStep )
      {
        Thread_Info[i].Step = 0.5f * (MinStep + MaxStep);
        Calc_K_Z(Thread_Info[i].Step, &Thread_Info[i].Ks_Div_Z, &Thread_Info[i].Km_Div_Z);
        Calc_K_X(Thread_Info[i].Step, &Thread_Info[i].Ks_Div_X, &Thread_Info[i].Km_Div_X);
        //Вывод сообщения о сбросе
        Setup_Print_LCD_MSG(RESET_USER_THREAD, RESET_USER_MSG1);
      }
    }
    //----------------------------------------------------------------------------------
  }
}

//Заполнение массива КОНУСОВ коэффициентами
void Init_All_Cone()
{
  //Рассчитываем минимальный и максимальный углы и сравниваем.
  //float MinimumConeDEG = Get_deg_DEG(254.99f);
  //float MaximumConeDEG = Get_deg_DEG(2.0f);
  //Рассчитываем минимальный и максимальный углы и сравниваем, с учётом типа тактования конуса
  float MinimumConeDEG = Get_deg_DEG(254.99f, (byte)0);
  float MaximumConeDEG = Get_deg_DEG(254.99f, (byte)1);
  char LCD_Row_1[17];    //Буферы для вывода на экран LCD.

  for (uint16_t i = 0; i < (sizeof(Cone_Info) / sizeof(Cone_Info[0])); i++)
  {
    if (Cone_Info[i].Type == TYPE_DEG)
    {
      ////Calc_C_DEG(Cone_Info[i].C1, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div);
      //Calc_C_DEG(Cone_Info[i].C1, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div, &Cone_Info[i].XZ);                          //New с выбором тактования Z->X или X->Z
      //Дополнительно вводим проверку допустимости конуса. В случае ошибки выводим надпись на экран LCD - сами коэфф. заполняются нулями
      if (!Calc_C_DEG(Cone_Info[i].C1, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div, &Cone_Info[i].XZ))
      {
        lcd.setCursor(0, 0);
        lcd.print(ERROR_CONE1);
        lcd.setCursor(0, 1);
        snprintf(LCD_Row_1, 17, "      %s      ", Cone_Info[CURRENT_CONE].Cone_Print);
        lcd.print(LCD_Row_1);
        _delay_ms(1000);
      }
    } else {
      ////Calc_C_AB(Cone_Info[i].C1, Cone_Info[i].C2, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div);
      //Calc_C_AB(Cone_Info[i].C1, Cone_Info[i].C2, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div, &Cone_Info[i].XZ);          //New с выбором тактования Z->X или X->Z
      //Дополнительно вводим проверку допустимости конуса. В случае ошибки выводим надпись на экран LCD - сами коэфф. заполняются нулями
      if(!Calc_C_AB(Cone_Info[i].C1, Cone_Info[i].C2, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div, &Cone_Info[i].XZ))
      {
        lcd.setCursor(0, 0);
        lcd.print(ERROR_CONE1);
        lcd.setCursor(0, 1);
        snprintf(LCD_Row_1, 17, "      %s      ", Cone_Info[CURRENT_CONE].Cone_Print);
        lcd.print(LCD_Row_1);
        _delay_ms(1000);
      }
      
    }
    //------------------------------------------------------------------------------------------------------
    //Проверка пользовательских конусов
    if (i == ((sizeof(Cone_Info) / sizeof(Cone_Info[0])) - 2))
    {
      //float MinC2 = Get_B_AB(Cone_Info[i].C1, 2.0f);           //Расчёт допустимого значения C2 при заданном C1
      //float MaxC2 = Get_B_AB(Cone_Info[i].C1, 254.99f);       //Расчёт допустимого значения C2 при заданном C1

      float MinC2 = Get_B_AB(Cone_Info[i].C1, 254.99f, (byte)1);           //Расчёт допустимого значения C2 при заданном C1
      float MaxC2 = Get_B_AB(Cone_Info[i].C1, 254.99f, (byte)0);       //Расчёт допустимого значения C2 при заданном C1


      if (Cone_Info[i].C2 < MinC2 || Cone_Info[i].C2 > MaxC2)
      {
        Cone_Info[i].C2 = 0.5f * (MinC2 + MaxC2);
        //Calc_C_AB(Cone_Info[i].C1, Cone_Info[i].C2, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div);
        Calc_C_AB(Cone_Info[i].C1, Cone_Info[i].C2, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div, &Cone_Info[i].XZ);        //New с выбором тактования Z->X или X->Z
        //Вывод сообщения о сбросе "Конуса A:B"
        Setup_Print_LCD_MSG(RESET_USER_CONEAB, RESET_USER_MSG2);
      }
      //===========================================================================
    } else if (i == ((sizeof(Cone_Info) / sizeof(Cone_Info[0])) - 1))
    {
      //Рассчитываем минимальный и максимальный углы и сравниваем.
      if (Cone_Info[i].C1 < MinimumConeDEG || Cone_Info[i].C1 > MaximumConeDEG)
      {
        Cone_Info[i].C1 = 0.5f * (MinimumConeDEG + MaximumConeDEG);
        Cone_Info[i].C2 = 0.0f;
        Calc_C_DEG(Cone_Info[i].C1, &Cone_Info[i].Cs_Div, &Cone_Info[i].Cm_Div, &Cone_Info[i].XZ);                          //New с выбором тактования Z->X или X->Z
        //Вывод сообщения о сбросе "Конуса A°"
        Setup_Print_LCD_MSG(RESET_USER_CONEDEG, RESET_USER_MSG2);
      }
    }
    //------------------------------------------------------------------------------------------------------
  }
}

//Обновление параметров
void Update_Parameters()
{
  //Init Section (Обновление значения переменных зависимых от вышеперечисленных переменных и инициализированных при старте программы)
  ENC_TICK             = (int)(ENC_LINE_PER_REV * 2);   //int!!!
  Scale                = (byte)HC_SCALE_1;              //byte!!!
  tmp_Ks_Divisor       = (byte)THRD_ACCEL;              //byte!!!
  tmp_Accel            = (byte)THRD_ACCEL;              //byte!!!
  Start_Speed          = (uint16_t)(ENC_LINE_PER_REV / ((uint32_t)MOTOR_Z_STEP_PER_REV * McSTEP_Z * MIN_FEED / SCREW_Z) / FEED_ACCEL);
  max_OCR5A            = (uint16_t)(ENC_LINE_PER_REV / ((uint32_t)MOTOR_Z_STEP_PER_REV * McSTEP_Z * MIN_FEED / SCREW_Z) / FEED_ACCEL);     // Начальная скорость подачи при разгоне/торможении
  max_OCR4A            = (uint16_t)((250000 / ((uint32_t)MIN_aFEED * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1) / FEED_ACCEL);
  max_OCR3A            = (uint16_t)HC_START_SPEED_1;
  min_OCR3A            = (uint16_t)HC_MAX_SPEED_1;
  Cutter_Width         = Cutter_Width_array[Cutter_Step];
  Cutting_Width        = Cutting_Width_array[Cutting_Step];
  R_Quad               = Sph_R_mm * Sph_R_mm;

  Init_All_Thread();  //Пересчёт и заполнение коэффициентов РЕЗЬБ
  Init_All_Cone();    //Пересчёт и заполнение коэффициентов КОНУСОВ

  //RPM_Scale = ENC_LINE_PER_REV * 3 / 60 ;  // 3с интервал измерения
}

//Функция сброса настроек на дефолтные
void Reset_To_Defaults()
{
  ENC_LINE_PER_REV                = _ENC_LINE_PER_REV;
  MOTOR_Z_STEP_PER_REV            = _MOTOR_Z_STEP_PER_REV;
  SCREW_Z                         = _SCREW_Z;
  McSTEP_Z                        = _McSTEP_Z;
  MOTOR_X_STEP_PER_REV            = _MOTOR_X_STEP_PER_REV;
  SCREW_X                         = _SCREW_X;
  REBOUND_X                       = _REBOUND_X;
  REBOUND_Z                       = _REBOUND_Z;
  McSTEP_X                        = _McSTEP_X;
  //
  THRD_ACCEL                      = _THRD_ACCEL;
  FEED_ACCEL                      = _FEED_ACCEL;
  //
  MIN_FEED                        = _MIN_FEED;
  MAX_FEED                        = _MAX_FEED;
  MIN_aFEED                       = _MIN_aFEED;
  MAX_aFEED                       = _MAX_aFEED;
  // Ускоренные перемещения
  MAX_RAPID_MOTION                = _MAX_RAPID_MOTION;
  MIN_RAPID_MOTION                = _MIN_RAPID_MOTION;
  REPEAt                          = _REPEAt;
  // Ручной энкодер (100 линий)
  HC_SCALE_1                      = _HC_SCALE_1;
  HC_SCALE_10                     = _HC_SCALE_10;
  HC_START_SPEED_1                = _HC_START_SPEED_1;
  HC_MAX_SPEED_1                  = _HC_MAX_SPEED_1;
  HC_START_SPEED_10               = _HC_START_SPEED_10;
  HC_MAX_SPEED_10                 = _HC_MAX_SPEED_10;
  HC_X_DIR                        = _HC_X_DIR;
  //-----------------------------------------------------
  Update_Parameters();
  Setup_Print_LCD_MSG(DONE1 , DONE2);     //Вывод надписи, что настройки сброшены на дефолтные
}

//Сохранение в EEPROM настроек. Update - не выполняет запись в ячейку, если её значение осталось прежним
void Save_EEPROM()
{
  eeprom_update_word((uint16_t*)2, (uint16_t)ENC_LINE_PER_REV);
  eeprom_update_word((uint16_t*)4, (uint16_t)MOTOR_Z_STEP_PER_REV);
  eeprom_update_word((uint16_t*)6, (uint16_t)SCREW_Z);
  eeprom_update_word((uint16_t*)8, (uint16_t)McSTEP_Z);
  eeprom_update_word((uint16_t*)10, (uint16_t)MOTOR_X_STEP_PER_REV);
  eeprom_update_word((uint16_t*)12, (uint16_t)SCREW_X);
  eeprom_update_word((uint16_t*)14, (uint16_t)REBOUND_X);
  eeprom_update_word((uint16_t*)16, (uint16_t)REBOUND_Z);
  eeprom_update_word((uint16_t*)18, (uint16_t)McSTEP_X);
  //
  eeprom_update_word((uint16_t*)20, (uint16_t)THRD_ACCEL);    //byte --> unsigned int
  eeprom_update_word((uint16_t*)22, (uint16_t)FEED_ACCEL);
  //
  eeprom_update_word((uint16_t*)24, (uint16_t)MIN_FEED);
  eeprom_update_word((uint16_t*)26, (uint16_t)MAX_FEED);
  eeprom_update_word((uint16_t*)28, (uint16_t)MIN_aFEED);
  eeprom_update_word((uint16_t*)30, (uint16_t)MAX_aFEED);
  //
  eeprom_update_word((uint16_t*)32, (uint16_t)MAX_RAPID_MOTION);
  eeprom_update_word((uint16_t*)34, (uint16_t)MIN_RAPID_MOTION);
  eeprom_update_word((uint16_t*)36, (uint16_t)REPEAt);
  //
  eeprom_update_word((uint16_t*)38, (uint16_t)HC_SCALE_1);
  eeprom_update_word((uint16_t*)40, (uint16_t)HC_SCALE_10);
  eeprom_update_word((uint16_t*)42, (uint16_t)HC_START_SPEED_1);
  eeprom_update_word((uint16_t*)44, (uint16_t)HC_MAX_SPEED_1);
  eeprom_update_word((uint16_t*)46, (uint16_t)HC_START_SPEED_10);
  eeprom_update_word((uint16_t*)48, (uint16_t)HC_MAX_SPEED_10);
  eeprom_update_word((uint16_t*)50, (uint16_t)HC_X_DIR);    //byte --> unsigned int
  //добавка
  //eeprom_update_word((uint16_t*)52, DELAY_MOTOR_Z_ENABLE);
  //eeprom_update_word((uint16_t*)54, DELAY_MOTOR_X_ENABLE);

  //Запись пользовательской резьбы. Два параметра. float шаг и int число проходов
  eeprom_update_float((float*)52, (float)Thread_Info[TOTAL_THREADS - 1].Step);   //4 байта
  eeprom_update_word((uint16_t*)56, (uint16_t)Thread_Info[TOTAL_THREADS - 1].Pass); //byte --> unsigned int

  //Запись пользовательского конуса по соотношению сторон A:B в предпоследнюю строку массива конусов. Два параметра: float C1 и float C2
  eeprom_update_float((float*)58, (float)Cone_Info[TOTAL_CONE - 2].C1);   //4 байта
  eeprom_update_float((float*)62, (float)Cone_Info[TOTAL_CONE - 2].C2);   //4 байта
  
  //Запись пользовательского конуса заданного в градусах в последнюю строку массива конусов. Один параметр float C1. Второй параметр float C2 в данном случае всегда равен 0 и его бессмысленно сохранять.
  eeprom_update_float((float*)66, (float)Cone_Info[TOTAL_CONE - 1].C1);   //4 байта

}

//Чтение EEPROM
void Load_EEPROM()
{
  //Проверяем в EEPROM флаг версии в ячейке 0, если он отличается, то записываем в эту ячейку номер версии и сохраняем в EEPROM дефолтные настройки
  if (eeprom_read_word((uint16_t*)0) != (uint16_t)_VERSION)
  {
    eeprom_update_word((uint16_t*)0, (uint16_t)_VERSION);
    Reset_To_Defaults();        //Добавил прямой вызов сброса на дефолтные и звуковые сигналы
    Save_EEPROM();
  }

  //Read one 16-bit word (little endian) from EEPROM address.
  //uint16_t eeprom_read_word (const uint16_t *__p);
  ENC_LINE_PER_REV     = (int)eeprom_read_word((uint16_t*)2);     //[SETUP: 0...32 767, 2 байта]
  MOTOR_Z_STEP_PER_REV = (int)eeprom_read_word((uint16_t*)4);     //[SETUP: 0...32 767, 2 байта]
  SCREW_Z              = (int)eeprom_read_word((uint16_t*)6);     //[SETUP: 0...32 767, 2 байта]
  McSTEP_Z             = (int)eeprom_read_word((uint16_t*)8);     //[SETUP: 0...32 767, 2 байта]
  MOTOR_X_STEP_PER_REV = (int)eeprom_read_word((uint16_t*)10);    //[SETUP: 0...32 767, 2 байта]
  SCREW_X              = (int)eeprom_read_word((uint16_t*)12);    //[SETUP: 0...32 767, 2 байта]
  REBOUND_X            = (int)eeprom_read_word((uint16_t*)14);    //[SETUP: 0...32 767, 2 байта]
  REBOUND_Z            = (int)eeprom_read_word((uint16_t*)16);    //[SETUP: 0...32 767, 2 байта]
  McSTEP_X             = (int)eeprom_read_word((uint16_t*)18);    //[SETUP: 0...32 767, 2 байта]
  //
  THRD_ACCEL           = (byte)eeprom_read_word((uint16_t*)20);   //[SETUP: 0...255, 1 байт, но храним в 2 байтах для стандартности]
  FEED_ACCEL           = (int)eeprom_read_word((uint16_t*)22);    //[SETUP: 0...32 767, 2 байта]
  //
  MIN_FEED             = (int)eeprom_read_word((uint16_t*)24);    //[SETUP: 0...32 767, 2 байта]
  MAX_FEED             = (int)eeprom_read_word((uint16_t*)26);    //[SETUP: 0...32 767, 2 байта]
  MIN_aFEED            = (int)eeprom_read_word((uint16_t*)28);    //[SETUP: 0...32 767, 2 байта]
  MAX_aFEED            = (int)eeprom_read_word((uint16_t*)30);    //[SETUP: 0...32 767, 2 байта]
  //
  MAX_RAPID_MOTION     = (int)eeprom_read_word((uint16_t*)32);    //[SETUP: 0...32 767, 2 байта]
  MIN_RAPID_MOTION     = (int)eeprom_read_word((uint16_t*)34);    //[SETUP: 0...32 767, 2 байта]
  REPEAt               = (int)eeprom_read_word((uint16_t*)36);    //[SETUP: 0...32 767, 2 байта]
  //
  HC_SCALE_1           = (int)eeprom_read_word((uint16_t*)38);    //[SETUP: 0...32 767, 2 байта]
  HC_SCALE_10          = (int)eeprom_read_word((uint16_t*)40);    //[SETUP: 0...32 767, 2 байта]
  HC_START_SPEED_1     = (int)eeprom_read_word((uint16_t*)42);    //[SETUP: 0...32 767, 2 байта]
  HC_MAX_SPEED_1       = (int)eeprom_read_word((uint16_t*)44);    //[SETUP: 0...32 767, 2 байта]
  HC_START_SPEED_10    = (int)eeprom_read_word((uint16_t*)46);    //[SETUP: 0...32 767, 2 байта]
  HC_MAX_SPEED_10      = (int)eeprom_read_word((uint16_t*)48);    //[SETUP: 0...32 767, 2 байта]
  HC_X_DIR             = (byte)eeprom_read_word((uint16_t*)50);   //[SETUP: 0...255, 1 байт, но храним в 2 байтах для стандартности]
  //добавка
  //DELAY_MOTOR_Z_ENABLE = (uint16_t)eeprom_read_word((uint16_t*)52);    //[SETUP: 0...65 535, 2 байта]
  //DELAY_MOTOR_X_ENABLE = (uint16_t)eeprom_read_word((uint16_t*)54);    //[SETUP: 0...65 535, 2 байта]

  //Обновление значения переменных зависимых от вышеперечисленных переменных и инициализированных при старте программы
  Update_Parameters();

  //Загрузка пользовательской резьбы из EEPROM в последнюю ячейку массива РЕЗЬБ. Два параметра. float шаг и int число проходов
  Thread_Info[TOTAL_THREADS - 1].Step = (float)eeprom_read_float((float*)52);      //4 байта                                                    //Запись в таблицу резьб пользовательского шага
  Thread_Info[TOTAL_THREADS - 1].Pass = (byte)eeprom_read_word((uint16_t*)56);     //2 байт unsigned int --> 1 byte                             //Запись в таблицу резьб пользовательского числа проходов
  Calc_K_Z(Thread_Info[TOTAL_THREADS - 1].Step, &Thread_Info[TOTAL_THREADS - 1].Ks_Div_Z, &Thread_Info[TOTAL_THREADS - 1].Km_Div_Z);            //Расчёт и запись в таблицу резьб Ks_Z и Km_Z
  Calc_K_X(Thread_Info[TOTAL_THREADS - 1].Step, &Thread_Info[TOTAL_THREADS - 1].Ks_Div_X, &Thread_Info[TOTAL_THREADS - 1].Km_Div_X);            //Расчёт и запись в таблицу резьб Ks_X и Km_X

  //Загрузка пользовательского конуса по соотношению сторон A:B в предпоследнюю строку массива конусов.
  //Два параметра: float C1 (это A) и float C2 (это B)
  Cone_Info[TOTAL_CONE - 2].C1 = eeprom_read_float((float*)58);   //4 байта
  Cone_Info[TOTAL_CONE - 2].C2 = eeprom_read_float((float*)62);   //4 байта
  //Расчёт и запись в таблицу конусов Cs_Div и Cm_Div и XZ
  Calc_C_AB(Cone_Info[TOTAL_CONE - 2].C1, Cone_Info[TOTAL_CONE - 2].C2, &Cone_Info[TOTAL_CONE - 2].Cs_Div, &Cone_Info[TOTAL_CONE - 2].Cm_Div, &Cone_Info[TOTAL_CONE - 2].XZ);


  //Загрузка пользовательского конуса заданного в градусах в последнюю строку массива конусов.
  //Один параметр float C1 (угол конуса в градусах). Второй параметр float C2 в данном случае всегда равен 0 и не используется.
  Cone_Info[TOTAL_CONE - 1].C1 = eeprom_read_float((float*)66);   //4 байта
  Cone_Info[TOTAL_CONE - 1].C2 = 0.0f;
  //Расчёт и запись в таблицу конусов Cs_Div и Cm_Div и XZ
  Calc_C_DEG(Cone_Info[TOTAL_CONE - 1].C1, &Cone_Info[TOTAL_CONE - 1].Cs_Div, &Cone_Info[TOTAL_CONE - 1].Cm_Div, &Cone_Info[TOTAL_CONE - 1].XZ);
}

//Функции для проверки переменных на корректность, аналог проверок в коде static_assert
bool Check_MIN_FEED()
{
  //a "Неверно задано значение MIN_FEED"
  if ((uint32_t)(ENC_LINE_PER_REV / ((float)MOTOR_Z_STEP_PER_REV * McSTEP_Z * MIN_FEED / SCREW_Z) / 2 + 0.5) <= 255)
  {
    //e "Неверно задано значение MIN_FEED"
    if ((uint32_t)(ENC_LINE_PER_REV / ((float)MOTOR_X_STEP_PER_REV * McSTEP_X * MIN_FEED / SCREW_X) / 2 + 0.5) <= 255)
    {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Check_MAX_FEED()
{
  //b "Неверно задано значение MAX_FEED"
  if ((uint32_t)(ENC_LINE_PER_REV / ((float)MOTOR_Z_STEP_PER_REV * McSTEP_Z * MAX_FEED / SCREW_Z) / 2 + 0.5) > 1)
  {
    //f "Неверно задано значение MAX_FEED"
    if ((uint32_t)(ENC_LINE_PER_REV / ((float)MOTOR_X_STEP_PER_REV * McSTEP_X * MAX_FEED / SCREW_X) / 2 + 0.5) > 1)
    {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Check_MIN_aFEED()
{
  //c "Неверно задано значение MIN_aFEED"
  if ((250000 / ((uint32_t)MIN_aFEED * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1) <= 65535)
  {
    //g "Неверно задано значение MIN_aFEED"
    if ((250000 / ((uint32_t)MIN_aFEED * MOTOR_X_STEP_PER_REV * McSTEP_X / ((uint32_t)60 * SCREW_X / 100) * 2) - 1) <= 65535)
    {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Check_MAX_aFEED()
{
  //d "Неверно задано значение MAX_aFEED"
  if ((250000 / ((uint32_t)MAX_aFEED * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1) > 1)
  {
    //h "Неверно задано значение MAX_aFEED"
    if ((250000 / ((uint32_t)MAX_aFEED * MOTOR_X_STEP_PER_REV * McSTEP_X / ((uint32_t)60 * SCREW_X / 100) * 2) - 1) > 1)
    {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

// Функция проверки. На входе старое и новое значение. Если проверка успешно выполнена возвращает новое, если нет - старое.
// Используется для проверки при изменении следующих переменных:
// ENC_LINE_PER_REV
// MOTOR_Z_STEP_PER_REV
// MOTOR_X_STEP_PER_REV
// McSTEP_Z
// McSTEP_X
// SCREW_Z
// SCREW_X
// MIN_FEED
// MAX_FEED
// MIN_aFEED
// MAX_aFEED
uint16_t Check_All(uint16_t OLD, uint16_t NEW)
{
  if (Check_MIN_FEED() &&
      Check_MAX_FEED() &&
      Check_MIN_aFEED() &&
      Check_MAX_aFEED() )
  {
    return NEW;
  } else {
    return OLD;
  }
}

void ScaleDiv2()
{
  if (scaleFloat >= 2) scaleFloat = (unsigned int)scaleFloat / (unsigned int)2;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ********** Обработчик нажатия кнопки Select **********
void Setup_Key_Select_Pressed()
{
  if (!key_sel_flag)
  {
    switch (SETUP_MODE)
    {
      case MODE_PARAMETERS:               //ПРОСМОТР И РЕДАКТИРОВАНИЕ ОСНОВНЫХ ПАРАМЕТРОВ "ЖЕЛЕЗА"
        if (bModeParameters)
        {
          Beep();
          if (bEditParameters)
          {
            bEditParameters = false; //Выходим из режима редактирования параметра
            Update_Parameters();      //Обновляем зависимые переменные и массивы резьб и конусов
          } else {
            bEditParameters = true; //Входим в режим редактирования параметра
          }
        }
        break;
      case MODE_READ_THREAD:              //ПРОСМОТР КОЭФФИЦИЕНТОВ РЕЗЬБ
        if (CURRENT_THREAD == (TOTAL_THREADS - 1))  //Для редактирования пользовательской резьбы
        {
          if (!bEditUserThread)
          {
            bEditUserThread = true;
          } else {
            Calc_K_Z(Thread_Info[TOTAL_THREADS - 1].Step, &Thread_Info[TOTAL_THREADS - 1].Ks_Div_Z, &Thread_Info[TOTAL_THREADS - 1].Km_Div_Z); //Расчёт и запись в таблицу резьб Ks_Z и Km_Z
            Calc_K_X(Thread_Info[TOTAL_THREADS - 1].Step, &Thread_Info[TOTAL_THREADS - 1].Ks_Div_X, &Thread_Info[TOTAL_THREADS - 1].Km_Div_X); //Расчёт и запись в таблицу резьб Ks_X и Km_X
            bEditUserThread = false;
          }
        } else {
          bEditUserThread = false;
        }
        break;
      case MODE_READ_CONE:                //ПРОСМОТР КОЭФФИЦИЕНТОВ КОНУСОВ
        if (CURRENT_CONE == (TOTAL_CONE - 2))         //Для редактирования пользовательского конуса A:B
        {
          if (!bEditUserConeAB)
          {
            bEditUserConeAB = true;
          } else {
            //Calc_C_AB(Cone_Info[TOTAL_CONE - 2].C1, Cone_Info[TOTAL_CONE - 2].C2, &Cone_Info[TOTAL_CONE - 2].Cs_Div, &Cone_Info[TOTAL_CONE - 2].Cm_Div);   //Расчёт и запись в таблицу конусов Cs_Div и Cm_Div
            Calc_C_AB(Cone_Info[TOTAL_CONE - 2].C1, Cone_Info[TOTAL_CONE - 2].C2, &Cone_Info[TOTAL_CONE - 2].Cs_Div, &Cone_Info[TOTAL_CONE - 2].Cm_Div, &Cone_Info[TOTAL_CONE - 2].XZ);   //Расчёт и запись в таблицу конусов Cs_Div и Cm_Div
            bEditUserConeAB = false;
          }
        } else if (CURRENT_CONE == (TOTAL_CONE - 1))  //Для редактирования пользовательского конуса заданного в градусах
        {
          if (!bEditUserConeDEG)
          {
            bEditUserConeDEG = true;
          } else {
            //Calc_C_DEG(Cone_Info[TOTAL_CONE - 1].C1, &Cone_Info[TOTAL_CONE - 1].Cs_Div, &Cone_Info[TOTAL_CONE - 1].Cm_Div);                               //Расчёт и запись в таблицу конусов Cs_Div и Cm_Div
            Calc_C_DEG(Cone_Info[TOTAL_CONE - 1].C1, &Cone_Info[TOTAL_CONE - 1].Cs_Div, &Cone_Info[TOTAL_CONE - 1].Cm_Div, &Cone_Info[TOTAL_CONE - 1].XZ);                               //Расчёт и запись в таблицу конусов Cs_Div и Cm_Div
            bEditUserConeDEG = false;
          }
        } else {
          bEditUserConeAB = false;
          bEditUserConeDEG = false;
        }
        break;
      case MODE_RESET_TO_DEFAULTS:        //СБРОС НАСТРОЕК НА ДЕФОЛТНЫЕ (Требует последующего сохранения)
        if (bModeResetToDefaults)
        {
          Beep();
          Reset_To_Defaults();
          bModeResetToDefaults = false;   //Выходим в главное меню
        }
        break;
      case MODE_EXIT_AND_SAVING:          //ВЫХОД И СОХРАНЕНИЕ
        if (bModeSaveAndExit)
        {
          BeepBeep();
          Save_EEPROM();                    //Сохраняем все параметры в память EEPROM
          asm("JMP 0");                     //Программная перезагрузка Arduino
        }
        break;
      case MODE_EXIT_WITHOUT_SAVING:      //ВЫХОД БЕЗ СОХРАНЕНИЯ
        if (bModeWithoutExit)
        {
          BeepBeep();
          asm("JMP 0");                     //Программная перезагрузка Arduino
        }
        break;
    }
    key_sel_flag = true;
  }
}

// ********** Обработчик нажатия кнопки Up **********
void Setup_Key_Up_Pressed()
{
  if (SETUP_MODE == MODE_PARAMETERS)                            //ПРОСМОТР И РЕДАКТИРОВАНИЕ ОСНОВНЫХ ПАРАМЕТРОВ "ЖЕЛЕЗА"
  {
    if (!bModeParameters)
    {
      SETUP_MODE = LAST_SETUP_Mode;                 //Переходим к последнему пункту меню
    } else {
      if (!bEditParameters)                         //Листаем, если переменная не находится в режиме редактирования и не достигла конца списка
      {
        if (SETUP_ID == ID_ENC_LINE_PER_REV )       //Если достигли начала списка, то переходим в конец списка
        {
          SETUP_ID = LAST_SETUP_id;
        } else {
          --SETUP_ID;                               //Листаем на предыдущий параметр, если переменная не достигла начала списка
        }
      } else {
        //Изменение переменных в режиме редактирования...
        switch (SETUP_ID)
        {
          case   ID_ENC_LINE_PER_REV:
            //Вдвое меньше диапазона переменной, и чётное
            if (ENC_LINE_PER_REV <= 16380) //Фактический максимум после увеличения 16382. ENC_TICK = 2*16382 = 32764
            {
              ENC_LINE_PER_REV = Check_All(ENC_LINE_PER_REV, ENC_LINE_PER_REV + 2); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MOTOR_Z_STEP_PER_REV:
            if (MOTOR_Z_STEP_PER_REV < 32767) //Фактический максимум после увеличения 32767 (Это предел для числа типа int)
            {
              MOTOR_Z_STEP_PER_REV = Check_All(MOTOR_Z_STEP_PER_REV, MOTOR_Z_STEP_PER_REV + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_SCREW_Z:
            if (SCREW_Z < 32767) //Фактический максимум после увеличения 32767 (Это предел для числа типа int)
            {
              SCREW_Z = Check_All(SCREW_Z, SCREW_Z + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_McSTEP_Z:
            if (McSTEP_Z < 32767) //Фактический максимум после увеличения 32767 (Это предел для числа типа int)
            {
              McSTEP_Z = Check_All(McSTEP_Z, McSTEP_Z + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_REBOUND_Z:
            if (REBOUND_Z < 32767) ++REBOUND_Z;
            break;
          case   ID_MOTOR_X_STEP_PER_REV:
            if (MOTOR_X_STEP_PER_REV < 32767) //Фактический максимум после увеличения 32767 (Это предел для числа типа int)
            {
              MOTOR_X_STEP_PER_REV = Check_All(MOTOR_X_STEP_PER_REV, MOTOR_X_STEP_PER_REV + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_SCREW_X:
            if (SCREW_X < 32767) //Фактический максимум после увеличения 32767 (Это предел для числа типа int)
            {
              SCREW_X = Check_All(SCREW_X, SCREW_X + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_McSTEP_X:
            if (McSTEP_X < 32767) //Фактический максимум после увеличения 32767 (Это предел для числа типа int)
            {
              McSTEP_X = Check_All(McSTEP_X, McSTEP_X + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_REBOUND_X:
            if (REBOUND_X < 32767) ++REBOUND_X;
            break;

          //Fix Отсутствовали
          case   ID_THRD_ACCEL:
            if (THRD_ACCEL < 255) ++THRD_ACCEL;
            break;

          case   ID_FEED_ACCEL:
            if (FEED_ACCEL < 255) ++FEED_ACCEL;
            break;
          //---

          case   ID_MIN_FEED:
            if (MIN_FEED < 32767 && MIN_FEED + 1 < MAX_FEED)
            {
              MIN_FEED = Check_All(MIN_FEED, MIN_FEED + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MAX_FEED:
            if (MAX_FEED < 32767) //Фактический максимум после увеличения 32767 (Это предел для числа типа int)
            {
              MAX_FEED = Check_All(MAX_FEED, MAX_FEED + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MIN_aFEED:
            if (MIN_aFEED < 32767 && MIN_aFEED + 1 < MAX_aFEED)
            {
              MIN_aFEED = Check_All(MIN_aFEED, MIN_aFEED + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MAX_aFEED:
            if (MAX_aFEED < 32767) //Фактический максимум после увеличения 32767 (Это предел для числа типа int)
            {
              MAX_aFEED = Check_All(MAX_aFEED, MAX_aFEED + 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MAX_RAPID_MOTION:
            if (MAX_RAPID_MOTION < 254) ++MAX_RAPID_MOTION;   //Fix: Допустимое значение не выше 255
            break;
          case   ID_MIN_RAPID_MOTION:
            if (MIN_RAPID_MOTION < 254) ++MIN_RAPID_MOTION;   //Fix: Допустимое значение не выше 255
            break;
          case   ID_REPEAt:
            if (REPEAt < 32767) ++REPEAt;
            break;
          case   ID_HC_SCALE_1:
            if (HC_SCALE_1 < 32767) ++HC_SCALE_1;
            break;
          case   ID_HC_SCALE_10:
            if (HC_SCALE_10 < 32767) ++HC_SCALE_10;
            break;
          case   ID_HC_START_SPEED_1:
            if (HC_START_SPEED_1 < 32767) ++HC_START_SPEED_1;
            break;
          case   ID_HC_MAX_SPEED_1:
            if (HC_MAX_SPEED_1 < 32767) ++HC_MAX_SPEED_1;
            break;
          case   ID_HC_START_SPEED_10:
            if (HC_START_SPEED_10 < 32767) ++HC_START_SPEED_10;
            break;
          case   ID_HC_MAX_SPEED_10:
            if (HC_MAX_SPEED_10 < 32767) ++HC_MAX_SPEED_10;
            break;
          case   ID_HC_X_DIR:
            if (HC_X_DIR == 0) ++HC_X_DIR;
            break;
            //case  ID_DELAY_MOTOR_Z_ENABLE:
            //  if (DELAY_MOTOR_Z_ENABLE < 999) ++DELAY_MOTOR_Z_ENABLE;
            //  break;
            //case  ID_DELAY_MOTOR_X_ENABLE:
            //  if (DELAY_MOTOR_X_ENABLE < 999) ++DELAY_MOTOR_X_ENABLE;
            //  break;
        }
        //---
      }
    }
  } else if (SETUP_MODE == MODE_READ_THREAD)                           //ПРОСМОТР КОЭФФИЦИЕНТОВ РЕЗЬБ
  {
    if (!bEditUserThread)
    {
      if (bModeThread)
      {
        if (CURRENT_THREAD > 0 )
        {
          --CURRENT_THREAD;                           //Листаем список до начала
        } else if (CURRENT_THREAD == 0 )
        {
          CURRENT_THREAD = ((sizeof(Thread_Info) / sizeof(Thread_Info[0])) - 1); //Как достигли начала списка - переходим в его конец
        }
      } else {
        --SETUP_MODE;                                 //Переход к пункту меню MODE_PARAMETERS
      }
    } else {
      //Если находимся в процессе редактирования пользовательской резьбы...
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
      float NextStep = Thread_Info[CURRENT_THREAD].Step + scaleFloat * USER_THREAD_STEP;
      //float minStepZ = MinimumStepZ(254.999f);
      //float minStepX = MinimumStepX(254.999f);
      //float MaxStepZ = MinimumStepZ(2.0f);
      //float MaxStepX = MinimumStepX(2.0f);

      float MaxStepZ = MinimumStepZ(1.0f);        //С новым алгоритмом в INT0
      float MaxStepX = MinimumStepX(1.0f);        //С новым алгоритмом в INT0
      
      if (NextStep <= USER_THREAD_MAX) {
        //if (NextStep > minStepZ && NextStep > minStepX) {
        if (NextStep < MaxStepZ && NextStep < MaxStepX) {
          Thread_Info[CURRENT_THREAD].Step = NextStep;
          if (scaleFloat < (32767 - USER_THREAD_CHANGE_SPEED)) scaleFloat = scaleFloat + USER_THREAD_CHANGE_SPEED;
        } else {
          ScaleDiv2();
          if (Thread_Info[CURRENT_THREAD].Step > MaxStepZ)
          {
            Thread_Info[CURRENT_THREAD].Step = MaxStepZ;
          }
          if (Thread_Info[CURRENT_THREAD].Step > MaxStepX)
          {
            Thread_Info[CURRENT_THREAD].Step = MaxStepX;
          }
        }
      } else {
        ScaleDiv2();
      }
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
  } else if (SETUP_MODE == MODE_READ_CONE)                             //ПРОСМОТР КОЭФФИЦИЕНТОВ КОНУСОВ
  {
    if (!bEditUserConeAB && !bEditUserConeDEG)                //Если мы не редактируем пользовательский конус...
    {
      if (bModeCone)
      {
        if (CURRENT_CONE > 0 )
        {
          --CURRENT_CONE;                           //Листаем список до начала
        } else if (CURRENT_CONE == 0 )
        {
          CURRENT_CONE = ((sizeof(Cone_Info) / sizeof(Cone_Info[0])) - 1); //Как достигли начала списка - переходим в его конец
        }
      } else {
        --SETUP_MODE;                                 //Переход к пункту меню MODE_READ_THREAD
      }
    } else {
      //Если мы редактируем пользовательский конус...
      float NextC1;
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
      if (bEditUserConeAB)
      {
        ////float MinC1 = Get_A_AB(Cone_Info[CURRENT_CONE].C2, 254.99f);           //Расчёт допустимого значения C2 при заданном C1
        //float MaxC1 = Get_A_AB(Cone_Info[CURRENT_CONE].C2, 2.0f);       //Расчёт допустимого значения C2 при заданном C1

        float MaxC1 = Get_A_AB(Cone_Info[CURRENT_CONE].C2, 254.99f, (byte)1);       //Расчёт допустимого значения C2 при заданном C1

        NextC1 = Cone_Info[CURRENT_CONE].C1 + scaleFloat * USER_CONEAB_STEP;
        if (NextC1 <= USER_CONEAB_MAX && NextC1 < MaxC1)
        {
          Cone_Info[CURRENT_CONE].C1 = NextC1;
          if (scaleFloat < (32767 - USER_CONEAB_CHANGE_SPEED)) scaleFloat = scaleFloat + USER_CONEAB_CHANGE_SPEED;
        } else {
          ScaleDiv2();
        }
      } else if (bEditUserConeDEG)
      {
        ////float MinDEG = Get_deg_DEG(254.99f);
        //float MaxDEG = Get_deg_DEG(2.0f);
        //С учётом типа тактования конуса
        float MaxDEG = Get_deg_DEG(254.99f, (byte)1);

        NextC1 = Cone_Info[CURRENT_CONE].C1 + scaleFloat * USER_CONEDEG_STEP;
        if (NextC1 <= USER_CONEDEG_MAX && NextC1 < MaxDEG )
        {
          Cone_Info[CURRENT_CONE].C1 = NextC1;
          if (scaleFloat < (32767 - USER_CONEDEG_CHANGE_SPEED)) scaleFloat = scaleFloat + USER_CONEDEG_CHANGE_SPEED;
        } else {
          ScaleDiv2();
        }
      }
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
  } else if (SETUP_MODE == MODE_RESET_TO_DEFAULTS)                       //СБРОС НАСТРОЕК НА ДЕФОЛТНЫЕ (Требует последующего сохранения)
  {
    --SETUP_MODE;                                   //Переход к пункту меню MODE_EXIT_AND_SAVING
  } else if (SETUP_MODE == MODE_EXIT_AND_SAVING)                       //ВЫХОД И СОХРАНЕНИЕ
  {
    --SETUP_MODE;                                   //Переход к пункту меню MODE_READ_CONE
  } else if (SETUP_MODE == MODE_EXIT_WITHOUT_SAVING)                   //ВЫХОД БЕЗ СОХРАНЕНИЯ
  {
    --SETUP_MODE;                                   //Переход к пункту меню MODE_EXIT_AND_SAVING
  }
  Beep();
}

// ********** Обработчик нажатия кнопки Down **********
void Setup_Key_Down_Pressed()
{
  if (SETUP_MODE == MODE_PARAMETERS)                  //ПРОСМОТР И РЕДАКТИРОВАНИЕ ОСНОВНЫХ ПАРАМЕТРОВ "ЖЕЛЕЗА"
  {
    if (!bModeParameters)
    {
      ++SETUP_MODE;                       //т.е фактически SETUP_MODE = MODE_READ_THREAD;
    } else {
      if (!bEditParameters)               //Листаем, если переменная не находится в режиме редактирования и не достигла конца списка
      {
        if (SETUP_ID < LAST_SETUP_id)       //Листаем на следующий параметр, если переменная не достигла конца списка
        {
          ++SETUP_ID;
        } else {                          //Если достигли конца списка, то переходим на начало списка
          SETUP_ID = ID_ENC_LINE_PER_REV;
        }
      } else {
        //Изменение переменных в режиме редактирования...
        switch (SETUP_ID)
        {
          case   ID_ENC_LINE_PER_REV:
            //Вдвое меньше диапазона переменной, и чётное
            if (ENC_LINE_PER_REV > 2)
            {
              ENC_LINE_PER_REV = Check_All(ENC_LINE_PER_REV, ENC_LINE_PER_REV - 2); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MOTOR_Z_STEP_PER_REV:
            if (MOTOR_Z_STEP_PER_REV > 0)
            {
              MOTOR_Z_STEP_PER_REV = Check_All(MOTOR_Z_STEP_PER_REV, MOTOR_Z_STEP_PER_REV - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_SCREW_Z:
            if (SCREW_Z > 0)
            {
              SCREW_Z = Check_All(SCREW_Z, SCREW_Z - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_McSTEP_Z:
            if (McSTEP_Z > 0)
            {
              McSTEP_Z = Check_All(McSTEP_Z, McSTEP_Z - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_REBOUND_Z:
            if (REBOUND_Z > 0) --REBOUND_Z;
            break;
          case   ID_MOTOR_X_STEP_PER_REV:
            if (MOTOR_X_STEP_PER_REV > 0)
            {
              MOTOR_X_STEP_PER_REV = Check_All(MOTOR_X_STEP_PER_REV, MOTOR_X_STEP_PER_REV - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_SCREW_X:
            if (SCREW_X > 0)
            {
              SCREW_X = Check_All(SCREW_X, SCREW_X - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_McSTEP_X:
            if (McSTEP_X > 0)
            {
              McSTEP_X = Check_All(McSTEP_X, McSTEP_X - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_REBOUND_X:
            if (REBOUND_X > 0) --REBOUND_X;
            break;

          //Fix Отсутствовали
          case   ID_THRD_ACCEL:
            if (THRD_ACCEL > 1) --THRD_ACCEL;
            break;

          case   ID_FEED_ACCEL:
            if (FEED_ACCEL > 1) --FEED_ACCEL;
            break;
          //---

          case   ID_MIN_FEED:
            if (MIN_FEED > 0)
            {
              MIN_FEED = Check_All(MIN_FEED, MIN_FEED - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MAX_FEED:
            if (MAX_FEED > 0 && MIN_FEED < MAX_FEED - 1)
            {
              MAX_FEED = Check_All(MAX_FEED, MAX_FEED - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MIN_aFEED:
            if (MIN_aFEED > 0)
            {
              MIN_aFEED = Check_All(MIN_aFEED, MIN_aFEED - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MAX_aFEED:
            if (MAX_aFEED > 0 && MIN_aFEED < MAX_aFEED - 1)
            {
              MAX_aFEED = Check_All(MAX_aFEED, MAX_aFEED - 1); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
            }
            break;
          case   ID_MAX_RAPID_MOTION:
            if (MAX_RAPID_MOTION > 0) --MAX_RAPID_MOTION;
            break;
          case   ID_MIN_RAPID_MOTION:
            if (MIN_RAPID_MOTION > 0) --MIN_RAPID_MOTION;
            break;
          case   ID_REPEAt:
            if (REPEAt > 0) --REPEAt;
            break;
          case   ID_HC_SCALE_1:
            if (HC_SCALE_1 > 0) --HC_SCALE_1;
            break;
          case   ID_HC_SCALE_10:
            if (HC_SCALE_10 > 0) --HC_SCALE_10;
            break;
          case   ID_HC_START_SPEED_1:
            if (HC_START_SPEED_1 > 0) --HC_START_SPEED_1;
            break;
          case   ID_HC_MAX_SPEED_1:
            if (HC_MAX_SPEED_1 > 0) --HC_MAX_SPEED_1;
            break;
          case   ID_HC_START_SPEED_10:
            if (HC_START_SPEED_10 > 0) --HC_START_SPEED_10;
            break;
          case   ID_HC_MAX_SPEED_10:
            if (HC_MAX_SPEED_10 > 0) --HC_MAX_SPEED_10;
            break;
          case   ID_HC_X_DIR:
            if (HC_X_DIR == 1) --HC_X_DIR;
            break;
            //case  ID_DELAY_MOTOR_Z_ENABLE:
            //  if (DELAY_MOTOR_Z_ENABLE > 0) --DELAY_MOTOR_Z_ENABLE;
            //  break;
            //case  ID_DELAY_MOTOR_X_ENABLE:
            //  if (DELAY_MOTOR_X_ENABLE > 0) --DELAY_MOTOR_X_ENABLE;
            //  break;
        }
        //---
      }
    }
  } else if (SETUP_MODE == MODE_READ_THREAD)                 //ПРОСМОТР КОЭФФИЦИЕНТОВ РЕЗЬБ
  {
    if (!bEditUserThread)
    {
      if (bModeThread)
      {
        if (CURRENT_THREAD < ((sizeof(Thread_Info) / sizeof(Thread_Info[0])) - 1) )
        {
          ++CURRENT_THREAD;                 //Листаем список до конца
        } else if (CURRENT_THREAD == ((sizeof(Thread_Info) / sizeof(Thread_Info[0])) - 1) )
        {
          CURRENT_THREAD = 0;               //Как достигли конца списка - переходим на его начало
        }
      } else {
        ++SETUP_MODE;                       //Переход к пункту меню MODE_READ_CONE
      }
    } else {
      //Если находимся в процессе редактирования пользовательской резьбы...
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
      float NextStep = Thread_Info[CURRENT_THREAD].Step - scaleFloat * USER_THREAD_STEP;
      float MinStepZ = MinimumStepZ(254.999f);
      float MinStepX = MinimumStepX(254.999f);
      if (NextStep >= USER_THREAD_MIN) {
        if (NextStep > MinStepZ && NextStep > MinStepX) {
          Thread_Info[CURRENT_THREAD].Step = NextStep;
          if (scaleFloat < (32767 - USER_THREAD_CHANGE_SPEED)) scaleFloat = scaleFloat + USER_THREAD_CHANGE_SPEED;
        } else {
          ScaleDiv2();
          if (Thread_Info[CURRENT_THREAD].Step < MinStepZ)
          {
            Thread_Info[CURRENT_THREAD].Step = MinStepZ;
          }
          if (Thread_Info[CURRENT_THREAD].Step < MinStepX)
          {
            Thread_Info[CURRENT_THREAD].Step = MinStepX;
          }
        }
      } else {
        ScaleDiv2();
      }
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
  } else if (SETUP_MODE == MODE_READ_CONE)                   //ПРОСМОТР КОЭФФИЦИЕНТОВ КОНУСОВ
  {
    if (!bEditUserConeAB && !bEditUserConeDEG)                //Если мы не редактируем пользовательский конус...
    {
      if (bModeCone)
      {
        if (CURRENT_CONE < ((sizeof(Cone_Info) / sizeof(Cone_Info[0])) - 1) )
        {
          ++CURRENT_CONE;                 //Листаем список до конца
        } else if (CURRENT_CONE == ((sizeof(Cone_Info) / sizeof(Cone_Info[0])) - 1) )
        {
          CURRENT_CONE = 0;               //Как достигли конца списка - переходим на его начало
        }
      } else {
        ++SETUP_MODE;                       //Переход к пункту меню MODE_EXIT_AND_SAVING
      }
    } else {
      //Если мы редактируем пользовательский конус...
      float NextC1;
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
      if (bEditUserConeAB)
      {
        //float MinC1 = Get_A_AB(Cone_Info[CURRENT_CONE].C2, 254.99f);           //Расчёт допустимого значения C2 при заданном C1
        ////float MaxC1 = Get_A_AB(Cone_Info[CURRENT_CONE].C2, 2.0f);       //Расчёт допустимого значения C2 при заданном C1

        float MinC1 = Get_A_AB(Cone_Info[CURRENT_CONE].C2, 254.99f, (byte)0);           //Расчёт допустимого значения C2 при заданном C1

        NextC1 = Cone_Info[CURRENT_CONE].C1 - scaleFloat * USER_CONEAB_STEP;
        if (NextC1 >= USER_CONEAB_MIN && NextC1 > MinC1)
        {
          Cone_Info[CURRENT_CONE].C1 = NextC1;
          if (scaleFloat < (32767 - USER_CONEAB_CHANGE_SPEED)) scaleFloat = scaleFloat + USER_CONEAB_CHANGE_SPEED;
        } else {
          ScaleDiv2();
        }
      } else if (bEditUserConeDEG) {
        //float MinDEG = Get_deg_DEG(254.99f);
        ////float MaxDEG = Get_deg_DEG(2.0f);
        //С учётом типа тактования конуса
        float MinDEG = Get_deg_DEG(254.99f, (byte)0);

        NextC1 = Cone_Info[CURRENT_CONE].C1 - scaleFloat * USER_CONEDEG_STEP;
        if (NextC1 >= USER_CONEDEG_MIN && NextC1 > MinDEG )
        {
          Cone_Info[CURRENT_CONE].C1 = NextC1;
          if (scaleFloat < (32767 - USER_CONEDEG_CHANGE_SPEED)) scaleFloat = scaleFloat + USER_CONEDEG_CHANGE_SPEED;
        } else {
          ScaleDiv2();
        }
      }
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
  } else if (SETUP_MODE == MODE_RESET_TO_DEFAULTS)             //СБРОС НАСТРОЕК НА ДЕФОЛТНЫЕ (Требует последующего сохранения)
  {
    ++SETUP_MODE;                         //Переход к пункту меню MODE_EXIT_AND_SAVING
  } else if (SETUP_MODE == MODE_EXIT_AND_SAVING)             //ВЫХОД И СОХРАНЕНИЕ
  {
    ++SETUP_MODE;                         //Переход к пункту меню MODE_EXIT_WITHOUT_SAVING
  } else if (SETUP_MODE == LAST_SETUP_Mode)         //Последний пункт меню - MODE_EXIT_WITHOUT_SAVING
  {
    SETUP_MODE = 1;                       //Переход к первому пункту меню
  }
  Beep();
}

// ********** Обработчик нажатия кнопки Right **********
void Setup_Key_Right_Pressed()
{
  switch (SETUP_MODE)
  {
    case MODE_PARAMETERS:                             //ПРОСМОТР И РЕДАКТИРОВАНИЕ ОСНОВНЫХ ПАРАМЕТРОВ "ЖЕЛЕЗА"
      if (!bModeParameters)
      {
        //Обработчик для изменения параметра в режиме редактирования
        bModeParameters = true;                       //Заходим в подменю просмотра/редактирования параметров
      } else {
        if (bEditParameters)                         //Листаем, если переменная не находится в режиме редактирования и не достигла конца списка
        {
          //Если находимся в режиме редактирования переменной ENC_LINE_PER_REV
          //Вдвое меньше диапазона переменной, и чётное
          if (SETUP_ID == ID_ENC_LINE_PER_REV && ENC_LINE_PER_REV <= 16372)    //Фактический максимум после увеличения 16382. ENC_TICK = 2*16382 = 32764
          {
            ENC_LINE_PER_REV = Check_All(ENC_LINE_PER_REV, ENC_LINE_PER_REV + 10); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
          }
        }
      }
      break;
    case MODE_READ_THREAD:                            //ПРОСМОТР КОЭФФИЦИЕНТОВ РЕЗЬБ
      if (!bEditUserThread)
      {
        if (!bModeThread)
        {
          bModeThread = true;                           //Заходим в подменю просмотра коэффициентов РЕЗЬБ
          //} else {
          //  //Если находимся в режиме просмотра коэффициентов РЕЗЬБ...
        }
      } else {
        //Если находимся в процессе редактирования пользовательской резьбы...
        if (Thread_Info[CURRENT_THREAD].Pass < 255) ++Thread_Info[CURRENT_THREAD].Pass;
      }
      break;
    case MODE_READ_CONE:                              //ПРОСМОТР КОЭФФИЦИЕНТОВ КОНУСОВ
      if (!bEditUserConeAB && !bEditUserConeDEG)                //Если мы не редактируем пользовательский конус...
      {
        if (!bModeCone)
        {
          bModeCone = true;                             //Заходим в подменю просмотра коэффициентов КОНУСОВ
          //} else {
          //  //Если находимся в режиме просмотра коэффициентов КОНУСОВ...
        }
      } else {
        //Если мы редактируем пользовательский конус...
        if (bEditUserConeAB)
        {
          ////float MinC2 = Get_B_AB(Cone_Info[CURRENT_CONE].C1, 2.0f);           //Расчёт допустимого значения C2 при заданном C1
          //float MaxC2 = Get_B_AB(Cone_Info[CURRENT_CONE].C1, 254.99f);       //Расчёт допустимого значения C2 при заданном C1

          float MaxC2 = Get_B_AB(Cone_Info[CURRENT_CONE].C1, 254.99f, (byte)0);       //Расчёт допустимого значения C2 при заданном C1


          float NextC2 = Cone_Info[CURRENT_CONE].C2 + scaleFloat * USER_CONEAB_STEP;
          if (NextC2 <= USER_CONEAB_MAX && NextC2 < MaxC2)
          {
            Cone_Info[CURRENT_CONE].C2 = NextC2;
            if (scaleFloat < (32767 - USER_CONEAB_CHANGE_SPEED)) scaleFloat = scaleFloat + USER_CONEAB_CHANGE_SPEED;
          } else {
            ScaleDiv2();
          }
        }
      }
      break;
    case MODE_RESET_TO_DEFAULTS:                     //СБРОС НА ДЕФОЛТНЫЕ
      if (!bModeResetToDefaults)
      {
        bModeResetToDefaults = true;
      }
      break;
    case MODE_EXIT_AND_SAVING:                        //ВЫХОД И СОХРАНЕНИЕ
      if (!bModeSaveAndExit)
      {
        bModeSaveAndExit = true;
      }
      break;
    case MODE_EXIT_WITHOUT_SAVING:                    //ВЫХОД БЕЗ СОХРАНЕНИЯ
      if (!bModeWithoutExit)
      {
        bModeWithoutExit = true;
      }
      break;
  }
  Beep();
}

// ********** Обработчик нажатия кнопки Left **********
void Setup_Key_Left_Pressed()
{
  switch (SETUP_MODE)
  {
    case MODE_PARAMETERS:                             //ПРОСМОТР И РЕДАКТИРОВАНИЕ ОСНОВНЫХ ПАРАМЕТРОВ "ЖЕЛЕЗА"

      if (!bModeParameters)
      {
        //Нет реакции на нажатие этой клавиши в этом пункте меню
      } else {
        //Находимся в подменю просмотра и редактирования параметров
        if (bEditParameters)                          //Находимся в процессе редактирования текущего параметра
        {
          //Если находимся в режиме редактирования переменной ENC_LINE_PER_REV
          //Вдвое меньше диапазона переменной, и чётное
          if (SETUP_ID == ID_ENC_LINE_PER_REV && ENC_LINE_PER_REV > 11)
          {
            ENC_LINE_PER_REV = Check_All(ENC_LINE_PER_REV, ENC_LINE_PER_REV - 10); // ENC_LINE_PER_REV, MOTOR_Z_STEP_PER_REV, MOTOR_X_STEP_PER_REV, McSTEP_Z, McSTEP_X, SCREW_Z, SCREW_X, MIN_FEED, MAX_FEED, MIN_aFEED, MAX_aFEED
          }
        } else {
          //Выходим в главное меню
          bModeParameters = false;                     //Выходим в главное меню
          bEditParameters = false;                     //Отключаем режим редактирования (хотя он должен быть выключен и true невозможно)
        }
      }
      break;
    case MODE_READ_THREAD:                            //ПРОСМОТР КОЭФФИЦИЕНТОВ РЕЗЬБ
      if (!bEditUserThread)
      {
        bModeThread = false;                           //Выходим в главное меню
      } else {
        //Если находимся в процессе редактирования пользовательской резьбы...
        if (Thread_Info[CURRENT_THREAD].Pass > 1) --Thread_Info[CURRENT_THREAD].Pass;
      }
      break;
    case MODE_READ_CONE:                              //ПРОСМОТР КОЭФФИЦИЕНТОВ КОНУСОВ

      if (!bEditUserConeAB && !bEditUserConeDEG)                //Если мы не редактируем пользовательский конус...
      {
        //if (bModeCone)
        //{
        bModeCone = false;                             //Выходим в главное меню
        //} else {
        //  //Нет реакции на нажатие этой клавиши в этом пункте меню
        //}
      } else {
        //Если мы редактируем пользовательский конус...
        if (bEditUserConeAB)
        {
          //float MinC2 = Get_B_AB(Cone_Info[CURRENT_CONE].C1, 2.0f);           //Расчёт допустимого значения C2 при заданном C1
          ////float MaxC2 = Get_B_AB(Cone_Info[CURRENT_CONE].C1, 254.99f);       //Расчёт допустимого значения C2 при заданном C1


          float MinC2 = Get_B_AB(Cone_Info[CURRENT_CONE].C1, 254.99f, (byte)1);           //Расчёт допустимого значения C2 при заданном C1


          float NextC2 = Cone_Info[CURRENT_CONE].C2 - scaleFloat * USER_CONEAB_STEP;
          if (NextC2 >= USER_CONEAB_MIN && NextC2 > MinC2)
          {
            Cone_Info[CURRENT_CONE].C2 = NextC2;
            if (scaleFloat < (32767 - USER_CONEAB_CHANGE_SPEED)) scaleFloat = scaleFloat + USER_CONEAB_CHANGE_SPEED;
          } else {
            ScaleDiv2();
          }
        }
      }
      break;
    case MODE_RESET_TO_DEFAULTS:                     //СБРОС НА ДЕФОЛТНЫЕ
      //if(bModeResetToDefaults)
      //{
      bModeResetToDefaults = false;                     //Выходим в главное меню
      //}
      break;
    case MODE_EXIT_AND_SAVING:                        //ВЫХОД И СОХРАНЕНИЕ
      //if(bModeSaveAndExit)
      //{
      bModeSaveAndExit = false;                     //Выходим в главное меню
      //}
      break;
    case MODE_EXIT_WITHOUT_SAVING:                    //ВЫХОД БЕЗ СОХРАНЕНИЯ
      //if(bModeWithoutExit)
      //{
      bModeWithoutExit = false;                     //Выходим в главное меню
      //}
      break;
  }
  Beep();
}

void Setup_Menu()
{
  //Обработчик клавиши ОК(Select) однократный. Срабатывает только на нажатие, и не работает при удержании клавиши.
  byte Button_Sel_New = Button_Sel_Read;        //Читаем состояние кнопки ОК(Select)
  if (Button_Sel_New == 0 && Button_Sel_Old == B00010000)                           //Кнопка нажата, предыдущее состояние отжата
  {
    Setup_Key_Select_Pressed();
    Setup_Print();
  } else if (Button_Sel_Old == 0)                                                   //предыдущее состояние нажата
  {
    Setup_Print();
  } else if (Button_Sel_New == B00010000 && Button_Sel_Old == B00010000)            //Кнопка отпущена, предыдущее состояние отпущена
  {
    key_sel_flag = false;
    Setup_Print();
  }
  Button_Sel_Old = Button_Sel_New;

  /////////// Кнопки Меню (с разрешённым автозажатием клавиш стрелок) //////////////////////////////////////

  byte Button_New = Buttons_Read;
  if (Button_New != Button_Old)                                  //Меняем == на !=
  {
    //Кнопочку Нажали или Отпустили, состояние переменной изменилось
    if      (Button_New == B00000111) Setup_Key_Down_Pressed();
    else if (Button_New == B00001011) Setup_Key_Up_Pressed();
    else if (Button_New == B00001101) Setup_Key_Right_Pressed();
    else if (Button_New == B00001110) Setup_Key_Left_Pressed();
    else     {
      button_flag = false;
      scaleFloat = 1;         //Сбрасываем множитель изменения шага пользователькой резьбы
    }

    Setup_KeyCycle = 0;                                               //Обнуляем переменную цикла
  } else {
    //Кнопочки(-ку) удерживают нажатой или наоборот сохраняет отпущенное состояние
    Setup_KeyCycle++;                                                 //Запускаем счётчик циклов
    if (Setup_KeyCycle > DELAY_SETUP_ENTER_KEYCYCLE)                        //это длительность удерживания клавиши для входа в цикл
    {
      if (Button_New == B00000111)
      {
        button_flag = false;                                    //Гасим флаг, чтобы повторно можно было вызвать обработчик этой кнопки
        Setup_Key_Down_Pressed();
      }
      else if (Button_New == B00001011)
      {
        button_flag = false;                                    //Гасим флаг, чтобы повторно можно было вызвать обработчик этой кнопки
        Setup_Key_Up_Pressed();
      }
      else if (Button_New == B00001101)
      {
        button_flag = false;                                    //Гасим флаг, чтобы повторно можно было вызвать обработчик этой кнопки
        Setup_Key_Right_Pressed();
      }
      else if (Button_New == B00001110)
      {
        button_flag = false;                                    //Гасим флаг, чтобы повторно можно было вызвать обработчик этой кнопки
        Setup_Key_Left_Pressed();
      }
      Setup_KeyCycle = (DELAY_SETUP_ENTER_KEYCYCLE - DELAY_SETUP_INTO_KEYCYCLE);  //Обнуляем переменную цикла или не до конца обнуляем, чтобы в нажатом состоянии цикл срабатывания был короче
    }
  }
  Button_Old = Button_New;
  //----------------------------------------------------------------------------------------------------------------------------------------
}

void Setup_Print()
{
  lcd.reset();
  char LCD_Row_1[17];    //Буферы для вывода на экран LCD.
  char LCD_Row_2[17];    //
  char EMPTY17[17];
  lcd.setCursor(0, 0);

  if (SETUP_MODE == MODE_PARAMETERS)
  {
    if (!bModeParameters)                           //Если находимся в главном меню
    {
      lcd.print(PARAM1);                            //"   SHOW & EDIT  "
      lcd.setCursor(0, 1);
      lcd.print(PARAM2);                            //"   PARAMETERS   "
    } else {                                        //Если находимся внутри меню MODE_PARAMETERS

      if (!bEditParameters)
      {
        snprintf(EMPTY17, 17, "%s", EMPTY16);
      } else {
        snprintf(EMPTY17, 17, "%s", EMPTY16Blink);    //В режиме редактирования отображаем символ "квадратика" после редактируемого параметра
      }

      switch (SETUP_ID)
      {
        case   ID_ENC_LINE_PER_REV:
          lcd.print("ENCODER_LINE    ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", ENC_LINE_PER_REV, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_MOTOR_Z_STEP_PER_REV:
          lcd.print("MOTOR_Z_STEP    ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", MOTOR_Z_STEP_PER_REV, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_SCREW_Z:
          lcd.print("SCREW_Z         ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", SCREW_Z, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_McSTEP_Z:
          lcd.print("McSTEP_Z        ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", McSTEP_Z, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_REBOUND_Z:
          lcd.print("REBOUND_Z       ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", REBOUND_Z, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_MOTOR_X_STEP_PER_REV:
          lcd.print("MOTOR_X_STEP    ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", MOTOR_X_STEP_PER_REV, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_SCREW_X:
          lcd.print("SCREW_X         ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", SCREW_X, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_McSTEP_X:
          lcd.print("McSTEP_X        ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", McSTEP_X, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_REBOUND_X:
          lcd.print("REBOUND_X       ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", REBOUND_X, EMPTY17);
          lcd.print(LCD_Row_2);
          break;

        //Fix Отсутствовали
        case   ID_THRD_ACCEL:
          lcd.print("THREAD_ACCEL    ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", THRD_ACCEL, EMPTY17);
          lcd.print(LCD_Row_2);
          break;

        case   ID_FEED_ACCEL:
          lcd.print("FEED_ACCEL      ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", FEED_ACCEL, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        //---


        case   ID_MIN_FEED:
          lcd.print("MIN_FEED        ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", MIN_FEED, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_MAX_FEED:
          lcd.print("MAX_FEED        ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", MAX_FEED, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_MIN_aFEED:
          lcd.print("MIN_aFEED       ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", MIN_aFEED, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_MAX_aFEED:
          lcd.print("MAX_aFEED       ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", MAX_aFEED, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_MAX_RAPID_MOTION:
          lcd.print("MAX_RAPID_MOTION");
          lcd.setCursor(0, 1);
          //Конвертация значения параметра в rpm
          //16000000/32/((MAX_RAPID_MOTION+1)*2)/800*60=107rpm, где 800 это наверное MOTOR_Z_STEP_PER_REV * McSTEP_Z
          //(16000000 / 32 / ((MAX_RAPID_MOTION + 1) * 2) / (MOTOR_Z_STEP_PER_REV * McSTEP_Z) * 60)
          //(unsigned int)(30000000.0 / ( (MAX_RAPID_MOTION + 1) * 2 * MOTOR_Z_STEP_PER_REV * McSTEP_Z) )
          if (!bEditParameters)
          {
            snprintf(LCD_Row_2, 17, "%d  (%ld rpm)                ", MAX_RAPID_MOTION, (unsigned long)(30000000.0f / (unsigned long)( ((unsigned long)MAX_RAPID_MOTION + 1) * (unsigned long)2 * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ) );
          } else {
            snprintf(LCD_Row_2, 17, "%d%c (%ld rpm)                ", MAX_RAPID_MOTION, (char)255, (unsigned long)(30000000.0f / (unsigned long)( ((unsigned long)MAX_RAPID_MOTION + 1) * (unsigned long)2 * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ) );
          }
          lcd.print(LCD_Row_2);
          break;
        case   ID_MIN_RAPID_MOTION:
          lcd.print("MIN_RAPID_MOTION");
          lcd.setCursor(0, 1);
          //(16000000 / 32 / ((MIN_RAPID_MOTION + 1) * 2) / (MOTOR_Z_STEP_PER_REV * McSTEP_Z) * 60)
          //(unsigned int)(30000000.0 / ( (MIN_RAPID_MOTION + 1) * 2 * MOTOR_Z_STEP_PER_REV * McSTEP_Z) )    //Частота 16МГц, делитель 32?
          if (!bEditParameters)
          {
            snprintf(LCD_Row_2, 17, "%d  (%ld rpm)                ", MIN_RAPID_MOTION, (unsigned long)(30000000.0f / (unsigned long)( ((unsigned long)MIN_RAPID_MOTION + 1) * (unsigned long)2 * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ) );
          } else {
            snprintf(LCD_Row_2, 17, "%d%c (%ld rpm)                ", MIN_RAPID_MOTION, (char)255, (unsigned long)(30000000.0f / (unsigned long)( ((unsigned long)MIN_RAPID_MOTION + 1) * (unsigned long)2 * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ) );
          }
          lcd.print(LCD_Row_2);
          break;
        case   ID_REPEAt:
          lcd.print("REPEAt          ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", REPEAt, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_HC_SCALE_1:
          lcd.print("HC_SCALE_1      ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", HC_SCALE_1, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_HC_SCALE_10:
          lcd.print("HC_SCALE_10     ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", HC_SCALE_10, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
        case   ID_HC_START_SPEED_1:
          lcd.print("HC_STARTSPEED_1 ");
          lcd.setCursor(0, 1);
          //250000/(250+1)/800*60/2 = 37rpm
          //(unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_START_SPEED_1 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) )
          if (!bEditParameters)
          {
            snprintf(LCD_Row_2, 17, "%d  (%ld rpm)                ", HC_START_SPEED_1, (unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_START_SPEED_1 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ) );
          } else {
            snprintf(LCD_Row_2, 17, "%d%c (%ld rpm)                ", HC_START_SPEED_1, (char)255, (unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_START_SPEED_1 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ));
          }
          lcd.print(LCD_Row_2);
          break;
        case   ID_HC_MAX_SPEED_1:
          lcd.print("HC_MAX_SPEED_1  ");
          lcd.setCursor(0, 1);
          if (!bEditParameters)
          {
            snprintf(LCD_Row_2, 17, "%d  (%ld rpm)                ", HC_MAX_SPEED_1, (unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_MAX_SPEED_1 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ) );
          } else {
            snprintf(LCD_Row_2, 17, "%d%c (%ld rpm)                ", HC_MAX_SPEED_1, (char)255, (unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_MAX_SPEED_1 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ));
          }
          lcd.print(LCD_Row_2);
          break;
        case   ID_HC_START_SPEED_10:
          lcd.print("HC_STARTSPEED_10");
          lcd.setCursor(0, 1);
          if (!bEditParameters)
          {
            snprintf(LCD_Row_2, 17, "%d  (%ld rpm)                ", HC_START_SPEED_10, (unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_START_SPEED_10 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ) );
          } else {
            snprintf(LCD_Row_2, 17, "%d%c (%ld rpm)                ", HC_START_SPEED_10, (char)255, (unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_START_SPEED_10 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ));
          }
          lcd.print(LCD_Row_2);
          break;
        case   ID_HC_MAX_SPEED_10:
          lcd.print("HC_MAX_SPEED_10 ");
          lcd.setCursor(0, 1);
          if (!bEditParameters)
          {
            snprintf(LCD_Row_2, 17, "%d  (%ld rpm)                ", HC_MAX_SPEED_10, (unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_MAX_SPEED_10 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ) );
          } else {
            snprintf(LCD_Row_2, 17, "%d%c (%ld rpm)                ", HC_MAX_SPEED_10, (char)255, (unsigned long)(7500000.0f / (unsigned long)( ((unsigned long)HC_MAX_SPEED_10 + 1) * (unsigned long)MOTOR_Z_STEP_PER_REV * (unsigned long)McSTEP_Z) ));
          }
          lcd.print(LCD_Row_2);
          break;
        case   ID_HC_X_DIR:
          lcd.print("HC_X_DIR        ");
          lcd.setCursor(0, 1);
          snprintf(LCD_Row_2, 17, "%d%s", HC_X_DIR, EMPTY17);
          lcd.print(LCD_Row_2);
          break;
          //case   ID_DELAY_MOTOR_Z_ENABLE:
          //  lcd.print("DELAY_MOTOR_Z   ");
          //  lcd.setCursor(0, 1);
          //  snprintf(LCD_Row_2, 17, "%d%s", DELAY_MOTOR_Z_ENABLE, EMPTY17);
          //  lcd.print(LCD_Row_2);
          //  break;
          //case   ID_DELAY_MOTOR_X_ENABLE:
          //  lcd.print("DELAY_MOTOR_X   ");
          //  lcd.setCursor(0, 1);
          //  snprintf(LCD_Row_2, 17, "%d%s", DELAY_MOTOR_X_ENABLE, EMPTY17);
          //  lcd.print(LCD_Row_2);
          //  break;
      }
      //lcd.print(LCD_Row_2);
    }
  } else if (SETUP_MODE == MODE_READ_THREAD)
  {
    if (!bModeThread)                               //Если находимся в главном меню
    {
      lcd.print(THREAD1);                           //"   SHOW Ks/Km   "
      lcd.setCursor(0, 1);
      lcd.print(THREAD2);                           //"     THREAD     "
    } else {                                        //Если находимся внутри пункта меню MODE_READ_THREAD
      if (!bEditUserThread) //Если мы не редактируем пользовательскую резьбу...
      {
        lcd.print(THREAD3);                           //10 знакомест "PEЗЬБA:   ", из них 3 русских "З Ь Б"
        int lenTP = strlen(Thread_Info[CURRENT_THREAD].Thread_Print);
        if ( lenTP == 4 )
        {
          //4 символа, например "1.00" + добавка 2 русскими знаками "мм"
          snprintf(LCD_Row_1, 5, "%s", Thread_Info[CURRENT_THREAD].Thread_Print);        //"0.25" + "мм"
          lcd.print(LCD_Row_1);
          lcd.print(MM);                                                              //2 знакоместа "мм", из них 2 русскими "м м"
        }
        else if (lenTP == 3 )
        {
          //3 символа, например " 80" + добавка "tpi"
          snprintf(LCD_Row_1, 7, "%stpi", Thread_Info[CURRENT_THREAD].Thread_Print);     //" 80" + "tpi"
          lcd.print(LCD_Row_1);
        } else {
          //6 символов, без добавки (таких нет, но на всякий случай)
          snprintf(LCD_Row_1, 7, "%s", Thread_Info[CURRENT_THREAD].Thread_Print);        //"0.25mm"
          lcd.print(LCD_Row_1);
        }

        lcd.setCursor(0, 1);
        //snprintf(LCD_Row_2, 17, "%d,%d %d,%d               ", Thread_Info[CURRENT_THREAD].Ks_Div_Z, Thread_Info[CURRENT_THREAD].Km_Div_Z, Thread_Info[CURRENT_THREAD].Ks_Div_X, Thread_Info[CURRENT_THREAD].Km_Div_X);
        //snprintf(LCD_Row_2, 17, "%d,%04d %d,%04d%s", Thread_Info[CURRENT_THREAD].Ks_Div_Z, Thread_Info[CURRENT_THREAD].Km_Div_Z, Thread_Info[CURRENT_THREAD].Ks_Div_X, Thread_Info[CURRENT_THREAD].Km_Div_X, EMPTY16);

        if (Thread_Info[CURRENT_THREAD].Ks_Div_Z < 1)
        {
          snprintf(LCD_Row_2, 17, "%d,%04d %d,%04d%s", Thread_Info[CURRENT_THREAD].Ks_Div_Z, Thread_Info[CURRENT_THREAD].Km_Div_Z, Thread_Info[CURRENT_THREAD].Ks_Div_X, Thread_Info[CURRENT_THREAD].Km_Div_X, FAILURE);
        } else if (Thread_Info[CURRENT_THREAD].Ks_Div_Z < 2)
        {
          snprintf(LCD_Row_2, 17, "%d,%04d %d,%04d%s", Thread_Info[CURRENT_THREAD].Ks_Div_Z, Thread_Info[CURRENT_THREAD].Km_Div_Z, Thread_Info[CURRENT_THREAD].Ks_Div_X, Thread_Info[CURRENT_THREAD].Km_Div_X, MAYBEFAILURE);
        } else {
          snprintf(LCD_Row_2, 17, "%d,%04d %d,%04d%s", Thread_Info[CURRENT_THREAD].Ks_Div_Z, Thread_Info[CURRENT_THREAD].Km_Div_Z, Thread_Info[CURRENT_THREAD].Ks_Div_X, Thread_Info[CURRENT_THREAD].Km_Div_X, EMPTY16);
        }

      } else {   //Если мы РЕДАКТИРУЕМ пользовательскую резьбу...
        char FloatStep[8];
        dtostrf(Thread_Info[CURRENT_THREAD].Step, 8, 4, FloatStep);
        lcd.print(STEP);
        snprintf(LCD_Row_1, 11, " %s%s", FloatStep, EMPTY16);
        lcd.print(LCD_Row_1);
        lcd.setCursor(0, 1);
        lcd.print(PASS);
        snprintf(LCD_Row_2, 11, " %8d%s", Thread_Info[CURRENT_THREAD].Pass, EMPTY16);
      }
      lcd.print(LCD_Row_2);
    }
  } else if (SETUP_MODE == MODE_READ_CONE)
  {
    if (!bModeCone)                                 //Если находимся в главном меню
    {
      lcd.print(CONE1);                             //"   SHOW Ks/Km   "
      lcd.setCursor(0, 1);
      lcd.print(CONE2);                             //"      CONE      "
    } else {                                        //Если находимся внутри пункта меню MODE_READ_CONE
      if (bEditUserConeAB)                          //Если мы редактируем пользовательский конус A:B...
      {
        char FloatStepAB[10];
        dtostrf(Cone_Info[CURRENT_CONE].C1, 10, 4, FloatStepAB);
        snprintf(LCD_Row_1, 17, "A: %s               ", FloatStepAB);
        lcd.print(LCD_Row_1);
        lcd.setCursor(0, 1);
        dtostrf(Cone_Info[CURRENT_CONE].C2, 10, 4, FloatStepAB);
        snprintf(LCD_Row_2, 17, "B: %s               ", FloatStepAB);
        lcd.print(LCD_Row_2);
      } else if (bEditUserConeDEG)                  //Если мы редактируем пользовательский конус заданный в градусах...
      {
        char FloatStepDEG[10];
        dtostrf(Cone_Info[CURRENT_CONE].C1, 10, 4, FloatStepDEG);
        snprintf(LCD_Row_1, 17, "DEG: %s\x00DF               ", FloatStepDEG);
        lcd.print(LCD_Row_1);
        lcd.setCursor(0, 1);
        lcd.print(EMPTY16);
      } else {
        lcd.print(CONE3);                           //7 знакомест "KOHУC: ", из них 1 русский  "У"
        snprintf(LCD_Row_1, 10, "%s     ", Cone_Info[CURRENT_CONE].Cone_Print); //4 символа " KM0" или " 45°" + 5 символов  "     "
        lcd.print(LCD_Row_1);
        lcd.setCursor(0, 1);
        //snprintf(LCD_Row_2, 17, "%3d,%04d               ", Cone_Info[CURRENT_CONE].Cs_Div, Cone_Info[CURRENT_CONE].Cm_Div);
        if (Cone_Info[CURRENT_CONE].XZ == 0)
        {
          snprintf(LCD_Row_2, 17, "%3d,%04d      ZX", Cone_Info[CURRENT_CONE].Cs_Div, Cone_Info[CURRENT_CONE].Cm_Div);
        } else {
          snprintf(LCD_Row_2, 17, "%3d,%04d      XZ", Cone_Info[CURRENT_CONE].Cs_Div, Cone_Info[CURRENT_CONE].Cm_Div);
        }


        lcd.print(LCD_Row_2);
      }
    }
  } else if (SETUP_MODE == MODE_RESET_TO_DEFAULTS)
  {
    if (!bModeResetToDefaults)
    {
      lcd.print(RESET_TO_DEFAULTS1);
      lcd.setCursor(0, 1);
      lcd.print(RESET_TO_DEFAULTS2);
    } else {
      lcd.print(YES_NO1);
      lcd.setCursor(0, 1);
      lcd.print(YES_NO2);
    }
  } else if (SETUP_MODE == MODE_EXIT_AND_SAVING)
  {
    if (!bModeSaveAndExit)
    {
      lcd.print(EXIT_SAVING1);                            //"    EXIT AND    "
      lcd.setCursor(0, 1);
      lcd.print(EXIT_SAVING2);                            //"     SAVING     "
    } else {
      lcd.print(YES_NO1);
      lcd.setCursor(0, 1);
      lcd.print(YES_NO2);
    }
  } else if (SETUP_MODE == MODE_EXIT_WITHOUT_SAVING)
  {
    if (!bModeWithoutExit)
    {
      lcd.print(EXIT_NOTSAVING1);                         //"  EXIT WITHOUT  "
      lcd.setCursor(0, 1);
      lcd.print(EXIT_NOTSAVING2);                         //"     SAVING     "
    } else {
      lcd.print(YES_NO1);
      lcd.setCursor(0, 1);
      lcd.print(YES_NO2);
    }
  }

}

void Loop_Setup_Menu()
{
  if (!Button_Sel_Read)
  {
    BeepBeep();             //Звуковой сигнал при входе в цикл SETUP
    for (;;)                //Бесконечный цикл опроса кнопок меню и обновление экрана LCD в режиме SETUP
    {
      Setup_Menu();         //Опрос кнопок в режиме SETUP
      Setup_Print();        //Обновление экрана LCD в режиме SETUP
      _delay_ms(125);       //Задержка в режиме SETUP - влияет на скорость реакции кнопок меню в том числе
    }
  }
}
