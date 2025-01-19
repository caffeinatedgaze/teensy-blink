#include <Arduino.h>
#include <cstdlib>
#include <iostream>
#include <SoftwareSerial.h>
#include "morse.hpp"
#include "codepoints.hpp"
#include "patternExecutor.hpp"
#include "main.hpp"

PatternExecutor *patternExecutor;
LaserStates laserStates;
uint64_t currentCodepointIdx = 0;
std::string currentCodepoint;
Signals currentCodepointMorseCode;
// Refresh rate that is equal to the duration of Dit – the shortest Morse code signal.
uint16_t refreshRate = 100; // in ms

void setup()
{
	while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");
	pinMode(LED_BUILTIN, OUTPUT);

	patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);

	if (0 == CODEPOINTS.size())
	{
		std::cout << "CODEPOINTS cannot be of zero length. Aborting.";
		exit(1);
	}
}

void teardown()
{
	delete patternExecutor;
}

void loop()
{
	try
	{
		currentCodepoint = CODEPOINTS[currentCodepointIdx];
		currentCodepointMorseCode = encodeNumeral(currentCodepoint.c_str());
		printSignals(currentCodepointMorseCode);

		for (uint8_t i = 0; i < currentCodepointMorseCode.size(); i++)
		{
			SignalPtr signal = currentCodepointMorseCode[i];

			// Set laser state according to the signal.
			patternExecutor->setLaserState(signal->value);
			std::cout << "Current signal type: " << signal->getType() << std::endl;
			printLaserStates(laserStates);
			// Blink the built-in LED.
			analogWrite(LED_BUILTIN, signal->value ? HIGH : LOW);
			// Wait for the signal duration.
			while (signal->counter < signal->max_value)
			{
				delay(refreshRate);
				signal->counter++;
			}
			// Move to the next laser according to the pattern.
			// Do not move if the next signal type is a break.
			std::string currentCodepointType = currentCodepointMorseCode[i + 1]->getType();
			if (
				currentCodepointType != LETTER_BREAK &&
				currentCodepointType != WORD_BREAK &&
				currentCodepointType != SENTENCE_BREAK)
			{
				patternExecutor->chooseNextLaser();
			}
		}

		currentCodepointIdx = (currentCodepointIdx + 1) % CODEPOINTS.size();
		std::cout << "Current codepoint Idx: " << currentCodepointIdx << std::endl;
		std::cout << "Codepoints length: " << CODEPOINTS.size() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return;
	}
	catch (...)
	{
		std::cerr << "Unknown exception caught" << std::endl;
		return;
	}
}

void printLaserStates(LaserStates &laserStates)
{
	Serial.println("Primary laser states:");
	for (uint8_t x = 0; x < LASER_ARRAY_X; x++)
	{
		for (uint8_t y = 0; y < LASER_ARRAY_Y; y++)
		{
			Serial.print(laserStates.primaryLaserStates.at(x).at(y));
		}
		Serial.println();
	}
	Serial.println("Secondary laser states:");
	for (uint8_t x = 0; x < LASER_ARRAY_X; x++)
	{
		for (uint8_t y = 0; y < LASER_ARRAY_Y; y++)
		{
			Serial.print(laserStates.secondaryLaserStates.at(x).at(y));
		}
		Serial.println();
	}
}