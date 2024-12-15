#include <iostream>
#include <vector>
#include <algorithm> 
#include "board.h"
#include "game_logic.h"
#include "utils.h"
using namespace std;


void printCapturedPieces(const vector<vector<Piece>>& capturedPieces) {
    for (size_t player = 1; player < capturedPieces.size(); ++player) {
        cout << "P" << player << "의 잡은 말: ";
        for (const auto& piece : capturedPieces[player]) {
            if (piece.type != KING) { // 킹은 표시하지 않음
                cout << pieceTypeToString(piece.type) << "_" << piece.id << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<Piece>> board = initializeBoard();
    vector<bool> activePlayers(5, true);
    vector<vector<Piece>> capturedPieces(5);
    vector<int> pieceCounters(5, 1); // 각 플레이어의 기물 ID 카운터
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
        cout << "1: 말을 움직인다, 2: 잡은 말을 배치한다, 3: 게임 방법 설명: ";
        cin >> actionChoice;

        if (actionChoice == 3) {
            cout << "=========================================" << endl;
            cout << "             게임 방법 설명              " << endl;
            cout << "=========================================" << endl;
            cout << "1. 각 플레이어는 자신의 턴에 다음 중 하나를 선택할 수 있습니다:" << endl;
            cout << "   - '1'을 선택하면 자신의 말을 움직입니다." << endl;
            cout << "   - '2'를 선택하면 잡은 말을 자신의 영역(각 플레이어 초기 상태에 왕을 포함한 가까운 4칸)에 배치합니다." << endl;
            cout << "2. 말을 움직이는 규칙은 다음과 같습니다:" << endl;
            cout << "   - 왕(King): 8방향으로 한 칸 이동 가능합니다." << endl;
            cout << "   - 비숍(Bishop): 대각선 방향으로 이동합니다." << endl;
            cout << "   - 룩(Rook): 상하좌우로 이동합니다." << endl;
            cout << "3. 상대방의 말을 잡으면 자신의 말로 사용할 수 있습니다 (단, 킹은 제외됩니다)." << endl;
            cout << "4. 자신의 킹이 잡히면 게임 오버가 됩니다." << endl;
            cout << "5. 한 명의 플레이어만 킹이 살아남으면 그 플레이어가 승리합니다." << endl;
            cout << "=========================================" << endl;
            continue;
        }

        if (actionChoice == 2) {
            // 잡은 말 배치 로직
            auto& currentCapturedPieces = capturedPieces[currentPlayer];
            currentCapturedPieces.erase(remove_if(currentCapturedPieces.begin(), currentCapturedPieces.end(),
                                                  [](const Piece& piece) { return piece.type == KING; }),
                                        currentCapturedPieces.end());

            if (currentCapturedPieces.empty()) {
                cout << "잡은 말이 없습니다. 다시 선택하세요." << endl;
                continue;
            }

            cout << "잡은 말 리스트:" << endl;
            for (size_t i = 0; i < currentCapturedPieces.size(); ++i) {
                cout << i + 1 << ": " << pieceTypeToString(currentCapturedPieces[i].type)
                     << "_" << currentCapturedPieces[i].id << endl;
            }

            int pieceIndex;
            cout << "배치할 말을 선택하세요: ";
            cin >> pieceIndex;

            if (pieceIndex < 1 || pieceIndex > currentCapturedPieces.size()) {
                cout << "잘못된 선택입니다. 다시 선택하세요." << endl;
                continue;
            }

            Piece selectedPiece = currentCapturedPieces[pieceIndex - 1];
            vector<pair<int, int>> validPositions = getValidPlacementPositions(board, currentPlayer);

            if (validPositions.empty()) {
                cout << "배치 가능한 위치가 없습니다. 턴을 종료합니다." << endl;
                continue;
            }

            cout << "배치 가능한 위치는 다음과 같습니다:" << endl;
            for (size_t i = 0; i < validPositions.size(); ++i) {
                cout << i + 1 << ": 좌표 (" << validPositions[i].second << ", " << validPositions[i].first << ")" << endl;
            }

            int positionChoice;
            cout << "배치할 위치를 선택하세요: ";
            cin >> positionChoice;

            if (positionChoice < 1 || positionChoice > validPositions.size()) {
                cout << "잘못된 선택입니다. 다시 선택하세요." << endl;
                continue;
            }

            int bx = validPositions[positionChoice - 1].first;
            int by = validPositions[positionChoice - 1].second;

            selectedPiece.owner = static_cast<Player>(currentPlayer);
            selectedPiece.id = pieceCounters[currentPlayer]++;
            board[by][bx] = selectedPiece;
            currentCapturedPieces.erase(currentCapturedPieces.begin() + (pieceIndex - 1));

            cout << "말을 (" << by << ", " << bx << ")에 배치했습니다." << endl;
            currentPlayer = (currentPlayer % 4) + 1;
            continue;
        }

        if (actionChoice != 1) {
            cout << "잘못된 선택입니다. 다시 입력하세요." << endl;
            continue;
        }

        // 기존 말 이동 로직
        cout << "플레이어 P" << currentPlayer << "의 기물 리스트:" << endl;
        vector<pair<Piece, pair<int, int>>> playerPieces;

        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int x = 0; x < BOARD_SIZE; ++x) {
                if (board[y][x].owner == static_cast<Player>(currentPlayer)) {
                    playerPieces.push_back({board[y][x], {x, y}});
                    cout << playerPieces.size() << ": " << pieceTypeToString(board[y][x].type)
                         << " (좌표: " << y << ", " << x << ")" << endl;
                }
            }
        }

        int pieceChoice;
        cout << "이동할 기물을 선택하세요: ";
        cin >> pieceChoice;

        if (pieceChoice < 1 || pieceChoice > playerPieces.size()) {
            cout << "잘못된 선택입니다. 다시 선택하세요." << endl;
            continue;
        }

        Piece selectedPiece = playerPieces[pieceChoice - 1].first;
        int sx = playerPieces[pieceChoice - 1].second.first;
        int sy = playerPieces[pieceChoice - 1].second.second;

        cout << "선택한 기물 위치: (" << sy << ", " << sx << ")" << endl;

        int moveDirection;
        cout << "이동 방향을 선택하세요: ";
        if (selectedPiece.type == KING) {
            cout << "1: 위, 2: 아래, 3: 좌, 4: 우, 5: 좌상, 6: 우상, 7: 좌하, 8: 우하" << endl;
        } else if (selectedPiece.type == BISHOP) {
            cout << "5: 좌상, 6: 우상, 7: 좌하, 8: 우하" << endl;
        } else if (selectedPiece.type == ROOK) {
            cout << "1: 위, 2: 아래, 3: 좌, 4: 우" << endl;
        }
        cin >> moveDirection;

        int dx = sx, dy = sy;
        switch (moveDirection) {
            case 1: dy++; break;
            case 2: dy--; break;
            case 3: dx--; break;
            case 4: dx++; break;
            case 5: dy++; dx--; break;
            case 6: dy++; dx++; break;
            case 7: dy--; dx--; break;
            case 8: dy--; dx++; break;
            default:
                cout << "잘못된 방향입니다. 다시 입력하세요." << endl;
                continue;
        }

        if (!isValidMove(board, sx, sy, dx, dy, selectedPiece.type, static_cast<Player>(currentPlayer))) {
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
