#include "Data_Container.h"
#include "Constants.h"
#include <fstream>



Data_Container data(resources_path);


Data_Container::Data_Container(std::string resources_path)
{
	small_font.load_from_txt(resources_path + "nokia-menu.txt", '-');
	medium_font.load_from_txt(resources_path + "nokia-small.txt", ' ');
	medium_bold_font.load_from_txt(resources_path + "nokia-small-bold.txt", ' ');
	big_font.load_from_txt(resources_path + "nokia-big.txt", ' ');

	file.open("data.bin", std::fstream::in);
	if (file)
	{
		read(snake_level);
		read(snake_top);
		read(song);
		read_vector(songs);
	}
	file.close();
}


Data_Container::~Data_Container()
{
	file.open("data.bin", std::fstream::out);
	write(snake_level);
	write(snake_top);
	write(song);
	write_vector(songs);
	file.close();
}


template<class T> void Data_Container::write(T& ref)
{
	file.write((char*)&ref, sizeof(ref));
}


template<class T> void Data_Container::read(T& ref)
{
	file.read((char*)&ref, sizeof(ref));
}


template<> void Data_Container::write(std::string& ref)
{
	int size = ref.size();
	write(size);
	file.write(ref.c_str(), size);
}


template<> void Data_Container::read(std::string& ref)
{
	int size;
	read(size);
	ref.resize(size);
	file.read((char*)ref.c_str(), size);
}


template<> void Data_Container::write(Composer_Song& ref)
{
	write(ref.name);
	write(ref.bpm);
	write_vector(ref.notes);
}


template<> void Data_Container::read(Composer_Song& ref)
{
	read(ref.name);
	read(ref.bpm);
	read_vector(ref.notes);
}


template<class T> void Data_Container::write_vector(std::vector<T>& ref)
{
	int size = ref.size();
	write(size);
	for (T& i : ref) write(i);
}


template<class T> void Data_Container::read_vector(std::vector<T>& ref)
{
	int size;
	read(size);
	ref.resize(size);
	for (T& i : ref) read(i);
}