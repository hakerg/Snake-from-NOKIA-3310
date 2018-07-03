#include "TTT_OX_Select.h"
#include "Scene_Manager.h"
#include "TTT_Gameplay.h"



TTT_OX_Select::TTT_OX_Select() :
	Menu({ 0, 0, 1 }, { "Wybierz O", "Wybierz X" })
{
}


TTT_OX_Select::~TTT_OX_Select()
{
}


void TTT_OX_Select::item_selected(int id)
{
	switch (id)
	{
	case 0:
		Scene_Manager::go_to_scene(new TTT_Gameplay(true, false));
		break;
	case 1:
		Scene_Manager::go_to_scene(new TTT_Gameplay(false, true));
		break;
	}
}