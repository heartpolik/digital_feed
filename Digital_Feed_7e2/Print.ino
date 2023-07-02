//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ***** Print ***** /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char ELS[]                  = "        ELS         ";           //16 знакомест, из них 0 русских знака
const char VERSION[]              = "   вepciя 043G1ua   ";           //16 знакомест, из них 3 русских знака "в и я"
const char WARNING1_1[]           = "       УВАГА:       ";           //16 знакомест, из них 2 русских знака "И И" (по сути это 1 знакоместо, а не два)
const char WARNING1_2[]           = "  УПOPИ HE ЗAДAHI!  ";           //16 знакомест, из них 6 русских знаков "У П Ы З Д Ы"
const char WARNING2_1[]           = "УCTAHOBИ KAPETKУ";           //16 знакомест, из них 3 русских знака "У И У"
const char WARNING2_2[]           = " B ИCXOДHУЮ ПOЗ.";           //16 знакомест, из них 4 русских знака "И Д У Ю П З"
const char WARNING3_1[]           = " OTKЛЮЧИ PУЧHOЙ ";           //16 знакомест, из них 6 русских знака "Л Ю Ч И У Ч Й"
const char WARNING3_2[]           = "     ЭHKOДEP    ";           //16 знакомест, из них 2 русских знака "Э Д"
const char THREAD[]               = "PEЗЬБA    ";                 //10 знакомест, из них 3 русских знака "З Ь Б"
const char FEED[]                 = "CИHXP мм/oб ";               //12 знакомест, из них 4 русских знака "И м м б"

const char FEED_RAPID[]           = "CИHXP    БЫCTPAЯ";           //16 знакомест, из них 5 русских знаков "И Б Ы Я П"

const char AFEED[]                = "ACИHX мм/мин ";              //13 знакомест, из них 6 русских знаков "И м м м и н"

const char AFEED_RAPID[]          = "ACИHX    БЫCTPAЯ";           //16 знакомест, из них 5 русских знаков "И Б Ы Я П"

const char MM[]                   = "мм";                         //2 знакоместа, из них 2 русских знака "мм"
const char MINRPM[]               = " Oб/мин<";                   //8 знакомест из них 4 русских знака "б м и н"
const char CONE_L[]               = "KOHУC <";                    //7 знакомест, из них 1 русский знак "У"
const char CONE_R[]               = "KOHУC >";                    //7 знакомест, из них 1 русский знак "У"

const char CONE_L_RAPID[]          = "KOHУC <  БЫCTPAЯ";           //16 знакомест, из них 5 русских знаков "И Б Ы Я П"
const char CONE_R_RAPID[]          = "KOHУC >  БЫCTPAЯ";           //16 знакомест, из них 5 русских знаков "И Б Ы Я П"


//const char RESERV1[]              = "    PEЗEPBHЫЙ   ";           //16 знакомест, из них 3 русских знака "З Ы Й"
//const char RESERV2[]              = "      PEЖИM     ";           //16 знакомест, из них 2 русских знака "Ж И"
const char SPHERE[]               = "ШAP  \xEC";                  //6 знакомест, из них 1 русский знак "Ш" и один спец-символ диаметра.
const char IMPOSSIBLE[]           = "PEЖИM HEBOЗMOЖEH";           //16 знакомест, перебор, из них 4 русских знака "Ж И З Ж"
const char EMPTY12[]              = "            ";               //12 знакомест, из них 0 русских знаков
const char NOZKA[]                = " Hoжкa \xEC";                //8 знакомест, из них 2 русских знака "ж к", и один спец-символ диаметра.
const char REZETZ_WIDTH[]         = "Шиp. peзцa  ";               //12 знакомест, из них 4 русских знака "Ш и з ц"
const char REZETZ_STEP[]          = "Шaг oбpaб.  ";               //12 знакомест, из них 4 русских знака "Ш г б б"
const char DIVIDER1[]             = "Зaд";                        //3 знакоместа, из них 2 русских знака "З д"
const char DIVIDER2[]             = "Teк";                        //3 знакоместа, из них 1 русский знак "к"
const char INTERN[]               = "Bнy.";                       //4 знакоместа, из них 1 русский знак "н"
const char MANUAL1[]              = "Pyч.";                       //4 знакоместа, из них 1 русский знак "ч"
const char EXTERN[]               = "Hap.";                       //4 знакоместа, из них 0 русских знаков
const char INTERN2[]              = "Bнy. П:";                    //7 знакомест, из них 2 русских "н П"
const char MANUAL2[]              = "Pyч. П:";                    //7 знакомест, из них 2 русских "ч П"
const char EXTERN2[]              = "Hap. П:";                    //7 знакомест, из них 1 русских "П"
//Тахометр
const char CURRPM[]               = " Oб/мин=";                   //8 знакомест из них 4 русских знака "б м и н"
const char EMPTY4[]               = "    ";                       //4 знакоместа, из них 0 русских знаков
const char TACHO[]                = "      Taxoмeтp      ";           //16 знакомест из них 2 русских знака "м т"
const char COMPLETE1[]            = "    OПEPAЦИЯ    ";           //16 знакомест из них 4 русских знака "П Ц И Я"
const char COMPLETE2[]            = "   ЗABEPШEHA!   ";           //16 знакомест из них 2 русских знака "З Ш"

// LiquidCrystal_1602_RUS lcd(8, 9, 10, 11, 12, 13);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

//unsigned int DEBUG_FLAG = 0;

void Print_LCD_Init()
{
  lcd.begin(16, 2);
}

void Print_LCD_Logo()
{
  lcd.setCursor(0, 0);
  lcd.print(ELS);               //16 знакомест "      ELS       ", из них 0 русских знака
  lcd.setCursor(0, 2);
  lcd.print(VERSION);           //16 знакомест "   вepcия 7e2   ", из них 3 русских знака "в и я"
}

//Для отладки
void Debug_Print_2x16(char str1[], char str2[])
{
  //DEBUG_FLAG = 1;
  char LCD_Row_1[17];    //Буферы для вывода на экран LCD.
  char LCD_Row_2[17];
  snprintf(LCD_Row_1, 17, "%s               ", str1);
  snprintf(LCD_Row_2, 17, "%s               ", str2);
  lcd.setCursor(0, 0);
  lcd.print(LCD_Row_1);
  lcd.setCursor(0, 1);
  lcd.print(LCD_Row_2);
  _delay_ms(2000);
  //DEBUG_FLAG = 0;
}

void Print()
{
  //if(DEBUG_FLAG != 0) return;

  
  char LCD_Row_1[17];    //Буферы для вывода на экран LCD. Вынесены из основного файла "Digital_Feed_7e2".
  char LCD_Row_2[17];    //Если переработать код, то можно оставить один буфер (печатаем всё равно по одной строке).
  lcd.setCursor(0, 0);

  //ПЕЧАТЬ ОШИБКИ. Сообщение в 2-х строках с русскими буквами.
  if (err_1_flag == true)
  {
    //"Limits not Set  "
    lcd.print(WARNING1_1);            //16 знакомест "   BHИMAHИE:    ", из них 2 русских знака "И И" (по сути это 1 знакоместо, а не два)
    lcd.setCursor(0, 1);
    lcd.print(WARNING1_2);            //16 знакомест "УПOPЫ HE ЗAДAHЫ!", из них 6 русских знака "У П Ы З Д Ы"
    return;
  }
  else if (err_2_flag == true)
  {
    //"Move to Init Pos"
    lcd.print(WARNING2_1);            //16 знакомест "УCTAHOBИ KAPETKУ", из них 3 русских знака "У И У"
    lcd.setCursor(0, 1);
    lcd.print(WARNING2_2);            //16 знакомест " B ИCXOДHУЮ ПOЗ.", из них 4 русских знака "И Д У Ю П З"
    return;
  }
  //
  else if (err_3_flag == true)
  {
    //
    lcd.print(WARNING3_1);            //16 знакомест "УCTAHOBИ KAPETKУ", из них 3 русских знака "У И У"
    lcd.setCursor(0, 1);
    lcd.print(WARNING3_2);            //16 знакомест " B ИCXOДHУЮ ПOЗ.", из них 4 русских знака "И Д У Ю П З"
    return;
  }
  //
  else if (Complete_flag == true)
   {
      lcd.reset();
      lcd.print(COMPLETE1);
      lcd.setCursor(0, 1);
      lcd.print(COMPLETE2);
      return;   
   }
  //================================    РЕЗЬБА   ===========================================================================================================================================
  if (Mode == Mode_Thread)
  {
    lcd.print(THREAD);                                                            //10 знакомест "PEЗЬБA    ", из них 3 русских "З Ь Б"
    int lenTP = strlen(Thread_Info[Thread_Step].Thread_Print);
    if ( lenTP == 4 )
    {
      //4 символа, например "1.00" + добавка 2 русскими знаками "мм"
      snprintf(LCD_Row_1, 5, "%s", Thread_Info[Thread_Step].Thread_Print);        //"0.25" + "мм"
      lcd.print(LCD_Row_1);
      lcd.print(MM);                                                              //2 знакоместа "мм", из них 2 русскими "м м"

      //snprintf(LCD_Row_1, 7, "%s%s", Thread_Info[Thread_Step].Thread_Print, MM);        //"0.25" + "мм"
      //lcd.print(LCD_Row_1);
    }
    else if (lenTP == 3 )
    {
      //3 символа, например " 80" + добавка "tpi"
      snprintf(LCD_Row_1, 7, "%stpi", Thread_Info[Thread_Step].Thread_Print);     //" 80" + "tpi"
      lcd.print(LCD_Row_1);
    } else {
      //6 символов, без добавки (таких нет, но на всякий случай)
      snprintf(LCD_Row_1, 7, "%s", Thread_Info[Thread_Step].Thread_Print);        //"0.25mm"
      lcd.print(LCD_Row_1);
    }
    lcd.setCursor(0, 1);
    switch (Sub_Mode_Thread)
    {
      case Sub_Mode_Thread_Int:
        lcd.print(INTERN);       //4 знакоместа "Bнy.", из них 1 русский знак "н"
        break;
      case Sub_Mode_Thread_Man:
        lcd.print(MANUAL1);       //4 знакоместа "Pyч.", из них 1 русский знак "ч"
        break;
      case Sub_Mode_Thread_Ext:
        lcd.print(EXTERN);       //4 знакоместа "Hap.", из них 0 русских
        break;
    }
//    //Тахометр
//    if (!flag_j && key_sel_flag)       //Если нажата кнопка "Select" и джойстик в нейтральном положении
//    {
//      lcd.print(CURRPM);               //8 знакомест " Oб/мин=", из них 4 русских "б м и н"
//      if (CurrentRPM > 999)
//      {
//        snprintf(LCD_Row_1, 5, "%4d", CurrentRPM);  //4 знакоместа : цифры от 1000 до 9999, русских знаков нет
//      } else {
//        snprintf(LCD_Row_1, 5, " %3d", CurrentRPM);  //4 знакоместа : пробел + цифры от 0 до 999, русских знаков нет
//      }
//    } else {
//      //--------
      lcd.print(MINRPM);              //8 знакомест " Oб/мин<", из них 4 русских знака "б м и н"
      if (strlen(Thread_Info[Thread_Step].Limit_Print) == 4)     //Если написано 4 значное число, например "1000"
      {
        snprintf(LCD_Row_1, 5, "%s", Thread_Info[Thread_Step].Limit_Print); //4 знакоместа : 4 символа впритык к символу "<"
      } else {
        snprintf(LCD_Row_1, 5, " %s", Thread_Info[Thread_Step].Limit_Print); //4 знакоместа : пробел + цифры от 0 до 999, русских знаков нет
      }
//    } //Эта скобочка - добавочка для тахометра
    lcd.print(LCD_Row_1);
  }
  //================================    ПОДАЧА СИНХРОННАЯ (ТОКАРНЫЙ РЕЖИМ)   ===========================================================================================================================================
  else if (Mode == Mode_Feed)
  {
    //lcd.print(FEED);                  //12 знакомест "CИHXP мм/oб ", из них 4 русских "И м м б"
    //snprintf(LCD_Row_1, 5, "%1d.%02d", Feed_mm / 100, Feed_mm % 100); //4 символа "0.03" ... "0.25"
    //lcd.print(LCD_Row_1);

    //Вывод информации о включении режима БЫСТРОЙ ПОДАЧИ вместо обычного вывода   
    if(Z_WORKING_RAPID_FLAG || X_WORKING_RAPID_FLAG)
    {
      lcd.print(FEED_RAPID);           //"CИHX     БЫCTPAЯ";           //16 знакомест, из них 5 русских знаков "И Б Ы Я"
    } else {
      lcd.print(FEED);                  //12 знакомест "CИHXP мм/oб ", из них 4 русских "И м м б"
      snprintf(LCD_Row_1, 5, "%1d.%02d", Feed_mm / 100, Feed_mm % 100); //4 символа "0.03" ... "0.25"
      lcd.print(LCD_Row_1);
    }
    //--
    
    lcd.setCursor(0, 1);
//    //Тахометр
//    if (!flag_j && key_sel_flag)       //Если нажата кнопка "Select" и джойстик в нейтральном положении
//    {
//      lcd.print(EMPTY4);               //4 знакоместа "    ", из них 0 русских знаков
//      lcd.print(CURRPM);               //8 знакомест " Oб/мин=", из них 4 русских "б м и н"
//      if (CurrentRPM > 999)
//      {
//        snprintf(LCD_Row_2, 5, "%4d", CurrentRPM);  //4 знакоместа : цифры от 1000 до 9999, русских знаков нет
//      } else {
//        snprintf(LCD_Row_2, 5, " %3d", CurrentRPM);  //4 знакоместа : пробел + цифры от 0 до 999, русских знаков нет
//      }
//    } else {
//      //--------
      switch (Sub_Mode_Feed)
      {
        case Sub_Mode_Feed_Int:
          lcd.print(INTERN2);           //7 знакомест "Bнy. П:", из них 2 русских "н П"
          snprintf(LCD_Row_2, 3, "%02d", Pass_Total - Pass_Nr + 1); //2 символа, русских знаков нет
          lcd.print(LCD_Row_2);
          break;
        case Sub_Mode_Feed_Man:
          lcd.print(MANUAL2);           //7 знакомест "Pyч. П:", из них 2 русских "ч П"
          snprintf(LCD_Row_2, 3, "%02d", Pass_Total);  //2 символа, русских знаков 0
          lcd.print(LCD_Row_2);
          break;
        case Sub_Mode_Feed_Ext:
          lcd.print(EXTERN2);           //7 знакомест "Hap. П:", из них 1 русских "П"
          snprintf(LCD_Row_2, 3, "%02d", Pass_Total - Pass_Nr + 1); //2 символа, русских знаков 0
          lcd.print(LCD_Row_2);
          break;
      }
      snprintf(LCD_Row_2, 8, " C:%01d.%02d", Ap / 100, Ap % 100);    //7 знакомест, русских знаков нет

//    } //Эта скобочка - добавочка для тахометра

    lcd.print(LCD_Row_2);
  }
  //================================    ПОДАЧА АСИНХРОННАЯ (ФРЕЗЕРНЫЙ РЕЖИМ)   ===========================================================================================================================================
  else if (Mode == Mode_aFeed)
  {
    //lcd.print(AFEED);                 //13 знакомест "ACИHX мм/мин ", из них 6 русских "И м м м и н"
    //snprintf(LCD_Row_1, 4, "%3d ", aFeed_mm); //3 знакоместа, 0 "русских" знаков (3-4 символа, обрезается до 3)
    //lcd.print(LCD_Row_1);
    
    //Вывод информации о включении режима БЫСТРОЙ ПОДАЧИ вместо обычного вывода   
    if(Z_WORKING_RAPID_FLAG || X_WORKING_RAPID_FLAG)
    {
      lcd.print(AFEED_RAPID);           //"ACИHX БЫCTPAЯ П.";           //16 знакомест, из них 5 русских знаков "И Б Ы Я"
    } else {
      lcd.print(AFEED);                 //13 знакомест "ACИHX мм/мин ", из них 6 русских "И м м м и н"
      snprintf(LCD_Row_1, 4, "%3d ", aFeed_mm); //3 знакоместа, 0 "русских" знаков (3-4 символа, обрезается до 3)
      lcd.print(LCD_Row_1);
    }
    //--

    lcd.setCursor(0, 1);
//    //Тахометр
//    if (!flag_j && key_sel_flag)       //Если нажата кнопка "Select" и джойстик в нейтральном положении
//    {
//      lcd.print(EMPTY4);               //4 знакоместа "    ", из них 0 русских знаков
//      lcd.print(CURRPM);               //8 знакомест " Oб/мин=", из них 4 русских "б м и н"
//      if (CurrentRPM > 999)
//      {
//        snprintf(LCD_Row_1, 5, "%4d", CurrentRPM);   //4 знакоместа : цифры от 1000 до 9999, русских знаков нет
//      } else {
//        snprintf(LCD_Row_1, 5, " %3d", CurrentRPM);  //4 знакоместа : пробел + цифры от 0 до 999, русских знаков нет
//      }
//    } else {
//      //--------
      switch (Sub_Mode_aFeed)
      {
        case Sub_Mode_aFeed_Int:
          lcd.print(INTERN2);           //7 знакомест "Bнy. П:", из них 2 русских "н П"
          snprintf(LCD_Row_1, 10, "%02d C:%01d.%02d", Pass_Total - Pass_Nr + 1, Ap / 100, Ap % 100); //9 знакомест, русских знаков 0
          break;
        case Sub_Mode_aFeed_Man:
          lcd.print(MANUAL2);           //7 знакомест "Pyч. П:", из них 2 русских "ч П"
          snprintf(LCD_Row_1, 10, "%02d C:%01d.%02d", Pass_Total, Ap / 100, Ap % 100); //9 знакомест, русских знаков 0
          break;
        case Sub_Mode_aFeed_Ext:
          lcd.print(EXTERN2);           //7 знакомест "Hap. П:", из них 1 русских "П"
          snprintf(LCD_Row_1, 10, "%02d C:%01d.%02d", Pass_Total - Pass_Nr + 1, Ap / 100, Ap % 100); //9 знакомест, русских знаков 0
          break;
      }
      
//    } //Эта скобочка - добавочка для тахометра
    lcd.print(LCD_Row_1);
  }
  //================================    КОНУС ЛЕВЫЙ   ===========================================================================================================================================
  else if (Mode == Mode_Cone_L)
  {
    
//    lcd.print(CONE_L);                          //7 знакомест "KOHУC <", из них 1 русский  "У"
//    //OLD
//    //snprintf(LCD_Row_1, 10, "%s %1d.%02d", Cone_Info[Cone_Step].Cone_Print, Feed_mm / 100, Feed_mm % 100); //4 символа " KM0" или " 45°" + 5 символов = 1 символ " " + 4 символа "0.10"
//    //NEW Из-за переделки КОНУСОВ на асинхронный режим
//    snprintf(LCD_Row_1, 10, "%s  %3d", Cone_Info[Cone_Step].Cone_Print, aFeed_mm); //4 символа " KM0" или " 45°" + 5 символов = 2 символа "  " + 3 символа "100"
//    lcd.print(LCD_Row_1);

    //Вывод информации о включении режима БЫСТРОЙ ПОДАЧИ вместо обычного вывода   
    if(Z_WORKING_RAPID_FLAG || X_WORKING_RAPID_FLAG)
    {
      lcd.print(CONE_L_RAPID);           //"KOHУC <  БЫCTPAЯ";           //16 знакомест, из них 5 русских знаков "Б Ы Я"
    } else {
      lcd.print(CONE_L);                          //7 знакомест "KOHУC <", из них 1 русский  "У"
      //OLD
      //snprintf(LCD_Row_1, 10, "%s %1d.%02d", Cone_Info[Cone_Step].Cone_Print, Feed_mm / 100, Feed_mm % 100); //4 символа " KM0" или " 45°" + 5 символов = 1 символ " " + 4 символа "0.10"
      //NEW Из-за переделки КОНУСОВ на асинхронный режим
      snprintf(LCD_Row_1, 10, "%s  %3d", Cone_Info[Cone_Step].Cone_Print, aFeed_mm); //4 символа " KM0" или " 45°" + 5 символов = 2 символа "  " + 3 символа "100"
      lcd.print(LCD_Row_1);
    }
    //--
   
    lcd.setCursor(0, 1);
    if (Sub_Mode_Cone == Sub_Mode_Cone_Int)
    {
      //lcd.print(INTERN);                        //4 знакоместа "Bнy.", из них 1 русский знак "н"
      //snprintf(LCD_Row_2, 13, " П:%02d D:%1d.%01d", Pass_Total-Pass_Nr+1, Ap/100, Ap%100);
      //lcd.print(LCD_Row_2);

      lcd.print(INTERN2);                         //7 знакомест "Pyч. П:", из них 2 русских "ч П"
      snprintf(LCD_Row_2, 10, "%02d C:%01d.%02d", Pass_Total-Pass_Nr+1, Ap/100, Ap%100);
      lcd.print(LCD_Row_2);
      
    }
    else if (Sub_Mode_Cone == Sub_Mode_Cone_Man)
    {
      //lcd.print(MANUAL1);                        //4 знакоместа "Pyч.", из них 1 русский знак "ч"
      //snprintf(LCD_Row_2, 13, " П:%02d D:%1d.%01d", Pass_Total, Ap/100, Ap%100);
      //lcd.print(LCD_Row_2);

      lcd.print(MANUAL2);                        //7 знакомест "Pyч. П:", из них 2 русских "ч П"
      snprintf(LCD_Row_2, 10, "%02d C:%01d.%02d", Pass_Total, Ap/100, Ap%100);
      lcd.print(LCD_Row_2);

      
    }
    else if (Sub_Mode_Cone == Sub_Mode_Cone_Ext)
    {
      //lcd.print(EXTERN);                        //4 знакоместа "Hap.", из них 0 русских
      //snprintf(LCD_Row_2, 13, " П:%02d D:%1d.%01d", Pass_Total-Pass_Nr+1, Ap/100, Ap%100);
      //lcd.print(LCD_Row_2);

      lcd.print(EXTERN2);                       //7 знакомест "Hap. П:", из них 1 русских "П"
      snprintf(LCD_Row_2, 10, "%02d C:%01d.%02d", Pass_Total-Pass_Nr+1, Ap/100, Ap%100);
      lcd.print(LCD_Row_2);
    }

//    //Тахометр
//    if (!flag_j && key_sel_flag)       //Если нажата кнопка "Select" и джойстик в нейтральном положении
//    {
//      lcd.print(CURRPM);               //8 знакомест " Oб/мин=", из них 4 русских "б м и н"
//      if (CurrentRPM > 999)
//      {
//        snprintf(LCD_Row_2, 5, "%4d", CurrentRPM);  //цифры от 1000 до 9999, русских знаков нет
//      } else {
//        snprintf(LCD_Row_2, 5, " %3d", CurrentRPM);  //пробел + цифры от 0 до 999, русских знаков нет
//      }
//      lcd.print(LCD_Row_2);
//    } else {
//      //--------
      
      //lcd.print(EMPTY12);                           //12 знакомест, из них 0 русских

//    } //Эта скобочка - добавочка для тахометра
  }
  //================================    КОНУС ПРАВЫЙ   ===========================================================================================================================================
  else if (Mode == Mode_Cone_R)
  {
//    lcd.print(CONE_R);                          //7 знакомест "KOHУC >", из них 1 русский  "У"
//    //OLD
//    //snprintf(LCD_Row_1, 10, "%s %1d.%02d", Cone_Info[Cone_Step].Cone_Print, Feed_mm / 100, Feed_mm % 100); //4 символа " KM0" или " 45°" + 5 символов = 1 символ " " + 4 символа "0.10"
//    //NEW Из-за переделки КОНУСОВ на асинхронный режим
//    snprintf(LCD_Row_1, 10, "%s  %3d", Cone_Info[Cone_Step].Cone_Print, aFeed_mm); //4 символа " KM0" или " 45°" + 5 символов = 2 символа "  " + 3 символа "100"
//    lcd.print(LCD_Row_1);

    //Вывод информации о включении режима БЫСТРОЙ ПОДАЧИ вместо обычного вывода   
    if(Z_WORKING_RAPID_FLAG || X_WORKING_RAPID_FLAG)
    {
      lcd.print(CONE_R_RAPID);           //"KOHУC <  БЫCTPAЯ";           //16 знакомест, из них 5 русских знаков "Б Ы Я"
    } else {
      lcd.print(CONE_R);                          //7 знакомест "KOHУC <", из них 1 русский  "У"
      //OLD
      //snprintf(LCD_Row_1, 10, "%s %1d.%02d", Cone_Info[Cone_Step].Cone_Print, Feed_mm / 100, Feed_mm % 100); //4 символа " KM0" или " 45°" + 5 символов = 1 символ " " + 4 символа "0.10"
      //NEW Из-за переделки КОНУСОВ на асинхронный режим
      snprintf(LCD_Row_1, 10, "%s  %3d", Cone_Info[Cone_Step].Cone_Print, aFeed_mm); //4 символа " KM0" или " 45°" + 5 символов = 2 символа "  " + 3 символа "100"
      lcd.print(LCD_Row_1);
    }
    //--
    
    lcd.setCursor(0, 1);
    if (Sub_Mode_Cone == Sub_Mode_Cone_Int)
    {
      //lcd.print(INTERN);                        //4 знакоместа "Bнy.", из них 1 русский знак "н"
      //snprintf(LCD_Row_2, 13, " П:%02d D:%1d.%01d", Pass_Total-Pass_Nr+1, Ap/100, Ap%100);
      //lcd.print(LCD_Row_2);

      lcd.print(INTERN2);                         //7 знакомест "Pyч. П:", из них 2 русских "ч П"
      snprintf(LCD_Row_2, 10, "%02d C:%01d.%02d", Pass_Total-Pass_Nr+1, Ap/100, Ap%100);
      lcd.print(LCD_Row_2);
      
    }
    else if (Sub_Mode_Cone == Sub_Mode_Cone_Man)
    {
      //lcd.print(MANUAL1);                        //4 знакоместа "Pyч.", из них 1 русский знак "ч"
      //snprintf(LCD_Row_2, 13, " П:%02d D:%1d.%01d", Pass_Total, Ap/100, Ap%100);
      //lcd.print(LCD_Row_2);

      lcd.print(MANUAL2);                        //7 знакомест "Pyч. П:", из них 2 русских "ч П"
      snprintf(LCD_Row_2, 10, "%02d C:%01d.%02d", Pass_Total, Ap/100, Ap%100);
      lcd.print(LCD_Row_2);
    }
    else if (Sub_Mode_Cone == Sub_Mode_Cone_Ext)
    {
      //lcd.print(EXTERN);                        //4 знакоместа "Hap.", из них 0 русских
      //snprintf(LCD_Row_2, 13, " П:%02d D:%1d.%01d", Pass_Total-Pass_Nr+1, Ap/100, Ap%100);
      //lcd.print(LCD_Row_2);

      lcd.print(EXTERN2);                       //7 знакомест "Hap. П:", из них 1 русских "П"
      snprintf(LCD_Row_2, 10, "%02d C:%01d.%02d", Pass_Total-Pass_Nr+1, Ap/100, Ap%100);
      lcd.print(LCD_Row_2);
    }
//    //Тахометр
//    if (!flag_j && key_sel_flag)       //Если нажата кнопка "Select" и джойстик в нейтральном положении
//    {
//      lcd.print(CURRPM);               //8 знакомест " Oб/мин=", из них 4 русских "б м и н"
//      if (CurrentRPM > 999)
//      {
//        snprintf(LCD_Row_2, 5, "%4d", CurrentRPM);  //цифры от 1000 до 9999, русских знаков нет
//      } else {
//        snprintf(LCD_Row_2, 5, " %3d", CurrentRPM);  //пробел + цифры от 0 до 999, русских знаков нет
//      }
//      lcd.print(LCD_Row_2);
//    } else {
//      //--------
      
      //lcd.print(EMPTY12);                           //12 знакомест, из них 0 русских

//    } //Эта скобочка - добавочка для тахометра
  }
  //================================    РЕЗЕРВНЫЙ РЕЖИМ   ===========================================================================================================================================
  else if (Mode == Mode_Reserve)
  {
    //lcd.print(RESERV1);                           //16 знакомест "    PEЗEPBHЫЙ   ", из них 3 русских знаков "З Ы Й"
    //lcd.setCursor(0, 1);
    //lcd.print(RESERV2);                           //16 знакомест "      PEЖИM     ", из них 2 русских знака "Ж И"
    //return;                                       //На удивление, это уменьшает размер программы

    //Тахометр
    lcd.print(TACHO);                               //16 знакомест "    Taxoмeтp    " из них 2 русских знака "м т"
    lcd.setCursor(0, 1);

    lcd.print(EMPTY4);               //4 знакоместа "    ", из них 0 русских знаков
    lcd.print(CURRPM);               //8 знакомест " Oб/мин=", из них 4 русских "б м и н"
//    if (!flag_j)       //Если джойстик в нейтральном положении
//    {
      if (CurrentRPM > 999)
      {
        snprintf(LCD_Row_1, 5, "%4d", CurrentRPM);  //цифры от 1000 до 9999, русских знаков нет
      } else {
        snprintf(LCD_Row_1, 5, " %3d", CurrentRPM);  //пробел + цифры от 0 до 999, русских знаков нет
      }
//    } else {
//      snprintf(LCD_Row_1, 5, " ???");  //пробел + ???
//    }
    lcd.print(LCD_Row_1);
    //-
  }
  //================================    РЕЖИМ ШАРа (Сфероточка)   ===========================================================================================================================================
  else if (Mode == Mode_Sphere)
  {
    if (!key_sel_flag)
    {
      lcd.print(SPHERE);                         //6 знакомест "ШAP  \xEC", из них 1 русский  "Ш" и один спец-символ диаметра.
      snprintf(LCD_Row_1, 11, "%2ld.%01ld  %1d.%02d  ", Sph_R_mm * 2 / 100, Sph_R_mm * 2 / 10 % 10, Feed_mm / 100, Feed_mm % 100); //10 символов, просто цифры и пробел
      lcd.print(LCD_Row_1);
      lcd.setCursor(0, 1);
      if (Sub_Mode_Sphere == Sub_Mode_Sphere_Int)
      {
        lcd.print(IMPOSSIBLE);                 //16 знакомест "PEЖИM HEBOЗMOЖEH", перебор, из них 4 русских знака "Ж И З Ж"
        return;
      }
      else
      {
        if (Sub_Mode_Sphere == Sub_Mode_Sphere_Man)
        {
          lcd.print(MANUAL1);                       //4 знакоместа "Pyч.", из них 1 русский знак "ч"
        }
        else if (Sub_Mode_Sphere == Sub_Mode_Sphere_Ext)
        {
          lcd.print(EXTERN);                        //4 знакоместа "Hap.", из них 0 русских
        }
        lcd.print(NOZKA);                           //8 знакомест " Hoжкa \xEC", из них 2 русских знака "ж к", и один спец-символ диаметра.
        snprintf(LCD_Row_1, 5, "%ld.%1ld%s", Bar_R_mm * 2 / 100, Bar_R_mm * 2 % 100, "00"); //"95.0" - 4 символа (обрезается до 4 символов, на конце нули)
        lcd.print(LCD_Row_1);
      }
    }
    else
    {
      lcd.reset(); //Вызываем добавленную функцию для сброса набора символов. Если её не вызывать, спонтанно остаются хвосты старых символов
      lcd.print(REZETZ_WIDTH);                     //12 знакомест, из них 4 русских знака "Ш и з ц"
      snprintf(LCD_Row_1, 5, "%1d.%02d  ", Cutter_Width / 100, Cutter_Width % 100); //"3.00" 4 символа (обрезается до 4 символов)
      lcd.print(LCD_Row_1);
      lcd.setCursor(0, 1);
      lcd.print(REZETZ_STEP);                      //12 знакомест "Шaг oбpaб.  ", из них 4 русских знака "Ш г б б"
      snprintf(LCD_Row_1, 5, "%1d.%02d  ", Cutting_Width / 100, Cutting_Width % 100); //"0.10" 4 символа (обрезается до 4 символов)
      lcd.print(LCD_Row_1);
    }
  }
  //================================    "ДЕЛИЛКА"   ===========================================================================================================================================
  else if (Mode == Mode_Divider)
  {
    //long Spindle_Angle = Enc_Pos * 36000 / ENC_TICK;

    //test x2
    
    long Spindle_Angle;
    //if(Enc_Pos == 0 && Enc_Pos_Divider < 0)
    //{
    //  Spindle_Angle = (2 * ENC_TICK + Enc_Pos_Divider) * 36000 / (2 * ENC_TICK);
    //} else {
      Spindle_Angle = (2 * Enc_Pos + Enc_Pos_Divider) * 36000 / (2 * ENC_TICK);
    //}
    //if(debug1++ > 200)
    //{
    //  debug1 = 0;
    //Serial.print("\n\r");
    //Serial.print("Enc_Pos=");Serial.print(Enc_Pos);Serial.print("\n\r");
    //Serial.print("Enc_Pos_Divider=");Serial.print(Enc_Pos_Divider);Serial.print("\n\r");
    //Serial.print("2 summ=");Serial.print(2 * Enc_Pos + Enc_Pos_Divider);Serial.print("\n\r");
    //Serial.print("Spindle_Angle=");Serial.print(Spindle_Angle);Serial.print("\n\r");
    //}
    
    
    long Required_Angle = 36000 * (Current_Tooth - 1) / Total_Tooth;
    lcd.print(DIVIDER1);      //3 знакоместа "Зaд", из них 2 русских знака "З д"
    snprintf(LCD_Row_1, 14, ":%3ld.%02ld Z:%3d", Required_Angle / 100, Required_Angle % 100, Total_Tooth);
    lcd.print(LCD_Row_1);
    lcd.setCursor(0, 1);
    lcd.print(DIVIDER2);      //3 знакоместа "Teк", из них 1 русский знак "к"
    snprintf(LCD_Row_1, 14, ":%3ld.%02ld n:%3d", Spindle_Angle / 100, Spindle_Angle % 100, Current_Tooth);   
    lcd.print(LCD_Row_1);
  }
}
