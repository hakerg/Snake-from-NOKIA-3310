#pragma once
#include "Animation.h"
class Big_Cross :
	public Animation
{
private:
	void draw_frame(Bitmap& target);

public:
	Big_Cross(int board_x, int board_y);
	~Big_Cross();
};

