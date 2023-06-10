#pragma once
#include "button.h"

class InfoButton : public Button
{

public:
	InfoButton(float x) :Button(x) {};

	void draw();
};
