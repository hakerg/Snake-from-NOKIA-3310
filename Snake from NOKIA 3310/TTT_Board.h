#pragma once



enum class TTT_Player { EMPTY, O, X, DRAW };


class TTT_Board
{
private:
	TTT_Player data[3][3];
	TTT_Player winner = TTT_Player::EMPTY;
	int available_moves = 9;

	void check_winner_row(int y);
	void check_winner_column(int x);
	void check_winner_diagonal(bool topright_bottomleft);

public:
	TTT_Board();
	~TTT_Board();
	TTT_Player at(int x, int y) { return data[x][y]; }
	void set(int x, int y, TTT_Player value);
	TTT_Player get_winner() { return winner; }
};

