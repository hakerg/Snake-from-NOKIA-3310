#include "Animation.h"



Animation::Animation(int pos_x, int pos_y, int draws_per_frame, int frames_count, bool looped)
{
	x = pos_x;
	y = pos_y;
	delay = draws_per_frame;
	frames = frames_count;
	loop = looped;
}


Animation::~Animation()
{
}


void Animation::draw(Bitmap& target)
{
	draw_frame(target);
	delay_count++;
	if (delay_count >= delay)
	{
		frame++;
		delay_count = 0;
		if (frame >= frames && frames != 0)
		{
			finished = true;
			if (loop) frame = 0;
			else frame = frames - 1;
		}
	}
}