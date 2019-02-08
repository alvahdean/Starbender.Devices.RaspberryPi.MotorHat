//#include "JoyBonnet.h"
#include <stdio.h>
#include <wiringPi.h>
#include <Starbender/JoyBonnet.h>

int main(void)
{

	printf("JoyBonnet starting...\n");
	JoyBonnet::Start(&JoyBonnet::TestHandler);
	printf("JoyBonnet running...\n");

	while (JoyBonnet::IsRunning()) 
	{ 
		RadialVector direction = JoyBonnet::Direction();
		if (direction.Magnitude>0)
		{
			printf("Direction: %.1f @ %.1f\n", direction.Magnitude, direction.Angle);
		}
		delay(10); 
	}

	printf("JoyBonnet exited...\n");

	return 0;
}
