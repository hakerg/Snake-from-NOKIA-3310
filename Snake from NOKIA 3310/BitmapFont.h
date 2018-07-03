#pragma once
#include "Bitmap.h"
#include <string>
#include <vector>
enum class Horizontal_Align { LEFT, RIGHT, CENTER };
enum class Vertical_Align { TOP, BOTTOM, MIDDLE };
class BitmapFont
{
private:
	int height;
	Bitmap* letter[256];

public:
	BitmapFont();
	~BitmapFont();
	void load_from_txt(std::string filename, int init_char_code);
	void draw_string(Bitmap& target, std::vector <std::string> string, int x, int y, int max_width, Horizontal_Align h_align = Horizontal_Align::LEFT, Vertical_Align v_align = Vertical_Align::TOP);
	void draw_string(Bitmap& target, std::string string, int x, int y, int max_width, Horizontal_Align h_align = Horizontal_Align::LEFT, Vertical_Align v_align = Vertical_Align::TOP)
	{
		draw_string(target, split_string(string), x, y, max_width, h_align, v_align);
	}
	void draw_string(Bitmap& target, std::vector <std::string> string, int x, int y, Vertical_Align v_align = Vertical_Align::TOP)
	{
		draw_string(target, string, x, y, target.w - x, Horizontal_Align::LEFT, v_align);
	}
	void draw_string(Bitmap& target, std::string string, int x, int y, Vertical_Align v_align = Vertical_Align::TOP)
	{
		draw_string(target, string, x, y, target.w - x, Horizontal_Align::LEFT, v_align);
	}
	int get_height() { return height; }
	std::vector <std::string> fit_string(std::string string, int max_width);
	std::vector <std::string> fit_string(std::vector <std::string> string, int max_width);
	std::vector <std::string> split_string(std::string string);
	std::string merge_string(std::vector <std::string> string);
	int get_width(std::string string);
	int get_width(std::vector <std::string> string);
	int get_height(std::vector <std::string> string);
};
