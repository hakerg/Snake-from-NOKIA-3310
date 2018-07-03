#include "Spectrum.h"
#include "Scene_Manager.h"
#include "Data_Container.h"



Spectrum::Spectrum(int& value, std::string label_text) : original(value)
{
	current = value;
	label = label_text;
}


Spectrum::~Spectrum()
{
}


void Spectrum::confirmed()
{
	original = current;
	Scene_Manager::go_to_previous_scene();
}


void Spectrum::arrow_pressed(sf::Vector2i direction)
{
	current -= direction.y;
	if (current < 1) current = 1;
	if (current > 9) current = 9;
}


void Spectrum::draw(Bitmap& target)
{
	data.medium_bold_font.draw_string(target, label, 5, 0);
	data.medium_bold_font.draw_string(target, "OK", target.w / 2, target.h, target.w, Horizontal_Align::CENTER, Vertical_Align::BOTTOM);
	for (int n = 0; n < 9; n++)
	{
		target.draw_rectangle(6 + 8 * n, 39, 5, 1);
		target.draw_rectangle(10 + 8 * n, 33 - 2 * n, 1, 6 + 2 * n);
	}
	for (int n = 0; n < current; n++)
	{
		target.draw_rectangle(5 + 8 * n, 32 - 2 * n, 4, 6 + 2 * n);
	}
}


void Spectrum::number_pressed(unsigned int number)
{
	if (number != 0) current = number;
}