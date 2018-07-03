#include "Composer_Menu.h"
#include "Scene_Manager.h"
#include "Composer.h"
#include "Change_Tempo.h"
#include "My_Songs.h"
#include "Big_Text.h"



Composer_Menu::Composer_Menu() : Menu({ 2 }, { "Graj", "Tempo", "Zapisz", "Moje utwory", "Koniec" })
{
}


Composer_Menu::~Composer_Menu()
{
}


void Composer_Menu::item_selected(int id)
{
	switch (id)
	{
	case 0:
		Scene_Manager::go_to_previous_scene();
		((Composer*)Scene_Manager::current_scene().get())->play_notes(data.song.notes);
		break;
	case 1:
		Scene_Manager::go_to_scene(new Change_Tempo);
		break;
	case 2:
		data.song.name = "Melodia#" + std::to_string(rand() % 10) + std::to_string(rand() % 10) + std::to_string(rand() % 10);
		data.songs.push_back(data.song);
		Scene_Manager::go_to_previous_scene();
		break;
	case 3:
		if (data.songs.empty())
		{
			Scene_Manager::go_to_scene(new Big_Text("Pusta Lista"));
		}
		else
		{
			Scene_Manager::go_to_scene(new My_Songs);
		}
		break;
	case 4:
		Scene_Manager::go_to_previous_scene();
		Scene_Manager::go_to_previous_scene();
		break;
	}
}