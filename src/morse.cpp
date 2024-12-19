#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <Arduino.h>
#include "morse.hpp"

// Encode an Arabic numeral into a sequence of signals
Signals encodeNumeral(const char numeral[4])
{
	Signals sequence;
	for (int i = 0; i < 4; ++i)
	{
		int digit = numeral[i] - '0';
		for (bool isDit : morseCode[digit])
		{
			if (isDit)
			{
				sequence.push_back(new Dit());
			}
			else
			{
				sequence.push_back(new Dah());
			}
			sequence.push_back(new SpaceBetweenCharacters());
		}
		sequence.push_back(new SpaceBetweenCodepoints());
	}
	sequence.push_back(new BreakBetweenSentences());
	return sequence;
}
