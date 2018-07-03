#include "Big_Text.h"
#include "Scene_Manager.h"
#include "Data_Container.h"



Big_Text::Big_Text(std::string visible_text) : text(visible_text)
{
}


Big_Text::~Big_Text()
{
}


void Big_Text::draw(Bitmap& target)
{
	data.big_font.draw_string(target, text, 0, 3);
}


void Big_Text::confirmed()
{
	Scene_Manager::go_to_previous_scene();
}