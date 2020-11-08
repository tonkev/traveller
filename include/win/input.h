#ifndef INPUT_WIN_H
#define INPUT_WIN_H

#include <winuser.h>

typedef enum {
    MOUSE_L = 1, MOUSE_R, MOUSE_M = 4, MOUSE_3, MOUSE_4, KEY_BACKSPACE = 8,
    KEY_TAB, KEY_ENTER = 13, KEY_CAPSLOCK = 20, KEY_ESC = 27, KEY_SPACE = 32, 
    KEY_PAGEUP, KEY_PAGEDOWN, KEY_END, KEY_HOME, KEY_LEFT, KEY_UP, KEY_RIGHT,
    KEY_DOWN, KEY_PRINTSCREEN = 44, KEY_INSERT, KEY_DELETE,
    KEY_0 = 48, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
    KEY_A = 65, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
    KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
    KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
    KEY_LCOMMAND, KEY_RCOMMAND, KEY_NUM0 = 96, KEY_NUM1, KEY_NUM2, KEY_NUM3,
    KEY_NUM4, KEY_NUM5, KEY_NUM6, KEY_NUM7, KEY_NUM8, KEY_NUM9, KEY_MULTIPLY,
    KEY_ADD, KEY_SEPERATOR, KEY_SUBTRACT, KEY_DECIMAL, KEY_DIVIDE, KEY_F1,
    KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
    KEY_F11, KEY_F12, KEY_LSHIFT = 160, KEY_RSHIFT, KEY_LCONTROL, KEY_RCONTROL,
    KEY_LALT, KEY_RALT, KEY_COLON = 186, KEY_PLUS, KEY_COMMA, KEY_MINUS,
    KEY_PERIOD, KEY_QUESTION, KEY_TILDE, KEY_LBRACKET = 219, KEY_RBRACKET,
    KEY_QUOTE, KEY_MISC0, KEY_MISC1 = 226, KEY_MAX
} InputCode;

void SetKeyDown(WPARAM keycode);
void SetKeyUp(WPARAM keycode);

#endif