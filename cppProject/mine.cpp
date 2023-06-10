#include "mine.h"
#include "defines.h"
#include <sgg/graphics.h>
#include "game.h"


void Mine::draw()
{
	graphics::Brush br;
	
	br.gradient = false;

	if (facing_down == true)
	{
		if (getHighlighted())
		{
			br.fill_secondary_color[0] = 0.66f;
			br.fill_secondary_color[1] = 0.66f;
			br.fill_secondary_color[2] = 0.66f;
			br.gradient = true;
		}
		

		if (!getFlagged())
		{
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "facingDown.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
		}
		else
		{
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "flagged.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
		}

	}
	else
	{
		switch (state)
		{
		case 0:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "0.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case 1:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "1.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case 2:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "2.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case 3:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "3.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case 4:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "4.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case 5:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "5.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case 6:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "6.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case 7:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "7.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case 8:
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "8.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		case -1:
			if (red_bomb) 
			{
				br.gradient = true;
				br.fill_color[0] = 1.0f;
				br.fill_color[1] = 0.0f;
				br.fill_color[2] = 0.0f;
				br.fill_opacity = 1.0f;
			}
			else
			{
				br.gradient = false;
				br.fill_color[0] = 0.0f;
			}
			br.outline_opacity = 0.0f;
			br.texture = std::string(ASSET_PATH) + "bomb.png";
			graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
			break;

		}
	}
}

void Mine::update()
{
	
}

bool Mine::contains(float x, float y)
{
	float dx = x - m_pos[0];
	float dy = y - m_pos[1];

	return abs(dx) < PLAYER_SIZE/2 && abs(dy) < PLAYER_SIZE/2;
}



