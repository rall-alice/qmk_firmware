#include "game_collect.h"
#include "mini_game_util.h"

#define PlayerSize 8
#define MaxX (MatrixCols - PlayerSize - 1)
#define MaxY (MatrixRows - 1)

const char face_list[][8] = {
  [NORMAL] = {0x28, 0x0b, 0x0c, 0x0d, 0x29, 0x0e, 0x0f, 0x10},
  [SAD]    = {0x28, 0xd5, 0xd8, 0xd6, 0xd8, 0x20, 0xd7, 0x29},
  [SMILE]  = {0x28, 0xd5, 0x07, 0xd6, 0x07, 0x20, 0xd7, 0x29}
};

char render_buff[MaxDisplayChar];
MiniGameState gs = {4, 2, 0, NORMAL};
CollectEnemy enemy = {0, 0, 0, 0};

bool create_enemy(void) {
  if (random_num(0, 5) == 0) {
    enemy.x = random_num(0, MatrixCols - 1);
    enemy.y = random_num(1, MatrixRows - 1);
    enemy.enable = 1;
    enemy.lost_at = random_num(5, 20);
    return 1;
  }
  return 0;
}

bool hit_check(void) {
  if (!enemy.enable) {
    return 0;
  }

  return (gs.y == enemy.y && (gs.x <= enemy.x && (gs.x+PlayerSize) >= enemy.x));
}

void collect_initialize(void) {
  return;
}

void collect_update(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case 11: // h
      gs.x--;
      break;
    case 13: // j
      gs.y++;
      break;
    case 14: // k
      gs.y--;
      break;
    case 15: // l
      gs.x++;
      break;
    default:
      break;
  }

  gs.face = NORMAL;
  if (gs.x < 0)        { gs.x = 0;    gs.face = SAD; }
  else if(gs.x > MaxX) { gs.x = MaxX; gs.face = SAD; }
  if (gs.y < 1)        { gs.y = 1;    gs.face = SAD; }
  else if(gs.y > MaxY) { gs.y = MaxY; gs.face = SAD; }

  if (!enemy.enable) {
    create_enemy();
  }

  if (hit_check()) {
    enemy.enable = 0;
    gs.score++;
    gs.face = SMILE;
  }

}

const char *collect_render(void) {

  char blank = 0x20;

  memset(render_buff, blank, sizeof(render_buff)); 

  char score_buff[MatrixCols];
  sprintf(score_buff, "score %d", gs.score);
  game_render_row(0, render_buff, score_buff);

  int enemy_pos = enemy.y * MatrixCols + enemy.x;
  int pos = gs.y * MatrixCols + gs.x;
  Facetype face = gs.face;;

  switch (gs.face) {
    case SMILE:
    case SAD:
      face = gs.face;
      break;
    default:
      face = NORMAL;
      break;
  }

  strncpy(&render_buff[pos], face_list[face], PlayerSize);

  if (enemy.enable) {
    render_buff[enemy_pos] = 0x01;
  }

  render_buff[MaxDisplayChar - 1] = 0x00;
  return render_buff;
}

GameInterface game_collect = {
  collect_initialize,
  collect_update,
  collect_render,
};

