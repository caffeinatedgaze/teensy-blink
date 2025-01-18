#pragma once

#include "main.hpp"

enum class PatternType
{
	ZigZag,
	Random
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