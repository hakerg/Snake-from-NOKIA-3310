#include "Song_Options.h"
#include "Scene_Manager.h"
#include "Data_Container.h"
#include "My_Songs.h"
#include "Big_Text.h"



Song_Options::Song_Options(int _song_id) : song_id(_song_id), Menu({ 2, 3, _song_id }, { "Graj", "Komponuj", "Skasuj" })
{
}


Song_Options::~Song_Options()
{
}


void Song_Options::item_selected(int id)
{
	switch (id)
	{
	case 0:
		Scene_Manager::go_to_previous_scene();
		Scene_Manager::current_scene()->play_notes(data.songs[song_id].notes);
		break;
	case 1:
		data.song = data.songs[song_id];
		Scene_Manager::go_to_previous_scene();
		Scene_Manager::go_to_previous_scene();
		Scene_Manager::go_to_previous_scene();
		break;
	case 2:
		data.songs.erase(data.songs.begin() + song_id);
		Scene_Manager::go_to_previous_scene();
		Scene_Manager::go_to_previous_scene();
		if (data.songs.empty())
		{
			Scene_Manager::go_to_scene(new Big_Text("Brak Melodii"));
		}
		else
		{
			Scene_Manager::go_to_scene(new My_Songs);
		}
	}
}