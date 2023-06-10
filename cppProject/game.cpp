#include "defines.h"
#include "game.h"
#include <sgg/graphics.h>
#include "mine.h"
#include <list>
#include "time.h"
#include "face.h"
#include "button.h"
#include <chrono>
#include <thread>


Game* Game::m_instance = nullptr; 

void Game::drawMainScreen() 
{
	graphics::setFont("assets//te.ttf");
	graphics::Brush sr;
	sr.outline_opacity = 0.0f;
	sr.texture = std::string(ASSET_PATH) + "board.png";
	graphics::drawRect(CANVAS_WIDTH /2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, sr);
	sr.fill_color[0] = 0.5;
	sr.fill_color[1] = 0.0f;
	sr.fill_color[2] = 0.0f;
	graphics::drawText(CANVAS_WIDTH / 45, CANVAS_HEIGHT / 12, 0.9, "MINESWEEPER'S", sr);
	graphics::drawText(CANVAS_WIDTH / 15, CANVAS_HEIGHT / 7, 0.9, "WORLD", sr);
	

	fa->draw();

	iButton->draw();
	

	for (auto mine : m_mines)
	{
		mine->draw();
	}

	graphics::drawText(CANVAS_WIDTH - 8.0f, 2.2f, 0.9f, "Mines Left: " + std::to_string(count_mines), sr);
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "minesw.png";
	graphics::drawRect(CANVAS_WIDTH /2, CANVAS_HEIGHT /2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	
	
	
	graphics::setFont("assets//te.ttf");
	
	
	
	graphics::drawText(CANVAS_WIDTH / 5.8, CANVAS_HEIGHT / 1.1, 1.3, "PRESS ENTER TO START THE GAME", br);
}

void Game::drawEndScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.55f;
	br.fill_color[1] = 0.55f;
	br.fill_color[2] = 0.55f;
	br.fill_secondary_color[0] = 0.66f;
	br.fill_secondary_color[1] = 0.66f;
	br.fill_secondary_color[2] = 0.66f;
	br.gradient = true;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::setFont("assets//cr.ttf");
	br.gradient = false;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	
	
	rButton->draw();



	if (count_mines == 0)
	{	
    	graphics::drawText(CANVAS_WIDTH / 3.2, CANVAS_HEIGHT / 2.5, 1.5, "WHAT A GAME!!", br);
		graphics::drawText(CANVAS_WIDTH / 2.8, CANVAS_HEIGHT / 2, 1.5, "YOU WON!!", br);
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		br.texture = std::string(ASSET_PATH) + "im3.png";
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, FACE_SIZE * 1.5, FACE_SIZE * 1.5, br);
	}
	else
	{
		graphics::drawText(CANVAS_WIDTH /4, CANVAS_HEIGHT /2.5 , 1.5, "NOT A GOOD GAME!!", br);
		graphics::drawText(CANVAS_WIDTH / 2.8, CANVAS_HEIGHT / 2, 1.5, "YOU LOST!!", br);
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		br.texture = std::string(ASSET_PATH) + "im4.png";
		graphics::drawRect(CANVAS_WIDTH /2 , CANVAS_HEIGHT / 1.5, FACE_SIZE*1.5, FACE_SIZE*1.5, br);
	}
}

void Game::drawInfo()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.55f;
	br.fill_color[1] = 0.55f;
	br.fill_color[2] = 0.55f;
	br.fill_secondary_color[0] = 0.66f;
	br.fill_secondary_color[1] = 0.66f;
	br.fill_secondary_color[2] = 0.66f;
	br.gradient = true;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	iButton->draw();

	std::string info_1 = "Minesweeper rules are very simple. The board is divided into cells,";
	std::string info_2 = "with mines randomly distributed.To win, you need to open all the cells.";
	std::string info_3 = "The number on a cell shows the number of mines adjacent to it.Using ";
	std::string info_4 = "this information, you can determine cells that are safe, and cells";
	std::string info_5 = "that contain mines. Cells suspected of being mines can be marked";
	std::string info_6 = "with a flag using the right mouse button.";

	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;

	br.gradient = false;

	graphics::drawText(1, CANVAS_HEIGHT / 3, 0.85, info_1, br);
	graphics::drawText(1, CANVAS_HEIGHT / 3 + 1.5, 0.85, info_2, br);
	graphics::drawText(1, CANVAS_HEIGHT / 3 + 3, 0.85, info_3, br);
	graphics::drawText(1, CANVAS_HEIGHT / 3 + 4.5, 0.85, info_4, br);
	graphics::drawText(1, CANVAS_HEIGHT / 3 + 6, 0.85, info_5, br);
	graphics::drawText(1, CANVAS_HEIGHT / 3 + 7.5, 0.85, info_6, br);

}

void Game::draw()
{
	if (status == STATUS_BEGIN)
	{
		drawStartScreen();
	}
	else if(status==STATUS_PLAYING)
	{
		drawMainScreen();
	}
	else if (status == STATUS_INFO)
	{
		drawInfo();
	}
	else
	{
		drawEndScreen();
	}
}

void Game::destroy() 
{
	for (auto m : m_mines)
	{
		delete m;
	}
	m_mines.clear();
	delete fa;
	delete rButton;
	delete iButton;

	end_update_main = false;
}

void Game::updateEndScreen()
{

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	
	float bx = graphics::windowToCanvasX(float(ms.cur_pos_x));
	float by = graphics::windowToCanvasY(float(ms.cur_pos_y));
	
	
		if (rButton->contains(bx,by)==true) {
		
			rButton->SetHigh(true);
			if (ms.button_left_released) {
				status = STATUS_PLAYING;

				destroy();

				init();
			}
		
		}
		else {
			rButton->SetHigh(false);
		}
	
}

void Game::updateMainScreen() 
{
	if (end_update_main) 
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		status = STATUS_END;
	}

	if (count_mines == 0)
	{
		fa->setStatus(4);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		status = STATUS_END;
	}

	for (auto mine : m_mines)
	{
		mine->update();
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(float(ms.cur_pos_x));
	float my = graphics::windowToCanvasY(float(ms.cur_pos_y));

	int counter = 0;

	std::list<Mine*>::iterator it;

	Mine* it_mine;

	for (auto mine : m_mines)
	{
		if (mine->contains(mx, my))
		{
			mine->setHighlighted(true);

			if (ms.button_left_pressed)
			{
				graphics::playSound(std::string(ASSET_PATH) + "bt.wav", 0.5f, false);
			}

			if (ms.button_left_down) {
				fa->setStatus(3);
			}
			else if (ms.button_left_released)
			{	
				if (mine->getState() == -1)
				{
					fa->setStatus(2);
					mine->setRedBomb(true);
					end_update_main = true;
					graphics::playSound(std::string(ASSET_PATH) + "exp.wav", 0.5f, false);

					for (auto mine : m_mines)
					{
						if (mine->getState() == -1)
						{
							mine->turn();
						}
					}	
					
				}


				if (mine->getState() == 0)
				{
					if (mine->getFacingDown())
					{
						turnNeighbors(mine, counter);
					}	
				}

				mine->turn();
			}
			else {
				fa->setStatus(1);
			}

			

			if (ms.button_right_released)
			{
				if (mine->getFlagged())
				{
					mine->setFlagged(false);
				}
				else
				{
					mine->setFlagged(true);
				}
			}
		}
		else
		{
			mine->setHighlighted(false);
		}

		counter++;
	}

	count_mines = 180 - BOMBS;

	for (auto mine : m_mines)
	{
		if (mine->getState() != -1 && !mine->getFacingDown())
		{
			count_mines -= 1;
		}
	}

	if (iButton->contains(mx, my))
	{
		iButton->SetHigh(true);

		if (ms.button_left_released)
		{
			status = STATUS_INFO;
		}
	}
	else
	{
		iButton->SetHigh(false);
	}
}

void Game::updateStarScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_PLAYING;
	}
}

void Game::updateInfo()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(float(ms.cur_pos_x));
	float my = graphics::windowToCanvasY(float(ms.cur_pos_y));

	if (iButton->contains(mx, my))
	{
		iButton->SetHigh(true);

		if (ms.button_left_released)
		{
			status = STATUS_PLAYING;
		}
	}
	else
	{

		iButton->SetHigh(false);

	}
}

void Game::update()
{
	if (status == STATUS_BEGIN) {
		updateStarScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateMainScreen();
	}
	else if (status == STATUS_INFO)
	{
		updateInfo();
	}
	else {
		updateEndScreen();
	}
	
	
	
}

void Game::init()
{
	Mine* m;

	fa = new Face();

	rButton = new RestartButton(RESTART_BUTTON_SIZE);
	rButton->setPosX(1.5);
	rButton->setPosY(18.0);

	iButton = new InfoButton(INFO_BUTTON_SIZE);
	iButton->setPosX(CANVAS_WIDTH - 1.5f);
	iButton->setPosY(1.9f);

	count_mines = 180 - BOMBS;

	float x = 1.2f;
	float y = 4.7f;


	while (y < CANVAS_HEIGHT - 1)
	{
		x = 1.2f;
		while (x < CANVAS_WIDTH)
		{

			m = new Mine();
			m_mines.push_front(m);

			m->setPosX(x);
			m->setPosY(y);

			x += PLAYER_SIZE;
		}

		y += PLAYER_SIZE;
	}



	srand(time(0));

	int rand_num;

	for (int i = 1; i <= BOMBS; i++)
	{
		std::list<Mine*>::iterator it = m_mines.begin();

		rand_num = rand() % 180;

		std::advance(it, rand_num);

		Mine* mine = *it;

		while (mine->getState() == -1)
		{
			rand_num = rand() % 180;

			it = m_mines.begin();

			std::advance(it, rand_num);

			Mine* mine = *it;
		}

		mine->setState(-1);

		
		if (rand_num == 0)
		{
			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 17);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

		}
		else if (rand_num == 17)
		{
			std::advance(it, -1);
			mine = *it;
			mine->plusState();

			std::advance(it, 18);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();
		}
		else if (rand_num == 162)
		{
			std::advance(it, -18);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 18);
			mine = *it;
			mine->plusState();
		}
		else if (rand_num == 179)
		{
			std::advance(it, -1);
			mine = *it;
			mine->plusState();

			std::advance(it, -17);
			mine = *it;
			mine->plusState();

			std::advance(it, -1);
			mine = *it;
			mine->plusState();
		}
		else if (rand_num > 0 && rand_num < 17)
		{
			std::advance(it, -1);
			mine = *it;
			mine->plusState();

			std::advance(it, 2);
			mine = *it;
			mine->plusState();

			std::advance(it, 16);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();
		}
		else if (rand_num > 162 && rand_num < 179)
		{
			std::advance(it, -19);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 16);
			mine = *it;
			mine->plusState();

			std::advance(it, 2);
			mine = *it;
			mine->plusState();
		}
		else if (rand_num % 18 == 0)
		{
			std::advance(it, -18);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 18);
			mine = *it;
			mine->plusState();

			std::advance(it, 17);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();
		}
		else if ((rand_num + 1) % 18 == 0)
		{
			std::advance(it, -19);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 17);
			mine = *it;
			mine->plusState();

			std::advance(it, 18);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();
		}
		else
		{
			std::advance(it, -19);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 16);
			mine = *it;
			mine->plusState();

			std::advance(it, 2);
			mine = *it;
			mine->plusState();

			std::advance(it, 16);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();

			std::advance(it, 1);
			mine = *it;
			mine->plusState();
		}
		
		
	}

	

}

Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game();

	return m_instance;
}

Game::~Game()
{
	destroy();
}

void Game::turnNeighbors(Mine* m, int cnt)
{
		std::list<Mine*>::iterator it;

		Mine* it_mine;

		it = m_mines.begin();

		std::advance(it, cnt);

		if (cnt == 0)
		{
			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 17);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			//count_mines -= 3;
		}
		else if (cnt == 17)
		{
			std::advance(it, -1);
			m = *it;
			m->turn();

			std::advance(it, 18);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();
		
			//count_mines -= 3;
		}
		else if (cnt == 162)
		{
			std::advance(it, -18);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 18);
			m = *it;
			m->turn();

			//count_mines -= 3;
		}
		else if (cnt == 179)
		{
			std::advance(it, -1);
			m = *it;
			m->turn();

			std::advance(it, -17);
			m = *it;
			m->turn();

			std::advance(it, -1);
			m = *it;
			m->turn();

			//count_mines -= 3;
		}
		else if (cnt > 0 && cnt < 17)
		{
			std::advance(it, -1);
			m = *it;
			m->turn();

			std::advance(it, 2);
			m = *it;
			m->turn();

			std::advance(it, 16);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			//count_mines -= 5;
		}
		else if (cnt > 162 && cnt < 179)
		{
			std::advance(it, -19);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 16);
			m = *it;
			m->turn();

			std::advance(it, 2);
			m = *it;
			m->turn();

			//count_mines -= 5;
		}
		else if (cnt % 18 == 0)
		{
			std::advance(it, -18);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 18);
			m = *it;
			m->turn();

			std::advance(it, 17);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			//count_mines -= 5;
		}
		else if ((cnt + 1) % 18 == 0)
		{
			std::advance(it, -19);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 17);
			m = *it;
			m->turn();

			std::advance(it, 18);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			//count_mines -= 5;
		}
		else
		{
			std::advance(it, -19);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 16);
			m = *it;
			m->turn();

			std::advance(it, 2);
			m = *it;
			m->turn();

			std::advance(it, 16);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			std::advance(it, 1);
			m = *it;
			m->turn();

			//count_mines -= 8;
		}
}
