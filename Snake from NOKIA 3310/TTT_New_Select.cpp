#include "TTT_New_Select.h"
#include "Scene_Manager.h"
#include "TTT_Gameplay.h"
#include "TTT_OX_Select.h"



TTT_New_Select::TTT_New_Select() :
	Menu({ 0, 0 }, { "Gracz & Gracz", "Gracz & AI" })
{
}


TTT_New_Select::~TTT_New_Select()
{
}


void TTT_New_Select::item_selected(int id)
{
	switch (id)
	{
	case 0:
		Scene_Manager::go_to_scene(new TTT_Gameplay(true, true));
		break;
	case 1:
		Scene_Manager::go_to_scene(new TTT_OX_Select);
		break;
	}
}