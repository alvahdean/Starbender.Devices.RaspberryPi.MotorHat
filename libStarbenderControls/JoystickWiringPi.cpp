#include "JoystickWiringPi.h"
#include <wiringPi.h>
#include <ads1115.h>
#include <stdio.h>
#include <math.h>

#define ADS115_ADDRESS		0x48
#define ADS115_PIN_BASE	1115 
#define PI 3.14159265
#define ADS_DIR_MAX	26272

JoystickWiringPi::JoystickWiringPi()
{
	ads1115Setup(ADS115_PIN_BASE, ADS115_ADDRESS);
	pinMode(ADS115_PIN_BASE, INPUT);
	pinMode(ADS115_PIN_BASE+1, INPUT);
	_direction.Magnitude = 0;
	_direction.Angle = 0;
}


JoystickWiringPi::~JoystickWiringPi()
{
}

RadialVector JoystickWiringPi::Direction()
{
	double y = ReadChannel(0);
	double x = ReadChannel(1);
	// printf("Direction: Raw X=%.1f, Raw Y=%.1f\n", x, y);

	double zero = ADS_DIR_MAX / 2;
	double xnorm = (x - zero) / zero;
	double ynorm = (zero - y) / zero;

	double mag= round(sqrt((xnorm*xnorm) + (ynorm*ynorm))*10)/10;
	double angle = 0;
	if (mag!=0)
		angle = atan2(ynorm, xnorm) * 180 / PI;

	_direction.Magnitude = mag;
	_direction.Angle = angle;

	// printf("Direction: Norm X=%.1f, Norm Y=%.1f, Magnitude=%.4f, Angle=%.1f\n", xnorm, ynorm, mag, angle);

	return _direction;
}

int JoystickWiringPi::ReadChannel(int channel)
{
	return analogRead(ADS115_PIN_BASE + channel);
}