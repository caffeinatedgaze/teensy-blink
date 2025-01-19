#ifndef MAIN_HPP
#define MAIN_HPP

#include <Arduino.h>
#include <cstdlib>
#include <iostream>
#include <SoftwareSerial.h>
#include <Adafruit_MCP23X17.h>

#define LASER_ARRAY_X 2
#define LASER_ARRAY_Y 25

// The number of lasers available via the I2C extender.
#define NON_EXTENDED_PINS_N 34
// The number of lasers available via the Teensy pins.
#define EXTENDED_PINS_N 16
#define TOTAL_PINS_N (NON_EXTENDED_PINS_N + EXTENDED_PINS_N)

using PinIdx = int;
using PinMap = std::array<PinIdx, TOTAL_PINS_N>;
extern PinMap pinByIdx;

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
int freeram();

extern unsigned long _heap_start;
extern unsigned long _heap_end;
extern char *__brkval;

#endif // MAIN_HPP