#pragma once
#include "Big_Text.h"
#include <SFML\Graphics.hpp>
class Welcome :
	public Big_Text
{
private:
	sf::Clock timer;

	void tick();
	void confirmed() {}
	void returned() {}

public:
	Welcome();
	~Welcome();
};

