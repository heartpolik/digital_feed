//ver. 1.1 Оптимизация выйгрыш 18 + 80 + 82 = 180 байт

void H_Coder()
{
   ///////////////
   // Масштаб
   ///////////////
   if (Motor_Z_Pos == Null_Z_Pos + Hand_Z_Pos && Motor_X_Pos == Null_X_Pos + Hand_X_Pos)
   {
      if (Scale == HC_SCALE_10 && flag_Scale_x1 == ON)    //Флаги масштаба ручного энкодера - стоял масштаб 10х переключается на 1х
      { 
         Hand_Count = 0;
         Hand_Count_New = 0;
         Hand_Count_Old = 0;
         Hand_Z_Pos = 0;
         Hand_X_Pos = 0;

         Null_Z_Pos = Motor_Z_Pos;
         Null_X_Pos = Motor_X_Pos;

         max_OCR3A = HC_START_SPEED_1;
         min_OCR3A = HC_MAX_SPEED_1;
         
         Scale = HC_SCALE_1;
      }
      else if (Scale == HC_SCALE_1 && flag_Scale_x10 == ON)    //Флаги масштаба ручного энкодера - стоял масштаб 1х переключается на 10х
      {
         Hand_Count = 0;
         Hand_Count_New = 0;
         Hand_Count_Old = 0;
         Hand_Z_Pos = 0;
         Hand_X_Pos = 0;

         Null_Z_Pos = Motor_Z_Pos;
         Null_X_Pos = Motor_X_Pos;

         max_OCR3A = HC_START_SPEED_10;
         min_OCR3A = HC_MAX_SPEED_10;
         
         Scale = HC_SCALE_10;
      }
   }
   
   /////////////////
   // Активная ось 
   /////////////////
   /////////////////
   //Активна ось Z ручного энкодера
   if (hand_Z == ON)
   {
      Disa_INT_Hcoder();
      Hand_Count_New = Hand_Count;    //Читаем переменную Hand_Count (управляется прерыванием INT2 от ручного энкодера) и запоминаем
      Ena_INT_Hcoder();

      //Если произошло изменение положения ручного энкодера...
      if (Hand_Count_New != Hand_Count_Old)
      {
         Hand_Count_Old = Hand_Count_New;       //Запоминаем новое значение переменной Hand_Count
         Hand_Z_Pos = (Hand_Count_New * Scale * MOTOR_Z_STEP_PER_REV * McSTEP_Z / SCREW_Z + McSTEP_Z /2)  & ~(McSTEP_Z - 1);

         //DEBUG
         #ifdef _DEBUG_HANDCODER
         Serial.print("Hand_Z_Pos=");Serial.print(Hand_Z_Pos);Serial.print("\n\r");
         #endif     
         
         Brake_Compens = max_OCR3A - min_OCR3A +1;
         Disable_INT_OCR3B();     //Выключаем обработчик оси X ручного энкодера
         Enable_INT_OCR3A();      //Включаем  обработчик оси Z ручного энкодера
      } 

      //Opti Выносим суммирование в отдельную переменную, тип long
      //В дальнейших вычислениях используем эту переменную. Выигрыш составляет 80 байт.
      long Summ_Null_Z_Pos_and_Hand_Z_Pos = Null_Z_Pos + Hand_Z_Pos;
      //-
      //OLD
      //if (Motor_Z_Pos < Null_Z_Pos + Hand_Z_Pos)
      //Opti
      //Определяем направление вращения ручного энкодера
      if (Motor_Z_Pos < Summ_Null_Z_Pos_and_Hand_Z_Pos)
      //-
      {
         Motor_Z_Dir = CW;
         Motor_Z_CW();              //Это макрос, Null_Z_Pos и Hand_Z_Pos не затрагивает
         //OLD
         //Limit_Pos_HC = Null_Z_Pos + Hand_Z_Pos - Brake_Compens;
         //Opti
         Limit_Pos_HC = Summ_Null_Z_Pos_and_Hand_Z_Pos - Brake_Compens;
         //-
         Limit_Pos = Limit_Pos_Left - Brake_Compens;
      }
      //OLD
      //else if (Motor_Z_Pos > Null_Z_Pos + Hand_Z_Pos)
      //Opti
      else if (Motor_Z_Pos > Summ_Null_Z_Pos_and_Hand_Z_Pos)
      //-
      {
         Motor_Z_Dir = CCW;
         Motor_Z_CCW();              //Это макрос, Null_Z_Pos и Hand_Z_Pos не затрагивает
         //OLD
         //Limit_Pos_HC = Null_Z_Pos + Hand_Z_Pos + Brake_Compens;
         //Opti
         Limit_Pos_HC = Summ_Null_Z_Pos_and_Hand_Z_Pos + Brake_Compens;
         //-
         Limit_Pos = Limit_Pos_Right + Brake_Compens;
      }
   }

   //////////////////////////
   //Активна ось X ручного энкодера
   else if (hand_X == ON)
   {
      Disa_INT_Hcoder();
      
      
      //Hand_Count_New имеет тип long, знаковое
      //OLD
      //if (HC_X_DIR == 0) {Hand_Count_New = Hand_Count;}
      //else               {Hand_Count_New = Hand_Count - Hand_Count *2;}   //Весьма странный способ записи.
      //Opti Более традиционная запись, выгода 18 байт
      if (HC_X_DIR == 0)              //Тут проверка настроек поперечной подачи: // 1-поперечка по часовой, 0-против
      {
        Hand_Count_New = Hand_Count;
      } else {
        Hand_Count_New = -Hand_Count;
      }
      //-     
      
      Ena_INT_Hcoder();
      
      if (Hand_Count_New != Hand_Count_Old)
      {
         Hand_Count_Old = Hand_Count_New;
         Hand_X_Pos = (Hand_Count_New * Scale * MOTOR_X_STEP_PER_REV * McSTEP_X / SCREW_X + McSTEP_X /2)  & ~(McSTEP_X - 1);

         //DEBUG
         #ifdef _DEBUG_HANDCODER
         Serial.print("Hand_X_Pos=");Serial.print(Hand_X_Pos);Serial.print("\n\r"); 
         #endif
         
         Brake_Compens = max_OCR3A - min_OCR3A + 1;
         Disable_INT_OCR3A();
         Enable_INT_OCR3B();
      } 

      //Opti Выносим суммирование в отдельную переменную, тип long
      //В дальнейших вычислениях используем эту переменную. Выигрыш составляет 82 байта.
      long Summ_Null_X_Pos_and_Hand_X_Pos = Null_X_Pos + Hand_X_Pos;
      //-
      //OLD
      //if (Motor_X_Pos < Null_X_Pos + Hand_X_Pos)
      //Opti
      if (Motor_X_Pos < Summ_Null_X_Pos_and_Hand_X_Pos)
      //-
      {
         Motor_X_Dir = CW;
         Motor_X_CW();              //Это макрос, Null_X_Pos и Hand_X_Pos не затрагивает
         //OLD
         //Limit_Pos_HC = Null_X_Pos + Hand_X_Pos - Brake_Compens;
         //Opti
         Limit_Pos_HC = Summ_Null_X_Pos_and_Hand_X_Pos - Brake_Compens;
         //-
      }
      //OLD
      //else if (Motor_X_Pos > Null_X_Pos + Hand_X_Pos)
      //Opti
      else if (Motor_X_Pos > Summ_Null_X_Pos_and_Hand_X_Pos)
      //-
      {
         Motor_X_Dir = CCW;
         Motor_X_CCW();              //Это макрос, Null_X_Pos и Hand_X_Pos не затрагивает
         //OLD
         //Limit_Pos_HC = Null_X_Pos + Hand_X_Pos + Brake_Compens;
         //Opti
         Limit_Pos_HC = Summ_Null_X_Pos_and_Hand_X_Pos + Brake_Compens;
         //-
      }
   }
      
   /////////////////////////////////////////////////
   //Opti Отключаем пустой код
   //else if (hand_Z == OFF && hand_X == OFF)
   //{
   //  //
   //}
   //-
}
