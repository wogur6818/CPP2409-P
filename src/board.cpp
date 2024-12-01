#include "board.h"
#include <iostream>
#include <iomanip>
using namespace std;

// 보드 초기화 함수
vector<vector<Piece>> initializeBoard() {
    vector<vector<Piece>> board(BOARD_SIZE, vector<Piece>(BOARD_SIZE, { EMPTY, NONE }));

    // PLAYER1 기물 배치 (왼쪽 아래)
    board[4][0] = { KING, PLAYER1 };
    board[4][1] = { BISHOP, PLAYER1 };
    board[3][0] = { ROOK, PLAYER1 };

    // PLAYER2 기물 배치 (오른쪽 아래)
    board[4][4] = { KING, PLAYER2 };
    board[4][3] = { BISHOP, PLAYER2 };
    board[3][4] = { ROOK, PLAYER2 };

    // PLAYER3 기물 배치 (오른쪽 위)
    board[0][4] = { KING, PLAYER3 };
    board[0][3] = { BISHOP, PLAYER3 };
    board[1][4] = { ROOK, PLAYER3 };

    // PLAYER4 기물 배치 (왼쪽 위)
    board[0][0] = { KING, PLAYER4 };
    board[0][1] = { BISHOP, PLAYER4 };
    board[1][0] = { ROOK, PLAYER4 };

    return board;
}

// 보드 출력 함수
void displayBoard(const vector<vector<Piece>>& board) {
    cout << "=========================================" << endl;
    cout << "              십이장기 보드 상태          " << endl;
    cout << "=========================================" << endl;

    for (int y = BOARD_SIZE - 1; y >= 0; y--) { // 아래에서 위로 출력
        cout << "|";
        for (int x = 0; x < BOARD_SIZE; x++) {
            const Piece& piece = board[y][x];
            if (piece.owner == NONE) {
                cout << setw(12) << "빈칸" << " |";
            } else {
                string owner = "P" + to_string(piece.owner) + "_";
                switch (piece.type) {
                    case KING: owner += "king"; break;
                    case BISHOP: owner += "bishop"; break;
                    case ROOK: owner += "rook"; break;
                    default: owner += "unknown";
                }
                cout << setw(12) << owner << " |";
            }
        }
        cout << endl;
        cout << "-----------------------------------------" << endl;
    }
}

// 기물 이동 처리 함수
void movePiece(vector<vector<Piece>>& board, int sx, int sy, int dx, int dy, vector<bool>& activePlayers) {
    if (board[dy][dx].type == KING) {
        // 킹이 제거되면 해당 플레이어를 비활성화
        activePlayers[board[dy][dx].owner] = false;
    }
    board[dy][dx] = board[sy][sx];
    board[sy][sx] = { EMPTY, NONE };
}
