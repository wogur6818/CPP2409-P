#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
using namespace std;

// 기물 구조체와 기타 선언
enum PieceType { EMPTY, KING, BISHOP, ROOK };
enum Player { NONE, PLAYER1, PLAYER2, PLAYER3, PLAYER4 };

struct Piece {
    PieceType type;
    Player owner;
};

const int BOARD_SIZE = 5;

// 함수 선언
vector<vector<Piece>> initializeBoard();
void displayBoard(const vector<vector<Piece>>& board);
void movePiece(vector<vector<Piece>>& board, int sx, int sy, int dx, int dy, vector<bool>& activePlayers);

#endif
