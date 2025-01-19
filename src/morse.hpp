// signal_encoder.h
#ifndef SIGNAL_ENCODER_H
#define SIGNAL_ENCODER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

const std::vector<std::vector<bool>> morseCodeByDigit = {
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

#define DIT "dit"
#define DAH "dah"
#define LETTER_BREAK "."
#define WORD_BREAK "|"
#define SENTENCE_BREAK "break"

// Base class for Signal types. It signifies either a letter or a break.
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
		return DIT;
	}
};

// Derived class for Dah
class Dah : public Signal
{
public:
	Dah() : Signal(0, 3, true) {} // Default values: counter = 0, max_value = 3, value = 1

	std::string getType() const override
	{
		return DAH;
	}
};

// Derived class for Space. Space between letters.
class LetterBreak : public Signal
{
public:
	LetterBreak() : Signal(0, 1, false) {} // Default values: counter = 0, max_value = 3, value = 0

	std::string getType() const override
	{
		return LETTER_BREAK;
	}
};

class WordBreak : public Signal
{
public:
	WordBreak() : Signal(0, 3, false) {} // Default values: counter = 0, max_value = 3, value = 0

	std::string getType() const override
	{
		return WORD_BREAK;
	}
};

// Derived class for Space
class SentenceBreak : public Signal
{
public:
	SentenceBreak() : Signal(0, 7, false) {} // Default values: counter = 0, max_value = 7, value = 0

	std::string getType() const override
	{
		return SENTENCE_BREAK;
	}
};

using SignalPtr = std::shared_ptr<Signal>;
// Representation of a codepoint in morse code (i.e. dits and dahs)
using Signals = std::vector<SignalPtr>;

// Function to encode an Arabic numeral into a sequence of dits and dahs
Signals encodeNumeral(const char numeral[4]);

void printSignals(const Signals &signals);

#endif // SIGNAL_ENCODER_H
