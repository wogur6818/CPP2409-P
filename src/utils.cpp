#include "utils.h"

string pieceTypeToString(PieceType type) {
    switch (type) {
        case KING: return "king";
        case BISHOP: return "bishop";
        case ROOK: return "rook";
        default: return "unknown";
    }
}
