#pragma once

#include "game_interface.h"
#include <stdio.h>
#include <string.h>

extern GameInterface game_collect;

bool create_enemy(void);
bool hit_check(void);

typedef enum _facetype {
  NORMAL = 0,
  SAD,
  SMILE,
} Facetype;

typedef struct _mg_state {
  int8_t x;
  int8_t y;
  uint16_t score;
  Facetype face;
} MiniGameState;

typedef struct _enemy {
  int8_t x;
  int8_t y;
  uint8_t lost_at;
  bool enable;
} CollectEnemy;

