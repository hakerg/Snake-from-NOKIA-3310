#pragma once
#include "Menu.h"
class Song_Options :
	public Menu
{
private:
	int song_id;
	void item_selected(int id);

public:
	Song_Options(int _song_id);
	~Song_Options();
};

