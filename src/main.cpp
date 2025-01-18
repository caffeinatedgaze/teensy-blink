#include <Arduino.h>
#include <cstdlib>
#include <iostream>
#include <SoftwareSerial.h>
#include "morse.hpp"
#include "main.hpp"

SoftwareSerial printer(21, 20);

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