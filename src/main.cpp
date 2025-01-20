#include "morse.hpp"
#include "codepoints.hpp"
#include "patternExecutor.hpp"
#include "main.hpp"

PatternExecutor *patternExecutor;
Adafruit_MCP23X17 mcp;

LaserStates laserStates;
uint64_t currentCodepointIdx = 0;
std::string currentCodepoint;
Signals currentCodepointMorseCode;
// Refresh rate that is equal to the duration of Dit – the shortest Morse code signal.
uint16_t refreshRate = 50; // in ms

// Serial port to the secondary.
const int rxPin = 21;
const int txPin = 20;

SoftwareSerial mySerial(rxPin, txPin);

#define TEST_REFRESH_RATE 50

void mcpDigitalWriteCallback(PinIdx pinIdx, int state)
{
	mcp.digitalWrite(pinIdx, state);
}

void setAllPinsAsOutput()
{
	// Set all of the non-extended pins as outputs.
	for (uint8_t j = 0; j < NON_EXTENDED_PINS_N; j++)
	{
		PinIdx pinIdx = pinByIdx.at(j);
		pinMode(pinIdx, OUTPUT);
		digitalWrite(pinIdx, LOW);
	}
	// Set all of the extended pins as outputs.
	for (uint8_t j = NON_EXTENDED_PINS_N; j < TOTAL_PINS_N; j++)
	{
		PinIdx pinIdx = pinByIdx.at(j);
		mcp.pinMode(pinIdx, OUTPUT);
		mcp.digitalWrite(pinIdx, LOW);
	}
}

// Make non-extended pins blink.
void testNonExtendedPins()
{
	for (uint8_t j = 0; j < NON_EXTENDED_PINS_N; j++)
	{
		PinIdx pinIdx = pinByIdx.at(j);
		digitalWrite(pinIdx, HIGH);
		delay(TEST_REFRESH_RATE);
	}
	delay(3000);
	for (uint8_t j = 0; j < NON_EXTENDED_PINS_N; j++)
	{
		PinIdx pinIdx = pinByIdx.at(j);
		digitalWrite(pinIdx, LOW);
		delay(TEST_REFRESH_RATE);
	}
}

// Make extended pins blink.
void testExtendedPins()
{
	for (uint8_t j = NON_EXTENDED_PINS_N; j < TOTAL_PINS_N; j++)
	{
		PinIdx pinIdx = pinByIdx.at(j);
		mcpDigitalWriteCallback(pinIdx, HIGH);
		delay(TEST_REFRESH_RATE);
	}
	delay(3000);
	for (uint8_t j = NON_EXTENDED_PINS_N; j < TOTAL_PINS_N; j++)
	{
		PinIdx pinIdx = pinByIdx.at(j);
		mcpDigitalWriteCallback(pinIdx, LOW);
		delay(TEST_REFRESH_RATE);
	}
}

void setup()
{
	while (!bitRead(USB1_PORTSC1, 7) && !Serial && millis() < 15000)
	// while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");

	mySerial.begin(9600);

	for (size_t i = 0; i < pinByIdx.size(); i++)
	{
		std::cout << "pinN = " << i << " " << pinByIdx.at(i) << std::endl;
	}

	patternExecutor = new PatternExecutor(PatternType::Linear, laserStates, mcpDigitalWriteCallback);

	if (0 == CODEPOINTS.size())
	{
		std::cout << "CODEPOINTS cannot be of zero length. Aborting.";
		exit(1);
	}

	if (!mcp.begin_I2C())
	{
		Serial.println("Failed to connect to the extender module over I2C.");
		while (1)
			;
	}

	setAllPinsAsOutput();
	testNonExtendedPins();
	testExtendedPins();
}

void teardown()
{
	delete patternExecutor;
}

void loop()
{
	std::cout << "Picking the next codepoint." << std::endl;
	currentCodepoint = CODEPOINTS.at(currentCodepointIdx);
	currentCodepointMorseCode = encodeNumeral(currentCodepoint.c_str());
	printSignals(currentCodepointMorseCode);
	std::cout << "Morse code length: " << currentCodepointMorseCode.size() << std::endl;

	for (size_t i = 0; i < currentCodepointMorseCode.size(); i++)
	{
		SignalPtr signal = currentCodepointMorseCode.at(i);

		// Set laser state according to the signal.
		patternExecutor->setLaserState(signal->value);
		std::cout << "Current signal type: " << signal->getType() << std::endl;
		printLaserStates(laserStates);
		// Wait for the signal duration.
		while (signal->counter < signal->max_value)
		{
			delay(refreshRate);
			signal->counter++;
		}
		// Move to the next laser according to the pattern.
		// Do not move if the next signal type is a break.
		if (i + 1 < currentCodepointMorseCode.size())
		{
			std::string currentCodepointType = currentCodepointMorseCode.at(i + 1)->getType();
			if (
				currentCodepointType != LETTER_BREAK &&
				currentCodepointType != WORD_BREAK &&
				currentCodepointType != SENTENCE_BREAK)
			{
				patternExecutor->chooseNextLaser();
			}
		}
	}

	currentCodepointIdx = (currentCodepointIdx + 1) % CODEPOINTS.size();
	std::cout << "Current codepoint Idx: " << currentCodepointIdx << std::endl;
	std::cout << "Codepoints length: " << CODEPOINTS.size() << std::endl;
	std::cout << "Free RAM: " << freeram() << std::endl;
}

void printLaserStates(LaserStates &laserStates)
{
	Serial.println("Primary laser states:");
	for (uint8_t x = 0; x < LASER_ARRAY_X; x++)
	{
		for (uint8_t y = 0; y < LASER_ARRAY_Y; y++)
		{
			Serial.print(laserStates.primaryLaserStates.at(x).at(y));
		}
		Serial.println();
	}
	Serial.println("Secondary laser states:");
	for (uint8_t x = 0; x < LASER_ARRAY_X; x++)
	{
		for (uint8_t y = 0; y < LASER_ARRAY_Y; y++)
		{
			Serial.print(laserStates.secondaryLaserStates.at(x).at(y));
		}
		Serial.println();
	}
}

int freeram()
{
	return (char *)&_heap_end - __brkval;
}