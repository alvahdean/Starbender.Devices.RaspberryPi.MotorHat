#include "Button.h"
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

#include <chrono>
using namespace std::chrono;

ButtonClass::ButtonClass(int pin, const char* name, int pressedPinValue, ButtonEventHandler handler)
{
	init(pin, name, pressedPinValue,handler);
}

void ButtonClass::init(int pin, const char* name, int pressedPinValue, ButtonEventHandler handler)
{
	_pin = -1;
	_clickInterval = 500;
	_pressedPinValue = 0;
	_isPressed = false;
	_pressTimestamp = 0;
	_releaseTimestamp = 0;
	Configure(pin, name, _pressedPinValue,handler);
}

ButtonClass::~ButtonClass()
{
}

const char* ButtonClass::Name() { return (const char*) _name; }

int ButtonClass::Pin() { return _pin; }

bool ButtonClass::IsPressed() 
{
	return _isPressed;
}

bool ButtonClass::IsConfigured()
{
	return isValidPin(_pin);
}

bool ButtonClass::Configure(int pin, const char* name, int pressedPinValue, ButtonEventHandler handler)
{
	_pin = pin;
	setName(name);
	_pressedPinValue = pressedPinValue;
	eventHandler = handler;
	if (isValidPin(_pin))
	{
		pinMode(pin, INPUT);
		if (pressedPinValue == 0)
		{
			pullUpDnControl(pin, PUD_UP);
		}
		else 
		{
			pullUpDnControl(pin, PUD_DOWN);
		}
		if (IsConfigured())
		{
			Poll();
		}
	}
	return IsConfigured();
}

void ButtonClass::SetClickInterval(unsigned long interval) { _clickInterval = interval; }

bool ButtonClass::Poll()
{
	return Poll(false);
}

bool ButtonClass::Poll(bool setState)
{
	if (!IsConfigured())
	{
		printf("Button.Poll: Button not configured!\n");
		return false;
	}

	int pinValue= digitalRead(_pin);
	bool isPressed = (pinValue == _pressedPinValue);

	if(setState)
		_isPressed = isPressed;

	return isPressed;
}

void ButtonClass::setName(const char* newName)
{
	if (newName == nullptr)
		newName = "";
	strncpy(_name, newName, MAX_BUTTON_NAME);
	_name[MAX_BUTTON_NAME - 1] = 0;
}

bool ButtonClass::isValidPin(int pin)
{
	return pin >= 0 && pin <= 30;
}

void ButtonClass::EdgeTransitionHandler()
{
	_isPressed = !_isPressed;

	unsigned long timestamp =
		std::chrono::system_clock::now().time_since_epoch() /
		std::chrono::milliseconds(1);
		//// system_clock::now().time_since_epoch() /
		//// milliseconds(1);

	if (!_isPressed)
	{
		unsigned long interval = timestamp - _pressTimestamp;
		_releaseTimestamp = timestamp;

		if (interval < _clickInterval && eventHandler != nullptr)
			eventHandler(*this,BUTTON_EVENT_CLICKED);
		else if (eventHandler != nullptr)
			eventHandler(*this,BUTTON_EVENT_RELEASED);
	}
	else
	{
		_pressTimestamp = timestamp;
		if(eventHandler !=nullptr)
			eventHandler(*this, BUTTON_EVENT_PRESSED);
	}
}