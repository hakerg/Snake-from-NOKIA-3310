#include "TTT_Menu.h"
#include "Scene_Manager.h"
#include "TTT_New_Select.h"
#include "TTT_Gameplay.h"



TTT_Menu::TTT_Menu() : Menu({ 0 }, { "Nowa gra", "Demo" })
{
}


TTT_Menu::~TTT_Menu()
{
}


void TTT_Menu::item_selected(int id)
{
	switch (id)
	{
	case 0:
		Scene_Manager::go_to_scene(new TTT_New_Select);
		break;
	case 1:
		Scene_Manager::go_to_scene(new TTT_Gameplay(false, false));
		break;
	}
}