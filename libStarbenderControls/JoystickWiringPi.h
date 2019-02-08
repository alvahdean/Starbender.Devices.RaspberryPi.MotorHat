#pragma once

#include "RadialVector.h"

class JoystickWiringPi
{
public:
	JoystickWiringPi();
	~JoystickWiringPi();

	RadialVector Direction();

private:
	RadialVector _direction;
	int ReadChannel(int channel);
};

