# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/keyboards/helix/rules.mk for a list of options that can be set.
#   See TOP/docs/config_options.md for more information.
#
LTO_ENABLE = yes  # if firmware size over limit, try this option

# Helix Spacific Build Options
# you can uncomment and edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集し、コメントアウトをはずします。
# HELIX_ROWS = 5              # Helix Rows is 4 or 5
 OLED_ENABLE = yes            # OLED_ENABLE
 LOCAL_GLCDFONT = yes         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
 LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
 #LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
 #LED_ANIMATIONS = no       # LED animations
# IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

# convert Helix-specific options (that represent combinations of standard options)
#   into QMK standard options.
include $(strip $(KEYBOARD_LOCAL_FEATURES_MK))

# 薙刀式の爲追記
UNICODE_ENABLE = yes
SRC +=    naginata_v14t.c
EXTRAFLAGS += -flto
SPACE_CADET_ENABLE = no
#NO_USB_STARTUP_CHECK = yes
# 薙刀式の爲追記、此處迄
RGBLIGHT_ENABLE = no
ENCODER_ENABLE = no
EXTRAKEY_ENABLE = no

# Custom Shift Keysの爲追記
SRC += custom_shift_keys.c
