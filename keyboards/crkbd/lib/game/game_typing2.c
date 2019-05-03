#include "game_typing.h"
#include "mini_game_util.h"

#define MaxQuestionSize (MatrixCols + 1)

// extern
const char code_to_name[60];

const char* question_list[] = {
  "APPLE",
  "BREAD",
  "CANDY",
  "DONUT",
  "EGG",
  "FIG",
  "GRAPE",
  "HONEY",
  "ICE",
  "JELLY",
  "KIWI",
  "LEMON",
  "MARSHMALLOW",
  "NOODLE",
  "ORANGE",
  "PIZZA",
  "QUIZ",
  "RAMEN",
  "SUSHI",
  "TOAST",
  "UDON",
  "VIM",
  "WAFFLE",
  "XYLOCARP",
  "YAMS",
  "ZUCCHINI",
};

const char* use_char_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

uint16_t score = 0;
uint16_t miss = 0;
char render_buff[MaxDisplayChar];
char question_buff[MatrixCols + 2] = "";

const char* get_next(void) {
  return question_list[random_num(0, strlen(use_char_list)-1)];
}

void typing_initialize(void){
  const char* next = get_next();
  memcpy(question_buff, next, strlen(next)*sizeof(char));
}

void typing_update(uint16_t keycode, keyrecord_t *record) {
  if (keycode >= 60) { return; }

  if (code_to_name[keycode] == (question_buff[0] + 0x20)) { // Upper to Lower
    score++;
    memcpy(question_buff, &question_buff[1], (MaxQuestionSize-1)*sizeof(char));

    if (strlen(question_buff) <= 0) {
      const char* next = get_next();
      memcpy(question_buff, next, strlen(next)*sizeof(char));
    }
    
  } else {
    miss++;
  }

}

const char *typing_render(void) {
  char blank = 0x20;
  char score_buff[MatrixCols];
  char next_buff[MatrixCols];

  memset(render_buff, blank, sizeof(render_buff)); 
  sprintf(next_buff, "next %c", question_buff[0]);
  sprintf(score_buff, "score %d  miss %d", score, miss);

  matrix_row_copy(0, render_buff, next_buff);
  matrix_row_copy(1, render_buff, score_buff);
  matrix_row_copy(3, render_buff, question_buff);

  render_buff[MaxDisplayChar - 1] = 0x00;
  return render_buff;
}

GameInterface game_typing = {
  typing_initialize,
  typing_update,
  typing_render,
};

