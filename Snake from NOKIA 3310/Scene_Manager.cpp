#include "Scene_Manager.h"
#include <iostream>



std::vector <std::shared_ptr <Scene>> Scene_Manager::scenes;


std::shared_ptr <Scene> Scene_Manager::current_scene()
{
	if (!scenes.size()) scenes.push_back(std::make_shared <Scene>());
	return scenes.back();
}


void Scene_Manager::go_to_scene(Scene* scene)
{
	scenes.push_back(std::shared_ptr <Scene>(scene));
}


void Scene_Manager::change_scene(Scene* scene)
{
	if (!scenes.size()) go_to_scene(scene);
	else scenes.back() = std::shared_ptr <Scene>(scene);
}


void Scene_Manager::go_to_previous_scene()
{
	if (scenes.size() > 1) scenes.pop_back();
}