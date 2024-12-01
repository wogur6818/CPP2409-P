#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "board.h"
using namespace std;

// 기물 타입 문자열 변환
string pieceTypeToString(PieceType type);
string centerText(const string& text, int width);

#endif
