#include "Snake_Gameplay.h"
#include "Scene_Manager.h"
#include "Big_Text.h"
#include "Data_Container.h"
#include <iostream>



Snake_Gameplay::Snake_Gameplay() : delay(sf::seconds(1.0f / data.snake_level))
{
	next_tick = delay;
	snake.clear();
	for (int i = 0; i < 9; i++)
	{
		snake.push_back(sf::Vector2i(i, 11));
	}
	food = sf::Vector2i(10, 5);
	direction = sf::Vector2i(1, 0);
	clock.restart();
}


Snake_Gameplay::~Snake_Gameplay()
{
}


void Snake_Gameplay::arrow_pressed(sf::Vector2i arrow)
{
	if (real_direction.x != -arrow.x || real_direction.y != -arrow.y)
	{
		direction = arrow;
	}
}


void Snake_Gameplay::tick()
{
	if (clock.getElapsedTime() >= next_tick)
	{
		next_tick += delay;

		real_direction = direction;
		sf::Vector2i new_head = snake.back() + real_direction;
		if (new_head.x < 0 || new_head.x >= 20 || new_head.y < 0 || new_head.y >= 12 || collides_with_snake(new_head))
		{
			game_over();
			return;
		}
		snake.push_back(new_head);
		if (new_head == food)
		{
			do food = sf::Vector2i(rand() % 20, rand() % 12);
			while (collides_with_snake(food));
		}
		else
		{
			snake.erase(snake.begin());
		}
	}
}


void Snake_Gameplay::draw(Bitmap& target)
{
	target.draw_border();
	draw_snake(target);
	draw_food(target);
}


bool Snake_Gameplay::collides_with_snake(sf::Vector2i pos)
{
	for (sf::Vector2i& v : snake) if (v == pos) return true;
	return false;
}


void Snake_Gameplay::draw_snake(Bitmap& target)
{
	auto pos = snake_to_screen(snake.front());
	target.draw_rectangle(pos.x, pos.y, 3, 3);
	for (unsigned int i = 1; i < snake.size(); i++)
	{
		auto pos = snake_to_screen(snake[i]);
		auto prevpos = snake_to_screen(snake[i - 1]);
		int w = 3, h = 3;
		if (prevpos.x != pos.x) w = 4;
		if (prevpos.y != pos.y) h = 4;
		if (prevpos.x < pos.x) pos.x -= 1;
		if (prevpos.y < pos.y) pos.y -= 1;
		target.draw_rectangle(pos.x, pos.y, w, h);
	}
}


void Snake_Gameplay::draw_food(Bitmap& target)
{
	auto pos = snake_to_screen(food);
	target.negate(pos.x + 1, pos.y);
	target.negate(pos.x, pos.y + 1);
	target.negate(pos.x + 2, pos.y + 1);
	target.negate(pos.x + 1, pos.y + 2);
}


sf::Vector2i Snake_Gameplay::snake_to_screen(sf::Vector2i snake_pos)
{
	return sf::Vector2i(snake_pos.x * 4 + 2, snake_pos.y * 4 + 2);
}


void Snake_Gameplay::game_over()
{
	int score = int((snake.size() - 9) / delay.asSeconds());
	if (score > data.snake_top) data.snake_top = score;
	Scene_Manager::change_scene(new Big_Text("Koniec Gry.\nWynik:\n" + std::to_string(score)));
}



void Snake_Gameplay::number_pressed(unsigned int number)
{
	switch (number)
	{
	case 2:
		arrow_pressed(sf::Vector2i(0, -1));
		break;
	case 4:
		arrow_pressed(sf::Vector2i(-1, 0));
		break;
	case 6:
		arrow_pressed(sf::Vector2i(1, 0));
		break;
	case 8:
		arrow_pressed(sf::Vector2i(0, 1));
		break;
	}
}