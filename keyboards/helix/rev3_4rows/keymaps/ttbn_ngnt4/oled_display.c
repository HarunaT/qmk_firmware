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

#ifdef OLED_ENABLE

void render_layer_status(void) {
  oled_write_P(PSTR("LAYER: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
           oled_write_P(PSTR("QWERTY"), false);
           break;
        case _NAGINATA:
           oled_write_P(PSTR("NAGINATA"), false);
           break;
        case _NUMPAD:
           oled_write_P(PSTR("NUMPAD"), false);
           break;
        case _FN_LEFT:
           oled_write_P(PSTR("FN_LEFT"), false);
           break;
        case _FN_RGHT:
           oled_write_P(PSTR("FN_RGHT"), false);
           break;
        default:
           oled_write_P(PSTR("UNDEF-"), false);
           
    }
}

void render_status(void) {
  static const char layer_moji[5][4][6] PROGMEM ={{
      {0x95,0x96,0x97,0x98,0},
      {0xb5,0xb6,0xb7,0xb8,0},
      {0xd5,0xd6,0xd7,0xd8,0} // 薙
      },{
      {0x99,0x9a,0x9b,0x9c,0},
      {0xb9,0xba,0xbb,0xbc,0},
      {0xd9,0xda,0xdb,0xdc,0} // 數
      },{
      {0x88,0x89,0x8a,0x8b,0x8c,0},
      {0xa8,0xa9,0xaa,0xab,0xac,0},
      {0xc8,0xc9,0xca,0xcb,0xcc,0} //紋章
      },{
      {0x9d,0x9e,0x9f,0x01,0},
      {0xbd,0xbe,0xbf,0x02,0},
      {0xdd,0xde,0xdf,0x03,0} //寫
      },{
      {0x04,0x05,0x06,0x07,0},
      {0x08,0x09,0x0b,0x0c,0},
      {0x0d,0x0e,0x0f,0x10,0} //編
      }};

  void render_moji_12345(int gyou){
    oled_write_P( (IS_LAYER_ON(_NAGINATA) ? layer_moji[0][gyou] : PSTR("    ")), false);
    oled_write_P( (IS_LAYER_ON(_NUMPAD) ? layer_moji[1][gyou] : PSTR("    ")), false);
    if (IS_LAYER_ON(_FN_LEFT) || IS_LAYER_ON(_FN_RGHT)) {
      oled_write_P(layer_moji[2][gyou], true);
    } else {
      oled_write_P(layer_moji[2][gyou], false);
    }
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? layer_moji[3][gyou] : PSTR("    "), false);
    oled_write_P(led_state.num_lock ? PSTR("    ") : layer_moji[4][gyou], false);
    }

  render_moji_12345(0);
  render_moji_12345(1);
  render_moji_12345(2);
}

static void render_logo(void) {
  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  oled_write_P(helix_logo, false);
}


void oled_task_user(void) {
  if(is_keyboard_master()){
    render_status();
  }else{
    render_logo();
    render_layer_status();
  }
}

#endif