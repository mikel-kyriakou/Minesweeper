#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include "game.h"
#include "mine.h"

void draw()
{
	Game * mygame = (Game *) graphics::getUserData();
	mygame->draw();

}


void update(float ms)
{
	Game* mygame = (Game*)graphics::getUserData();
	mygame->update();
	
}


int main(int argc, char** argv)
{
	
	graphics::createWindow(900, 600, "MINESWEEPER v0.1");
	
	Game* game = Game::getInstance();
	graphics::setUserData(game);

	game->init();

	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::startMessageLoop();

	delete game;

	return 0;
}