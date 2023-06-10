#include "defines.h"
#include "InfoButton.h"
#include "button.h"
#include <sgg/graphics.h>

void InfoButton::draw()
{
	Button::draw();

	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "info.png";

	graphics::drawRect(Button::getPosX(), Button::getPosY(), Button::getSize()-0.2f, Button::getSize()-0.2f, br);
}
