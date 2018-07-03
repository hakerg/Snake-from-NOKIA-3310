#include "Composer.h"
#include "Data_Container.h"
#include "Scene_Manager.h"
#include "Composer_Menu.h"



Composer::Composer()
{
}


Composer::~Composer()
{
}


void Composer::tick()
{

}


void Composer::draw_note_symbols(Bitmap& target)
{
	target.negate(0, 4);
	target.negate(1, 3);
	target.negate(1, 5);
	target.negate(2, 3);
	target.negate(2, 5);
	target.negate(3, 0);
	target.negate(3, 1);
	target.negate(3, 2);
	target.negate(3, 3);
	target.negate(3, 4);

	target.negate(5, 4);
	target.negate(6, 3);
	target.negate(6, 4);
	target.negate(6, 5);
	target.negate(7, 3);
	target.negate(7, 4);
	target.negate(7, 5);
	target.negate(8, 0);
	target.negate(8, 1);
	target.negate(8, 2);
	target.negate(8, 3);
	target.negate(8, 4);

	target.negate(10, 4);
	target.negate(11, 3);
	target.negate(11, 4);
	target.negate(11, 5);
	target.negate(12, 3);
	target.negate(12, 4);
	target.negate(12, 5);
	target.negate(13, 0);
	target.negate(13, 1);
	target.negate(13, 2);
	target.negate(13, 3);
	target.negate(13, 4);
	target.negate(14, 0);
	target.negate(15, 1);
}


void Composer::draw(Bitmap& target)
{
	draw_note_symbols(target);
	data.medium_bold_font.draw_string(target, "Opcje", target.w / 2, target.h, target.w, Horizontal_Align::CENTER, Vertical_Align::BOTTOM);
	data.small_font.draw_string(target, std::to_string(notes.size()), target.w, 0, target.w, Horizontal_Align::RIGHT);

	std::string text = "";
	for (auto& n : notes) text += note_to_string(n) + " ";
	auto fitted = data.medium_bold_font.fit_string(text, target.w);
	if (fitted.size() > 3)
	{
		fitted.erase(fitted.begin(), fitted.end() - 3);
	}
	data.medium_bold_font.draw_string(target, fitted, 0, 10);
}


std::string Composer::note_to_string(Note n)
{
	std::string ret = "";
	ret += std::to_string(n.length);
	if (n.dot) ret += '.';
	if (n.pause) ret += '-';
	else
	{
		ret += n.height;
		if (n.hash) ret += '#';
		ret += std::to_string(n.octave);
	}
	return ret;
}


void Composer::number_pressed(unsigned int number)
{
	switch (number)
	{
	case 1:
		notes.emplace_back(current_length, current_octave, 'c');
		play_note(notes.back());
		break;
	case 2:
		notes.emplace_back(current_length, current_octave, 'd');
		play_note(notes.back());
		break;
	case 3:
		notes.emplace_back(current_length, current_octave, 'e');
		play_note(notes.back());
		break;
	case 4:
		notes.emplace_back(current_length, current_octave, 'f');
		play_note(notes.back());
		break;
	case 5:
		notes.emplace_back(current_length, current_octave, 'g');
		play_note(notes.back());
		break;
	case 6:
		notes.emplace_back(current_length, current_octave, 'a');
		play_note(notes.back());
		break;
	case 7:
		notes.emplace_back(current_length, current_octave, 'b');
		play_note(notes.back());
		break;
	case 8:
		if (!notes.empty())
		{
			if (current_length < 32) current_length *= 2;
			else current_length = 1;
			notes.back().length = current_length;
			play_note(notes.back());
		}
		break;
	case 9:
		if (!notes.empty())
		{
			if (current_length > 1) current_length /= 2;
			else current_length = 32;
			notes.back().length = current_length;
			play_note(notes.back());
		}
		break;
	case 0:
		notes.emplace_back(current_length);
		break;
	}
}


void Composer::number_held(unsigned int number)
{
	if (number >= 1 && number <= 7) notes.back().dot = true;
	play_note(notes.back());
}


void Composer::returned()
{
	if (notes.empty())
	{
		Scene_Manager::go_to_previous_scene();
		Scene_Manager::current_scene()->mute();
	}
	else notes.pop_back();
}


void Composer::returned_held()
{
	notes.clear();
}


void Composer::confirmed()
{
	Scene_Manager::go_to_scene(new Composer_Menu);
	Scene_Manager::current_scene()->mute();
}


void Composer::hash_pressed()
{
	if (!notes.empty())
	{
		auto& note = notes.back();
		if (!note.pause && note.height != 'e' && note.height != 'b')
		{
			note.hash = !note.hash;
			play_note(note);
		}
	}
}


void Composer::star_pressed()
{
	if (!notes.empty())
	{
		auto& note = notes.back();
		current_octave = (current_octave) % 3 + 1;
		note.octave = current_octave;
		play_note(note);
	}
}