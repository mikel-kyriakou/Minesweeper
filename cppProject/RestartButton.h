#pragma once
#include "button.h"

class RestartButton : public Button
{

public:
	RestartButton(float x) : Button(x) {};

	void draw();

};