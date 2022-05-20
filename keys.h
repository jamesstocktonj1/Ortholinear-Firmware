// File for defining the key layouts for the Split Ortholinear Keyboard
// James Stockton
// 19/05/2022

#include "Adafruit_TinyUSB.h"


#define USR_KEY_0 0xb0
#define USR_KEY_1 0xb1
#define USR_KEY_2 0xb2
#define USR_KEY_3 0xb3
#define USR_KEY_4 0xb4
#define USR_KEY_5 0xb5



uint8_t primaryLayer[4][12] = {
  HID_KEY_ESCAPE,       HID_KEY_Q,        HID_KEY_W,        HID_KEY_E,    HID_KEY_R,    HID_KEY_T,      HID_KEY_Y,          HID_KEY_U,          HID_KEY_I,        HID_KEY_O,            HID_KEY_P,          HID_KEY_BACKSPACE, 
  HID_KEY_TAB,          HID_KEY_A,        HID_KEY_S,        HID_KEY_D,    HID_KEY_F,    HID_KEY_G,      HID_KEY_H,          HID_KEY_J,          HID_KEY_K,        HID_KEY_L,            HID_KEY_SEMICOLON,  HID_KEY_ENTER, 
  HID_KEY_SHIFT_LEFT,   HID_KEY_Z,        HID_KEY_X,        HID_KEY_C,    HID_KEY_V,    HID_KEY_B,      HID_KEY_N,          HID_KEY_M,          HID_KEY_COMMA,    HID_KEY_PERIOD,       HID_KEY_BACKSLASH,  HID_KEY_RIGHT_SHIFT, 
  HID_KEY_CONTROL_LEFT, HID_KEY_GUI_LEFT, HID_KEY_ALT_LEFT, USR_KEY_0,    USR_KEY_1,    HID_KEY_SPACE,  HID_KEY_NONE,       HID_KEY_ARROW_LEFT, HID_KEY_ARROW_UP, HID_KEY_ARROW_DOWN,   HID_KEY_ARROW_RIGHT,HID_KEY_NONE, 
};

uint8_t secondaryLayer[4][12] = {
  HID_KEY_ESCAPE,       HID_KEY_1,        HID_KEY_2,        HID_KEY_3,    HID_KEY_4,    HID_KEY_5,      HID_KEY_6,          HID_KEY_7,          HID_KEY_8,        HID_KEY_9,            HID_KEY_0,          HID_KEY_BACKSPACE, 
  HID_KEY_TAB,          HID_KEY_A,        HID_KEY_S,        HID_KEY_D,    HID_KEY_F,    HID_KEY_G,      HID_KEY_H,          HID_KEY_J,          HID_KEY_K,        HID_KEY_L,            HID_KEY_SEMICOLON,  HID_KEY_ENTER, 
  HID_KEY_SHIFT_LEFT,   HID_KEY_Z,        HID_KEY_X,        HID_KEY_C,    HID_KEY_V,    HID_KEY_B,      HID_KEY_N,          HID_KEY_M,          HID_KEY_COMMA,    HID_KEY_PERIOD,       HID_KEY_BACKSLASH,  HID_KEY_RIGHT_SHIFT, 
  HID_KEY_CONTROL_LEFT, HID_KEY_GUI_LEFT, HID_KEY_ALT_LEFT, USR_KEY_0,    USR_KEY_1,    HID_KEY_SPACE,  HID_KEY_NONE,       HID_KEY_ARROW_LEFT, HID_KEY_ARROW_UP, HID_KEY_ARROW_DOWN,   HID_KEY_ARROW_RIGHT,HID_KEY_NONE, 
};
