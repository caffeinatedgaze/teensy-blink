#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>
#include <Arduino.h>
#include "morse.hpp"

// Encode an Arabic numeral into a sequence of signals
Signals encodeNumeral(const char numeral[4])
{
	Signals sequence;
	for (size_t i = 0; i < 4; ++i)
	{
		int digit = numeral[i] - '0';
		bool isNotLastSignalForWord = i < 3;
		for (size_t j = 0; j < morseCodeByDigit[digit].size(); j++)
		{
			bool isDit = morseCodeByDigit[digit][j];
			bool isNotLastSignalForLetter = j < morseCodeByDigit[digit].size() - 1;
			if (isDit)
			{
				sequence.push_back(std::make_shared<Dit>());
			}
			else
			{
				sequence.push_back(std::make_shared<Dah>());
			}
			if (isNotLastSignalForLetter)
			{
				sequence.push_back(std::make_shared<LetterBreak>());
			}
		}
		if (isNotLastSignalForWord)
		{
			sequence.push_back(std::make_shared<WordBreak>());
		}
	}
	for (const auto& signal : sequence)
	{
		std::cout << signal->getType() << " ";
	}
	std::cout << std::endl;
	return sequence;
}
