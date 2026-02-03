#include "chess.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
void push_move(Pos pos) {
  if (valid_moves.size == 63) {
    fprintf(stderr, "WHAT THE FUCK"); // too lazy to realloc for now
    exit(1);
  }

  valid_moves.pos[valid_moves.size] = (Pos){pos.gx, pos.gy};
  valid_moves.size++;
}
void clear_glmovarr() { free(valid_moves.pos); }
void new_glmovarr() {
  valid_moves.pos = malloc(sizeof(Pos) * 64);
  valid_moves.size = 0;
}
bool valid_move(Pos pos) {
  for (short i = 0; i < valid_moves.size; i++) {
    if (samePos(pos, valid_moves.pos[i])) {
      return true;
    }
  }
  return false;
}
