#pragma once
#include "Animation.h"
class Loading_Bar :
	public Animation
{
private:
	int w, h, f;

	void draw_frame(Bitmap& target);

public:
	Loading_Bar(int pos_x, int pos_y, int width, int height, int float_length);
	~Loading_Bar();
};

