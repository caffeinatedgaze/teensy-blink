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

u_int currentCodepointIndex = 0;
u_int currentLaserIndex = 0;
const int refreshRate = 100;
const int cyclesBeforePrint = 30; // N times of the refresh rate.
u_int currentCycle = 0;
u_int currentPrintingLine = 0;

void loop()
{
	// for (std::string tgCode : telegraphCodes) {  
	// 	printer.println(tgCode.c_str());
	std::string currentCodepoint = CODEPOINTS[currentCodepointIndex++];
	// 	delay(500);
	// }
	// std::cout << "Current codepoint: " << currentCodepoint << std::endl;
	Signals signals = encodeNumeral(currentCodepoint.c_str());

	// for (const Signal *signal : signals)
	// {
	// 	std::cout << signal->getType() << " ";
	// }
	// std::cout << std::endl;

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
				printer.println(forPrinting[currentPrintingLine].c_str());
				currentPrintingLine = (currentPrintingLine + 1) % forPrinting.size();
				currentCycle = 1;
			}
			currentCycle++;
			delay(refreshRate);
		}
	}
	currentLaserIndex = (currentLaserIndex + 1) % LASER_ARRAY_LINE_LEN;
	currentCodepointIndex = (currentCodepointIndex + 1) % CODEPOINTS->length();
}