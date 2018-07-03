#pragma once
#include <string>
#include <vector>

struct Note
{
	char height;
	int length, octave;
	bool hash, dot, pause;

	Note() {}
	Note(int _length, int _octave, char _height, bool _dot = false, bool _hash = false) :
		length(_length), octave(_octave), height(_height), dot(_dot), pause(false), hash(_hash) {}
	Note(int _length, bool _dot = false) :
		length(_length), octave(NULL), height(NULL), dot(_dot), pause(true), hash(NULL) {}
};


class Composer_Song
{
public:
	std::string name;
	int bpm = 120;
	std::vector<Note> notes;

	Composer_Song();
	~Composer_Song();
};

