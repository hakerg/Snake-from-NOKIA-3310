#pragma once
#include "Scene.h"
#include <SFML\Graphics.hpp>
class Snake_Gameplay :
	public Scene
{
private:
	const sf::Time delay;
	sf::Time next_tick;
	sf::Clock clock;
	std::vector <sf::Vector2i> snake;
	sf::Vector2i food, direction, real_direction;

	void number_pressed(unsigned int number);
	void arrow_pressed(sf::Vector2i arrow);
	void tick();
	void draw(Bitmap& target);
	bool collides_with_snake(sf::Vector2i pos);
	void draw_snake(Bitmap& target);
	void draw_food(Bitmap& target);
	sf::Vector2i snake_to_screen(sf::Vector2i snake_pos);
	void game_over();

public:
	Snake_Gameplay();
	~Snake_Gameplay();
};

