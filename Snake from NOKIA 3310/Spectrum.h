#pragma once
#include "Scene.h"
class Spectrum :
	public Scene
{
private:
	int& original;
	int current;
	std::string label;

	void confirmed();
	void arrow_pressed(sf::Vector2i direction);
	void number_pressed(unsigned int number);
	void draw(Bitmap& target);

public:
	Spectrum(int& value, std::string label_text);
	~Spectrum();
};

