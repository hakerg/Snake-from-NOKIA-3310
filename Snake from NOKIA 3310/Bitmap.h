#pragma once
class Bitmap
{
private:
	bool* const data;

public:
	const int w, h;

	Bitmap(int width, int height);
	Bitmap(int width, int height, bool data[]);
	~Bitmap();
	void clear();
	void draw_border();
	void draw_border(int x, int y, int width, int height);
	void draw_rectangle(int x, int y, int w, int h);
	void draw_rectangle(int x, int y, int w, int h, bool color);
	void blit_to(int x, int y, Bitmap& target);
	bool& at(int x, int y) { return data[x + y * w]; }
	void negate(int x, int y);
};
