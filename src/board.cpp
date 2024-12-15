#include "board.h"
#include <iostream>
#include <iomanip>
using namespace std;

// 보드 초기화 함수
vector<vector<Piece>> initializeBoard() {
    vector<vector<Piece>> board(BOARD_SIZE, vector<Piece>(BOARD_SIZE, { EMPTY, NONE }));

    // 초기 배치
    board[4][0] = { KING, PLAYER1 };
    board[4][1] = { BISHOP, PLAYER1 };
    board[3][0] = { ROOK, PLAYER1 };

    board[4][4] = { KING, PLAYER2 };
    board[4][3] = { BISHOP, PLAYER2 };
    board[3][4] = { ROOK, PLAYER2 };

    board[0][4] = { KING, PLAYER3 };
    board[0][3] = { BISHOP, PLAYER3 };
    board[1][4] = { ROOK, PLAYER3 };

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

    for (int y = BOARD_SIZE - 1; y >= 0; y--) {
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
void movePiece(vector<vector<Piece>>& board, int sx, int sy, int dx, int dy, vector<bool>& activePlayers, vector<vector<Piece>>& capturedPieces, int currentPlayer) {
    if (board[dy][dx].owner != NONE && board[dy][dx].owner != currentPlayer) {
        capturedPieces[currentPlayer].push_back(board[dy][dx]); // 잡은 말 저장
        cout << "P" << currentPlayer << "이 P" << board[dy][dx].owner << "의 말을 잡았습니다: "
             << (board[dy][dx].type == KING ? "KING" : board[dy][dx].type == BISHOP ? "BISHOP" : "ROOK") << endl;
    }

    if (board[dy][dx].type == KING) {
        activePlayers[board[dy][dx].owner] = false;
        cout << "P" << board[dy][dx].owner << "의 KING이 제거되었습니다. 게임 오버!" << endl;
    }

    board[dy][dx] = board[sy][sx];
    board[sy][sx] = { EMPTY, NONE };
}
