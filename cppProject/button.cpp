#pragma once

#include "button.h"
#include "defines.h"
#include "sgg/graphics.h"

void Button::draw() 
{	

	graphics::Brush button;

	if (b_highlight == true)
	{
		button.gradient = true;
	}
	else
	{
		button.gradient = false;
	}

	button.fill_secondary_color[0] = 0.66f;
	button.fill_secondary_color[1] = 0.66f;
	button.fill_secondary_color[2] = 0.66f;
		
	button.outline_opacity = 0.0f;
	button.texture = std::string(ASSET_PATH) + "facingDown.png";
	graphics::drawRect(b_pos[0], b_pos[1], size, size, button);

}

bool Button::contains(float x, float y)
{
	float dx = x - b_pos[0];
	float dy = y - b_pos[1];

	return abs(dx) < size / 2 && abs(dy) <size / 2;
}
