/*
 * isr.c:
 *	Wait for Interrupt test program - ISR method
 *
 *	How to test:
 *	  Use the SoC's pull-up and pull down resistors that are avalable
 *	on input pins. So compile & run this program (via sudo), then
 *	in another terminal:
 *		gpio mode 0 up
 *		gpio mode 0 down
 *	at which point it should trigger an interrupt. Toggle the pin
 *	up/down to generate more interrupts to test.
 *
 * Copyright (c) 2013 Gordon Henderson.
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include "Button.h"
#include "JoyBonnet.h"

int main(void)
{
	printf("Start JoyBonnet...\n");
	JoyBonnet::Start(ButtonHandler);

	printf("JoyBonnet running...\n");
	while (JoyBonnet::IsRunning())
	{
		delay(50);
	}
}

void ButtonHandler(ButtonClass& button, int eventId)
{
	char* name = button.Name();
	switch(eventId)
	{
	case BUTTON_EVENT_PRESSED:
		printf("%s pressed\n", name);
		break;
	case BUTTON_EVENT_RELEASED:
		printf("%s released\n", name);
		break;
	case BUTTON_EVENT_CLICKED:
		printf("%s clicked\n", name);
		break;
	default:
		printf("%s unhandled event\n", name);
		break;
	}
}

