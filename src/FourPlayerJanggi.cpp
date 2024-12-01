#include <iostream>
#include <vector>
#include "board.h"
#include "game_logic.h"
using namespace std;

int main() {
    // 보드 초기화
    vector<vector<Piece>> board = initializeBoard();

    // 플레이어 상태: 활성화 여부
    vector<bool> activePlayers(5, true); // 1~4 플레이어 활성화

    int currentPlayer = PLAYER1;

    while (true) {
        // 현재 플레이어가 활성화되지 않았다면 다음 플레이어로 이동
        if (!activePlayers[currentPlayer]) {
            currentPlayer = (currentPlayer % 4) + 1;
            continue;
        }

        // 현재 보드 출력
        displayBoard(board);
        cout << "현재 플레이어: P" << currentPlayer << endl;

        // 기물 선택
        int pieceChoice;
        cout << "이동할 기물을 선택하세요 (1: king, 2: bishop, 3: rook): ";
        cin >> pieceChoice;

        PieceType selectedType;
        switch (pieceChoice) {
            case 1: selectedType = KING; break;
            case 2: selectedType = BISHOP; break;
            case 3: selectedType = ROOK; break;
            default:
                cout << "잘못된 선택입니다. 다시 입력하세요." << endl;
                continue;
        }

        // 선택한 기물의 위치 찾기
        int sx = -1, sy = -1;
        bool pieceFound = false;
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (board[y][x].type == selectedType && board[y][x].owner == static_cast<Player>(currentPlayer)) {
                    sx = x;
                    sy = y;
                    pieceFound = true;
                    break;
                }
            }
            if (pieceFound) break;
        }

        if (!pieceFound) {
            cout << "선택한 기물이 없습니다. 다시 입력하세요." << endl;
            continue;
        }

        cout << "선택한 기물 위치: (" << (4 - sy) << ", " << sx << ")" << endl;

        // 이동 방향 입력
        int moveDirection;
        cout << "이동 방향을 선택하세요: ";
        if (selectedType == KING) {
            cout << "1: 위, 2: 아래, 3: 좌, 4: 우, 5: 좌상, 6: 우상, 7: 좌하, 8: 우하" << endl;
        } else if (selectedType == BISHOP) {
            cout << "5: 좌상, 6: 우상, 7: 좌하, 8: 우하" << endl;
        } else if (selectedType == ROOK) {
            cout << "1: 위, 2: 아래, 3: 좌, 4: 우" << endl;
        }
        cin >> moveDirection;

        // 목표 위치 계산
        int dx = sx, dy = sy;
        switch (moveDirection) {
            case 1: dy++; break; // 위
            case 2: dy--; break; // 아래
            case 3: dx--; break; // 좌
            case 4: dx++; break; // 우
            case 5: dy++; dx--; break; // 좌상
            case 6: dy++; dx++; break; // 우상
            case 7: dy--; dx--; break; // 좌하
            case 8: dy--; dx++; break; // 우하
            default:
                cout << "잘못된 방향입니다. 다시 입력하세요." << endl;
                continue;
        }

        // 이동 가능성 확인
        if (!isValidMove(board, sx, sy, dx, dy, selectedType, static_cast<Player>(currentPlayer))) {
            cout << "잘못된 이동입니다. 다시 시도하세요." << endl;
            continue;
        }

        // 이동 처리
        movePiece(board, sx, sy, dx, dy, activePlayers);

        // 승리 조건 확인
        Player winner = checkWinner(board, activePlayers);
        if (winner != NONE) {
            cout << "플레이어 P" << winner << "가 승리했습니다!" << endl;
            break;
        }

        // 다음 플레이어로 이동
        currentPlayer = (currentPlayer % 4) + 1;
    }

    return 0;
}
