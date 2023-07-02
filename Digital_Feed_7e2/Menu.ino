#define DELAY_ENTER_KEYCYCLE 10   //Задержка для входа в режим автонажатия. Значения от 1 до разумного максимума. По умолчанию 10.
#define DELAY_INTO_KEYCYCLE 5     //Интервал срабатывания автонажатия. Значения от 1 до DELAY_ENTER_KEYCYCLE. По умолчанию 5.

byte KeyCycle = 0;            //Это глобальная переменная счётчик циклов обработчика клавиш стрелок. Размерность byte, наверное хватит.

void Menu()
{
  //Для отладки
  //Serial.begin(115200);


  /////// Джойстик ///////////////////////////////////////////////
  byte Joy_New = Joy_Read;
  {
    //OLD
    /*
      if      (Joy_New == B00001110) Joy_LeftPressed();
      else if (Joy_New == B00001101) Joy_RightPressed();
      else if (Joy_New == B00001011) Joy_UpPressed();
      else if (Joy_New == B00000111) Joy_DownPressed();
      else if (Joy_New == B00001111) Joy_NoPressed();
    */
    //Opti Switch. Выигрыш 24 байт (только при использовании default: Joy_NoPressed())
    //68098 68146!!! 68074
    switch (Joy_New)
    {
      case B00001110:                 //14
        Joy_LeftPressed();
        break;
      case B00001101:                 //13
        Joy_RightPressed();
        break;
      case B00001011:                 //11
        Joy_UpPressed();
        break;
      case B00000111:                 //7
        Joy_DownPressed();
        break;
      case B00001111:                 //15
        //default:                 //Именно default. Т.е. от n-го сравнения с B00001111 отказываемся, по-умолчанию если ни одна из кнопок джойстика не нажата, то считаем, что они не нажаты (звучит глупо, но это так).
        //Serial.print("Joy_NoPressed...\n");
        Joy_NoPressed();
        break;
    }
    //-
  }
  //Serial.print("Joy_New="); Serial.print(Joy_New); Serial.print("\n");

  /////// Переключатель Режима ////////////////////////////////
  if (!Joy_Z_flag && !Joy_X_flag)
  {
    byte Mode_New = Mode_Read;
    if (Mode_New != Mode_Old)
    {
      //OLD
      /*
        if      (Mode_New == B01111111) {
        Switch_Thread();
        }
        else if (Mode_New == B10111111) {
        Switch_Feed();
        }
        else if (Mode_New == B11011111) {
        Switch_aFeed();
        }
        else if (Mode_New == B11101111) {
        Switch_Cone_L();
        }
        else if (Mode_New == B11110111) {
        Switch_Cone_R();
        }
        else if (Mode_New == B11111011) {
        Switch_Reserve();
        }
        else if (Mode_New == B11111101) {
        Switch_Sphere();
        }
        else if (Mode_New == B11111110) {
        Switch_Divider();
        }
      */
      //Opti SWITCH. Выигрыш 278 байт.
      switch (Mode_New)
      {
        //Ещё есть состояние 255, это когда переключатель в промежуточном положении, и ни один контакт селектора не замкнут. 255 состояние возникает
        //при каждом переключении режима: 127-255-191-255-223-255-239-255-...255-254
        case B01111111:             //127
          Switch_Thread();
          break;
        case B10111111:             //191
          Switch_Feed();
          break;
        case B11011111:             //223
          Switch_aFeed();
          break;
        case B11101111:             //239
          Switch_Cone_L();
          break;
        case B11110111:             //247
          Switch_Cone_R();
          break;
        case B11111011:             //251
          Switch_Reserve();
          break;
        case B11111101:             //253
          Switch_Sphere();
          break;
        case B11111110:             //254
          Switch_Divider();
          break;
          //default:                    //255 в нашем случае
          //  break;
      }
      //Serial.print("Mode_New="); Serial.print(Mode_New); Serial.print("\n");
      //---
      Mode_Old = Mode_New;
    }
    ///////// Переключатель Подрежима //////////////////////////////
    //Opti: Перенесён сюда, убрана лишняя проверка условия. Выигрыш 8 байт.
    byte Submode_New = Submode_Read;
    if (Submode_New != Submode_Old)
    {
      //OLD
      /*
        if      (Submode_New == B11000000) Switch_Int();
        else if (Submode_New == B10100000) Switch_Man();
        else if (Submode_New == B01100000) Switch_Ext();
      */
      //Opti2 Замена на switch. Выигрыш 16 байт.
      switch (Submode_New)
      {
        //Ещё есть состояние 254, это когда переключатель в промежуточном положении, и ни один контакт селектора не замкнут. 254 состояние возникает
        //при каждом переключении режима: 192-224-160-224-96
        case B11000000:             //192
          Switch_Int();
          break;
        case B01100000:             //96
          Switch_Ext();
          break;
        case B10100000:             //160
          Switch_Man();
          break;
          //default:                  //224
          //  break;
      }
      //Serial.print("Submode_New="); Serial.print(Submode_New); Serial.print("\n");
      //-
      Submode_Old = Submode_New;
    }
    //---
  }

  //OLD
  /*
    if (!Joy_Z_flag && !Joy_X_flag)
    {
      byte Submode_New = Submode_Read;
      if (Submode_New != Submode_Old)
      {
        if      (Submode_New == B11000000) Switch_Int();
        else if (Submode_New == B10100000) Switch_Man();
        else if (Submode_New == B01100000) Switch_Ext();
        Submode_Old = Submode_New;
      }
    }
  */

  /////////// Кнопки Меню //////////////////////////////////////
  /////////// Кнопка Select, или OK //////////////////////////////////////
  byte Button_Sel_New = Button_Sel_Read;
  if (Button_Sel_New == Button_Sel_Old)
  {
    if (!Button_Sel_Read) {
      Key_Select_Pressed();
    } else {
      key_sel_flag = false;
      Print();
    }
  }
  Button_Sel_Old = Button_Sel_New;


  //OLD
  /////////// Кнопки Меню - 4 Стрелки без автозажатия, дефолтный код Олега
  /*
     byte Button_New = Buttons_Read;
     if (Button_New == Button_Old)
     {
        if      (Button_New == B00000111) Key_Down_Pressed();
        else if (Button_New == B00001011) Key_Up_Pressed();
        else if (Button_New == B00001101) Key_Right_Pressed();
        else if (Button_New == B00001110) Key_Left_Pressed();
        else     button_flag = false;
     }
     Button_Old = Button_New;
  */

  /////////// Кнопки Меню - 4 Стрелки (с разрешённым автозажатием клавиш стрелок) //////////////////////////////////////
  byte Button_New = Buttons_Read;
  if (Button_New != Button_Old)                                  //Меняем == на !=
  {
    //Кнопочку Нажали или Отпустили, состояние переменной изменилось
    //OLD
    /*
      if      (Button_New == B00000111) Key_Down_Pressed();
      else if (Button_New == B00001011) Key_Up_Pressed();
      else if (Button_New == B00001101) Key_Right_Pressed();
      else if (Button_New == B00001110) Key_Left_Pressed();
      else     button_flag = false;
    */
    //Opti SWITCH. Выигрыш 20 байт.
    switch (Button_New)
    {
      case B00000111:
        Key_Down_Pressed();
        break;
      case B00001011:
        Key_Up_Pressed();
        break;
      case B00001101:
        Key_Right_Pressed();
        break;
      case B00001110:
        Key_Left_Pressed();
        break;
      default:
        button_flag = false;
        break;
    }
    //---
    KeyCycle = 0;                                               //Обнуляем переменную цикла
  } else {
    //Кнопочки(-ку) удерживают нажатой или наоборот сохраняет отпущенное состояние
    KeyCycle++;                                                 //Запускаем счётчик циклов
    if (KeyCycle > DELAY_ENTER_KEYCYCLE)                        //это длительность удерживания клавиши для входа в цикл
    {
      //OLD
      if (Button_New == B00000111)
      {
        button_flag = false;                                    //Гасим флаг, чтобы повторно можно было вызвать обработчик этой кнопки
        Key_Down_Pressed();
      }
      else if (Button_New == B00001011)
      {
        button_flag = false;                                    //Гасим флаг, чтобы повторно можно было вызвать обработчик этой кнопки
        Key_Up_Pressed();
      }
      else if (Button_New == B00001101)
      {
        button_flag = false;                                    //Гасим флаг, чтобы повторно можно было вызвать обработчик этой кнопки
        Key_Right_Pressed();
      }
      else if (Button_New == B00001110)
      {
        button_flag = false;                                    //Гасим флаг, чтобы повторно можно было вызвать обработчик этой кнопки
        Key_Left_Pressed();
      }
      KeyCycle = (DELAY_ENTER_KEYCYCLE - DELAY_INTO_KEYCYCLE);  //Обнуляем переменную цикла или не до конца обнуляем, чтобы в нажатом состоянии цикл срабатывания был короче
    }
  }
  Button_Old = Button_New;
  //----------------------------------------------------------------------------------------------------------------------------------------

  /////// Кнопки Лимитов ///////////////////////////////////////
  byte Limit_Button_New = Limit_Buttons_Read;
  if (Limit_Button_New == Limit_Button_Old)
  {
    //OLD IF-IF ELSE-IF ELSE...ELSE
    /*
      if      (Limit_Button_New == B00010101) Limit_Left_Pressed();
      else if (Limit_Button_New == B01000101) Limit_Right_Pressed();
      else if (Limit_Button_New == B01010001) Limit_Front_Pressed();
      else if (Limit_Button_New == B01010100) Limit_Rear_Pressed();
      else     limit_button_flag = false;
    */
    //NEW Opti SWITCH. Выигрыш 94 байт.
    switch (Limit_Button_New)
    {
      case B00010101:
        Limit_Left_Pressed();
        break;
      case B01000101:
        Limit_Right_Pressed();
        break;
      case B01010001:
        Limit_Front_Pressed();
        break;
      case B01010100:
        Limit_Rear_Pressed();
        break;
      default:
        limit_button_flag = false;
        break;
    }
    //---
  }
  Limit_Button_Old = Limit_Button_New;


  /////// Переключатель Оси для ГРИ ////////////////////////////
  byte Hand_Axis_New = Hand_Axis_Read;
  if (Hand_Axis_New != Hand_Axis_Old)
  {
    //OLD
    /*
      if      (Hand_Axis_New == B00100000) {
      Switch_Hand_Axis_Z();
      }
      else if (Hand_Axis_New == B00010000) {
      Switch_Hand_Axis_X();
      }
      else if (Hand_Axis_New == B00110000) {
      Switch_Hand_Axis_No();
      }
    */
    //Opti SWITCH. Выигрыш 24 байт.
    //У этого переключателя состояния только 32-48-16, поэтому среднее положение можно как default использовать
    switch (Hand_Axis_New)
    {
      case B00100000:                 //32
        Switch_Hand_Axis_Z();
        break;
      case B00010000:                 //16
        Switch_Hand_Axis_X();
        break;
      //case B00110000:                 //48
      default:         //Именно default. Т.е. от 3-го сравнения с B00110000 отказываемся, по-умолчанию тумблер считается в среднем положении.
        Switch_Hand_Axis_No();
        break;
    }
    //Serial.print("Hand_Axis_New="); Serial.print(Hand_Axis_New); Serial.print("\n");
    //---
    Hand_Axis_Old = Hand_Axis_New;
  }


  /////// Переключатель Масштаба для РГИ //////////////////////
  byte Hand_Scale_New = Hand_Scale_Read;
  if (Hand_Scale_New != Hand_Scale_Old)
  {
    //OLD
    /*
      if      (Hand_Scale_New == B00000001) {
      Switch_Scale_x1();
      }
      else if (Hand_Scale_New == B00000010) {
      Switch_Scale_x10();
      }
    */
    //Opti. Выигрыш 6 байт.
    //У этого переключателя состояния 1-3-2. Состояние 3, в момент переключения тумблера - не используется
    switch (Hand_Scale_New)
    {
      case B00000010:             //2   Тумблер в положении "x10".
        Switch_Scale_x10();
        break;
      case B00000001:             //1   Тумблер в положении "x1".
        Switch_Scale_x1();
        break;
        //default:                  //3   Не используется, возникает в момент переключения тумблера
        //  break;
    }
    //Serial.print("Hand_Scale_New="); Serial.print(Hand_Scale_New); Serial.print("\n");
    //---
    Hand_Scale_Old = Hand_Scale_New;
  }

  //OLD
  CLEAR_KEYB_TIMER;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработка Джойстика ********** ///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработчик Джойстик Влево **********
//Opti IF-ELSE заменён на SWITCH (Выигрыша нет). Часть суб-режимов FORCE_SLOW переведена на default - вот тут выигрыш 8 байт... Читаемость кода, как по мне, стала лучше
void Joy_LeftPressed()
{
  flag_j = ON;                        //Зажигаем Флаг Джойстика

  //Если переключатель ручного энкодера в активной позиции - взводим флаг ошибки3
  if (hand_Z == ON || hand_X == ON)
  {
    err_3_flag = true;
  }
  //Принудительно выключаем ручной энкодер
  Disa_INT_Hcoder();                  //Выключаем прерывание от ручного энкодера
  Disable_INT_OCR3A();                //Выключаем обработчик ручного энкодера по оси Z
  Disable_INT_OCR3B();                //Выключаем обработчик ручного энкодера по оси X
  hand_Z = OFF;                       //Гасим флаг управления оси Z от ручного энкодера
  hand_X = OFF;                       //Гасим флаг управления оси X от ручного энкодера
  Hand_Count = 0;                     //Сброс на 0 переменных ручного энкодера
  Hand_Count_New = 0;                 //Сброс на 0 переменных ручного энкодера
  Hand_Count_Old = 0;                 //Сброс на 0 переменных ручного энкодера
  Hand_Z_Pos = 0;                     //Сброс на 0 переменных ручного энкодера
  Hand_X_Pos = 0;                     //Сброс на 0 переменных ручного энкодера
  //Выходим из функции при наличии ошибки3
  if (err_3_flag == true)
  {
    return;
  }

  //Opti Mode на основе Switch
  switch (Mode)
  {
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //РЕЗЬБА
    case Mode_Thread:
      switch (Sub_Mode_Thread)
      {
        case Sub_Mode_Thread_Ext:                     //РЕЗЬБА-НАРУЖНАЯ
          if (Spindle_Dir == CW) {
            Thread_Ext_Left();
          } else {
            Thread_Ext_Right();
          }
          break;

        case Sub_Mode_Thread_Int:                     //РЕЗЬБА-ВНУТРЕННЯЯ
          if (Spindle_Dir == CW) {
            Thread_Int_Left();
          } else {
            Thread_Int_Right();
          }
          break;

        case Sub_Mode_Thread_Man:                   //РЕЗЬБА-РУЧНОЙ РЕЖИМ
          //default:
          if (err_1_flag || err_2_flag) break;
          if (Spindle_Dir == CW)
          {
            Thread_Left(c_flag, d_flag);
          } else
          {
            //OLD
            //if (!Button_Rapid) {
            //  Limit_Pos = Limit_Pos_Min;
            //} else {
            //  Limit_Pos = Limit_Pos_Right + Brake_Compens;
            //}
            //NEW
            if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
            {
              Limit_Pos = Limit_Pos_Right + Brake_Compens;
            } else {                      //Иначе нажата кнопка "Быстрая подача"
              Limit_Pos = Limit_Pos_Min;
            }
            //---
            Thread_Right(c_flag, d_flag);
          }
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //СИНХРОННАЯ ПОДАЧА
    case Mode_Feed:
      switch (Sub_Mode_Feed)
      {
        case Sub_Mode_Feed_Ext:                       //СИНХРОННАЯ ПОДАЧА-НАРУЖНАЯ
          Feed_Ext_Left();
          break;

        case Sub_Mode_Feed_Int:                       //СИНХРОННАЯ ПОДАЧА-ВНУТРЕННЯЯ
          Feed_Int_Left();
          break;

        case Sub_Mode_Feed_Man:                     //СИНХРОННАЯ ПОДАЧА-РУЧНОЙ РЕЖИМ
          //default:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          //NEW
          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR5A == max_OCR5A)
            {
              Z_NEED_RUN_RAPID_FLAG = OFF;
              if (!Z_WORKING_RAPID_FLAG)
              {
                if (Read_Z_Ena_State == false) Motor_Z_Enable();
                //-Z_NEED_RUN_FEED_FLAG = ON;                                     //СМУЩАЕТ включение флага до вызова функции NEW_...
                //Feed_Left(a_flag, b_flag);
                NEW_Feed_Left(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_Z_Pos < (Limit_Pos_Left - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {

              Z_NEED_RUN_FEED_FLAG = OFF;
              if (!Z_WORKING_FEED_FLAG)
              {
                //Rapid_Feed_Left(a_flag, b_flag);
                NEW_Feed_Left(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
              }

              }
            */
            //NEW START
            if (!Z_WORKING_FEED_FLAG && !Z_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_Z_Pos < (Limit_Pos_Left - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_Feed_Left(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
              }
            }
            //-
          }
          //---
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //АСИНХРОННАЯ ПОДАЧА
    case Mode_aFeed:
      switch (Sub_Mode_aFeed)
      {
        case Sub_Mode_aFeed_Ext:                                  //АСИНХРОННАЯ ПОДАЧА-НАРУЖНАЯ
          NEW_aFeed_Ext_Left();
          break;

        case Sub_Mode_aFeed_Int:                                  //АСИНХРОННАЯ ПОДАЧА-ВНУТРЕННЯЯ
          NEW_aFeed_Int_Left();
          break;

        case Sub_Mode_aFeed_Man:                                //АСИНХРОННАЯ ПОДАЧА-РУЧНОЙ РЕЖИМ
          //default:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          //NEW
          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR4A == max_OCR4A)     //Косвенно подразумевается, что мотор неподвижен - частота минимальная, как на старте
            {
              Z_NEED_RUN_RAPID_FLAG = OFF;               //Выключается командный флаг быстрой подачи (мотор переходит на торможение если он работал на быстрой)
              if (!Z_WORKING_RAPID_FLAG)           //Ждём флага остановки мотора на быстрой подаче и потом вызывается NEW_aFeed_Left-SLOW
              {
                if (Read_Z_Ena_State == false) Motor_Z_Enable();
                //-Z_NEED_RUN_FEED_FLAG = ON;                                     //СМУЩАЕТ включение флага до вызова функции NEW_...
                //aFeed_Left(a_flag, b_flag);
                NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);      //ОБЫЧНАЯ АСИНХРОННАЯ ПОДАЧА
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_Z_Pos < (Limit_Pos_Left - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))    //Так понимаю, что мотор не стоит вблизи левого упора
              {
              Z_NEED_RUN_FEED_FLAG = OFF;            //Выключается командный флаг обычной подачи (мотор переходит на торможение)
              if (!Z_WORKING_FEED_FLAG)             //Ждём флага остановки мотора по обычной подачи и потом вызывается NEW_aFeed_Left-RAPID
              {
                //Rapid_Feed_Left(a_flag, b_flag);
                NEW_aFeed_Left(a_flag, b_flag, FORCE_RAPID);      //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
              }
              }
            */
            //NEW START
            if (!Z_WORKING_FEED_FLAG && !Z_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_Z_Pos < (Limit_Pos_Left - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))    //Так понимаю, что мотор не стоит вблизи левого упора
              {
                NEW_aFeed_Left(a_flag, b_flag, FORCE_RAPID);      //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
              }
            }
            //---
          }
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //КОНУСА
    case Mode_Cone_L:
    case Mode_Cone_R:

      //NEW
      switch (Sub_Mode_Cone)
      {
        case Sub_Mode_Cone_Man:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          //NEW
          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR4A == max_OCR4A)
            {
              Z_NEED_RUN_RAPID_FLAG = OFF;
              if (!Z_WORKING_RAPID_FLAG)
              {
                //Cone_Left(a_flag, b_flag);
                NEW_Cone_Left(a_flag, b_flag, FORCE_SLOW);     //ОБЫЧНАЯ ПОДАЧА
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_Z_Pos < (Limit_Pos_Left - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
              Z_NEED_RUN_FEED_FLAG = OFF;
              if (!Z_WORKING_FEED_FLAG)
              {
                //Rapid_Cone_Left(a_flag, b_flag);
                NEW_Cone_Left(a_flag, b_flag, FORCE_RAPID);     //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
              }
              }
            */
            //NEW START
            if (!Z_WORKING_FEED_FLAG && !Z_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_Z_Pos < (Limit_Pos_Left - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_Cone_Left(a_flag, b_flag, FORCE_RAPID);     //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
              }
            }
            //---
          }
          break;
        case Sub_Mode_Cone_Int:
          NEW_Cone_Int_Left();
          break;

        case Sub_Mode_Cone_Ext:
          NEW_Cone_Ext_Left();
          break;
          //---
          //New
      }
      //---
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //СФЕРА
    case Mode_Sphere:
      if (err_1_flag || err_2_flag) break;
      Sphere_Ext(a_flag, b_flag);
      break;
      //------------------------------------------------------------------------------------------------------------------------------------------------------------
  }   //END Switch(Mode)
}

// ********** Обработчик Джойстик Вправо **********
//Opti IF-ELSE заменён на SWITCH (Выигрыша нет, даже проигрыш 10 байт). Часть суб-режимов FORCE_SLOW переведена на default. Читаемость кода, как по мне, стала лучше
void Joy_RightPressed()
{
  flag_j = ON;

  //Если переключатель ручного энкодера в активной позиции - взводим флаг ошибки3
  if (hand_Z == ON || hand_X == ON)
  {
    err_3_flag = true;
  }
  //Принудительно выключаем ручной энкодер
  Disa_INT_Hcoder();                  //Выключаем прерывание от ручного энкодера
  Disable_INT_OCR3A();                //Выключаем обработчик ручного энкодера по оси Z
  Disable_INT_OCR3B();                //Выключаем обработчик ручного энкодера по оси X
  hand_Z = OFF;                       //Гасим флаг управления оси Z от ручного энкодера
  hand_X = OFF;                       //Гасим флаг управления оси X от ручного энкодера
  Hand_Count = 0;                     //Сброс на 0 переменных ручного энкодера
  Hand_Count_New = 0;                 //Сброс на 0 переменных ручного энкодера
  Hand_Count_Old = 0;                 //Сброс на 0 переменных ручного энкодера
  Hand_Z_Pos = 0;                     //Сброс на 0 переменных ручного энкодера
  Hand_X_Pos = 0;                     //Сброс на 0 переменных ручного энкодера
  //Выходим из функции при наличии ошибки3
  if (err_3_flag == true)
  {
    return;
  }

  switch (Mode)
  {
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //РЕЗЬБА
    case Mode_Thread:
      switch (Sub_Mode_Thread)
      {
        case Sub_Mode_Thread_Ext:                             //РЕЗЬБА-НАРУЖНАЯ
          if (Spindle_Dir == CW) {
            Thread_Ext_Right();
          } else {
            Thread_Ext_Left();
          }
          break;

        case Sub_Mode_Thread_Int:                             //РЕЗЬБА-ВНУТРЕННЯЯ
          if (Spindle_Dir == CW) {
            Thread_Int_Right();
          } else {
            Thread_Int_Left();
          }
          break;

        case Sub_Mode_Thread_Man:                          //РЕЗЬБА-РУЧНОЙ РЕЖИМ
          //default:
          if (err_1_flag || err_2_flag) break;
          if (Spindle_Dir == CW)
          {
            //OLD
            /*
              if (!Button_Rapid)
              {
              Limit_Pos = Limit_Pos_Min;
              } else {
              Limit_Pos = Limit_Pos_Right + Brake_Compens;
              }
            */
            //NEW
            if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
            {
              Limit_Pos = Limit_Pos_Right + Brake_Compens;
            } else {                      //Иначе нажата кнопка "Быстрая подача"
              Limit_Pos = Limit_Pos_Min;
            }
            //---
            Thread_Right(c_flag, d_flag);
          } else {
            Thread_Left(c_flag, d_flag);
          }
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //СИНХРОННАЯ ПОДАЧА
    case Mode_Feed:
      switch (Sub_Mode_Feed)
      {
        case Sub_Mode_Feed_Ext:                       //СИНХРОННАЯ ПОДАЧА-НАРУЖНАЯ
          Feed_Ext_Right();
          break;

        case Sub_Mode_Feed_Int:                       //СИНХРОННАЯ ПОДАЧА-ВНУТРЕННЯЯ
          Feed_Int_Right();
          break;

        case Sub_Mode_Feed_Man:                       //СИНХРОННАЯ ПОДАЧА-РУЧНОЙ РЕЖИМ
          //default:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          //NEW
          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR5A == max_OCR5A)
            {
              Z_NEED_RUN_RAPID_FLAG = OFF;
              if (!Z_WORKING_RAPID_FLAG)
              {
                if (Read_Z_Ena_State == false) Motor_Z_Enable();
                //-Z_NEED_RUN_FEED_FLAG = ON;                                     //СМУЩАЕТ включение флага до вызова функции NEW_...
                //Feed_Right(a_flag, b_flag);
                NEW_Feed_Right(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_Z_Pos > (Limit_Pos_Right + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
              Z_NEED_RUN_FEED_FLAG = OFF;
              if (!Z_WORKING_FEED_FLAG)
              {
                //Rapid_Feed_Right(a_flag, b_flag);
                NEW_Feed_Right(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
              }
              }
            */
            //NEW START
            if (!Z_WORKING_FEED_FLAG && !Z_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_Z_Pos > (Limit_Pos_Right + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_Feed_Right(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
              }
            }
            //---
          }
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //АСИНХРОННАЯ ПОДАЧА
    case Mode_aFeed:
      switch (Sub_Mode_aFeed)
      {
        case Sub_Mode_aFeed_Ext:                            //АСИНХРОННАЯ ПОДАЧА-НАРУЖНАЯ
          NEW_aFeed_Ext_Right();
          break;

        case Sub_Mode_aFeed_Int:                            //АСИНХРОННАЯ ПОДАЧА-ВНУТРЕННЯЯ
          NEW_aFeed_Int_Right();
          break;

        case Sub_Mode_aFeed_Man:                          //АСИНХРОННАЯ ПОДАЧА-РУЧНОЙ РЕЖИМ
          //default:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          //NEW
          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR4A == max_OCR4A)
            {
              Z_NEED_RUN_RAPID_FLAG = OFF;
              if (!Z_WORKING_RAPID_FLAG)
              {
                if (Read_Z_Ena_State == false) Motor_Z_Enable();
                //-Z_NEED_RUN_FEED_FLAG = ON;                                     //СМУЩАЕТ включение флага до вызова функции NEW_...
                //aFeed_Right(a_flag, b_flag);
                NEW_aFeed_Right(a_flag, b_flag, FORCE_SLOW);      //ОБЫЧНАЯ АСИНХРОННАЯ ПОДАЧА
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_Z_Pos > (Limit_Pos_Right + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
              Z_NEED_RUN_FEED_FLAG = OFF;
              if (!Z_WORKING_FEED_FLAG)
              {
                //Rapid_Feed_Right(a_flag, b_flag);
                NEW_aFeed_Right(a_flag, b_flag, FORCE_RAPID);      //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
              }
              }
            */
            //NEW START
            if (!Z_WORKING_FEED_FLAG && !Z_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_Z_Pos > (Limit_Pos_Right + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_aFeed_Right(a_flag, b_flag, FORCE_RAPID);      //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
              }
            }
            //---
          }
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //КОНУСА
    case Mode_Cone_L:
    case Mode_Cone_R:
      //NEW
      switch (Sub_Mode_Cone)
      {
        case Sub_Mode_Cone_Man:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          //NEW
          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR4A == max_OCR4A)
            {
              Z_NEED_RUN_RAPID_FLAG = OFF;
              if (!Z_WORKING_RAPID_FLAG)
              {
                //Cone_Right(a_flag, b_flag);
                NEW_Cone_Right(a_flag, b_flag, FORCE_SLOW);     //ОБЫЧНАЯ ПОДАЧА
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_Z_Pos > (Limit_Pos_Right + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
              Z_NEED_RUN_FEED_FLAG = OFF;
              if (!Z_WORKING_FEED_FLAG)
              {
                //Rapid_Cone_Right(a_flag, b_flag);
                NEW_Cone_Right(a_flag, b_flag, FORCE_RAPID);     //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
              }
              }
            */
            //NEW START
            if (!Z_WORKING_FEED_FLAG && !Z_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_Z_Pos > (Limit_Pos_Right + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_Cone_Right(a_flag, b_flag, FORCE_RAPID);     //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
              }
            }
            //---
          }
          break;
        case Sub_Mode_Cone_Int:
          NEW_Cone_Int_Right();
          break;

        case Sub_Mode_Cone_Ext:
          NEW_Cone_Ext_Right();
          break;
          //NEW
      }
      break;
      //---
      //------------------------------------------------------------------------------------------------------------------------------------------------------------
  }
}

// ********** Обработчик Джойстик Вверх **********
//Opti IF-ELSE заменён на SWITCH (Выигрыш всего 2 байта). Часть суб-режимов FORCE_SLOW переведена на default. Читаемость кода, как по мне, стала лучше
void Joy_UpPressed()
{
  flag_j = ON;

  //Если переключатель ручного энкодера в активной позиции - взводим флаг ошибки3
  if (hand_Z == ON || hand_X == ON)
  {
    err_3_flag = true;
  }
  //Принудительно выключаем ручной энкодер
  Disa_INT_Hcoder();                  //Выключаем прерывание от ручного энкодера
  Disable_INT_OCR3A();                //Выключаем обработчик ручного энкодера по оси Z
  Disable_INT_OCR3B();                //Выключаем обработчик ручного энкодера по оси X
  hand_Z = OFF;                       //Гасим флаг управления оси Z от ручного энкодера
  hand_X = OFF;                       //Гасим флаг управления оси X от ручного энкодера
  Hand_Count = 0;                     //Сброс на 0 переменных ручного энкодера
  Hand_Count_New = 0;                 //Сброс на 0 переменных ручного энкодера
  Hand_Count_Old = 0;                 //Сброс на 0 переменных ручного энкодера
  Hand_Z_Pos = 0;                     //Сброс на 0 переменных ручного энкодера
  Hand_X_Pos = 0;                     //Сброс на 0 переменных ручного энкодера
  //Выходим из функции при наличии ошибки3
  if (err_3_flag == true)
  {
    return;
  }

  switch (Mode)
  {
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //РЕЗЬБА
    case Mode_Thread:
      switch (Sub_Mode_Thread)
      {
        case Sub_Mode_Thread_Man:                   //РЕЗЬБА-РУЧНОЙ РЕЖИМ
          if (err_1_flag || err_2_flag) break;
          if (Spindle_Dir == CW) {
            Thread_Front(c_flag, d_flag);
          } else {
            Thread_Rear(c_flag, d_flag);
          }
          //default:
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //СИНХРОННАЯ ПОДАЧА
    case Mode_Feed:
      switch (Sub_Mode_Feed)
      {
        case Sub_Mode_Feed_Ext:                       //СИНХРОННАЯ ПОДАЧА-НАРУЖНАЯ
          Feed_Ext_Front();
          break;

        case Sub_Mode_Feed_Int:                       //СИНХРОННАЯ ПОДАЧА-ВНУТРЕННЯЯ
          Feed_Int_Front();
          break;

        case Sub_Mode_Feed_Man:                     //СИНХРОННАЯ ПОДАЧА-РУЧНОЙ РЕЖИМ
          //default:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR5A == max_OCR5A)
            {
              X_NEED_RUN_RAPID_FLAG = OFF;
              if (!X_WORKING_RAPID_FLAG)
              {
                if (Read_X_Ena_State == false) Motor_X_Enable();
                X_NEED_RUN_FEED_FLAG = ON;
                //Feed_Front(a_flag, b_flag);
                NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
              X_NEED_RUN_FEED_FLAG = OFF;
              if (!X_WORKING_FEED_FLAG)
              {
                //Rapid_Feed_Front(a_flag, b_flag);
                NEW_Feed_Front(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
              }
              }
            */
            //NEW START
            if (!X_WORKING_FEED_FLAG && !X_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_Feed_Front(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
              }
            }
            //---
          }
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //АСИНХРОННАЯ ПОДАЧА
    case Mode_aFeed:
      switch (Sub_Mode_aFeed)
      {
        case Sub_Mode_aFeed_Ext:
          NEW_aFeed_Ext_Front();
          break;

        case Sub_Mode_aFeed_Int:
          NEW_aFeed_Int_Front();                      //ЗАГЛУШКА-ПУСТЫШКА
          break;

        case Sub_Mode_aFeed_Man:                      //АСИНХРОННАЯ ПОДАЧА-РУЧНОЙ РЕЖИМ
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR4A == max_OCR4A)
            {
              X_NEED_RUN_RAPID_FLAG = OFF;
              if (!X_WORKING_RAPID_FLAG)
              {
                if (Read_X_Ena_State == false) Motor_X_Enable();
                X_NEED_RUN_FEED_FLAG = ON;
                //aFeed_Front(a_flag, b_flag);
                NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);      //ОБЫЧНАЯ АСИНХРОННАЯ ПОДАЧА
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
              X_NEED_RUN_FEED_FLAG = OFF;
              if (!X_WORKING_FEED_FLAG)
              {
                //Rapid_Feed_Front(a_flag, b_flag);
                NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);      //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
              }
              }
            */
            //NEW START
            if (!X_WORKING_FEED_FLAG && !X_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);      //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
              }
            }
            //---
          }
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //КОНУС (ЛЕВЫЙ)
    case Mode_Cone_L:
      if (err_1_flag || err_2_flag) break;

      //NEW3 RAPID BUTTON PRESS START
      //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
      if (SpeedMode != MANUAL) break;

      //NEW
      if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
      {
        //if (OCR5A == max_OCR5A)
        if (OCR4A == max_OCR4A)
        {
          X_NEED_RUN_RAPID_FLAG = OFF;
          if (!X_WORKING_RAPID_FLAG)
          {
            if (Read_X_Ena_State == false) Motor_X_Enable();
            X_NEED_RUN_FEED_FLAG = ON;
            //Feed_Front(a_flag, b_flag);
            //NEW_Feed_Front(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
            NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
          }
        }
      } else {                      //Иначе нажата кнопка "Быстрая подача"
        //OLD START
        /*
          if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
          {
          X_NEED_RUN_FEED_FLAG = OFF;
          if (!X_WORKING_FEED_FLAG)
          {
            //Rapid_Feed_Front(a_flag, b_flag);
            //NEW_Feed_Front(a_flag, b_flag, true);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
            NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
          }
          }
        */
        //NEW START
        if (!X_WORKING_FEED_FLAG && !X_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
        {
          if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
          {
            NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
          }
        }
        //---
      }
      //---
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //КОНУС (ПРАВЫЙ)
    case Mode_Cone_R:
      if (err_1_flag || err_2_flag) break;

      //NEW3 RAPID BUTTON PRESS START
      //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
      if (SpeedMode != MANUAL) break;

      //NEW
      if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
      {
        //if (OCR5A == max_OCR5A)
        if (OCR4A == max_OCR4A)
        {
          X_NEED_RUN_RAPID_FLAG = OFF;
          if (!X_WORKING_RAPID_FLAG)
          {
            if (Read_X_Ena_State == false) Motor_X_Enable();
            X_NEED_RUN_FEED_FLAG = ON;
            //Feed_Front(a_flag, b_flag);
            //NEW_Feed_Front(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
            NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
          }
        }
      } else {                      //Иначе нажата кнопка "Быстрая подача"
        //OLD START
        /*
          if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
          {
          X_NEED_RUN_FEED_FLAG = OFF;
          if (!X_WORKING_FEED_FLAG)
          {
            //Rapid_Feed_Front(a_flag, b_flag);
            //NEW_Feed_Front(a_flag, b_flag, true);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
            NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
          }
          }
        */
        //NEW START
        if (!X_WORKING_FEED_FLAG && !X_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
        {
          if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
          {
            NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
          }
        }
        //---
      }
      //---
      break;
      //------------------------------------------------------------------------------------------------------------------------------------------------------------
  }
}

// ********** Обработчик Джойстик Вниз **********
//Opti
void Joy_DownPressed()
{
  flag_j = ON;

  //Если переключатель ручного энкодера в активной позиции - взводим флаг ошибки3
  if (hand_Z == ON || hand_X == ON)
  {
    err_3_flag = true;
  }
  //Принудительно выключаем ручной энкодер
  Disa_INT_Hcoder();                  //Выключаем прерывание от ручного энкодера
  Disable_INT_OCR3A();                //Выключаем обработчик ручного энкодера по оси Z
  Disable_INT_OCR3B();                //Выключаем обработчик ручного энкодера по оси X
  hand_Z = OFF;                       //Гасим флаг управления оси Z от ручного энкодера
  hand_X = OFF;                       //Гасим флаг управления оси X от ручного энкодера
  Hand_Count = 0;                     //Сброс на 0 переменных ручного энкодера
  Hand_Count_New = 0;                 //Сброс на 0 переменных ручного энкодера
  Hand_Count_Old = 0;                 //Сброс на 0 переменных ручного энкодера
  Hand_Z_Pos = 0;                     //Сброс на 0 переменных ручного энкодера
  Hand_X_Pos = 0;                     //Сброс на 0 переменных ручного энкодера
  //Выходим из функции при наличии ошибки3
  if (err_3_flag == true)
  {
    return;
  }

  switch (Mode)
  {
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    //РЕЗЬБА
    case Mode_Thread:
      /*
        switch (Sub_Mode_Thread)
        {
         case Sub_Mode_Thread_Man:
           if (err_1_flag || err_2_flag) break;
           if (Spindle_Dir == CW) {
             Thread_Rear(c_flag, d_flag);
           } else {
             Thread_Front(c_flag, d_flag);
           }
           break;
        }
        break;
      */
      if (Sub_Mode_Thread == Sub_Mode_Thread_Man && !err_1_flag && !err_2_flag)
      {
        if (Spindle_Dir == CW) {
          Thread_Rear(c_flag, d_flag);
        } else {
          Thread_Front(c_flag, d_flag);
        }
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    case Mode_Feed:
      switch (Sub_Mode_Feed)
      {
        case Sub_Mode_Feed_Ext:
          Feed_Ext_Rear();
          break;

        case Sub_Mode_Feed_Int:
          Feed_Int_Rear();                //ЗАГЛУШКА-ПУСТЫШКА
          break;

        case Sub_Mode_Feed_Man:
          //default:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          //NEW
          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR5A == max_OCR5A)
            {
              X_NEED_RUN_RAPID_FLAG = OFF;
              if (!X_WORKING_RAPID_FLAG)
              {
                if (Read_X_Ena_State == false) Motor_X_Enable();
                X_NEED_RUN_FEED_FLAG = ON;
                //Feed_Rear(a_flag, b_flag);
                NEW_Feed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
              X_NEED_RUN_FEED_FLAG = OFF;
              if (!X_WORKING_FEED_FLAG)
              {
                //Rapid_Feed_Rear(a_flag, b_flag);
                NEW_Feed_Rear(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
              }
              }
            */
            //NEW START
            if (!X_WORKING_FEED_FLAG && !X_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_Feed_Rear(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
              }
            }
            //---
          }
          //---
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    case Mode_aFeed:
      switch (Sub_Mode_aFeed)
      {
        case Sub_Mode_aFeed_Ext:
          NEW_aFeed_Ext_Rear();
          break;

        case Sub_Mode_aFeed_Int:
          NEW_aFeed_Int_Rear();     //ЗАГЛУШКА-ПУСТЫШКА
          break;

        case Sub_Mode_aFeed_Man:
          if (err_1_flag || err_2_flag) break;

          //NEW3 RAPID BUTTON PRESS START
          //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
          if (SpeedMode != MANUAL) break;

          //NEW
          if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
          {
            if (OCR4A == max_OCR4A)
            {
              X_NEED_RUN_RAPID_FLAG = OFF;
              if (!X_WORKING_RAPID_FLAG)
              {
                if (Read_X_Ena_State == false) Motor_X_Enable();
                X_NEED_RUN_FEED_FLAG = ON;
                //aFeed_Rear(a_flag, b_flag);
                NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);      //ОБЫЧНАЯ АСИНХРОННАЯ ПОДАЧА
              }
            }
          } else {                      //Иначе нажата кнопка "Быстрая подача"
            //OLD START
            /*
              if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
              X_NEED_RUN_FEED_FLAG = OFF;
              if (!X_WORKING_FEED_FLAG)
              {
                //Rapid_Feed_Rear(a_flag, b_flag);
                NEW_aFeed_Rear(a_flag, b_flag, FORCE_RAPID);      //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
              }
              }
            */
            //NEW START
            if (!X_WORKING_FEED_FLAG && !X_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
            {
              if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
              {
                NEW_aFeed_Rear(a_flag, b_flag, FORCE_RAPID);      //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
              }
            }
            //---
          }
          //---
          break;
      }
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    case Mode_Cone_L:
      if (err_1_flag || err_2_flag) break;

      //NEW3 RAPID BUTTON PRESS START
      //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
      if (SpeedMode != MANUAL) break;

      //NEW
      if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
      {
        if (OCR4A == max_OCR4A)
        {
          X_NEED_RUN_RAPID_FLAG = OFF;
          if (!X_WORKING_RAPID_FLAG)
          {
            if (Read_X_Ena_State == false) Motor_X_Enable();
            X_NEED_RUN_FEED_FLAG = ON;
            //Feed_Rear(a_flag, b_flag);
            //NEW_Feed_Rear(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
            NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ АСИНХРОННОЙ ПОДАЧИ
          }
        }
      } else {                      //Иначе нажата кнопка "Быстрая подача"
        //OLD START
        /*
          if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
          {
          X_NEED_RUN_FEED_FLAG = OFF;
          if (!X_WORKING_FEED_FLAG)
          {
            //Rapid_Feed_Rear(a_flag, b_flag);
            //NEW_Feed_Rear(a_flag, b_flag, true);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
            NEW_aFeed_Rear(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
          }
          }
        */
        //NEW START
        if (!X_WORKING_FEED_FLAG && !X_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
        {
          if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
          {
            NEW_aFeed_Rear(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
          }
        }
        //---
      }
      //---
      break;
    //------------------------------------------------------------------------------------------------------------------------------------------------------------
    case Mode_Cone_R:
      if (err_1_flag || err_2_flag) break;

      //NEW3 RAPID BUTTON PRESS START
      //Общий смысл: если мотор уже в режиме подача или быстрая подача, то кнопка Rapid не обрабатывается - не происходит переключения ОБЫЧНАЯ ПОДАЧА - БЫСТРАЯ ПОДАЧА во время работы
      if (SpeedMode != MANUAL) break;

      //NEW
      if (Button_Rapid_Not_Pressed) //Сначала проверка условия на кнопку ускоренной подачи. Истинно, если кнопка "Быстрая подача" не нажата.
      {
        if (OCR4A == max_OCR4A)
        {
          X_NEED_RUN_RAPID_FLAG = OFF;
          if (!X_WORKING_RAPID_FLAG)
          {
            if (Read_X_Ena_State == false) Motor_X_Enable();
            X_NEED_RUN_FEED_FLAG = ON;
            //Feed_Rear(a_flag, b_flag);
            //NEW_Feed_Rear(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
            NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ АСИНХРОННОЙ ПОДАЧИ
          }
        }
      } else {                      //Иначе нажата кнопка "Быстрая подача"
        //OLD START
        /*
          if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
          {
          X_NEED_RUN_FEED_FLAG = OFF;
          if (!X_WORKING_FEED_FLAG)
          {
            //Rapid_Feed_Rear(a_flag, b_flag);
            //NEW_Feed_Rear(a_flag, b_flag, true);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
            NEW_aFeed_Rear(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
          }
          }
        */
        //NEW START
        if (!X_WORKING_FEED_FLAG && !X_NEED_RUN_FEED_FLAG) //Если флаги обычной подачи показывают полный СТОП
        {
          if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
          {
            NEW_aFeed_Rear(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ АСИНХРОННОЙ ПОДАЧИ
          }
        }
        //---
      }
      //---
      break;
      //------------------------------------------------------------------------------------------------------------------------------------------------------------
  }
}

// ********** Обработчик Джойстик в нейтрали **********
void Joy_NoPressed()
{
  //NEW Многопроходный КОНУС
  Complete_flag = false;
  Cone_qStep = 0;

  //---

  if (flag_j == ON)
  {
#ifdef _DEBUG_MENU
    Serial.print("Joy_NoPressed() + flag_j == ON\n\r");
#endif

    if (!Z_WORKING_FEED_FLAG && !Z_WORKING_RAPID_FLAG && !X_WORKING_FEED_FLAG && !X_WORKING_RAPID_FLAG)
    {
      flag_j = OFF;

      //NEW
      SpeedMode = MANUAL;


      //Disable_INT_OCR4A();  //test
      //Disable_INT_OCR4B();  //test
      //Disable_INT_OCR4C();  //test

#ifdef _DEBUG_MENU
      Serial.print("1)Motor_Z_Pos="); Serial.print(Motor_Z_Pos);
#endif

      Motor_Z_Pos = ((Motor_Z_Pos + McSTEP_Z / 2) & ~(McSTEP_Z - 1));

#ifdef _DEBUG_MENU
      Serial.print(" 2)Motor_Z_Pos="); Serial.print(Motor_Z_Pos); Serial.print("\n\r");
#endif

      Motor_X_Pos = ((Motor_X_Pos + McSTEP_X / 2) & ~(McSTEP_X - 1));
      Null_Z_Pos = Motor_Z_Pos;
      Null_X_Pos = Motor_X_Pos;

      Motor_Z_RemovePulse();
      Motor_X_RemovePulse();
      Ks_Count = 0;
      Km_Count = 0;
      Cs_Count = 0;
      Cm_Count = 0;
      Repeat_Count = 0;
      a_flag = false;
      c_flag = false;
      d_flag = false;
      cycle_flag = false;
      Pass_Nr = 1;
      OCR5A = max_OCR5A;
      OCR4A = max_OCR4A;

      //OCR4B = max_OCR4B;  //new
      //OCR4C = max_OCR4C;  //new


      OCR2A = MIN_RAPID_MOTION;

      //test Отключаем функцию выключения моторов на стопе - они остаются включёнными
      /*
        if (!flag_hand_Z)
        {
        //Motor_Z_Disable();
        //Serial.print("flag_hand_Z=false!!! Motor_Z_Disable() - OFF_Z\n");   //test
        }
        if (!flag_hand_X)
        {
        //Motor_X_Disable();
        //Serial.print("flag_hand_X=false!!! Motor_X_Disable() - OFF_X\n");   //test
        }
      */
    }
  }

  Joy_Z_flag = OFF;
  Joy_X_flag = OFF;
  Z_NEED_RUN_FEED_FLAG = OFF;
  X_NEED_RUN_FEED_FLAG = OFF;
  Z_NEED_RUN_RAPID_FLAG = OFF;
  X_NEED_RUN_RAPID_FLAG = OFF;
  b_flag = false;

  err_3_flag = false;   //new


  //Если мотор Z  не находятся в работе в режимах подачи или быстрой подачи - т.е. на нём нет импульсов STEP...
  if (!Z_WORKING_FEED_FLAG && !Z_WORKING_RAPID_FLAG)
  {
    if (hand_Z == OFF)
    {
      if (flag_hand_Z == ON)
      {
        hand_Z = ON;
      }
    }
    H_Coder();          //Функция-Обработчик ручного энкодера в файле HandCoder.ino
  }

  //Если мотор X  не находятся в работе в режимах подачи или быстрой подачи - т.е. на нём нет импульсов STEP...
  if (!X_WORKING_FEED_FLAG && !X_WORKING_RAPID_FLAG)           //Это не взаимоисключающие случаи? (!Z_WORKING_FEED_FLAG && !Z_WORKING_RAPID_FLAG) и (!X_WORKING_FEED_FLAG && !X_WORKING_RAPID_FLAG) ? может "else if" использовать?
  {
    if (hand_X == OFF)
    {
      if (flag_hand_X == ON)
      {
        hand_X = ON;
      }
    }
    H_Coder();          //Функция-Обработчик ручного энкодера в файле HandCoder.ino
  }

  //Opti Пустой код
  /*
    if (Mode == Mode_Thread)
    {
    //
    if (Sub_Mode_Thread != Sub_Mode_Thread_Man)
    {
      //
    }
    }

    if (Mode == Mode_Feed || Mode == Mode_aFeed)
    {
    //
    if (Sub_Mode_Feed != Sub_Mode_Feed_Man)
    {
      //
    }
    }
  */

  if (Mode == Mode_Cone_L || Mode == Mode_Cone_R)
  {
    //NEW Многопроходный КОНУС
    Pass_Nr = 1;
    //---
    if (!Z_WORKING_FEED_FLAG && !Z_WORKING_RAPID_FLAG)
    {
      X_WORKING_RAPID_FLAG = OFF;
      X_WORKING_FEED_FLAG = OFF;
      //NEW Многопроходный КОНУС
      cycle_flag = false;
      Motor_X_Pos = Null_X_Pos;
      //---
    }
  }

  //OLD
  /*
    if ((Mode == Mode_Thread && Sub_Mode_Thread == Sub_Mode_Thread_Man) ||
      (Mode == Mode_Feed && Sub_Mode_Feed == Sub_Mode_Feed_Man) ||
      (Mode == Mode_aFeed && Sub_Mode_aFeed == Sub_Mode_aFeed_Man) ||
      (Mode == Mode_Cone_L && Sub_Mode_Cone == Sub_Mode_Cone_Man) ||
      (Mode == Mode_Cone_R && Sub_Mode_Cone == Sub_Mode_Cone_Man) ||
      (Mode == Mode_Sphere && Sub_Mode_Sphere == Sub_Mode_Sphere_Man) ||
      (Mode == Mode_Divider))
    {
    //
    }
    else
    {
    Disa_INT_Hcoder();
    }
  */
  //Opti. Выигрыш 24 байта.
  switch (Mode)
  {
    case Mode_Thread:
      if (Sub_Mode_Thread == Sub_Mode_Thread_Man) return;
      break;
    case Mode_Feed:
      if (Sub_Mode_Feed == Sub_Mode_Feed_Man) return;
      break;
    case Mode_aFeed:
      if (Sub_Mode_aFeed == Sub_Mode_aFeed_Man) return;
      break;
    case Mode_Cone_L:
    case Mode_Cone_R:
      if (Sub_Mode_Cone == Sub_Mode_Cone_Man) return;
      break;
    case Mode_Sphere:
      if (Sub_Mode_Sphere == Sub_Mode_Sphere_Man) return;
      break;
    case Mode_Divider:
      return;
    default:
      break;
  }
  Disa_INT_Hcoder();
  //---
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработка Переключателя Режима ********** //////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NEW Opti
void Reset_Hand_NullPos()
{
  Hand_Count = 0;
  Hand_Count_New = 0;
  Hand_Count_Old = 0;
  Hand_Z_Pos = 0;
  Hand_X_Pos = 0;
  Null_Z_Pos = Motor_Z_Pos;
  Null_X_Pos = Motor_X_Pos;
}

//NEW Opti
void Reset_Step_rapid()
{
  Z_WORKING_FEED_FLAG = OFF;
  X_WORKING_FEED_FLAG = OFF;
  Z_WORKING_RAPID_FLAG = OFF;
  X_WORKING_RAPID_FLAG = OFF;
}

//NEW Opti
void Reset_Ks_Km_Repeat()
{
  Ks_Count = 0;
  Km_Count = 0;
  Repeat_Count = 0;
}

//NEW
void Motors_OFF()
{
  Motor_Z_Disable();
  Motor_X_Disable();
}

void Switch_Thread()
{
  //OLD
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  Ena_INT_Thrd();
  Mode = Mode_Thread;

  //OLD
  //Z_WORKING_FEED_FLAG = OFF;
  //X_WORKING_FEED_FLAG = OFF;
  //Z_WORKING_RAPID_FLAG = OFF;
  //X_WORKING_RAPID_FLAG = OFF;
  //Opti
  Reset_Step_rapid();     //-> Z_WORKING_FEED_FLAG = OFF; X_WORKING_FEED_FLAG = OFF; Z_WORKING_RAPID_FLAG = OFF; X_WORKING_RAPID_FLAG = OFF;

  //OLD
  //Ks_Count = 0;
  //Km_Count = 0;
  //Repeat_Count = 0;
  //Opti
  Reset_Ks_Km_Repeat();     //-> Ks_Count = 0; Km_Count = 0; Repeat_Count = 0;

  Print();

  Motors_OFF();   //test Моторы в выключенное состояние
}

void Switch_Feed()
{
  //OLD
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  Ena_INT_Z_Feed();
  Mode = Mode_Feed;

  //OLD
  //Z_WORKING_FEED_FLAG = OFF;
  //X_WORKING_FEED_FLAG = OFF;
  //Z_WORKING_RAPID_FLAG = OFF;
  //X_WORKING_RAPID_FLAG = OFF;
  //Opti
  Reset_Step_rapid();     //-> Z_WORKING_FEED_FLAG = OFF; X_WORKING_FEED_FLAG = OFF; Z_WORKING_RAPID_FLAG = OFF; X_WORKING_RAPID_FLAG = OFF;

  //OLD
  //Ks_Count = 0;
  //Km_Count = 0;
  //Repeat_Count = 0;
  //Opti
  Reset_Ks_Km_Repeat();     //-> Ks_Count = 0; Km_Count = 0; Repeat_Count = 0;

  Pass_Total = 1;

  Ap = 0; //new

  Print();

  Motors_OFF();   //test Моторы в выключенное состояние
}

void Switch_aFeed()
{
  //OLD
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  Mode = Mode_aFeed;

  //OLD
  //Z_WORKING_FEED_FLAG = OFF;
  //X_WORKING_FEED_FLAG = OFF;
  //Z_WORKING_RAPID_FLAG = OFF;
  //X_WORKING_RAPID_FLAG = OFF;
  //Opti
  Reset_Step_rapid();     //-> Z_WORKING_FEED_FLAG = OFF; X_WORKING_FEED_FLAG = OFF; Z_WORKING_RAPID_FLAG = OFF; X_WORKING_RAPID_FLAG = OFF;

  Pass_Total = 1;

  //Многопроходный aFeed
  Enc_Pos = 0;
  Ap = 0;
  //-

  Print();

  Motors_OFF();   //test Моторы в выключенное состояние
}

void Switch_Cone_L()
{
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  //Ena_INT_Z_Feed();
  //Ena_INT_Z_aFeed();
  //Disable_INT_ALL();

  Mode = Mode_Cone_L;

  //OLD
  //Z_WORKING_FEED_FLAG = OFF;
  //X_WORKING_FEED_FLAG = OFF;
  //Z_WORKING_RAPID_FLAG = OFF;
  //X_WORKING_RAPID_FLAG = OFF;
  //Opti
  Reset_Step_rapid();     //-> Z_WORKING_FEED_FLAG = OFF; X_WORKING_FEED_FLAG = OFF; Z_WORKING_RAPID_FLAG = OFF; X_WORKING_RAPID_FLAG = OFF;

  //OLD
  //Ks_Count = 0;
  //Km_Count = 0;
  //Repeat_Count = 0;
  //Opti
  Reset_Ks_Km_Repeat();     //-> Ks_Count = 0; Km_Count = 0; Repeat_Count = 0;

  Pass_Total = 1;

  //NEW Многопроходный КОНУС
  Cone_qStep = 0;
  Ap = 0;
  //---

  Print();

  Motors_OFF();   //test Моторы в выключенное состояние
}

void Switch_Cone_R()
{
  //OLD
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  //Ena_INT_Z_Feed();
  //  Ena_INT_Z_aFeed();
  //Disable_INT_ALL();

  Mode = Mode_Cone_R;

  //OLD
  //Z_WORKING_FEED_FLAG = OFF;
  //X_WORKING_FEED_FLAG = OFF;
  //Z_WORKING_RAPID_FLAG = OFF;
  //X_WORKING_RAPID_FLAG = OFF;
  //Opti
  Reset_Step_rapid();     //-> Z_WORKING_FEED_FLAG = OFF; X_WORKING_FEED_FLAG = OFF; Z_WORKING_RAPID_FLAG = OFF; X_WORKING_RAPID_FLAG = OFF;

  //OLD
  //Ks_Count = 0;
  //Km_Count = 0;
  //Repeat_Count = 0;
  //Opti
  Reset_Ks_Km_Repeat();     //-> Ks_Count = 0; Km_Count = 0; Repeat_Count = 0;

  Pass_Total = 1;

  //NEW Многопроходный КОНУС
  Cone_qStep = 0;
  Ap = 0;
  //---

  Print();

  Motors_OFF();   //test Моторы в выключенное состояние
}

void Switch_Reserve()
{
  //OLD
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  Mode = Mode_Reserve;

  //NEW
  Ena_INT_TACHO();



  Print();

  Motors_OFF();   //test Моторы в выключенное состояние
}

void Switch_Sphere()
{
  //OLD
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  //   Ena_INT_Z_Feed(); //
  Mode = Mode_Sphere;

  //OLD
  //Z_WORKING_FEED_FLAG = OFF;
  //X_WORKING_FEED_FLAG = OFF;
  //Z_WORKING_RAPID_FLAG = OFF;
  //X_WORKING_RAPID_FLAG = OFF;
  //Opti
  Reset_Step_rapid();     //-> Z_WORKING_FEED_FLAG = OFF; X_WORKING_FEED_FLAG = OFF; Z_WORKING_RAPID_FLAG = OFF; X_WORKING_RAPID_FLAG = OFF;

  //OLD
  //Ks_Count = 0;
  //Km_Count = 0;
  //Repeat_Count = 0;
  //Opti
  Reset_Ks_Km_Repeat();     //-> Ks_Count = 0; Km_Count = 0; Repeat_Count = 0;

  Pass_Total = 1;
  Print();

  Motors_OFF();   //test Моторы в выключенное состояние
}

void Switch_Divider()
{
  //OLD
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti Выигрыш 140 байт?
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  Ena_INT_Thrd();
  Mode = Mode_Divider;

  //OLD
  //Z_WORKING_FEED_FLAG = OFF;
  //X_WORKING_FEED_FLAG = OFF;
  //Z_WORKING_RAPID_FLAG = OFF;
  //X_WORKING_RAPID_FLAG = OFF;
  //Opti Выигрыш 12 байт
  Reset_Step_rapid();     //-> Z_WORKING_FEED_FLAG = OFF; X_WORKING_FEED_FLAG = OFF; Z_WORKING_RAPID_FLAG = OFF; X_WORKING_RAPID_FLAG = OFF;

  //OLD
  //Ks_Count = 0;
  //Km_Count = 0;
  //Repeat_Count = 0;
  //Opti Выигрыш 16 байт
  Reset_Ks_Km_Repeat();     //-> Ks_Count = 0; Km_Count = 0; Repeat_Count = 0;

  Motors_OFF();   //test Моторы в выключенное состояние
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработка Переключателя Подрежима ********** ///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Switch_Int()
{
  switch (Mode)
  {
    case Mode_Thread:
    case Mode_Feed:
    case Mode_aFeed:
    case Mode_Cone_L:
    case Mode_Cone_R:
      if ((limit_Left_flag == ON && limit_Right_flag == ON) ||
          (limit_Front_flag == ON && limit_Rear_flag == ON))
      {
        Sub_Mode_Thread = Sub_Mode_Thread_Int;
        Sub_Mode_Feed = Sub_Mode_Feed_Int;
        Sub_Mode_aFeed = Sub_Mode_aFeed_Int;
        Sub_Mode_Cone = Sub_Mode_Cone_Int;
        err_1_flag = false;
        Z_WORKING_FEED_FLAG = OFF;
        X_WORKING_FEED_FLAG = OFF;
        Z_WORKING_RAPID_FLAG = OFF;
        X_WORKING_RAPID_FLAG = OFF;
        Ks_Count = 0;
        Km_Count = 0;
        Repeat_Count = 0;

        if (Motor_Z_Pos == Limit_Pos_Right ||
            Motor_Z_Pos == Limit_Pos_Left ||
            Motor_X_Pos == Limit_Pos_Rear ||
            Motor_X_Pos == Limit_Pos_Front)
        {
          err_2_flag = false;
        }
        else
        {
          Sub_Mode_Thread = Sub_Mode_Thread_Man;
          Sub_Mode_Feed = Sub_Mode_Feed_Man;
          Sub_Mode_aFeed = Sub_Mode_aFeed_Man;
          Sub_Mode_Cone = Sub_Mode_Cone_Man;
          err_2_flag = true;
          Beep_Error();
        }
      }
      else
      {
        Sub_Mode_Thread = Sub_Mode_Thread_Man;
        Sub_Mode_Feed = Sub_Mode_Feed_Man;
        Sub_Mode_aFeed = Sub_Mode_aFeed_Man;
        Sub_Mode_Cone = Sub_Mode_Cone_Man;
        err_1_flag = true;
        Beep_Error();
      }
      Print();
      break;

    case Mode_Sphere:  /////////////////////////////////////////////////////////////////////////////////////
      if (limit_Right_flag == ON && limit_Rear_flag == ON)
      {
        Sub_Mode_Sphere = Sub_Mode_Sphere_Int;
        err_1_flag = false;
        Z_WORKING_FEED_FLAG = OFF;
        X_WORKING_FEED_FLAG = OFF;
        Ks_Count = 0;
        Km_Count = 0;
        Repeat_Count = 0;

        if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear)
        {
          err_2_flag = false;
        }
        else
        {
          Sub_Mode_Sphere = Sub_Mode_Sphere_Man;
          err_2_flag = true;
          Beep_Error();
        }
      }
      else
      {
        Sub_Mode_Sphere = Sub_Mode_Sphere_Man;
        err_1_flag = true;
        Beep_Error();
      }
      Print();
      break;
  }
}

//Opti небольшая оптимизация switch
void Switch_Man()
{
  //OLD
  /*
    switch (Mode)
    {
    case Mode_Thread:
    case Mode_Feed:
    case Mode_aFeed:
    case Mode_Cone_L:
    case Mode_Cone_R:
    case Mode_Sphere:
      Sub_Mode_Thread = Sub_Mode_Thread_Man;
      Sub_Mode_Feed = Sub_Mode_Feed_Man;
      Sub_Mode_aFeed = Sub_Mode_aFeed_Man;
      Sub_Mode_Cone = Sub_Mode_Cone_Man;
      Sub_Mode_Sphere = Sub_Mode_Sphere_Man;
      err_1_flag = false;
      err_2_flag = false;
      Z_WORKING_FEED_FLAG = OFF;
      X_WORKING_FEED_FLAG = OFF;
      Z_WORKING_RAPID_FLAG = OFF;
      X_WORKING_RAPID_FLAG = OFF;
      Ks_Count = 0;
      Km_Count = 0;
      Repeat_Count = 0;
      Print();
      break;
    }
  */
  //Opti Выигрыш 5 байт
  switch (Mode)
  {
    case Mode_Reserve:
    case Mode_Divider:
      break;
    default:                                  //Все остальные режимы
      Sub_Mode_Thread = Sub_Mode_Thread_Man;
      Sub_Mode_Feed = Sub_Mode_Feed_Man;
      Sub_Mode_aFeed = Sub_Mode_aFeed_Man;
      Sub_Mode_Cone = Sub_Mode_Cone_Man;
      Sub_Mode_Sphere = Sub_Mode_Sphere_Man;
      err_1_flag = false;
      err_2_flag = false;
      Z_WORKING_FEED_FLAG = OFF;
      X_WORKING_FEED_FLAG = OFF;
      Z_WORKING_RAPID_FLAG = OFF;
      X_WORKING_RAPID_FLAG = OFF;
      Ks_Count = 0;
      Km_Count = 0;
      Repeat_Count = 0;
      Print();
      break;
  }
  //---
}

void Switch_Ext()
{
  switch (Mode) //////////////////////////////////////////////////////////////////////////////////////////////
  {
    case Mode_Thread:
    case Mode_Feed:
    case Mode_aFeed:
    case Mode_Cone_L:
    case Mode_Cone_R:
      if ((limit_Left_flag == ON && limit_Right_flag == ON) ||
          (limit_Front_flag == ON && limit_Rear_flag == ON))
      {
        Sub_Mode_Thread = Sub_Mode_Thread_Ext;
        Sub_Mode_Feed = Sub_Mode_Feed_Ext;
        Sub_Mode_aFeed = Sub_Mode_aFeed_Ext;
        Sub_Mode_Cone = Sub_Mode_Cone_Ext;
        err_1_flag = false;
        Z_WORKING_FEED_FLAG = OFF;
        X_WORKING_FEED_FLAG = OFF;
        Z_WORKING_RAPID_FLAG = OFF;
        X_WORKING_RAPID_FLAG = OFF;
        Ks_Count = 0;
        Km_Count = 0;
        Repeat_Count = 0;

        if (Motor_Z_Pos == Limit_Pos_Right ||
            Motor_Z_Pos == Limit_Pos_Left ||
            Motor_X_Pos == Limit_Pos_Rear ||
            Motor_X_Pos == Limit_Pos_Front)
        {
          err_2_flag = false;
        }
        else
        {
          Sub_Mode_Thread = Sub_Mode_Thread_Man;
          Sub_Mode_Feed = Sub_Mode_Feed_Man;
          Sub_Mode_aFeed = Sub_Mode_aFeed_Man;
          Sub_Mode_Cone = Sub_Mode_Cone_Man;
          err_2_flag = true;
          Beep_Error();
        }
      }
      else
      {
        Sub_Mode_Thread = Sub_Mode_Thread_Man;
        Sub_Mode_Feed = Sub_Mode_Feed_Man;
        Sub_Mode_aFeed = Sub_Mode_aFeed_Man;
        Sub_Mode_Cone = Sub_Mode_Cone_Man;
        err_1_flag = true;
        Beep_Error();
      }
      Print();
      break;

    case Mode_Sphere:  /////////////////////////////////////////////////////////////////////////////////////
      if (limit_Right_flag == ON && limit_Rear_flag == ON)
      {
        Sub_Mode_Sphere = Sub_Mode_Sphere_Ext;
        err_1_flag = false;
        Z_WORKING_FEED_FLAG = OFF;
        X_WORKING_FEED_FLAG = OFF;
        Ks_Count = 0;
        Km_Count = 0;
        Repeat_Count = 0;

        if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear)
        {
          err_2_flag = false;
        } else {
          Sub_Mode_Sphere = Sub_Mode_Sphere_Man;
          err_2_flag = true;
          Beep_Error();
        }
      }
      else
      {
        Sub_Mode_Sphere = Sub_Mode_Sphere_Man;
        err_1_flag = true;
        Beep_Error();
      }
      Print();
      break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработка Кнопок Меню ********** ///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработчик нажатия кнопки Select **********
//Opti Закомментировал пустой код и вынес проверку if (!Joy_Z_flag && !Joy_X_flag) до switch(Mode)
void Key_Select_Pressed()
{
  if (!key_sel_flag)
  {
    //Opti
    if (!Joy_Z_flag && !Joy_X_flag)
    {

      switch (Mode)
      {
        //Opti Пустой код
        /*
          case Mode_Feed:
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            //
          }
          break;

          case Mode_Cone_L:
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            //
          }
          break;

          case Mode_Cone_R:
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            //
          }
          break;

          case Mode_Thread:
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            //
          }
          break;
        */

        case Mode_Sphere:
          //if (!Joy_Z_flag && !Joy_X_flag)
          //{
          Beep();
          //}
          break;

        case Mode_Divider:
          //if (!Joy_Z_flag && !Joy_X_flag)
          //{
          Enc_Pos = 0;
          //NEW3
          //Для ДЕЛИЛКИх2
          get_Enc_Pos_Divider();
          //---
          //---
          Beep();
          //}
          break;
      }

    } //Opti

    key_sel_flag = true;
    Print();
  }
}

// ********** Обработчик нажатия кнопки Up **********
void Key_Up_Pressed()
{
  if (!button_flag)
  {
    switch (Mode)
    {
      case Mode_Feed:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (Ap < 100)      {
            Ap = Ap + 10;
            Beep();
          }
          else if (Ap < 200) {
            Ap = Ap + 20;
            Beep();
          }
          else if (Ap < 500) {
            Ap = Ap + 50;
            Beep();
          }
          else if (Ap < 900) {
            Ap = Ap + 100;
            Beep();
          }
        }
        Print();
        break;

      //NEW Многопроходный aFeed
      case Mode_aFeed:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (Ap < 10) {
            Ap = Ap +  5;
            Beep();
          } else if (Ap < 500) {
            Ap = Ap + 10;
            Beep();
          } else if (Ap < 900) {
            Ap = Ap + 50;
            Beep();
          }
        }
        Print();
        break;
      //---

      case Mode_Thread:
        if (Thread_Step < TOTAL_THREADS - 1)
        {
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            Thread_Step++;
            Ks_Count = 0;
            Km_Count = 0;
            Repeat_Count = 0;
            Z_WORKING_FEED_FLAG = OFF;
            X_WORKING_FEED_FLAG = OFF;
            Z_WORKING_RAPID_FLAG = OFF;
            X_WORKING_RAPID_FLAG = OFF;
            Beep();
          }
        }
        Print();
        break;

      //NEW Многопроходный КОНУС
      case Mode_Cone_L:
      case Mode_Cone_R:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (Ap < 500)
          {
            Ap = Ap + 10;
            Beep();
          } else if (Ap < 900)
          {
            Ap = Ap + 50;
            Beep();
          }
        }
        Print();
        break;
      //---

      case Mode_Sphere:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (!key_sel_flag)
          {
            if      (Sph_R_mm < 1250) {
              Sph_R_mm = Sph_R_mm + 25;
              Beep();
            }
            else if (Sph_R_mm < 2500) {
              Sph_R_mm = Sph_R_mm + 50;
              Beep();
            }
            else if (Sph_R_mm < 4750) {
              Sph_R_mm = Sph_R_mm + 250;
              Beep();
            }

            R_Quad = Sph_R_mm * Sph_R_mm;
            Sph_R = (MOTOR_X_STEP_PER_REV * McSTEP_X * Sph_R_mm / SCREW_X);
          }
          else
          {
            if (Cutter_Step < TOTAL_CUTTER_WIDTH - 1)
            {
              Cutter_Step++;
              Cutter_Width = Cutter_Width_array[Cutter_Step];
              Beep();
            }
          }
        }
        Print();
        break;

      case Mode_Divider:
        if (Total_Tooth < 255)
        {
          Total_Tooth++;
          Current_Tooth = 1;
          Beep();
        }
        Print();
        break;
    }

    button_flag = true;
  }
}

// ********** Обработчик нажатия кнопки Down **********
void Key_Down_Pressed()
{
  if (!button_flag)
  {
    switch (Mode)
    {
      case Mode_Feed:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (Ap > 500)      {
            Ap = Ap - 100;
            Beep();
          }
          else if (Ap > 200) {
            Ap = Ap - 50;
            Beep();
          }
          else if (Ap > 100) {
            Ap = Ap - 20;
            Beep();
          }
          else if (Ap > 0)   {
            Ap = Ap - 10;
            Beep();
          }
        }
        Print();
        break;

      //NEW Многопроходный aFeed
      case Mode_aFeed:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (Ap > 500) {
            Ap = Ap - 50;
            Beep();
          } else if (Ap > 10) {
            Ap = Ap - 10;
            Beep();
          } else if (Ap > 0) {
            Ap = Ap -  5;
            Beep();
          }
        }
        Print();
        break;
      //---

      case Mode_Thread:
        if (Thread_Step > 0)
        {
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            Thread_Step--;
            Ks_Count = 0;
            Km_Count = 0;
            Repeat_Count = 0;
            Z_WORKING_FEED_FLAG = OFF;
            X_WORKING_FEED_FLAG = OFF;
            Z_WORKING_RAPID_FLAG = OFF;
            X_WORKING_RAPID_FLAG = OFF;
            Beep();
          }
        }
        Print();
        break;

      //NEW Многопроходный КОНУС
      case Mode_Cone_L:
      case Mode_Cone_R:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (Ap > 500)
          {
            Ap = Ap - 50;
            Beep();
          } else if (Ap > 0)
          {
            Ap = Ap - 10;
            Beep();
          }
        }
        Print();
        break;
      //---

      case Mode_Sphere:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (!key_sel_flag)
          {
            if      (Sph_R_mm > 2500) {
              Sph_R_mm = Sph_R_mm - 250;
              Beep();
            } else if (Sph_R_mm > 1250) {
              Sph_R_mm = Sph_R_mm - 50;
              Beep();
            } else if (Sph_R_mm > 50)   {
              Sph_R_mm = Sph_R_mm - 25;
              Beep();
            }
            if (Sph_R_mm < Bar_R_mm) Bar_R_mm = Sph_R_mm;

            R_Quad = Sph_R_mm * Sph_R_mm;
            Sph_R = (MOTOR_X_STEP_PER_REV * McSTEP_X * Sph_R_mm / SCREW_X);   // радиус сферы в шагах
          } else {
            if (Cutter_Step > 0)
            {
              Cutter_Step--;
              Cutter_Width = Cutter_Width_array[Cutter_Step];
              Beep();
            }
          }

        }
        Print();
        break;

      case Mode_Divider:
        if (Total_Tooth > 1)
        {
          Total_Tooth--;
          Current_Tooth = 1;
          Beep();
        }
        Print();
        break;
    }
    button_flag = true;
  }
}

// ********** Обработчик нажатия кнопки Left **********
void Key_Left_Pressed()
{
  if (!button_flag)
  {
    switch (Mode)
    {
      case Mode_Feed:
        if (Pass_Total > 1)
        {
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            Pass_Total--;
            Beep();
          }
        }
        Print();
        break;

      //NEW Многопроходный aFeed
      case Mode_aFeed:
        if (Pass_Total > 1 && !Joy_Z_flag && !Joy_X_flag)
        {
          Pass_Total--;
          Beep();
        }
        Print();
        break;
      //---


      case Mode_Cone_L:
      case Mode_Cone_R:
        //OLD
        /*
          if (Cone_Step > 0)
          {
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            Cone_Step--;
            Ks_Count = 0;
            Km_Count = 0;
            Repeat_Count = 0;
            Z_WORKING_FEED_FLAG = OFF;
            X_WORKING_FEED_FLAG = OFF;
            Z_WORKING_RAPID_FLAG = OFF;
            X_WORKING_RAPID_FLAG = OFF;
            Beep();
          }
          }
        */
        //NEW Многопроходный КОНУС
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (key_sel_flag)      //Если нажата кнопка "Select"
          {
            if (Pass_Total > 1)
            {
              Pass_Total--;
              Beep();
            }
          } else {
            if (Cone_Step > 0)
            {
              Cone_Step--;
              Ks_Count = 0;
              Km_Count = 0;
              Repeat_Count = 0;
              Z_WORKING_FEED_FLAG = OFF;
              X_WORKING_FEED_FLAG = OFF;
              Z_WORKING_RAPID_FLAG = OFF;
              X_WORKING_RAPID_FLAG = OFF;
              Beep();
            }
          }
        }
        //--
        Print();
        break;

      case Mode_Sphere:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (!key_sel_flag)
          {
            if (Bar_R_mm > 0)
            {
              Bar_R_mm = Bar_R_mm - 25;
              Bar_R = (MOTOR_X_STEP_PER_REV * McSTEP_X * Bar_R_mm / SCREW_X);
              Beep();
            }
          } else {
            if (Cutting_Step > 0)
            {
              Cutting_Step--;
              Cutting_Width = Cutting_Width_array[Cutting_Step];
              Beep();
            }
          }
        }
        Print();
        break;

      case Mode_Divider:
        if (Current_Tooth > 1)
        {
          Current_Tooth--;
          Beep();
        } else if (Current_Tooth == 1)
        {
          Current_Tooth = Total_Tooth;
          Beep();
        }
        Print();
        break;
    }
    button_flag = true;
  }
}

// ********** Обработчик нажатия кнопки Right **********
void Key_Right_Pressed()
{
  if (!button_flag)
  {
    switch (Mode)
    {
      case Mode_Feed:
        if (Pass_Total < 9)
        {
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            Pass_Total++;
            Beep();
          }
        }
        Print();
        break;

      //NEW Многопроходный aFeed
      case Mode_aFeed:
        if (Pass_Total < 99 && !Joy_Z_flag && !Joy_X_flag)
        {
          Pass_Total++;
          Beep();
        }
        Print();
        break;
      //---

      case Mode_Cone_L:
      case Mode_Cone_R:
        //OLD
        /*
          if (Cone_Step < TOTAL_CONE - 1)
          {
          if (!Joy_Z_flag && !Joy_X_flag)
          {
            Cone_Step++;
            Ks_Count = 0;
            Km_Count = 0;
            Repeat_Count = 0;
            Z_WORKING_FEED_FLAG = OFF;
            X_WORKING_FEED_FLAG = OFF;
            Z_WORKING_RAPID_FLAG = OFF;
            X_WORKING_RAPID_FLAG = OFF;
            Beep();
          }
          }
        */
        //NEW Многопроходный КОНУС
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (key_sel_flag)      //Если нажата кнопка "Select"
          {
            if (Pass_Total < 99)
            {
              Pass_Total++;
              Beep();
            }
          } else {
            if (Cone_Step < TOTAL_CONE - 1)
            {
              Cone_Step++;
              Ks_Count = 0;
              Km_Count = 0;
              Repeat_Count = 0;
              Z_WORKING_FEED_FLAG = OFF;
              X_WORKING_FEED_FLAG = OFF;
              Z_WORKING_RAPID_FLAG = OFF;
              X_WORKING_RAPID_FLAG = OFF;
              Beep();
            }
          }
        }
        //---
        Print();
        break;

      case Mode_Sphere:
        if (!Joy_Z_flag && !Joy_X_flag)
        {
          if (!key_sel_flag)
          {
            if (Bar_R_mm < Sph_R_mm)
            {
              Bar_R_mm = Bar_R_mm + 25;
              Bar_R = (MOTOR_X_STEP_PER_REV * McSTEP_X * Bar_R_mm / SCREW_X);   // радиус недореза в шагах
              Beep();
            }
          } else {
            if (Cutting_Step < TOTAL_CUTTING_STEP - 1)
            {
              Cutting_Step++;
              Cutting_Width = Cutting_Width_array[Cutting_Step];
              Beep();
            }
          }
        }
        Print();
        break;

      case Mode_Divider:
        if (Current_Tooth < Total_Tooth)
        {
          Current_Tooth++;
          Beep();
        }
        else if (Current_Tooth == Total_Tooth)
        {
          Current_Tooth = 1;
          Beep();
        }
        Print();
        break;
    }
    button_flag = true;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработка кнопок лимита ********** /////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработчик нажатия кнопки Limit_Left **********
void Limit_Left_Pressed()
{
  if (!limit_button_flag)
  {
    limit_button_flag = true;
    switch (Mode)
    {
      case Mode_Thread:
      case Mode_Feed:
      case Mode_aFeed:
      case Mode_Cone_L:
      case Mode_Cone_R:
        if (!Joy_Z_flag && Submode_Read == B10100000)
        {
          if (limit_Left_flag == OFF)
          {
            if (Motor_Z_Pos > (Limit_Pos_Right + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
            {
              limit_Left_flag = ON;
              Limit_Pos_Left = ((Motor_Z_Pos + McSTEP_Z / 2) & ~(McSTEP_Z - 1));
              Limit_Left_LED_On();
              Beep();
            }
          } else {
            limit_Left_flag = OFF;
            Limit_Pos_Left = Limit_Pos_Max;
            Limit_Left_LED_Off();
            Beep();
          }
        }
        break;               //Fix - пропущен был break
    }
  }
}

// ********** Обработчик нажатия кнопки Limit_Right **********
void Limit_Right_Pressed()
{
  if (!limit_button_flag)
  {
    limit_button_flag = true;
    switch (Mode)
    {
      case Mode_Thread:
      case Mode_Feed:
      case Mode_aFeed:
      case Mode_Cone_L:
      case Mode_Cone_R:
      case Mode_Sphere:
        if (!Joy_Z_flag && Submode_Read == B10100000)
        {
          if (limit_Right_flag == OFF)
          {
            if (Motor_Z_Pos < (Limit_Pos_Left - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
            {
              limit_Right_flag = ON;
              Limit_Pos_Right = ((Motor_Z_Pos + McSTEP_Z / 2) & ~(McSTEP_Z - 1));
              Limit_Right_LED_On();
              Beep();
            }
          } else {
            limit_Right_flag = OFF;
            Limit_Pos_Right = Limit_Pos_Min;
            Limit_Right_LED_Off();
            Beep();
          }
        }
        break;               //Fix - пропущен был break
    }
  }
}

// ********** Обработчик нажатия кнопки Limit_Front **********
void Limit_Front_Pressed()
{
  if (!limit_button_flag)
  {
    limit_button_flag = true;
    switch (Mode)
    {
      case Mode_Thread:
      case Mode_Feed:
      case Mode_aFeed:
      //NEW
      case Mode_Cone_L:
      case Mode_Cone_R:
        //-

        if (!Joy_X_flag && Submode_Read == B10100000)
        {
          if (limit_Front_flag == OFF)
          {
            if (Motor_X_Pos > (Limit_Pos_Rear + ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
            {
              limit_Front_flag = ON;
              Limit_Pos_Front = ((Motor_X_Pos + McSTEP_X / 2) & ~(McSTEP_X - 1));
              Limit_Front_LED_On();
              Beep();
            }
          } else {
            limit_Front_flag = OFF;
            Limit_Pos_Front = Limit_Pos_Max;
            Limit_Front_LED_Off();
            Beep();
          }
        }
        break;               //Fix - пропущен был break
    }
  }
}

// ********** Обработчик нажатия кнопки Limit_Rear **********
void Limit_Rear_Pressed()
{
  if (!limit_button_flag)
  {
    limit_button_flag = true;
    switch (Mode)
    {
      case Mode_Thread:
      case Mode_Feed:
      case Mode_aFeed:

      //NEW
      case Mode_Cone_L:
      case Mode_Cone_R:
      //-

      case Mode_Sphere:
        if (!Joy_X_flag && Submode_Read == B10100000)
        {
          if (limit_Rear_flag == OFF)
          {
            if (Motor_X_Pos < (Limit_Pos_Front - ((MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt) * 2))
            {
              limit_Rear_flag = ON;
              Limit_Pos_Rear = ((Motor_X_Pos + McSTEP_X / 2) & ~(McSTEP_X - 1));
              Limit_Rear_LED_On();
              Beep();
            }
          } else {
            limit_Rear_flag = OFF;
            Limit_Pos_Rear = Limit_Pos_Min;
            Limit_Rear_LED_Off();
            Beep();
          }
        }
        break;               //Fix - пропущен был break
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработка переключателя оси РГИ ********** /////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Switch_Hand_Axis_Z()
{
  //Fix: убрано выключение мотора X
  //Motor_X_Disable();
  Motor_Z_Enable();

  flag_hand_X = OFF;
  hand_X = OFF;
  flag_hand_Z = ON;

  Hand_Count = 0;
  Hand_Count_New = 0;
  Hand_Count_Old = 0;
  Hand_Z_Pos = 0;
  Null_Z_Pos = Motor_Z_Pos;

  Disable_INT_OCR3B();
  Enable_INT_OCR3A();
  Ena_INT_Hcoder();
}

void Switch_Hand_Axis_X()
{
  //Fix: убрано выключение мотора Z
  //Motor_Z_Disable();
  Motor_X_Enable();

  flag_hand_Z = OFF;
  hand_Z = OFF;
  flag_hand_X = ON;

  Hand_Count = 0;
  Hand_Count_New = 0;
  Hand_Count_Old = 0;
  Hand_X_Pos = 0;
  Null_X_Pos = Motor_X_Pos;

  Disable_INT_OCR3A();
  Enable_INT_OCR3B();
  Ena_INT_Hcoder();
}

void Switch_Hand_Axis_No()
{
  //Fix: убрано выключение мотора X
  //Motor_X_Disable();
  //Fix: убрано выключение мотора Z
  //Motor_Z_Disable();

  flag_hand_Z = OFF;
  hand_Z = OFF;
  flag_hand_X = OFF;
  hand_X = OFF;

  //OLD
  //Hand_Count = 0;
  //Hand_Count_New = 0;
  //Hand_Count_Old = 0;
  //Hand_Z_Pos = 0;
  //Hand_X_Pos = 0;
  //Null_Z_Pos = Motor_Z_Pos;
  //Null_X_Pos = Motor_X_Pos;
  //Opti Выигрыш 67128 - 66894 = 234 байт!!!
  Reset_Hand_NullPos();   //-> Hand_Count = 0; Hand_Count_New = 0; Hand_Count_Old = 0; Hand_Z_Pos = 0; Hand_X_Pos = 0; Null_Z_Pos = Motor_Z_Pos; Null_X_Pos = Motor_X_Pos;

  Disa_INT_Hcoder();
  Disable_INT_OCR3A();
  Disable_INT_OCR3B();

  err_3_flag = false;   //new
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Обработка Масштаба РГИ ********** /////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Switch_Scale_x1()
{
  flag_Scale_x10 = OFF;
  flag_Scale_x1 = ON;
  hand_Z = OFF;
  hand_X = OFF;
}

void Switch_Scale_x10()
{
  flag_Scale_x1 = OFF;
  flag_Scale_x10 = ON;
  hand_Z = OFF;
  hand_X = OFF;
}
