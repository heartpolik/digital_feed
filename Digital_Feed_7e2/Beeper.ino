//Версия 1.1 Функция _delay_ms(...) заменена на delay(...) - Уменьшает размер скетча на 8 байт
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ********** Beeper ********** //////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DELAY_MS

void Beep()
{
   Beeper_On();
   #ifdef DELAY_MS
    _delay_ms(25);
   #else
    delay(64*25);
   #endif
   Beeper_Off();
}

void BeepBeep()
{
   Beeper_On();
   #ifdef DELAY_MS
    _delay_ms(25);
   #else
    delay(64*25);
   #endif
   Beeper_Off();   
   #ifdef DELAY_MS
    _delay_ms(200);
   #else
    delay(64*200);
   #endif
   Beeper_On();
   #ifdef DELAY_MS
    _delay_ms(25);
   #else
    delay(64*25);
   #endif
   Beeper_Off();
}

void Beep_Error()
{
   Beeper_On();
   #ifdef DELAY_MS
    _delay_ms(250);
   #else
    delay(64*250);
   #endif
   Beeper_Off();
}

void BeepComplete()  // три длинных сигнала
{
   Complete_flag = true;
   Print();
   Beeper_On();
   _delay_ms(500);
   Beeper_Off();   
   _delay_ms(100);
   Beeper_On();
   _delay_ms(500);
   Beeper_Off();
   _delay_ms(100);
   Beeper_On();
   _delay_ms(500);
   Beeper_Off();
}

/*
void Beep2()
{
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();   
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
}

void Beep5()
{
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();   
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
}


void Beep10()
{
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();   
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();   
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
   _delay_ms(25);
   Beeper_On();
   _delay_ms(25);
   Beeper_Off();
}
*/
