struct LaserStates
// States (on/off) of lasers in each array.
{
	bool primaryLaserStates[24][24] = {false};
	bool secondaryLaserStates[24][24] = {false};
};