#include "utils.h"
#include <iomanip>
#include <sstream>

string pieceTypeToString(PieceType type) {
    switch (type) {
        case KING: return "king";
        case BISHOP: return "bishop";
        case ROOK: return "rook";
        default: return "";
    }
}

string centerText(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    string centeredText = string(padding, ' ') + text + string(padding, ' ');
    if (centeredText.length() < width) {
        centeredText += " ";
    }
    return centeredText;
}
