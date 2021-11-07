/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// place overrides here
#define TAPPING_TERM 200
#define SSD1306OLED
#define MASTER_RIGHT
// If you need more program area, try select and reduce rgblight modes to use.

/*
// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif
*/

// 薙刀式の爲追記

#define NAGINATA_TATEGAKI
// #define NAGINATA_YOKOGAKI

#define NAGINATA_EDIT_WIN // JP106
#define UNICODE_SELECTED_MODES UC_WINC

#define NAGINATA_EDIT_MAC // US101
// Macはunicode入力を使わない
#define MAC_LIVE_CONVERSION // Macでライブ変換をオンにしている場合
#define PERMISSIVE_HOLD
// #define NAGINATA_EDIT_LINUX
// #define UNICODE_SELECTED_MODES UC_LNX

// #define NAGINATA_KOUCHI_SHIFT // シフトを後置でも有効にする

// 薙刀式の爲追記、此處迄
