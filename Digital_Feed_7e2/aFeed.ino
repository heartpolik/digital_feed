// ********** Режим "Асинхронная Подача" ********** //////////////////////////////////////////////////////////////////////////////////
//=====================================================================================================================================================================================================================
void NEW_aFeed_Left(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    b_flag = false;
    a_flag = true;
    Joy_X_flag = OFF;
    X_NEED_RUN_FEED_FLAG = OFF;
    X_NEED_RUN_RAPID_FLAG = OFF;

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (Z_WORKING_RAPID_FLAG == OFF)
    {
      OCR4A = max_OCR4A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;   //По своей сути это константа (после прохода секции SETUP), можно вычислить заранее
  }
  else            //ОБЫЧНАЯ ПОДАЧА
  {
    if (b_flag == true) return;
    a_flag = false;
    b_flag = true;
    Joy_X_flag = OFF;
    X_NEED_RUN_FEED_FLAG = OFF;

    //OLD
    Start_Speed = (250000 / ((uint32_t)MIN_aFEED * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1) / FEED_ACCEL;
    //-

    //Тут участок плавной раскрутки (торможения), но он работает только у левого лимита
    //  if (Motor_Z_Pos < Limit_Pos_Left - Start_Speed * 2)
    //  {

    //Большее значение OCR4A это более медленное вращение (интервал опроса таймера больше)
    //и наоборот - чем меньше значение OCR4A тем быстрее вращается (интервал опроса таймера меньше)
    //OCR4A это uint16_t, от 0 до 65535

    //OLD
    aFeed_Divisor = 250000 / ((uint32_t)aFeed_mm * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1;
    //-

    if (aFeed_Divisor < Start_Speed)          //!!!!!!!!!!!!!!!!!!!!!!!!
    {
      max_OCR4A = Start_Speed;
      if (Z_WORKING_FEED_FLAG == OFF)
      {
        OCR4A = Start_Speed;
        //Beep2();    //ОТЛАДКА
      }
    } else {
      max_OCR4A = aFeed_Divisor;
      OCR4A = aFeed_Divisor;
      //Beep10();    //ОТЛАДКА
    }
    //  } else {
    //    aFeed_Divisor = Start_Speed;
    //    max_OCR4A = Start_Speed;
    //    OCR4A = Start_Speed;
    //  }

    Brake_Compens = (max_OCR4A - aFeed_Divisor) + 1;
  }
  Limit_Pos = Limit_Pos_Left - Brake_Compens;

  Motor_Z_Dir = CW;
  Motor_Z_CW();
  if (Read_Z_Ena_State == false) Motor_Z_Enable();

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
  Ena_INT_Z_aFeed();

}
//=====================================================================================================================================================================================================================
void NEW_aFeed_Right(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    b_flag = false;
    a_flag = true;
    Joy_X_flag = OFF;
    X_NEED_RUN_FEED_FLAG = OFF;
    X_NEED_RUN_RAPID_FLAG = OFF;

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (Z_WORKING_RAPID_FLAG == OFF)
    {
      OCR4A = max_OCR4A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;
  }
  else            //ОБЫЧНАЯ ПОДАЧА
  {
    if (b_flag == true) return;
    a_flag = false;
    b_flag = true;
    Joy_X_flag = OFF;
    X_NEED_RUN_FEED_FLAG = OFF;

    //OLD
    Start_Speed = (250000 / ((uint32_t)MIN_aFEED * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1) / FEED_ACCEL;
    //-

    //Тут участок плавной раскрутки (торможения), но он работает только у левого лимита
    //  if (Motor_Z_Pos > Limit_Pos_Right + Start_Speed * 2)
    //  {

    //OLD
    aFeed_Divisor = 250000 / ((uint32_t)aFeed_mm * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1;
    //-

    if (aFeed_Divisor < Start_Speed)
    {
      max_OCR4A = Start_Speed;
      if (Z_WORKING_FEED_FLAG == OFF)
      {
        OCR4A = Start_Speed;
        //Beep2();    //ОТЛАДКА
      }
    } else {
      max_OCR4A = aFeed_Divisor;
      OCR4A = aFeed_Divisor;
      //Beep10();    //ОТЛАДКА
    }
    //  } else {
    //    aFeed_Divisor = Start_Speed;
    //    max_OCR4A = Start_Speed;
    //    OCR4A = Start_Speed;
    //  }

    Brake_Compens = (max_OCR4A - aFeed_Divisor) + 1;
  }
  Limit_Pos = Limit_Pos_Right + Brake_Compens;

  Motor_Z_Dir = CCW;
  Motor_Z_CCW();
  if (Read_Z_Ena_State == false) Motor_Z_Enable();

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
  Ena_INT_Z_aFeed();

}
//=====================================================================================================================================================================================================================
void NEW_aFeed_Front(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    b_flag = false;
    a_flag = true;
    Joy_Z_flag = OFF;
    Z_NEED_RUN_FEED_FLAG = OFF;
    Z_NEED_RUN_RAPID_FLAG = OFF;

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (X_WORKING_RAPID_FLAG == OFF)
    {
      OCR4A = max_OCR4A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;
  }
  else            //ОБЫЧНАЯ ПОДАЧА
  {
    if (b_flag == true) return;
    a_flag = false;
    b_flag = true;
    Joy_Z_flag = OFF;
    Z_NEED_RUN_FEED_FLAG = OFF;

    //OLD
    Start_Speed = (250000 / ((uint32_t)MIN_aFEED * MOTOR_X_STEP_PER_REV * McSTEP_X / ((uint32_t)60 * SCREW_X / 100) * 2) - 1) / FEED_ACCEL;
    //---

    if (Motor_X_Pos < Limit_Pos_Front - Start_Speed * 2)
    {
      //OLD
      aFeed_Divisor = 250000 / ((uint32_t)aFeed_mm * MOTOR_X_STEP_PER_REV * McSTEP_X / ((uint32_t)60 * SCREW_X / 100) * 2) - 1;
      //-

      if (aFeed_Divisor < Start_Speed)
      {
        max_OCR4A = Start_Speed;
        if (X_WORKING_FEED_FLAG == OFF)
        {
          OCR4A = Start_Speed;
        }
      } else {
        max_OCR4A = aFeed_Divisor;
        OCR4A = aFeed_Divisor;
      }
    } else {
      aFeed_Divisor = Start_Speed;
      max_OCR4A = Start_Speed;
      OCR4A = Start_Speed;
    }

    Brake_Compens = (max_OCR4A - aFeed_Divisor) + 1;
  }
  Limit_Pos = Limit_Pos_Front - Brake_Compens;

  Motor_X_Dir = CW;
  Motor_X_CW();
  if (Read_X_Ena_State == false) Motor_X_Enable();

  Joy_X_flag = ON;

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
  Ena_INT_X_aFeed();

}
//=====================================================================================================================================================================================================================
void NEW_aFeed_Rear(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    b_flag = false;
    a_flag = true;
    Joy_Z_flag = OFF;
    Z_NEED_RUN_FEED_FLAG = OFF;
    Z_NEED_RUN_RAPID_FLAG = OFF;

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (X_WORKING_RAPID_FLAG == OFF)
    {
      OCR4A = max_OCR4A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;
  }
  else            //ОБЫЧНАЯ ПОДАЧА
  {
    if (b_flag == true) return;
    a_flag = false;
    b_flag = true;
    Joy_Z_flag = OFF;
    Z_NEED_RUN_FEED_FLAG = OFF;

    //OLD
    Start_Speed = (250000 / ((uint32_t)MIN_aFEED * MOTOR_X_STEP_PER_REV * McSTEP_X / ((uint32_t)60 * SCREW_X / 100) * 2) - 1) / FEED_ACCEL;
    //-

    if (Motor_X_Pos > Limit_Pos_Rear + Start_Speed * 2)
    {
      //OLD
      aFeed_Divisor = 250000 / ((uint32_t)aFeed_mm * MOTOR_X_STEP_PER_REV * McSTEP_X / ((uint32_t)60 * SCREW_X / 100) * 2) - 1;
      //-

      if (aFeed_Divisor < Start_Speed)
      {
        max_OCR4A = Start_Speed;
        if (X_WORKING_FEED_FLAG == OFF)
        {
          OCR4A = Start_Speed;
        }
      } else {
        max_OCR4A = aFeed_Divisor;
        OCR4A = aFeed_Divisor;
      }
    } else {
      aFeed_Divisor = Start_Speed;
      max_OCR4A = Start_Speed;
      OCR4A = Start_Speed;
    }

    Brake_Compens = (max_OCR4A - aFeed_Divisor) + 1;
  }
  Limit_Pos = Limit_Pos_Rear + Brake_Compens;

  Motor_X_Dir = CCW;
  Motor_X_CCW();
  if (Read_X_Ena_State == false) Motor_X_Enable();

  Joy_X_flag = ON;

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
  Ena_INT_X_aFeed();

}
//=====================================================================================================================================================================================================================
//=====================================================================================================================================================================================================================
//=============       Режим многопроходная асинхронная подача            ==============================================================================================================================================
//=====================================================================================================================================================================================================================
//=====================================================================================================================================================================================================================

void NEW_aFeed_Ext_Left()
{ if ( Ap != 0 )
  {
    if ((Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF) ||
        (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF))
    {
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        unsigned long Infeed_Value = (int)(((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X) * McSTEP_X);
        if (Infeed_Value == 0)
        {
          if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + 1);
          else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
        }
        else
        {
          if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
          else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + (Infeed_Value * (Pass_Total - (Pass_Total - Pass_Nr)))); //
        }
        Limit_Front_LED_On();
        BeepBeep();
        //aFeed_Front(a_flag, b_flag);
        //NEW
        NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

        w = Infeed_Value;

      }

      else if (cycle_flag == false && Pass_Nr > Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X;
        //aFeed_Front(a_flag, b_flag);
        //NEW
        NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        Limit_Pos_Front = Limit_Pos_Max;
        Limit_Pos_Rear = Limit_Pos_Min;
        //if (SelectMenu != 1) {
        Pass_Total = 1;
        //}
        Pass_Nr = 1;
        Print();
        BeepComplete();

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //aFeed_Left(a_flag, b_flag);
        //NEW
        NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF)
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Rear = Limit_Pos_Front - REBOUND_X - (w * (Pass_Total - (Pass_Total - Pass_Nr)));
      Limit_Rear_LED_On();
      //aFeed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

    }

    else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Right(a_flag, b_flag);
      //NEW
      NEW_aFeed_Right(a_flag, b_flag, FORCE_RAPID);

    }

    //////////////
  } else
  {
    if (Motor_Z_Pos == Limit_Pos_Right && Z_WORKING_FEED_FLAG == OFF)
    {
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
        cycle_flag = true;

        Limit_Front_LED_On();
        Limit_Rear_LED_On();
        a_flag = false;
        b_flag = false;

        //aFeed_Left(a_flag, b_flag);
        //NEW
        NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);

        BeepBeep();
      }

      else if ( Pass_Nr > Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        //if (SelectMenu != 1) {
        Pass_Total = 1;
        //}
        Pass_Nr = 1;
        Print();
        BeepComplete();

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Left && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;
      cycle_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Right(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);

    }
    ////////
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////

void NEW_aFeed_Ext_Right()
{ if ( Ap != 0 )
  {
    if ((Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF) ||
        (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF))
    {
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        unsigned long Infeed_Value = (int)(((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X) * McSTEP_X);
        if (Infeed_Value == 0)
        {
          if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + 1);
          else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
        }
        else
        {
          if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
          else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + (Infeed_Value * (Pass_Total - (Pass_Total - Pass_Nr)))); //
        }
        Limit_Front_LED_On();
        BeepBeep();
        //aFeed_Front(a_flag, b_flag);
        //NEW
        NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

        w = Infeed_Value;

      }

      else if (cycle_flag == false && Pass_Nr > Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X;
        //aFeed_Front(a_flag, b_flag);
        //NEW
        NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        Limit_Pos_Front = Limit_Pos_Max;
        Limit_Pos_Rear = Limit_Pos_Min;
        //if (SelectMenu != 1) {
        Pass_Total = 1;
        //}
        Pass_Nr = 1;
        Print();
        BeepComplete();
      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //aFeed_Right(a_flag, b_flag);
        //NEW
        NEW_aFeed_Right(a_flag, b_flag, FORCE_SLOW);

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF)
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Rear = Limit_Pos_Front - REBOUND_X - (w * (Pass_Total - (Pass_Total - Pass_Nr)));
      Limit_Rear_LED_On();
      //aFeed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

    }

    else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Left(a_flag, b_flag);
      //NEW
      NEW_aFeed_Left(a_flag, b_flag, FORCE_RAPID);

    }

  } else
  {
    if (Motor_Z_Pos == Limit_Pos_Left && Z_WORKING_FEED_FLAG == OFF)
    {
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
        cycle_flag = true;

        Limit_Front_LED_On();
        Limit_Rear_LED_On();
        a_flag = false;
        b_flag = false;

        //aFeed_Right(a_flag, b_flag);
        //NEW
        NEW_aFeed_Right(a_flag, b_flag, FORCE_SLOW);

        BeepBeep();
      }

      else if ( Pass_Nr > Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        //if (SelectMenu != 1) {
        Pass_Total = 1;
        //}
        Pass_Nr = 1;
        Print();
        BeepComplete();

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Right && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;
      cycle_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Left(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);
    }
    ////////
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void NEW_aFeed_Int_Left()
{ if ( Ap != 0 )
  {
    if ((Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF) ||
        (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF))
    {
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        unsigned long Infeed_Value = (int)(((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X) * McSTEP_X);
        if (Infeed_Value == 0)
        {
          if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - 1);
          else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
        }
        else
        {
          if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
          else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X - (Infeed_Value * (Pass_Total - (Pass_Total - Pass_Nr)))); //
        }
        Limit_Rear_LED_On();
        BeepBeep();
        //aFeed_Rear(a_flag, b_flag);
        //NEW
        NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

        w = Infeed_Value;

      }

      else if (cycle_flag == false && Pass_Nr > Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        Limit_Pos_Rear = Limit_Pos_Front - REBOUND_X;
        //aFeed_Rear(a_flag, b_flag);
        //NEW
        NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        Limit_Pos_Front = Limit_Pos_Max;
        Limit_Pos_Rear = Limit_Pos_Min;
        //if (SelectMenu != 1) {
        Pass_Total = 1;
        //}
        Pass_Nr = 1;
        Print();
        BeepComplete();
      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //aFeed_Left(a_flag, b_flag);
        //NEW
        NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X + (w * (Pass_Total - (Pass_Total - Pass_Nr)));
      Limit_Front_LED_On();
      //aFeed_Front(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

    }

    else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Right(a_flag, b_flag);
      //NEW
      NEW_aFeed_Right(a_flag, b_flag, FORCE_RAPID);

    }

  } else
  {
    if (Motor_Z_Pos == Limit_Pos_Right && Z_WORKING_FEED_FLAG == OFF)
    {
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
        cycle_flag = true;

        Limit_Front_LED_On();
        Limit_Rear_LED_On();
        a_flag = false;
        b_flag = false;

        //aFeed_Left(a_flag, b_flag);
        //NEW
        NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);

        BeepBeep();
      }

      else if ( Pass_Nr > Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        //if (SelectMenu != 1) {
        Pass_Total = 1;
        //}
        Pass_Nr = 1;
        Print();
        BeepComplete();

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Left && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;
      cycle_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Right(a_flag, b_flag);
      //NEW
      NEW_aFeed_Right(a_flag, b_flag, FORCE_RAPID);

    }
  }
}



/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
void NEW_aFeed_Int_Right()
{ if ( Ap != 0 )
  {
    if ((Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF) ||
        (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF))
    {
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        unsigned long Infeed_Value = (int)(((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X) * McSTEP_X);
        if (Infeed_Value == 0)
        {
          if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - 1);
          else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
        }
        else
        {
          if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
          else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X - (Infeed_Value * (Pass_Total - (Pass_Total - Pass_Nr)))); //
        }
        Limit_Rear_LED_On();
        BeepBeep();
        //aFeed_Rear(a_flag, b_flag);
        //NEW
        NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

        w = Infeed_Value;

      }

      else if (cycle_flag == false && Pass_Nr > Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        Limit_Pos_Rear = Limit_Pos_Front - REBOUND_X;
        //aFeed_Rear(a_flag, b_flag);
        //NEW
        NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        Limit_Pos_Front = Limit_Pos_Max;
        Limit_Pos_Rear = Limit_Pos_Min;
        //if (SelectMenu != 1) {
        Pass_Total = 1;
        //}
        Pass_Nr = 1;
        Print();
        BeepComplete();
      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //aFeed_Right(a_flag, b_flag);
        //NEW
        NEW_aFeed_Right(a_flag, b_flag, FORCE_SLOW);

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X + (w * (Pass_Total - (Pass_Total - Pass_Nr)));
      Limit_Front_LED_On();
      //aFeed_Front(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

    }

    else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Left(a_flag, b_flag);
      //NEW
      NEW_aFeed_Left(a_flag, b_flag, FORCE_RAPID);

    }

  } else
  {
    if (Motor_Z_Pos == Limit_Pos_Left && Z_WORKING_FEED_FLAG == OFF)
    {
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
        cycle_flag = true;

        Limit_Front_LED_On();
        Limit_Rear_LED_On();
        a_flag = false;
        b_flag = false;

        //aFeed_Right(a_flag, b_flag);
        //NEW
        NEW_aFeed_Right(a_flag, b_flag, FORCE_SLOW);

        BeepBeep();
      }

      else if ( Pass_Nr > Pass_Total)
      {
        cycle_flag = true;
        a_flag = false;
        b_flag = false;

        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        //if (SelectMenu != 1) {
        Pass_Total = 1;
        //}
        Pass_Nr = 1;
        Print();
        BeepComplete();

      }
    }

    else if (Motor_Z_Pos == Limit_Pos_Right && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;
      cycle_flag = false;

      Pass_Nr++;
      Print();
      //Rapid_Feed_Left(a_flag, b_flag);
      //NEW
      NEW_aFeed_Left(a_flag, b_flag, FORCE_RAPID);

    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
void NEW_aFeed_Ext_Front()
{
  if ((Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Limit_Pos_Right && X_WORKING_FEED_FLAG == OFF) ||
      (Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Null_Z_Pos && X_WORKING_FEED_FLAG == OFF))
  {
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      a_flag = false;
      b_flag = false;

      unsigned long Infeed_Value = (int)(((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X) * McSTEP_X);
      if (Infeed_Value == 0)
      {
        if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + 1);
        else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z);
      }
      else
      {
        if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + Infeed_Value);
        else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z + Infeed_Value);
      }
      Limit_Left_LED_On();
      BeepBeep();
      //aFeed_Left(a_flag, b_flag);
      //NEW
      NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);

    }

    else if (cycle_flag == false && Pass_Nr > Pass_Total)
    {
      a_flag = false;
      b_flag = false;

      Limit_Pos_Left = Limit_Pos_Right + REBOUND_Z;
      //aFeed_Left(a_flag, b_flag);
      //NEW
      NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);

      Limit_Left_LED_Off();
      Limit_Right_LED_Off();
      Limit_Pos_Left = Limit_Pos_Max;
      Limit_Pos_Right = Limit_Pos_Min;
      //if (SelectMenu != 1) {
      Pass_Total = 1;
      //}
      Pass_Nr = 1;
      Print();
      BeepComplete();
    }
  }

  else if (Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Limit_Pos_Left && Z_WORKING_FEED_FLAG == OFF)
  {
    if (Pass_Nr <= Pass_Total)
    {
      a_flag = false;
      b_flag = false;

      //aFeed_Front(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

    }
  }

  else if (Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Limit_Pos_Left && X_WORKING_FEED_FLAG == OFF)
  {
    cycle_flag = false;
    a_flag = false;
    b_flag = false;

    Limit_Pos_Right = (Limit_Pos_Left - REBOUND_Z);
    Limit_Right_LED_On();
    //aFeed_Right(a_flag, b_flag);
    //NEW
    NEW_aFeed_Right(a_flag, b_flag, FORCE_SLOW);

  }

  else if (Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Limit_Pos_Right && Z_WORKING_FEED_FLAG == OFF)
  {
    a_flag = false;
    b_flag = false;

    Pass_Nr++;
    Print();
    //Rapid_Feed_Rear(a_flag, b_flag);
    //NEW
    NEW_aFeed_Rear(a_flag, b_flag, FORCE_RAPID);

  }
}

//////////////////////////////////////////////////////////////////////////////
void NEW_aFeed_Ext_Rear()
{
  if ((Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Limit_Pos_Right && X_WORKING_FEED_FLAG == OFF) ||
      (Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Null_Z_Pos && X_WORKING_FEED_FLAG == OFF))
  {
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      a_flag = false;
      b_flag = false;

      unsigned long Infeed_Value = (int)(((float)MOTOR_X_STEP_PER_REV * Ap / SCREW_X) * McSTEP_X);
      if (Infeed_Value == 0)
      {
        if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + 1);
        else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z);
      }
      else
      {
        if (Pass_Nr == 1) Limit_Pos_Left = (Null_Z_Pos + Infeed_Value);
        else              Limit_Pos_Left = (Limit_Pos_Right + REBOUND_Z + Infeed_Value);
      }
      Limit_Left_LED_On();
      BeepBeep();
      //aFeed_Left(a_flag, b_flag);
      //NEW
      NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);

    }

    else if (cycle_flag == false && Pass_Nr > Pass_Total)
    {
      a_flag = false;
      b_flag = false;

      Limit_Pos_Left = Limit_Pos_Right + REBOUND_Z;
      //aFeed_Left(a_flag, b_flag);
      //NEW
      NEW_aFeed_Left(a_flag, b_flag, FORCE_SLOW);

      Limit_Left_LED_Off();
      Limit_Right_LED_Off();
      Limit_Pos_Left = Limit_Pos_Max;
      Limit_Pos_Right = Limit_Pos_Min;
      //if (SelectMenu != 1) {
      Pass_Total = 1;
      //}
      Pass_Nr = 1;
      Print();
      BeepComplete();
    }
  }

  else if (Motor_X_Pos == Limit_Pos_Front && Motor_Z_Pos == Limit_Pos_Left && Z_WORKING_FEED_FLAG == OFF)
  {
    if (Pass_Nr <= Pass_Total)
    {
      a_flag = false;
      b_flag = false;

      //aFeed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

    }
  }

  else if (Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Limit_Pos_Left && X_WORKING_FEED_FLAG == OFF)
  {
    cycle_flag = false;
    a_flag = false;
    b_flag = false;

    Limit_Pos_Right = (Limit_Pos_Left - REBOUND_Z);
    Limit_Right_LED_On();
    //aFeed_Right(a_flag, b_flag);
    //NEW
    NEW_aFeed_Right(a_flag, b_flag, FORCE_SLOW);

  }

  else if (Motor_X_Pos == Limit_Pos_Rear && Motor_Z_Pos == Limit_Pos_Right && Z_WORKING_FEED_FLAG == OFF)
  {
    a_flag = false;
    b_flag = false;

    Pass_Nr++;
    Print();
    //Rapid_Feed_Front(a_flag, b_flag);
    //NEW
    NEW_aFeed_Front(a_flag, b_flag, FORCE_RAPID);

  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void NEW_aFeed_Int_Front()
{
  //
}

////////////////////////////////////////////////////////////////////////////////////////////////
void NEW_aFeed_Int_Rear()
{
  //
}
