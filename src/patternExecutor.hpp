#pragma once

#include <cstdint>
#include "main.hpp"

enum class PatternType
{
	Linear,
};

using SetExtendedPinCallback = std::function<void(PinIdx, int)>;

// Changes the state of the laser array according to a pattern.
class PatternExecutor
{
public:
	PatternType patternType;
	LaserStates &laserStates;

	SetExtendedPinCallback setExtendedPinCallback;

	// Keep track of the current position in the laser array.
	TeensyType currentTeensyType = TeensyType::Primary;
	uint8_t currentLaserX = 0;
	uint8_t currentLaserY = 0;

	PatternExecutor(
		PatternType patternType,
		LaserStates &laserStates,
		SetExtendedPinCallback setExtendedPinCallback) : patternType(patternType),
														 laserStates(laserStates),
														 setExtendedPinCallback(setExtendedPinCallback)
	{
	}

	// Switch between primary and secondary Teensy.
	void switchTeensy();

	// Choose the next laser according to the pattern.
	void chooseNextLaser();

	// Update the laser array in the primary as well as send command to the secondary.
	void setLaserState(bool laserState);

	// Set a certain laser pin.
	void setLaserState(PinIdx pinIdx, bool laserState, bool isExtended);
};