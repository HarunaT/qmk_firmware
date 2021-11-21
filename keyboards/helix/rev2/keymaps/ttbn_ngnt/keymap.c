#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

/*
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
*/

#ifdef SSD1306OLED
  #include "ssd1306.h"
  #include "drivers/oled/oled_driver.h"
#endif

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif


extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
// 薙刀式
    _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
    _NUMPAD,
    _FUNCTION
};

enum custom_keycodes {
  SANDS = NG_SAFE_RANGE,
  EISU,
  KANA,
  NMPD
};

//key name aliases
#define SANDS SFT_T(KC_SPC)
#define EISU LT(_FUNCTION,KC_NO) //單打で英數、保持で機能面へ。
#define KANA KC_LANG1
//#define NMPD KC_NO

/*
enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)
*/


#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |Space |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  ^   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  :   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |TO(Nu)| S(0) |   N  |   M  |   ,  |   .  |   /  |  ]   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Alt  | GUI  | S(V) |LN2/Fn|SandS | Bksp |Enter |SandS | KANA | JYEN |  @   |  [   |  _   |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_SPC, KC_1,   KC_2,   KC_3,   KC_4, KC_5,                 KC_6,  KC_7, KC_8,   KC_9,   KC_0,   KC_EQL, \
      KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R, KC_T,                 KC_Y,  KC_U, KC_I,   KC_O,   KC_P,   KC_MINS, \
      KC_TAB, KC_A,   KC_S,   KC_D,   KC_F, KC_G,                 KC_H,  KC_J, KC_K,   KC_L,   KC_SCLN,KC_QUOT, \
      KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V, KC_B, NMPD,   S(KC_0),KC_N,  KC_M, KC_COMM,KC_DOT, KC_SLSH,KC_NUHS, \
      KC_LCTL,KC_LALT,KC_LGUI,S(KC_V),EISU, SANDS,KC_BSPC,KC_ENT, SANDS, KANA, KC_JYEN,KC_LBRC,KC_RBRC,KC_RO \
      ),

// 薙刀式
  [_NAGINATA] = LAYOUT( \
      _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
      _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,                NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
      _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,                NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
      _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,_______,_______,NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
      _______,_______,_______,_______,_______,NG_SHFT,_______,_______,NG_SHFT,_______,_______,_______,_______,_______ \
      ),
// 薙刀式

  /* Numpad
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |   <  |   >  |   ?  |             |   /  |   .  |   =  |   /  |   *  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   !  |   "  |   [  |   ]  |   '  |             |   *  |   7  |   8  |   9  |   -  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   #  |   $  |   (  |   )  |   ~  |             |   -  |   4  |   5  |   6  |   +  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   %  |   &  |   {  |   }  |   |  |      | NLCK |   +  |   1  |   2  |   3  | Ent  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      | Ent  |      |   0  |   0  |   .  | Ent  |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUMPAD] = LAYOUT( \
      _______,_______,_______,KC_LABK,KC_RABK,KC_QUES,                   KC_PSLS, KC_PDOT,KC_PEQL,KC_PSLS,KC_PAST,_______, \
      _______,S(KC_1),S(KC_2),KC_RBRC,KC_NUHS,S(KC_7),                   KC_PAST,   KC_P7,KC_P8,  KC_P9,  KC_PMNS,_______, \
      _______,S(KC_3),S(KC_4),S(KC_8),S(KC_9),KC_PLUS,                   KC_PMNS,   KC_P4,KC_P5,  KC_P6,  KC_PPLS,_______, \
      _______,S(KC_5),S(KC_6),KC_RCBR,KC_PIPE,S(KC_JYEN),_______,KC_NLCK,KC_PPLS,   KC_P1,KC_P2,  KC_P3,  KC_PENT,_______, \
      _______,_______,_______,_______,_______,_______,   _______,KC_PENT,_______,   KC_P0,KC_P0,  KC_PDOT,KC_PENT,_______ \
      ),

  /* Function
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | CAPS |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |GA+Esc|NG_WIN|      |  Up  |      |CA+Del|             | VoUp | Home |  Up  | PgUp | TAYO | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |NG_MAC|  Lt  |  Dn  |  Rt  | S(^) |             | VoDn |  Lt  |  Dn  |  Rt  | MLV  | F13  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |NG_OS?|      |  Dn  |TO(Qw)|      |Enter |   `  | Mute | End  |  Dn  | PgDn | KOTI | F14  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |Shift | Del  |Enter |Shift |      |      |      | PSCR | F15  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FUNCTION] = LAYOUT( \
      KC_CAPS,    KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,                KC_F6,      KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, \
      LAG(KC_ESC),NGSW_WIN,_______,KC_UP,  _______,LCA(KC_DEL),          KC__VOLUP,  KC_HOME,KC_UP,  KC_PGUP,NG_TAYO,KC_F12, \
      _______,    NGSW_MAC,KC_LEFT,KC_DOWN,KC_RGHT,S(KC_EQL),            KC__VOLDOWN,KC_LEFT,KC_DOWN,KC_RGHT,NG_MLV ,KC_F13, \
      _______,    NG_SHOS, _______,KC_DOWN,TO(0),  _______,   KC_ENT,KC_GRV,KC__MUTE,KC_END, KC_DOWN,KC_PGDN,NG_KOTI,KC_F14, \
      _______,    _______, _______,_______,_______,KC_LSHIFT,KC_DEL,KC_ENT,KC_RSHIFT,_______,_______,_______,KC_PSCR,KC_F15 \
      ),
};

#else
#error "undefined keymaps"
#endif


/*
#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif
*/

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
/*
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}
*/

uint16_t NMPD_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
     // 薙刀式
    case EISU:
      if (record->tap.count && record->event.pressed) {  //單打の擧動を設定
        naginata_off();
      } else if (record->event.pressed) {  //保持時の擧動を設定
        layer_on(_FUNCTION);
      } else {  //離した時の擧動を設定
        layer_off(_FUNCTION);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        naginata_on();
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
/*
void keyboard_post_init_user(void) {
  for (int i = 0; i < 6; i++) {
    rgblight_setrgb_at(0, 0, 0, i);
  }
  rgblight_set();
}
*/
/*
uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _QWERTY:
      for (int i = 0; i < 6; i++) {
        setrgb(0, 0, 0, (LED_TYPE *)&led[i]);
      }
      rgblight_set();
      break;

    case _NUMPAD:
      for (int i = 0; i < 6; i++) {
        setrgb(0, 128, 0, (LED_TYPE *)&led[i]);
      }
      rgblight_set();
      break;
    case _FUNCTION:
      for (int i = 0; i < 6; i++) {
        setrgb(0, 0, 128,(LED_TYPE *)&led[i]);
      }
      rgblight_set();
      break;
  }
  return state;
}
*/

void matrix_init_user(void) {

  // 薙刀式
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式
  
    //#ifdef AUDIO_ENABLE
    //    startup_user();
    //#endif
    //#ifdef RGBLIGHT_ENABLE
    //  RGB_current_mode = rgblight_config.mode;
    //#endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
    //    iota_gfx_init(!has_usb());   // turns on the display
        iota_gfx_init(true);  //trueで逆さまにする。
    #endif
}


/*
#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif
*/

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_QWERTY 0
#define L_NAGINATA (1<<_NAGINATA)
#define L_NUMPAD (1<<_NUMPAD)
#define L_FUNCTION (1<<_FUNCTION)
//#define L_ADJUST (1<<_ADJUST)
//#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("LAYER: "));
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
           matrix_write_P(matrix, PSTR("QWERTY"));
           break;
        case _NAGINATA:
           matrix_write_P(matrix, PSTR("NAGINATA"));
           break;
        case _NUMPAD:
           matrix_write_P(matrix, PSTR("NUMPAD"));
           break;
        case _FUNCTION:
           matrix_write_P(matrix, PSTR("FUNCTION"));
           break;
        default:
           matrix_write_P(matrix, PSTR("UNDEF-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}


void render_status(struct CharacterMatrix *matrix) {

  static const char layer_moji[5][4][9] PROGMEM ={{
      {0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0},
      {0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0},
      {0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0} // 機能
      },{
      {0x9d,0x9e,0x9f,0x01,0x04,0x05,0x06,0x07,0},
      {0xbd,0xbe,0xbf,0x02,0x08,0x09,0x40,0x0b,0},
      {0xdd,0xde,0xdf,0x03,0x0c,0x0d,0x0e,0x0f,0} // 數鍵
      },{
      {0x88,0x89,0x8a,0x8b,0x8c,0},
      {0xa8,0xa9,0xaa,0xab,0xac,0},
      {0xc8,0xc9,0xca,0xcb,0xcc,0} //紋章
      },{
      {0x10,0x11,0x12,0x13,0},
      {0x14,0x15,0x16,0x17,0},
      {0x18,0x19,0x1a,0x1b,0} //寫
      },{
      {0x1c,0x1d,0x1e,0x1f,0},
      {0x60,0x61,0x62,0x63,0},
      {0x64,0x65,0x66,0x67,0} //編
      //},{
      //{0x68,0x69,0x6a,0x6b,0},
      //{0x6c,0x6d,0x6e,0x6e,0},
      //{0x6f,0x70,0x71,0x72,0} //大
      }};

  void caps_num(int gyou){
    matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? layer_moji[3][gyou] : PSTR("    "));
    matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? PSTR("    ") : layer_moji[4][gyou]);
    }

  switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      matrix_write_P(matrix, PSTR("        "));
      matrix_write_P(matrix, layer_moji[2][0]);
      caps_num(0);
      matrix_write_P(matrix, PSTR("        "));
      matrix_write_P(matrix, layer_moji[2][1]);
      caps_num(1);
      matrix_write_P(matrix, PSTR("        "));
      matrix_write_P(matrix, layer_moji[2][2]);
      caps_num(2);
      break;
    case _NUMPAD:
      matrix_write_P(matrix, layer_moji[1][0]);
      matrix_write_P(matrix, layer_moji[2][0]);
      caps_num(0);
      matrix_write_P(matrix, layer_moji[1][1]);
      matrix_write_P(matrix, layer_moji[2][1]);
      caps_num(1);
      matrix_write_P(matrix, layer_moji[1][2]);
      matrix_write_P(matrix, layer_moji[2][2]);
      caps_num(2);
      break;
    case _FUNCTION:
      matrix_write_P(matrix, layer_moji[0][0]);
      matrix_write_P(matrix, PSTR("     "));
      caps_num(0);
      matrix_write_P(matrix, layer_moji[0][1]);
      matrix_write_P(matrix, PSTR("     "));
      caps_num(1);
      matrix_write_P(matrix, layer_moji[0][2]);
      matrix_write_P(matrix, PSTR("     "));
      caps_num(2);
      break;
    default:
      matrix_write_P(matrix, PSTR("        "));
      matrix_write_P(matrix, layer_moji[2][0]);
      matrix_write_P(matrix, PSTR("\n"));
      matrix_write_P(matrix, PSTR("UNDEF-  "));
      matrix_write_P(matrix, layer_moji[2][1]);
      matrix_write_P(matrix, PSTR("\n"));
      matrix_write_P(matrix, PSTR("        "));
      matrix_write_P(matrix, layer_moji[2][2]);
  }
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
/*
  render_logo(&matrix);
  render_layer_status(&matrix);
  */
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_layer_status(&matrix);
  }
  
  
  matrix_update(&display, &matrix);
}

#endif
