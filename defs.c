#include "chess.h"
Pos *current_pos;
Piece *current_piece;
Pos all_knight_valid[8], all_pawn_valid[4], all_rook_valid[32],
    all_queen_valid[32], all_king_valid[10], all_bishop_valid[32];
Texture2D w_pawn, b_pawn, w_rook, b_rook, w_bishop, b_bishop, w_queen, b_queen,
    w_knight, b_knight, w_king, b_king;

Moves valid_moves;
