#include <Arduino.h>
#include <unity.h>
#include "main.hpp"

void setUp(void)
{
	// set stuff up here
}

void tearDown(void)
{
	// clean stuff up here
}

// Test that initial matrix is full of zeros.
void testInitialMatrix()
{
	// Arrange
	bool expectedPrimaryLaserStates[24][24] = {false};
	bool expectedSecondaryLaserStates[24][24] = {false};
	LaserStates laserStates;

	// Assert
	TEST_ASSERT_EQUAL_MEMORY(
		expectedPrimaryLaserStates, laserStates.primaryLaserStates, sizeof(expectedPrimaryLaserStates));
	TEST_ASSERT_EQUAL_MEMORY(
		expectedSecondaryLaserStates, laserStates.secondaryLaserStates, sizeof(expectedPrimaryLaserStates));
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
	RUN_TEST(testInitialMatrix);
	UNITY_END();
}