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

void test_encodeNumeral_1111(void)
{
	// Arrange
	Signals expectedSignals = {
		// 1
		new Dit(),
		new Dah(),
		new Dah(),
		new Dah(),
		new Dah(),
		// 1
		new Dit(),
		new Dah(),
		new Dah(),
		new Dah(),
		new Dah(),
		// 1
		new Dit(),
		new Dah(),
		new Dah(),
		new Dah(),
		new Dah(),
		// 1
		new Dit(),
		new Dah(),
		new Dah(),
		new Dah(),
		new Dah(),
	};

	// Act
	Signals signals = encodeNumeral("1111");

	// Assert
	TEST_ASSERT_EQUAL_INT(expectedSignals.size(), signals.size());
	for (u_int i = 0; i < signals.size(); i++)
	{
		TEST_ASSERT(*signals.at(i) == *expectedSignals[i]);
	}
}

void test_encodeNumeral_9123(void)
{
	// Arrange
	Signals expectedSignals = {
		// 9
		new Dah(),
		new Dah(),
		new Dah(),
		new Dah(),
		new Dit(),
		// 1
		new Dit(),
		new Dah(),
		new Dah(),
		new Dah(),
		new Dah(),
		// 2
		new Dit(),
		new Dit(),
		new Dah(),
		new Dah(),
		new Dah(),
		// 3
		new Dit(),
		new Dit(),
		new Dit(),
		new Dah(),
		new Dah(),
	};

	// Act
	Signals signals = encodeNumeral("9123");

	// Assert
	TEST_ASSERT_EQUAL_INT(expectedSignals.size(), signals.size());
	for (u_int i = 0; i < signals.size(); i++)
	{
		TEST_ASSERT(*signals.at(i) == *expectedSignals[i]);
	}
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

int main(void)
{
	setup();
	RUN_TEST(test_encodeNumeral_1111);
	RUN_TEST(test_encodeNumeral_9123);
	UNITY_END();
}