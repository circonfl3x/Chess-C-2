#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
void fillBoard(Board *b) {
  for (uint x = 0; x < 8; x++) {
    for (uint y = 0; y < 8; y++) {
      b->cell[x][y].color = x % 2 == (y % 2 == 0 ? 0 : 1) ? CWHITE : CBLACK;
      b->cell[x][y].pos.gx = x;
      b->cell[x][y].pos.gy = y;
    }
  }
}
Cell *getCell(Board *b, uint x, uint y) {
  if (x > BWIDTH || y > BHEIGHT) {
    fprintf(stderr, "Cannot get cell data out of bounds");
    return NULL;
  }
  return &b->cell[x][y];
}
void loadTextures() {
  Image w_p = LoadImage("pieces/WP.png");
  Image b_p = LoadImage("pieces/BP.png");
  w_pawn = LoadTextureFromImage(w_p);
  b_pawn = LoadTextureFromImage(b_p);
  UnloadImage(w_p);
  UnloadImage(b_p);

  Image w_r = LoadImage("pieces/WR.png");
  Image b_r = LoadImage("pieces/BR.png");

  w_rook = LoadTextureFromImage(w_r);
  b_rook = LoadTextureFromImage(b_r);
  UnloadImage(w_r);
  UnloadImage(b_r);

  Image w_b = LoadImage("pieces/WB.png");
  Image b_b = LoadImage("pieces/BB.png");

  w_bishop = LoadTextureFromImage(w_b);
  b_bishop = LoadTextureFromImage(b_b);
  UnloadImage(w_b);
  UnloadImage(b_b);

  Image w_n = LoadImage("pieces/WN.png");
  Image b_n = LoadImage("pieces/BN.png");
  w_knight = LoadTextureFromImage(w_n);
  b_knight = LoadTextureFromImage(b_n);
  UnloadImage(w_n);
  UnloadImage(b_n);
  Image w_k = LoadImage("pieces/WK.png");
  Image b_k = LoadImage("pieces/BK.png");
  w_king = LoadTextureFromImage(w_k);
  b_king = LoadTextureFromImage(b_k);
  UnloadImage(w_k);
  UnloadImage(b_k);

  Image w_q = LoadImage("pieces/WQ.png");
  Image b_q = LoadImage("pieces/BQ.png");
  w_queen = LoadTextureFromImage(w_q);
  b_queen = LoadTextureFromImage(b_q);
  UnloadImage(w_q);
  UnloadImage(b_q);
}
void unloadTextures() {
  UnloadTexture(w_pawn);
  UnloadTexture(b_pawn);
  UnloadTexture(w_rook);
  UnloadTexture(b_rook);
  UnloadTexture(w_bishop);
  UnloadTexture(b_bishop);
  UnloadTexture(w_knight);
  UnloadTexture(b_knight);
  UnloadTexture(w_king);
  UnloadTexture(b_king);
  UnloadTexture(w_queen);
  UnloadTexture(b_queen);
}
bool isOccupied(Pieces *pieces, Pos *pos) {
  if (select_piece(pieces, pos))
    return true;
  return false;
}
bool isWOccupied(Pieces *pieces, Pos *pos) {
  Piece *p = select_piece(pieces, pos);
  if (!p)
    return false;
  if (p->color == CWHITE && p->isAlive)
    return true;
  return false;
}
bool isBOccupied(Pieces *pieces, Pos *pos) {

  Piece *p = select_piece(pieces, pos);
  if (!p)
    return false;
  if (p->color == CBLACK && p->isAlive)
    return true;
  return false;
}

bool isEnemyOccupied(COLOR color, Pieces *pieces, Pos *pos) {
  if (color == CWHITE) {
    return isBOccupied(pieces, pos);
  }
  return isWOccupied(pieces, pos);
}

void drawSquare(int gx, int gy, Color color) {

  DrawRectangle(gx * CWIDTH, gy * CHEIGHT, CWIDTH, CHEIGHT, color);

  DrawRectangle(gx * CWIDTH, gy * CHEIGHT, OUTWIDTH, CHEIGHT, BLACK);
  DrawRectangle(gx * CWIDTH + CWIDTH - OUTWIDTH, gy * CHEIGHT, OUTWIDTH,
                CHEIGHT, BLACK);

  DrawRectangle(gx * CWIDTH, gy * CHEIGHT, CWIDTH, OUTHEIGHT, BLACK);
  DrawRectangle(gx * CWIDTH + CWIDTH, gy * CHEIGHT - OUTHEIGHT, CWIDTH,
                OUTHEIGHT, BLACK);
}
