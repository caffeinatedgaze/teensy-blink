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

// expected encoded sequence:
//
// 	dit . dah . dah . dah . dah | dit . dah . dah . dah . dah | dit . dah . dah . dah . dah | dit . dah . dah . dah . dah
void test_encodeNumeral_1111(void)
{
	// Arrange
	Signals expectedSignals = {
		// 1
		new Dit(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new WordBreak(),
		// 1
		new Dit(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new WordBreak(),
		// 1
		new Dit(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new WordBreak(),
		// 1
		new Dit(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
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

// expected encoded sequence:
//
// 	dah . dah . dah . dah . dit | dit . dah . dah . dah . dah | dit . dit . dah . dah . dah | dit . dit . dit . dah . dah
void test_encodeNumeral_9123(void)
{
	// Arrange
	Signals expectedSignals = {
		// 9
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dit(),
		new WordBreak(),
		// 1
		new Dit(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new WordBreak(),
		// 2
		new Dit(),
		new LetterBreak(),
		new Dit(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
		new Dah(),
		new WordBreak(),
		// 3
		new Dit(),
		new LetterBreak(),
		new Dit(),
		new LetterBreak(),
		new Dit(),
		new LetterBreak(),
		new Dah(),
		new LetterBreak(),
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