#include QMK_KEYBOARD_H
#include "mini_game.h"
#include "game_interface.h"
#include "game_logo.h"
#include "game_collect.h"
#include "game_typing.h"
#include <time.h>

// extern 
GameInterface game_collect;
GameInterface game_typing;

GameType game_type = LOGO;
GameInterface game_list[GAME_MAX] = {};

void minigame_change(GameType type) {
  game_type = type;
}

void minigame_initialize(void) {
  srand(time(NULL));
  game_list[LOGO] = game_logo;
  game_list[COLLECT] = game_collect;
  game_list[TYPING] = game_typing;
  for (int i=0; i<GAME_MAX; i++) {
    game_list[i].initialize();
  }
}

void minigame_update(uint16_t keycode, keyrecord_t *record) {
  game_list[game_type].update(keycode, record);
}

const char *minigame_render(void) {
  return game_list[game_type].render();
}

