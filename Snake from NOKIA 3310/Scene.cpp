#include "Scene.h"
#include "Bitmap.h"
#include "Scene_Manager.h"
#include <typeinfo>
#include <iostream>



Scene::Scene()
{
	exit = false;
}


Scene::~Scene()
{
}


void Scene::draw(Bitmap& target)
{
	data.medium_font.draw_string(target, std::string("Scene:\n") + (typeid(*this).name() + 6), 0, 0);
}


void Scene::tone(int midi_note, sf::Time duration)
{
	BASS_MIDI_EVENT event;
	memset(&event, 0, sizeof(event));
	event.event = MIDI_EVENT_NOTE;
	event.param = MAKEWORD(midi_note, 127);
	if (events.size() > 0) event.pos = events.back().pos;
	events.push_back(event);
	event.param = MAKEWORD(midi_note, 0);
	event.pos += DWORD(duration.asSeconds() * 44100 * 4);
	events.push_back(event);
}


void Scene::silence(sf::Time duration)
{
	BASS_MIDI_EVENT event;
	memset(&event, 0, sizeof(event));
	event.event = MIDI_EVENT_NOTE;
	event.param = MAKEWORD(0, 0);
	event.pos = DWORD(duration.asSeconds() * 44100 * 4);
	if (events.size() > 0) event.pos += events.back().pos;
	events.push_back(event);
}


void Scene::mute()
{
	events.clear();
	silence(sf::seconds(0));
}


std::vector <BASS_MIDI_EVENT> Scene::get_midi_events()
{
	std::vector <BASS_MIDI_EVENT> ret = events;
	events.clear();
	return ret;
}


void Scene::keyPressed(Nokia_Key key)
{
	key_clocks[(int)key] = std::make_unique<sf::Clock>();
	if (key >= Nokia_Key::NUM0 && key <= Nokia_Key::NUM9) number_pressed((int)key);
	else switch (key)
	{
	case Nokia_Key::CONFIRM:
		confirmed();
		break;
	case Nokia_Key::BACK:
		returned();
		break;
	case Nokia_Key::UP:
		arrow_pressed(sf::Vector2i(0, -1));
		break;
	case Nokia_Key::DOWN:
		arrow_pressed(sf::Vector2i(0, 1));
		break;
	case Nokia_Key::STAR:
		star_pressed();
		break;
	case Nokia_Key::HASH:
		hash_pressed();
		break;
	}
}


void Scene::keyReleased(Nokia_Key key)
{
	key_clocks[(int)key].reset(nullptr);
}


void Scene::returned()
{
	Scene_Manager::go_to_previous_scene();
}


void Scene::check_key_clocks()
{
	for (unsigned int n = 0; n < key_clocks.size(); n++)
	{
		if (key_clocks[n].get() == nullptr) continue;
		if (key_clocks[n]->getElapsedTime() >= sf::seconds(1.0f))
		{
			key_clocks[n].reset(nullptr);
			if (n >= 0 && n <= 9) number_held(n);
			else switch (Nokia_Key(n))
			{
			case Nokia_Key::CONFIRM:
				confirmed_held();
				break;
			case Nokia_Key::BACK:
				returned_held();
				break;
			case Nokia_Key::UP:
				arrow_held(sf::Vector2i(0, -1));
				break;
			case Nokia_Key::DOWN:
				arrow_held(sf::Vector2i(0, 1));
				break;
			case Nokia_Key::STAR:
				star_held();
				break;
			case Nokia_Key::HASH:
				hash_held();
				break;
			}
		}
	}
}


void Scene::play_note(Note n)
{
	sf::Time length = sf::seconds(60 * (n.dot ? 6.0f : 4.0f) / n.length / data.song.bpm);
	if (n.pause) silence(length);
	else
	{
		int key;
		switch (n.height)
		{
		case 'c': key = 0; break;
		case 'd': key = 2; break;
		case 'e': key = 4; break;
		case 'f': key = 5; break;
		case 'g': key = 7; break;
		case 'a': key = 9; break;
		case 'b': key = 11; break;
		}
		key += 60 + n.octave * 12 + int(n.hash);
		tone(key, length);
	}
}


void Scene::play_notes(std::vector<Note>& notes)
{
	for (auto& n : notes) play_note(n);
}