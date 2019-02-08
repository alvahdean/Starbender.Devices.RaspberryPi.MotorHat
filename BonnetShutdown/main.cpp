#include <stdio.h>
#include <wiringPi.h>
#include <Starbender/JoyBonnet.h>
#include <Starbender/Button.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
//#include <string.h>


#define GPIO_HALT_COMMAND "/usr/local/bin/gpiohalt"
#define SHUTDOWN_PIN		BUTTON_PLAYER1_PIN
#define TOGGLE_PIN			BUTTON_PLAYER2_PIN

bool enabled = true;
void ShutdownHandler(ButtonClass& button, int eventId);

int main(void)
{
	printf("BonnetShutdown startup...");
	JoyBonnet::Start(&ShutdownHandler);

	while (JoyBonnet::IsRunning())
	{
		delay(1000);
	}

	printf("BonnetShutdown exiting...");
	return 0;
}

void ShutdownHandler(ButtonClass& button, int eventId)
{
	const char* name = button.Name();
	const int pin = button.Pin();

	if (pin == SHUTDOWN_PIN && eventId == BUTTON_EVENT_CLICKED)
	{
		if (enabled)
		{
			printf("Shutting down Raspberry Pi in 4 seconds");
			fflush(stdout);
			for (int i = 0; i < 5; i++)
			{
				printf(".");
				fflush(stdout);
				delay(1000);
			}

			int status = setreuid(0, 0);

			if (status < 0) 
			{
				fprintf(stderr, "Insufficient privileges to shutdown system\n");
			}
			else 
			{
				system("shutdown -h now");
			}
		}
		else
		{
			printf("SHUTDOWN DISABLED\n");
		}
	}
	else if (pin == TOGGLE_PIN)
	{
		if (eventId == BUTTON_EVENT_CLICKED)
		{
			enabled = !enabled;
			if (enabled)
				printf("BonnetShutdown enabled\n");
			else
				printf("BonnetShutdown disabled\n");
		}
		else if (eventId == BUTTON_EVENT_RELEASED)
		{
				printf("BonnetShutdown exiting...\n");
				JoyBonnet::Stop();
		}
	}
}