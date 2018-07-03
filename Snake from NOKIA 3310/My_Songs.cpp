#include "My_Songs.h"
#include "Data_Container.h"
#include "Scene_Manager.h"
#include "Song_Options.h"



My_Songs::My_Songs() : Menu({ 2, 3 }, {})
{
	for (Composer_Song& song : data.songs) items.push_back(song.name);
}


My_Songs::~My_Songs()
{
}


void My_Songs::item_selected(int id)
{
	Scene_Manager::go_to_scene(new Song_Options(id));
	Scene_Manager::current_scene()->mute();
}


void My_Songs::returned()
{
	Scene_Manager::go_to_previous_scene();
	Scene_Manager::current_scene()->mute();
}