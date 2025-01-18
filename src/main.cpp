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
uint16_t refreshRate = 200; // in ms

void setup()
{
	while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");
	pinMode(LED_BUILTIN, OUTPUT);

	patternExecutor = new PatternExecutor(PatternType::ZigZag, laserStates);

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
	currentCodepoint = CODEPOINTS[currentCodepointIdx];
	currentCodepointMorseCode = encodeNumeral(currentCodepoint.c_str());
	printSignals(currentCodepointMorseCode);

	for (const auto &signal : currentCodepointMorseCode)
	{
		// Set laser state according to the signal.
		patternExecutor->setLaserState(signal->value);
		analogWrite(LED_BUILTIN, signal->value ? HIGH : LOW);

		// Wait for the signal duration.
		while (signal->counter < signal->max_value)
		{
			delay(refreshRate);
			signal->counter++;
		}
	}

	currentCodepointIdx = (currentCodepointIdx + 1) % CODEPOINTS.size();
	std::cout << "Current codepoint Idx: " << currentCodepointIdx << std::endl;
	std::cout << "Codepoints length: " << CODEPOINTS.size() << std::endl;

	// initialize pattern producer with the matrix and its dimensions
	// getCodepoint from the translated sequence.
	// convert codepoint into morse code (i.e. Dits, Dahs, and breaks).
	// iterate over each signal of the codepoint's morse code and
	// pass its value - on/off - into the current pattern producer (i.e. ZigZag or Random).
	//
	// wait for the break duration.
	// ... repeat.
}