#include "TTT_Playground.h"
#include <iostream>



TTT_Playground::TTT_Playground()
{
}


TTT_Playground::~TTT_Playground()
{
}


void TTT_Playground::set(int board_x, int board_y, int x, int y)
{
	TTT_Board& b = boards[board_x][board_y];
	b.set(x, y, next_player);
	if (next_player == TTT_Player::O) next_player = TTT_Player::X;
	else next_player = TTT_Player::O;
	if (boards[x][y].get_winner() == TTT_Player::EMPTY)
	{
		active_board_x = x;
		active_board_y = y;
	}
	else
	{
		active_board_x = -1;
		active_board_y = -1;
	}
	if (b.get_winner() != TTT_Player::EMPTY)
	{
		check_winner_row(board_y);
		check_winner_column(board_x);
		if (board_x == board_y) check_winner_diagonal(false);
		if (board_x == 2 - board_y) check_winner_diagonal(true);
		if (b.get_winner() == TTT_Player::O) o_wins++;
		else if (b.get_winner() == TTT_Player::X) x_wins++;
		available_boards--;
		if (available_boards == 0 && winner == TTT_Player::EMPTY)
		{
			if (o_wins > x_wins) winner = TTT_Player::O;
			else if (o_wins < x_wins) winner = TTT_Player::X;
			else winner = TTT_Player::DRAW;
		}
	}
}


void TTT_Playground::check_winner_row(int board_y)
{
	if (!(boards[0][board_y].get_winner() == TTT_Player::O || boards[0][board_y].get_winner() == TTT_Player::X)) return;
	if (boards[0][board_y].get_winner() == boards[1][board_y].get_winner() && boards[0][board_y].get_winner() == boards[2][board_y].get_winner())
	{
		winner = boards[0][board_y].get_winner();
	}
}


void TTT_Playground::check_winner_column(int board_x)
{
	if (!(boards[board_x][0].get_winner() == TTT_Player::O || boards[board_x][0].get_winner() == TTT_Player::X)) return;
	if (boards[board_x][0].get_winner() == boards[board_x][1].get_winner() && boards[board_x][0].get_winner() == boards[board_x][2].get_winner())
	{
		winner = boards[board_x][0].get_winner();
	}
}


void TTT_Playground::check_winner_diagonal(bool board_topright_bottomleft)
{
	if (!(boards[1][1].get_winner() == TTT_Player::O || boards[1][1].get_winner() == TTT_Player::X)) return;
	if (boards[1][1].get_winner() == boards[2 * board_topright_bottomleft][0].get_winner() && boards[1][1].get_winner() == boards[2 - 2 * board_topright_bottomleft][2].get_winner())
	{
		winner = boards[1][1].get_winner();
	}
}


void TTT_Playground::calculate_turn(sf::Time limit, int* board_x, int* board_y, int* x, int* y)
{
	sf::Clock timer;
	auto turns = available_turns();
	int turns_count = turns.size();
	std::vector <float> win_rate(turns_count, 0.5f);
	std::vector <int> checks(turns_count, 0);
	std::vector <TTT_Playground> playgrounds(turns_count, *this);
	for (int i = 0; i < turns_count; i++)
	{
		auto& t = turns[i];
		playgrounds[i].set(t.board_x, t.board_y, t.x, t.y);
	}
	int index = 0;
	do
	{
		auto& r = win_rate[index];
		auto& c = checks[index];
		TTT_Playground p(playgrounds[index]);
		TTT_Player w = p.get_winner_with_random_turns();
		float rate;
		if (w == next_player) rate = 1.0f;
		else if (w == TTT_Player::DRAW) rate = 0.5f;
		else rate = 0.0f;
		r = (r * c + rate) / (c + 1);
		c++;
		index++;
		if (index == turns_count) index = 0;
	}
	while (timer.getElapsedTime() < limit);
	index = 0;
	for (int i = 1; i < turns_count; i++)
	{
		if (win_rate[i] > win_rate[index]) index = i;
	}
	auto& turn = turns[index];
	*y = turn.y;
	*x = turn.x;
	*board_y = turn.board_y;
	*board_x = turn.board_x;
}


std::vector <TTT_Playground_Position> TTT_Playground::available_turns()
{
	std::vector <TTT_Playground_Position> ret;
	ret.clear();
	if (active_board_x == -1)
	{
		for (int bx = 0; bx < 3; bx++)
			for (int by = 0; by < 3; by++)
			{
				TTT_Board& b = boards[bx][by];
				if (b.get_winner() == TTT_Player::EMPTY)
				{
					for (int x = 0; x < 3; x++)
						for (int y = 0; y < 3; y++)
						{
							if (b.at(x, y) == TTT_Player::EMPTY) ret.emplace_back(bx, by, x, y);
						}
				}
			}
	}
	else
	{
		TTT_Board& b = boards[active_board_x][active_board_y];
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
			{
				if (b.at(x, y) == TTT_Player::EMPTY) ret.emplace_back(active_board_x, active_board_y, x, y);
			}
	}
	return ret;
}


TTT_Player TTT_Playground::get_winner_with_random_turns()
{
	if (winner != TTT_Player::EMPTY) return winner;
	auto turns = available_turns();
	auto turn = turns[rand() % turns.size()];
	set(turn.board_x, turn.board_y, turn.x, turn.y);
	return get_winner_with_random_turns();
}