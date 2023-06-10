#pragma once
#include <sgg/graphics.h>
#include "defines.h"

class Mine
{
	float m_pos[2];
	int state = 0;
	bool facing_down = true;
	bool m_highlighted = false;
	bool flagged = false;
	bool red_bomb = false;

public:

	void draw();
	void update();

	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float x) { m_pos[1] = x; }

	int getState() { return state; }
	void setState(int num) { state = num; }
	void plusState() { if(state!=-1) state += 1; }

	void turn() { facing_down = false; }
	bool getFacingDown() { return facing_down; }

	void setHighlighted(bool b) { m_highlighted = b; }
	bool getHighlighted() { return m_highlighted; }

	bool contains(float x, float y);

	bool getFlagged(){ return flagged; }
	void setFlagged(bool b) { flagged = b; }

	bool getRedBomb() { return red_bomb; }
	void setRedBomb(bool b) { red_bomb = b; }
	
};
