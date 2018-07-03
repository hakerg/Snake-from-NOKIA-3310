#pragma once
#include <SFML\Graphics.hpp>
#include <bassmidi.h>
#include <array>
#include <memory>
#include "Bitmap.h"
#include "BitmapFont.h"
#include "Data_Container.h"

enum class Nokia_Key {
	UNKNOWN = -1,
	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,
	STAR = 10,
	HASH,
	CONFIRM,
	BACK,
	UP,
	DOWN,
	KEY_COUNT
};


class Scene
{
private:
	std::vector <BASS_MIDI_EVENT> events;
	std::array<std::unique_ptr<sf::Clock>, (int)Nokia_Key::KEY_COUNT> key_clocks;

protected:
	void tone(int midi_note, sf::Time duration);
	void silence(sf::Time duration);

public:
	bool exit = false;
	bool play_sound_on_click = true;
	bool vibrate = false;

	Scene();
	~Scene();
	void keyPressed(Nokia_Key key);
	void keyReleased(Nokia_Key key);
	void check_key_clocks();

	virtual void confirmed() {}
	virtual void returned();
	virtual void number_pressed(unsigned int number) {}
	virtual void star_pressed() {}
	virtual void hash_pressed() {}
	virtual void arrow_pressed(sf::Vector2i direction) {}

	virtual void confirmed_held() {}
	virtual void returned_held() {}
	virtual void number_held(unsigned int number) {}
	virtual void star_held() {}
	virtual void hash_held() {}
	virtual void arrow_held(sf::Vector2i direction) {}

	virtual void tick() {}
	virtual void draw(Bitmap& target);
	std::vector <BASS_MIDI_EVENT> get_midi_events();
	void mute();
	void play_note(Note n);
	void play_notes(std::vector<Note>& notes);
};