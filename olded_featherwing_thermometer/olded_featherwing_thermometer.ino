#include <Arduino.h>
#include <U8g2lib.h>
#include <avr/dtostrf.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//U8G2_SH1107_128X128_1_HW_I2C u8g2(U8G2_R1, U8X8_PIN_NONE);
U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);


void setup(void) {
  sensors.begin();
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop(void) {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
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
