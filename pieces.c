#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
Piece *select_piece(Pieces *pieces, Pos *pos) {

  Piece *ret = NULL;
  for (int i = 0; i < PNUM; i++) {
    if (samePos(pieces->w_pieces[i].occupies->pos, *pos)) {
      ret = &pieces->w_pieces[i];
      break;
    }
    if (samePos(pieces->b_pieces[i].occupies->pos, *pos)) {
      ret = &pieces->b_pieces[i];
      break;
    }
  }
  return ret;
}
void fillPieces(Pieces *p, Board *b) {

  for (int i = 0; i < PNUM; i++) {
    p->w_pieces[i].color = CWHITE;
    p->w_pieces[i].isAlive = true;
    p->b_pieces[i].color = CBLACK;
    p->b_pieces[i].isAlive = true;
  }
  for (int i = 0; i < 8; i++) {
    p->w_pieces[i].piece_type = PAWN;
    p->w_pieces[i].occupies = getCell(b, i, 6);

    p->b_pieces[i].piece_type = PAWN;
    p->b_pieces[i].occupies = getCell(b, i, 1);
  }
  // WHITE BISHOPS
  p->w_pieces[8].piece_type = BISHOP;
  p->w_pieces[8].occupies = getCell(b, 2, 7);

  p->w_pieces[9].piece_type = BISHOP;
  p->w_pieces[9].occupies = getCell(b, 5, 7);

  // BLACK BISHOPS
  p->b_pieces[8].piece_type = BISHOP;
  p->b_pieces[8].occupies = getCell(b, 2, 0);

  p->b_pieces[9].piece_type = BISHOP;
  p->b_pieces[9].occupies = getCell(b, 5, 0);

  // WHITE KNIGHTS
  p->w_pieces[10].piece_type = KNIGHT;
  p->w_pieces[10].occupies = getCell(b, 1, 7);

  p->w_pieces[11].piece_type = KNIGHT;
  p->w_pieces[11].occupies = getCell(b, 6, 7);
  // BLACK KNIGHTS
  p->b_pieces[10].piece_type = KNIGHT;
  p->b_pieces[10].occupies = getCell(b, 1, 0);

  p->b_pieces[11].piece_type = KNIGHT;
  p->b_pieces[11].occupies = getCell(b, 6, 0);

  // WHITE ROOKS

  p->w_pieces[12].piece_type = ROOK;
  p->w_pieces[12].occupies = getCell(b, 0, 7);

  p->w_pieces[13].piece_type = ROOK;
  p->w_pieces[13].occupies = getCell(b, 7, 7);
  // BLACK ROOKS
  p->b_pieces[12].piece_type = ROOK;
  p->b_pieces[12].occupies = getCell(b, 7, 0);
  p->b_pieces[13].piece_type = ROOK;
  p->b_pieces[13].occupies = getCell(b, 0, 0);

  // WHITE KING AND QUEEN
  p->w_pieces[14].piece_type = KING;
  p->w_pieces[14].occupies = getCell(b, 4, 7);

  p->w_pieces[15].piece_type = QUEEN;
  p->w_pieces[15].occupies = getCell(b, 3, 7);

  // BLACK KING AND QUEEN
  p->b_pieces[14].piece_type = KING;
  p->b_pieces[14].occupies = getCell(b, 4, 0);

  p->b_pieces[15].piece_type = QUEEN;
  p->b_pieces[15].occupies = getCell(b, 3, 0);
}

bool samePos(Pos a, Pos b) { return a.gx == b.gx && a.gy == b.gy; }
Piece *get_piece_at(Pieces *p, Pos pos) {
  for (int i = 0; i < PNUM; i++) {
    if (samePos(p->w_pieces[i].occupies->pos, pos)) {
      return &p->w_pieces[i];
    }
    if (samePos(p->b_pieces[i].occupies->pos, pos)) {
      return &p->b_pieces[i];
    }
  }
  return NULL;
}

void drawMoves(Piece *current_piece, Pieces *pieces) {
  clear_glmovarr();
  new_glmovarr();
  bool blocked = false;
  if (!current_piece)
    return;
  // PAWN
  if (current_piece->piece_type == PAWN) {
    Pos tmp = current_piece->occupies->pos;
    tmp.gy += (current_piece->color == CWHITE ? -1 : 1);
    bool blocked = true;
    // check if blocked
    tmp.gx -= tmp.gx > 0 ? 1 : 0;
    for (; tmp.gx < current_piece->occupies->pos.gx + 2; tmp.gx++) {
      if (tmp.gx == current_piece->occupies->pos.gx) {
        if (!isOccupied(pieces, &tmp)) {
          drawSquare(tmp.gx, tmp.gy, RED);
          push_move(tmp);
          blocked = false;
        }
      } else if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
      }
    }
    // double move bb
    if (current_piece->occupies->pos.gy ==
        (current_piece->color == CWHITE ? 6 : 1)) {

      tmp.gy += (current_piece->color == CWHITE ? -1 : 1);
      tmp.gx = current_piece->occupies->pos.gx;
      if (!isOccupied(pieces, &tmp) && !blocked) {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }

  }

  // ROOK
  else if (current_piece->piece_type == ROOK) {

    Pos tmp = current_piece->occupies->pos;
    // draw empty positions to the right
    for (int i = current_piece->occupies->pos.gx + 1; i <= BWIDTH; i++) {

      tmp.gx = i;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;

      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }

    for (int i = current_piece->occupies->pos.gx - 1; i >= 0; i--) {

      tmp.gx = i;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;

      }

      else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
    // VERTICAL LINES
    tmp = current_piece->occupies->pos;

    for (int i = current_piece->occupies->pos.gy + 1; i <= BHEIGHT; i++) {

      tmp.gy = i;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;

      }

      else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }

    for (int i = current_piece->occupies->pos.gy - 1; i >= 0; i--) {

      tmp.gy = i;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;

      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
  }

  // BISHOP
  else if (current_piece->piece_type == BISHOP) {

    Pos tmp = current_piece->occupies->pos;
    for (int x = current_piece->occupies->pos.gx + 1,
             y = current_piece->occupies->pos.gy + 1;
         x <= BWIDTH && y <= BHEIGHT; x++, y++) {
      tmp.gx = x;
      tmp.gy = y;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;
      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }

    for (int x = current_piece->occupies->pos.gx - 1,
             y = current_piece->occupies->pos.gy + 1;
         x >= 0 && y <= BHEIGHT; x--, y++) {
      tmp.gx = x;
      tmp.gy = y;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;
      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }

    for (int x = current_piece->occupies->pos.gx - 1,
             y = current_piece->occupies->pos.gy - 1;
         x >= 0 && y >= 0; x--, y--) {
      tmp.gx = x;
      tmp.gy = y;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;
      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
    for (int x = current_piece->occupies->pos.gx + 1,
             y = current_piece->occupies->pos.gy - 1;
         x <= BWIDTH && y >= 0; x++, y--) {
      tmp.gx = x;
      tmp.gy = y;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;
      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
  }
  // KING
  else if (current_piece->piece_type == KING) {
    Pos tmp = current_piece->occupies->pos;

    // top row
    tmp.gy -= tmp.gy > 0 ? 1 : 0;
    tmp.gx -= tmp.gx > 0 ? 1 : 0;
    int init = tmp.gx;
    for (; tmp.gy <= (current_piece->occupies->pos.gy + 1 > BHEIGHT
                          ? BHEIGHT
                          : current_piece->occupies->pos.gy + 1);
         tmp.gy++) {
      for (; tmp.gx <= (current_piece->occupies->pos.gx + 1 > BWIDTH
                            ? BWIDTH
                            : current_piece->occupies->pos.gx + 1);
           tmp.gx++) {
        if (!isOccupied(pieces, &tmp)) {
          drawSquare(tmp.gx, tmp.gy, RED);
          push_move(tmp);
        } else if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
          drawSquare(tmp.gx, tmp.gy, GREEN);
          push_move(tmp);
        } else
          ;
      }
      tmp.gx = init;
    }
  }
  // QUEEN
  else if (current_piece->piece_type == QUEEN) {
    Pos tmp = current_piece->occupies->pos;
    // draw empty positions to the right
    for (int i = current_piece->occupies->pos.gx + 1; i <= BWIDTH; i++) {

      tmp.gx = i;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;

      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }

    for (int i = current_piece->occupies->pos.gx - 1; i >= 0; i--) {

      tmp.gx = i;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;

      }

      else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
    // VERTICAL LINES
    tmp = current_piece->occupies->pos;

    for (int i = current_piece->occupies->pos.gy + 1; i <= BHEIGHT; i++) {

      tmp.gy = i;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;

      }

      else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }

    for (int i = current_piece->occupies->pos.gy - 1; i >= 0; i--) {

      tmp.gy = i;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;

      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
    for (int x = current_piece->occupies->pos.gx + 1,
             y = current_piece->occupies->pos.gy + 1;
         x <= BWIDTH && y <= BHEIGHT; x++, y++) {
      tmp.gx = x;
      tmp.gy = y;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;
      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }

    for (int x = current_piece->occupies->pos.gx - 1,
             y = current_piece->occupies->pos.gy + 1;
         x >= 0 && y <= BHEIGHT; x--, y++) {
      tmp.gx = x;
      tmp.gy = y;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;
      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
    for (int x = current_piece->occupies->pos.gx - 1,
             y = current_piece->occupies->pos.gy - 1;
         x >= 0 && y >= 0; x--, y--) {
      tmp.gx = x;
      tmp.gy = y;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;
      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
    for (int x = current_piece->occupies->pos.gx + 1,
             y = current_piece->occupies->pos.gy - 1;
         x <= BWIDTH && y >= 0; x++, y--) {
      tmp.gx = x;
      tmp.gy = y;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {
        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
        break;
      } else if (isOccupied(pieces, &tmp))
        break;
      else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
    }
  } else if (current_piece->piece_type == KNIGHT) {
    Pos tmp = current_piece->occupies->pos;
    Pos *valid = all_knight_valid;

    for (int i = 0; i < 8; i++) {
      tmp.gx += valid[i].gx;
      tmp.gy += valid[i].gy;
      if (isEnemyOccupied(current_piece->color, pieces, &tmp)) {

        drawSquare(tmp.gx, tmp.gy, GREEN);
        push_move(tmp);
      } else if (isOccupied(pieces, &tmp)) {
      } else {
        drawSquare(tmp.gx, tmp.gy, RED);
        push_move(tmp);
      }
      tmp = current_piece->occupies->pos;
    }
  }
}
void setUpPositions() {
  Pos *valid = all_knight_valid;
  valid[0] = (Pos){2, 1};
  valid[1] = (Pos){1, 2};

  valid[2] = (Pos){-1, 2};
  valid[3] = (Pos){-2, 1};
  valid[4] = (Pos){-2, -1};
  valid[5] = (Pos){-1, -2};
  valid[6] = (Pos){1, -2};
  valid[7] = (Pos){2, -1};

  // PAWN
  valid = all_pawn_valid;
  valid[0] = (Pos){0, 1};
  valid[1] = (Pos){0, 2};
  valid[2] = (Pos){1, 1};
  valid[3] = (Pos){-1, 1};
}
