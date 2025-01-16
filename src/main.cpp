#include <Arduino.h>
#include <cstdlib>
#include <iostream>
#include <SoftwareSerial.h>
#include "morse.hpp"
#include "codepoints.hpp"
#include "forPrinting.hpp"

SoftwareSerial printer(21, 20);

void setup()
{
	while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");
	pinMode(LED_BUILTIN, OUTPUT);
	for (int i = 0; i < 10; i++)
	{
		pinMode(i, OUTPUT);
	}
	printer.begin(9600);
}

void loop()
{
}