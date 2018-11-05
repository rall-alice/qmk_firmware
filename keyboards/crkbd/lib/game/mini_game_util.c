#include QMK_KEYBOARD_H
#include "mini_game_util.h"

uint8_t random_num(uint8_t min, uint8_t max) {
  return rand()%(max+1-min) + min;
}

void game_render_row(uint8_t row, char* buff, const char* str) {
  if (MatrixRows <= row) { return; }
  uint8_t copy_size = (strlen(str) > MatrixCols) ? MatrixCols: strlen(str);
  memcpy(&buff[row*MatrixCols], str, copy_size);
}
