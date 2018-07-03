#pragma once
#include "Scene.h"
#include "TTT_Playground.h"
#include "Animation.h"
#include "Loading_Bar.h"
#include "Data_Container.h"
#include <vector>
#include <memory>
#include <thread>
class TTT_Gameplay :
	public Scene
{
private:
	std::thread t;
	bool O_is_player, X_is_player, thinking = false;
	TTT_Playground playground;
	std::vector <std::shared_ptr <Animation>> animations;
	Loading_Bar loading_bar;
	int ai_bx = -1, ai_by = -1, ai_x = -1, ai_y = -1;
	int selected_board_x = -1, selected_board_y = -1, selected_cell_x = -1, selected_cell_y = -1;

	void tick();
	void draw(Bitmap& target);
	void set(int board_x, int board_y, int x, int y);
	void switch_player();
	void launch_ai_thread();
	void number_pressed(unsigned int number);
	void winner_scene();
	void confirmed();
	void arrow_pressed(sf::Vector2i direction);
	void returned();
	bool controls_player();

public:
	TTT_Gameplay(bool O_controls_player, bool X_controls_player);
	~TTT_Gameplay();
};

