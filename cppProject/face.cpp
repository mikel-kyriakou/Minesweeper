#include "sgg/graphics.h"
#include "defines.h"
#include "face.h"

void Face::update()
{


	}

void Face::draw()
{
	graphics::Brush face;
	face.outline_opacity = 0.0f;
	switch (status_face) {

	case 1:
		
		face.texture = std::string(ASSET_PATH) + "im1.png";
		
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 10.7, FACE_SIZE,FACE_SIZE, face);
		break;

	case 2:
		
		face.texture = std::string(ASSET_PATH) + "im4.png";
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 10.7, FACE_SIZE, FACE_SIZE, face);
		break;
	
	case 3:
		
		face.texture = std::string(ASSET_PATH) + "im2.png";
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 10.7, FACE_SIZE, FACE_SIZE, face);
		break;

	case 4:
		
		face.texture = std::string(ASSET_PATH) + "im3.png";
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 10.7, FACE_SIZE, FACE_SIZE, face);
		


	}
}