#pragma once
#include "Scene.h"
#include <vector>
#include "Data_Container.h"

class Composer :
	public Scene
{
private:
	static const std::string notes_strings[];
	int current_length = 4, current_octave = 1;
	std::vector<Note>& notes = data.song.notes;

	void tick();
	void draw(Bitmap& target);
	void draw_note_symbols(Bitmap& target);
	std::string note_to_string(Note e);
	void number_pressed(unsigned int number);
	void number_held(unsigned int number);
	void returned();
	void returned_held();
	void confirmed();
	void hash_pressed();
	void star_pressed();

public:
	Composer();
	~Composer();
};

