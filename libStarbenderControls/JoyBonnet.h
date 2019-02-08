#pragma once
#include "Button.h"
#include "RadialVector.h"

// Define the pin index
#define BUTTON_PLAYER1		0
#define BUTTON_PLAYER2		1
#define BUTTON_START		2
#define BUTTON_SELECT		3
#define BUTTON_A			4
#define BUTTON_B			5
#define BUTTON_X			6
#define BUTTON_Y			7

#define BUTTON_MASK_ALL		0xFF
#define BUTTON_COUNT		8

// Define the BCM pin numbers linked to the buttons on the bonnet
#define BUTTON_PLAYER1_PIN	4
#define BUTTON_PLAYER2_PIN	3
#define BUTTON_START_PIN	25
#define BUTTON_SELECT_PIN	28
#define BUTTON_A_PIN		26
#define BUTTON_B_PIN		22
#define BUTTON_X_PIN		27
#define BUTTON_Y_PIN		23

#define BUTTON_PLAYER1_NAME	"PLAYER 1"
#define BUTTON_PLAYER2_NAME	"PLAYER 2"
#define BUTTON_START_NAME	"START"
#define BUTTON_SELECT_NAME	"SELECT"
#define BUTTON_A_NAME		"A"
#define BUTTON_B_NAME		"B"
#define BUTTON_X_NAME		"X"
#define BUTTON_Y_NAME		"Y"

namespace JoyBonnet
{
	void Start(ButtonEventHandler handler);
	void Stop();
	bool IsRunning();
	RadialVector Direction();
	void TestHandler(ButtonClass& button, int eventId);
};
