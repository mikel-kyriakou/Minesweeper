#pragma once
#include <list>
#include "mine.h"
#include "face.h"
#include "button.h"
#include "RestartButton.h"
#include "InfoButton.h"


class Game
{
	typedef enum{STATUS_BEGIN,STATUS_PLAYING,STATUS_END, STATUS_INFO} status_t;
	static Game* m_instance;
	Game() {}
	Face* fa;
	std::list<Mine*> m_mines;
	status_t status = STATUS_BEGIN;
	int count_mines;
	RestartButton* rButton;
	InfoButton* iButton;
	bool end_update_main = false;

public:
	void draw();
	void update();
	void init();	
	static Game* getInstance();
	~Game();
	void updateStarScreen();
	void updateMainScreen();
	void drawStartScreen();
	void drawMainScreen();
	void drawEndScreen();
	void drawInfo();
	void updateInfo();
	void updateEndScreen();
	void destroy();
	void turnNeighbors(Mine* m, int cnt);
};