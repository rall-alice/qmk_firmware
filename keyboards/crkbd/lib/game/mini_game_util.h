#pragma once
#include "../../ssd1306.h"
#include <string.h>

uint8_t random_num(uint8_t min, uint8_t max);
void matrix_row_copy(uint8_t row, char* buff, const char* str);
