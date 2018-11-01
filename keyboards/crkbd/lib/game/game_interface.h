#pragma once

#include "crkbd.h"

typedef struct _game_interface {
	void (*initialize)(void);
	void (*update)(uint16_t keycode, keyrecord_t *record);
	const char *(*view)(void);
} GameInterFace;

