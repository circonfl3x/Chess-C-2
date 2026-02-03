#pragma once
#include <raylib.h>
#define WIDTH 800
#define HEIGHT 800
#define CWIDTH 100
#define CHEIGHT 100
#define BWIDTH 8
#define BHEIGHT 8
#define PWIDTH 32
#define PHEIGHT 32
#define PNUM 16
#define OUTWIDTH 1
#define OUTHEIGHT 1
#define CSQUARE PURPLE
#define CMOVE RED
// gx and gy are defined as arbitrary x and y positions relative
// to the number of squares
typedef enum { CWHITE = 0, CBLACK } COLOR;
typedef enum { PAWN = 0, KNIGHT, BISHOP, ROOK, KING, QUEEN } PIECE_T;
typedef struct {
  unsigned int gx;
  unsigned int gy;
} Pos;
typedef struct {
  Pos *pos;
  short size;
} Moves;
typedef struct {
  Pos pos;
  COLOR color;

} Cell;
typedef struct {
  Cell cell[8][8];
} Board;
typedef struct {
  PIECE_T piece_type;
  Cell *occupies;
  COLOR color;
  bool isAlive;

} Piece;
typedef struct {
  // order of filling will be first 8 pawns
  // 2 horses
  // 2 bishops
  // 2 rooks
  // king
  // queen
  Piece w_pieces[PNUM];
  Piece b_pieces[PNUM];
} Pieces;

void fillBoard(Board *b);
Cell *getCell(Board *b, unsigned int x, unsigned int y);
void fillPieces(Pieces *p, Board *b);
void loadTextures();
void unloadTextures();
extern Texture2D w_pawn, b_pawn, w_rook, b_rook, w_bishop, b_bishop, w_queen,
    b_queen, w_knight, b_knight, w_king, b_king;
extern Pos *current_pos;
extern Piece *current_piece;
extern Moves valid_moves; // implicitly has a max (default) val of 64
extern Pos all_knight_valid[8], all_pawn_valid[4], all_rook_valid[32],
    all_queen_valid[32], all_king_valid[10], all_bishop_valid[32];
bool samePos(Pos a, Pos b);
void coords_to_gcoords(Pos *pos, int x, int y);
Piece *select_piece(Pieces *pieces, Pos *pos);

bool isOccupied(Pieces *pieces, Pos *pos);
bool isWOccupied(Pieces *pieces, Pos *pos);
bool isBOccupied(Pieces *pieces, Pos *pos);
bool isEnemyOccupied(COLOR color, Pieces *pieces, Pos *pos);
void drawMoves(Piece *current_piece, Pieces *pieces);
void drawSquare(int gx, int gy, Color color);
bool canMove(Piece *current_piece, Pieces *pieces, Pos new_pos);
void setUpPositions();
void gen_all_possible();

void push_move(Pos pos);
void new_glmovarr();
void clear_glmovarr();
bool valid_move(Pos pos);
