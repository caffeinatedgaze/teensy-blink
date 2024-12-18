#include <Arduino.h>
#include <cstdlib>
#include "morse.hpp"

void setup()
{
	Dit dit;
	Dah dah;
	Space space;

	while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");
}

void loop()
{
	SignalSequence signalSequence = encodeNumeral(1);
	Signal* signal = signalSequence.front();
	std::cout << signal->getType().c_str() << std::endl;
}