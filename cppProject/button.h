#pragma once


class Button {
	float b_pos[2];
	bool b_highlight;
	float size;
public:
	Button(float x) { size = x; }

	void draw();
	void update();
	
	void setPosX(float x) { b_pos[0] = x; }
	void setPosY(float x) { b_pos[1] = x; }
	float getPosX() { return b_pos[0]; }
	float getPosY() { return b_pos[1]; }

	bool contains(float x, float y);
	void SetHigh(bool x) { b_highlight = x; }

	float getSize() { return size; }
	
};
