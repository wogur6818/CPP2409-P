#include "game_logic.h"
#include <cmath>
using namespace std;

bool isValidMove(const vector<vector<Piece>>& board, int sx, int sy, int dx, int dy, PieceType type, Player currentPlayer) {
    if (dx < 0 || dx >= BOARD_SIZE || dy < 0 || dy >= BOARD_SIZE) {
        return false;
    }

    if (board[dy][dx].owner == currentPlayer) {
        return false;
    }

    int dx_diff = dx - sx;
    int dy_diff = dy - sy;

    switch (type) {
        case KING: return abs(dx_diff) <= 1 && abs(dy_diff) <= 1;
        case BISHOP: return abs(dx_diff) == abs(dy_diff);
        case ROOK: return dx_diff == 0 || dy_diff == 0;
        default: return false;
    }
}

Player checkWinner(const vector<vector<Piece>>& board, const vector<bool>& activePlayers) {
    vector<bool> kingAlive(5, false);

    for (const auto& row : board) {
        for (const auto& piece : row) {
            if (piece.type == KING && piece.owner != NONE) {
                kingAlive[piece.owner] = true;
            }
        }
    }

    int activeCount = 0;
    Player lastPlayer = NONE;
    for (int i = 1; i <= 4; i++) {
        if (activePlayers[i] && kingAlive[i]) {
            activeCount++;
            lastPlayer = static_cast<Player>(i);
        }
    }

    return (activeCount == 1) ? lastPlayer : NONE;
}

