#include "Menu.h"
#include "Data_Container.h"



Menu::Menu(std::vector <int> tree_numbers, std::vector <std::string> items_strings) :
	numbers(tree_numbers), items(items_strings)
{
}


Menu::~Menu()
{
}


void Menu::confirmed()
{
	item_selected(current);
}


void Menu::number_pressed(unsigned int number)
{
	if (number == 0) number = 9;
	else number--;
	if (number < items.size()) {
		change_current_item(number);
		item_selected(current);
	}
}


void Menu::arrow_pressed(sf::Vector2i direction)
{
	change_current_item((current + direction.y + items.size()) % items.size());
}


void Menu::draw(Bitmap& target)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		if (page_begin + i >= items.size()) break;
		data.medium_bold_font.draw_string(target, items[page_begin + i], 2, 8 + i * 10);
	}
	std::string tree = "";
	for (int n : numbers)
	{
		tree += std::to_string(n + 1) + '-';
	}
	tree += std::to_string(current + 1);
	data.small_font.draw_string(target, tree, target.w, 0, target.w, Horizontal_Align::RIGHT);
	target.draw_rectangle(0, 7 + (current - page_begin) * 10, target.w - 6, 10);
	draw_scroll(target);
	data.medium_bold_font.draw_string(target, "OK", target.w / 2, target.h, target.w, Horizontal_Align::CENTER, Vertical_Align::BOTTOM);

#ifdef _DEBUG
	frames++;
	if (frametime.getElapsedTime() >= next_fps)
	{
		fps = frames;
		frames = 0;
		next_fps += sf::seconds(1.0f);
	}
	data.small_font.draw_string(target, std::to_string(fps), target.w, target.h, target.w, Horizontal_Align::RIGHT, Vertical_Align::BOTTOM);
#endif
}


void Menu::draw_scroll(Bitmap& target)
{
	int offset_pixels;
	if (items.size() <= 1) offset_pixels = 0;
	else offset_pixels = current * 23 / (items.size() - 1);
	target.draw_rectangle(target.w - 3, 7, 1, offset_pixels);
	target.draw_rectangle(target.w - 3, 7 + offset_pixels, 2, 1);
	target.draw_rectangle(target.w - 1, 8 + offset_pixels, 1, 5);
	target.draw_rectangle(target.w - 3, 13 + offset_pixels, 2, 1);
	target.draw_rectangle(target.w - 3, 14 + offset_pixels, 1, 23 - offset_pixels);
}


void Menu::change_current_item(int new_position)
{
	current = new_position;
	if (current < page_begin) page_begin = current;
	if (current > page_begin + 2) page_begin = current - 2;
}