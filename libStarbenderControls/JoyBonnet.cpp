#include <thread>
#include <stdio.h>
#include <wiringPi.h>
#include "JoyBonnet.h"
#include "JoystickWiringPi.h"
#include "Button.h"

namespace JoyBonnet 
{
	JoystickWiringPi* Stick = nullptr;
	ButtonClass* Button[8];
	std::thread Monitor;
	bool volatile isRunning = false;
	bool _isInitialized = false;

	void monitorThread()
	{
		isRunning = true;
		bool current[BUTTON_COUNT];

		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			current[i] = Button[i]->Poll();
		}
		while (isRunning)
		{
			for (int i = 0; i < BUTTON_COUNT; i++)
			{
				bool value = Button[i]->Poll();
				if (value != current[i])
				{
					Button[i]->EdgeTransitionHandler();
					current[i] = value;
				}
			}
			delay(10);
		}
	}
	
	bool IsRunning() { return isRunning; }

	void Stop()
	{
		if (isRunning)
		{
			printf("Stopping JoyBonnet thread...\n");
			isRunning = false;
			printf("Joining JoyBonnet thread...\n");
			Monitor.join();
			printf("JoyBonnet thread complete...\n");
		}

		if (Stick != nullptr)
		{
			delete Stick;
			Stick = nullptr;
		}

		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			ButtonClass* button = Button[i];
			if (button != nullptr)
			{
				delete button;
				Button[i] = nullptr;
			}
		}
	}

	void Start(ButtonEventHandler handler)
	{
		if (!_isInitialized)
		{
			wiringPiSetup();
			_isInitialized = true;
		}

		if (IsRunning())
		{
			Stop();
		}

		Stick = new JoystickWiringPi();
		Button[BUTTON_PLAYER1] = new ButtonClass(BUTTON_PLAYER1_PIN, BUTTON_PLAYER1_NAME, 0, handler);
		Button[BUTTON_PLAYER2] = new ButtonClass(BUTTON_PLAYER2_PIN, BUTTON_PLAYER2_NAME, 0, handler);
		Button[BUTTON_SELECT] = new ButtonClass(BUTTON_SELECT_PIN, BUTTON_SELECT_NAME, 0, handler);
		Button[BUTTON_START] = new ButtonClass(BUTTON_START_PIN, BUTTON_START_NAME, 0, handler);
		Button[BUTTON_A] = new ButtonClass(BUTTON_A_PIN, BUTTON_A_NAME, 0, handler);
		Button[BUTTON_B] = new ButtonClass(BUTTON_B_PIN, BUTTON_B_NAME, 0, handler);
		Button[BUTTON_X] = new ButtonClass(BUTTON_X_PIN, BUTTON_X_NAME, 0, handler);
		Button[BUTTON_Y] = new ButtonClass(BUTTON_Y_PIN, BUTTON_Y_NAME, 0, handler);

		printf("Starting JoyBonnet thread...\n");

		std::thread Monitor (monitorThread);

		printf("Waiting on thread start...\n");
		while (!isRunning)
		{
			printf(".");
			fflush(stdout);
		}

		printf("\nJoyBonnet thread running...\n");
		Monitor.detach();
	}

	RadialVector Direction()
	{
		return Stick->Direction();
	}

	void TestHandler(ButtonClass& button, int eventId)
	{
		const char* name = button.Name();

		switch (eventId)
		{
		case BUTTON_EVENT_CLICKED:
			printf("Button[%s]: Clicked\n", name);
			break;
		case BUTTON_EVENT_RELEASED:
			printf("Button[%s]: Released\n", name);
			break;
		case BUTTON_EVENT_PRESSED:
			printf("Button[%s]: Pressed\n", name);
			break;
		default:
			printf("Button[%s]: Unhandled EventId %d\n", name, eventId);
			break;
		}
	}
}