#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <Arduino.h>
#include "morse.hpp"

// Function 1: Display signals
void displaySignals(const SignalArray &signals)
{
	std::cout << "Signal Sequence:\n";
	for (const auto &signal : signals)
	{
		std::cout << "Type: " << signal->getType()
				  << ", Counter: " << signal->counter
				  << ", Max Value: " << signal->max_value
				  << ", Value: " << signal->value << std::endl;
	}
}

// Function 2: Encode an Arabic numeral into a sequence of signals
SignalArray encodeNumeral(int numeral)
{
	SignalArray sequence = {&Dit(), &Dah()};
	return sequence;
}

// void setup()
// {
// 	Dit dit;
// 	Dah dah;
// 	Space space;

// 	while (!Serial && millis() < 15000)
// 	{
// 		// wait for Arduino Serial Monitor to be ready
// 	}
// 	Serial.println("Serial port is ready.");

// 	// std::cout << "Dit -> Type: " << dit.getType() << ", Max Value: " << dit.max_value << ", Value: " << dit.value << std::endl;
// 	// std::cout << "Dah -> Type: " << dah.getType() << ", Max Value: " << dah.max_value << ", Value: " << dah.value << std::endl;
// 	// std::cout << "Space -> Type: " << space.getType() << ", Max Value: " << space.max_value << ", Value: " << space.value << std::endl;

// 	// std::cout << "\n--- Testing Numeral Encoding ---\n";
// 	// int numeral = 12030;
// 	// SignalSequence encodedSequence = encodeNumeral(numeral);
// 	// displaySignals(encodedSequence);

// 	// // Clean up dynamically allocated memory
// 	// for (auto *signal : encodedSequence)
// 	// {
// 	// 	delete signal;
// 	// }
// }
