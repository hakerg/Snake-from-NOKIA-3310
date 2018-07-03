#include "Game_List.h"
#include "Scene_Manager.h"
#include "TTT_Menu.h"
#include "Snake_Menu.h"
#include "Composer.h"



Game_List::Game_List() :
	Menu({}, { "Tic-Tac-Toe II", "Snake", "Kompozytor", "Koniec" })
{
}


Game_List::~Game_List()
{
}


void Game_List::item_selected(int id)
{
	switch (id)
	{
	case 0:
		Scene_Manager::go_to_scene(new TTT_Menu);
		break;
	case 1:
		Scene_Manager::go_to_scene(new Snake_Menu);
		break;
	case 2:
		Scene_Manager::go_to_scene(new Composer);
		break;
	case 3:
		exit = true;
		break;
	}
}


void Game_List::returned()
{
	exit = true;
}