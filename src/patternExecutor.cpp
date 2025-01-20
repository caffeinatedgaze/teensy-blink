#include <Arduino.h>
#include "patternExecutor.hpp"

std::array<PatternType, 3> patternTypes = {PatternType::Linear, PatternType::Random, PatternType::Hiuyan};

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

// Decide if the pin is extended based on the array number and current index inside this array.
bool isPinExtended(uint16_t arrayNumber, uint16_t idx)
{
	switch (arrayNumber)
	{
	case 0:
		// Non of the elements in the first array are extended.
		return false;
	case 1:
		return idx > NON_EXTENDED_PINS_N - LASER_ARRAY_Y - 1;
	default:
		std::cout << "Unexpected arrayNumber." << std::endl;
	}
}

PinIdx getPinId(uint16_t arrayNumber, uint16_t idx)
{
	switch (arrayNumber)
	{
	case 0:
		return pinByIdx.at(idx);
	case 1:
		return pinByIdx.at(idx + LASER_ARRAY_Y);
	default:
		std::cout << "Unexpected arrayNumber." << std::endl;
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
		PinIdx pinIdx = getPinId(currentLaserX, currentLaserY);
		// If extended pin, then set using MCP.
		if (isPinExtended(currentLaserX, currentLaserY))
		{
			this->setExtendedPinCallback(pinIdx, laserState ? HIGH : LOW);
		}
		// If non-extended, then set using normal API.
		else
		{
			digitalWrite(pinIdx, laserState ? HIGH : LOW);
		}
		break;
	}
	case TeensyType::Secondary:
	{
		std::cout << "Setting secondary laser state." << std::endl;
		laserStates.secondaryLaserStates[currentLaserX][currentLaserY] = laserState;
		// Send command to the secondary Teensy using serial.
		PinIdx pinIdx = getPinId(currentLaserX, currentLaserY);
		std::string command = "SET " + std::to_string(pinIdx) + " " + std::to_string(isPinExtended(currentLaserX, currentLaserY)) + " " + std::to_string(laserState);
		std::cout << command << std::endl;
		this->writeSerialCallback(command);
		break;
	}
	}
}

void PatternExecutor::setLaserState(PinIdx pinIdx, bool laserState, bool isExtended)
{
	if (isExtended)
	{
		this->setExtendedPinCallback(pinIdx, laserState ? HIGH : LOW);
	}
	else
	{
		digitalWrite(pinIdx, laserState ? HIGH : LOW);
	}
}

void LinearPatternExecutor::chooseNextLaser()
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

void RandomPatternExecutor::chooseNextLaser()
{
	// Turn off the current laser.
	setLaserState(false);

	// Move on.
	currentLaserY = random(0, LASER_ARRAY_Y);
	currentLaserX = random(0, LASER_ARRAY_X);
	currentTeensyType = random(0, 2) == 0 ? TeensyType::Primary : TeensyType::Secondary;
}

void HiuyanPatternExecutor::chooseNextLaser()
{
	// Turn off the current laser.
	setLaserState(false);

	// Move on.
	currentLaserY = random(0, LASER_ARRAY_Y);
	currentLaserX = random(0, LASER_ARRAY_X);
	currentTeensyType = random(0, 2) == 0 ? TeensyType::Primary : TeensyType::Secondary;
}
