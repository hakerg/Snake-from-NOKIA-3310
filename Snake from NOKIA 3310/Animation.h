#pragma once
#include "Bitmap.h"
class Animation
{
private:
	virtual void draw_frame(Bitmap& target) = 0;

public:
	int x, y, frame = 0, delay, delay_count = 0, frames, loop, finished = false;

	Animation(int pos_x, int pos_y, int draws_per_frame, int frames_count = 0, bool looped = false);
	~Animation();
	void draw(Bitmap& target);
};

