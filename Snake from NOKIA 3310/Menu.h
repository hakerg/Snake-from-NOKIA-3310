#pragma once
#include "Scene.h"
#include <vector>
class Menu :
	public Scene
{
private:
	unsigned int current = 0, page_begin = 0;
#ifdef _DEBUG
	sf::Clock frametime;
	sf::Time next_fps = sf::seconds(1.0f);
	int frames = 0, fps = 0;
#endif

	void confirmed();
	void number_pressed(unsigned int number);
	void arrow_pressed(sf::Vector2i direction);
	void draw_scroll(Bitmap& target);
	void change_current_item(int new_position);
	void draw(Bitmap& target);
	virtual void item_selected(int id) = 0;

protected:
	std::vector <std::string> items;
	std::vector <int> numbers;

	Menu(std::vector <int> tree_numbers, std::vector <std::string> items_strings);
	~Menu();
};

