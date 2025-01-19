#pragma once

#include "main.hpp"
#include <cstdint>

enum class PatternType
{
	Linear,
};

// Changes the state of the laser array according to a pattern.
class PatternExecutor
{
public:
	PatternType patternType;
	LaserStates &laserStates;

	// Keep track of the current position in the laser array.
	TeensyType currentTeensyType = TeensyType::Primary;
	uint8_t currentLaserX = 0;
	uint8_t currentLaserY = 0;

	PatternExecutor(LaserStates &laserStates) : patternType(patternType), laserStates(laserStates)
	{
	}

	// Switch between primary and secondary Teensy.
	void switchTeensy();

	// Choose the next laser according to the pattern.
	void chooseNextLaser();

	// Update the laser array in the primary as well as send command to the secondary.
	void setLaserState(bool laserState);
};