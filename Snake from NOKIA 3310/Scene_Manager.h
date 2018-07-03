#pragma once
#include "Scene.h"
#include <vector>
#include <memory>
class Scene_Manager
{
private:
	static std::vector <std::shared_ptr <Scene>> scenes;

public:
	static std::shared_ptr <Scene> current_scene();
	static void go_to_scene(Scene* scene);
	static void change_scene(Scene* scene);
	static void go_to_previous_scene();
};

