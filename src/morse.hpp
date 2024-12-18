// signal_encoder.h
#ifndef SIGNAL_ENCODER_H
#define SIGNAL_ENCODER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int TELEGRAPH_CODEPOINT_LEN = 4;
const int LASER_ARRAY_LINES_N = 4;
const int LASER_ARRAY_LINE_LEN = 4;

// Base class for Signal types
class Signal
{
public:
	int counter;
	int max_value;
	int value;

	Signal(int cnt = 0, int max_val = 0, int val = 0)
		: counter(cnt), max_value(max_val), value(val) {}

	virtual std::string getType() const = 0; // Pure virtual function
	virtual ~Signal() = default;

	operator std::string() const
	{
		return this->getType();
	}
};

// Derived class for Dit
class Dit : public Signal
{
public:
	Dit() : Signal(0, 1, 1) {} // Default values: counter = 0, max_value = 1, value = 1

	std::string getType() const override
	{
		return "dit";
	}
};

// Derived class for Dah
class Dah : public Signal
{
public:
	Dah() : Signal(0, 3, 1) {} // Default values: counter = 0, max_value = 3, value = 1

	std::string getType() const override
	{
		return "dah";
	}
};

// Derived class for Space
class Space : public Signal
{
public:
	Space() : Signal(0, 3, 0) {} // Default values: counter = 0, max_value = 3, value = 0

	std::string getType() const override
	{
		return "space";
	}
};

// Representation of a codepoint in morse code (i.e. dits and dahs)
using SignalArray = std::array<Signal *, TELEGRAPH_CODEPOINT_LEN>;

// State of each laser in the array
using LaserStates = bool[LASER_ARRAY_LINES_N][LASER_ARRAY_LINE_LEN];

// Function to encode an Arabic numeral into a sequence of dits and dahs
SignalArray encodeNumeral(int numeral);

// Function to display signals
void displaySignals(const SignalArray &signals);

// Process input
void processInput();

#endif // SIGNAL_ENCODER_H
