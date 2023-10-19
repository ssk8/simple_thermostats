#include "LCDthermostat.h"

void setup() {
    Wire.begin();
    lcd.begin(16, 2);

    // most backpacks have the backlight on pin 3.
    lcd.configureBacklightPin(3);
    lcd.backlight();
    
    pinMode(RELAY_PIN, OUTPUT);

    tempProbe.begin();
    tempProbe.setResolution(0, TEMPERATURE_PRECISION);

    //setpoint = INITIAL_SETPOINT;
    
    //
    // when using this version of liquid crystal, it interacts (fairly) nicely with task manager.
    // instead of doing stuff in loop, we can schedule things to be done. But just be aware than
    // only one task can draw to the display. Never draw to the display in two tasks.
    //
    // You don't have to use the library with task manager like this, it's an option.

    taskManager.scheduleFixedRate(250, [] {
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(tempC, 1);
        lcd.print((char)223);
        lcd.print("C     ");
        lcd.setCursor(0, 1);
        lcd.print("set:");
        lcd.print(setpoint, 0);
        lcd.print((char)223);
        lcd.print("C  heat:");
        lcd.print((digitalRead(RELAY_PIN) == RELAY_ACTIVE));
    });

}

void loop() {

  encoded = encoder.read();
  setpoint = INITIAL_SETPOINT + encoded/4;
  tempProbe.requestTemperatures();
  tempC = tempProbe.getTempCByIndex(0); 

  if (tempC < setpoint &&  digitalRead(RELAY_PIN) != RELAY_ACTIVE){ 
    digitalWrite(RELAY_PIN, RELAY_ACTIVE);
    }
  if (tempC > setpoint + TEMP_OFFSET &&  digitalRead(RELAY_PIN) == RELAY_ACTIVE){
   digitalWrite(RELAY_PIN, !RELAY_ACTIVE);
    }
  delay(100);
  taskManager.runLoop();

}
