#include <U8g2lib.h>
#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include <avr/dtostrf.h>

#define MAXDO   5
#define MAXCS   6
#define MAXCLK  9

//U8G2_SH1107_128X128_1_HW_I2C u8g2(U8G2_R1, U8X8_PIN_NONE);
U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

void setup(void) {
  thermocouple.begin();
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop(void) {
  float tempC = thermocouple.readCelsius();
  char temp_ca[4];
  dtostrf(tempC, sizeof(temp_ca), 1, temp_ca);
  
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_helvB24_tf);
    //u8g2.setFont(u8g2_font_logisoso38_tf);
    //u8g2.setCursor(0, 60);
    u8g2.setCursor(0, 32);
    u8g2.print(temp_ca);
    u8g2.print("°C");

  } while ( u8g2.nextPage() );
  //delay(1000);
}
