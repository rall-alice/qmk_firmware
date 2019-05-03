#include QMK_KEYBOARD_H
#include <keymap_jp.h>
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _CURSOR 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  CURSOR,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define JP_HAT  JP_CIRC  // ^
#define JP_RO   KC_RO    // \, _ 

#define S_COPY  RGUI(KC_C)
#define S_PASTE RGUI(KC_V)



//Tap Dance Declarations
enum {
  T_CD = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [T_CD]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_DOT),
// Other declarations would go here, separated by commas, if you have them
};


/* template
    _______, _______,_______, _______,_______, _______,   _______,                        _______, _______, _______, _______, _______, _______, _______, \
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |   [  |                    |   ]  |   6  |   7  |   8  |   9  |   0  |Pscree|
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  `   |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |  Del |                    | Bksp |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | Space|                    | Enter|   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|      ||||||||      | Enter| Raise|||||||| Left | Down |  Up  | Right|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,                        XXXXXXX,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_YEN, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    JP_HAT,                         KC_MINS , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_ESC,                         TD(T_CD), KC_H,    KC_J,    KC_K,    KC_L,    JP_COLN, KC_SCLN, \
    MO(_CURSOR),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LSFT,                       KC_RCTL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, JP_RO, \
    RAISE, KC_LALT, KC_LGUI, KC_LANG2,          KC_BSPC ,KC_SPC,  LOWER,         RAISE, KC_RSFT, KC_ENT,            KC_LANG1, KC_DOWN, KC_UP,   KC_RGHT  \
  ),

  /* Lower   */
  [_LOWER] = LAYOUT(
    _______, _______,_______, _______,_______, _______,   _______,                        _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ , \
    _______, _______,_______, _______,_______, _______,   _______,                        _______, _______, _______, _______, _______, _______, _______, \
    _______, _______,_______, _______,_______, _______,   _______,                        _______, _______, _______, _______, _______, _______, _______, \
    _______, _______,_______, _______,         _______,   _______ ,_______,      _______,_______ , _______,         _______, _______, _______, _______   \
  ),

  /* Raise   */
  [_RAISE] = LAYOUT(
    _______, KC_F1,  KC_F2,   KC_F3,  KC_F4,   KC_F5,     _______,                        _______, KC_F6,   KC_F7,   KC_F8,  KC_F9,   KC_F10,  _______,  \
    _______, JP_QUOT,JP_DQT,  JP_EXLM,_______, _______,   _______,                        _______, _______, JP_LPRN, JP_RPRN,_______, JP_PERC, _______, \
    _______, JP_AT,  JP_SCLN, JP_DLR, _______, _______,   _______,                        _______, JP_HASH, JP_LBRC, JP_RBRC,_______, _______, _______, \
    _______, _______,_______, JP_COLN,_______, JP_YEN,    _______,                        _______, JP_AMPR, JP_LCBR, JP_RCBR,_______, _______, _______, \
    _______, _______,_______, _______,         _______,   _______ ,_______,      _______,_______ , _______,         _______, _______, _______, _______   \
  ),

  /* Cursor   */
  [_CURSOR] = LAYOUT(
    _______, _______,_______, _______,_______, _______,   _______,                        _______, _______, _______, _______, _______, _______, _______, \
    _______, _______,_______, _______,_______, _______,   _______,                        _______, _______, _______, _______, _______, _______, _______, \
    _______, _______,_______, _______,_______, _______,   _______,                        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______, \
    _______, _______,_______, _______,_______, _______,   _______,                        _______, _______, _______, _______, _______, _______, _______, \
    _______, _______,_______, _______,         _______,   _______ ,_______,      _______,_______ , _______,         _______, _______, _______, _______   \
  ),


  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    RESET,   _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______,_______, _______,         _______,   _______ ,_______,      _______,_______ , _______,         _______, _______, _______, _______   \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
