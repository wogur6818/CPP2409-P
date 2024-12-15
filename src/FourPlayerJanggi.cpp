#include <iostream>
#include <vector>
#include "board.h"
#include "game_logic.h"
#include "utils.h"
using namespace std;

int main() {
    // 보드 초기화
    vector<vector<Piece>> board = initializeBoard();

    // 플레이어 상태: 활성화 여부
    vector<bool> activePlayers(5, true); // 1~4 플레이어 활성화

    // 잡은 말 저장
    vector<vector<Piece>> capturedPieces(5); // 각 플레이어별로 잡은 말 저장

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

        // 턴 선택
        int actionChoice;
        cout << "1: 말을 움직인다, 2: 잡은 말을 배치한다: ";
        cin >> actionChoice;

        if (actionChoice == 2) {
            // 잡은 말 배치
            if (capturedPieces[currentPlayer].empty()) {
                cout << "잡은 말이 없습니다. 다시 선택하세요." << endl;
                continue;
            }

            // 잡은 말 리스트 출력
            cout << "잡은 말 리스트:" << endl;
            for (size_t i = 0; i < capturedPieces[currentPlayer].size(); ++i) {
                cout << i + 1 << ": " << pieceTypeToString(capturedPieces[currentPlayer][i].type) << endl;
            }

            // 배치할 말 선택
            int pieceIndex;
            cout << "배치할 말을 선택하세요: ";
            cin >> pieceIndex;

            if (pieceIndex < 1 || pieceIndex > capturedPieces[currentPlayer].size()) {
                cout << "잘못된 선택입니다. 다시 선택하세요." << endl;
                continue;
            }

            Piece selectedPiece = capturedPieces[currentPlayer][pieceIndex - 1];

            // 배치할 위치 입력
            int bx, by;
            while (true) {
                cout << "배치할 위치를 입력하세요 (x y): ";
                cin >> bx >> by;

                if (bx < 0 || bx >= BOARD_SIZE || by < 0 || by >= BOARD_SIZE || board[by][bx].owner != NONE) {
                    cout << "잘못된 위치입니다. 빈칸에만 배치할 수 있습니다." << endl;
                } else {
                    break;
                }
            }

            // 말 배치
            board[by][bx] = selectedPiece;
            capturedPieces[currentPlayer].erase(capturedPieces[currentPlayer].begin() + (pieceIndex - 1));
            cout << "말을 (" << bx << ", " << by << ")에 배치했습니다." << endl;

            // 다음 턴으로
            currentPlayer = (currentPlayer % 4) + 1;
            continue;
        }

        if (actionChoice != 1) {
            cout << "잘못된 선택입니다. 다시 입력하세요." << endl;
            continue;
        }

        // 기존 말 이동
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
        movePiece(board, sx, sy, dx, dy, activePlayers, capturedPieces, currentPlayer);

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
