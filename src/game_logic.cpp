#include "game_logic.h"
#include <cmath>

bool isValidMove(const vector<vector<Piece>>& board, int sx, int sy, int dx, int dy, PieceType type, Player currentPlayer) {
    if (dx < 0 || dx >= BOARD_SIZE || dy < 0 || dy >= BOARD_SIZE) return false;
    if (board[dy][dx].owner == currentPlayer) return false;

    int dx_diff = dx - sx, dy_diff = dy - sy;

    switch (type) {
        case KING: return abs(dx_diff) <= 1 && abs(dy_diff) <= 1;
        case BISHOP: return abs(dx_diff) == abs(dy_diff);
        case ROOK: return dx_diff == 0 || dy_diff == 0;
        default: return false;
    }
}

vector<pair<int, int>> getValidPlacementPositions(const vector<vector<Piece>>& board, int currentPlayer) {
    vector<pair<int, int>> positions;

    int x_start = (currentPlayer == PLAYER1 || currentPlayer == PLAYER4) ? 0 : 3;
    int y_start = (currentPlayer == PLAYER1 || currentPlayer == PLAYER2) ? 3 : 0;

    for (int y = y_start; y < y_start + 2; y++) {
        for (int x = x_start; x < x_start + 2; x++) {
            if (board[y][x].owner == NONE) {
                positions.push_back({x, y});
            }
        }
    }

    return positions;
}

Player checkWinner(const vector<vector<Piece>>& board, const vector<bool>& activePlayers) {
    vector<bool> kingAlive(5, false); // 각 플레이어의 왕 생존 상태

    for (const auto& row : board) {
        for (const auto& piece : row) {
            if (piece.type == KING && piece.owner != NONE) {
                kingAlive[piece.owner] = true;
            }
        }
    }

    // 한 명의 플레이어만 왕이 살아있다면 승리
    int activeCount = 0;
    Player lastPlayer = NONE;
    for (size_t i = 1; i < kingAlive.size(); ++i) {
        if (kingAlive[i] && activePlayers[i]) {
            activeCount++;
            lastPlayer = static_cast<Player>(i);
        }
    }

    return (activeCount == 1) ? lastPlayer : NONE;
}