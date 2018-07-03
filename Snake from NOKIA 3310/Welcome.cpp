#include "Welcome.h"
#include "Scene_Manager.h"
#include "Game_List.h"



Welcome::Welcome() : Big_Text("Symulator\nNOKIA 3310")
{
	play_sound_on_click = false;
}


Welcome::~Welcome()
{
}


void Welcome::tick()
{
	if (timer.getElapsedTime() >= sf::seconds(3)) Scene_Manager::change_scene(new Game_List);
}