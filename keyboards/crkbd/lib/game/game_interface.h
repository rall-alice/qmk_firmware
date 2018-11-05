#pragma once

#include "crkbd.h"
#include "../../ssd1306.h"

#define MaxDisplayChar (int)(MatrixCols * MatrixRows)

typedef struct _game_interface {
  void (*initialize)(void);
  void (*update)(uint16_t keycode, keyrecord_t *record);
  const char *(*render)(void);
} GameInterface;

