#include "game_typing.h"
#include "mini_game_util.h"

const uint8_t max_size = 22;
const char* use_char_list = "abcdefghijklmnopqestuvwxyz";

const char code_to_name[60];

uint16_t score = 0;
uint16_t miss = 0;
char view[84];
char question_buff[23] = "";

char get_char(void);

char get_char(void) {
	return use_char_list[random_num(0, strlen(use_char_list)-1)];
}

void typing_initialize(void){
	for (int i = 0; i < max_size; i++) {
		question_buff[i] = get_char();
	}
}

void typing_update(uint16_t keycode, keyrecord_t *record) {
  if (keycode >= 60) { return; }

	if (code_to_name[keycode] == question_buff[0]) {
		question_buff[max_size - 1] = get_char();
		memcpy(question_buff, &question_buff[1], (max_size-1)*sizeof(char));
		score++;
	} else {
		miss++;
	}

}

const char *typing_draw(void) {
	char blank = 0x20;
	char score_buff[21];
	char next_buff[21];

	memset(view, blank, sizeof(view)); 
	sprintf(next_buff, "next %c", question_buff[0]);
	sprintf(score_buff, "score %d  miss %d", score, miss);

	draw_row(0, view, next_buff);
	draw_row(1, view, score_buff);
	draw_row(3, view, question_buff);

	view[83] = 0x00;
	return view;
}

GameInterFace game_typing = {
	typing_initialize,
	typing_update,
	typing_draw,
};

