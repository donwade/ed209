// ST7789 library example
// (c) 2019 Pawel A. Hernik

#ifdef HAS_LCD

#include <SPI.h>
#include <Adafruit_GFX.h>

#define SCR_WD ST7789_TFTWIDTH
#define SCR_HT ST7789_TFTHEIGHT

#include "ST7789_AVR.h"
#include "bitmap.h"

uint16_t colorBar[50];


void setup2(void)
{
  lcd.init(SCR_WD, SCR_HT);
  lcd.fillScreen(BLACK);

  int i,j;
  for(j=0;j<7;j++)
    for(i=0;i<7;i++)
      lcd.drawImageF(i*34,j*34,32,32,mario);
  delay(4000);

  Serial.println("Setup2 done");
}

void loop2()
{
  lcd.drawImageF(random(0,240-32),random(0,240-32),32,32,mario);
}

#else
	void setup2(void) {};
	void loop2(void) {};
#endif

