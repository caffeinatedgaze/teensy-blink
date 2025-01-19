#include <Arduino.h>
#include <cstdlib>
#include <iostream>
#include <SoftwareSerial.h>
#include <Adafruit_AW9523.h>

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

extern unsigned long _heap_start;
extern unsigned long _heap_end;
extern char *__brkval;

int freeram()
{
	return (char *)&_heap_end - __brkval;
}

void setup()
{
	// while (!bitRead(USB1_PORTSC1, 7) && !Serial && millis() < 15000)
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

	// todo: enable all of the pins.
	for (uint8_t i = 0; i < LASER_ARRAY_X; i++)
	{
		for (uint8_t j = 0; j < LASER_ARRAY_Y; j++)
		{
			pinMode(j, OUTPUT);
		}
	}

	// Adafruit_AW9523 aw;
	// if (!aw.begin(0x58))
	// {
	// 	std::cout << "AW9523 not found? Check wiring!" << std::endl;
	// 	while (1)
	// 		delay(10); // halt forever
	// }
}

void teardown()
{
	delete patternExecutor;
}

void loop()
{
	for (uint8_t j = 0; j < 100; j++)
	{
		digitalWrite(j, LOW);
	}

	try
	{
	std::cout << "Picking the next codepoint." << std::endl;
	currentCodepoint = CODEPOINTS.at(currentCodepointIdx);
	currentCodepointMorseCode = encodeNumeral(currentCodepoint.c_str());
	printSignals(currentCodepointMorseCode);
	std::cout << "Morse code length: " << currentCodepointMorseCode.size() << std::endl;

	for (size_t i = 0; i < currentCodepointMorseCode.size(); i++)
	{
		SignalPtr signal = currentCodepointMorseCode.at(i);

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
		if (i + 1 < currentCodepointMorseCode.size())
		{
			std::string currentCodepointType = currentCodepointMorseCode.at(i + 1)->getType();
			if (
				currentCodepointType != LETTER_BREAK &&
				currentCodepointType != WORD_BREAK &&
				currentCodepointType != SENTENCE_BREAK)
			{
				patternExecutor->chooseNextLaser();
			}
		}
	}

	currentCodepointIdx = (currentCodepointIdx + 1) % CODEPOINTS.size();
	std::cout << "Current codepoint Idx: " << currentCodepointIdx << std::endl;
	std::cout << "Codepoints length: " << CODEPOINTS.size() << std::endl;
	std::cout << "Free RAM: " << freeram() << std::endl;
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