#pragma once

#define LASER_ARRAY_X 2
#define LASER_ARRAY_Y 24

struct LaserStates
// States (on/off) of lasers in each array.
{
	bool primaryLaserStates[LASER_ARRAY_X][LASER_ARRAY_Y] = {false};
	bool secondaryLaserStates[LASER_ARRAY_X][LASER_ARRAY_Y] = {false};
};

enum class TeensyType
{
	Primary,
	Secondary
};


void printLaserStates(LaserStates &laserStates)
{
	Serial.println("Primary laser states:");
	for (uint8_t x = 0; x < LASER_ARRAY_X; x++)
	{
		for (uint8_t y = 0; y < LASER_ARRAY_Y; y++)
		{
			Serial.print(laserStates.primaryLaserStates[x][y]);
		}
		Serial.println();
	}
	Serial.println("Secondary laser states:");
	for (uint8_t x = 0; x < LASER_ARRAY_X; x++)
	{
		for (uint8_t y = 0; y < LASER_ARRAY_Y; y++)
		{
			Serial.print(laserStates.secondaryLaserStates[x][y]);
		}
		Serial.println();
	}
}