#include "chess.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void coords_to_gcoords(Pos *pos, int x, int y) {

  pos->gx = floor((float)x / CWIDTH);
  pos->gy = floor((float)y / CHEIGHT);
}
