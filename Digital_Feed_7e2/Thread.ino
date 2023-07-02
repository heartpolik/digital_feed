//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Режим "Резьба" ********** //////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Thread_Left(bool & c_flag, bool & d_flag)
{
  if (c_flag == true) return;
  d_flag = false;
  c_flag = true;

  Joy_X_flag = OFF;
  //OLD
  //if (Motor_Z_Pos < (Limit_Pos_Left - (THRD_ACCEL * REPEAt ) * 2))
  //Opti
  int THRD_ACCEL_REPEAt = THRD_ACCEL * REPEAt;
  if (Motor_Z_Pos < (Limit_Pos_Left - THRD_ACCEL_REPEAt * 2))
    //-
  {
    Ks_Divisor = Thread_Info[Thread_Step].Ks_Div_Z;
    if (tmp_Ks_Divisor != Ks_Divisor)
    {
      //tmp_Accel = THRD_ACCEL + Ks_Divisor;
      //tmp_Ks_Divisor = THRD_ACCEL + Ks_Divisor;
      tmp_Ks_Divisor = tmp_Accel = THRD_ACCEL + Ks_Divisor;               //Opti: короче запись
    }
    //OLD
    //Brake_Compens = THRD_ACCEL * REPEAt + 1;
    //Opti
    Brake_Compens = THRD_ACCEL_REPEAt + 1;
    //-
  } else {
    //OLD
    //Ks_Divisor = THRD_ACCEL + Thread_Info[0].Ks_Div_Z;
    //tmp_Accel = Ks_Divisor;
    //tmp_Ks_Divisor = Ks_Divisor;
    //Opti
    tmp_Ks_Divisor = tmp_Accel = Ks_Divisor = THRD_ACCEL + Thread_Info[0].Ks_Div_Z;     //Opti: короче запись
    //-
    //Brake_Compens = tmp_Accel - Ks_Divisor + 1;   //Оп. что за нелогичность? tmp_Accel - Ks_Divisor = 0!!!
    Brake_Compens = 1;                                //Opti: Оп. что за нелогичность? tmp_Accel - Ks_Divisor = 0!!! Brake_Compens всегда 1
  }

  Km_Divisor = Thread_Info[Thread_Step].Km_Div_Z;
  Ks_Count = 0;
  Km_Count = 0;
  Limit_Pos = Limit_Pos_Left - Brake_Compens;

  Motor_Z_Dir = CW;
  Motor_Z_CW();
  if (Read_Z_Ena_State == false) Motor_Z_Enable();
  Joy_Z_flag = ON;
}


void Thread_Right(bool & c_flag, bool & d_flag)
{
  if (d_flag == true) return;
  c_flag = false;
  d_flag = true;

  Joy_X_flag = OFF;
  //OLD
  //if (Motor_Z_Pos > Limit_Pos_Right + THRD_ACCEL * REPEAt * 2 || Motor_Z_Pos <= Limit_Pos_Right)
  //Opti
  int THRD_ACCEL_REPEAt = THRD_ACCEL * REPEAt;
  if (Motor_Z_Pos > Limit_Pos_Right + THRD_ACCEL_REPEAt * 2 || Motor_Z_Pos <= Limit_Pos_Right)
    //-
  {
    Ks_Divisor = Thread_Info[Thread_Step].Ks_Div_Z;
    if (tmp_Ks_Divisor != Ks_Divisor)
    {
      //tmp_Accel = THRD_ACCEL + Ks_Divisor;
      //tmp_Ks_Divisor = THRD_ACCEL + Ks_Divisor;
      tmp_Ks_Divisor = tmp_Accel = THRD_ACCEL + Ks_Divisor;               //Opti: короче запись
    }
    //Brake_Compens = THRD_ACCEL * REPEAt + 1;
    Brake_Compens = THRD_ACCEL_REPEAt + 1;                                //Opti: короче запись
  }
  else
  {
    //OLD
    //Ks_Divisor = THRD_ACCEL + Thread_Info[0].Ks_Div_Z;
    //tmp_Accel = Ks_Divisor;
    //tmp_Ks_Divisor = Ks_Divisor;
    //Opti
    tmp_Ks_Divisor = tmp_Accel = Ks_Divisor = THRD_ACCEL + Thread_Info[0].Ks_Div_Z;   //Opti: короче запись
    //OLD
    //Brake_Compens = tmp_Accel - Ks_Divisor + 1;                                  //Opti: Оп. что за нелогичность? tmp_Accel - Ks_Divisor = 0!!! Brake_Compens всегда 1
    //Opti
    Brake_Compens = 1;                                                            //Opti: Оп. что за нелогичность? tmp_Accel - Ks_Divisor = 0!!! Brake_Compens всегда 1
    //-
  }

  Km_Divisor = Thread_Info[Thread_Step].Km_Div_Z;
  Ks_Count = 0;
  Km_Count = 0;
  Limit_Pos = Limit_Pos_Right + Brake_Compens;

  Motor_Z_Dir = CCW;
  Motor_Z_CCW();
  if (Read_Z_Ena_State == false) Motor_Z_Enable();
  Joy_Z_flag = ON;
}


void Thread_Front(bool & c_flag, bool & d_flag)
{
  if (c_flag == true) return;
  d_flag = false;
  c_flag = true;

  Joy_Z_flag = OFF;
  //OLD
  //if (Motor_X_Pos < (Limit_Pos_Front - (THRD_ACCEL * REPEAt) * 2))
  //Opti
  int THRD_ACCEL_REPEAt = THRD_ACCEL * REPEAt;
  if (Motor_X_Pos < (Limit_Pos_Front - THRD_ACCEL_REPEAt * 2))
    //-
  {

    if (Sub_Mode_Thread == Sub_Mode_Thread_Man) {
      Ks_Divisor = Thread_Info[Thread_Step].Ks_Div_X;
      Km_Divisor = Thread_Info[Thread_Step].Km_Div_X;
    } else {
      //OLD
      //Ks_Divisor = Thread_Info[Thread_Step].Ks_Div_Z;
      //Km_Divisor = Thread_Info[Thread_Step].Km_Div_Z;
      //Ks_Divisor = (Ks_Divisor + (float)(Km_Divisor + 5000) / 10000) * ((float)McSTEP_Z / McSTEP_X);
      //Km_Divisor = 0;
      //Opti: короче запись
      Ks_Divisor = (Thread_Info[Thread_Step].Ks_Div_Z + (float)(Thread_Info[Thread_Step].Km_Div_Z + 5000) / 10000) * ((float)McSTEP_Z / McSTEP_X);
      Km_Divisor = 0;
      //-
    }

    if (tmp_Ks_Divisor != Ks_Divisor)
    {
      //OLD
      //tmp_Accel = THRD_ACCEL + Ks_Divisor;
      //tmp_Ks_Divisor = THRD_ACCEL + Ks_Divisor;
      //Opti
      tmp_Ks_Divisor = tmp_Accel = THRD_ACCEL + Ks_Divisor;                  //Opti: короче запись
      //-
    }
    //OLD
    //Brake_Compens = THRD_ACCEL * REPEAt + 1;
    //Opti
    Brake_Compens = THRD_ACCEL_REPEAt + 1;
    //-
  } else {
    //OLD
    //Ks_Divisor = THRD_ACCEL + Thread_Info[0].Ks_Div_X;
    //Km_Divisor = 0;
    //tmp_Accel = Ks_Divisor;
    //tmp_Ks_Divisor = Ks_Divisor;
    //Opti                                                                    //Opti: короче запись
    tmp_Ks_Divisor = tmp_Accel = Ks_Divisor = THRD_ACCEL + Thread_Info[0].Ks_Div_X;
    Km_Divisor = 0;
    //-
    //OLD
    //Brake_Compens = tmp_Accel - Ks_Divisor + 1;                                  //Opti: Оп. что за нелогичность? tmp_Accel - Ks_Divisor = 0!!! Brake_Compens всегда 1
    //Opti
    Brake_Compens = 1;                                                            //Opti: Оп. что за нелогичность? tmp_Accel - Ks_Divisor = 0!!! Brake_Compens всегда 1
    //-
  }

  Ks_Count = 0;
  Km_Count = 0;
  Limit_Pos = Limit_Pos_Front - Brake_Compens;

  Motor_X_Dir = CW;
  Motor_X_CW();
  if (Read_X_Ena_State == false) Motor_X_Enable();
  Joy_X_flag = ON;
}


void Thread_Rear(bool & c_flag, bool & d_flag)
{
  if (d_flag == true) return;
  c_flag = false;
  d_flag = true;

  Joy_Z_flag = OFF;
  //OLD
  //if (Motor_X_Pos > (Limit_Pos_Rear + (THRD_ACCEL * REPEAt) * 2))
  //Opti
  int THRD_ACCEL_REPEAt = THRD_ACCEL * REPEAt;
  if (Motor_X_Pos > (Limit_Pos_Rear + THRD_ACCEL_REPEAt * 2))
    //-
  {
    if (Sub_Mode_Thread == Sub_Mode_Thread_Man) {
      Ks_Divisor = Thread_Info[Thread_Step].Ks_Div_X;
      Km_Divisor = Thread_Info[Thread_Step].Km_Div_X;
    } else {
      //OLD
      //Ks_Divisor = Thread_Info[Thread_Step].Ks_Div_Z;
      //Km_Divisor = Thread_Info[Thread_Step].Km_Div_Z;
      //Ks_Divisor = (Ks_Divisor + (float)(Km_Divisor + 5000) / 10000) * ((float)McSTEP_Z / McSTEP_X);
      //Km_Divisor = 0;
      //Opti                  //Opti: короче запись
      Ks_Divisor = (Thread_Info[Thread_Step].Ks_Div_Z + (float)(Thread_Info[Thread_Step].Km_Div_Z + 5000) / 10000) * ((float)McSTEP_Z / McSTEP_X);
      Km_Divisor = 0;
      //-
    }
    if (tmp_Ks_Divisor != Ks_Divisor)
    {
      //OLD
      //tmp_Accel = THRD_ACCEL + Ks_Divisor;
      //tmp_Ks_Divisor = THRD_ACCEL + Ks_Divisor;
      //Opti
      tmp_Ks_Divisor = tmp_Accel = THRD_ACCEL + Ks_Divisor;                  //Opti: короче запись
      //-
    }
    //OLD
    //Brake_Compens = THRD_ACCEL * REPEAt + 1;
    //Opti
    Brake_Compens = THRD_ACCEL_REPEAt + 1;                  //Opti: короче запись
    //-
  } else {
    //OLD
    //Ks_Divisor = THRD_ACCEL + Thread_Info[0].Ks_Div_X;
    //Km_Divisor = 0;
    //tmp_Accel = Ks_Divisor;
    //tmp_Ks_Divisor = Ks_Divisor;
    //Brake_Compens = tmp_Accel - Ks_Divisor + 1;
    //Opti
    Ks_Divisor = tmp_Ks_Divisor = tmp_Accel = THRD_ACCEL + Thread_Info[0].Ks_Div_X;     //Opti: короче запись
    Km_Divisor = 0;
    Brake_Compens = 1;                                                                  //Opti: Оп. что за нелогичность? tmp_Accel - Ks_Divisor = 0!!! Brake_Compens всегда 1
    //-
  }

  Ks_Count = 0;
  Km_Count = 0;
  Limit_Pos = Limit_Pos_Rear + Brake_Compens;

  Motor_X_Dir = CCW;
  Motor_X_CCW();
  if (Read_X_Ena_State == false) Motor_X_Enable();
  Joy_X_flag = ON;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Режим "Цикл Резьба" ********** /////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ORIGINAL
/*
  void Thread_Ext_Left()
  {
   if ((Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear) || (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos))
   {
      Pass_Total = Thread_Info[Thread_Step].Pass;
      if (cycle_flag == false && Pass_Nr <= Pass_Total)
      {
         cycle_flag = true;
         c_flag = false;
         d_flag = false;

         float Step_mm = Thread_Info[Thread_Step].Step;
         float Pass_Depth;
         if(Pass_Nr == 1) {Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 6) - (Step_mm * 0.866 / 8)) / sqrt(Pass_Total-1) * sqrt(0.3);}
         else             {Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 6) - (Step_mm * 0.866 / 8)) / sqrt(Pass_Total-1) * sqrt(Pass_Nr-1);}
         long Infeed_Value = long(Pass_Depth / ((float)SCREW_X/100 / MOTOR_X_STEP_PER_REV) + 0.5) * McSTEP_X + McSTEP_X;

         Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
         Limit_Front_LED_On();
         Pass_Nr++;
         BeepBeep();
         Thread_Front(c_flag, d_flag);
      }

      else if ((cycle_flag == false) && (Pass_Nr > Pass_Total && Pass_Nr <= Pass_Total + PASS_FINISH))
      {
         cycle_flag = true;
         c_flag = false;
         d_flag = false;

         Pass_Nr++;
         BeepBeep();
         Thread_Front(c_flag, d_flag);
      }

      else if (cycle_flag == false && Pass_Nr > Pass_Total + PASS_FINISH)
      {
         c_flag = false;
         d_flag = false;

         Limit_Pos_Front = Null_X_Pos;
         Thread_Front(c_flag, d_flag);

         Limit_Front_LED_Off();
         Limit_Rear_LED_Off();
         Limit_Pos_Front = Limit_Pos_Max;
         Limit_Pos_Rear = Limit_Pos_Min;
      }
   }

   else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front)
   {
      c_flag = false;
      d_flag = false;

      Thread_Left(c_flag, d_flag);
   }

   else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front)
   {
      cycle_flag = false;
      c_flag = false;
      d_flag = false;

      Limit_Pos_Rear = (Null_X_Pos - REBOUND_X);
      Limit_Rear_LED_On();

      Thread_Rear(c_flag, d_flag);
   }

   else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear)
   {
      c_flag = false;
      d_flag = false;

      Thread_Right(c_flag, d_flag);
   }
  }
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Opti Условия развёрнуты, Выигрыш 92 байт
void Thread_Ext_Left()
{
  if (Motor_Z_Pos == Limit_Pos_Right)
  {
    if (Motor_X_Pos == Limit_Pos_Rear || Motor_X_Pos == Null_X_Pos)
    {
      Pass_Total = Thread_Info[Thread_Step].Pass;
      if (cycle_flag == false)
      {
        if (Pass_Nr <= Pass_Total)
        {
          cycle_flag = true;
          c_flag = false;
          d_flag = false;

          
          float Pass_Depth;
          //OLD
          //float Step_mm = Thread_Info[Thread_Step].Step;
          //if (Pass_Nr == 1) {
          //  Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 6) - (Step_mm * 0.866 / 8)) / sqrt(Pass_Total - 1) * sqrt(0.3);
          //}
          //else             {
          //  Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 6) - (Step_mm * 0.866 / 8)) / sqrt(Pass_Total - 1) * sqrt(Pass_Nr - 1);
          //}
          //Opti Выигрыш 92 байт
          const float csf = (float)(1.0f - 1.0f/6.0f - 1.0f/8.0f);    // 1  -0.16(6)  - 0.125 = 0,708(3), близко к sin(45°) == cos(45°) = 0.707107 == M_SQRT1_2 //const float csf = cos(M_PI_4);
          float Step_0866 = 0.8660254f * csf * Thread_Info[Thread_Step].Step / sqrt(Pass_Total - 1);
          if (Pass_Nr == 1) {
            Pass_Depth = Step_0866 * sqrt(0.3);
          } else {
            Pass_Depth = Step_0866 * sqrt(Pass_Nr - 1);
          }
          //-
          long Infeed_Value = long(Pass_Depth / ((float)SCREW_X / 100 / MOTOR_X_STEP_PER_REV) + 0.5) * McSTEP_X + McSTEP_X;

          Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
          Limit_Front_LED_On();
          Pass_Nr++;
          BeepBeep();
          Thread_Front(c_flag, d_flag);
        } else if (Pass_Nr > Pass_Total && Pass_Nr <= Pass_Total + PASS_FINISH)
        {
          cycle_flag = true;
          c_flag = false;
          d_flag = false;

          Pass_Nr++;
          BeepBeep();
          Thread_Front(c_flag, d_flag);
        } else if (Pass_Nr > Pass_Total + PASS_FINISH)
        {
          c_flag = false;
          d_flag = false;

          Limit_Pos_Front = Null_X_Pos;
          Thread_Front(c_flag, d_flag);

          Limit_Front_LED_Off();
          Limit_Rear_LED_Off();
          Limit_Pos_Front = Limit_Pos_Max;
          Limit_Pos_Rear = Limit_Pos_Min;
        }
      }
    }
    else if (Motor_X_Pos == Limit_Pos_Front)
    {
      c_flag = false;
      d_flag = false;
      Thread_Left(c_flag, d_flag);
    }
  }
  else if (Motor_Z_Pos == Limit_Pos_Left)
  {
    if (Motor_X_Pos == Limit_Pos_Front)
    {
      cycle_flag = false;
      c_flag = false;
      d_flag = false;

      Limit_Pos_Rear = (Null_X_Pos - REBOUND_X);
      Limit_Rear_LED_On();

      Thread_Rear(c_flag, d_flag);
    } else if (Motor_X_Pos == Limit_Pos_Rear)
    {
      c_flag = false;
      d_flag = false;

      Thread_Right(c_flag, d_flag);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ORIGINAL
/*
  void Thread_Ext_Right()  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  {
  if ((Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear) || (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Null_X_Pos))
  {
    Pass_Total = Thread_Info[Thread_Step].Pass;
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      c_flag = false;
      d_flag = false;

      float Step_mm = Thread_Info[Thread_Step].Step;
      float Pass_Depth = 0;
      if (Pass_Nr == 1) {
        Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 6) - (Step_mm * 0.866 / 8)) / sqrt(Pass_Total - 1) * sqrt(0.3);
      }
      else             {
        Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 6) - (Step_mm * 0.866 / 8)) / sqrt(Pass_Total - 1) * sqrt(Pass_Nr - 1);
      }
      long Infeed_Value = long(Pass_Depth / ((float)SCREW_X / 100 / MOTOR_X_STEP_PER_REV) + 0.5) * McSTEP_X + McSTEP_X;
      Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
      Limit_Front_LED_On();
      Pass_Nr++;

      BeepBeep();
      Thread_Front(c_flag, d_flag);
    }

    else if ((cycle_flag == false) && (Pass_Nr > Pass_Total && Pass_Nr <= Pass_Total + PASS_FINISH))
    {
      cycle_flag = true;
      c_flag = false;
      d_flag = false;

      Pass_Nr++;
      BeepBeep();
      Thread_Front(c_flag, d_flag);
    }

    else if (cycle_flag == false && Pass_Nr > Pass_Total + PASS_FINISH)
    {
      c_flag = false;
      d_flag = false;

      Limit_Pos_Front = Null_X_Pos;
      Thread_Front(c_flag, d_flag);

      Limit_Front_LED_Off();
      Limit_Rear_LED_Off();
      Limit_Pos_Front = Limit_Pos_Max;
      Limit_Pos_Rear = Limit_Pos_Min;
    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front)
  {
    c_flag = false;
    d_flag = false;

    Thread_Right(c_flag, d_flag);
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front)
  {
    cycle_flag = false;
    c_flag = false;
    d_flag = false;

    Limit_Pos_Rear = (Null_X_Pos - REBOUND_X);
    Limit_Rear_LED_On();

    Thread_Rear(c_flag, d_flag);
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear)
  {
    c_flag = false;
    d_flag = false;

    Thread_Left(c_flag, d_flag);
  }
  }
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Opti Условия развёрнуты, Выигрыш 92 байт
void Thread_Ext_Right()
{
  if (Motor_Z_Pos == Limit_Pos_Left)
  {
    if (Motor_X_Pos == Limit_Pos_Rear || Motor_X_Pos == Null_X_Pos)
    {
      Pass_Total = Thread_Info[Thread_Step].Pass;
      if (cycle_flag == false)
      {
        if (Pass_Nr <= Pass_Total)
        {
          cycle_flag = true;
          c_flag = false;
          d_flag = false;

          
          float Pass_Depth = 0;
          //OLD
          //float Step_mm = Thread_Info[Thread_Step].Step;
          //if (Pass_Nr == 1) {
          //  Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 6) - (Step_mm * 0.866 / 8)) / sqrt(Pass_Total - 1) * sqrt(0.3);
          //}
          //else             {
          //  Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 6) - (Step_mm * 0.866 / 8)) / sqrt(Pass_Total - 1) * sqrt(Pass_Nr - 1);
          //}
          //Opti Выигрыш 92 байт
          const float csf = (float)(1.0f - 1.0f/6.0f - 1.0f/8.0f);    // 1  -0.16(6)  - 0.125 = 0,708(3), близко к sin(45°) == cos(45°) = 0.707107 == M_SQRT1_2 //const float csf = cos(M_PI_4);
          float Step_0866 = 0.8660254f * csf * Thread_Info[Thread_Step].Step / sqrt(Pass_Total - 1);
          if (Pass_Nr == 1) {
            Pass_Depth = Step_0866 * sqrt(0.3);
          } else {
            Pass_Depth = Step_0866 * sqrt(Pass_Nr - 1);
          }
          //-
          long Infeed_Value = long(Pass_Depth / ((float)SCREW_X / 100 / MOTOR_X_STEP_PER_REV) + 0.5) * McSTEP_X + McSTEP_X;
          Limit_Pos_Front = (Null_X_Pos + Infeed_Value);
          Limit_Front_LED_On();
          Pass_Nr++;

          BeepBeep();
          Thread_Front(c_flag, d_flag);
        } else if (Pass_Nr > Pass_Total && Pass_Nr <= Pass_Total + PASS_FINISH)
        {
          cycle_flag = true;
          c_flag = false;
          d_flag = false;

          Pass_Nr++;
          BeepBeep();
          Thread_Front(c_flag, d_flag);
        } else if (Pass_Nr > Pass_Total + PASS_FINISH)
        {
          c_flag = false;
          d_flag = false;

          Limit_Pos_Front = Null_X_Pos;
          Thread_Front(c_flag, d_flag);

          Limit_Front_LED_Off();
          Limit_Rear_LED_Off();
          Limit_Pos_Front = Limit_Pos_Max;
          Limit_Pos_Rear = Limit_Pos_Min;
        }
      }
    } else if (Motor_X_Pos == Limit_Pos_Front)
    {
      c_flag = false;
      d_flag = false;

      Thread_Right(c_flag, d_flag);
    }
  }
  else if (Motor_Z_Pos == Limit_Pos_Right)
  {
    if (Motor_X_Pos == Limit_Pos_Front)
    {
      cycle_flag = false;
      c_flag = false;
      d_flag = false;

      Limit_Pos_Rear = (Null_X_Pos - REBOUND_X);
      Limit_Rear_LED_On();

      Thread_Rear(c_flag, d_flag);
    } else if (Motor_X_Pos == Limit_Pos_Rear)
    {
      c_flag = false;
      d_flag = false;

      Thread_Left(c_flag, d_flag);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ORIGINAL
/*
  void Thread_Int_Left()
  {
  if ((Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front) || (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Null_X_Pos))
  {
    Pass_Total = Thread_Info[Thread_Step].Pass;
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      c_flag = false;
      d_flag = false;

      float Step_mm = Thread_Info[Thread_Step].Step;
      float Pass_Depth = 0;
      if (Pass_Nr == 1) {
        Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 4) - (Step_mm * 0.866 / 18)) / sqrt(Pass_Total - 1) * sqrt(0.3);
      }
      else             {
        Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 4) - (Step_mm * 0.866 / 18)) / sqrt(Pass_Total - 1) * sqrt(Pass_Nr - 1);
      }
      long Infeed_Value = long(Pass_Depth / ((float)SCREW_X / 100 / MOTOR_X_STEP_PER_REV) + 0.5) * McSTEP_X + McSTEP_X;
      Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
      Limit_Rear_LED_On();
      Pass_Nr++;

      BeepBeep();
      Thread_Rear(c_flag, d_flag);
    }

    else if ((cycle_flag == false) && (Pass_Nr > Pass_Total && Pass_Nr <= Pass_Total + PASS_FINISH))
    {
      cycle_flag = true;
      c_flag = false;
      d_flag = false;

      Pass_Nr++;
      BeepBeep();
      Thread_Rear(c_flag, d_flag);
    }

    else if (cycle_flag == false && Pass_Nr > Pass_Total + PASS_FINISH)
    {
      c_flag = false;
      d_flag = false;

      Limit_Pos_Rear = Null_X_Pos;
      Thread_Rear(c_flag, d_flag);

      Limit_Front_LED_Off();
      Limit_Rear_LED_Off();
      Limit_Pos_Front = Limit_Pos_Max;
      Limit_Pos_Rear = Limit_Pos_Min;
    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear)
  {
    c_flag = false;
    d_flag = false;

    Thread_Left(c_flag, d_flag);
  }

  else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear)
  {
    cycle_flag = false;
    c_flag = false;
    d_flag = false;

    Limit_Pos_Front = (Null_X_Pos + REBOUND_X);
    Limit_Front_LED_On();

    Thread_Front(c_flag, d_flag);
  }

  else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front)
  {
    c_flag = false;
    d_flag = false;

    Thread_Right(c_flag, d_flag);
  }
  }
*/
//Opti Условия развёрнуты, Выигрыш 92 байт
void Thread_Int_Left()
{
  if (Motor_Z_Pos == Limit_Pos_Right)
  {
    if (Motor_X_Pos == Limit_Pos_Front || Motor_X_Pos == Null_X_Pos)
    {
      Pass_Total = Thread_Info[Thread_Step].Pass;
      if (cycle_flag == false)
      {
        if (Pass_Nr <= Pass_Total)
        {
          cycle_flag = true;
          c_flag = false;
          d_flag = false;

          float Pass_Depth = 0;
          //OLD
          //float Step_mm = Thread_Info[Thread_Step].Step;
          //if (Pass_Nr == 1) {
          //  Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 4) - (Step_mm * 0.866 / 18)) / sqrt(Pass_Total - 1) * sqrt(0.3);
          //}
          //else             {
          //  Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 4) - (Step_mm * 0.866 / 18)) / sqrt(Pass_Total - 1) * sqrt(Pass_Nr - 1);
          //}
          //Opti Выигрыш 92 байт
          const float csf = (float)(1.0f - 1.0f/4.0f - 1.0f/18.0f);
          float Step_0866 = 0.8660254f * csf * Thread_Info[Thread_Step].Step / sqrt(Pass_Total - 1);
          if (Pass_Nr == 1) {
            Pass_Depth = Step_0866 * sqrt(0.3);
          } else {
            Pass_Depth = Step_0866 * sqrt(Pass_Nr - 1);
          }
          //-
          
          long Infeed_Value = long(Pass_Depth / ((float)SCREW_X / 100 / MOTOR_X_STEP_PER_REV) + 0.5) * McSTEP_X + McSTEP_X;
          Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
          Limit_Rear_LED_On();
          Pass_Nr++;

          BeepBeep();
          Thread_Rear(c_flag, d_flag);
        } else if (Pass_Nr > Pass_Total && Pass_Nr <= Pass_Total + PASS_FINISH)
        {
          cycle_flag = true;
          c_flag = false;
          d_flag = false;

          Pass_Nr++;
          BeepBeep();
          Thread_Rear(c_flag, d_flag);
        } else if (Pass_Nr > Pass_Total + PASS_FINISH)
        {
          c_flag = false;
          d_flag = false;

          Limit_Pos_Rear = Null_X_Pos;
          Thread_Rear(c_flag, d_flag);

          Limit_Front_LED_Off();
          Limit_Rear_LED_Off();
          Limit_Pos_Front = Limit_Pos_Max;
          Limit_Pos_Rear = Limit_Pos_Min;
        }
      }
    }
    else if (Motor_X_Pos == Limit_Pos_Rear)
    {
      c_flag = false;
      d_flag = false;

      Thread_Left(c_flag, d_flag);
    }
  }
  else if (Motor_Z_Pos == Limit_Pos_Left)
  {
    if (Motor_X_Pos == Limit_Pos_Rear)
    {
      cycle_flag = false;
      c_flag = false;
      d_flag = false;

      Limit_Pos_Front = (Null_X_Pos + REBOUND_X);
      Limit_Front_LED_On();

      Thread_Front(c_flag, d_flag);
    } else if (Motor_X_Pos == Limit_Pos_Front)
    {
      c_flag = false;
      d_flag = false;

      Thread_Right(c_flag, d_flag);
    }
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ORIGINAL
/*
  void Thread_Int_Right()
  {
  if ((Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Front) || (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Null_X_Pos))
  {
    Pass_Total = Thread_Info[Thread_Step].Pass ;
    if (cycle_flag == false && Pass_Nr <= Pass_Total)
    {
      cycle_flag = true;
      c_flag = false;
      d_flag = false;

      float Step_mm = Thread_Info[Thread_Step].Step;
      float Pass_Depth = 0;
      if (Pass_Nr == 1) {
        Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 4) - (Step_mm * 0.866 / 18)) / sqrt(Pass_Total - 1) * sqrt(0.3);
      }
      else             {
        Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 4) - (Step_mm * 0.866 / 18)) / sqrt(Pass_Total - 1) * sqrt(Pass_Nr - 1);
      }
      long Infeed_Value = long(Pass_Depth / ((float)SCREW_X / 100 / MOTOR_X_STEP_PER_REV) + 0.5) * McSTEP_X + McSTEP_X;
      Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
      Limit_Rear_LED_On();
      Pass_Nr++;

      BeepBeep();
      Thread_Rear(c_flag, d_flag);
    }

    else if ((cycle_flag == false) && (Pass_Nr > Pass_Total && Pass_Nr <= Pass_Total + PASS_FINISH))
    {
      cycle_flag = true;
      c_flag = false;
      d_flag = false;

      Pass_Nr++;
      BeepBeep();
      Thread_Rear(c_flag, d_flag);
    }

    else if (cycle_flag == false && Pass_Nr > Pass_Total + PASS_FINISH)
    {
      c_flag = false;
      d_flag = false;

      Limit_Pos_Rear = Null_X_Pos;
      Thread_Rear(c_flag, d_flag);

      Limit_Front_LED_Off();
      Limit_Rear_LED_Off();
      Limit_Pos_Front = Limit_Pos_Max;
      Limit_Pos_Rear = Limit_Pos_Min;
    }
  }

  else if (Motor_Z_Pos == Limit_Pos_Left && Motor_X_Pos == Limit_Pos_Rear)
  {
    c_flag = false;
    d_flag = false;

    Thread_Right(c_flag, d_flag);
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Rear)
  {
    cycle_flag = false;
    c_flag = false;
    d_flag = false;

    Limit_Pos_Front = (Null_X_Pos + REBOUND_X);
    Limit_Front_LED_On();

    Thread_Front(c_flag, d_flag);
  }

  else if (Motor_Z_Pos == Limit_Pos_Right && Motor_X_Pos == Limit_Pos_Front)
  {
    c_flag = false;
    d_flag = false;

    Thread_Left(c_flag, d_flag);
  }
  }
*/
//Opti Условия развёрнуты, Выигрыш 92 байт
void Thread_Int_Right()
{
  if (Motor_Z_Pos == Limit_Pos_Left)
  {
    if (Motor_X_Pos == Limit_Pos_Front || Motor_X_Pos == Null_X_Pos)
    {
      Pass_Total = Thread_Info[Thread_Step].Pass ;
      if (cycle_flag == false)
      {
        if (Pass_Nr <= Pass_Total)
        {
          cycle_flag = true;
          c_flag = false;
          d_flag = false;

          float Pass_Depth = 0;
          //OLD
          //float Step_mm = Thread_Info[Thread_Step].Step;
          //if (Pass_Nr == 1) {
          //  Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 4) - (Step_mm * 0.866 / 18)) / sqrt(Pass_Total - 1) * sqrt(0.3);
          //}
          //else             {
          //  Pass_Depth = ((Step_mm * 0.866) - (Step_mm * 0.866 / 4) - (Step_mm * 0.866 / 18)) / sqrt(Pass_Total - 1) * sqrt(Pass_Nr - 1);
          //}
          //Opti Выигрыш 92 байт
          const float csf = (float)(1.0f - 1.0f/4.0f - 1.0f/18.0f);
          float Step_0866 = 0.8660254f * csf * Thread_Info[Thread_Step].Step / sqrt(Pass_Total - 1);
          if (Pass_Nr == 1) {
            Pass_Depth = Step_0866 * sqrt(0.3);
          } else {
            Pass_Depth = Step_0866 * sqrt(Pass_Nr - 1);
          }
          //-
          long Infeed_Value = long(Pass_Depth / ((float)SCREW_X / 100 / MOTOR_X_STEP_PER_REV) + 0.5) * McSTEP_X + McSTEP_X;
          Limit_Pos_Rear = (Null_X_Pos - Infeed_Value);
          Limit_Rear_LED_On();
          Pass_Nr++;

          BeepBeep();
          Thread_Rear(c_flag, d_flag);
        } else if (Pass_Nr > Pass_Total && Pass_Nr <= Pass_Total + PASS_FINISH)
        {
          cycle_flag = true;
          c_flag = false;
          d_flag = false;

          Pass_Nr++;
          BeepBeep();
          Thread_Rear(c_flag, d_flag);
        } else if (Pass_Nr > Pass_Total + PASS_FINISH)
        {
          c_flag = false;
          d_flag = false;

          Limit_Pos_Rear = Null_X_Pos;
          Thread_Rear(c_flag, d_flag);

          Limit_Front_LED_Off();
          Limit_Rear_LED_Off();
          Limit_Pos_Front = Limit_Pos_Max;
          Limit_Pos_Rear = Limit_Pos_Min;
        }
      }
    }
    else if (Motor_X_Pos == Limit_Pos_Rear)
    {
      c_flag = false;
      d_flag = false;

      Thread_Right(c_flag, d_flag);
    }
  }
  else if (Motor_Z_Pos == Limit_Pos_Right)
  {
    if (Motor_X_Pos == Limit_Pos_Rear)
    {
      cycle_flag = false;
      c_flag = false;
      d_flag = false;

      Limit_Pos_Front = (Null_X_Pos + REBOUND_X);
      Limit_Front_LED_On();

      Thread_Front(c_flag, d_flag);
    } else if (Motor_X_Pos == Limit_Pos_Front)
    {
      c_flag = false;
      d_flag = false;

      Thread_Left(c_flag, d_flag);
    }
  }
}
