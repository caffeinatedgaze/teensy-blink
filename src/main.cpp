#include <Arduino.h>
#include <cstdlib>
#include <iostream>
#include <SoftwareSerial.h>
#include "morse.hpp"
#include "main.hpp"

enum class PatternType
{
	ZigZag,
	Random
};

enum class TeensyType
{
	Primary,
	Secondary
};

// Changes the state of the laser array according to a pattern: zigzag or random.
class PatternExecutor
{
public:
	PatternType patternType;
	TeensyType currentTeensyType = TeensyType::Primary;
	LaserStates &laserStates;

	PatternExecutor(PatternType patternType, LaserStates &laserStates) : patternType(patternType), laserStates(laserStates)
	{
	}

	// Choose the next laser according to the pattern.
	void chooseNextLaser();

	// Update the laser array in the primary as well as send command to the secondary.
	void setLaserState(bool laserState);
};

LaserStates laserStates;
PatternExecutor *patternExecutor;

void setup()
{
	while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");
	pinMode(LED_BUILTIN, OUTPUT);

	patternExecutor = new PatternExecutor(PatternType::ZigZag, laserStates);
}

void teardown()
{
	delete patternExecutor;
}

void loop()
{
	analogWrite(LED_BUILTIN, HIGH);
	delay(1000);
	analogWrite(LED_BUILTIN, LOW);
	delay(1000);

	// initialize pattern producer with the matrix and its dimensions
	// getCodepoint from the translated sequence.
	// convert codepoint into morse code (i.e. Dits, Dahs, and breaks).
	// iterate over each signal of the codepoint's morse code and
	// pass its value - on/off - into the current pattern producer (i.e. ZigZag or Random).
	//
	// wait for the break duration.
	// ... repeat.
}