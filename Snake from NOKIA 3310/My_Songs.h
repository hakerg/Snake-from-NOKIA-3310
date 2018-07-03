#pragma once
#include "Menu.h"
class My_Songs :
	public Menu
{
private:
	void item_selected(int id);
	void returned();

public:
	My_Songs();
	~My_Songs();
};

