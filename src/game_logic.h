#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include "board.h"

bool isValidMove(const vector<vector<Piece>>& board, int sx, int sy, int dx, int dy, PieceType type, Player currentPlayer);
vector<pair<int, int>> getValidPlacementPositions(const vector<vector<Piece>>& board, int currentPlayer);
Player checkWinner(const vector<vector<Piece>>& board, const vector<bool>& activePlayers);

#endif
