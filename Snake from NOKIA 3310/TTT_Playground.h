#pragma once
#include "TTT_Board.h"
#include "SFML\Graphics.hpp"

struct TTT_Playground_Position
{
	int board_x, board_y, x, y;
	TTT_Playground_Position(int a, int b, int c, int d)
	{
		board_x = a;
		board_y = b;
		x = c;
		y = d;
	}
};

class TTT_Playground
{
private:
	TTT_Board boards[3][3];
	TTT_Player winner = TTT_Player::EMPTY;
	int available_boards = 9, o_wins = 0, x_wins = 0;
	int active_board_x = -1, active_board_y = -1;
	TTT_Player next_player = TTT_Player::O;

	void check_winner_row(int board_y);
	void check_winner_column(int board_x);
	void check_winner_diagonal(bool board_topright_bottomleft);
	TTT_Player get_winner_with_random_turns();

public:
	TTT_Playground();
	~TTT_Playground();
	TTT_Board& board(int x, int y) { return boards[x][y]; }
	void set(int board_x, int board_y, int x, int y);
	TTT_Player get_winner() { return winner; }
	void calculate_turn(sf::Time limit, int* board_x, int* board_y, int* x, int* y);
	std::vector <TTT_Playground_Position> available_turns();
	int get_active_board_x() { return active_board_x; }
	int get_active_board_y() { return active_board_y; }
	TTT_Player who_is_next() { return next_player; }
};

