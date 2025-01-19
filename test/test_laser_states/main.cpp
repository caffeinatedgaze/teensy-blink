#include <Arduino.h>
#include <unity.h>
#include "main.hpp"
#include "patternExecutor.hpp"
#include "patternExecutor.cpp"

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
	bool expectedPrimaryLaserStates[LASER_ARRAY_X][LASER_ARRAY_Y] = {false};
	bool expectedSecondaryLaserStates[LASER_ARRAY_X][LASER_ARRAY_Y] = {false};
	LaserStates laserStates;

	// Assert
	TEST_ASSERT_EQUAL_MEMORY(
		expectedPrimaryLaserStates, laserStates.primaryLaserStates, sizeof(expectedPrimaryLaserStates));
	TEST_ASSERT_EQUAL_MEMORY(
		expectedSecondaryLaserStates, laserStates.secondaryLaserStates, sizeof(expectedPrimaryLaserStates));
}

void testSwitchTeensy()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);

	// Act
	patternExecutor->switchTeensy();

	// Assert
	TEST_ASSERT_EQUAL(TeensyType::Secondary, patternExecutor->currentTeensyType);

	// Tear down
	delete patternExecutor;
}

// Test that the laser is switched to the next one in linear manner from initial state.
void testChooseNextLaserInitial()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);

	// Act
	patternExecutor->chooseNextLaser();

	// Assert
	TEST_ASSERT_EQUAL(0, patternExecutor->currentLaserX);
	TEST_ASSERT_EQUAL(1, patternExecutor->currentLaserY);
	TEST_ASSERT_EQUAL(TeensyType::Primary, patternExecutor->currentTeensyType);
}

// Test that there is a switch between arrays inside the primary teensy.
void testChooseNextLaserSwitchArrayInPrimary()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);
	patternExecutor->currentLaserY = LASER_ARRAY_Y - 1;

	// Act
	patternExecutor->chooseNextLaser();

	// Assert
	TEST_ASSERT_EQUAL(1, patternExecutor->currentLaserX);
	TEST_ASSERT_EQUAL(0, patternExecutor->currentLaserY);
	TEST_ASSERT_EQUAL(TeensyType::Primary, patternExecutor->currentTeensyType);

	// Tear down
	delete patternExecutor;
}

// Test that there is a switch between arrays inside the secondary teensy.
void testChooseNextLaserSwitchArrayInSecondary()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);
	patternExecutor->currentLaserY = LASER_ARRAY_Y - 1;
	patternExecutor->currentTeensyType = TeensyType::Secondary;

	// Act
	patternExecutor->chooseNextLaser();

	// Assert
	TEST_ASSERT_EQUAL(1, patternExecutor->currentLaserX);
	TEST_ASSERT_EQUAL(0, patternExecutor->currentLaserY);
	TEST_ASSERT_EQUAL(TeensyType::Secondary, patternExecutor->currentTeensyType);

	// Tear down
	delete patternExecutor;
}

// Test that there is a switch between teensy to secondary.
void testChooseNextLaserSwitchTeensyToSecondary()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);
	patternExecutor->currentLaserY = LASER_ARRAY_Y - 1;
	patternExecutor->currentTeensyType = TeensyType::Primary;
	patternExecutor->currentLaserX = 1;

	// Act
	patternExecutor->chooseNextLaser();

	// Assert
	TEST_ASSERT_EQUAL(0, patternExecutor->currentLaserX);
	TEST_ASSERT_EQUAL(0, patternExecutor->currentLaserY);
	TEST_ASSERT_EQUAL(TeensyType::Secondary, patternExecutor->currentTeensyType);

	// Tear down
	delete patternExecutor;
}

// Test that there is a switch between teensy to primary.
void testChooseNextLaserSwitchTeensyToPrimary()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);
	patternExecutor->currentLaserY = LASER_ARRAY_Y - 1;
	patternExecutor->currentTeensyType = TeensyType::Secondary;
	patternExecutor->currentLaserX = 1;

	// Act
	patternExecutor->chooseNextLaser();

	// Assert
	TEST_ASSERT_EQUAL(0, patternExecutor->currentLaserX);
	TEST_ASSERT_EQUAL(0, patternExecutor->currentLaserY);
	TEST_ASSERT_EQUAL(TeensyType::Primary, patternExecutor->currentTeensyType);

	// Tear down
	delete patternExecutor;
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
	RUN_TEST(testSwitchTeensy);
	RUN_TEST(testChooseNextLaserInitial);
	RUN_TEST(testChooseNextLaserSwitchArrayInPrimary);
	RUN_TEST(testChooseNextLaserSwitchArrayInSecondary);
	RUN_TEST(testChooseNextLaserSwitchTeensyToSecondary);
	RUN_TEST(testChooseNextLaserSwitchTeensyToPrimary);
	UNITY_END();
}