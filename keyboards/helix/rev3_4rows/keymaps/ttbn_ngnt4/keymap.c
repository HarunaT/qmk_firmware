/* Copyright 2020 yushakobo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Custom Shift Keys
#include "custom_shift_keys.h"
const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT , KC_EXLM}, // Shift . is !
    {KC_COMM, KC_QUES}, // Shift , is ?
    {KC_MINS, KC_SLSH }, // Shift - is /
    {KC_QUOT, KC_SCLN}, // Shift : is ; ... JISの:はQUOT
    {S(KC_7), S(KC_2)} // Shift ' is " ... JISの'はS7 "はS2
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY = 0,
// 薙刀式
    _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
    _NUMPAD,
    _FN_LEFT,
    _FN_RGHT
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SANDS = NG_SAFE_RANGE,
  EISU,
  KANA,
  NMPD
};

#define SANDS SFT_T(KC_SPC)
#define EISU LT(_FN_LEFT,KC_NO) //單打で英數、保持で機能面へ。
#define KANA LT(_FN_RGHT,KC_NO)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   Q  |   U  |   A  |   L  |  .!  |             |  -/  |  '"  |   S  |   C  |   K  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   J  |   P  |   O  |   N  |   B  |             |  ,?  |   I  |   H  |   T  |   V  |  :;  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   X  |   W  |   G  |   F  |   M  |             |   Z  |   E  |   R  |   D  |   Y  |  ]   |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * | Ctrl | Alt  | GUI  | NMPD | EISU |SandS | Bksp |Enter |SandS | KANA | JYEN |  @   |  [   |  _   |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_ESC, KC_Q,   KC_U,   KC_A, KC_L, KC_DOT,              KC_MINS, S(KC_7), KC_S, KC_C, KC_K, KC_MINS, \
      KC_TAB, KC_J,   KC_P,   KC_O, KC_N, KC_B,                KC_COMM, KC_I,    KC_H, KC_T, KC_V, KC_QUOT, \
      KC_LSFT,KC_X,   KC_W,   KC_G, KC_F, KC_M,                KC_Z,    KC_E,    KC_R, KC_D, KC_Y, KC_NUHS, \
      KC_LCTL,KC_LALT,KC_LGUI,NMPD, EISU, SANDS,KC_BSPC,KC_ENT,SANDS,KANA, KC_INT3,KC_LBRC,KC_RBRC,KC_INT1 \
      ),

// 薙刀式
  [_NAGINATA] = LAYOUT( \
      _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,                NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
      _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,                NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
      _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,                NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
      _______,_______,_______,_______,_______,NG_SHFT,_______,_______,NG_SHFT,_______,KC_COMM,KC_DOT, _______,_______ \
      ),
// 薙刀式

  /* Numpad
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   #  |   $  |   <  |   >  |   |  |             |   =  |   7  |   8  |   9  |   ^  | NUM  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   [  |   ]  |   (  |   )  |   \  |             |   -  |   4  |   5  |   6  |   *  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   %  |   &  |   {  |   }  |   ~  |             |   +  |   1  |   2  |   3  |   /  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      | Ent  |      |   0  |   ,  |   .  |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUMPAD] = LAYOUT( \
      _______,S(KC_3),S(KC_4),KC_LABK,KC_RABK,S(KC_INT3),             KC_PEQL,KC_P7,KC_P8,KC_P9,  KC_EQL, KC_NUM, \
      _______,KC_RBRC,KC_NUHS,S(KC_8),S(KC_9),A(KC_INT3),             KC_PMNS,KC_P4,KC_P5,KC_P6,  KC_PAST,_______, \
      _______,S(KC_5),S(KC_6),KC_RCBR,KC_PIPE,KC_PLUS,                KC_PPLS,KC_P1,KC_P2,KC_P3,  KC_PSLS,_______, \
      _______,_______,_______,_______,_______,_______,_______,KC_PENT,_______,KC_P0,KC_COMM,KC_PDOT,_______,_______ \
      ),

  /* Function Left (EISU)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |GA+Esc|NG_WIN|LCGNRM|  Up  | TATE |CA+Del|             | VoUp | Home |  Up  | PgUp | TAYO |   `  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |NG_OS?|  Lt  |  Dn  |  Rt  | YOKO |             | VoDn |  Lt  |  Dn  |  Rt  | MLV  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |NG_MAC|LCGSWP|  Dn  |Enter | Del  |             | Mute | End  |  Dn  | PgDn | KOTI |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |Shift | CAPS |Enter |Shift |Space |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FN_LEFT] = LAYOUT( \
      LAG(KC_ESC),NGSW_WIN,CG_LNRM,KC_UP,  NG_TATE,LCA(KC_DEL),          KC_VOLU,KC_HOME,KC_UP,  KC_PGUP,NG_TAYO,KC_GRV, \
      _______,    NG_SHOS, KC_LEFT,KC_DOWN,KC_RGHT,NG_YOKO,              KC_VOLD,KC_LEFT,KC_DOWN,KC_RGHT,NG_MLV, _______, \
      _______,    NGSW_MAC,CG_LSWP,KC_DOWN,KC_ENT,KC_DEL,                KC_MUTE,KC_END, KC_DOWN,KC_PGDN,NG_KOTI,_______, \
      _______,   _______, _______,_______,_______,KC_LSFT,KC_CAPS,KC_ENT,KC_RSFT,KC_SPC,_______,_______,_______,_______ \
      ),

  /* Function Right (KANA)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |   ,  |   .  |   0  |  F13 |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |Space |Shift |      |Enter |Shift |      |      | PSCR |  F15 |  F14 |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FN_RGHT] =  LAYOUT( \
      _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                   KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,KC_F11, \
      _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,  KC_F12, \
      _______,_______,_______,_______,_______,_______,                 _______,_______,KC_COMM,KC_DOT ,KC_0,  KC_F13, \
      _______,_______,_______,_______,KC_SPC ,KC_LSFT,_______,KC_ENT,KC_RSFT,_______,_______,KC_PSCR,KC_F15,KC_F14 \
      )
};

uint16_t NMPD_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_shift_keys(keycode, record)) { return false; } // Custom Shift Keysの爲の1行
  switch (keycode) {
     // 薙刀式
    case EISU:
      if (record->tap.count && record->event.pressed) {  //單打の擧動を設定
        naginata_off();
      } else if (record->event.pressed) {  //保持時の擧動を設定
        layer_on(_FN_LEFT);
      } else {  //離した時の擧動を設定
        layer_off(_FN_LEFT);
      }
      return false;
      break;
    case KANA:
      if (record->tap.count && record->event.pressed) {  //單打の擧動を設定
        naginata_on();
      } else if (record->event.pressed) {  //保持時の擧動を設定
        layer_on(_FN_RGHT);
      } else {  //離した時の擧動を設定
        layer_off(_FN_RGHT);
      }
      return false;
      break;
      // 薙刀式

    case NMPD:
      if(record->event.pressed){
        NMPD_timer = timer_read();
        layer_on(2);
      } else {
        layer_off(2);
        if (timer_elapsed(NMPD_timer) < TAPPING_TERM) {
          layer_on(2);
        }
      }
      return false;
      break;
  }

  // 薙刀式
    if (!process_naginata(keycode, record))
      return false;
  // 薙刀式

  return true;
}

void matrix_init_user(void) {

  // 薙刀式
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式

}

#define SPLIT_TRANSPORT_MIRROR
bool should_process_keypress(void){return true;}
