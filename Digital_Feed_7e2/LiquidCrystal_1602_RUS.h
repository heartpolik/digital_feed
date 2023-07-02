#ifndef _LiquidCrystal_1602_RUS
#define _LiquidCrystal_1602_RUS

//-----------------   Используемые символы   ------------------------------------------------------------------------------------------------------------------------------
  //===Буквы====

#define _rus_B					//Б
#define _rus_G				  //Г
#define _rus_D					//Д
#define _rus_ZH					//Ж
#define _rus_Z					//З
#define _rus_I					//И
#define _rus_II				  //Й
#define _rus_L				  //Л
#define _rus_P					//П
#define _rus_U					//У
#define _rus_F				  //Ф
#define _rus_TS				  //Ц
#define _rus_CH				//Ч
#define _rus_SH					//Ш
//#define _rus_SCH				//Щ
//#define _rus_tverd			//Ъ
#define _rus_Y					//Ы
#define _rus_myagk				//Ь
#define _rus_EE				  //Э
#define _rus_YU					//Ю
#define _rus_YA				  //Я
#define _rus_b					//б
#define _rus_v					//в
#define _rus_g					//г
#define _rus_d					//д
//#define _rus_yo				//ё
#define _rus_zh					//ж
#define _rus_z					//з
#define _rus_i					//и
//#define _rus_ii				//й
#define _rus_k					//к
//#define _rus_l				//л
#define _rus_m					//м
#define _rus_n					//н
//#define _rus_p				//п
#define _rus_t					//т
//#define _rus_u				//y
//#define _rus_f				//ф
#define _rus_ts					//ц
#define _rus_ch					//ч
//#define _rus_sh				//ш
//#define _rus_sch				//щ
//#define _rus_tverd_mal		//ъ
#define _rus_y					//ы
//#define _rus_myagk_mal 		//ь
//#define _rus_ee				//э
//#define _rus_yu				//ю
#define _rus_ya					//я

//#define _RUS_TO_ENG             //Конвертация русских знаков в их английские аналоги. Для UTF-строк.
//#define _DEGREE					//Преобразование значка °

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include <Print.h>

#define BYTE 0
#ifdef ARDUINO_ARCH_AVR
  typedef uint32_t _uint_farptr_t;
#else
  typedef uint8_t* _uint_farptr_t;
  #ifndef memcpy_PF
    #define memcpy_PF(dest, src, len) memcpy((dest), (src), (len))
  #endif
#endif

class LiquidCrystal_1602_RUS : public LiquidCrystal {
public:
  LiquidCrystal_1602_RUS(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t = 0);
  void print(const wchar_t[]);
  void print(const char[]);
  void print(int, int = DEC);
  void print(unsigned int, int = DEC);
  void print(long, int = DEC);
  void print(unsigned long, int = DEC);
  void print(const String &);
  void print(char, int = BYTE);
  void print(unsigned char, int = BYTE);
  void print(double, int = 2);
  void clear();
  //Добавляем новую функцию для очистки набора символов
  void reset();
  //-
  void setCursor(uint8_t, uint8_t);
  uint8_t getCursorCol();
  uint8_t getCursorRow();
  wchar_t *asciiutf8(unsigned char);

private:
  void CharSetToLCD(uint8_t *, uint8_t *);
  void ResetAllIndex();
  void printwc(const wchar_t);
  uint8_t mbtowc(wchar_t *, char *, uint8_t);

  uint8_t max_symbol_count;  //Максимальное количество переназначаемых символов (по умолчанию 8: от 0 до 7)
  int symbol_index;//Индекс символа (от 0 до 7)
  uint8_t cursor_col;
  uint8_t cursor_row;
  //===Буквы====
#ifdef _rus_B
  uint8_t index_rus_B;					//Б
#endif

#ifdef _rus_G
  uint8_t index_rus_G;					//Г
#endif

#ifdef _rus_D
  uint8_t index_rus_D;					//Д
#endif

#ifdef _rus_ZH
  uint8_t index_rus_ZH;					//Ж
#endif

#ifdef _rus_Z
  uint8_t index_rus_Z;					//З
#endif

#ifdef _rus_I
  uint8_t index_rus_I;					//И
#endif

#ifdef _rus_II
  uint8_t index_rus_II;					//Й
#endif

#ifdef _rus_L
  uint8_t index_rus_L;					//Л
#endif

#ifdef _rus_P
  uint8_t index_rus_P;					//П
#endif

#ifdef _rus_U
  uint8_t index_rus_U;					//У
#endif

#ifdef _rus_F
  uint8_t index_rus_F;					//Ф
#endif

#ifdef _rus_TS
  uint8_t index_rus_TS;					//Ц
#endif

#ifdef _rus_CH
  uint8_t index_rus_CH;					//Ч
#endif

#ifdef _rus_SH
  uint8_t index_rus_SH;					//Ш
#endif

#ifdef _rus_SCH
  uint8_t index_rus_SCH;				//Щ
#endif

#ifdef _rus_tverd
  uint8_t index_rus_tverd;				//Ъ
#endif

#ifdef _rus_Y
  uint8_t index_rus_Y;					//Ы
#endif

#ifdef _rus_myagk
  uint8_t index_rus_myagk;				//Ь
#endif

#ifdef _rus_EE
  uint8_t index_rus_EE;					//Э
#endif

#ifdef _rus_YU
  uint8_t index_rus_YU;					//Ю
#endif

#ifdef _rus_YA
  uint8_t index_rus_YA;					//Я
#endif

#ifdef _rus_b
  uint8_t index_rus_b;					//б
#endif

#ifdef _rus_v
  uint8_t index_rus_v;					//в
#endif

#ifdef _rus_g
  uint8_t index_rus_g;					//г
#endif

#ifdef _rus_d
  uint8_t index_rus_d;					//д
#endif

#ifdef _rus_yo
  uint8_t index_rus_yo;					//ё
#endif

#ifdef _rus_zh
  uint8_t index_rus_zh;					//ж
#endif

#ifdef _rus_z
  uint8_t index_rus_z;					//з
#endif

#ifdef _rus_i
  uint8_t index_rus_i;					//и
#endif

#ifdef _rus_ii
  uint8_t index_rus_ii;					//й
#endif

#ifdef _rus_k
  uint8_t index_rus_k;					//к
#endif

#ifdef _rus_l
  uint8_t index_rus_l;					//л
#endif

#ifdef _rus_m
  uint8_t index_rus_m;					//м
#endif

#ifdef _rus_n
  uint8_t index_rus_n;					//н
#endif

#ifdef _rus_p
  uint8_t index_rus_p;					//п
#endif

#ifdef _rus_t
  uint8_t index_rus_t;					//т
#endif

#ifdef _rus_u
  uint8_t index_rus_u;					//y
#endif

#ifdef _rus_f
  uint8_t index_rus_f;					//ф
#endif

#ifdef _rus_ts
  uint8_t index_rus_ts;					//ц
#endif

#ifdef _rus_ch
  uint8_t index_rus_ch;					//ч
#endif

#ifdef _rus_sh
  uint8_t index_rus_sh;					//ш
#endif

#ifdef _rus_sch
  uint8_t index_rus_sch;				//щ
#endif

#ifdef _rus_tverd_mal
  uint8_t index_rus_tverd_mal;			//ъ
#endif

#ifdef _rus_y
  uint8_t index_rus_y;					//ы
#endif

#ifdef _rus_myagk_mal
  uint8_t index_rus_myagk_mal;			//ь
#endif

#ifdef _rus_ee
  uint8_t index_rus_ee;					//э
#endif

#ifdef _rus_yu
  uint8_t index_rus_yu;					//ю
#endif

#ifdef _rus_ya
  uint8_t index_rus_ya;					//я
#endif

};

#ifdef _rus_B
extern const byte rus_B[];				//Б
#endif

#ifdef _rus_G
extern const byte rus_G[];				//Г
#endif

#ifdef _rus_D
extern const byte rus_D[];				//Д
#endif

#ifdef _rus_ZH
extern const byte rus_ZH[];				//Ж
#endif

#ifdef _rus_Z
extern const byte rus_Z[];				//З
#endif

#ifdef _rus_I
extern const byte rus_I[];				//И
#endif

#ifdef _rus_II
extern const byte rus_II[];				//Й
#endif

#ifdef _rus_L
extern const byte rus_L[];				//Л
#endif

#ifdef _rus_P
extern const byte rus_P[];				//П
#endif

#ifdef _rus_U
extern const byte rus_U[];				//У
#endif

#ifdef _rus_F
extern const byte rus_F[];				//Ф
#endif

#ifdef _rus_TS
extern const byte rus_TS[];				//Ц
#endif

#ifdef _rus_CH
extern const byte rus_CH[];				//Ч
#endif

#ifdef _rus_SH
extern const byte rus_SH[];				//Ш
#endif

#ifdef _rus_SCH
extern const byte rus_SCH[];			//Щ
#endif

#ifdef _rus_tverd
extern const byte rus_tverd[];			//Ъ
#endif

#ifdef _rus_Y
extern const byte rus_Y[];				//Ы
#endif

#ifdef _rus_myagk
extern const byte rus_myagk[];			//Ь
#endif

#ifdef _rus_EE
extern const byte rus_EE[];				//Э
#endif

#ifdef _rus_YU
extern const byte rus_YU[];				//Ю
#endif

#ifdef _rus_YA
extern const byte rus_YA[];				//Я
#endif

#ifdef _rus_b
extern const byte rus_b[];				//б
#endif

#ifdef _rus_v
extern const byte rus_v[];				//в
#endif

#ifdef _rus_g
extern const byte rus_g[];				//г
#endif

#ifdef _rus_d
extern const byte rus_d[];				//д
#endif

#ifdef _rus_yo
extern const byte rus_yo[];				//ё
#endif

#ifdef _rus_zh
extern const byte rus_zh[];				//ж
#endif

#ifdef _rus_z
extern const byte rus_z[];				//з
#endif

#ifdef _rus_i
extern const byte rus_i[];				//и
#endif

#ifdef _rus_ii
extern const byte rus_ii[];				//й
#endif

#ifdef _rus_k
extern const byte rus_k[];				//к
#endif

#ifdef _rus_l
extern const byte rus_l[];				//л
#endif

#ifdef _rus_m
extern const byte rus_m[];				//м
#endif

#ifdef _rus_n
extern const byte rus_n[];				//н
#endif

#ifdef _rus_p
extern const byte rus_p[];				//п
#endif

#ifdef _rus_t
extern const byte rus_t[];				//т
#endif

#ifdef _rus_u
extern const byte rus_u[];				//у
#endif

#ifdef _rus_f
extern const byte rus_f[];				//ф
#endif

#ifdef _rus_ts
extern const byte rus_ts[];				//ц
#endif

#ifdef _rus_ch
extern const byte rus_ch[];				//ч
#endif

#ifdef _rus_sh
extern const byte rus_sh[];				//ш
#endif

#ifdef _rus_sch
extern const byte rus_sch[];			//щ
#endif

#ifdef _rus_tverd_mal
extern const byte rus_tverd_mal[];		//ъ
#endif

#ifdef _rus_y
extern const byte rus_y[];				//ы
#endif

#ifdef _rus_myagk_mal
extern const byte rus_myagk_mal[];		//ь
#endif

#ifdef _rus_ee
extern const byte rus_ee[];				//э
#endif

#ifdef _rus_yu
extern const byte rus_yu[];				//ю
#endif

#ifdef _rus_ya
extern const byte rus_ya[];				//я
#endif

extern wchar_t char_utf8[];

#endif
