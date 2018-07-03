#include "BitmapFont.h"
#include <fstream>
#include <vector>
#include <iostream>



BitmapFont::BitmapFont()
{
}


BitmapFont::~BitmapFont()
{
	for (int n = 0; n < 256; n++) delete letter[n];
}


void BitmapFont::load_from_txt(std::string filename, int init_char_code)
{
	std::fstream file(filename, std::fstream::in);
	std::string s;
	do std::getline(file, s);
	while (s[0] == '#');
	for (int i = init_char_code; i < 256; i++)
	{
		std::vector <std::string> letter_data;
		letter_data.clear();
		while (true)
		{
			std::getline(file, s);
			if (s.size() == 0) break;
			letter_data.push_back(s);
		}
		if (letter_data.size() == 0) break;

		Bitmap*& l = letter[i];
		l = new Bitmap(letter_data[0].size(), letter_data.size());
		height = l->h;
		for (int x = 0; x < l->w; x++)
			for (int y = 0; y < l->h; y++)
			{
				l->at(x, y) = (letter_data[y][x] == '0');
			}
	}
	file.close();
}


void BitmapFont::draw_string(Bitmap& target, std::vector <std::string> string, int x, int y, int max_width, Horizontal_Align h_align, Vertical_Align v_align)
{
	std::vector <std::string> fitted = fit_string(string, max_width);

	int h = get_height(fitted);
	if (v_align == Vertical_Align::BOTTOM) y -= h;
	else if (v_align == Vertical_Align::MIDDLE) y -= h / 2;

	for (std::string s : fitted)
	{
		int w = get_width(s);
		int tx = x;
		if (h_align == Horizontal_Align::RIGHT) tx -= w;
		else if (h_align == Horizontal_Align::CENTER) tx -= w / 2;

		for (char& c : s)
		{
			letter[c]->blit_to(tx, y, target);
			tx += letter[c]->w + 1;
		}
		y += height + 2;
	}
}


std::vector <std::string> BitmapFont::fit_string(std::string string, int max_width)
{
	std::vector <std::string> ret(1, string);
	int w = -1;
	for (int i = 0; i < (signed)ret.back().size(); i++)
	{
		w += 1 + letter[ret.back()[i]]->w;
		if (w > max_width)
		{
			auto pos = ret.back().find_last_of(' ', i);
			std::string new_line;
			if (pos == std::string::npos)
			{
				new_line = ret.back().substr(i);
				ret.back() = ret.back().substr(0, i);
			}
			else
			{
				new_line = ret.back().substr(pos + 1);
				ret.back() = ret.back().substr(0, pos);
			}
			ret.push_back(new_line);
			i = -1;
			w = -1;
		}
	}
	if (ret.back().empty()) ret.pop_back();
	return ret;
}


std::vector <std::string> BitmapFont::fit_string(std::vector <std::string> string, int max_width)
{
	std::vector <std::string> ret;
	ret.clear();
	for (std::string& s : string)
	{
		auto v = fit_string(s, max_width);
		ret.insert(ret.end(), v.begin(), v.end());
	}
	return ret;
}


std::vector <std::string> BitmapFont::split_string(std::string string)
{
	std::vector <std::string> ret(1, string);
	auto pos = ret.back().find_first_of('\n');
	while (pos != std::string::npos)
	{
		std::string new_line = ret.back().substr(pos + 1);
		ret.back() = ret.back().substr(0, pos);
		ret.push_back(new_line);
		pos = ret.back().find_first_of('\n');
	}
	return ret;
}


std::string BitmapFont::merge_string(std::vector <std::string> string)
{
	std::string ret = "";
	for (auto& s : string)
	{
		ret += s + '\n';
	}
	if (!ret.empty()) ret.pop_back();
	return ret;
}


int BitmapFont::get_width(std::string string)
{
	int w = -1;
	for (char& c : string)
	{
		w += letter[c]->w + 1;
	}
	return w;
}


int BitmapFont::get_width(std::vector <std::string> string)
{
	int max = 0;
	for (std::string s : string)
	{
		int t = get_width(s);
		if (t > max) max = t;
	}
	return max;
}


int BitmapFont::get_height(std::vector <std::string> string)
{
	return string.size() * (height + 2) - 2;
}