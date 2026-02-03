#include "chess.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) {

  InitWindow(WIDTH, HEIGHT, "Chess");
  SetTargetFPS(60);
  Board board;
  Pieces pieces;
  fillBoard(&board);
  fillPieces(&pieces, &board);
  current_pos = malloc(sizeof(Pos));
  // coords_to_gcoords(current_pos, 1, 1);
  loadTextures();
  setUpPositions();
  uint cellWidth = WIDTH / BWIDTH;
  uint cellHeight = HEIGHT / BHEIGHT;

  while (!WindowShouldClose()) {
    BeginDrawing();
    for (uint x = 0; x < BWIDTH; x++) {
      for (uint y = 0; y < BHEIGHT; y++) {
        DrawRectangle(x * cellWidth, y * cellHeight, cellWidth, cellHeight,
                      board.cell[x][y].color == CWHITE ? BEIGE : BROWN);
      }
    }
    drawMoves(current_piece, &pieces);
    Vector2 mp = GetMousePosition();

    coords_to_gcoords(current_pos, mp.x, mp.y);
    // TODO [DONE]: pass this as a ref
    // to the function. An allocation
    // every frame is very wasteful
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (current_piece != NULL) {
        if (!valid_move(*current_pos)) {
          current_piece = NULL;
        } else if (current_piece->color == CWHITE) {
          if (isWOccupied(&pieces, current_pos))
            ;
          else if (isBOccupied(&pieces, current_pos)) {
            Piece *p = select_piece(&pieces, current_pos);
            p->occupies->pos.gx = -100;
            p->occupies->pos.gy = -100;

            p->isAlive = false;
            current_piece->occupies->pos.gx = current_pos->gx;
            current_piece->occupies->pos.gy = current_pos->gy;
          } else {
            current_piece->occupies->pos.gx = current_pos->gx;
            current_piece->occupies->pos.gy = current_pos->gy;
          }
          current_piece = NULL;
        } else if (current_piece->color == CBLACK) {

          if (isBOccupied(&pieces, current_pos))
            ;
          else if (isWOccupied(&pieces, current_pos)) {
            Piece *p = select_piece(&pieces, current_pos);
            p->occupies->pos.gx = -100;
            p->occupies->pos.gy = -100;
            p->isAlive = false;
            current_piece->occupies->pos.gx = current_pos->gx;
            current_piece->occupies->pos.gy = current_pos->gy;

          } else {
            current_piece->occupies->pos.gx = current_pos->gx;
            current_piece->occupies->pos.gy = current_pos->gy;
          }
          current_piece = NULL;
        }
      } else {
        current_piece = select_piece(&pieces, current_pos);
        // printf("%d\n", current_piece->piece_type);
      }
    }
    if (current_piece != NULL) {
      DrawRectangle(current_piece->occupies->pos.gx * cellWidth,
                    current_piece->occupies->pos.gy * cellHeight, cellWidth,
                    cellHeight, PURPLE);
    }
    DrawRectangle(current_pos->gx * cellWidth, current_pos->gy * cellHeight,
                  cellWidth, cellHeight, BLUE);

    for (int i = 0; i < 16; i++) {
      if (pieces.w_pieces[i].isAlive) {
        if (pieces.w_pieces[i].piece_type == PAWN) {
          DrawTexture(w_pawn, pieces.w_pieces[i].occupies->pos.gx * (cellWidth),

                      (pieces.w_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        } else if (pieces.w_pieces[i].piece_type == BISHOP) {
          DrawTexture(
              w_bishop, pieces.w_pieces[i].occupies->pos.gx * (cellWidth),

              (pieces.w_pieces[i].occupies->pos.gy) * cellHeight, WHITE);
        } else if (pieces.w_pieces[i].piece_type == ROOK) {
          DrawTexture(w_rook, pieces.w_pieces[i].occupies->pos.gx * (cellWidth),

                      (pieces.w_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        } else if (pieces.w_pieces[i].piece_type == KING) {
          DrawTexture(w_king, pieces.w_pieces[i].occupies->pos.gx * (cellWidth),

                      (pieces.w_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        } else if (pieces.w_pieces[i].piece_type == KNIGHT) {
          DrawTexture(
              w_knight, pieces.w_pieces[i].occupies->pos.gx * (cellWidth),

              (pieces.w_pieces[i].occupies->pos.gy) * cellHeight, WHITE);
        } else if (pieces.w_pieces[i].piece_type == QUEEN) {
          DrawTexture(
              w_queen, pieces.w_pieces[i].occupies->pos.gx * (cellWidth),

              (pieces.w_pieces[i].occupies->pos.gy) * cellHeight, WHITE);
        } else {
          DrawTexture(w_king, pieces.w_pieces[i].occupies->pos.gx * (cellWidth),

                      (pieces.w_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        }
      }
      if (pieces.b_pieces[i].isAlive) {
        if (pieces.b_pieces[i].piece_type == PAWN) {
          DrawTexture(b_pawn, pieces.b_pieces[i].occupies->pos.gx * (cellWidth),

                      (pieces.b_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        } else if (pieces.b_pieces[i].piece_type == BISHOP) {
          DrawTexture(
              b_bishop, pieces.b_pieces[i].occupies->pos.gx * (cellWidth),

              (pieces.b_pieces[i].occupies->pos.gy) * cellHeight, WHITE);
        } else if (pieces.b_pieces[i].piece_type == ROOK) {
          DrawTexture(b_rook, pieces.b_pieces[i].occupies->pos.gx * (cellWidth),

                      (pieces.b_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        } else if (pieces.b_pieces[i].piece_type == KING) {
          DrawTexture(b_king, pieces.b_pieces[i].occupies->pos.gx * (cellWidth),

                      (pieces.b_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        } else if (pieces.b_pieces[i].piece_type == KNIGHT) {
          DrawTexture(b_knight, pieces.b_pieces[i].occupies->pos.gx * cellWidth,

                      (pieces.b_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        } else if (pieces.b_pieces[i].piece_type == QUEEN) {
          DrawTexture(
              b_queen, pieces.b_pieces[i].occupies->pos.gx * (cellWidth),

              (pieces.b_pieces[i].occupies->pos.gy) * cellHeight, WHITE);
        } else {
          DrawTexture(b_king, pieces.b_pieces[i].occupies->pos.gx * (cellWidth),

                      (pieces.b_pieces[i].occupies->pos.gy) * cellHeight,
                      WHITE);
        }
      endloop:
      }
    }

    EndDrawing();
  }
  free(current_pos);
  unloadTextures();
}
