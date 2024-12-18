#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "morse.hpp"


// Function 1: Display signals
void displaySignals(const SignalSequence& signals) {
    std::cout << "Signal Sequence:\n";
    for (const auto& signal : signals) {
        std::cout << "Type: " << signal->getType()
                  << ", Counter: " << signal->counter
                  << ", Max Value: " << signal->max_value
                  << ", Value: " << signal->value << std::endl;
    }
}

// Function 2: Encode an Arabic numeral into a sequence of signals
SignalSequence encodeNumeral(int numeral) {
    SignalSequence sequence;

    std::cout << "Encoding numeral: " << numeral << std::endl;

    while (numeral > 0) {
        int digit = numeral % 10;
        if (digit == 0) {
            sequence.push_back(new Space());
        } else if (digit % 2 == 0) {
            sequence.push_back(new Dah());
        } else {
            sequence.push_back(new Dit());
        }
        numeral /= 10;
    }

    // Reverse sequence to maintain digit order
    std::reverse(sequence.begin(), sequence.end());

    return sequence;
}

// Main function to test functionality
// int main() {
//     std::cout << "--- Testing Signal Classes ---\n";
//     Dit dit;
//     Dah dah;
//     Space space;

//     std::cout << "Dit -> Type: " << dit.getType() << ", Max Value: " << dit.max_value << ", Value: " << dit.value << std::endl;
//     std::cout << "Dah -> Type: " << dah.getType() << ", Max Value: " << dah.max_value << ", Value: " << dah.value << std::endl;
//     std::cout << "Space -> Type: " << space.getType() << ", Max Value: " << space.max_value << ", Value: " << space.value << std::endl;

//     std::cout << "\n--- Testing Numeral Encoding ---\n";
//     int numeral = 12030;
//     SignalSequence encodedSequence = encodeNumeral(numeral);
//     displaySignals(encodedSequence);

//     // Clean up dynamically allocated memory
//     for (auto* signal : encodedSequence) {
//         delete signal;
//     }

//     return 0;
// }
