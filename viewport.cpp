// ST7789 library example
// (c) 2019 Pawel A. Hernik

#if 1 //def HAS_LCD

#include <SPI.h>
#include <Adafruit_GFX.h>

#define SCR_WD ST7789_TFTWIDTH
#define SCR_HT ST7789_TFTHEIGHT

#include "ST7789_AVR.h"

uint16_t colorBar[50];

ST7789_AVR *lcd; //new ST7789_AVR(ENGINE_HSPI);

void setup2(void)
{
  lcd = new ST7789_AVR(ENGINE_HSPI);
  lcd->init(SCR_WD, SCR_HT);
  lcd->fillScreen(BLACK);
  Serial.println("Setup2 done");
}

void loop2()
{
	delay(10000);
}

#else
	void setup2(void) {};
	void loop2(void) {};
#endif

