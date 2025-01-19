#include <Arduino.h>
#include "patternExecutor.hpp"

void PatternExecutor::switchTeensy()
{
	switch (currentTeensyType)
	{
	case TeensyType::Primary:
		currentTeensyType = TeensyType::Secondary;
		break;
	case TeensyType::Secondary:
		currentTeensyType = TeensyType::Primary;
		break;
	}
}

void PatternExecutor::chooseNextLaser()
{
	// Move on.
	currentLaserY++;

	// Decide if you need to switch to another array or teensy.
	if (currentLaserY == LASER_ARRAY_Y)
	{
		switch (currentLaserX)
		{
		case 0:
			// Move the next line of lasers inside the current teensy.
			currentLaserX = 1;
			break;
		case 1:
			// Switch to the other teensy.
			switchTeensy();
			currentLaserX = 0;
			break;
		}
		currentLaserY = 0;
	}
}

void PatternExecutor::setLaserState(bool laserState)
{
	switch (currentTeensyType)
	{
	case TeensyType::Primary:
	{
		laserStates.primaryLaserStates[currentLaserX][currentLaserY] = laserState;
		break;
	}
	case TeensyType::Secondary:
	{
		laserStates.secondaryLaserStates[currentLaserX][currentLaserY] = laserState;
		// todo: Send command to the secondary Teensy.
		break;
	}
	}
	analogWrite(LED_BUILTIN, laserState ? HIGH : LOW);
}
