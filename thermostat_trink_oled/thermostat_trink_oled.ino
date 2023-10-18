#include <Adafruit_DotStar.h>

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 1
#define RELAY_PIN 4
#define RELAY_ACTIVE LOW
#define TEMP_SETPOINT 24
#define TEMP_OFFSET 1

Adafruit_DotStar dot = Adafruit_DotStar(1, 7, 8, DOTSTAR_BRG);

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temp_sensor(&oneWire);

void setup(void) {
  dot.begin();
  dot.clear();
  dot.show();
  u8g2.begin();
  u8g2.enableUTF8Print();
  temp_sensor.begin();
  pinMode(RELAY_PIN, OUTPUT);
}

void loop(void) {
  temp_sensor.requestTemperatures();
  float tempC = temp_sensor.getTempCByIndex(0);
  u8g2.setFont(u8g2_font_helvB10_tf); 
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.setCursor(0, 12);
  u8g2.print("current temp: ");
  u8g2.setFont(u8g2_font_helvB24_tf); 
  u8g2.setCursor(0, 45);
  u8g2.print(tempC, 1);
  u8g2.print("°C   ");
  u8g2.setFont(u8g2_font_helvB10_tf); 
  u8g2.setCursor(0, 62);
  u8g2.print("setpoint: ");
  u8g2.print(TEMP_SETPOINT);
  u8g2.print("°C   ");
  u8g2.sendBuffer();

  if (tempC < TEMP_SETPOINT &&  digitalRead(RELAY_PIN) != RELAY_ACTIVE){ 
    digitalWrite(RELAY_PIN, RELAY_ACTIVE);
    dot.setPixelColor(0, 0, 10, 0);
    dot.show();
    }
  if (tempC > TEMP_SETPOINT+TEMP_OFFSET &&  digitalRead(RELAY_PIN) == RELAY_ACTIVE){
   digitalWrite(RELAY_PIN, !RELAY_ACTIVE);
   dot.setPixelColor(0, 0, 0, 10);
   dot.show();
    }
  delay(100);
}
