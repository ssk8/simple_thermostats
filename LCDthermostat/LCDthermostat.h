#include <Arduino.h>
#include <LiquidCrystalIO.h>

#include <IoAbstractionWire.h>
#include <Wire.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <Encoder.h>

#define ENCODER_PIN0 0
#define ENCODER_PIN1 1
#define BUTTON_PIN A2
#define RELAY_PIN 5
#define ONE_WIRE_BUS 4

Encoder encoder(ENCODER_PIN0, ENCODER_PIN1);
long encoded = 0;

float setpoint;
float tempC;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempProbe(&oneWire);

#define RELAY_ACTIVE LOW
#define INITIAL_SETPOINT 38
#define TEMP_OFFSET 1
#define TEMPERATURE_PRECISION 9

LiquidCrystalI2C_RS_EN(lcd, 0x27, false)
