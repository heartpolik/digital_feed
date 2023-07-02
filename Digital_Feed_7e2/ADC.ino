//Версия 1.4
//Раскомментировать строку "#define ADC_DEBUG" для отладки через "Монитор порта", скорость 115200 бод
//#define ADC_DEBUG
#define ADC_MINIMUM_VALUE 0
#define ADC_MAXIMUM_VALUE 1023
#define ADC_DEAD_ZONE 5

//Блок для проверки корректности заданных параметров ADC_MINIMUM_VALUE и ADC_MAXIMUM_VALUE
static_assert(ADC_MINIMUM_VALUE >= 0 && ADC_MINIMUM_VALUE <= 400 , "Неверно задано значение ADC_MINIMUM_VALUE. Допустимый диапазон 0...400.");
static_assert(ADC_MAXIMUM_VALUE >= 600 && ADC_MAXIMUM_VALUE <= 1023, "Неверно задано значение ADC_MAXIMUM_VALUE. Допустимый диапазон 600...1023.");

int ADC_Cycle = 0;    //Счётчик функции чтения параметров резистора. Предназначен для снижения частоты запросов к АЦП.
int New_ADC_Feed = 0; //Выносим из функции, как глобальную переменную. В ней хранится значение показаний резистора сразу после чтения из АЦП - до сглаживания и других обработок.
int Old_ADC_Feed = 0; //Переменная для запоминания предыдущего показания резистора до сглаживания
bool ADC_NeedUpdateFeedMode = false;  //Переменная для принудительного обновления показаний резистора при переключении из режима aFeed-на любой другой.
bool ADC_NeedUpdateaFeedMode = false;  //Переменная для принудительного обновления показаний резистора при переключении на режим aFeed из любого другого.

//Отладка ADC в "Монитор порта", скорость 115200 бод
void setup_ADC()
{
  //Настройка параметров АЦП
  ADMUX = 0x00  | (1 << REFS0)                              // выставляем опорное напряжение Vcc 5В (REFS0 = 1, REFS1 = 0)
          | (1 << MUX0) | (1 << MUX1) | (1 << MUX2);    // снимать сигнал будем с входа Ардуины A7 - ADC7 - PORTF7 (MUX0 = 1, MUX1 = 1, MUX2 = 1)
  ADCSRA = 0x00 | (1 << ADEN)                               // Включаем АЦП (Bit7 ADC Enable)
           | (1 << ADPS2)      //Делитель 16  ADPS0 = 0, ADPS1 = 0, ADPS2 = 1 - Частота преобразования 1МГц, точность около 8 бит
           | (1 << ADSC);                            //(Bit6 ADC Start Conversion) Выполнить первое считывание АЦП. После цикла чтения флаг сбросится в 0. Аналог команды bitWrite(ADCSRA, 6, 1);// Запускаем преобразование установкой бита 6 (=ADSC) в ADCSRA

}

/////////// Опрос Переменника Подачи ///////////
bool Read_ADC_ResistorFeed()
{
  if (++ADC_Cycle > 4999) // Ставим счётчик, чтобы уменьшить количество обращений к чтению параметров АЦП
  {

//    _time = micros();
    
    //Работает в Proteus
    //Запуск ADC-преобразования, ждём окончания и считываем значение
    ADCSRA |= (1 << ADSC);                  // Запускаем ADC-преобразование
    while ((ADCSRA & (1 << ADIF)) == 0);    // Ожидаем поднятия флага об окончании преобразования
    New_ADC_Feed = (ADCL | ADCH << 8);      // Считываем полученное значение

    ADC_Cycle = 0;      //После выполнения чтения резистора - сбрасываем счётчик

//    _time = micros() - _time;
//    Serial.print("ADC time=");Serial.print(_time);Serial.print("\n\r");
//    //По замерам в протеусе время 16-20 мкс

#ifdef _DEBUG_ADC
    Serial.print("New_ADC_Feed = "); Serial.print(New_ADC_Feed); Serial.print("\n");
#endif
  }

  if (New_ADC_Feed > ADC_Feed + ADC_DEAD_ZONE || New_ADC_Feed < ADC_Feed - ADC_DEAD_ZONE)
  {
    //Проверка заданных пределов входного значения
    if (New_ADC_Feed < ADC_MINIMUM_VALUE)
    {
      New_ADC_Feed = ADC_MINIMUM_VALUE;
    }
    else if (New_ADC_Feed > ADC_MAXIMUM_VALUE)
    {
      New_ADC_Feed = ADC_MAXIMUM_VALUE;
    }

#ifdef _DEBUG_ADC
    //    Serial.print("New_ADC_Feed ->"); Serial.print(New_ADC_Feed); Serial.print("\n");
#endif
  }

  //Сглаживание
  //if ( ! ( ADC_Cycle % 625 ) )      //5000 разделяем на 8 под-циклов по 625
  if ( ! ( ADC_Cycle % 250 ) )      //5000 разделяем на 20 под-циклов по 250
  {
    if (++x > (sizeof(ADC_Array) / sizeof(ADC_Array[0]) - 1))   //Записано в общем виде.
    {
      x = 0;
    }

    Old_ADC_Feed = ADC_Feed;        //Сохраняем предыдущее показание резистора с учётом сглаживания

    //Выполняем сглаживание показаний
    Sum_ADC = Sum_ADC - ADC_Array[x];
    ADC_Array[x] = New_ADC_Feed;
    Sum_ADC = Sum_ADC + New_ADC_Feed;
    ADC_Feed = Sum_ADC / (sizeof(ADC_Array) / sizeof(ADC_Array[0]));    //Записано в общем виде.

    //Если после сглаживания показания изменились возвращаем true, если нет - false
    if (ADC_Feed != Old_ADC_Feed)
    {
      return true;
    } else {
      return false;
    }
  }

  return false;
}

//inline __attribute__((always_inline))
bool Update_ADC_Feed()
{
  //Старая формула под обычный диапазон 0...1023
  //uint16_t Feed_mm_New = (MAX_FEED - long(MAX_FEED - MIN_FEED + 1) * ADC_Feed / 1024);
  //Новая формула с учётом настройки диапазона под конкретный резистор
  //uint16_t Feed_mm_New = (MAX_FEED - long(MAX_FEED - MIN_FEED + 1) * (ADC_Feed - ADC_MINIMUM_VALUE) / (ADC_MAXIMUM_VALUE - ADC_MINIMUM_VALUE + 1));
  uint16_t Feed_mm_New = (MAX_FEED - (long)(MAX_FEED - MIN_FEED + 1) * (ADC_Feed - ADC_MINIMUM_VALUE) / (ADC_MAXIMUM_VALUE - ADC_MINIMUM_VALUE + 1));
  //-
  if (Feed_mm_New != Feed_mm)
  {
    Feed_mm = Feed_mm_New;
    return true;
  } else {
    return false;
  }
}

//inline __attribute__((always_inline))
bool Update_ADC_aFeed()
{
  //Старая формула под обычный диапазон 0...1023
  //uint16_t aFeed_mm_New = (MAX_aFEED / 10 - long(MAX_aFEED / 10 - MIN_aFEED / 10 + 1) * ADC_Feed / 1024);
  //Новая формула с учётом настройки диапазона под конкретный резистор
  //uint16_t aFeed_mm_New = (MAX_aFEED / 10 - long(MAX_aFEED / 10 - MIN_aFEED / 10 + 1) * (ADC_Feed - ADC_MINIMUM_VALUE) / (ADC_MAXIMUM_VALUE - ADC_MINIMUM_VALUE + 1));
  uint16_t aFeed_mm_New = (MAX_aFEED / 10 - (long)(MAX_aFEED / 10 - MIN_aFEED / 10 + 1) * (ADC_Feed - ADC_MINIMUM_VALUE) / (ADC_MAXIMUM_VALUE - ADC_MINIMUM_VALUE + 1));
  //-
  aFeed_mm_New = (aFeed_mm_New * 10);
  if (aFeed_mm_New != aFeed_mm)
  {
    aFeed_mm = aFeed_mm_New;
    return true;
  } else {
    return false;
  }
}

void Read_ADC_Feed()
{
  switch (Mode)
  {
    case Mode_Feed:
    //case Mode_Cone_L:       //Перенесено т.к. режим КОНУСОВ стал АСИНХРОННЫМ
    //case Mode_Cone_R:       //Перенесено т.к. режим КОНУСОВ стал АСИНХРОННЫМ
    case Mode_Sphere:

      //case Mode_Thread:     //Только для теста производительности (Как только проводится опрос резистора - падает производительность и тахометр занижает показания в разы!!!

      //Read_ADC_ResistorFeed();      //Выполняем опрос Переменного резистора подач    //Исключение для режима "РЕЗЬБА". Для "Mode_Feed", "Mode_Cone_L", "Mode_Cone_R", "Mode_Sphere" - обрабатываем. Так меньше скетч, но есть warning

      //if (!Read_ADC_ResistorFeed() )
      //  break;

      if (ADC_NeedUpdateFeedMode)
      {
        ADC_NeedUpdateFeedMode = false;
      } else {
        if (!Read_ADC_ResistorFeed() )
          break;
      }


      if (Update_ADC_Feed())      //Проверяем было ли обновление показаний Переменного резистора подач
      {
        ADC_NeedUpdateaFeedMode = true;
        Print();
        Beep();
        //OLD
        //if (Button_Rapid != 0)      //Сначала проверка условия на кнопку ускоренной подачи
        //NEW
        if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          //---
        {
          if (Mode == Mode_Feed)   ////////////////////////////////
          {
            if (Joy_Z_flag == ON && Z_WORKING_FEED_FLAG == ON)
            {
              b_flag = false;
              if (Motor_Z_Dir == CW)
              {
                //Feed_Left(a_flag, b_flag);
                NEW_Feed_Left(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
              else
              {
                //Feed_Right(a_flag, b_flag);
                NEW_Feed_Right(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
            }
            else if (Joy_X_flag == ON && X_WORKING_FEED_FLAG == ON)
            {
              b_flag = false;
              if (Motor_X_Dir == CW)
              {
                //Feed_Front(a_flag, b_flag);
                NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
              else
              {
                //Feed_Rear(a_flag, b_flag);
                NEW_Feed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
            }
          }
          //Перенесено т.к. режим КОНУСОВ стал АСИНХРОННЫМ
          /*
            else if (Mode == Mode_Cone_L || Mode == Mode_Cone_R)   ////////////////////////////////
            {
            if (Joy_Z_flag == ON && Z_WORKING_FEED_FLAG == ON)
            {
              b_flag = false;
              if (Motor_Z_Dir == CW)
              {
                //Cone_Left(a_flag, b_flag);
                NEW_Cone_Left(a_flag, b_flag, false);     //ОБЫЧНАЯ ПОДАЧА
              }
              else
              {
                //Cone_Right(a_flag, b_flag);
                NEW_Cone_Right(a_flag, b_flag, false);     //ОБЫЧНАЯ ПОДАЧА
              }
            }
            else if (Joy_X_flag == ON && X_WORKING_FEED_FLAG == ON)
            {
              b_flag = false;
              if (Motor_X_Dir == CW)
              {
                //Feed_Front(a_flag, b_flag);
                NEW_Feed_Front(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
              else
              {
                //Feed_Rear(a_flag, b_flag);
                NEW_Feed_Rear(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
            }
            }
          */
        }
      }
      break;

    case Mode_Cone_L:       //Перенесено т.к. режим стал АСИНХРОННЫМ
    case Mode_Cone_R:       //Перенесено т.к. режим стал АСИНХРОННЫМ
    case Mode_aFeed:
      //Read_ADC_ResistorFeed();     //Выполняем опрос Переменного резистора подач

      //if (!Read_ADC_ResistorFeed())
      //  break;

      if (ADC_NeedUpdateaFeedMode)
      {
        ADC_NeedUpdateaFeedMode = false;
      } else {
        if (!Read_ADC_ResistorFeed() )
          break;
      }

      if (Update_ADC_aFeed())      //Проверяем было ли обновление показаний Переменного резистора подач
      {
        ADC_NeedUpdateFeedMode = true;
        Print();
        Beep();
        //OLD
        //if (Button_Rapid != 0)      //Сначала проверка условия на кнопку ускоренной подачи
        //NEW
        if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          //---
        {
          //NEW
          if (Mode == Mode_aFeed)
          {
            //-
            if (Joy_Z_flag == ON && Z_WORKING_FEED_FLAG == ON)
            {
              b_flag = false;
              if (Motor_Z_Dir == CW)
              {
                //aFeed_Left(a_flag, b_flag);
                NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);      //ОБЫЧНАЯ АСИНХРОННАЯ ПОДАЧА
              }
              else
              {
                //aFeed_Right(a_flag, b_flag);
                NEW_aFeed_Right(a_flag, b_flag, FORCE_SLOW);      //ОБЫЧНАЯ АСИНХРОННАЯ ПОДАЧА
              }
            }
            else if (Joy_X_flag == ON && X_WORKING_FEED_FLAG == ON)
            {
              b_flag = false;
              if (Motor_X_Dir == CW)
              {
                //aFeed_Front(a_flag, b_flag);
                NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);      //ОБЫЧНАЯ АСИНХРОННАЯ ПОДАЧА
              }
              else
              {
                //aFeed_Rear(a_flag, b_flag);
                NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);      //ОБЫЧНАЯ АСИНХРОННАЯ ПОДАЧА
              }
            }
            //--------------
            //Перенесено т.к. режим КОНУСОВ стал АСИНХРОННЫМ
          }
          else if (Mode == Mode_Cone_L || Mode == Mode_Cone_R)   ////////////////////////////////
          {
            if (Joy_Z_flag == ON && Z_WORKING_FEED_FLAG == ON)
            {
              b_flag = false;
              if (Motor_Z_Dir == CW)
              {
                //Cone_Left(a_flag, b_flag);
                NEW_Cone_Left(a_flag, b_flag, FORCE_SLOW);     //ОБЫЧНАЯ ПОДАЧА (АСИНХРОННАЯ)
              }
              else
              {
                //Cone_Right(a_flag, b_flag);
                NEW_Cone_Right(a_flag, b_flag, FORCE_SLOW);     //ОБЫЧНАЯ ПОДАЧА (АСИНХРОННАЯ)
              }
            }
            else if (Joy_X_flag == ON && X_WORKING_FEED_FLAG == ON)
            {
              b_flag = false;
              if (Motor_X_Dir == CW)
              {
                //Feed_Front(a_flag, b_flag);
                //NEW_Feed_Front(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
                NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ АСИНХРОННОЙ ПОДАЧИ
              }
              else
              {
                //Feed_Rear(a_flag, b_flag);
                //NEW_Feed_Rear(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
                NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ АСИНХРОННОЙ ПОДАЧИ
              }
            }
          }

          //--------------
        }
      }
      break;
      //
      //case Mode_Reserve:
      //case Mode_Divider:
      //default:
      //                 break;   //В этих режимах ничего не делаем - на выход
  }
  //-
}
