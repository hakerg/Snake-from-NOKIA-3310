#pragma once
#include "Scene.h"
class Big_Text :
	public Scene
{
private:
	const std::string text;

	void draw(Bitmap& target);
	virtual void confirmed();

public:
	Big_Text(std::string visible_text);
	~Big_Text();
};

