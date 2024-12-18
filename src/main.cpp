#include <Arduino.h>
#include <cstdlib>
#include "morse.hpp"

void setup()
{
	while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");
	pinMode(1, OUTPUT);
}

void loop()
{
	digitalWrite(1, HIGH);
	delay(1000);
}