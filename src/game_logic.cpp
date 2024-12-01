#include "game_logic.h"
#include <cmath>
using namespace std;

bool isValidMove(const vector<vector<Piece>>& board, int sx, int sy, int dx, int dy, PieceType type, Player currentPlayer) {
    // 보드 범위 확인
    if (dx < 0 || dx >= BOARD_SIZE || dy < 0 || dy >= BOARD_SIZE) {
        return false;
    }

    // 같은 팀 기물이 있는 경우 이동 불가
    if (board[dy][dx].owner == currentPlayer) {
        return false;
    }

    // 이동 규칙 확인
    int dx_diff = dx - sx;
    int dy_diff = dy - sy;

    switch (type) {
        case KING: // 모든 방향 1칸 이동
            return abs(dx_diff) <= 1 && abs(dy_diff) <= 1;
        case BISHOP: // 대각선 이동
            if (abs(dx_diff) == abs(dy_diff)) { // 대각선 조건
                int stepX = (dx_diff > 0) ? 1 : -1;
                int stepY = (dy_diff > 0) ? 1 : -1;
                for (int i = 1; i < abs(dx_diff); ++i) {
                    int intermediateX = sx + i * stepX;
                    int intermediateY = sy + i * stepY;
                    if (board[intermediateY][intermediateX].owner != NONE) {
                        return false; // 경로에 기물이 있으면 이동 불가
                    }
                }
                return true;
            }
            return false;
        case ROOK: // 상하좌우 이동
            if (dx_diff == 0 || dy_diff == 0) { // 직선 이동 조건
                int step = (dx_diff != 0) ? ((dx_diff > 0) ? 1 : -1) : ((dy_diff > 0) ? 1 : -1);
                for (int i = 1; i < abs(dx_diff + dy_diff); ++i) {
                    if (dx_diff != 0 && board[sy][sx + i * step].owner != NONE) {
                        return false; // 가로 경로에 기물이 있으면 이동 불가
                    }
                    if (dy_diff != 0 && board[sy + i * step][sx].owner != NONE) {
                        return false; // 세로 경로에 기물이 있으면 이동 불가
                    }
                }
                return true;
            }
            return false;
        default:
            return false;
    }
}

Player checkWinner(const vector<vector<Piece>>& board, vector<bool>& activePlayers) {
    vector<bool> kingAlive(5, false); // 1~4 플레이어의 킹 상태

    for (const auto& row : board) {
        for (const auto& piece : row) {
            if (piece.type == KING && piece.owner != NONE) {
                kingAlive[piece.owner] = true; // 킹이 존재하는 플레이어 확인
            }
        }
    }

    // 킹이 죽은 플레이어는 비활성화
    for (int i = 1; i <= 4; i++) {
        if (!kingAlive[i]) {
            activePlayers[i] = false;
        }
    }

    // 활성화된 플레이어가 한 명만 남으면 승리
    int activeCount = 0;
    Player lastPlayer = NONE;
    for (int i = 1; i <= 4; i++) {
        if (activePlayers[i]) {
            activeCount++;
            lastPlayer = static_cast<Player>(i);
        }
    }

    return (activeCount == 1) ? lastPlayer : NONE;
}
