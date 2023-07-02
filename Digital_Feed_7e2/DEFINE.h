#ifndef DEFINE_h
#define DEFINE_h
//==================================================================================================================================
// ***** MY CONSTANT *****
#define CW               0
#define CCW              1
#define ON               1
#define OFF              0

//Для КОНУСОВ
#define FORCE_RAPID        2
#define FORCE_SLOW         1
#define MANUAL             0


#define Beeper_Init()          DDRH = B01100010;\
  PORTH = B10011101    // LCD-H5,H6 Buzzer-PH1_Pin16
#define Beeper_On()            PORTH |= (1<<1)     // Pin16 0
#define Beeper_Off()           PORTH &= ~(1<<1)      // Pin16 1

// ***** Stepper Motor *****
#define Motor_Init()           DDRL = B11111011;\
  PORTL = B0000100

//Линия STEP Z
#define Motor_Z_SetPulse()     PORTL &= ~(1<<0)     // Pin49 0
#define Motor_Z_RemovePulse()  PORTL |= (1<<0)      // Pin49 1
#define Motor_Z_InvertPulse()  PORTL ^= (1<<0)      // Pin49
#define Read_Z_State           (PINL & (1<<0))

#define Motor_X_SetPulse()     PORTL &= ~(1<<1)     // Pin48 0
#define Motor_X_RemovePulse()  PORTL |= (1<<1)      // Pin48 1
#define Motor_X_InvertPulse()  PORTL ^= (1<<1)      // Pin48
#define Read_X_State           (PINL & (1<<1))

//Линия DIR Z
#define Motor_Z_CW()           PORTL &= ~(1<<6)    // Pin43 0
#define Motor_Z_CCW()          PORTL |= (1<<6)     // Pin43 1

#define Motor_X_CW()           PORTL &= ~(1<<5)    // Pin44 0
#define Motor_X_CCW()          PORTL |= (1<<5)     // Pin44 1

//Линия ENA Z
#define Motor_Z_Enable()   do {PORTL |= (1<<4); _delay_ms(120);} while(0)   // Pin45 1
#define Motor_Z_Disable()      PORTL &= ~(1<<4)                             // Pin45 0
#define Read_Z_Ena_State       (PINL & (1<<4))

#define Motor_X_Enable()   do {PORTL |= (1<<3); _delay_ms(120);} while(0)   // Pin46 1
#define Motor_X_Disable()      PORTL &= ~(1<<3)                             // Pin46 0
#define Read_X_Ena_State       (PINL & (1<<3))

// ***** Tacho *****
#define TachoSetPulse()        PORTL |= (1<<7)      // Pin42 1
#define TachoRemovePulse()     PORTL &= ~(1<<7)     // Pin42 0

#define Encoder_Init()         DDRD = B00000000;\
  PORTD = B11111111        // подтяжка PIN_21, 20, 19, 18
//#define Enc_Read              (PIND & (1<<1))     //Дублируется с макросом Enc_Ch_B и нигде не используется
#define Enc_Ch_A              (PIND & (1<<0))
#define Enc_Ch_B              (PIND & (1<<1))

// ***** Hand_Coder *****            // Z/X: Input-E4,E5, подтяжка-E4,E5, X1/X10: Input-J0,J1, подтяжка-J0,J1.
#define Hand_Init()            DDRE = B00000000;\
  PORTE = B11111111;\
  DDRJ = B00000000;\
  PORTJ = B11111111

#define Hand_Ch_A             (PIND & (1<<2))
#define Hand_Ch_B             (PIND & (1<<3))

#define Hand_Axis_Read        (PINE & B00110000)       // E4,E5

#define Hand_Scale_Read        (PINJ & B00000011)      // J0,J1

//***** Limit Buttons & LEDs *****
#define Limit_Init()           DDRA = B10101010;\
  PORTA = B01010101    // IN-A0,A2,A4,A6, OUT-A1,A3,A5,A7, подтяжка

#define Limit_Buttons_Read    (PINA & B01010101)    // PA0 Pin22, PA2 Pin24, PA4 Pin26, PA6 Pin28.

#define Limit_Rear_LED_On()    PORTA &= ~(1<<1)     // PA1, Pin23 0
#define Limit_Rear_LED_Off()   PORTA |= (1<<1)      // PA1, Pin23 1
#define Limit_Front_LED_On()   PORTA &= ~(1<<3)     // PA3, Pin25 0
#define Limit_Front_LED_Off()  PORTA |= (1<<3)      // PA3, Pin25 1
#define Limit_Right_LED_On()   PORTA &= ~(1<<5)     // PA5, Pin27 0
#define Limit_Right_LED_Off()  PORTA |= (1<<5)      // PA5, Pin27 1
#define Limit_Left_LED_On()    PORTA &= ~(1<<7)     // PA7, Pin29 0
#define Limit_Left_LED_Off()   PORTA |= (1<<7)      // PA7, Pin29 1

#define Limit_Pos_Max          1073741824
#define Limit_Pos_Min         -1073741824

#define Menu_Buttons_Init()    DDRF = B00000000;\
  PORTF = B11111111;

#define Buttons_Read           (PINF & B00001111)    // Pin_A0 PF0, Pin_A1 PF1, Pin_A2 PF2, Pin_A3 PF3, Pin_A4 PF4.

#define Button_Sel_Read        (PINF & B00010000)    // Pin_A4 PF4

#define Joy_Init()             DDRK = B00000000;\
  PORTK = B11111111;    // подтяжка PIN_A8, A9, A10, A11, A12 // Submode Sw: A13, A14, A15

#define Joy_Read              (PINK & B00001111)     // PK0 PK1 PK2 PK3
//#define Button_Rapid          (PINK & B00010000)     // PK4

//возвращается true, если 4-ый слева бит равен 1, т.е. еcли на PK4 высокий логический уровень - то не нажата кнопка "Быстрая подача" ("Rapid Button")
//возвращает  false, если на PK4 низкий логический уровень - т.е. нажата кнопка "Быстрая подача" ("Rapid Button")
#define Button_Rapid_Not_Pressed          (PINK & B00010000)


#define Submode_Read          (PINK & B11100000)     // PK5 PK6 PK7

// ***** Mode *****
#define Mode_Switch_Init()     DDRC = B00000000;\
  PORTC = B11111111;        // подтяжка PORT_A, ОБЯЗАТЕЛЬНА! внешняя подтяжка к +5 через 1К резисторы
#define Mode_Read             (PINC & B11111111)

//***** Ускоренное перемещение *****
// 16MHz/32 = 500kHz [Prescaler clk_T2S/32]
//#define Timer2_Init()          TCCR2A = (1<<WGM21);TCCR2B = (1<<CS20)|(1<<CS21); 

//***** РГИ перемещение *****
// 16MHz/64 = 250kHz [Prescaler clk_T2S/64]
#define Timer3_Init()          TCCR3A = 0;TCCR3B = (1<<WGM32)|(1<<CS30)|(1<<CS31); 

// ***** aFeed *****
//OLD
/*#define Timer4_Init()          TCCR4B = (1<<WGM42)|(1<<CS40)|(1<<CS41); // 16MHz/64 = 250kHz [Prescaler clk_T2S/64]*/
//NEW
// 16MHz/64 = 250kHz [Prescaler clk_T2S/64]
/*#define Timer4_Init()          TCCR4A = 0;TCCR4B = (1<<ICNC4)|(1<<ICES4)|(1<<WGM42)|(1<<CS40)|(1<<CS41);*/
//#define Timer4_Init()            TCCR4A = 0;TCCR4B = (1<<ICNC4)|(1<<WGM42)|(1<<CS40)|(1<<CS41);

#define Timer4_Init()            TCCR4A = 0x00;TCCR4B = 0x00 | (1<<WGM42)|(1<<CS40)|(1<<CS41);


// ***** Feed *****
//[External clock source on Tn pin. Clock on rising edge.]
//"Таймер" синхронизирован с внешним сигналом
//Таймер 5 тактуется от внешнего импульса с пина PL2#47 T5 (сигнал с одного из каналов энкодера шпинделя)
//TCCR5A все биты сброшены (точнее со 2 по 7 бит отвечают за режим) - Normal port operation, OCnA/OCnB/OCnC disconnected
//       биты 0 и 1 (WGM51=0 WGM50=0)
//TCCR5B биты CS50=1 CS51=1 CS52=1 задают режим External clock source on T5 pin. Clock on rising edge - Внешний источник тактовых импульсов на выводе T5. Переключение по восходящему фронту LOW->HIGHT
//       биты WGM50=0 WGM51=0 (в регистре TCCR5A) и WGM52=1 WGM53=0 задают режим №4 Waveform Generation Mode "CTC" (Clear Timer on Compare Match )
//       в этом режиме частота вызова таймера управляется делителем в OCR5A (импульсы с T5 -> делитель в OCR5A -> вызов обработчика при совпадении)
//       вызовы обработчиков TIMER5_COMPB_vect и TIMER5_COMPC_vect также управляются делителем в OCR5A!!!
//
//       Есть ещё режим №12 Waveform Generation Mode "CTC" (Clear Timer on Compare Match )
//       биты WGM50=0 WGM51=0 (в регистре TCCR5A) и WGM52=1 WGM53=1
//       Отличие режима что обработчики TIMER5_COMPB_vect и TIMER5_COMPC_vect управляются своими собственными делителями OCR5B и OCR5С

#define Timer5_Init()          TCCR5A = 0;TCCR5B = (1<<WGM52) | (1<<CS52) | (1<<CS51) | (1<<CS50) 


// ***** Cone *****
//NEW для SETUP
#define TYPE_AB 0
#define TYPE_DEG 1
//-
#define PASS_FINISH   3 // THRD_PS_FN ???

//----
// ***** My Flags *****
typedef struct
{
  uint8_t bit0 : 1;
  uint8_t bit1 : 1;
  uint8_t bit2 : 1;
  uint8_t bit3 : 1;
  uint8_t bit4 : 1;
  uint8_t bit5 : 1;
  uint8_t bit6 : 1;
  uint8_t bit7 : 1;
} FLAG;

//Step_Z_flag -> Z_WORKING_FEED_FLAG
//Step_X_flag -> X_WORKING_FEED_FLAG

#define Spindle_Dir        ((volatile FLAG*)_SFR_MEM_ADDR(GPIOR0))->bit0    // CW-0, CCW-1
#define Motor_Z_Dir        ((volatile FLAG*)_SFR_MEM_ADDR(GPIOR0))->bit1    // CW-0, CCW-1
#define Joy_Z_flag         ((volatile FLAG*)_SFR_MEM_ADDR(GPIOR0))->bit2    // On-1, Off-0
#define Z_WORKING_FEED_FLAG        ((volatile FLAG*)_SFR_MEM_ADDR(GPIOR0))->bit3    // On-1, Off-0
#define Motor_X_Dir        ((volatile FLAG*)_SFR_MEM_ADDR(GPIOR0))->bit4    // CW-0, CCW-1
#define Joy_X_flag         ((volatile FLAG*)_SFR_MEM_ADDR(GPIOR0))->bit5    // On-1, Off-0
#define X_WORKING_FEED_FLAG        ((volatile FLAG*)_SFR_MEM_ADDR(GPIOR0))->bit6    // On-1, Off-0
#define Cone_flag          ((volatile FLAG*)_SFR_MEM_ADDR(GPIOR0))->bit7    // On-1, Off-0
//----

// ***** Interrupts *****
//Настройка внешних прерываний

//INT_0 Генерируется от пина PD0#21 INT0 (сигнал с одного из каналов энкодера шпинделя)
//В регистре EICRA биты ISC00=1 ISC01=0 --- Any edge of INTn generates asynchronously an interrupt request / (изменение) – срабатывает при изменении сигнала (с LOW на HIGH и наоборот)
#define INT0_Init()               EICRA |= (1<<ISC00)


//INT_1 Генерируется от пина PD1#20 INT0 (сигнал с одного из каналов энкодера шпинделя)
//В регистре EICRA биты ISC10=1 ISC11=0 --- Any edge of INTn generates asynchronously an interrupt request / (изменение) – срабатывает при изменении сигнала (с LOW на HIGH и наоборот)
#define INT1_Init()               EICRA |= (1<<ISC10)


//INT_2 Генерируется от пина PD2#19 (сигнал от одного из каналов ручного энкодера)
//В регистре EICRA биты ISC20=1 ISC21=0 --- Any edge of INTn generates asynchronously an interrupt request / (изменение) – срабатывает при изменении сигнала (с LOW на HIGH и наоборот)
#define INT2_Init()               EICRA |= (1<<ISC20)
//Вызов только при спадании уровня сигнала, а не каждый тик как было до этого (это упростит код обработчика в Interrupt.ino)
//#define INT2_Init()               EICRA |= (1<<ISC21)


#define Enable_INT0()             EIMSK |= (1<<INT0)
#define Disable_INT0()            EIMSK &= ~(1<<INT0)

//NEW
#define Enable_INT1()             EIMSK |= (1<<INT1)
#define Disable_INT1()            EIMSK &= ~(1<<INT1)



#define Ena_INT_Hcoder()      do {EIFR = (1<<INTF2); EIMSK |= (1<<INT2);} while(0)
#define Disa_INT_Hcoder()         EIMSK &= ~(1<<INT2)

#define Enable_INT_OCR2A()    do {TCNT2 = 0; TIFR2 = (1<<OCF2A); TIMSK2 = (1<<OCIE2A);} while(0)
#define Disable_INT_OCR2A()       TIMSK2 &= ~(1<<OCIE2A)

#define Enable_INT_OCR2B()    do {TCNT2 = 0; TIFR2 = (1<<OCF2B); TIMSK2 = (1<<OCIE2B);} while(0)
#define Disable_INT_OCR2B()       TIMSK2 &= ~(1<<OCIE2B)

#define Enable_INT_OCR3A()    do {TCNT3 = 0; TIFR3 = (1<<OCF3A); TIMSK3 = (1<<OCIE3A);} while(0)
#define Disable_INT_OCR3A()       TIMSK3 &= ~(1<<OCIE3A)

#define Enable_INT_OCR3B()    do {TCNT3 = 0; TIFR3 = (1<<OCF3B); TIMSK3 = (1<<OCIE3B);} while(0)
#define Disable_INT_OCR3B()       TIMSK3 &= ~(1<<OCIE3B)

//#define Enable_INT_OCR4A()    do {TCNT4 = 0; TIFR4 = (1<<OCF4A); TIMSK4 = (1<<OCIE4A);} while(0)
//#define Disable_INT_OCR4A()       TIMSK4 &= ~(1<<OCIE4A)
//#define Enable_INT_OCR4A()    do {TCNT4 = 0; bitSet(TIFR4,OCF4A); bitSet(TIMSK4,OCIE4A);} while(0)
//#define Disable_INT_OCR4A()       bitClear(TIMSK4,OCIE4A)

//-----------------
#define Enable_INT_OCR4A()    do {TCNT4 = 0x00; TIFR4 =0x00  | (1<<OCF4A); TIMSK4 = 0x00  | (1<<OCIE4A) | (0<<OCIE4B) | (0<<OCIE4C);} while(0)
#define Disable_INT_OCR4A()       TIMSK4 = 0x00 & ~(1<<OCIE4A)

#define Enable_INT_OCR4B()    do {TCNT4 = 0x00; TIFR4 =0x00  | (1<<OCF4B); TIMSK4 = 0x00  | (0<<OCIE4A) | (1<<OCIE4B) | (0<<OCIE4C);} while(0)
#define Disable_INT_OCR4B()       TIMSK4 = 0x00 & ~(1<<OCIE4B)

#define Enable_INT_OCR4C()    do {TCNT4 = 0x00; TIFR4 =0x00  | (1<<OCF4C); TIMSK4 = 0x00  | (0<<OCIE4A) | (0<<OCIE4B) | (1<<OCIE4C);} while(0)
#define Disable_INT_OCR4C()       TIMSK4 = 0x00 & ~(1<<OCIE4C)

//-------------------



//#define Enable_INT_OCR4B()    do {TCNT4 = 0; TIFR4 = (1<<OCF4B); TIMSK4 = (1<<OCIE4B);} while(0)
//#define Disable_INT_OCR4B()       TIMSK4 &= ~(1<<OCIE4B)
//#define Enable_INT_OCR4B()    do {TCNT4 = 0; bitSet(TIFR4,OCF4B); bitSet(TIMSK4,OCIE4B);} while(0)
//#define Disable_INT_OCR4B()       bitClear(TIMSK4,OCIE4B)


#define Enable_INT_OCR5A()    do {TCNT5 = 0; TIFR5 = (1<<OCF5A); TIMSK5 = (1<<OCIE5A);} while(0)
#define Disable_INT_OCR5A()       TIMSK5 &= ~(1<<OCIE5A)

#define Enable_INT_OCR5B()    do {TCNT5 = 0; TIFR5 = (1<<OCF5B); TIMSK5 = (1<<OCIE5B);} while(0)
#define Disable_INT_OCR5B()       TIMSK5 &= ~(1<<OCIE5B)

////////////////////////////////////////////////////////////
#define Ena_INT_Thrd()        do {Disable_INT_OCR4A();\
    Disable_INT_OCR4B();\
    Disable_INT_OCR4C();\
    Disable_INT_OCR5A();\
    Disable_INT_OCR5B();\
    Enable_INT1();\
    Enable_INT0();} while(0)

#define Ena_INT_Z_Feed()      do {Disable_INT0();\
    Disable_INT_OCR4A();\
    Disable_INT_OCR4B();\
    Disable_INT_OCR4C();\
    Disable_INT_OCR5B();\
    Disable_INT1();\
    Enable_INT_OCR5A();} while(0)

#define Ena_INT_Z_aFeed()     do {Disable_INT0();\
    Disable_INT_OCR4B();\
    Disable_INT_OCR4C();\
    Disable_INT_OCR5A();\
    Disable_INT_OCR5B();\
    Disable_INT1();\
    Enable_INT_OCR4A();} while(0)

#define Ena_INT_X_Feed()      do {Disable_INT0();\
    Disable_INT_OCR4A();\
    Disable_INT_OCR4B();\
    Disable_INT_OCR4C();\
    Disable_INT_OCR5A();\
    Disable_INT1();\
    Enable_INT_OCR5B();} while(0)

#define Ena_INT_X_aFeed()     do {Disable_INT0();\
    Disable_INT_OCR4A();\
    Disable_INT_OCR4C();\
    Disable_INT_OCR5A();\
    Disable_INT_OCR5B();\
    Disable_INT1();\
    Enable_INT_OCR4B();} while(0)

#define Ena_INT_Z_aCone()     do {Disable_INT0();\
    Disable_INT_OCR4A();\
    Disable_INT_OCR4B();\
    Disable_INT_OCR5A();\
    Disable_INT_OCR5B();\
    Disable_INT1();\
    Enable_INT_OCR4C();} while(0)


#define Ena_INT_TACHO()     do {Disable_INT0();\
    Disable_INT_OCR4A();\
    Disable_INT_OCR4B();\
    Disable_INT_OCR4C();\
    Disable_INT_OCR5A();\
    Disable_INT_OCR5B();\
    Enable_INT1();} while(0)


/*
#define Ena_INT_Z_Rapid()     do {Disable_INT0();\
    Disable_INT_OCR2B();\
    Disable_INT_OCR4A();\
    Disable_INT_OCR4B();\
    Disable_INT_OCR4C();\
    Disable_INT_OCR5A();\
    Disable_INT_OCR5B();\
    Enable_INT_OCR2A();} while(0)

#define Ena_INT_X_Rapid()     do {Disable_INT0();\
    Disable_INT_OCR2A();\
    Disable_INT_OCR4A();\
    Disable_INT_OCR4B();\
    Disable_INT_OCR4C();\
    Disable_INT_OCR5A();\
    Disable_INT_OCR5B();\
    Enable_INT_OCR2B();} while(0)
*/

//OLD
//#define KEYB_TIMER_FLAG       (TIFR1 & (1<<OCF1A))
//#define CLEAR_KEYB_TIMER   do {TCNT1 = 0; (TIFR1 |= (1<<OCF1A));} while(0)

//NEW Использование WDT-таймера
#define WDT_TIMER_FLAG          (WDTCSR & (1<<WDIF))
#define KEYB_TIMER_FLAG       (_WDT_TIMER_FLAG == true)
#define CLEAR_KEYB_TIMER   (_WDT_TIMER_FLAG = false)

//==================================================================================================================================
#endif
