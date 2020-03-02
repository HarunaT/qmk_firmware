#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


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
    _NUMPAD,
    _FUNCTION
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

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
   * | Ctrl | S(V) | Alt  | GUI  |LANG2 |MO(Fn)| Bksp |Enter |SandS |LANG1 | JYEN |  @   |  [   |  _   |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_SPC, KC_1,   KC_2,   KC_3,   KC_4,    KC_5,                KC_6,         KC_7,    KC_8,   KC_9,   KC_0,   KC_EQL, \
      KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,    KC_T,                KC_Y,         KC_U,    KC_I,   KC_O,   KC_P,   KC_MINS, \
      KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,    KC_G,                KC_H,         KC_J,    KC_K,   KC_L,   KC_SCLN,KC_QUOT, \
      KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,    KC_B, TO(1), S(KC_0),KC_N,         KC_M,    KC_COMM,KC_DOT, KC_SLSH,KC_NUHS, \
      KC_LCTL,S(KC_V),KC_LALT,KC_LGUI,KC_LANG2,MO(2),KC_BSPC,KC_ENT,SFT_T(KC_SPC),KC_LANG1,KC_JYEN,KC_LBRC,KC_RBRC,KC_RO \
      ),

  /* Numpad
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |Spece |      |      |   <  |   >  |   ?  |             |   /  |   .  |   =  |   /  |   *  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Esc  |   !  |   "  |   [  |   ]  |   '  |             |   *  |   7  |   8  |   9  |   -  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   #  |   $  |   (  |   )  |   ~  |             |   -  |   4  |   5  |   6  |   +  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   %  |   &  |   {  |   }  |   |  |TO(Nu)| NLCK |   +  |   1  |   2  |   3  | Ent  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      | Alt  | GUI  |LANG2 |MO(Fn)| Bksp | Ent  |SandS |   0  |   0  |   .  | Ent  |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUMPAD] = LAYOUT( \
      _______,_______,_______,KC_LABK,KC_RABK,KC_QUES,                   KC_PSLS, KC_PDOT,KC_PEQL,KC_PSLS,KC_PAST,_______, \
      _______,KC_EXLM,KC_AT,  KC_RBRC,KC_NUHS,KC_AMPR,                   KC_PAST,   KC_P7,KC_P8,  KC_P9,  KC_PMNS,_______, \
      _______,KC_HASH,KC_DLR, KC_ASTR,KC_LPRN,KC_TILD,                   KC_PMNS,   KC_P4,KC_P5,  KC_P6,  KC_PPLS,_______, \
      _______,KC_PERC,KC_CIRC,KC_RCBR,KC_PIPE,S(KC_JYEN),_______,KC_NLCK,KC_PPLS,   KC_P1,KC_P2,  KC_P3,  KC_PENT,_______, \
      _______,_______,_______,_______,_______,_______,KC_BSPC,KC_PENT,SFT_T(KC_SPC),KC_P0,KC_P0,  KC_PDOT,KC_PENT,_______ \
      ),

  /* Function
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | CAPS |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |GA+Esc|      |      |  Up  |      |CA+Del|             |      | Home |  Up  | PgUp | PSCR | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |      |  Lt  |  Dn  |  Rt  | S(^) |             |  Lt  |  Lt  |  Dn  |  Rt  |      | F13  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|      |      |  Dn  |      |TO(Qw)|Enter |   `  |      | End  |  Dn  | PgDn |      | F14  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |      | Alt  | GUI  |LANG2 |MO(Fn)| Del  |Enter |Shift |LANG1 |      |      |      | F15  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FUNCTION] = LAYOUT( \
      KC_CAPS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, \
      G(A(KC_ESC)),_______,_______,KC_UP,_______,LCA(KC_DEL),       _______,KC_HOME,KC_UP,  KC_PGUP,KC_PSCR,KC_F12, \
      _______,_______,KC_LEFT,KC_DOWN,KC_RGHT,S(KC_EQL),            KC_LEFT,KC_LEFT,KC_DOWN,KC_RGHT,_______,KC_F13, \
      _______,_______,_______,KC_DOWN,_______,TO(0),  KC_ENT,KC_GRV,_______,KC_END, KC_DOWN,KC_PGDN,_______,KC_F14 , \
      _______,_______,_______,_______,_______,_______,KC_DEL,KC_ENT,_______,_______,_______,_______,_______,KC_F15 \
      ),

  
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


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
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_ANIMATIONS)
  char buf[30];
  if(rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write_P(matrix, os_logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[0][1]);
  }else{
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
