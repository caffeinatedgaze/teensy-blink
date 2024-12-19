// signal_encoder.h
#ifndef SIGNAL_ENCODER_H
#define SIGNAL_ENCODER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int TELEGRAPH_CODEPOINT_LEN = 4;
const int LASER_ARRAY_LINE_LEN = 10;

const std::vector<std::vector<bool>> morseCode = {
	{false, false, false, false, false}, // 0: 5 Dahs
	{true, false, false, false, false},	 // 1: 1 Dit, 4 Dahs
	{true, true, false, false, false},	 // 2: 2 Dits, 3 Dahs
	{true, true, true, false, false},	 // 3: 3 Dits, 2 Dahs
	{true, true, true, true, false},	 // 4: 4 Dits, 1 Dah
	{true, true, true, true, true},		 // 5: 5 Dits
	{false, true, true, true, true},	 // 6: 1 Dah, 4 Dits
	{false, false, true, true, true},	 // 7: 2 Dahs, 3 Dits
	{false, false, false, true, true},	 // 8: 3 Dahs, 2 Dits
	{false, false, false, false, true}	 // 9: 4 Dahs, 1 Dit
};

// Base class for Signal types
class Signal
{
public:
	int counter;
	int max_value;
	bool value;

	Signal(int cnt = 0, int max_val = 0, int val = false)
		: counter(cnt), max_value(max_val), value(val) {}

	virtual std::string getType() const = 0; // Pure virtual function
	virtual ~Signal() = default;

	operator std::string() const
	{
		return this->getType();
	}
	bool operator==(const Signal &other) const
	{
		return getType() == other.getType();
	}
};

// Derived class for Dit
class Dit : public Signal
{
public:
	Dit() : Signal(0, 1, true) {} // Default values: counter = 0, max_value = 1, value = 1

	std::string getType() const override
	{
		return "dit";
	}
};

// Derived class for Dah
class Dah : public Signal
{
public:
	Dah() : Signal(0, 3, true) {} // Default values: counter = 0, max_value = 3, value = 1

	std::string getType() const override
	{
		return "dah";
	}
};

// Derived class for Space. Space between letters.
class SpaceBetweenCharacters : public Signal
{
public:
	SpaceBetweenCharacters() : Signal(0, 1, false) {} // Default values: counter = 0, max_value = 3, value = 0

	std::string getType() const override
	{
		return ".";
	}
};

class SpaceBetweenCodepoints: public Signal
{
public:
	SpaceBetweenCodepoints() : Signal(0, 3, false) {} // Default values: counter = 0, max_value = 3, value = 0

	std::string getType() const override
	{
		return "|";
	}
};

// Derived class for Space
class BreakBetweenSentences: public Signal
{
public:
	BreakBetweenSentences() : Signal(0, 7, false) {} // Default values: counter = 0, max_value = 7, value = 0

	std::string getType() const override
	{
		return "break";
	}
};

// Representation of a codepoint in morse code (i.e. dits and dahs)
using Signals = std::vector<Signal *>;

// State of each laser in the array
using LaserStates = bool[LASER_ARRAY_LINE_LEN];

// Function to encode an Arabic numeral into a sequence of dits and dahs
Signals encodeNumeral(const char numeral[4]);

// Function to display signals
void displaySignals(const Signals &signals);

// Process input
void processInput();

// Update a single laser
void updateLaser(LaserStates laserStates, int i, int j, Signal *signal);

#endif // SIGNAL_ENCODER_H
