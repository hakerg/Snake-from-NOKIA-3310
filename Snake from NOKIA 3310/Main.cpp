#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <bassmidi.h>
#include "Bitmap.h"
#include "Welcome.h"
#include "Constants.h"
#include "Scene_Manager.h"
#include "Data_Container.h"

const float screen_width = RES_X * PIXEL_WIDTH + PIXEL_SPACE + SHADOW_OFFSET;
const float screen_height = RES_Y * PIXEL_HEIGHT + PIXEL_SPACE + SHADOW_OFFSET;
const sf::FloatRect nokia_screen(80, 265, 267, 196);
bool fullscreen = false;
sf::Vector2f nokia_screen_scaling, nokia_scaling, nokia_screen_size, nokia_size;
sf::Vector2f f_nokia_screen_scaling, f_nokia_scaling;
sf::RectangleShape pixel(sf::Vector2f(PIXEL_WIDTH - PIXEL_SPACE, PIXEL_HEIGHT - PIXEL_SPACE));
sf::RectangleShape f_pixel(sf::Vector2f(PIXEL_WIDTH - PIXEL_SPACE, PIXEL_HEIGHT - PIXEL_SPACE));
sf::Texture nokia_texture, fullscreen_texture, blat_texture;
sf::RenderTexture texture, texture2, clearance_texture, whole_nokia;// , blurred_nokia;
sf::RenderTexture f_texture, f_texture2, f_clearance_texture;
sf::Sprite sprite, nokia_sprite, whole_nokia_sprite, /*blurred_nokia_sprite, */fullscreen_sprite, blat_sprite, shadow_sprite;
sf::Sprite f_nokia_sprite;
sf::Shader blur;
sf::ContextSettings context_settings;
std::array<sf::RectangleShape, 16> key_overlays;


std::array<const sf::IntRect, 16> key_regions = {
	sf::IntRect(165, 867, 86, 50),
	sf::IntRect(48, 640, 78, 52),
	sf::IntRect(165, 657, 88, 49),
	sf::IntRect(288, 640, 81, 52),
	sf::IntRect(52, 708, 80, 52),
	sf::IntRect(164, 728, 88, 49),
	sf::IntRect(283, 709, 83, 51),
	sf::IntRect(55, 776, 82, 55),
	sf::IntRect(165, 797, 86, 49),
	sf::IntRect(280, 778, 80, 53),
	sf::IntRect(61, 847, 80, 52),
	sf::IntRect(276, 848, 79, 52),
	sf::IntRect(135, 511, 146, 47),
	sf::IntRect(62, 530, 70, 74),
	sf::IntRect(305, 532, 47, 58),
	sf::IntRect(230, 564, 56, 72)
};


void window_resized(float new_x, float new_y)
{
	nokia_scaling.y = new_y / nokia_texture.getSize().y;
	nokia_scaling.x = nokia_scaling.y;
	nokia_screen_size = sf::Vector2f(nokia_screen.width * nokia_scaling.x, nokia_screen.height * nokia_scaling.y);
	nokia_screen_scaling = sf::Vector2f(nokia_screen_size.x / screen_width, nokia_screen_size.y / screen_height);
	nokia_size = sf::Vector2f(nokia_texture.getSize().x * nokia_scaling.x, nokia_texture.getSize().y * nokia_scaling.y);
	f_nokia_scaling.x = new_x / nokia_screen.width;
	f_nokia_scaling.y = new_y / nokia_screen.height;
	f_nokia_screen_scaling = sf::Vector2f(nokia_screen.width * f_nokia_scaling.x / screen_width, nokia_screen.height * f_nokia_scaling.y / screen_height);

	pixel.setScale(nokia_screen_scaling);
	f_pixel.setScale(f_nokia_screen_scaling);

	texture.create((unsigned)ceil(nokia_screen_size.x) + 1, (unsigned)ceil(nokia_screen_size.y) + 1, context_settings);
	texture2.create(texture.getSize().x, texture.getSize().y);
	clearance_texture.create(texture.getSize().x, texture.getSize().y, context_settings);
	whole_nokia.create((unsigned)ceil(nokia_size.x), (unsigned)ceil(nokia_size.y), context_settings);
	//blurred_nokia.create(new_x, new_y);
	f_texture.create((unsigned)new_x, (unsigned)new_y, context_settings);
	f_texture2.create(f_texture.getSize().x, f_texture.getSize().y);
	f_clearance_texture.create(f_texture.getSize().x, f_texture.getSize().y, context_settings);

	sprite.setPosition(nokia_screen.left * nokia_scaling.x, nokia_screen.top * nokia_scaling.y);
	nokia_sprite.setScale(nokia_scaling.x, nokia_scaling.y);
	whole_nokia_sprite.setPosition((new_x - nokia_size.x) * 0.5f, 0);
	float blur_scale_x = new_x / nokia_size.x;
	//blurred_nokia_sprite.setScale(blur_scale_x, blur_scale_x);
	//blurred_nokia_sprite.setPosition(0, (new_y - blurred_nokia.getSize().y * blurred_nokia_sprite.getScale().y) * 0.5f);
	f_nokia_sprite.setTexture(nokia_texture);
	f_nokia_sprite.setPosition(sf::Vector2f(-nokia_screen.left * f_nokia_scaling.x, -nokia_screen.top * f_nokia_scaling.y));
	f_nokia_sprite.setScale(f_nokia_scaling);
	sf::Vector2f blat_scale(new_x / blat_texture.getSize().x, new_y / blat_texture.getSize().y);
	if (blat_scale.x > blat_scale.y) blat_scale.y = blat_scale.x;
	else blat_scale.x = blat_scale.y;
	blat_sprite.setScale(blat_scale);
	blat_sprite.setOrigin(blat_texture.getSize().x * 0.5f, blat_texture.getSize().y * 0.5f);
	blat_sprite.setPosition(new_x * 0.5f, new_y * 0.5f);
	shadow_sprite.setScale(1.05f, 1.05f);
	shadow_sprite.setPosition(whole_nokia_sprite.getPosition());
	shadow_sprite.setColor(sf::Color(0, 0, 0, 200));
	fullscreen_sprite.setPosition(sf::Vector2f(new_x, new_y));
	fullscreen_sprite.setScale(new_x * 0.0005f, new_y * 0.0005f);

	for (int y = 0; y < RES_Y; y++)
	{
		for (int x = 0; x < RES_X; x++)
		{
			pixel.setFillColor(sf::Color(0, 0, 0, 8));
			pixel.setPosition((x * PIXEL_WIDTH + PIXEL_SPACE + SHADOW_OFFSET) * nokia_screen_scaling.x, (y * PIXEL_HEIGHT + PIXEL_SPACE + SHADOW_OFFSET) * nokia_screen_scaling.y);
			clearance_texture.draw(pixel);
			pixel.setFillColor(sf::Color(0, 0, 0, 32));
			pixel.setPosition((x * PIXEL_WIDTH + PIXEL_SPACE) * nokia_screen_scaling.x, (y * PIXEL_HEIGHT + PIXEL_SPACE) * nokia_screen_scaling.y);
			clearance_texture.draw(pixel);

			f_pixel.setFillColor(sf::Color(0, 0, 0, 8));
			f_pixel.setPosition((x * PIXEL_WIDTH + PIXEL_SPACE + SHADOW_OFFSET) * f_nokia_screen_scaling.x, (y * PIXEL_HEIGHT + PIXEL_SPACE + SHADOW_OFFSET) * f_nokia_screen_scaling.y);
			f_clearance_texture.draw(f_pixel);
			f_pixel.setFillColor(sf::Color(0, 0, 0, 32));
			f_pixel.setPosition((x * PIXEL_WIDTH + PIXEL_SPACE) * f_nokia_screen_scaling.x, (y * PIXEL_HEIGHT + PIXEL_SPACE) * f_nokia_screen_scaling.y);
			f_clearance_texture.draw(f_pixel);
		}
	}
	clearance_texture.display();
	f_clearance_texture.display();

	for (unsigned int n = 0; n < key_overlays.size(); n++)
	{
		sf::RectangleShape& shape = key_overlays[n];
		shape.setScale(nokia_scaling.x, nokia_scaling.y);
		shape.setPosition(sf::Vector2f(key_regions[n].left * nokia_scaling.x, key_regions[n].top * nokia_scaling.y));
	}
}


Nokia_Key keyboard_to_nokia_key(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Numpad0) return Nokia_Key::NUM0;
	if (key == sf::Keyboard::Numpad1) return Nokia_Key::NUM7;
	if (key == sf::Keyboard::Numpad2) return Nokia_Key::NUM8;
	if (key == sf::Keyboard::Numpad3) return Nokia_Key::NUM9;
	if (key == sf::Keyboard::Numpad4) return Nokia_Key::NUM4;
	if (key == sf::Keyboard::Numpad5) return Nokia_Key::NUM5;
	if (key == sf::Keyboard::Numpad6) return Nokia_Key::NUM6;
	if (key == sf::Keyboard::Numpad7) return Nokia_Key::NUM1;
	if (key == sf::Keyboard::Numpad8) return Nokia_Key::NUM2;
	if (key == sf::Keyboard::Numpad9) return Nokia_Key::NUM3;
	if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) return Nokia_Key(key - sf::Keyboard::Num0);
	if (key == sf::Keyboard::Enter) return Nokia_Key::CONFIRM;
	if (key == sf::Keyboard::Backspace || key == sf::Keyboard::Escape) return Nokia_Key::BACK;
	if (key == sf::Keyboard::Up) return Nokia_Key::UP;
	if (key == sf::Keyboard::Down) return Nokia_Key::DOWN;
	if (key == sf::Keyboard::Left) return Nokia_Key::NUM4;
	if (key == sf::Keyboard::Right) return Nokia_Key::NUM6;
	if (key == sf::Keyboard::Multiply) return Nokia_Key::STAR;
	if (key == sf::Keyboard::Divide) return Nokia_Key::HASH;
	return Nokia_Key::UNKNOWN;
}


sf::Vector2i screen_to_nokia_position(sf::Vector2i mouse)
{
	float scale = nokia_sprite.getScale().x;
	return sf::Vector2i(int((mouse.x - whole_nokia_sprite.getPosition().x) / scale), int(mouse.y / scale));
}


int main(int argc, char** argv)
{
	context_settings.antialiasingLevel = 8;
	blur.loadFromFile(resources_path + "gaussian_blur.glsl", sf::Shader::Fragment);
	blur.setUniform("iChannel0", sf::Shader::CurrentTexture);
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "NOKIA 3310", sf::Style::Fullscreen, context_settings);
	nokia_texture.loadFromFile(resources_path + "nokia.png");
	nokia_sprite.setTexture(nokia_texture);
	blat_texture.loadFromFile(resources_path + "blat.jpg");
	blat_sprite.setTexture(blat_texture);
	fullscreen_texture.loadFromFile(resources_path + "fullscreen_white_192x192.png");
	fullscreen_sprite.setTexture(fullscreen_texture);
	fullscreen_sprite.setOrigin(static_cast<sf::Vector2f>(fullscreen_texture.getSize()));
	fullscreen_sprite.setColor(sf::Color(255, 255, 255, 64));
	window_resized((float)window.getSize().x, (float)window.getSize().y);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	nokia_texture.setSmooth(true);
	blat_texture.setSmooth(true);
	//blurred_nokia.setSmooth(true);
	whole_nokia.setSmooth(true);
	for (unsigned int n = 0; n < key_overlays.size(); n++)
	{
		sf::RectangleShape& overlay = key_overlays[n];
		overlay.setFillColor(sf::Color::Transparent);
		overlay.setOutlineThickness(1.0f);
		overlay.setOutlineColor(sf::Color::Transparent);
		overlay.setSize(sf::Vector2f((float)key_regions[n].width, (float)key_regions[n].height));
	}

	BASS_Init(-1, 44100, NULL, NULL, NULL);
	BASS_SetConfig(BASS_CONFIG_BUFFER, 200);
	HSOUNDFONT soundfont = BASS_MIDI_FontInit((resources_path + "NOKIA 3310.sf2").c_str(), NULL);
	BASS_MIDI_FONT fonts;
	fonts.font = soundfont;
	fonts.bank = 0;
	fonts.preset = -1;
	BASS_MIDI_StreamSetFonts(NULL, &fonts, 1);
	HSTREAM stream = BASS_MIDI_StreamCreate(16, NULL, 44100);
	HSTREAM click = BASS_MIDI_StreamCreate(1, NULL, 44100);
	BASS_ChannelPlay(stream, false);
	BASS_ChannelPlay(click, false);
	for (int i = 0; i < 16; i++) BASS_MIDI_StreamEvent(stream, i, MIDI_EVENT_MODE, 1);
	BASS_MIDI_StreamEvent(click, 0, MIDI_EVENT_MODE, 1);
	BASS_MIDI_StreamEvent(click, 0, MIDI_EVENT_PROGRAM, 127);
	BASS_MIDI_StreamEvent(stream, 9, MIDI_EVENT_DRUMS, true);

	srand((unsigned)time(NULL));
	Bitmap screen(RES_X, RES_Y);
	float real_screen[RES_X][RES_Y];
	memset(real_screen, 0, sizeof(real_screen));
	Scene_Manager::change_scene(new Welcome);
	bool vibrating = false;

	sf::Clock pixel_timer;
	
	while (true)
	{
		sf::Event event;
		auto position = screen_to_nokia_position(sf::Mouse::getPosition());
		while (window.pollEvent(event))
		{
			Nokia_Key nokia_key;
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y)));
				window_resized((float)window.getSize().x, (float)window.getSize().y);
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::F11)
				{
					fullscreen = !fullscreen;
				}
				nokia_key = keyboard_to_nokia_key(event.key.code);
				std::cout << int(nokia_key) << std::endl;
				if (nokia_key == Nokia_Key::UNKNOWN) break;
				Scene_Manager::current_scene()->keyPressed(nokia_key);
				if (Scene_Manager::current_scene()->play_sound_on_click)
				{
					BASS_MIDI_EVENT events[2];
					memset(events, 0, sizeof(events));
					events[0].event = MIDI_EVENT_NOTE;
					events[0].param = MAKEWORD(60, 127);
					events[0].pos = 0;
					events[1].event = MIDI_EVENT_NOTE;
					events[1].param = MAKEWORD(60, 0);
					events[1].pos = DWORD(0.1 * 44100 * 4);
					BASS_MIDI_StreamEvents(click, BASS_MIDI_EVENTS_STRUCT | BASS_MIDI_EVENTS_CANCEL | BASS_MIDI_EVENTS_TIME, events, 2);
				}
				break;

			case sf::Event::KeyReleased:
				nokia_key = keyboard_to_nokia_key(event.key.code);
				if (nokia_key == Nokia_Key::UNKNOWN) break;
				Scene_Manager::current_scene()->keyReleased(nokia_key);
				break;

			case sf::Event::MouseMoved:
				for (unsigned int n = 0; n < key_regions.size(); n++)
				{
					if (key_regions[n].contains(position))
					{
						key_overlays[n].setOutlineColor(sf::Color::White);
					}
					else
					{
						key_overlays[n].setOutlineColor(sf::Color::Transparent);
					}
				}
				if (fullscreen_sprite.getGlobalBounds().contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
				{
					fullscreen_sprite.setColor(sf::Color(255, 255, 255, 255));
				}
				else
				{
					fullscreen_sprite.setColor(sf::Color(255, 255, 255, 64));
				}
				break;

			case sf::Event::MouseButtonPressed:
				for (unsigned int n = 0; n < key_regions.size(); n++)
				{
					if (key_regions[n].contains(position))
					{
						if (Scene_Manager::current_scene()->play_sound_on_click)
						{
							BASS_MIDI_EVENT events[2];
							memset(events, 0, sizeof(events));
							events[0].event = MIDI_EVENT_NOTE;
							events[0].param = MAKEWORD(60, 127);
							events[0].pos = 0;
							events[1].event = MIDI_EVENT_NOTE;
							events[1].param = MAKEWORD(60, 0);
							events[1].pos = DWORD(0.1 * 44100 * 4);
							BASS_MIDI_StreamEvents(click, BASS_MIDI_EVENTS_STRUCT | BASS_MIDI_EVENTS_CANCEL | BASS_MIDI_EVENTS_TIME, events, 2);
						}
						Scene_Manager::current_scene()->keyPressed(Nokia_Key(n));
					}
				}
				if (fullscreen_sprite.getGlobalBounds().contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)))
				{
					fullscreen = !fullscreen;
				}
				break;

			case sf::Event::MouseButtonReleased:
				for (int n = 0; n < (int)Nokia_Key::KEY_COUNT; n++)
				{
					Scene_Manager::current_scene()->keyReleased(Nokia_Key(n));
				}
				break;
			}
		}
		Scene_Manager::current_scene()->check_key_clocks();

		if (Scene_Manager::current_scene()->exit) window.close();
		if (!window.isOpen()) break;

		Scene_Manager::current_scene()->tick();
		auto midi_events = Scene_Manager::current_scene()->get_midi_events();
		if (midi_events.size() > 0)
		{
			BASS_MIDI_StreamEvent(stream, 0, MIDI_EVENT_NOTESOFF, NULL);
			BASS_MIDI_StreamEvents(stream, BASS_MIDI_EVENTS_STRUCT | BASS_MIDI_EVENTS_TIME | BASS_MIDI_EVENTS_CANCEL, &midi_events[0], midi_events.size());
		}
		if (Scene_Manager::current_scene()->vibrate)
		{
			if (!vibrating)
			{
				BASS_MIDI_StreamEvent(stream, 9, MIDI_EVENT_NOTE, MAKEWORD(60, 127));
				vibrating = true;
			}
		}
		else
		{
			if (vibrating)
			{
				BASS_MIDI_StreamEvent(stream, 9, MIDI_EVENT_NOTE, MAKEWORD(60, 0));
				vibrating = false;
			}
		}

		screen.clear();
		Scene_Manager::current_scene()->draw(screen);


		const float fade_factor = pixel_timer.getElapsedTime().asSeconds() / PIXEL_DELAY;
		pixel_timer.restart();
		for (int y = 0; y < RES_Y; y++)
		{
			for (int x = 0; x < RES_X; x++)
			{
				if (screen.at(x, y))
				{
					real_screen[x][y] += fade_factor;
					if (real_screen[x][y] > 1) real_screen[x][y] = 1;
				}
				else
				{
					real_screen[x][y] -= fade_factor;
					if (real_screen[x][y] < 0) real_screen[x][y] = 0;
				}
			}
		}

		window.clear(sf::Color::White);
		if (fullscreen)
		{
			f_texture.clear(sf::Color::Transparent);
			f_texture.draw(sf::Sprite(f_clearance_texture.getTexture()));
			for (int y = 0; y < RES_Y; y++)
			{
				for (int x = 0; x < RES_X; x++)
				{
					if (real_screen[x][y] > 0)
					{
						f_pixel.setFillColor(sf::Color(0, 0, 0, sf::Uint8(real_screen[x][y] * 63.75)));
						f_pixel.setPosition((x * PIXEL_WIDTH + PIXEL_SPACE + SHADOW_OFFSET) * f_nokia_screen_scaling.x, (y * PIXEL_HEIGHT + PIXEL_SPACE + SHADOW_OFFSET) * f_nokia_screen_scaling.y);
						f_texture.draw(f_pixel);
						f_pixel.setFillColor(sf::Color(0, 0, 0, sf::Uint8(real_screen[x][y] * 255)));
						f_pixel.setPosition((x * PIXEL_WIDTH + PIXEL_SPACE) * f_nokia_screen_scaling.x, (y * PIXEL_HEIGHT + PIXEL_SPACE) * f_nokia_screen_scaling.y);
						f_texture.draw(f_pixel);
					}
				}
			}
			f_texture.display();
			f_texture2.clear(sf::Color::Transparent);
			blur.setUniform("iResolution", static_cast<sf::Vector2f>(f_texture.getSize()));
			blur.setUniform("direction", sf::Vector2f(f_nokia_screen_scaling.x, 0.0f));
			f_texture2.draw(sf::Sprite(f_texture.getTexture()), &blur);
			f_texture2.display();
			f_texture.clear(sf::Color::Transparent);
			blur.setUniform("direction", sf::Vector2f(0.0f, f_nokia_screen_scaling.y));
			f_texture.draw(sf::Sprite(f_texture2.getTexture()), &blur);
			f_texture.display();
			window.draw(f_nokia_sprite);
			window.draw(sf::Sprite(f_texture.getTexture()));
		}
		else
		{
			texture.clear(sf::Color::Transparent);
			texture.draw(sf::Sprite(clearance_texture.getTexture()));
			for (int y = 0; y < RES_Y; y++)
			{
				for (int x = 0; x < RES_X; x++)
				{
					if (real_screen[x][y] > 0)
					{
						pixel.setFillColor(sf::Color(0, 0, 0, sf::Uint8(real_screen[x][y] * 63.75)));
						pixel.setPosition((x * PIXEL_WIDTH + PIXEL_SPACE + SHADOW_OFFSET) * nokia_screen_scaling.x, (y * PIXEL_HEIGHT + PIXEL_SPACE + SHADOW_OFFSET) * nokia_screen_scaling.y);
						texture.draw(pixel);
						pixel.setFillColor(sf::Color(0, 0, 0, sf::Uint8(real_screen[x][y] * 255)));
						pixel.setPosition((x * PIXEL_WIDTH + PIXEL_SPACE) * nokia_screen_scaling.x, (y * PIXEL_HEIGHT + PIXEL_SPACE) * nokia_screen_scaling.y);
						texture.draw(pixel);
					}
				}
			}
			texture.display();
			texture2.clear(sf::Color::Transparent);
			blur.setUniform("iResolution", static_cast<sf::Vector2f>(texture.getSize()));
			blur.setUniform("direction", sf::Vector2f(nokia_screen_scaling.x, 0.0f));
			texture2.draw(sf::Sprite(texture.getTexture()), &blur);
			texture2.display();
			texture.clear(sf::Color::Transparent);
			blur.setUniform("direction", sf::Vector2f(0.0f, nokia_screen_scaling.y));
			texture.draw(sf::Sprite(texture2.getTexture()), &blur);
			texture.display();
			sprite.setTexture(texture.getTexture());
			whole_nokia.clear(sf::Color::Transparent);
			whole_nokia.draw(nokia_sprite);
			whole_nokia.draw(sprite);
			for (sf::RectangleShape& shape : key_overlays)
			{
				if (shape.getOutlineColor() != sf::Color::Transparent) whole_nokia.draw(shape);
			}
			whole_nokia.display();
			whole_nokia_sprite.setTexture(whole_nokia.getTexture());
			/*blurred_nokia.draw(sf::Sprite(whole_nokia.getTexture()));
			blurred_nokia.display();
			blur.setUniform("iResolution", static_cast<sf::Vector2f>(blurred_nokia.getSize()));
			blur.setUniform("direction", sf::Vector2f(4.0f, 0.0f));
			for (int n = 0; n < 5; n++)
			{
				blurred_nokia.draw(sf::Sprite(blurred_nokia.getTexture()), &blur);
				blurred_nokia.display();
			}
			blur.setUniform("direction", sf::Vector2f(0.0f, 4.0f));
			for (int n = 0; n < 5; n++)
			{
				blurred_nokia.draw(sf::Sprite(blurred_nokia.getTexture()), &blur);
				blurred_nokia.display();
			}
			blurred_nokia_sprite.setTexture(blurred_nokia.getTexture());
			window.draw(blurred_nokia_sprite);*/
			shadow_sprite.setTexture(whole_nokia.getTexture());
			window.draw(blat_sprite);
			window.draw(shadow_sprite);
			window.draw(whole_nokia_sprite);
		}
		window.draw(fullscreen_sprite);
		window.display();
	}

	return EXIT_SUCCESS;
}