// #include <Arduino.h>
// #include <SoftwareSerial.h>
// #include <sstream>
// #include <string>
// #include "main.hpp"
// #include "patternExecutor.hpp"

// // Define RX and TX pins for SoftwareSerial
// const int rxPin = 21;
// const int txPin = 20;

// #define TEST_REFRESH_RATE 50

// SoftwareSerial mySerial(rxPin, txPin);
// PatternExecutor *patternExecutor;
// Adafruit_MCP23X17 mcp;
// LaserStates laserStates;

// void mcpDigitalWriteCallback(PinIdx pinIdx, int state)
// {
// 	mcp.digitalWrite(pinIdx, state);
// }

// void writeSerialCallback(const std::string &command)
// {
// 	mySerial.println(command.c_str());
// }

// void setAllPinsAsOutput()
// {
// 	// Set all of the non-extended pins as outputs.
// 	for (uint8_t j = 0; j < NON_EXTENDED_PINS_N; j++)
// 	{
// 		PinIdx pinIdx = pinByIdx.at(j);
// 		pinMode(pinIdx, OUTPUT);
// 		digitalWrite(pinIdx, LOW);
// 	}
// 	// Set all of the extended pins as outputs.
// 	for (uint8_t j = NON_EXTENDED_PINS_N; j < TOTAL_PINS_N; j++)
// 	{
// 		PinIdx pinIdx = pinByIdx.at(j);
// 		mcp.pinMode(pinIdx, OUTPUT);
// 		mcp.digitalWrite(pinIdx, LOW);
// 	}
// }

// // Make pins blink.
// void testPins()
// {
// 	for (uint8_t j = 0; j < NON_EXTENDED_PINS_N; j++)
// 	{
// 		PinIdx pinIdx = pinByIdx.at(j);
// 		digitalWrite(pinIdx, HIGH);
// 		delay(TEST_REFRESH_RATE);
// 	}
// 	for (uint8_t j = NON_EXTENDED_PINS_N; j < TOTAL_PINS_N; j++)
// 	{
// 		PinIdx pinIdx = pinByIdx.at(j);
// 		mcpDigitalWriteCallback(pinIdx, HIGH);
// 		delay(TEST_REFRESH_RATE);
// 	}
// 	delay(3000);
// 	for (uint8_t j = NON_EXTENDED_PINS_N; j < TOTAL_PINS_N; j++)
// 	{
// 		PinIdx pinIdx = pinByIdx.at(j);
// 		mcpDigitalWriteCallback(pinIdx, LOW);
// 		delay(TEST_REFRESH_RATE);
// 	}
// 	for (uint8_t j = 0; j < NON_EXTENDED_PINS_N; j++)
// 	{
// 		PinIdx pinIdx = pinByIdx.at(j);
// 		digitalWrite(pinIdx, LOW);
// 		delay(TEST_REFRESH_RATE);
// 	}
// }

// void setup()
// {
// 	Serial.begin(9600);
// 	mySerial.begin(9600);

// 	while (!bitRead(USB1_PORTSC1, 7) && !Serial && millis() < 15000)
// 	{
// 		// wait for the serial monitor to be ready.
// 	}
// 	Serial.println("Ready to receive commands...");

// 	if (!mcp.begin_I2C())
// 	{
// 		Serial.println("Failed to connect to the extender module over I2C.");
// 		while (1)
// 			;
// 	}

// 	patternExecutor = new PatternExecutor(PatternType::Linear, laserStates, mcpDigitalWriteCallback, writeSerialCallback);
// 	setAllPinsAsOutput();
// 	testPins();
// }

// void teardown()
// {
// 	delete patternExecutor;
// }

// struct Command
// {
// 	std::string cmd;
// 	PinIdx pinIdx;
// 	bool isExtended;
// 	bool state;
// };

// Command parseCommand(const std::string &command)
// {
// 	std::istringstream iss(command);
// 	Command cmdStruct;
// 	std::string cmd;
// 	int integerValue;
// 	bool boolValue1, boolValue2;

// 	iss >> cmd >> integerValue >> boolValue1 >> boolValue2;

// 	std::cout << "Command: " << cmd << std::endl;
// 	std::cout << "Pin Index: " << integerValue << std::endl;
// 	std::cout << "Is Extended: " << boolValue1 << std::endl;
// 	std::cout << "State: " << boolValue2 << std::endl;

// 	cmdStruct.cmd = cmd;
// 	cmdStruct.pinIdx = static_cast<PinIdx>(integerValue);
// 	cmdStruct.isExtended = boolValue1;
// 	cmdStruct.state = boolValue2;

// 	return cmdStruct;
// }

// void loop()
// {
// 	if (mySerial.available())
// 	{
// 		std::string command = mySerial.readStringUntil('\n').c_str();
// 		Command cmd = parseCommand(command);

// 		if (cmd.cmd == "SET")
// 		{
// 			Serial.print("Command: ");
// 			Serial.println(cmd.cmd.c_str());
// 			Serial.print("Pin Index: ");
// 			Serial.println(cmd.pinIdx);
// 			Serial.print("Is Extended: ");
// 			Serial.println(cmd.isExtended);
// 			Serial.print("State: ");
// 			Serial.println(cmd.state);

// 			std::cout << "Setting laser state." << std::endl;
// 			patternExecutor->setLaserState(cmd.pinIdx, cmd.state, cmd.isExtended);
// 		}
// 		else if (cmd.cmd == "BLINK")
// 		{
// 			Serial.print("Command: ");
// 			Serial.println(cmd.cmd.c_str());
// 			Serial.println("Blinking all pins.");
// 			setAllPinsAsOutput();
// 			testPins();
// 		}
// 		else if (cmd.cmd == "RESET")
// 		{
// 			Serial.print("Command: ");
// 			Serial.println(cmd.cmd.c_str());
// 			Serial.println("Resetting all pins.");
// 			setAllPinsAsOutput();
// 			testPins();
// 		}
// 		else
// 		{
// 			Serial.println("Unknown command");
// 		}
// 	}
// }