#include "game_collect.h"
#include "mini_game_util.h"

const uint8_t player_size = 8;
const uint8_t max_x = 21;
const uint8_t max_y = 3;

typedef enum _facetype {
	NORMAL = 0,
	SAD,
	SMILE,
} Facetype;

const char face_list[][8] = {
	[NORMAL] = {0x28, 0x0b, 0x0c, 0x0d, 0x29, 0x0e, 0x0f, 0x10},
  [SAD]    = {0x28, 0xd5, 0xd8, 0xd6, 0xd8, 0x20, 0xd7, 0x29},
  [SMILE]  = {0x28, 0xd5, 0x07, 0xd6, 0x07, 0x20, 0xd7, 0x29}
};

bool create_enemy(void);
bool hit_check(void);

void collect_initialize(void);
void collect_update(uint16_t keycode, keyrecord_t *record);
const char *collect_draw(void);

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
} Enemy;

GameInterFace game_collect = {
	collect_initialize,
	collect_update,
	collect_draw,
};

MiniGameState gs = {4, 2, 0, NORMAL};
Enemy enemy = {0, 0, 0, 0};
char view[84];

bool create_enemy(void) {
	if (random_num(0, 5) == 0) {
		enemy.x = random_num(0, max_x - 1);
		enemy.y = random_num(1, max_y);
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

	if (gs.y == enemy.y &&
			(gs.x <= enemy.x &&
			(gs.x+player_size) >= enemy.x)
	) {
		return 1;
	}

	return 0;
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

	gs.face = 0;
	if (gs.x < 0) { gs.x = 0; gs.face = SAD; }
	else if(gs.x > 12) { gs.x = 12; gs.face = SAD; }
	if (gs.y < 1) { gs.y = 1; gs.face = SAD; }
	else if(gs.y > max_y) { gs.y = max_y; gs.face = SAD; }

	if (!enemy.enable) {
		create_enemy();
	}

	if (hit_check()) {
		enemy.enable = 0;
		gs.score++;
		gs.face = SMILE;
	}

}

const char *collect_draw(void) {

	// char base = 0x30;
	char blank = 0x20;

	memset(view, blank, sizeof(view)); 

	char score_buff[21];
	sprintf(score_buff, "score %d", gs.score);
	strncpy(view, score_buff, strlen(score_buff));

	int enemy_pos = enemy.y * 21 + enemy.x;
	int pos = gs.y * 21 + gs.x;
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
	
	strncpy(&view[pos], face_list[face], player_size);

	if (enemy.enable) {
		view[enemy_pos] = 0x01;
	}

	view[83] = 0x00;
	return view;
}

