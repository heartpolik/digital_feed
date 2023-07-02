//==============================================================================================================================================================================================================

void NEW_Feed_Left(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    a_flag = true;
    b_flag = false;
    Joy_X_flag = OFF;                   //На Рапиде точно так же
    X_NEED_RUN_FEED_FLAG = OFF;                  //На Рапиде точно так же
    X_NEED_RUN_RAPID_FLAG = OFF;

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (Z_WORKING_RAPID_FLAG == OFF)
    {
      OCR5A = max_OCR5A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;   //По своей сути это константа (после прохода секции SETUP), можно вычислить заранее

  }
  else            //ОБЫЧНАЯ ПОДАЧА
  {
    if (b_flag == true) return;         //На Рапиде проверяется флаг a_flag
    a_flag = false;                     //На Рапиде наоборот - a_flag = true;
    b_flag = true;                      //На Рапиде наоборот - b_flag = false;
    Joy_X_flag = OFF;                   //На Рапиде точно так же
    X_NEED_RUN_FEED_FLAG = OFF;                  //На Рапиде точно так же

    //OLD
    Start_Speed = ENC_LINE_PER_REV / ((float)MOTOR_Z_STEP_PER_REV * McSTEP_Z * MIN_FEED / SCREW_Z) / FEED_ACCEL /2 +0.5;
    //
    if (Motor_Z_Pos < Limit_Pos_Left - Start_Speed * 2)
    {
      //OLD
      Feed_Divisor = ENC_LINE_PER_REV / ((float)MOTOR_Z_STEP_PER_REV * McSTEP_Z * Feed_mm / SCREW_Z) /2 +0.5;
      //
      if (Feed_Divisor < Start_Speed)
      {
        max_OCR5A = Start_Speed;
        if (Z_WORKING_FEED_FLAG == OFF)
        {
          OCR5A = Start_Speed;
        }
      } else {
        max_OCR5A = Feed_Divisor;
        OCR5A = Feed_Divisor;
      }
    }
    else
    {
      Feed_Divisor = Start_Speed;
      max_OCR5A = Start_Speed;
      OCR5A = Start_Speed;
    }

    Brake_Compens = max_OCR5A - Feed_Divisor + 1;           //На Рапиде другие формулы
  }
  Limit_Pos = Limit_Pos_Left - Brake_Compens;               //На Рапиде точно так же

  Motor_Z_Dir = CW;                                         //На Рапиде точно так же
  Motor_Z_CW();                                             //На Рапиде точно так же
  if (Read_Z_Ena_State == false) Motor_Z_Enable();          //На Рапиде точно так же

  Joy_Z_flag = ON;                                          //На Рапиде точно так же

  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    SpeedMode = FORCE_RAPID;
    Z_NEED_RUN_RAPID_FLAG = ON;
  } else if (CurrentSpeedMode == FORCE_SLOW)   //ОБЫЧНАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    SpeedMode = FORCE_SLOW;
    Z_NEED_RUN_FEED_FLAG = ON;
  } else {                                    //ОБЫЧНАЯ ПОДАЧА
    SpeedMode = MANUAL;
    Z_NEED_RUN_FEED_FLAG = ON;
  }

  Ena_INT_Z_Feed();   //new
}
//==============================================================================================================================================================================================================
void NEW_Feed_Right(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    a_flag = true;
    b_flag = false;
    Joy_X_flag = OFF;           //На Рапиде точно так же
    X_NEED_RUN_FEED_FLAG = OFF;          //На Рапиде точно так же
    X_NEED_RUN_RAPID_FLAG = OFF;

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (Z_WORKING_RAPID_FLAG == OFF)
    {
      OCR5A = max_OCR5A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---
    
    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;     //На Рапиде другая формула
  }
  else            //ОБЫЧНАЯ ПОДАЧА
  {
    if (b_flag == true) return; //На Рапиде проверяется флаг a_flag
    a_flag = false;             //На Рапиде a_flag = true
    b_flag = true;              //На Рапиде b_flag = false
    Joy_X_flag = OFF;           //На Рапиде точно так же
    X_NEED_RUN_FEED_FLAG = OFF;          //На Рапиде точно так же

    //OLD
    Start_Speed = ENC_LINE_PER_REV / ((float)MOTOR_Z_STEP_PER_REV * McSTEP_Z * MIN_FEED / SCREW_Z) / FEED_ACCEL /2 +0.5;
    //

    if (Motor_Z_Pos > Limit_Pos_Right + Start_Speed * 2)
    {
      //OLD
      Feed_Divisor = ENC_LINE_PER_REV / ((float)MOTOR_Z_STEP_PER_REV * McSTEP_Z * Feed_mm / SCREW_Z) /2 +0.5;
      //
      
      if (Feed_Divisor < Start_Speed)
      {
        max_OCR5A = Start_Speed;
        if (Z_WORKING_FEED_FLAG == OFF)
        {
          OCR5A = Start_Speed;
        }
      } else {
        max_OCR5A = Feed_Divisor;
        OCR5A = Feed_Divisor;
      }
    }
    else
    {
      Feed_Divisor = Start_Speed;
      max_OCR5A = Start_Speed;
      OCR5A = Start_Speed;
    }
    Brake_Compens = (max_OCR5A - Feed_Divisor) + 1;     //На Рапиде другая формула
  }
  Limit_Pos = Limit_Pos_Right + Brake_Compens;          //На Рапиде точно так же

  Motor_Z_Dir = CCW;                                    //На Рапиде точно так же
  Motor_Z_CCW();                                        //На Рапиде точно так же
  if (Read_Z_Ena_State == false) Motor_Z_Enable();      //На Рапиде точно так же

  Joy_Z_flag = ON;

  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    SpeedMode = FORCE_RAPID;
    Z_NEED_RUN_RAPID_FLAG = ON;
  } else if (CurrentSpeedMode == FORCE_SLOW)   //ОБЫЧНАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    SpeedMode = FORCE_SLOW;
    Z_NEED_RUN_FEED_FLAG = ON;
  } else {                                    //ОБЫЧНАЯ ПОДАЧА
    SpeedMode = MANUAL;
    Z_NEED_RUN_FEED_FLAG = ON;
  }

  Ena_INT_Z_Feed();   //new
}
//==============================================================================================================================================================================================================
void NEW_Feed_Front(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    a_flag = true;
    b_flag = false;
    Joy_Z_flag = OFF;                       //На Рапиде точно так же
    Z_NEED_RUN_FEED_FLAG = OFF;                      //На Рапиде точно так же
    Z_NEED_RUN_RAPID_FLAG = OFF;                     //Только на Рапиде

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (X_WORKING_RAPID_FLAG == OFF)
    {
      OCR5A = max_OCR5A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;
  }
  else            //ОБЫЧНАЯ ПОДАЧА
  {
    if (b_flag == true) return;            //На Рапиде проверяется флаг a_flag
    a_flag = false;
    b_flag = true;
    Joy_Z_flag = OFF;                      //На Рапиде точно так же
    Z_NEED_RUN_FEED_FLAG = OFF;                     //На Рапиде точно так же

    //OLD
    Start_Speed = ENC_LINE_PER_REV / ((float)MOTOR_X_STEP_PER_REV * McSTEP_X * MIN_FEED / SCREW_X) / FEED_ACCEL /2 +0.5;
    //
    
    if (Motor_X_Pos < Limit_Pos_Front - Start_Speed * 2)
    {
      //OLD
      Feed_Divisor = ENC_LINE_PER_REV / ((float)MOTOR_X_STEP_PER_REV * McSTEP_X * Feed_mm / SCREW_X) /2 +0.5;
      //-
      
      if (Feed_Divisor < Start_Speed)
      {
        max_OCR5A = Start_Speed;
        if (X_WORKING_FEED_FLAG == OFF)
        {
          OCR5A = Start_Speed;
        }
      } else {
        max_OCR5A = Feed_Divisor;
        OCR5A = Feed_Divisor;
      }
    }
    else
    {
      Feed_Divisor = Start_Speed;
      max_OCR5A = Start_Speed;
      OCR5A = Start_Speed;
    }
    Brake_Compens = max_OCR5A - Feed_Divisor + 1;                   //Отличается от Рапида формулой
  }
  Limit_Pos = Limit_Pos_Front - Brake_Compens;                      //На Рапиде точно так же

  Motor_X_Dir = CW;                                                 //На Рапиде точно так же
  Motor_X_CW();                                                     //На Рапиде точно так же
  if (Read_X_Ena_State == false) Motor_X_Enable();                  //На Рапиде точно так же

  Joy_X_flag = ON;                                                  //На Рапиде точно так же

  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    SpeedMode = FORCE_RAPID;
    X_NEED_RUN_RAPID_FLAG = ON;   
  } else if (CurrentSpeedMode == FORCE_SLOW)   //ОБЫЧНАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    SpeedMode = FORCE_SLOW;
    X_NEED_RUN_FEED_FLAG = ON;
  } else {                                    //ОБЫЧНАЯ ПОДАЧА
    SpeedMode = MANUAL;
    X_NEED_RUN_FEED_FLAG = ON;
  }
  
  Ena_INT_X_Feed();   //new
}
//==============================================================================================================================================================================================================
void NEW_Feed_Rear(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;                                   //На Рапиде проверяется флаг a_flag
    b_flag = false;
    a_flag = true;
    Joy_Z_flag = OFF;                                             //На Рапиде точно так же
    Z_NEED_RUN_FEED_FLAG = OFF;                                            //На Рапиде точно так же
    Z_NEED_RUN_RAPID_FLAG = OFF;                                           //Только на Рапиде

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (X_WORKING_RAPID_FLAG == OFF)
    {
      OCR5A = max_OCR5A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;
  }
  else            //ОБЫЧНАЯ ПОДАЧА
  {
    if (b_flag == true) return;                                   //На обычной подаче проверяется флаг b_flag
    a_flag = false;
    b_flag = true;
    Joy_Z_flag = OFF;                                             //На Рапиде точно так же
    Z_NEED_RUN_FEED_FLAG = OFF;                                            //На Рапиде точно так же

    //OLD
    Start_Speed = ENC_LINE_PER_REV / ((float)MOTOR_X_STEP_PER_REV * McSTEP_X * MIN_FEED / SCREW_X) / FEED_ACCEL /2 +0.5;
    //
    
    if (Motor_X_Pos > Limit_Pos_Rear + Start_Speed * 2)
    {
      //OLD
      Feed_Divisor = ENC_LINE_PER_REV / ((float)MOTOR_X_STEP_PER_REV * McSTEP_X * Feed_mm / SCREW_X) /2 +0.5;
      //-
      
      if (Feed_Divisor < Start_Speed)
      {
        max_OCR5A = Start_Speed;
        if (X_WORKING_FEED_FLAG == OFF)
        {
          OCR5A = Start_Speed;
        }
      } else {
        max_OCR5A = Feed_Divisor;
        OCR5A = Feed_Divisor;
      }
    }
    else
    {
      Feed_Divisor = Start_Speed;
      max_OCR5A = Start_Speed;
      OCR5A = Start_Speed;
    }
    Brake_Compens = max_OCR5A - Feed_Divisor + 1;                   //Отличается от Рапида формулой
  }
  Limit_Pos = Limit_Pos_Rear + Brake_Compens;                       //На Рапиде точно так же

  Motor_X_Dir = CCW;                                                //На Рапиде точно так же
  Motor_X_CCW();                                                    //На Рапиде точно так же
  if (Read_X_Ena_State == false) Motor_X_Enable();                  //На Рапиде точно так же

  Joy_X_flag = ON;                                                  //На Рапиде точно так же

  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    SpeedMode = FORCE_RAPID;
    X_NEED_RUN_RAPID_FLAG = ON;   
  } else if (CurrentSpeedMode == FORCE_SLOW)   //ОБЫЧНАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    SpeedMode = FORCE_SLOW;
    X_NEED_RUN_FEED_FLAG = ON;
  } else {                                    //ОБЫЧНАЯ ПОДАЧА
    SpeedMode = MANUAL;
    X_NEED_RUN_FEED_FLAG = ON;
  }
  
  Ena_INT_X_Feed();   //new
}
//==============================================================================================================================================================================================================


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Режим "Цикл Подача" ********** /////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Opti Выгода 18 байт + перекомпановка проверок
void Feed_Ext_Left()
{
  //OLD
  //if ((Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF) ||
  //    (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF))
  //{
  //Opti
  if (Motor_Z_Pos == Limit_Pos_Right)
  {
    if (Z_WORKING_FEED_FLAG == OFF && (Motor_X_Pos == Limit_Pos_Rear || Motor_X_Pos == Null_X_Pos))
    {
      //-

      //OLD
      //if (cycle_flag == false && Pass_Nr <= Pass_Total)
      //Opti Выносим условие cycle_flag == false
      if (cycle_flag == false)
      {
        //OLD
        //else if (cycle_flag == false && Pass_Nr > Pass_Total)
        //Opti (Pass_Nr > Pass_Total)
        //Поменял местами ветки условий. (Pass_Nr > Pass_Total) - проверяется первым.
        if (Pass_Nr > Pass_Total)
          //-
        {
          a_flag = false;
          b_flag = false;

          Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X ;
          //Feed_Front(a_flag, b_flag);
          NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ

          Limit_Front_LED_Off();
          Limit_Rear_LED_Off();
          Limit_Pos_Front = Limit_Pos_Max;
          Limit_Pos_Rear = Limit_Pos_Min;
          Pass_Total = 1;
          Pass_Nr = 1;
          Print();
        }


        //OLD
        //if (Pass_Nr <= Pass_Total)
        //Opti Вторая проверка (Pass_Nr <= Pass_Total) не проводится, а используется ELSE - т.к. 1 и 2 проверка взаимоисключающие.
        else
          //-
        {
          cycle_flag = true;
          a_flag = false;
          b_flag = false;
          //OLD
          //long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X + 0.5) * McSTEP_X;
          //Opti Выгода 18 байт (Infeed_Value тип int + умножение на McSTEP_X происходит в ветке условия
          int Infeed_Value = (int)((float)(MOTOR_X_STEP_PER_REV * Ap) / SCREW_X + 0.5f);
          //-
          if (Infeed_Value == 0)
          {
            if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + 1);
            else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
          } else {
            //OLD
            //if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
            //else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + Infeed_Value);
            //Opti
            long Infeed_Value_long = Infeed_Value * McSTEP_X;
            if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value_long);
            else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + Infeed_Value_long);
            //-
          }
          Limit_Front_LED_On();
          BeepBeep();
          //Feed_Front(a_flag, b_flag);
          NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
        }

        //Opti
      }
      //-
    }

    //OLD
    //else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
      //-
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //Feed_Left(a_flag, b_flag);
        NEW_Feed_Left(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
      }
    }
    //Opti
  }
  //-
  //-------------------------------------------------------------------------------------------------------------------------------
  //OLD
  //else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF)
  //Opti
  else if (Motor_Z_Pos == Limit_Pos_Left)
  {
    if (Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF)
      //-

    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
      Limit_Rear_LED_On();
      //Feed_Rear(a_flag, b_flag);
      NEW_Feed_Rear(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
    }
    //OLD
    //else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
      //-
    {
      a_flag = false;
      b_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Right(a_flag, b_flag);
      NEW_Feed_Right(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
    }
    //Opti
  }
  //-
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Feed_Ext_Right()
{
  //OLD
  //if ((Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF) ||
  //    (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF))
  //{
  //Opti
  if (Motor_Z_Pos == Limit_Pos_Left)
  {
    if (Z_WORKING_FEED_FLAG == OFF && (Motor_X_Pos == Limit_Pos_Rear || Motor_X_Pos == Null_X_Pos))
    {
      //-


      //OLD
      //if (cycle_flag == false && Pass_Nr <= Pass_Total)
      //Opti
      if (cycle_flag == false)
      {

        //OLD
        //else if (cycle_flag == false && Pass_Nr > Pass_Total)
        //Opti
        //Поменял местами ветки условий. (Pass_Nr > Pass_Total) - проверяется первым.
        if (Pass_Nr > Pass_Total)
          //-
        {
          a_flag = false;
          b_flag = false;

          Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X;
          //Feed_Front(a_flag, b_flag);
          NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ

          Limit_Front_LED_Off();
          Limit_Rear_LED_Off();
          Limit_Pos_Front = Limit_Pos_Max;
          Limit_Pos_Rear = Limit_Pos_Min;
          Pass_Total = 1;
          Pass_Nr = 1;
          Print();
        }

        //OLD
        //if (Pass_Nr <= Pass_Total)
        //Opti Вторая проверка (Pass_Nr <= Pass_Total) не проводится, а используется ELSE - т.к. 1 и 2 проверка взаимоисключающие.
        else
          //-
        {
          cycle_flag = true;
          a_flag = false;
          b_flag = false;
          //OLD
          //long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X + 0.5) * McSTEP_X;
          //Opti Выгода 18 байт (Infeed_Value тип int + умножение на McSTEP_X происходит в ветке условия
          int Infeed_Value = (int)((float)(MOTOR_X_STEP_PER_REV * Ap) / SCREW_X + 0.5f);
          //-
          if (Infeed_Value == 0)
          {
            if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + 1);
            else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
          }
          else
          {
            //OLD
            //if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
            //else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + Infeed_Value);
            //Opti
            long Infeed_Value_long = Infeed_Value * McSTEP_X;
            if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value_long);
            else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + Infeed_Value_long);
            //-
          }
          Limit_Front_LED_On();
          BeepBeep();
          //Feed_Front(a_flag, b_flag);
          NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
        }

        //Opti
      }
      //-
    }
    //OLD
    //else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
      //-
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //Feed_Right(a_flag, b_flag);
        NEW_Feed_Right(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
      }
    }
    //Opti
  }
  //----------------------------------------------------------------------------------------------------------------------
  //OLD
  //else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF)
  //Opti Выгода тут 30 байт
  else if (Motor_Z_Pos == Limit_Pos_Right)
  {
    if (Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF)
      //-
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
      Limit_Rear_LED_On();
      //Feed_Rear(a_flag, b_flag);
      NEW_Feed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
    }
    //OLD
    //else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
      //-
    {
      a_flag = false;
      b_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Left(a_flag, b_flag);
      NEW_Feed_Left(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
    }
    //Opti
  }
  //-
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void Feed_Int_Left()
{
  //OLD
  //  if ((Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF) ||
  //      (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF))
  //  {
  //Opti
  if (Motor_Z_Pos == Limit_Pos_Right)
  {
    if (Z_WORKING_FEED_FLAG == OFF && (Motor_X_Pos == Limit_Pos_Front || Motor_X_Pos == Null_X_Pos))
    {

      //-
      //OLD
      //if (cycle_flag == false && Pass_Nr <= Pass_Total)
      //Opti
      if (cycle_flag == false)
      {

        //OLD
        //else if (cycle_flag == false && Pass_Nr > Pass_Total)
        //Opti
        //Поменял местами ветки условий. (Pass_Nr > Pass_Total) - проверяется первым.
        if (Pass_Nr > Pass_Total)
          //-
        {
          a_flag = false;
          b_flag = false;

          Limit_Pos_Rear = Limit_Pos_Front - REBOUND_X;
          //Feed_Rear(a_flag, b_flag);
          NEW_Feed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ

          Limit_Front_LED_Off();
          Limit_Rear_LED_Off();
          Limit_Pos_Front = Limit_Pos_Max;
          Limit_Pos_Rear = Limit_Pos_Min;
          Pass_Total = 1;
          Pass_Nr = 1;
          Print();
        }

        //OLD
        //if (Pass_Nr <= Pass_Total)
        //Opti Вторая проверка (Pass_Nr <= Pass_Total) не проводится, а используется ELSE - т.к. 1 и 2 проверка взаимоисключающие.
        else
          //-
        {
          cycle_flag = true;
          a_flag = false;
          b_flag = false;
          //OLD
          //long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X + 0.5) * McSTEP_X;
          //Opti Выгода 18 байт (Infeed_Value тип int + умножение на McSTEP_X происходит в ветке условия
          int Infeed_Value = (int)((float)(MOTOR_X_STEP_PER_REV * Ap) / SCREW_X + 0.5f);
          //-
          if (Infeed_Value == 0)
          {
            if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - 1);
            else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
          }
          else
          {
            //OLD
            //if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
            //else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X - Infeed_Value);
            //Opti
            long Infeed_Value_long = Infeed_Value * McSTEP_X;
            if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - Infeed_Value_long);
            else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X - Infeed_Value_long);
            //-
          }
          Limit_Rear_LED_On();
          BeepBeep();
          //Feed_Rear(a_flag, b_flag);
          NEW_Feed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
        }

        //Opti
      }
      //-
    }
    //OLD
    //  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
      //-
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //Feed_Left(a_flag, b_flag);
        NEW_Feed_Left(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
      }
    }
    //Opti
  }
  //-
  //----------------------------------------------------------------------------------------------------------------
  //OLD
  //else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
  //Opti
  else if (Motor_Z_Pos == Limit_Pos_Left)
  {
    if (Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
      //-
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
      Limit_Front_LED_On();
      //Feed_Front(a_flag, b_flag);
      NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
    }
    //OLD
    //else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
      //-
    {
      a_flag = false;
      b_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Right(a_flag, b_flag);
      NEW_Feed_Right(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
    }
    //Opti
  }
  //-
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void Feed_Int_Right()
{
  //OLD
  //if ((Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF) ||
  //    (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF))
  //{
  //Opti
  if (Motor_Z_Pos == Limit_Pos_Left)
  {
    if (Z_WORKING_FEED_FLAG == OFF && (Motor_X_Pos == Limit_Pos_Front || Motor_X_Pos == Null_X_Pos))
    {
      //---
      //OLD
      //if (cycle_flag == false && Pass_Nr <= Pass_Total)
      //Opti
      if (cycle_flag == false)
      {

        //OLD
        //else if (cycle_flag == false && Pass_Nr > Pass_Total)
        //Opti
        //Поменял местами ветки условий. (Pass_Nr > Pass_Total) - проверяется первым.
        if (Pass_Nr > Pass_Total)
          //---
        {
          a_flag = false;
          b_flag = false;

          Limit_Pos_Rear = Limit_Pos_Front - REBOUND_X;
          //Feed_Rear(a_flag, b_flag);
          NEW_Feed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ

          Limit_Front_LED_Off();
          Limit_Rear_LED_Off();
          Limit_Pos_Front = Limit_Pos_Max;
          Limit_Pos_Rear = Limit_Pos_Min;
          Pass_Total = 1;
          Pass_Nr = 1;
          Print();
        }
        //OLD
        //if (Pass_Nr <= Pass_Total)
        //Opti Вторая проверка (Pass_Nr <= Pass_Total) не проводится, а используется ELSE - т.к. 1 и 2 проверка взаимоисключающие.
        else
          //-
        {
          cycle_flag = true;
          a_flag = false;
          b_flag = false;
          //OLD
          //long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X + 0.5) * McSTEP_X;
          //Opti Выгода 18 байт (Infeed_Value тип int + умножение на McSTEP_X происходит в ветке условия
          int Infeed_Value = (int)((float)(MOTOR_X_STEP_PER_REV * Ap) / SCREW_X + 0.5f);
          //-
          if (Infeed_Value == 0)
          {
            if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - 1);
            else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
          }
          else
          {
            //OLD
            //if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
            //else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X - Infeed_Value);
            //Opti
            long Infeed_Value_long = Infeed_Value * McSTEP_X;
            if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - Infeed_Value_long);
            else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X - Infeed_Value_long);
            //-
          }
          Limit_Rear_LED_On();
          BeepBeep();
          //Feed_Rear(a_flag, b_flag);
          NEW_Feed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
        }

        //Opti
      }
      //---
    }
    //OLD
    //else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
      //---
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //Feed_Right(a_flag, b_flag);
        NEW_Feed_Right(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
      }
    }
    //Opti
  }
  //---
  //------------------------------------------------------------------------------------------------------
  //OLD
  //else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
  //Opti
  else if (Motor_Z_Pos == Limit_Pos_Right)
  {
    if (Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
      //-
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
      Limit_Front_LED_On();
      //Feed_Front(a_flag, b_flag);
      NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
    }
    //OLD
    //else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
      //-
    {
      a_flag = false;
      b_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Left(a_flag, b_flag);
      NEW_Feed_Left(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
    }
    //Opti
  }
  //---
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Opti Выгода всего 18 байт. Преобразования (как у функций выше) не дают аналогичное снижение размера кода - большая часть кода оставлена дефолтной.
void Feed_Ext_Front()
{
  if ((Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Limit_Pos_Right && X_WORKING_FEED_FLAG == OFF) ||
      (Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Null_Z_Pos && X_WORKING_FEED_FLAG == OFF))
  {
    //OLD
    //if (cycle_flag == false && Pass_Nr <= Pass_Total)
    //Opti
    if (cycle_flag == false)
    {
      //OLD
      //else if (cycle_flag == false && Pass_Nr > Pass_Total)
      //Opti
      //Поменял местами ветки условий. (Pass_Nr > Pass_Total) - проверяется первым.
      if (Pass_Nr > Pass_Total)
        //---
      {
        a_flag = false;
        b_flag = false;

        Limit_Pos_Left = Limit_Pos_Right + REBOUND_Z;
        //Feed_Left(a_flag, b_flag);
        NEW_Feed_Left(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ

        Limit_Left_LED_Off();
        Limit_Right_LED_Off();
        Limit_Pos_Left = Limit_Pos_Max;                         //СБРОС ЛИМИТА !!!
        Limit_Pos_Right = Limit_Pos_Min;                        //СБРОС ЛИМИТА !!!
        Pass_Total = 1;
        Pass_Nr = 1;
        Print();
      }
      //OLD
      //if (Pass_Nr <= Pass_Total)
      //Opti Вторая проверка (Pass_Nr <= Pass_Total) не проводится, а используется ELSE - т.к. 1 и 2 проверка взаимоисключающие.
      else
        //---
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;
        //OLD
        //long Infeed_Value = (int)((float)MOTOR_Z_STEP_PER_REV * Ap / SCREW_Z + 0.5) * McSTEP_Z;
        //Opti Выгода 18 байт (Infeed_Value тип int + умножение на McSTEP_Z происходит в ветке условия
        int Infeed_Value = (int)((float)(MOTOR_Z_STEP_PER_REV * Ap) / SCREW_Z + 0.5f);
        //-
        if (Infeed_Value == 0)
        {
          if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + 1);
          else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z);
        }
        else
        {
          //OLD
          //if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + Infeed_Value);
          //else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z + Infeed_Value);
          //Opti
          long Infeed_Value_long = Infeed_Value * McSTEP_Z;
          if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + Infeed_Value_long);
          else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z + Infeed_Value_long);
          //-
        }
        Limit_Left_LED_On();
        BeepBeep();
        //Feed_Left(a_flag, b_flag);
        NEW_Feed_Left(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
      }

      //Opti
    }
    //---
  }
  else if (Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Limit_Pos_Left && Z_WORKING_FEED_FLAG == OFF)
  {
    //OLD
    //if (Pass_Nr <= Pass_Total)
    //Opti
    if (Pass_Total > Pass_Nr)
    {
      a_flag = false;
      b_flag = false;

      //Feed_Front(a_flag, b_flag);
      NEW_Feed_Front(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
    }
  }
  //OLD
  //else if (Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Limit_Pos_Left && X_WORKING_FEED_FLAG == OFF)
  //Opti
  else if (Motor_X_Pos == Limit_Pos_Front)
  {
    if (Motor_Z_Pos == Limit_Pos_Left)
      //---
    {
      if (X_WORKING_FEED_FLAG == OFF)
      {
        cycle_flag = false;
        a_flag = false;
        b_flag = false;

        Limit_Pos_Right = (Limit_Pos_Left - REBOUND_Z);
        Limit_Right_LED_On();
        //Feed_Right(a_flag, b_flag);
        NEW_Feed_Right(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
      }
    }
    //OLD
    //else if (Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Limit_Pos_Right && Z_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_Z_Pos == Limit_Pos_Right)
      //---
    {
      if (Z_WORKING_FEED_FLAG == OFF)
      {
        a_flag = false;
        b_flag = false;

        Pass_Nr++;
        Print();
        //Rapid_Feed_Rear(a_flag, b_flag);
        NEW_Feed_Rear(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
      }
    }
    //Opti
  }
  //---
}

//////////////////////////////////////////////////////////////////////////////
//Opti Выгода всего 18 байт. Преобразования (как у функций выше) не дают аналогичное снижение размера кода - большая часть кода оставлена дефолтной.
void Feed_Ext_Rear()
{
  if ((Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Limit_Pos_Right && X_WORKING_FEED_FLAG == OFF) ||
      (Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Null_Z_Pos && X_WORKING_FEED_FLAG == OFF))
  {
    //OLD
    //if (cycle_flag == false && Pass_Nr <= Pass_Total)
    //Opti
    if (cycle_flag == false)
    {
      //OLD
      //else if (cycle_flag == false && Pass_Nr > Pass_Total)
      //Opti
      //Поменял местами ветки условий. (Pass_Nr > Pass_Total) - проверяется первым.
      if (Pass_Nr > Pass_Total)
        //-
      {
        a_flag = false;
        b_flag = false;

        Limit_Pos_Left = Limit_Pos_Right + REBOUND_Z;
        //Feed_Left(a_flag, b_flag);
        NEW_Feed_Left(a_flag, b_flag, false);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ

        Limit_Left_LED_Off();                                   //ГАСИМ ИНДИКАЦИЮ ЛЕВОГО ЛИМИТА
        Limit_Right_LED_Off();                                  //ГАСИМ ИНДИКАЦИЮ ПРАВОГО ЛИМИТА
        Limit_Pos_Left = Limit_Pos_Max;                         //СБРОС ЛИМИТА !!!
        Limit_Pos_Right = Limit_Pos_Min;                        //СБРОС ЛИМИТА !!!
        Pass_Total = 1;
        Pass_Nr = 1;
        Print();
      }
      //OLD
      //if (Pass_Nr <= Pass_Total)
      //Opti Вторая проверка (Pass_Nr <= Pass_Total) не проводится, а используется ELSE - т.к. 1 и 2 проверка взаимоисключающие.
      else
        //-
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;
        //OLD
        //long Infeed_Value = (int)((float)MOTOR_Z_STEP_PER_REV * Ap / SCREW_Z + 0.5) * McSTEP_Z;
        //Opti Выгода 18 байт (Infeed_Value тип int + умножение на McSTEP_Z происходит в ветке условия
        int Infeed_Value = (int)((float)(MOTOR_Z_STEP_PER_REV * Ap) / SCREW_Z + 0.5f);
        //-
        if (Infeed_Value == 0)
        {
          if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + 1);
          else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z);
        }
        else
        {
          //OLD
          //if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + Infeed_Value);
          //else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z + Infeed_Value);
          //Opti
          long Infeed_Value_long = Infeed_Value * McSTEP_Z;
          if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + Infeed_Value_long);
          else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z + Infeed_Value_long);
          //-
        }
        Limit_Left_LED_On();
        BeepBeep();
        //Feed_Left(a_flag, b_flag);
        NEW_Feed_Left(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
      }
      //Opti
    }
    //-
  }
  else if (Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Limit_Pos_Left && Z_WORKING_FEED_FLAG == OFF)
  {
    //OLD
    //if (Pass_Nr <= Pass_Total)
    //Opti
    if (Pass_Total > Pass_Nr)
      //---
    {
      a_flag = false;
      b_flag = false;

      //Feed_Rear(a_flag, b_flag);
      NEW_Feed_Rear(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
    }
  }
  //OLD
  //else if (Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Limit_Pos_Left && X_WORKING_FEED_FLAG == OFF)
  //Opti
  else if (Motor_X_Pos == Limit_Pos_Rear)
  {
    if (Motor_Z_Pos == Limit_Pos_Left)
      //-
    {
      if (X_WORKING_FEED_FLAG == OFF)
      {
        cycle_flag = false;
        a_flag = false;
        b_flag = false;

        Limit_Pos_Right = (Limit_Pos_Left - REBOUND_Z);
        Limit_Right_LED_On();
        //Feed_Right(a_flag, b_flag);
        NEW_Feed_Right(a_flag, b_flag, FORCE_SLOW);   //ОБЫЧНЫЙ РЕЖИМ ПОДАЧИ
      }
    }
    //OLD
    //else if (Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Limit_Pos_Right && Z_WORKING_FEED_FLAG == OFF)
    //Opti
    else if (Motor_Z_Pos == Limit_Pos_Right)
      //-
    {
      if (Z_WORKING_FEED_FLAG == OFF)
      {
        a_flag = false;
        b_flag = false;

        Pass_Nr++;
        Print();
        //Rapid_Feed_Front(a_flag, b_flag);
        NEW_Feed_Front(a_flag, b_flag, FORCE_RAPID);   //РЕЖИМ БЫСТРОЙ ПОДАЧИ
      }
    }
    //Opti
  }
  //---
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void Feed_Int_Front()
{
  //
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Feed_Int_Rear()
{
  //
}
