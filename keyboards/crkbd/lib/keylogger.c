#include <stdio.h>
#include "crkbd.h"

char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

const char* code_to_name_verboze[] = {
// 0x00
" ", " ", " ", " ", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l",
// 0x10
"m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2",
// 0x20
"3", "4", "5", "6", "7", "8", "9", "0", "Ret", "Esc", "Bs", "Tab", "Spc", "-", "=", "[",
// 0x30
"]", "\\", "#", ";", "'", " ", ",", ".", "/", "Caps", "F1", "F2", "F3", "F4", "F5", "F6",
// 0x40
"F7", "F8", "F9", "F10", "F11", "F12", "PrS", "Pau", "Ins", "Hom", "PUp", "Del", "End", "PDn", "Rgt",
// 0x50
"Lft", "Dwn", "Up", "PNL", "P/", "P*", "P-", "P+", "PRt","P1", "P2", "P3", "P4", "P5", "P6", "P7",
// 0x60
"P8", "P9", "P0", "P.", "Yen", "App", "Pow", "P=", "F13", "F14", "F15", "F16", "F17","F18", "F19", "F20",
// 0x70
"F21", "F22", "F23", "F24", "Exe", "Hlp", "Mn", "Sct", "Stp", "Agn", "Und", "Cut", "Cpy", "Pst", "Fnd", "Mt",
// 0x80
"VUp", "VDw", "LCL", "LNL", "LSL", "Cmm", "Equ", "In1", "In2", "In3", "In4", "In5","In6", "In7", "In8", "In9",
// 0x90
 "LN1","LN2", "LN3", "LN4", "LN5", "LN6", "LN7", "LN8", "LN9", "Alt", "Att", "Cnc", "Clr", "Pri", "Ret", "Sep",
// 0xa0
"Out", "Opr", "Clr", "CrS", "ExS", "", "", "", "", "", "", "",
// 0xb0
"00", "000", "TS", "DS", "CU", "CSU", "P(", "P)", "P{", "P}", "PTb", "PBs", "PA", "PB", "PC", "PD",
// 0xc0
"PE", "PF", "XOR", "P^", "P%", "P<", "P>", "P&", "P&&", "P|", "P||", "P:", "P#", "P ", "P@", "P!",
// 0xd0
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
// 0xe0
"LCt", "LSf", "LAl", "LGu", "RCt", "RSf", "RAl", "RGu"};


void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}
