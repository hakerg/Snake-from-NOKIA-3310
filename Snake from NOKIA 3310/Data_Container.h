#pragma once
#include <string>
#include <fstream>
#include "BitmapFont.h"
#include "Composer_Song.h"


class Data_Container
{
private:
	std::fstream file;

	template<class T> void write(T& ref);
	template<class T> void read(T& ref);
	template<> void write(std::string& ref);
	template<> void read(std::string& ref);
	template<> void write(Composer_Song& ref);
	template<> void read(Composer_Song& ref);
	template<class T> void write_vector(std::vector<T>& ref);
	template<class T> void read_vector(std::vector<T>& ref);

public:
	BitmapFont medium_font, medium_bold_font, small_font, big_font;

	int snake_level = 5, snake_top = 0;
	Composer_Song song;
	std::vector<Composer_Song> songs;

	Data_Container(std::string resources_path);
	~Data_Container();
};

extern Data_Container data;