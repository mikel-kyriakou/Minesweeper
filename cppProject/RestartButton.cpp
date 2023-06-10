#include "defines.h"
#include "RestartButton.h"
#include "button.h"
#include <sgg/graphics.h>

void RestartButton::draw()
{
	Button::draw();

	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "po.png";

	graphics::drawRect(Button::getPosX(), Button::getPosY(), Button::getSize(), Button::getSize(), br);
}