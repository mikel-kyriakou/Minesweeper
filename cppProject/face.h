#pragma once
#include "defines.h"


class Face {
	int status_face = 1;
	
	

public:
	void update();
	void draw();
	
	void setStatus(int x) { status_face = x; }
};