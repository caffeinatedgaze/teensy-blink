#include <Arduino.h>
#include <unity.h>
#include <iostream>
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
	std::array<std::array<bool, LASER_ARRAY_Y>, LASER_ARRAY_X> expectedPrimaryLaserStates = {false};
	std::array<std::array<bool, LASER_ARRAY_Y>, LASER_ARRAY_X> expectedSecondaryLaserStates = {false};
	// bool expectedPrimaryLaserStates[LASER_ARRAY_X][LASER_ARRAY_Y] = {false};
	// bool expectedSecondaryLaserStates[LASER_ARRAY_X][LASER_ARRAY_Y] = {false};
	LaserStates laserStates;

	// Assert
	for (int i = 0; i < LASER_ARRAY_X; i++)
	{
		for (int j = 0; j < LASER_ARRAY_Y; j++)
		{
			TEST_ASSERT_EQUAL(expectedPrimaryLaserStates.at(i).at(j), laserStates.primaryLaserStates.at(i).at(j));
			TEST_ASSERT_EQUAL(expectedSecondaryLaserStates.at(i).at(j), laserStates.secondaryLaserStates.at(i).at(j));
		}
	}
	// TEST_ASSERT_EQUAL_MEMORY(
	// 	expectedPrimaryLaserStates, laserStates.primaryLaserStates, sizeof(expectedPrimaryLaserStates));
	// TEST_ASSERT_EQUAL_MEMORY(
	// 	expectedSecondaryLaserStates, laserStates.secondaryLaserStates, sizeof(expectedPrimaryLaserStates));
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

// Test that the previous laser is set to off when moving on to the next one.
void testLaserResetWhenMovingOn()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);
	patternExecutor->currentLaserY = 0;
	patternExecutor->currentLaserX = 0;
	patternExecutor->currentTeensyType = TeensyType::Primary;
	patternExecutor->setLaserState(true);

	// Act
	patternExecutor->chooseNextLaser();
	patternExecutor->setLaserState(true);

	// Assert
	TEST_ASSERT_EQUAL(false, laserStates.primaryLaserStates.at(0).at(0));
	TEST_ASSERT_EQUAL(true, laserStates.primaryLaserStates.at(0).at(1));

	// Tear down
	delete patternExecutor;
}

// Test that all of the previous lasers are off when moving on to the next one 4 times.
void testLaserResetWhenMovingOn4Times()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);
	patternExecutor->currentLaserY = 0;
	patternExecutor->currentLaserX = 0;
	patternExecutor->currentTeensyType = TeensyType::Primary;
	patternExecutor->setLaserState(true);

	// Act
	for (int i = 0; i < 4; i++)
	{
		patternExecutor->chooseNextLaser();
		patternExecutor->setLaserState(true);
	}

	// Assert
	TEST_ASSERT_EQUAL(false, laserStates.primaryLaserStates.at(0).at(0));
	TEST_ASSERT_EQUAL(false, laserStates.primaryLaserStates.at(0).at(1));
	TEST_ASSERT_EQUAL(false, laserStates.primaryLaserStates.at(0).at(2));
	TEST_ASSERT_EQUAL(false, laserStates.primaryLaserStates.at(0).at(3));
	TEST_ASSERT_EQUAL(true, laserStates.primaryLaserStates.at(0).at(4));

	// Tear down
	delete patternExecutor;
}

// Test that all of the previous lasers are off when moving on to the next one N times.
void testLaserResetWhenMovingOnNTimes()
{
	// Arrange
	LaserStates laserStates;
	PatternExecutor *patternExecutor = new PatternExecutor(PatternType::Linear, laserStates);
	patternExecutor->currentLaserY = 0;
	patternExecutor->currentLaserX = 0;
	patternExecutor->currentTeensyType = TeensyType::Primary;
	patternExecutor->setLaserState(true);
	const int numberOfMoves = 16;

	// Act
	for (int i = 0; i < numberOfMoves; i++)
	{
		patternExecutor->chooseNextLaser();
		patternExecutor->setLaserState(true);
	}

	// Assert
	for (int i = 0; i < numberOfMoves; i++)
	{
		TEST_ASSERT_EQUAL(false, laserStates.primaryLaserStates.at(0).at(i));
	}
	TEST_ASSERT_EQUAL(true, laserStates.primaryLaserStates.at(0).at(numberOfMoves));

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
	RUN_TEST(testLaserResetWhenMovingOn);
	RUN_TEST(testLaserResetWhenMovingOn4Times);
	RUN_TEST(testLaserResetWhenMovingOnNTimes);
	UNITY_END();
}