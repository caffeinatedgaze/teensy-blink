#include <Arduino.h>
#include <unity.h>
#include "morse.hpp"
#include "morse.cpp"

void setUp(void)
{
	// set stuff up here
}

void tearDown(void)
{
	// clean stuff up here
}

void test_1(void)
{
	SignalArray signalSequence = encodeNumeral(1);
	TEST_ASSERT_EQUAL_STRING(signalSequence.front()->getType().c_str(), "dit");
}

void test_process_input(void)
{
}

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	while (!Serial && millis() < 15000)
	{
		// wait for Arduino Serial Monitor to be ready
	}
	Serial.println("Serial port is ready.");

	UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{
	RUN_TEST(test_1);
	RUN_TEST(test_process_input);
	UNITY_END(); // stop unit testing
	exit(0);
}