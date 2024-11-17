#include <iostream>
#include <vector>
#include <iomanip> // For formatting output
using namespace std;

// 기물 종류를 나타내는 열거형
enum PieceType { EMPTY, KING, KNIGHT, SOLDIER };

// 플레이어를 나타내는 열거형
enum Player { NONE, PLAYER1, PLAYER2, PLAYER3, PLAYER4 };

// 기물 구조체 정의
struct Piece {
    PieceType type;
    Player owner;
};

// 보드 크기 정의
const int BOARD_SIZE = 5;

// 보드를 초기화하는 함수
vector<vector<Piece>> initializeBoard() {
    vector<vector<Piece>> board(BOARD_SIZE, vector<Piece>(BOARD_SIZE, { EMPTY, NONE }));
    
    // PLAYER1의 기물 배치
    board[0][0] = { KING, PLAYER1 };
    board[0][1] = { KNIGHT, PLAYER1 };
    board[1][0] = { SOLDIER, PLAYER1 };
    
    // PLAYER2의 기물 배치
    board[0][4] = { KING, PLAYER2 };
    board[0][3] = { KNIGHT, PLAYER2 };
    board[1][4] = { SOLDIER, PLAYER2 };
    
    // PLAYER3의 기물 배치
    board[4][4] = { KING, PLAYER3 };
    board[4][3] = { KNIGHT, PLAYER3 };
    board[3][4] = { SOLDIER, PLAYER3 };
    
    // PLAYER4의 기물 배치
    board[4][0] = { KING, PLAYER4 };
    board[4][1] = { KNIGHT, PLAYER4 };
    board[3][0] = { SOLDIER, PLAYER4 };
    
    return board;
}

// 보드를 출력하는 함수
void displayBoard(const vector<vector<Piece>>& board) {
    cout << "=========================================" << endl;
    cout << "              십이장기 보드 상태          " << endl;
    cout << "=========================================" << endl;

    for (int y = 0; y < BOARD_SIZE; y++) {
        cout << "|"; // 좌측 테두리
        for (int x = 0; x < BOARD_SIZE; x++) {
            const Piece& piece = board[y][x];
            if (piece.owner == NONE) {
                cout << "  빈칸  |";
            } else {
                cout << " ";
                switch (piece.owner) {
                    case PLAYER1: cout << "P1_"; break;
                    case PLAYER2: cout << "P2_"; break;
                    case PLAYER3: cout << "P3_"; break;
                    case PLAYER4: cout << "P4_"; break;
                    default: break;
                }
                switch (piece.type) {
                    case KING: cout << "왕 "; break;
                    case KNIGHT: cout << "기사"; break;
                    case SOLDIER: cout << "병사"; break;
                    default: break;
                }
                cout << " |";
            }
        }
        cout << endl;
        // 가로 줄 출력
        cout << "-----------------------------------------" << endl;
    }
}

// 메인 함수
int main() {
    // 보드 초기화
    vector<vector<Piece>> board = initializeBoard();
    
    // 보드 출력
    cout << "초기 5x5 십이장기 보드 상태:" << endl;
    displayBoard(board);

    return 0;
}

