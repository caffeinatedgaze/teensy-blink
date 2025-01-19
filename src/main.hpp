#pragma once

#define LASER_ARRAY_X 2
#define LASER_ARRAY_Y 24

struct LaserStates
// States (on/off) of lasers in each array.
{
	// bool primaryLaserStates[LASER_ARRAY_X][LASER_ARRAY_Y] = {false};
	// bool secondaryLaserStates[LASER_ARRAY_X][LASER_ARRAY_Y] = {false};
	std::array<std::array<bool, LASER_ARRAY_Y>, LASER_ARRAY_X> primaryLaserStates = {false};
	std::array<std::array<bool, LASER_ARRAY_Y>, LASER_ARRAY_X> secondaryLaserStates = {false};
};

enum class TeensyType
{
	Primary,
	Secondary
};


void printLaserStates(LaserStates &laserStates);