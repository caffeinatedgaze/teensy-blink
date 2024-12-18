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
	SignalSequence signalSequence = encodeNumeral(1);
	TEST_ASSERT_EQUAL_STRING(signalSequence.front()->getType().c_str(), "dit");
}

void test_2(void)
{
	SignalSequence signalSequence = encodeNumeral(1);
	TEST_ASSERT_EQUAL_STRING(signalSequence.front()->getType().c_str(), "dit");
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
	RUN_TEST(test_2);
	UNITY_END(); // stop unit testing
	exit(0);
}