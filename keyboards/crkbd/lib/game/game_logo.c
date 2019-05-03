#include "game_logo.h"
#include "mini_game_util.h"

const char *read_logo(void);

void logo_initialize(void){}

void logo_update(uint16_t keycode, keyrecord_t *record) {}

GameInterface game_logo = {
  logo_initialize,
  logo_update,
  read_logo,
};

