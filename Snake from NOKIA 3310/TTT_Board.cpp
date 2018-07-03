#include "TTT_Board.h"
#include <cstring>



TTT_Board::TTT_Board()
{
	memset(data, 0, sizeof(data));
}


TTT_Board::~TTT_Board()
{
}


void TTT_Board::set(int x, int y, TTT_Player value)
{
	data[x][y] = value;
	check_winner_row(y);
	check_winner_column(x);
	if (x == y) check_winner_diagonal(false);
	if (x == 2 - y) check_winner_diagonal(true);
	available_moves--;
	if (available_moves == 0 && winner == TTT_Player::EMPTY) winner = TTT_Player::DRAW;
}


void TTT_Board::check_winner_row(int y)
{
	if (data[0][y] != TTT_Player::EMPTY && data[0][y] == data[1][y] && data[0][y] == data[2][y])
	{
		winner = data[0][y];
	}
}


void TTT_Board::check_winner_column(int x)
{
	if (data[x][0] != TTT_Player::EMPTY && data[x][0] == data[x][1] && data[x][0] == data[x][2])
	{
		winner = data[x][0];
	}
}


void TTT_Board::check_winner_diagonal(bool topright_bottomleft)
{
	if (data[1][1] != TTT_Player::EMPTY && data[1][1] == data[2 * topright_bottomleft][0] && data[1][1] == data[2 - 2 * topright_bottomleft][2])
	{
		winner = data[1][1];
	}
}