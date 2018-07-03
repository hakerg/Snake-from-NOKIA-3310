#include "TTT_Gameplay.h"
#include "Small_Cross.h"
#include "Small_Nought.h"
#include "Big_Cross.h"
#include "Big_Nought.h"
#include "Scene_Manager.h"
#include "Big_Text.h"
#include "Data_Container.h"



TTT_Gameplay::TTT_Gameplay(bool O_controls_player, bool X_controls_player) : loading_bar(70, 46, 12, 4, 2)
{
	O_is_player = O_controls_player;
	X_is_player = X_controls_player;
	switch_player();
}


TTT_Gameplay::~TTT_Gameplay()
{
}


void TTT_Gameplay::draw(Bitmap& target)
{
	target.draw_rectangle(14, 0, 1, 51);
	target.draw_rectangle(32, 0, 1, 51);
	target.draw_rectangle(50, 0, 1, 51);
	target.draw_rectangle(68, 0, 1, 51);
	target.draw_rectangle(15, 16, 17, 1);
	target.draw_rectangle(33, 16, 17, 1);
	target.draw_rectangle(51, 16, 17, 1);
	target.draw_rectangle(15, 34, 17, 1);
	target.draw_rectangle(33, 34, 17, 1);
	target.draw_rectangle(51, 34, 17, 1);

	for (int x = 0; x < 3; x++)
	{
		int offset_x = 18 * x;
		for (int y = 0; y < 3; y++)
		{
			int offset_y = 18 * y;
			TTT_Board& b = playground.board(x, y);
			if (b.get_winner() != TTT_Player::O && b.get_winner() != TTT_Player::X)
			{
				target.draw_rectangle(20 + offset_x, offset_y, 1, 15);
				target.draw_rectangle(26 + offset_x, offset_y, 1, 15);
				target.draw_rectangle(16 + offset_x, 4 + offset_y, 4, 1);
				target.draw_rectangle(21 + offset_x, 4 + offset_y, 5, 1);
				target.draw_rectangle(27 + offset_x, 4 + offset_y, 4, 1);
				target.draw_rectangle(16 + offset_x, 10 + offset_y, 4, 1);
				target.draw_rectangle(21 + offset_x, 10 + offset_y, 5, 1);
				target.draw_rectangle(27 + offset_x, 10 + offset_y, 4, 1);
			}
		}
	}

	for (std::shared_ptr <Animation> a : animations)
	{
		a->draw(target);
	}

	if (thinking) loading_bar.draw(target);

	if (selected_board_x != -1)
	{
		if (selected_cell_x != -1)
		{
			target.draw_rectangle(16 + selected_board_x * 18 + selected_cell_x * 6, selected_board_y * 18 + selected_cell_y * 6, 3, 3, true);
		}
		else switch (selected_board_y)
		{
		case 0:
			target.draw_rectangle(15 + selected_board_x * 18, 0, 17, 16);
			break;
		case 1:
			target.draw_rectangle(15 + selected_board_x * 18, 17, 17, 17);
			break;
		case 2:
			target.draw_rectangle(15 + selected_board_x * 18, 35, 17, 16);
			break;
		}
	}

	if (playground.get_winner() == TTT_Player::EMPTY)
	{
		data.medium_font.draw_string(target, (playground.who_is_next() == TTT_Player::O ? "O" : "X"), 0, target.h, 14, Horizontal_Align::LEFT, Vertical_Align::BOTTOM);
	}
}


void TTT_Gameplay::set(int board_x, int board_y, int x, int y)
{
	if (playground.who_is_next() == TTT_Player::X) animations.push_back(std::make_shared <Small_Cross>(board_x, board_y, x, y));
	else animations.push_back(std::make_shared <Small_Nought>(board_x, board_y, x, y));
	playground.set(board_x, board_y, x, y);
	TTT_Board& b = playground.board(board_x, board_y);
	if (b.get_winner() == TTT_Player::O || b.get_winner() == TTT_Player::X)
	{
		animations.erase(std::remove_if(animations.begin(), animations.end(), [=](const auto& a)
		{
			return (a->x >= 16 + board_x * 18) && (a->x < 34 + board_x * 18) && (a->y >= board_y * 18) && (a->y < 18 + board_y * 18);
		}
		) ,animations.end());

		if (b.get_winner() == TTT_Player::O) animations.push_back(std::make_shared <Big_Nought>(board_x, board_y));
		else animations.push_back(std::make_shared <Big_Cross>(board_x, board_y));
	}

	if (playground.get_winner() == TTT_Player::EMPTY) switch_player();
	else winner_scene();
}


void TTT_Gameplay::tick()
{
	if (ai_bx != -1)
	{
		thinking = false;
		set(ai_bx, ai_by, ai_x, ai_y);
		ai_bx = ai_by = ai_x = ai_y = -1;
	}
}


void TTT_Gameplay::switch_player()
{
	selected_cell_x = -1;
	selected_cell_y = -1;
	if (controls_player())
	{
		selected_board_x = playground.get_active_board_x();
		selected_board_y = playground.get_active_board_y();
	}
	else
	{
		selected_board_x = -1;
		selected_board_y = -1;
		launch_ai_thread();
	}
}


void TTT_Gameplay::launch_ai_thread()
{
	sf::Time limit = sf::seconds(!O_is_player && !X_is_player ? 0.75f : 3.0f);
	if (t.joinable()) t.join();
	t = std::thread(&TTT_Playground::calculate_turn, playground, limit, &ai_bx, &ai_by, &ai_x, &ai_y);
	thinking = true;
}


void TTT_Gameplay::number_pressed(unsigned int number)
{
	if (number == 0) return;
	if (controls_player())
	{
		number--;
		int sel_x = number % 3;
		int sel_y = number / 3;
		if (selected_board_x == -1)
		{
			if (playground.board(sel_x, sel_y).get_winner() == TTT_Player::EMPTY)
			{
				selected_board_x = sel_x;
				selected_board_y = sel_y;
			}
		}
		else
		{
			if (playground.board(selected_board_x, selected_board_y).at(sel_x, sel_y) == TTT_Player::EMPTY) set(selected_board_x, selected_board_y, sel_x, sel_y);
		}
	}
}


void TTT_Gameplay::winner_scene()
{
	switch (playground.get_winner())
	{
	case TTT_Player::O:
		if (O_is_player == true && X_is_player == true) Scene_Manager::change_scene(new Big_Text("O Wygrywa!"));
		else if (O_is_player == false && X_is_player == false);
		else if (O_is_player == true && X_is_player == false) Scene_Manager::change_scene(new Big_Text("O Wygrywa!"));
		else Scene_Manager::change_scene(new Big_Text("Koniec Gry."));
		break;
	case TTT_Player::X:
		if (O_is_player == true && X_is_player == true) Scene_Manager::change_scene(new Big_Text("X Wygrywa!"));
		else if (O_is_player == false && X_is_player == false);
		else if (O_is_player == true && X_is_player == false) Scene_Manager::change_scene(new Big_Text("Koniec Gry."));
		else Scene_Manager::change_scene(new Big_Text("X Wygrywa!"));
		break;
	case TTT_Player::DRAW:
		if (O_is_player == true && X_is_player == true) Scene_Manager::change_scene(new Big_Text("Remis."));
		else if (O_is_player == false && X_is_player == false);
		else if (O_is_player == true && X_is_player == false) Scene_Manager::change_scene(new Big_Text("Remis."));
		else Scene_Manager::change_scene(new Big_Text("Remis."));
		break;
	}
}


void TTT_Gameplay::confirmed()
{
	if (controls_player())
	{
		if (selected_board_x == -1)
		{
			selected_board_x = 1;
			selected_board_y = 1;
		}
		else if (selected_cell_x == -1)
		{
			if (playground.board(selected_board_x, selected_board_y).get_winner() == TTT_Player::EMPTY)
			{
				selected_cell_x = 1;
				selected_cell_y = 1;
			}
		}
		else if (playground.board(selected_board_x, selected_board_y).at(selected_cell_x, selected_cell_y) == TTT_Player::EMPTY) set(selected_board_x, selected_board_y, selected_cell_x, selected_cell_y);
	}
}


void TTT_Gameplay::arrow_pressed(sf::Vector2i direction)
{
	if (controls_player())
	{
		if (selected_board_x == -1)
		{
			selected_board_x = 1 + direction.x;
			selected_board_y = 1 + direction.y;
		}
		else if (selected_cell_x == -1)
		{
			if (playground.get_active_board_x() == -1)
			{
				selected_board_x = (selected_board_x + direction.x + 3) % 3;
				selected_board_y = (selected_board_y + direction.y + 3) % 3;
			}
			else
			{
				selected_cell_x = 1 + direction.x;
				selected_cell_y = 1 + direction.y;
			}
		}
		else
		{
			selected_cell_x = (selected_cell_x + direction.x + 3) % 3;
			selected_cell_y = (selected_cell_y + direction.y + 3) % 3;
		}
	}
}


void TTT_Gameplay::returned()
{
	if (selected_cell_x != -1 && controls_player())
	{
		selected_cell_x = -1;
		selected_cell_y = -1;
	}
	else
	{
		t.join();
		Scene_Manager::go_to_previous_scene();
	}
}


bool TTT_Gameplay::controls_player()
{
	return playground.who_is_next() == TTT_Player::O && O_is_player || playground.who_is_next() == TTT_Player::X && X_is_player;
}