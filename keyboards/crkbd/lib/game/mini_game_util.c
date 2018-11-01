#include QMK_KEYBOARD_H
#include "mini_game_util.h"
#include <string.h>

uint8_t random_num(uint8_t min, uint8_t max) {
	return rand()%(max+1-min) + min;
}

void draw_row(uint8_t row, char* view, const char* str) {
	uint8_t copy_size = (strlen(str) > 21) ? 21 : strlen(str);
	memcpy(&view[row*21], str, copy_size);

}
