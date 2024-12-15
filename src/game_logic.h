#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include "board.h"

bool isValidMove(const vector<vector<Piece>>& board, int sx, int sy, int dx, int dy, PieceType type, Player currentPlayer);
Player checkWinner(const vector<vector<Piece>>& board, const vector<bool>& activePlayers);

#endif
