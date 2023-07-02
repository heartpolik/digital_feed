//==============================================================================================================================================================================================================
void NEW_Cone_Left(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  //Timer4_Init()

  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    a_flag = true;
    b_flag = false;

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (Z_WORKING_RAPID_FLAG == OFF)
    {
      OCR4A = max_OCR4A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;
    Cs_Count = 0;                               //Счётчик конуса текущий - целая часть
    Cm_Count = 0;                               //Счётчик конуса текущий - десятитысячная дробная часть
  } else {                          //ОБЫЧНАЯ ПОДАЧА
    if (b_flag == true) return;
    a_flag = false;
    b_flag = true;

    Cs_Divisor = Cone_Info[Cone_Step].Cs_Div;   //Коэффициент конуса из таблицы конусов - целая часть
    Cm_Divisor = Cone_Info[Cone_Step].Cm_Div;   //Коэффициент конуса из таблицы конусов - десятитысячная дробная часть
    //NEW
    XZ_Divisor = Cone_Info[Cone_Step].XZ;

    #ifdef _DEBUG_CONE
    Serial.print("Cone_Left "); Serial.print(Cs_Divisor); Serial.print("."); Serial.print(Cm_Divisor); Serial.print(" XZ="); Serial.print(XZ_Divisor); Serial.print("\n\r");
    #endif

    //OLD
    Start_Speed = (250000 / ((uint32_t)MIN_aFEED * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1) /FEED_ACCEL;
    //-

    if (Motor_Z_Pos < Limit_Pos_Left - Start_Speed * 2)
    {
      //OLD
      aFeed_Divisor = 250000 / ((uint32_t)aFeed_mm * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1;
      //-

      if (aFeed_Divisor < Start_Speed)                          //Feed_Divisor везде заменён на aFeed_Divisor
      {
        max_OCR4A = Start_Speed;                                //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
        if (Z_WORKING_FEED_FLAG == OFF)
        {
          OCR4A = Start_Speed;                                  //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
        }
      }
      else
      {
        max_OCR4A = aFeed_Divisor;                               //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
        OCR4A = aFeed_Divisor;                                   //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
      }
    }
    else
    {
      aFeed_Divisor = Start_Speed;
      max_OCR4A = Start_Speed;                                  //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
      OCR4A = Start_Speed;                                      //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
    }
    Brake_Compens = max_OCR4A - aFeed_Divisor + 1;               //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
  }
  Limit_Pos = Limit_Pos_Left - Brake_Compens;

  Motor_Z_Dir = CW;
  Motor_Z_CW();
  if (Read_Z_Ena_State == false) Motor_Z_Enable();

  if (Mode == Mode_Cone_L)
  {
    Motor_X_Dir = CW;
    Motor_X_CW();
  } else if (Mode == Mode_Cone_R)
  {
    Motor_X_Dir = CCW;
    Motor_X_CCW();
  }

  if (Read_X_Ena_State == false) Motor_X_Enable();

  Joy_Z_flag = ON;
  X_WORKING_FEED_FLAG = ON;

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
  Ena_INT_Z_aCone();                                          //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4C
}
//==============================================================================================================================================================================================================
void NEW_Cone_Right(bool & a_flag, bool & b_flag, byte CurrentSpeedMode)
{
  //Timer4_Init()

  if (CurrentSpeedMode == FORCE_RAPID)          //БЫСТРАЯ ПОДАЧА ПРИНУДИТЕЛЬНАЯ
  {
    if (a_flag == true) return;
    a_flag = true;
    b_flag = false;

    //NEW На быстрой подаче стартуем сразу с минимальной скоростью MIN_RAPID_MOTION
    if (Z_WORKING_RAPID_FLAG == OFF)
    {
      OCR4A = max_OCR4A = (unsigned int)MIN_RAPID_MOTION;
    }
    //---

    Brake_Compens = (MIN_RAPID_MOTION - MAX_RAPID_MOTION) * REPEAt + 1;
    Cs_Count = 0;
    Cm_Count = 0;

  } else {            //ОБЫЧНАЯ ПОДАЧА
    if (b_flag == true) return;
    a_flag = false;
    b_flag = true;

    Cs_Divisor = Cone_Info[Cone_Step].Cs_Div;
    Cm_Divisor = Cone_Info[Cone_Step].Cm_Div;
    //NEW
    XZ_Divisor = Cone_Info[Cone_Step].XZ;

    #ifdef _DEBUG_CONE
    Serial.print("Cone_Left "); Serial.print(Cs_Divisor); Serial.print("."); Serial.print(Cm_Divisor); Serial.print(" XZ="); Serial.print(XZ_Divisor); Serial.print("\n\r");
    #endif

    //OLD
    Start_Speed = (250000 / ((uint32_t)MIN_aFEED * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1) /FEED_ACCEL;
    //-

    if (Motor_Z_Pos > Limit_Pos_Right + Start_Speed * 2)
    {
      //OLD
      aFeed_Divisor = 250000 / ((uint32_t)aFeed_mm * MOTOR_Z_STEP_PER_REV * McSTEP_Z / ((uint32_t)60 * SCREW_Z / 100) * 2) - 1;
      //-

      if (aFeed_Divisor < Start_Speed)                          //Feed_Divisor везде заменён на aFeed_Divisor
      {
        max_OCR4A = Start_Speed;                                //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
        if (Z_WORKING_FEED_FLAG == OFF)
        {
          OCR4A = Start_Speed;                                  //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
        }
      }
      else
      {
        max_OCR4A = aFeed_Divisor;                               //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
        OCR4A = aFeed_Divisor;                                   //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
      }
    }
    else
    {
      aFeed_Divisor = Start_Speed;
      max_OCR4A = Start_Speed;                                  //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
      OCR4A = Start_Speed;                                      //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
    }
    Brake_Compens = max_OCR4A - aFeed_Divisor + 1;               //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4A
  }
  Limit_Pos = Limit_Pos_Right + Brake_Compens;

  Motor_Z_Dir = CCW;
  Motor_Z_CCW();
  if (Read_Z_Ena_State == false) Motor_Z_Enable();

  if (Mode == Mode_Cone_L)
  {
    Motor_X_Dir = CCW;
    Motor_X_CCW();
  } else if (Mode == Mode_Cone_R)
  {
    Motor_X_Dir = CW;
    Motor_X_CW();
  }
  if (Read_X_Ena_State == false) Motor_X_Enable();

  Joy_Z_flag = ON;
  X_WORKING_FEED_FLAG = ON;   //В режиме КОНУСОВ активируются оба мотора

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

  Ena_INT_Z_aCone();                                          //Изменяем для КОНУСОВ синхронный таймер OCR5A на асинхронный OCR4C
}
//==============================================================================================================================================================================================================
/*
  void Cone_Front(bool & a_flag, bool & b_flag)
  {
  if (b_flag == true) return;
  a_flag = false;
  b_flag = true;
  }
*/
//==============================================================================================================================================================================================================
/*
  void Cone_Rear(bool & a_flag, bool & b_flag)
  {
  if (b_flag == true) return;
  a_flag = false;
  b_flag = true;
  }
*/
//==============================================================================================================================================================================================================
//===========================================================================================
//================************многопроходный конус**************=============================
//===========================================================================================


  void NEW_Cone_Ext_Left()
  {
  if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF)
  {
    Cone_qStep = 0;
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      a_flag = false;
      b_flag = false;

      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      if (Infeed_Value == 0)
      {
        if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + 1);
        else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
      }
      else
      {
        if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
        else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + Infeed_Value);
      }
      Limit_Front_LED_On();
      BeepBeep();
      //Feed_Front(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF && Cone_qStep != 6)
  {
    if (Pass_Nr <= Pass_Total)
    {
      a_flag = false;
      b_flag = false;

      //Cone_Left(a_flag, b_flag);
      //NEW
      NEW_Cone_Left(a_flag, b_flag, FORCE_SLOW);

      Cone_qStep = 1;
    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Left && Cone_qStep == 1)
  {
    Motor_Z_Pos = Limit_Pos_Left;
    Motor_X_Pos = Limit_Pos_Front;
    Cone_qStep = 2;
  }
  else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && Cone_qStep == 2)
  {
    cycle_flag = false;
    a_flag = false;
    b_flag = false;

    Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
    Limit_Rear_LED_On();
    //Feed_Rear(a_flag, b_flag);
    //NEW
    NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

    Cone_qStep = 3;
  }
  else if (Motor_Z_Pos == Limit_Pos_Left && Cone_qStep == 3 && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
  {
    a_flag = false;
    b_flag = false;
    //Rapid_Cone_Right(a_flag, b_flag);
    //NEW
    NEW_Cone_Right(a_flag, b_flag, FORCE_RAPID);

    Cone_qStep = 4;
    Pass_Nr++;
  }
  else if (Motor_Z_Pos == Limit_Pos_Right && Cone_qStep == 4 && Z_WORKING_FEED_FLAG == OFF)
  {
    Motor_Z_Pos = Limit_Pos_Right;
    Motor_X_Pos = Limit_Pos_Rear;
    Cone_qStep = 5;
  }
  else if (Motor_Z_Pos == Limit_Pos_Right && Cone_qStep == 5 && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
  {
    if (Pass_Total - Pass_Nr + 1 > 0)
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;
      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X) + Infeed_Value;
      Limit_Front_LED_On();
      //Feed_Front(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

      BeepBeep();
      Print();
    }
    else     {
      Cone_qStep = 6;
      a_flag = false;
      b_flag = false;
      Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X;
      Limit_Front_LED_Off();
      Limit_Rear_LED_Off();
      Pass_Total = 1;
      Pass_Nr = 1;
      //Feed_Front(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

      BeepComplete();
      Print();
    }
    if (Cone_qStep == 6)
    {
      Limit_Pos_Front = Limit_Pos_Max;
      Limit_Pos_Rear = Limit_Pos_Min;
    }
  }
  }


/*
//Простенькая оптимизация ~ -300 байт
void NEW_Cone_Ext_Left()
{
  if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF)
  {
    Cone_qStep = 0;
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      a_flag = false;
      b_flag = false;

      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      if (Infeed_Value == 0)
      {
        if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + 1);
        else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
      }
      else
      {
        if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
        else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + Infeed_Value);
      }
      Limit_Front_LED_On();
      BeepBeep();
      //Feed_Front(a_flag, b_flag);
      //NEW
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

    }
  } else if (Cone_qStep != 6)
  {
    if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
    {
      if (Pass_Nr <= Pass_Total)
      {
        a_flag = false;
        b_flag = false;

        //Cone_Left(a_flag, b_flag);
        //NEW
        NEW_Cone_Left(a_flag, b_flag, FORCE_SLOW);

        Cone_qStep = 1;
      }
    }

  } else if (Cone_qStep == 1)
  {
    if (Motor_Z_Pos == Limit_Pos_Left)
    {
      Motor_Z_Pos = Limit_Pos_Left;
      Motor_X_Pos = Limit_Pos_Front;
      Cone_qStep = 2;
    }

  } else if (Cone_qStep == 2)
  {
    if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front)
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;

      Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
      Limit_Rear_LED_On();
      //Feed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

      Cone_qStep = 3;
    }

  } else if (Cone_qStep == 3)
  {
    if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
    {
      a_flag = false;
      b_flag = false;
      //Rapid_Cone_Right(a_flag, b_flag);
      //NEW
      NEW_Cone_Right(a_flag, b_flag, FORCE_RAPID);

      Cone_qStep = 4;
      Pass_Nr++;
    }

  } else if (Cone_qStep == 4)
  {
    if (Motor_Z_Pos == Limit_Pos_Right && Z_WORKING_FEED_FLAG == OFF)
    {
      Motor_Z_Pos = Limit_Pos_Right;
      Motor_X_Pos = Limit_Pos_Rear;
      Cone_qStep = 5;
    }

  } else if (Cone_qStep == 5)
  {
    if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
    {
      if (Pass_Total - Pass_Nr + 1 > 0)
      {
        cycle_flag = false;
        a_flag = false;
        b_flag = false;
        unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
        Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X) + Infeed_Value;
        Limit_Front_LED_On();
        //Feed_Front(a_flag, b_flag);
        //NEW
        NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

        BeepBeep();
        Print();
      }
      else     {
        Cone_qStep = 6;
        a_flag = false;
        b_flag = false;
        Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X;
        Limit_Front_LED_Off();
        Limit_Rear_LED_Off();
        Pass_Total = 1;
        Pass_Nr = 1;
        //Feed_Front(a_flag, b_flag);
        //NEW
        NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

        BeepComplete();
        Print();
      }
      if (Cone_qStep == 6)
      {
        Limit_Pos_Front = Limit_Pos_Max;
        Limit_Pos_Rear = Limit_Pos_Min;
      }
    }
  }


}
*/
////////////////////////////////////////////////////////////////////////////////////////////////
void NEW_Cone_Ext_Right()
{
  if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF)
  {
    Cone_qStep = 0;
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      a_flag = false;
      b_flag = false;

      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      if (Infeed_Value == 0)
      {
        if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + 1);
        else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
      }
      else
      {
        if (Pass_Nr == 1) Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
        else              Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X + Infeed_Value);
      }
      Limit_Front_LED_On();
      BeepBeep();
      //Feed_Front(a_flag, b_flag);
      
      //NEW
      #ifdef _DEBUG_CONE
      Serial.print("NEW_Cone_Ext_Right 0...\n\r");
      #endif
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);
    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF && Cone_qStep != 6)
  {
    if (Pass_Nr <= Pass_Total)
    {
      a_flag = false;
      b_flag = false;

      //Cone_Right(a_flag, b_flag);
      //NEW
      #ifdef _DEBUG_CONE
      Serial.print("NEW_Cone_Ext_Right !=6...\n\r");
      #endif
      NEW_Cone_Right(a_flag, b_flag, FORCE_SLOW);

      Cone_qStep = 1;
    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Cone_qStep == 1)
  {
    Motor_Z_Pos = Limit_Pos_Right;
    Motor_X_Pos = Limit_Pos_Front;
    Cone_qStep = 2;
    #ifdef _DEBUG_CONE
    Serial.print("NEW_Cone_Ext_Right 1...\n\r");
    #endif
  }
  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front && Cone_qStep == 2)
  {
    cycle_flag = false;
    a_flag = false;
    b_flag = false;

    Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X);
    Limit_Rear_LED_On();
    //Feed_Rear(a_flag, b_flag);
    //NEW
    #ifdef _DEBUG_CONE
    Serial.print("NEW_Cone_Ext_Right 2...\n\r");
    #endif
    NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

    Cone_qStep = 3;
  }
  else if (Motor_Z_Pos == Limit_Pos_Right && Cone_qStep == 3 && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF)
  {
    a_flag = false;
    b_flag = false;
    //Rapid_Cone_Left(a_flag, b_flag);
    //NEW
    #ifdef _DEBUG_CONE
    Serial.print("NEW_Cone_Ext_Right 3...\n\r");
    #endif
    NEW_Cone_Left(a_flag, b_flag, FORCE_RAPID);

    Cone_qStep = 4;
    Pass_Nr++;
  }
  else if (Motor_Z_Pos == Limit_Pos_Left && Cone_qStep == 4 && Z_WORKING_FEED_FLAG == OFF)
  {
    Motor_Z_Pos = Limit_Pos_Left;
    Motor_X_Pos = Limit_Pos_Rear;
    #ifdef _DEBUG_CONE
    Serial.print("NEW_Cone_Ext_Right 4...\n\r");
    #endif
    Cone_qStep = 5;
  }
  else if (Motor_Z_Pos == Limit_Pos_Left && Cone_qStep == 5 && Motor_X_Pos == Limit_Pos_Rear && Z_WORKING_FEED_FLAG == OFF)
  {
    if (Pass_Total - Pass_Nr + 1 > 0 )
    { cycle_flag = false;
      a_flag = false;
      b_flag = false;
      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X) + Infeed_Value;
      Limit_Front_LED_On();
      BeepBeep();
      //Feed_Front(a_flag, b_flag);
      //NEW
      #ifdef _DEBUG_CONE
      Serial.print("NEW_Cone_Ext_Right 5...\n\r");
      #endif
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

      Print();
    }
    else {
      Cone_qStep = 6;
      a_flag = false;
      b_flag = false;
      Limit_Pos_Front = Limit_Pos_Rear + REBOUND_X;
      Limit_Front_LED_Off();
      Limit_Rear_LED_Off();
      Pass_Total = 1;
      Pass_Nr = 1;
      //Feed_Front(a_flag, b_flag);
      //NEW
      #ifdef _DEBUG_CONE
      Serial.print("NEW_Cone_Ext_Right 6...\n\r");
      #endif
      NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

      BeepComplete();
      Print();
    }
    if (Cone_qStep == 6)
    {
      #ifdef _DEBUG_CONE
      Serial.print("NEW_Cone_Ext_Right 6-2...\n\r");
      #endif
      Limit_Pos_Front = Limit_Pos_Max;
      Limit_Pos_Rear = Limit_Pos_Min;
    }

  }
}
///////////////////////////////////////////////////////////////////////////////////////////////
void NEW_Cone_Int_Left()
{
  if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF)
  {
    Cone_qStep = 0;
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      a_flag = false;
      b_flag = false;

      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      if (Infeed_Value == 0)
      {
        if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos + 1);
        else              Limit_Pos_Rear = (Limit_Pos_Rear + REBOUND_X);
      }
      else
      {
        if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
        else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X - Infeed_Value);
      }
      Limit_Rear_LED_On();
      BeepBeep();
      //Feed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF && Cone_qStep != 6)
  {
    if (Pass_Nr <= Pass_Total)
    {
      a_flag = false;
      b_flag = false;

      //Cone_Left(a_flag, b_flag);
      //NEW
      NEW_Cone_Left(a_flag, b_flag, FORCE_SLOW);

      Cone_qStep = 1;
    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Left && Cone_qStep == 1)
  {
    Motor_Z_Pos = Limit_Pos_Left;
    Motor_X_Pos = Limit_Pos_Rear;
    Cone_qStep = 2;
  }
  else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && Cone_qStep == 2)
  {
    cycle_flag = false;
    a_flag = false;
    b_flag = false;

    Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
    Limit_Front_LED_On();
    //Feed_Front(a_flag, b_flag);
    //NEW
    NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

    Cone_qStep = 3;
  }
  else if (Motor_Z_Pos == Limit_Pos_Left && Cone_qStep == 3 && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
  {
    a_flag = false;
    b_flag = false;
    //Rapid_Cone_Right(a_flag, b_flag);
    //NEW
    NEW_Cone_Right(a_flag, b_flag, FORCE_RAPID);

    Cone_qStep = 4;
    Pass_Nr++;
  }
  else if (Motor_Z_Pos == Limit_Pos_Right && Cone_qStep == 4 && Z_WORKING_FEED_FLAG == OFF)
  {
    Motor_Z_Pos = Limit_Pos_Right;
    Motor_X_Pos = Limit_Pos_Front;
    Cone_qStep = 5;
  }
  else if (Motor_Z_Pos == Limit_Pos_Right && Cone_qStep == 5 && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF)
  {
    if (Pass_Total - Pass_Nr + 1 > 0 )
    { cycle_flag = false;
      a_flag = false;
      b_flag = false;
      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X) - Infeed_Value;
      Limit_Rear_LED_On();
      //Feed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

      BeepBeep();
      Print();
    }
    else {
      Cone_qStep = 6;
      a_flag = false;
      b_flag = false;
      Limit_Pos_Rear = Limit_Pos_Front - REBOUND_X;
      Limit_Front_LED_Off();
      Limit_Rear_LED_Off();
      Pass_Total = 1;
      Pass_Nr = 1;
      //Feed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

      BeepComplete();
      Print();
    }
    if (Cone_qStep == 6)
    {
      Limit_Pos_Front = Limit_Pos_Max;
      Limit_Pos_Rear = Limit_Pos_Min;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void NEW_Cone_Int_Right()
{
  if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Null_X_Pos && Z_WORKING_FEED_FLAG == OFF)
  {
    Cone_qStep = 0;
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      a_flag = false;
      b_flag = false;

      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      if (Infeed_Value == 0)
      {
        if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos + 1);
        else              Limit_Pos_Rear = (Limit_Pos_Rear + REBOUND_X);
      }
      else
      {
        if (Pass_Nr == 1) Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
        else              Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X - Infeed_Value);
      }
      Limit_Rear_LED_On();
      BeepBeep();
      //Feed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear && X_WORKING_FEED_FLAG == OFF && Cone_qStep != 6)
  {
    if (Pass_Nr <= Pass_Total)
    {
      a_flag = false;
      b_flag = false;

      //Cone_Right(a_flag, b_flag);
      //NEW
      NEW_Cone_Right(a_flag, b_flag, FORCE_SLOW);

      Cone_qStep = 1;
    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Cone_qStep == 1)
  {
    Motor_Z_Pos = Limit_Pos_Right;
    Motor_X_Pos = Limit_Pos_Rear;
    Cone_qStep = 2;
  }
  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear && Cone_qStep == 2)
  {
    cycle_flag = false;
    a_flag = false;
    b_flag = false;

    Limit_Pos_Front = (Limit_Pos_Rear + REBOUND_X);
    Limit_Front_LED_On();
    //Feed_Front(a_flag, b_flag);
    //NEW
    NEW_aFeed_Front(a_flag, b_flag, FORCE_SLOW);

    Cone_qStep = 3;
  }
  else if (Motor_Z_Pos == Limit_Pos_Right && Cone_qStep == 3 && Motor_X_Pos == Limit_Pos_Front && X_WORKING_FEED_FLAG == OFF)
  {
    a_flag = false;
    b_flag = false;
    //Rapid_Cone_Left(a_flag, b_flag);
    //NEW
    NEW_Cone_Left(a_flag, b_flag, FORCE_RAPID);

    Cone_qStep = 4;
    Pass_Nr++;
  }
  else if (Motor_Z_Pos == Limit_Pos_Left && Cone_qStep == 4 && Z_WORKING_FEED_FLAG == OFF)
  {
    Motor_Z_Pos = Limit_Pos_Left;
    Motor_X_Pos = Limit_Pos_Front;
    Cone_qStep = 5;
  }
  else if (Motor_Z_Pos == Limit_Pos_Left && Cone_qStep == 5 && Motor_X_Pos == Limit_Pos_Front && Z_WORKING_FEED_FLAG == OFF)
  {
    if (Pass_Total - Pass_Nr + 1 > 0 )
    {
      cycle_flag = false;
      a_flag = false;
      b_flag = false;
      unsigned long Infeed_Value = (int)((float)MOTOR_X_STEP_PER_REV * (Ap / 2) / SCREW_X + 0.5) * McSTEP_X;
      Limit_Pos_Rear = (Limit_Pos_Front - REBOUND_X) - Infeed_Value;
      Limit_Rear_LED_On();
      //Feed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

      BeepBeep();
      Print();
    }
    else {
      Cone_qStep = 6;
      a_flag = false;
      b_flag = false;
      Limit_Pos_Rear = Limit_Pos_Front - REBOUND_X;
      Limit_Front_LED_Off();
      Limit_Rear_LED_Off();
      Pass_Total = 1;
      Pass_Nr = 1;
      //Feed_Rear(a_flag, b_flag);
      //NEW
      NEW_aFeed_Rear(a_flag, b_flag, FORCE_SLOW);

      BeepComplete();
      Print();
    }
    if (Cone_qStep == 6)
    { Limit_Pos_Front = Limit_Pos_Max;
      Limit_Pos_Rear = Limit_Pos_Min;
    }
  }

}
