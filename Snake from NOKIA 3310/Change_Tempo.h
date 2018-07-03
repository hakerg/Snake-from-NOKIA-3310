#pragma once
#include "Menu.h"
class Change_Tempo :
	public Menu
{
private:
	void item_selected(int id);

public:
	Change_Tempo();
	~Change_Tempo();
};

