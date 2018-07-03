#include "Snake_Menu.h"
#include "Scene_Manager.h"
#include "Snake_Gameplay.h"
#include "Spectrum.h"
#include "Big_Text.h"
#include "Data_Container.h"



Snake_Menu::Snake_Menu() : Menu({ 1 }, { "Nowa gra", "Poziom", "Rekord" })
{
}


Snake_Menu::~Snake_Menu()
{
}


void Snake_Menu::item_selected(int id)
{
	switch (id)
	{
	case 0:
		Scene_Manager::go_to_scene(new Snake_Gameplay);
		break;
	case 1:
		Scene_Manager::go_to_scene(new Spectrum(data.snake_level, "Poziom:"));
		break;
	case 2:
		Scene_Manager::go_to_scene(new Big_Text("Najlepszy\nWynik:\n" + std::to_string(data.snake_top)));
		break;
	}
}