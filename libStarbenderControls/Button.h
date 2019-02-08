#pragma once

#if __cplusplus <= 199711L
#error This library needs at least a C++11 compliant compiler
#endif

#define MAX_BUTTON_NAME	32
#define BUTTON_EVENT_PRESSED	1
#define BUTTON_EVENT_RELEASED	2
#define BUTTON_EVENT_CLICKED	3

class ButtonClass;

typedef void(*ButtonEventHandler)(ButtonClass& button, int eventId);
typedef void(*WiringPiInterruptHandler)(void);

class ButtonClass
{
public:
	ButtonClass(int pin, const char* name, int pressedPinValue, ButtonEventHandler handler);
	~ButtonClass();

	const char* Name();
	int Pin();
	bool IsPressed();
	bool IsConfigured();
	bool Configure(int pin, const char* name, int pressedPinValue, ButtonEventHandler handler);
	void SetClickInterval(unsigned long interval);
	bool Poll();
	bool Poll(bool setState);
	void EdgeTransitionHandler();

private:
	int _pin;
	int _pressedPinValue;
	char _name[MAX_BUTTON_NAME];
	bool _isPressed;
	unsigned long _pressTimestamp;
	unsigned long _releaseTimestamp;
	unsigned long _clickInterval;
	ButtonEventHandler eventHandler;

	void init(int pin, const char* name, int pressedPinValue, ButtonEventHandler handler);
	void setName(const char* newName);
	bool isValidPin(int pin);
};

