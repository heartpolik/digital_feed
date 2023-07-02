#include "LiquidCrystal_1602_RUS.h"

wchar_t char_utf8[] = L" ";

//user_custom_symbols - количество символов, доступное пользователю для использования в своих целях (не более 8)
//Всего переопределяемых символов в LCD - 8.
//Символы с индексом от 0 до (7 - user_custom_symbols) используются библиотекой
//Символы с индексом от (8 - user_custom_symbols) до 7 - можно переопределять пользователю
//По умолчанию количество переопределяемых символов равно 0
LiquidCrystal_1602_RUS :: LiquidCrystal_1602_RUS(uint8_t rs,  uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t user_custom_symbols) : LiquidCrystal (rs, enable, d0, d1, d2, d3)
{
  max_symbol_count = 8 - user_custom_symbols;
  symbol_index = 0;
  cursor_col = 0;
  cursor_row = 0;
  ResetAllIndex();//Сброс значений индексов (неинициализированы = 255)
}

void LiquidCrystal_1602_RUS::clear()
{
  LiquidCrystal::clear();
  ResetAllIndex();
}

//Добавляем новую функцию для очистки набора символов
void LiquidCrystal_1602_RUS::reset()
{
  ResetAllIndex();
}
//-

void LiquidCrystal_1602_RUS::setCursor(uint8_t col, uint8_t row)
{
  cursor_col = col;
  cursor_row = row;
  LiquidCrystal::setCursor(cursor_col, cursor_row);
}
uint8_t LiquidCrystal_1602_RUS::getCursorCol()
{
  return cursor_col;
}
uint8_t LiquidCrystal_1602_RUS::getCursorRow()
{
  return cursor_row;
}

uint8_t LiquidCrystal_1602_RUS::mbtowc(wchar_t *_chr, char *_str, uint8_t mb_num) {
  if (mb_num != 2) return 0;
  if ((_str[0] & 0xC0) == 0xC0 && (_str[1] & 0x80) == 0x80) {
    *_chr = ((_str[0] & 0x1F) << 6) + (_str[1] & 0x3F);
    return 2;
  }
  else {
    *_chr = _str[0];
    return 1;
  }
}

void LiquidCrystal_1602_RUS::print(const char *c_str) {
  wchar_t _str;
  int current_char = 0;
  int size = strlen(c_str);

  while (current_char < size)
  {
    current_char += mbtowc(&_str, (char *)c_str + current_char, 2);
    printwc(_str);
    cursor_col++;
  }
}
void LiquidCrystal_1602_RUS::print(int val, int base) {
  cursor_col += LiquidCrystal::print(val, base);
}
void LiquidCrystal_1602_RUS::print(unsigned int val, int base) {
  cursor_col += LiquidCrystal::print(val, base);
}
void LiquidCrystal_1602_RUS::print(long val, int base) {
  cursor_col += LiquidCrystal::print(val, base);
}
void LiquidCrystal_1602_RUS::print(unsigned long val, int base) {
  cursor_col += LiquidCrystal::print(val, base);
}
void LiquidCrystal_1602_RUS::print(char val, int base) {
  cursor_col += LiquidCrystal::print(val, base);
}
void LiquidCrystal_1602_RUS::print(unsigned char val, int base) {
  cursor_col += LiquidCrystal::print(val, base);
}
void LiquidCrystal_1602_RUS::print(const String &str) {
  wchar_t _str;
  const char *c_str = str.c_str();
  int current_char = 0;
  int size = str.length();

  while (current_char < size)
  {
    current_char += mbtowc(&_str, (char*)c_str + current_char, 2);
    printwc(_str);
    cursor_col++;
  }
}

void LiquidCrystal_1602_RUS::print(double val, int base) {
  cursor_col += LiquidCrystal::print(val, base);
}
void LiquidCrystal_1602_RUS::print(const wchar_t *_str) {
  int current_char  = 0;
  int size = 0;

  //Определяем длину строки (количество символов)
  while (_str[size] != 0)
  {
    size++;
  }

  while (current_char < size)
  {
    printwc(_str[current_char]);
    current_char++;
    cursor_col++;
  }

}
void LiquidCrystal_1602_RUS::CharSetToLCD(uint8_t *array, uint8_t *index)
{
  uint8_t x, y;

  if (*index == 255) // Если символ еще не создан, то создаем
  {
    x = getCursorCol();
    y = getCursorRow();
    createChar(symbol_index, (uint8_t *)array);// Создаем символ на текущем (по очереди) месте в знакогенераторе (от 0 до MAX_SYMBOL_COUNT)
    setCursor(x, y);
    write(symbol_index);// Выводим символ на экран
    //Запомианем, что букве соответствует определенный индекс
    *index = symbol_index;
    symbol_index++;
    if (symbol_index >= max_symbol_count)
    {
      symbol_index = 0;
      ResetAllIndex();
    }
  }
  else   //Иначе печатаем уже существующий
    write(*index);
}
void LiquidCrystal_1602_RUS::ResetAllIndex()
{
  symbol_index = 0;

#ifdef _rus_B
  index_rus_B = 255;					//Б
#endif

#ifdef _rus_G
  index_rus_G = 255;					//Г
#endif

#ifdef _rus_D
  index_rus_D = 255;					//Д
#endif

#ifdef _rus_ZH
  index_rus_ZH = 255;					//Ж
#endif

#ifdef _rus_Z
  index_rus_Z = 255;					//З
#endif

#ifdef _rus_I
  index_rus_I = 255;					//И
#endif

#ifdef _rus_II
  index_rus_II = 255;					//Й
#endif

#ifdef _rus_L
  index_rus_L = 255;					//Л
#endif

#ifdef _rus_P
  index_rus_P = 255;					//П
#endif

#ifdef _rus_U
  index_rus_U = 255;					//У
#endif

#ifdef _rus_F
  index_rus_F = 255;					//Ф
#endif

#ifdef _rus_TS
  index_rus_TS = 255;					//Ц
#endif

#ifdef _rus_CH
  index_rus_CH = 255;					//Ч
#endif

#ifdef _rus_SH
  index_rus_SH = 255;					//Ш
#endif

#ifdef _rus_SCH
  index_rus_SCH = 255;					//Щ
#endif

#ifdef _rus_tverd
  index_rus_tverd = 255;				//Ъ
#endif

#ifdef _rus_Y
  index_rus_Y = 255;					//Ы
#endif

#ifdef _rus_myagk
  index_rus_myagk = 255;				//Ь
#endif

#ifdef _rus_EE
  index_rus_EE = 255;					//Э
#endif

#ifdef _rus_YU
  index_rus_YU = 255;					//Ю
#endif

#ifdef _rus_YA
  index_rus_YA = 255;					//Я
#endif

#ifdef _rus_b
  index_rus_b = 255;					//б
#endif

#ifdef _rus_v
  index_rus_v = 255;					//в
#endif

#ifdef _rus_g
  index_rus_g = 255;					//г
#endif

#ifdef _rus_d
  index_rus_d = 255;					//д
#endif

#ifdef _rus_yo
  index_rus_yo = 255;					//ё
#endif

#ifdef _rus_zh
  index_rus_zh = 255;					//ж
#endif

#ifdef _rus_z
  index_rus_z = 255;					//з
#endif

#ifdef _rus_i
  index_rus_i = 255;					//и
#endif

#ifdef _rus_ii
  index_rus_ii = 255;					//й
#endif

#ifdef _rus_k
  index_rus_k = 255;					//к
#endif

#ifdef _rus_l
  index_rus_l = 255;					//л
#endif

#ifdef _rus_m
  index_rus_m = 255;					//м
#endif

#ifdef _rus_n
  index_rus_n = 255;					//н
#endif

#ifdef _rus_p
  index_rus_p = 255;					//п
#endif

#ifdef _rus_t
  index_rus_t = 255;					//т
#endif

#ifdef _rus_u
  index_rus_u = 255;					//y
#endif

#ifdef _rus_f
  index_rus_f = 255;					//ф
#endif

#ifdef _rus_ts
  index_rus_ts = 255;					//ц
#endif

#ifdef _rus_ch
  index_rus_ch = 255;					//ч
#endif

#ifdef _rus_sh
  index_rus_sh = 255;					//ш
#endif

#ifdef _rus_sch
  index_rus_sch = 255;					//щ
#endif

#ifdef _rus_tverd_mal
  index_rus_tverd_mal = 255;			//ъ
#endif

#ifdef _rus_y
  index_rus_y = 255;					//ы
#endif

#ifdef _rus_myagk_mal
  index_rus_myagk_mal = 255;			//ь
#endif

#ifdef _rus_ee
  index_rus_ee = 255;					//э
#endif

#ifdef _rus_yu
  index_rus_yu = 255;					//ю
#endif

#ifdef _rus_ya
  index_rus_ya = 255;					//я
#endif

}

void LiquidCrystal_1602_RUS::printwc(const wchar_t _chr) {
  uint8_t rus_[8];
  switch (_chr)
  {
    //Русский алфавит, требующий новых символов
    //Единовременно может быть заменено только 8 символов
#ifdef _rus_B
    case 1041: //Б
      memcpy_PF(rus_, (_uint_farptr_t)rus_B, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_B);
      break;
#endif
#ifdef _rus_G
    case 1043: //Г
      memcpy_PF(rus_, (_uint_farptr_t)rus_G, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_G);
      break;
#endif
#ifdef _rus_D
    case 1044: //Д
      memcpy_PF(rus_, (_uint_farptr_t)rus_D, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_D);
      break;
#endif
#ifdef _rus_ZH
    case 1046: //Ж
      memcpy_PF(rus_, (_uint_farptr_t)rus_ZH, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ZH);
      break;
#endif
#ifdef _rus_Z
    case 1047: //З
      memcpy_PF(rus_, (_uint_farptr_t)rus_Z, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_Z);
      break;
#endif
#ifdef _rus_I
    case 1048: //И
      memcpy_PF(rus_, (_uint_farptr_t)rus_I, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_I);
      break;
#endif
#ifdef _rus_II
    case 1049: //Й
      memcpy_PF(rus_, (_uint_farptr_t)rus_II, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_II);
      break;
#endif
#ifdef _rus_L
    case 1051: //Л
      memcpy_PF(rus_, (_uint_farptr_t)rus_L, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_L);
      break;
#endif
#ifdef _rus_P
    case 1055: //П
      memcpy_PF(rus_, (_uint_farptr_t)rus_P, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_P);
      break;
#endif
#ifdef _rus_U
    case 1059: //У
      memcpy_PF(rus_, (_uint_farptr_t)rus_U, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_U);
      break;
#endif
#ifdef _rus_F
    case 1060: //Ф
      memcpy_PF(rus_, (_uint_farptr_t)rus_F, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_F);
      break;
#endif
#ifdef _rus_TS
    case 1062: //Ц
      memcpy_PF(rus_, (_uint_farptr_t)rus_TS, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_TS);
      break;
#endif
#ifdef _rus_CH
    case 1063: //Ч
      memcpy_PF(rus_, (_uint_farptr_t)rus_CH, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_CH);
      break;
#endif
#ifdef _rus_SH
	case 1064: //Ш
      memcpy_PF(rus_, (_uint_farptr_t)rus_SH, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_SH);
      break;
#endif
#ifdef _rus_SCH
    case 1065: //Щ
      memcpy_PF(rus_, (_uint_farptr_t)rus_SCH, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_SCH);
      break;
#endif
#ifdef _rus_tverd
    case 1066: //Ъ
      memcpy_PF(rus_, (_uint_farptr_t)rus_tverd, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_tverd);
      break;
#endif
#ifdef _rus_Y
case 1067: //Ы
      memcpy_PF(rus_, (_uint_farptr_t)rus_Y, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_Y);
      break;
#endif
#ifdef _rus_myagk
    case 1068: //Ь
      memcpy_PF(rus_, (_uint_farptr_t)rus_myagk, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_myagk);
      break;
#endif
#ifdef _rus_EE
    case 1069: //Э
      memcpy_PF(rus_, (_uint_farptr_t)rus_EE, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_EE);
      break;
#endif
#ifdef _rus_YU
    case 1070: //Ю
      memcpy_PF(rus_, (_uint_farptr_t)rus_YU, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_YU);
      break;
#endif
#ifdef _rus_YA
    case 1071: //Я
      memcpy_PF(rus_, (_uint_farptr_t)rus_YA, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_YA);
      break;
#endif
#ifdef _rus_b
    case 1073: //б
      memcpy_PF(rus_, (_uint_farptr_t)rus_b, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_b);
      break;
#endif
#ifdef _rus_v
    case 1074: //в
      memcpy_PF(rus_, (_uint_farptr_t)rus_v, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_v);
      break;
#endif
#ifdef _rus_g
    case 1075: //г
      memcpy_PF(rus_, (_uint_farptr_t)rus_g, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_g);
      break;
#endif
#ifdef _rus_d
    case 1076: //д
      memcpy_PF(rus_, (_uint_farptr_t)rus_d, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_d);
      break;
#endif
#ifdef _rus_yo
    case 1105: //ё
      memcpy_PF(rus_, (_uint_farptr_t)rus_yo, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_yo);
      break;
#endif
#ifdef _rus_zh
    case 1078: //ж
      memcpy_PF(rus_, (_uint_farptr_t)rus_zh, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_zh);
      break;
#endif
#ifdef _rus_z
    case 1079: //з
      memcpy_PF(rus_, (_uint_farptr_t)rus_z, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_z);
      break;
#endif
#ifdef _rus_i
    case 1080: //и
      memcpy_PF(rus_, (_uint_farptr_t)rus_i, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_i);
      break;
#endif
#ifdef _rus_ii
    case 1081: //й
      memcpy_PF(rus_, (_uint_farptr_t)rus_ii, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ii);
      break;
#endif
#ifdef _rus_k
    case 1082: //к
      memcpy_PF(rus_, (_uint_farptr_t)rus_k, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_k);
      break;
#endif
#ifdef _rus_l
    case 1083: //л
      memcpy_PF(rus_, (_uint_farptr_t)rus_l, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_l);
      break;
#endif
#ifdef _rus_m
    case 1084: //м
      memcpy_PF(rus_, (_uint_farptr_t)rus_m, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_m);
      break;
#endif
#ifdef _rus_n
    case 1085: //н
      memcpy_PF(rus_, (_uint_farptr_t)rus_n, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_n);
      break;
#endif
#ifdef _rus_p
    case 1087: //п
      memcpy_PF(rus_, (_uint_farptr_t)rus_p, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_p);
      break;
#endif
#ifdef _rus_t
    case 1090: //т
      memcpy_PF(rus_, (_uint_farptr_t)rus_t, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_t);
      break;
#endif
#ifdef _rus_f
    case 1092: //ф
      memcpy_PF(rus_, (_uint_farptr_t)rus_f, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_f);
      break;
#endif
#ifdef _rus_ts
    case 1094: //ц
      memcpy_PF(rus_, (_uint_farptr_t)rus_ts, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ts);
      break;
#endif
#ifdef _rus_ch
    case 1095: //ч
      memcpy_PF(rus_, (_uint_farptr_t)rus_ch, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ch);
      break;
#endif
#ifdef _rus_sh
    case 1096: //ш
      memcpy_PF(rus_, (_uint_farptr_t)rus_sh, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_sh);
      break;
#endif
#ifdef _rus_sch
    case 1097: //щ
      memcpy_PF(rus_, (_uint_farptr_t)rus_sch, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_sch);
      break;
#endif
#ifdef _rus_tverd_mal
    case 1098: //ъ
      memcpy_PF(rus_, (_uint_farptr_t)rus_tverd_mal, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_tverd_mal);
      break;
#endif
#ifdef _rus_y
    case 1099: //ы
      memcpy_PF(rus_, (_uint_farptr_t)rus_y, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_y);
      break;
#endif
#ifdef _rus_myagk_mal
    case 1100: //ь
      memcpy_PF(rus_, (_uint_farptr_t)rus_myagk_mal, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_myagk_mal);
      break;
#endif
#ifdef _rus_ee
    case 1101: //э
      memcpy_PF(rus_, (_uint_farptr_t)rus_ee, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ee);
      break;
#endif
#ifdef _rus_yu
    case 1102: //ю
      memcpy_PF(rus_, (_uint_farptr_t)rus_yu, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_yu);
      break;
#endif
#ifdef _rus_ya
    case 1103: //я
      memcpy_PF(rus_, (_uint_farptr_t)rus_ya, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ya);
      break;
#endif

#ifdef _RUS_TO_ENG
    //Русский алфавит, использующий одинаковые с английским алфавитом символы
    case 1040: //А
      LiquidCrystal::print("A");
      break;
    case 1042: //В
      LiquidCrystal::print("B");
      break;
    case 1045: //Е
      LiquidCrystal::print("E");
      break;
    case 1025: //Ё
      LiquidCrystal::print("E");
      break;
    case 1050: //К
      LiquidCrystal::print("K");
      break;
    case 1052: //M
      LiquidCrystal::print("M");
      break;
    case 1053: //H
      LiquidCrystal::print("H");
      break;
    case 1054: //O
      LiquidCrystal::print("O");
      break;
    case 1056: //P
      LiquidCrystal::print("P");
      break;
    case 1057: //C
      LiquidCrystal::print("C");
      break;
    case 1058: //T
      LiquidCrystal::print("T");
      break;
    case 1061: //X
      LiquidCrystal::print("X");
      break;
    case 1072: //а
      LiquidCrystal::print("a");
      break;
    case 1077: //е
      LiquidCrystal::print("e");
      break;
    case 1086: //o
      LiquidCrystal::print("o");
      break;
    case 1088: //p
      LiquidCrystal::print("p");
      break;
    case 1089: //c
      LiquidCrystal::print("c");
      break;
    case 1091: //y
      LiquidCrystal::print("y");
      break;
    case 1093: //x
      LiquidCrystal::print("x");
      break;
#endif


#ifdef _DEGREE
    case 0x00B0: //Знак градуса Dec 176
      LiquidCrystal::write(223);
      break;
#endif

    //Английский алфавит без изменения
    default:
      LiquidCrystal::print((char)_chr);
      break;
  }
}

//Перевод символа из кодировки ASCII в UTF-8 (для печати расширенных русских символов на LCD)
wchar_t *LiquidCrystal_1602_RUS::asciiutf8(unsigned char ascii)
{
  if (ascii == 168) *char_utf8 = 0x401; //код ASCII буквы Ё
  else if (ascii == 184) *char_utf8 = 0x451; //код ASCII буквы ё
  else if (ascii >= 192) //остальные буквы русского алфавита
  {
    *char_utf8 = ascii + 848;
  }
  else *char_utf8 = ascii;

  return char_utf8;
}

//Б
const byte rus_B[8] PROGMEM = {
  0b11111,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b11110,
  0b00000
};
//Г
const byte rus_G[8] PROGMEM = {
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b00000
};
//Д
const byte rus_D[8] PROGMEM = {
  0b00110,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b11111,
  0b10001
};
//Ж
const byte rus_ZH[8] PROGMEM = {
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b00000
};
//З
const byte rus_Z[8] PROGMEM = {
  0b01110,
  0b10001,
  0b00001,
  0b00110,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//И
const byte rus_I[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};
//Й
const byte rus_II[8] PROGMEM = {
  0b10101,
  0b10001,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};
//Л
const byte rus_L[8] PROGMEM = {
  0b00111,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b10001,
  0b00000
};
//П
const byte rus_P[8] PROGMEM = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b00000
};
//У
const byte rus_U[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//Ф
const byte rus_F[8] PROGMEM = {
  0b00100,
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b00100,
  0b00000
};
//Ц
const byte rus_TS[8] PROGMEM = {
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b11111,
  0b00001
};
//Ч
const byte rus_CH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b00001,
  0b00001,
  0b00000
};
//Ш
const byte rus_SH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00000
};
//Щ
const byte rus_SCH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00001
};
//Ъ
const byte rus_tverd[8] PROGMEM = {
  0b11000,
  0b01000,
  0b01000,
  0b01110,
  0b01001,
  0b01001,
  0b01110,
  0b00000
};
//Ы
const byte rus_Y[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b11101,
  0b10011,
  0b10011,
  0b11101,
  0b00000
};
//Ь
const byte rus_myagk[8] PROGMEM = {
  0b10000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b11110,
  0b00000
};
//Э
const byte rus_EE[8] PROGMEM = {
  0b01110,
  0b10001,
  0b00001,
  0b00111,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//Ю
const byte rus_YU[8] PROGMEM = {
  0b10010,
  0b10101,
  0b10101,
  0b11101,
  0b10101,
  0b10101,
  0b10010,
  0b00000
};
//Я
const byte rus_YA[8] PROGMEM = {
  0b01111,
  0b10001,
  0b10001,
  0b01111,
  0b00101,
  0b01001,
  0b10001,
  0b00000
};
const byte rus_b[8] PROGMEM = {
  0b00011,
  0b01100,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};//б
const byte rus_v[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11110,
  0b10001,
  0b11110,
  0b10001,
  0b11110,
  0b00000
};//в
const byte rus_g[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11110,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b00000
};//г
const byte rus_d[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00110,
  0b01010,
  0b01010,
  0b01010,
  0b11111,
  0b10001
};//д
const byte rus_yo[8] PROGMEM = {
  0b01010,
  0b00000,
  0b01110,
  0b10001,
  0b11111,
  0b10000,
  0b01111,
  0b00000
};//ё
const byte rus_zh[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b01110,
  0b10101,
  0b10101,
  0b00000
};//ж
const byte rus_z[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00110,
  0b10001,
  0b01110,
  0b00000
};//з
const byte rus_i[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};//и
const byte rus_ii[8] PROGMEM = {
  0b01010,
  0b00100,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};//й
const byte rus_k[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10100,
  0b11000,
  0b10100,
  0b10010,
  0b00000
};//к
const byte rus_l[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00111,
  0b01001,
  0b01001,
  0b01001,
  0b10001,
  0b00000
};//л
const byte rus_m[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b11011,
  0b10101,
  0b10001,
  0b10001,
  0b00000
};//м
const byte rus_n[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b11111,
  0b10001,
  0b10001,
  0b00000
};//н
const byte rus_p[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b00000
};//п
const byte rus_t[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};//т
const byte rus_f[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b10101,
  0b01110,
  0b00100,
  0b00000
};//ф
const byte rus_ts[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b11111,
  0b00001
};//ц
const byte rus_ch[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b00001,
  0b00000
};//ч
const byte rus_sh[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00000
};//ш
const byte rus_sch[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00001
};//щ
const byte rus_tverd_mal[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11000,
  0b01000,
  0b01110,
  0b01001,
  0b01110,
  0b00000
};//ъ
const byte rus_y[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b11101,
  0b10011,
  0b11101,
  0b00000
};//ы
const byte rus_myagk_mal[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b11110,
  0b00000
};//ь
const byte rus_ee[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00111,
  0b10001,
  0b01110,
  0b00000
};//э
const byte rus_yu[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10101,
  0b11101,
  0b10101,
  0b10010,
  0b00000
};//ю
const byte rus_ya[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01111,
  0b10001,
  0b01111,
  0b00101,
  0b01001,
  0b00000
};//я
