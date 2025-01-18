#include <Arduino.h>
#include <cstdlib>
#include <iostream>
#include <SoftwareSerial.h>
#include "morse.hpp"

SoftwareSerial printer(21, 20);

struct LaserStates
// States (on/off) of lasers in each array.
{
	bool primaryLaserStates[24][24] = {false};
	bool secondaryLaserStates[24][24] = {false};
};

void setup()
{
	while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");
	pinMode(LED_BUILTIN, OUTPUT);
	printer.begin(9600);
}

void loop()
{
	analogWrite(LED_BUILTIN, HIGH);
	delay(1000);
	analogWrite(LED_BUILTIN, LOW);
	delay(1000);
}