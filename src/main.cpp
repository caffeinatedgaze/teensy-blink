#include <Arduino.h>
#include <cstdlib>
#include <iostream>
#include "morse.hpp"
#include "codepoints.hpp"

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
}

u_int currentCodepointIndex = 0;
u_int currentLaserIndex = 0;
const int refreshRate = 100;
const int cyclesBeforePrint = 30; // N times of the refresh rate.
u_int currentCycle = 0;
LaserStates laserStates = {false};

void loop()
{
	std::string currentCodepoint = CODEPOINTS[currentCodepointIndex++];
	std::cout << "Current codepoint: " << currentCodepoint << std::endl;
	Signals signals = encodeNumeral(currentCodepoint.c_str());

	for (const Signal *signal : signals)
	{
		std::cout << signal->getType() << " ";
	}
	std::cout << std::endl;

	for (Signal *signal : signals)
	{
		if (signal->value)
		{
			digitalWrite(currentLaserIndex, HIGH);
			digitalWrite(LED_BUILTIN, HIGH);
		}
		else
		{
			digitalWrite(currentLaserIndex, LOW);
			digitalWrite(LED_BUILTIN, LOW);
		}
		while (signal->counter < signal->max_value)
		{
			signal->counter++;
			if (currentCycle % cyclesBeforePrint == 0)
			{
				std::cout << "Printing" << std::endl;
				currentCycle = 1;
			}
			currentCycle++;
			delay(refreshRate);
		}
	}

	currentLaserIndex++;
	if (currentLaserIndex == LASER_ARRAY_LINE_LEN - 1)
	{
		currentLaserIndex = 0;
	}
	if (currentCodepointIndex == CODEPOINTS->length() - 1)
	{
		currentCodepointIndex = 0;
	}
}