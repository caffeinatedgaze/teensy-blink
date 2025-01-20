#pragma once

#include <cstdint>
#include "main.hpp"

enum class PatternType
{
	Linear,
	Random,
	Hiuyan,
};

extern std::array<PatternType, 3> patternTypes;

using SetExtendedPinCallback = std::function<void(PinIdx, int)>;
using WriteSerialCallback = std::function<void(const std::string &)>;

// Changes the state of the laser array according to a pattern.
class PatternExecutor
{
public:
	LaserStates &laserStates;

	SetExtendedPinCallback setExtendedPinCallback;
	WriteSerialCallback writeSerialCallback;

	// Keep track of the current position in the laser array.
	TeensyType currentTeensyType = TeensyType::Primary;
	uint8_t currentLaserX = 0;
	uint8_t currentLaserY = 0;

	PatternExecutor(
		LaserStates &laserStates,
		SetExtendedPinCallback setExtendedPinCallback,
		WriteSerialCallback writeSerialCallback) : laserStates(laserStates),
												   setExtendedPinCallback(setExtendedPinCallback),
												   writeSerialCallback(writeSerialCallback)
	{
	}

	// Switch between primary and secondary Teensy.
	void switchTeensy();

	// Choose the next laser according to the pattern.
	virtual void chooseNextLaser() = 0;

	// Update the laser array in the primary as well as send command to the secondary.
	void setLaserState(bool laserState);

	// Set a certain laser pin.
	void setLaserState(PinIdx pinIdx, bool laserState, bool isExtended);
};

class LinearPatternExecutor : public PatternExecutor
{
public:
	LinearPatternExecutor(
		LaserStates &laserStates,
		SetExtendedPinCallback setExtendedPinCallback,
		WriteSerialCallback writeSerialCallback) : PatternExecutor(laserStates,
																   setExtendedPinCallback,
																   writeSerialCallback)
	{
	}

	void chooseNextLaser() override;
};

class RandomPatternExecutor : public PatternExecutor
{
public:
	RandomPatternExecutor(
		LaserStates &laserStates,
		SetExtendedPinCallback setExtendedPinCallback,
		WriteSerialCallback writeSerialCallback) : PatternExecutor(laserStates,
																   setExtendedPinCallback,
																   writeSerialCallback)
	{
	}

	void chooseNextLaser() override;
};

class HiuyanPatternExecutor : public PatternExecutor
{
public:
	HiuyanPatternExecutor(
		LaserStates &laserStates,
		SetExtendedPinCallback setExtendedPinCallback,
		WriteSerialCallback writeSerialCallback) : PatternExecutor(laserStates,
																   setExtendedPinCallback,
																   writeSerialCallback)
	{
	}

	void chooseNextLaser() override;
};