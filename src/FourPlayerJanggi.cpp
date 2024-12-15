#include <iostream>
#include <vector>
#include "board.h"
#include "game_logic.h"
#include "utils.h"
using namespace std;

void printCapturedPieces(const vector<vector<Piece>>& capturedPieces) {
    for (size_t player = 1; player < capturedPieces.size(); ++player) {
        cout << "P" << player << "의 잡은 말: ";
        for (const auto& piece : capturedPieces[player]) {
            cout << pieceTypeToString(piece.type) << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<Piece>> board = initializeBoard();
    vector<bool> activePlayers(5, true);
    vector<vector<Piece>> capturedPieces(5); // 각 플레이어별 잡은 말 저장

    int currentPlayer = PLAYER1;

    while (true) {
        if (!activePlayers[currentPlayer]) {
            currentPlayer = (currentPlayer % 4) + 1;
            continue;
        }

        displayBoard(board);
        printCapturedPieces(capturedPieces);

        cout << "현재 플레이어: P" << currentPlayer << endl;

        int actionChoice;
        cout << "1: 말을 움직인다, 2: 잡은 말을 배치한다: ";
        cin >> actionChoice;

        if (actionChoice == 2) {
            // 잡은 말이 없는 경우 처리
            if (capturedPieces[currentPlayer].empty()) {
                cout << "잡은 말이 없습니다. 다시 선택하세요." << endl;
                continue;
            }

            // 잡은 말 리스트 출력
            cout << "잡은 말 리스트:" << endl;
            for (size_t i = 0; i < capturedPieces[currentPlayer].size(); ++i) {
                cout << i + 1 << ": " << pieceTypeToString(capturedPieces[currentPlayer][i].type) << endl;
            }

            int pieceIndex;
            cout << "배치할 말을 선택하세요: ";
            cin >> pieceIndex;

            if (pieceIndex < 1 || pieceIndex > capturedPieces[currentPlayer].size()) {
                cout << "잘못된 선택입니다. 다시 선택하세요." << endl;
                continue;
            }

            Piece selectedPiece = capturedPieces[currentPlayer][pieceIndex - 1];

            // 플레이어별 배치 가능한 위치 설정
            vector<pair<int, int>> validPositions;
            if (currentPlayer == PLAYER1) {
                validPositions = {{0, 4}, {1, 4}, {0, 3}, {1, 3}};
            } else if (currentPlayer == PLAYER2) {
                validPositions = {{3, 4}, {4, 4}, {3, 3}, {4, 3}};
            } else if (currentPlayer == PLAYER3) {
                validPositions = {{3, 0}, {4, 0}, {3, 1}, {4, 1}};
            } else if (currentPlayer == PLAYER4) {
                validPositions = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
            }

            // 빈칸 필터링
            vector<pair<int, int>> filteredPositions;
            for (const auto& pos : validPositions) {
                int x = pos.first;
                int y = pos.second;
                if (board[y][x].owner == NONE) {
                    filteredPositions.push_back(pos);
                }
            }

            if (filteredPositions.empty()) {
                cout << "배치 가능한 위치가 없습니다. 다시 선택하세요." << endl;
                continue;
            }

            // 유효한 위치 출력
            cout << "배치할 위치를 선택하세요:" << endl;
            for (size_t i = 0; i < filteredPositions.size(); ++i) {
                cout << i + 1 << ": 좌표 (" << filteredPositions[i].first << ", " << filteredPositions[i].second << ")" << endl;
            }

            int positionChoice;
            cin >> positionChoice;

            if (positionChoice < 1 || positionChoice > filteredPositions.size()) {
                cout << "잘못된 선택입니다. 다시 선택하세요." << endl;
                continue;
            }

            // 선택된 위치에 말 배치
            int bx = filteredPositions[positionChoice - 1].first;
            int by = filteredPositions[positionChoice - 1].second;
            board[by][bx] = selectedPiece;

            // 잡은 말 리스트에서 제거
            capturedPieces[currentPlayer].erase(capturedPieces[currentPlayer].begin() + (pieceIndex - 1));
            cout << "말을 (" << bx << ", " << by << ")에 배치했습니다." << endl;

            currentPlayer = (currentPlayer % 4) + 1;
            continue;
        }

        if (actionChoice != 1) {
            cout << "잘못된 선택입니다. 다시 입력하세요." << endl;
            continue;
        }

        // 기존 말 이동 로직 (생략)
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

        cout << "선택한 기물 위치: (" << sy << ", " << sx << ")" << endl;

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

        if (!isValidMove(board, sx, sy, dx, dy, selectedType, static_cast<Player>(currentPlayer))) {
            cout << "잘못된 이동입니다. 다시 시도하세요." << endl;
            continue;
        }

        movePiece(board, sx, sy, dx, dy, activePlayers, capturedPieces, currentPlayer);

        Player winner = checkWinner(board, activePlayers);
        if (winner != NONE) {
            cout << "플레이어 P" << winner << "가 승리했습니다!" << endl;
            break;
        }

        currentPlayer = (currentPlayer % 4) + 1;
    }

    return 0;
}
