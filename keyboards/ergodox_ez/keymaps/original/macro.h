#ifndef ERGO_ORIGINAL_MACRO
#define ERGO_ORIGINAL_MACRO

#include QMK_KEYBOARD_H
#include "def.h"

#define RANGE_ERROR (DEVEL_STR_REPEAT_MAX + 1)

uint8_t in_range(uint8_t count, uint8_t max_size) {
	if (count > max_size) { return RANGE_ERROR; }
	return count;
}

uint8_t init_count(uint8_t state_count, uint8_t max_size) {
	uint8_t count = state_count - 1;
	if (in_range(count, max_size) == RANGE_ERROR) { return RANGE_ERROR; }
	return count;
}

void tap_dance_finish(const char* string_list[], uint8_t count) {
	if (count != RANGE_ERROR) {
		send_string(string_list[count]);
	}
}

void dance_comment(qk_tap_dance_state_t *state, void *user_data) {
	uint8_t count = init_count(state->count, COMM_OUT);
	tap_dance_finish(devel_comment_list, count);
};

void dance_p_key(qk_tap_dance_state_t *state, void *user_data) {
	uint8_t count = init_count(state->count, PUBLIC);
	tap_dance_finish(devel_p_key_list, count);
};

#endif

