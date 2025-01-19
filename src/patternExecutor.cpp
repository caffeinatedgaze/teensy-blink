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
	// Turn off the current laser.
	setLaserState(false);

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
		// Update state in the matrix.
		laserStates.primaryLaserStates[currentLaserX][currentLaserY] = laserState;
		// Retrieve the real pin number.
		PinIdx pinIdx = pinByIdx.at(currentLaserY);
		// If extended pin, then set using MCP.
		if (currentLaserY >= NON_EXTENDED_PINS_N)
		{
			this->setExtendedPinCallback(pinIdx, laserState ? HIGH : LOW);
		}
		// If non-extended, then set using normal API.
		else
		{
			analogWrite(currentLaserY, laserState ? HIGH : LOW);
		}
		break;
	}
	case TeensyType::Secondary:
	{
		laserStates.secondaryLaserStates[currentLaserX][currentLaserY] = laserState;
		// todo: Send command to the secondary Teensy.
		break;
	}
	}
}
