#include "keyboard.h"


CAMLprim value ml_al_install_keyboard(value unit)
{
    CAMLparam1(unit);
    if (!al_install_keyboard()) {
        caml_failwith("al_install_keyboard");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_keyboard_installed, Val_bool)

ml_function_noarg(al_uninstall_keyboard)

ml_function_noarg_ret(al_get_keyboard_event_source, Val_ptr)


enum {
    ML_KEY_A,
    ML_KEY_B,
    ML_KEY_C,
    ML_KEY_D,
    ML_KEY_E,
    ML_KEY_F,
    ML_KEY_G,
    ML_KEY_H,
    ML_KEY_I,
    ML_KEY_J,
    ML_KEY_K,
    ML_KEY_L,
    ML_KEY_M,
    ML_KEY_N,
    ML_KEY_O,
    ML_KEY_P,
    ML_KEY_Q,
    ML_KEY_R,
    ML_KEY_S,
    ML_KEY_T,
    ML_KEY_U,
    ML_KEY_V,
    ML_KEY_W,
    ML_KEY_X,
    ML_KEY_Y,
    ML_KEY_Z,
    ML_KEY_0,
    ML_KEY_1,
    ML_KEY_2,
    ML_KEY_3,
    ML_KEY_4,
    ML_KEY_5,
    ML_KEY_6,
    ML_KEY_7,
    ML_KEY_8,
    ML_KEY_9,
    ML_KEY_PAD_0,
    ML_KEY_PAD_1,
    ML_KEY_PAD_2,
    ML_KEY_PAD_3,
    ML_KEY_PAD_4,
    ML_KEY_PAD_5,
    ML_KEY_PAD_6,
    ML_KEY_PAD_7,
    ML_KEY_PAD_8,
    ML_KEY_PAD_9,
    ML_KEY_F1,
    ML_KEY_F2,
    ML_KEY_F3,
    ML_KEY_F4,
    ML_KEY_F5,
    ML_KEY_F6,
    ML_KEY_F7,
    ML_KEY_F8,
    ML_KEY_F9,
    ML_KEY_F10,
    ML_KEY_F11,
    ML_KEY_F12,
    ML_KEY_ESCAPE,
    ML_KEY_TILDE,
    ML_KEY_MINUS,
    ML_KEY_EQUALS,
    ML_KEY_BACKSPACE,
    ML_KEY_TAB,
    ML_KEY_OPENBRACE,
    ML_KEY_CLOSEBRACE,
    ML_KEY_ENTER,
    ML_KEY_SEMICOLON,
    ML_KEY_QUOTE,
    ML_KEY_BACKSLASH,
    ML_KEY_BACKSLASH2,
    ML_KEY_COMMA,
    ML_KEY_FULLSTOP,
    ML_KEY_SLASH,
    ML_KEY_SPACE,
    ML_KEY_INSERT,
    ML_KEY_DELETE,
    ML_KEY_HOME,
    ML_KEY_END,
    ML_KEY_PGUP,
    ML_KEY_PGDN,
    ML_KEY_LEFT,
    ML_KEY_RIGHT,
    ML_KEY_UP,
    ML_KEY_DOWN,
    ML_KEY_PAD_SLASH,
    ML_KEY_PAD_ASTERISK,
    ML_KEY_PAD_MINUS,
    ML_KEY_PAD_PLUS,
    ML_KEY_PAD_DELETE,
    ML_KEY_PAD_ENTER,
    ML_KEY_PRINTSCREEN,
    ML_KEY_PAUSE,
    ML_KEY_ABNT_C1,
    ML_KEY_YEN,
    ML_KEY_KANA,
    ML_KEY_CONVERT,
    ML_KEY_NOCONVERT,
    ML_KEY_AT,
    ML_KEY_CIRCUMFLEX,
    ML_KEY_COLON2,
    ML_KEY_KANJI,
    ML_KEY_LSHIFT,
    ML_KEY_RSHIFT,
    ML_KEY_LCTRL,
    ML_KEY_RCTRL,
    ML_KEY_ALT,
    ML_KEY_ALTGR,
    ML_KEY_LWIN,
    ML_KEY_RWIN,
    ML_KEY_MENU,
    ML_KEY_SCROLLLOCK,
    ML_KEY_NUMLOCK,
    ML_KEY_CAPSLOCK,
    ML_KEY_PAD_EQUALS,
    ML_KEY_BACKQUOTE,
    ML_KEY_SEMICOLON2,
    ML_KEY_COMMAND,
    ML_KEY_BACK,
    ML_KEY_VOLUME_UP,
    ML_KEY_VOLUME_DOWN,
    ML_KEY_SEARCH,
    ML_KEY_DPAD_CENTER,
    ML_KEY_BUTTON_X,
    ML_KEY_BUTTON_Y,
    ML_KEY_DPAD_UP,
    ML_KEY_DPAD_DOWN,
    ML_KEY_DPAD_LEFT,
    ML_KEY_DPAD_RIGHT,
    ML_KEY_SELECT,
    ML_KEY_START,
    ML_KEY_L1,
    ML_KEY_R1,
};

enum {
    ML_KEYMOD_SHIFT = 1 << 0,
    ML_KEYMOD_CTRL = 1 << 1,
    ML_KEYMOD_ALT = 1 << 2,
    ML_KEYMOD_LWIN = 1 << 3,
    ML_KEYMOD_RWIN = 1 << 4,
    ML_KEYMOD_MENU = 1 << 5,
    ML_KEYMOD_ALTGR = 1 << 6,
    ML_KEYMOD_COMMAND = 1 << 7,
    ML_KEYMOD_SCROLLLOCK = 1 << 8,
    ML_KEYMOD_NUMLOCK = 1 << 9,
    ML_KEYMOD_CAPSLOCK = 1 << 10,
    ML_KEYMOD_INALTSEQ = 1 << 11,
    ML_KEYMOD_ACCENT1 = 1 << 12,
    ML_KEYMOD_ACCENT2 = 1 << 13,
    ML_KEYMOD_ACCENT3 = 1 << 14,
    ML_KEYMOD_ACCENT4 = 1 << 15,
};

value convert_keycode_from_c(int c_keycode)
{
    int keycode;
    switch (c_keycode) {
        case ALLEGRO_KEY_A: keycode = ML_KEY_A; break;
        case ALLEGRO_KEY_B: keycode = ML_KEY_B; break;
        case ALLEGRO_KEY_C: keycode = ML_KEY_C; break;
        case ALLEGRO_KEY_D: keycode = ML_KEY_D; break;
        case ALLEGRO_KEY_E: keycode = ML_KEY_E; break;
        case ALLEGRO_KEY_F: keycode = ML_KEY_F; break;
        case ALLEGRO_KEY_G: keycode = ML_KEY_G; break;
        case ALLEGRO_KEY_H: keycode = ML_KEY_H; break;
        case ALLEGRO_KEY_I: keycode = ML_KEY_I; break;
        case ALLEGRO_KEY_J: keycode = ML_KEY_J; break;
        case ALLEGRO_KEY_K: keycode = ML_KEY_K; break;
        case ALLEGRO_KEY_L: keycode = ML_KEY_L; break;
        case ALLEGRO_KEY_M: keycode = ML_KEY_M; break;
        case ALLEGRO_KEY_N: keycode = ML_KEY_N; break;
        case ALLEGRO_KEY_O: keycode = ML_KEY_O; break;
        case ALLEGRO_KEY_P: keycode = ML_KEY_P; break;
        case ALLEGRO_KEY_Q: keycode = ML_KEY_Q; break;
        case ALLEGRO_KEY_R: keycode = ML_KEY_R; break;
        case ALLEGRO_KEY_S: keycode = ML_KEY_S; break;
        case ALLEGRO_KEY_T: keycode = ML_KEY_T; break;
        case ALLEGRO_KEY_U: keycode = ML_KEY_U; break;
        case ALLEGRO_KEY_V: keycode = ML_KEY_V; break;
        case ALLEGRO_KEY_W: keycode = ML_KEY_W; break;
        case ALLEGRO_KEY_X: keycode = ML_KEY_X; break;
        case ALLEGRO_KEY_Y: keycode = ML_KEY_Y; break;
        case ALLEGRO_KEY_Z: keycode = ML_KEY_Z; break;
        case ALLEGRO_KEY_0: keycode = ML_KEY_0; break;
        case ALLEGRO_KEY_1: keycode = ML_KEY_1; break;
        case ALLEGRO_KEY_2: keycode = ML_KEY_2; break;
        case ALLEGRO_KEY_3: keycode = ML_KEY_3; break;
        case ALLEGRO_KEY_4: keycode = ML_KEY_4; break;
        case ALLEGRO_KEY_5: keycode = ML_KEY_5; break;
        case ALLEGRO_KEY_6: keycode = ML_KEY_6; break;
        case ALLEGRO_KEY_7: keycode = ML_KEY_7; break;
        case ALLEGRO_KEY_8: keycode = ML_KEY_8; break;
        case ALLEGRO_KEY_9: keycode = ML_KEY_9; break;
        case ALLEGRO_KEY_PAD_0: keycode = ML_KEY_PAD_0; break;
        case ALLEGRO_KEY_PAD_1: keycode = ML_KEY_PAD_1; break;
        case ALLEGRO_KEY_PAD_2: keycode = ML_KEY_PAD_2; break;
        case ALLEGRO_KEY_PAD_3: keycode = ML_KEY_PAD_3; break;
        case ALLEGRO_KEY_PAD_4: keycode = ML_KEY_PAD_4; break;
        case ALLEGRO_KEY_PAD_5: keycode = ML_KEY_PAD_5; break;
        case ALLEGRO_KEY_PAD_6: keycode = ML_KEY_PAD_6; break;
        case ALLEGRO_KEY_PAD_7: keycode = ML_KEY_PAD_7; break;
        case ALLEGRO_KEY_PAD_8: keycode = ML_KEY_PAD_8; break;
        case ALLEGRO_KEY_PAD_9: keycode = ML_KEY_PAD_9; break;
        case ALLEGRO_KEY_F1: keycode = ML_KEY_F1; break;
        case ALLEGRO_KEY_F2: keycode = ML_KEY_F2; break;
        case ALLEGRO_KEY_F3: keycode = ML_KEY_F3; break;
        case ALLEGRO_KEY_F4: keycode = ML_KEY_F4; break;
        case ALLEGRO_KEY_F5: keycode = ML_KEY_F5; break;
        case ALLEGRO_KEY_F6: keycode = ML_KEY_F6; break;
        case ALLEGRO_KEY_F7: keycode = ML_KEY_F7; break;
        case ALLEGRO_KEY_F8: keycode = ML_KEY_F8; break;
        case ALLEGRO_KEY_F9: keycode = ML_KEY_F9; break;
        case ALLEGRO_KEY_F10: keycode = ML_KEY_F10; break;
        case ALLEGRO_KEY_F11: keycode = ML_KEY_F11; break;
        case ALLEGRO_KEY_F12: keycode = ML_KEY_F12; break;
        case ALLEGRO_KEY_ESCAPE: keycode = ML_KEY_ESCAPE; break;
        case ALLEGRO_KEY_TILDE: keycode = ML_KEY_TILDE; break;
        case ALLEGRO_KEY_MINUS: keycode = ML_KEY_MINUS; break;
        case ALLEGRO_KEY_EQUALS: keycode = ML_KEY_EQUALS; break;
        case ALLEGRO_KEY_BACKSPACE: keycode = ML_KEY_BACKSPACE; break;
        case ALLEGRO_KEY_TAB: keycode = ML_KEY_TAB; break;
        case ALLEGRO_KEY_OPENBRACE: keycode = ML_KEY_OPENBRACE; break;
        case ALLEGRO_KEY_CLOSEBRACE: keycode = ML_KEY_CLOSEBRACE; break;
        case ALLEGRO_KEY_ENTER: keycode = ML_KEY_ENTER; break;
        case ALLEGRO_KEY_SEMICOLON: keycode = ML_KEY_SEMICOLON; break;
        case ALLEGRO_KEY_QUOTE: keycode = ML_KEY_QUOTE; break;
        case ALLEGRO_KEY_BACKSLASH: keycode = ML_KEY_BACKSLASH; break;
        case ALLEGRO_KEY_BACKSLASH2: keycode = ML_KEY_BACKSLASH2; break;
        case ALLEGRO_KEY_COMMA: keycode = ML_KEY_COMMA; break;
        case ALLEGRO_KEY_FULLSTOP: keycode = ML_KEY_FULLSTOP; break;
        case ALLEGRO_KEY_SLASH: keycode = ML_KEY_SLASH; break;
        case ALLEGRO_KEY_SPACE: keycode = ML_KEY_SPACE; break;
        case ALLEGRO_KEY_INSERT: keycode = ML_KEY_INSERT; break;
        case ALLEGRO_KEY_DELETE: keycode = ML_KEY_DELETE; break;
        case ALLEGRO_KEY_HOME: keycode = ML_KEY_HOME; break;
        case ALLEGRO_KEY_END: keycode = ML_KEY_END; break;
        case ALLEGRO_KEY_PGUP: keycode = ML_KEY_PGUP; break;
        case ALLEGRO_KEY_PGDN: keycode = ML_KEY_PGDN; break;
        case ALLEGRO_KEY_LEFT: keycode = ML_KEY_LEFT; break;
        case ALLEGRO_KEY_RIGHT: keycode = ML_KEY_RIGHT; break;
        case ALLEGRO_KEY_UP: keycode = ML_KEY_UP; break;
        case ALLEGRO_KEY_DOWN: keycode = ML_KEY_DOWN; break;
        case ALLEGRO_KEY_PAD_SLASH: keycode = ML_KEY_PAD_SLASH; break;
        case ALLEGRO_KEY_PAD_ASTERISK: keycode = ML_KEY_PAD_ASTERISK; break;
        case ALLEGRO_KEY_PAD_MINUS: keycode = ML_KEY_PAD_MINUS; break;
        case ALLEGRO_KEY_PAD_PLUS: keycode = ML_KEY_PAD_PLUS; break;
        case ALLEGRO_KEY_PAD_DELETE: keycode = ML_KEY_PAD_DELETE; break;
        case ALLEGRO_KEY_PAD_ENTER: keycode = ML_KEY_PAD_ENTER; break;
        case ALLEGRO_KEY_PRINTSCREEN: keycode = ML_KEY_PRINTSCREEN; break;
        case ALLEGRO_KEY_PAUSE: keycode = ML_KEY_PAUSE; break;
        case ALLEGRO_KEY_ABNT_C1: keycode = ML_KEY_ABNT_C1; break;
        case ALLEGRO_KEY_YEN: keycode = ML_KEY_YEN; break;
        case ALLEGRO_KEY_KANA: keycode = ML_KEY_KANA; break;
        case ALLEGRO_KEY_CONVERT: keycode = ML_KEY_CONVERT; break;
        case ALLEGRO_KEY_NOCONVERT: keycode = ML_KEY_NOCONVERT; break;
        case ALLEGRO_KEY_AT: keycode = ML_KEY_AT; break;
        case ALLEGRO_KEY_CIRCUMFLEX: keycode = ML_KEY_CIRCUMFLEX; break;
        case ALLEGRO_KEY_COLON2: keycode = ML_KEY_COLON2; break;
        case ALLEGRO_KEY_KANJI: keycode = ML_KEY_KANJI; break;
        case ALLEGRO_KEY_LSHIFT: keycode = ML_KEY_LSHIFT; break;
        case ALLEGRO_KEY_RSHIFT: keycode = ML_KEY_RSHIFT; break;
        case ALLEGRO_KEY_LCTRL: keycode = ML_KEY_LCTRL; break;
        case ALLEGRO_KEY_RCTRL: keycode = ML_KEY_RCTRL; break;
        case ALLEGRO_KEY_ALT: keycode = ML_KEY_ALT; break;
        case ALLEGRO_KEY_ALTGR: keycode = ML_KEY_ALTGR; break;
        case ALLEGRO_KEY_LWIN: keycode = ML_KEY_LWIN; break;
        case ALLEGRO_KEY_RWIN: keycode = ML_KEY_RWIN; break;
        case ALLEGRO_KEY_MENU: keycode = ML_KEY_MENU; break;
        case ALLEGRO_KEY_SCROLLLOCK: keycode = ML_KEY_SCROLLLOCK; break;
        case ALLEGRO_KEY_NUMLOCK: keycode = ML_KEY_NUMLOCK; break;
        case ALLEGRO_KEY_CAPSLOCK: keycode = ML_KEY_CAPSLOCK; break;
        case ALLEGRO_KEY_PAD_EQUALS: keycode = ML_KEY_PAD_EQUALS; break;
        case ALLEGRO_KEY_BACKQUOTE: keycode = ML_KEY_BACKQUOTE; break;
        case ALLEGRO_KEY_SEMICOLON2: keycode = ML_KEY_SEMICOLON2; break;
        case ALLEGRO_KEY_COMMAND: keycode = ML_KEY_COMMAND; break;
        case ALLEGRO_KEY_BACK: keycode = ML_KEY_BACK; break;
        case ALLEGRO_KEY_VOLUME_UP: keycode = ML_KEY_VOLUME_UP; break;
        case ALLEGRO_KEY_VOLUME_DOWN: keycode = ML_KEY_VOLUME_DOWN; break;
        case ALLEGRO_KEY_SEARCH: keycode = ML_KEY_SEARCH; break;
        case ALLEGRO_KEY_DPAD_CENTER: keycode = ML_KEY_DPAD_CENTER; break;
        case ALLEGRO_KEY_BUTTON_X: keycode = ML_KEY_BUTTON_X; break;
        case ALLEGRO_KEY_BUTTON_Y: keycode = ML_KEY_BUTTON_Y; break;
        case ALLEGRO_KEY_DPAD_UP: keycode = ML_KEY_DPAD_UP; break;
        case ALLEGRO_KEY_DPAD_DOWN: keycode = ML_KEY_DPAD_DOWN; break;
        case ALLEGRO_KEY_DPAD_LEFT: keycode = ML_KEY_DPAD_LEFT; break;
        case ALLEGRO_KEY_DPAD_RIGHT: keycode = ML_KEY_DPAD_RIGHT; break;
        case ALLEGRO_KEY_SELECT: keycode = ML_KEY_SELECT; break;
        case ALLEGRO_KEY_START: keycode = ML_KEY_START; break;
        default: keycode = -1;
    }
    return Val_int(keycode);
}

int convert_keycode_from_ml(value keycode)
{
    CAMLparam1(keycode);
    static int const keycode_conv[] = {
        [ML_KEY_A] = ALLEGRO_KEY_A,
        [ML_KEY_B] = ALLEGRO_KEY_B,
        [ML_KEY_C] = ALLEGRO_KEY_C,
        [ML_KEY_D] = ALLEGRO_KEY_D,
        [ML_KEY_E] = ALLEGRO_KEY_E,
        [ML_KEY_F] = ALLEGRO_KEY_F,
        [ML_KEY_G] = ALLEGRO_KEY_G,
        [ML_KEY_H] = ALLEGRO_KEY_H,
        [ML_KEY_I] = ALLEGRO_KEY_I,
        [ML_KEY_J] = ALLEGRO_KEY_J,
        [ML_KEY_K] = ALLEGRO_KEY_K,
        [ML_KEY_L] = ALLEGRO_KEY_L,
        [ML_KEY_M] = ALLEGRO_KEY_M,
        [ML_KEY_N] = ALLEGRO_KEY_N,
        [ML_KEY_O] = ALLEGRO_KEY_O,
        [ML_KEY_P] = ALLEGRO_KEY_P,
        [ML_KEY_Q] = ALLEGRO_KEY_Q,
        [ML_KEY_R] = ALLEGRO_KEY_R,
        [ML_KEY_S] = ALLEGRO_KEY_S,
        [ML_KEY_T] = ALLEGRO_KEY_T,
        [ML_KEY_U] = ALLEGRO_KEY_U,
        [ML_KEY_V] = ALLEGRO_KEY_V,
        [ML_KEY_W] = ALLEGRO_KEY_W,
        [ML_KEY_X] = ALLEGRO_KEY_X,
        [ML_KEY_Y] = ALLEGRO_KEY_Y,
        [ML_KEY_Z] = ALLEGRO_KEY_Z,
        [ML_KEY_0] = ALLEGRO_KEY_0,
        [ML_KEY_1] = ALLEGRO_KEY_1,
        [ML_KEY_2] = ALLEGRO_KEY_2,
        [ML_KEY_3] = ALLEGRO_KEY_3,
        [ML_KEY_4] = ALLEGRO_KEY_4,
        [ML_KEY_5] = ALLEGRO_KEY_5,
        [ML_KEY_6] = ALLEGRO_KEY_6,
        [ML_KEY_7] = ALLEGRO_KEY_7,
        [ML_KEY_8] = ALLEGRO_KEY_8,
        [ML_KEY_9] = ALLEGRO_KEY_9,
        [ML_KEY_PAD_0] = ALLEGRO_KEY_PAD_0,
        [ML_KEY_PAD_1] = ALLEGRO_KEY_PAD_1,
        [ML_KEY_PAD_2] = ALLEGRO_KEY_PAD_2,
        [ML_KEY_PAD_3] = ALLEGRO_KEY_PAD_3,
        [ML_KEY_PAD_4] = ALLEGRO_KEY_PAD_4,
        [ML_KEY_PAD_5] = ALLEGRO_KEY_PAD_5,
        [ML_KEY_PAD_6] = ALLEGRO_KEY_PAD_6,
        [ML_KEY_PAD_7] = ALLEGRO_KEY_PAD_7,
        [ML_KEY_PAD_8] = ALLEGRO_KEY_PAD_8,
        [ML_KEY_PAD_9] = ALLEGRO_KEY_PAD_9,
        [ML_KEY_F1] = ALLEGRO_KEY_F1,
        [ML_KEY_F2] = ALLEGRO_KEY_F2,
        [ML_KEY_F3] = ALLEGRO_KEY_F3,
        [ML_KEY_F4] = ALLEGRO_KEY_F4,
        [ML_KEY_F5] = ALLEGRO_KEY_F5,
        [ML_KEY_F6] = ALLEGRO_KEY_F6,
        [ML_KEY_F7] = ALLEGRO_KEY_F7,
        [ML_KEY_F8] = ALLEGRO_KEY_F8,
        [ML_KEY_F9] = ALLEGRO_KEY_F9,
        [ML_KEY_F10] = ALLEGRO_KEY_F10,
        [ML_KEY_F11] = ALLEGRO_KEY_F11,
        [ML_KEY_F12] = ALLEGRO_KEY_F12,
        [ML_KEY_ESCAPE] = ALLEGRO_KEY_ESCAPE,
        [ML_KEY_TILDE] = ALLEGRO_KEY_TILDE,
        [ML_KEY_MINUS] = ALLEGRO_KEY_MINUS,
        [ML_KEY_EQUALS] = ALLEGRO_KEY_EQUALS,
        [ML_KEY_BACKSPACE] = ALLEGRO_KEY_BACKSPACE,
        [ML_KEY_TAB] = ALLEGRO_KEY_TAB,
        [ML_KEY_OPENBRACE] = ALLEGRO_KEY_OPENBRACE,
        [ML_KEY_CLOSEBRACE] = ALLEGRO_KEY_CLOSEBRACE,
        [ML_KEY_ENTER] = ALLEGRO_KEY_ENTER,
        [ML_KEY_SEMICOLON] = ALLEGRO_KEY_SEMICOLON,
        [ML_KEY_QUOTE] = ALLEGRO_KEY_QUOTE,
        [ML_KEY_BACKSLASH] = ALLEGRO_KEY_BACKSLASH,
        [ML_KEY_BACKSLASH2] = ALLEGRO_KEY_BACKSLASH2,
        [ML_KEY_COMMA] = ALLEGRO_KEY_COMMA,
        [ML_KEY_FULLSTOP] = ALLEGRO_KEY_FULLSTOP,
        [ML_KEY_SLASH] = ALLEGRO_KEY_SLASH,
        [ML_KEY_SPACE] = ALLEGRO_KEY_SPACE,
        [ML_KEY_INSERT] = ALLEGRO_KEY_INSERT,
        [ML_KEY_DELETE] = ALLEGRO_KEY_DELETE,
        [ML_KEY_HOME] = ALLEGRO_KEY_HOME,
        [ML_KEY_END] = ALLEGRO_KEY_END,
        [ML_KEY_PGUP] = ALLEGRO_KEY_PGUP,
        [ML_KEY_PGDN] = ALLEGRO_KEY_PGDN,
        [ML_KEY_LEFT] = ALLEGRO_KEY_LEFT,
        [ML_KEY_RIGHT] = ALLEGRO_KEY_RIGHT,
        [ML_KEY_UP] = ALLEGRO_KEY_UP,
        [ML_KEY_DOWN] = ALLEGRO_KEY_DOWN,
        [ML_KEY_PAD_SLASH] = ALLEGRO_KEY_PAD_SLASH,
        [ML_KEY_PAD_ASTERISK] = ALLEGRO_KEY_PAD_ASTERISK,
        [ML_KEY_PAD_MINUS] = ALLEGRO_KEY_PAD_MINUS,
        [ML_KEY_PAD_PLUS] = ALLEGRO_KEY_PAD_PLUS,
        [ML_KEY_PAD_DELETE] = ALLEGRO_KEY_PAD_DELETE,
        [ML_KEY_PAD_ENTER] = ALLEGRO_KEY_PAD_ENTER,
        [ML_KEY_PRINTSCREEN] = ALLEGRO_KEY_PRINTSCREEN,
        [ML_KEY_PAUSE] = ALLEGRO_KEY_PAUSE,
        [ML_KEY_ABNT_C1] = ALLEGRO_KEY_ABNT_C1,
        [ML_KEY_YEN] = ALLEGRO_KEY_YEN,
        [ML_KEY_KANA] = ALLEGRO_KEY_KANA,
        [ML_KEY_CONVERT] = ALLEGRO_KEY_CONVERT,
        [ML_KEY_NOCONVERT] = ALLEGRO_KEY_NOCONVERT,
        [ML_KEY_AT] = ALLEGRO_KEY_AT,
        [ML_KEY_CIRCUMFLEX] = ALLEGRO_KEY_CIRCUMFLEX,
        [ML_KEY_COLON2] = ALLEGRO_KEY_COLON2,
        [ML_KEY_KANJI] = ALLEGRO_KEY_KANJI,
        [ML_KEY_LSHIFT] = ALLEGRO_KEY_LSHIFT,
        [ML_KEY_RSHIFT] = ALLEGRO_KEY_RSHIFT,
        [ML_KEY_LCTRL] = ALLEGRO_KEY_LCTRL,
        [ML_KEY_RCTRL] = ALLEGRO_KEY_RCTRL,
        [ML_KEY_ALT] = ALLEGRO_KEY_ALT,
        [ML_KEY_ALTGR] = ALLEGRO_KEY_ALTGR,
        [ML_KEY_LWIN] = ALLEGRO_KEY_LWIN,
        [ML_KEY_RWIN] = ALLEGRO_KEY_RWIN,
        [ML_KEY_MENU] = ALLEGRO_KEY_MENU,
        [ML_KEY_SCROLLLOCK] = ALLEGRO_KEY_SCROLLLOCK,
        [ML_KEY_NUMLOCK] = ALLEGRO_KEY_NUMLOCK,
        [ML_KEY_CAPSLOCK] = ALLEGRO_KEY_CAPSLOCK,
        [ML_KEY_PAD_EQUALS] = ALLEGRO_KEY_PAD_EQUALS,
        [ML_KEY_BACKQUOTE] = ALLEGRO_KEY_BACKQUOTE,
        [ML_KEY_SEMICOLON2] = ALLEGRO_KEY_SEMICOLON2,
        [ML_KEY_COMMAND] = ALLEGRO_KEY_COMMAND,
        [ML_KEY_BACK] = ALLEGRO_KEY_BACK,
        [ML_KEY_VOLUME_UP] = ALLEGRO_KEY_VOLUME_UP,
        [ML_KEY_VOLUME_DOWN] = ALLEGRO_KEY_VOLUME_DOWN,
        [ML_KEY_SEARCH] = ALLEGRO_KEY_SEARCH,
        [ML_KEY_DPAD_CENTER] = ALLEGRO_KEY_DPAD_CENTER,
        [ML_KEY_BUTTON_X] = ALLEGRO_KEY_BUTTON_X,
        [ML_KEY_BUTTON_Y] = ALLEGRO_KEY_BUTTON_Y,
        [ML_KEY_DPAD_UP] = ALLEGRO_KEY_DPAD_UP,
        [ML_KEY_DPAD_DOWN] = ALLEGRO_KEY_DPAD_DOWN,
        [ML_KEY_DPAD_LEFT] = ALLEGRO_KEY_DPAD_LEFT,
        [ML_KEY_DPAD_RIGHT] = ALLEGRO_KEY_DPAD_RIGHT,
        [ML_KEY_SELECT] = ALLEGRO_KEY_SELECT,
        [ML_KEY_START] = ALLEGRO_KEY_START,
    };
    CAMLreturnT(int, keycode_conv[Int_val(keycode)]);
}

static int const keymod_conv[][2] = {
    { ML_KEYMOD_SHIFT, ALLEGRO_KEYMOD_SHIFT },
    { ML_KEYMOD_CTRL, ALLEGRO_KEYMOD_CTRL },
    { ML_KEYMOD_ALT, ALLEGRO_KEYMOD_ALT },
    { ML_KEYMOD_LWIN, ALLEGRO_KEYMOD_LWIN },
    { ML_KEYMOD_RWIN, ALLEGRO_KEYMOD_RWIN },
    { ML_KEYMOD_MENU, ALLEGRO_KEYMOD_MENU },
    { ML_KEYMOD_ALTGR, ALLEGRO_KEYMOD_ALTGR },
    { ML_KEYMOD_COMMAND, ALLEGRO_KEYMOD_COMMAND },
    { ML_KEYMOD_SCROLLLOCK, ALLEGRO_KEYMOD_SCROLLLOCK },
    { ML_KEYMOD_NUMLOCK, ALLEGRO_KEYMOD_NUMLOCK },
    { ML_KEYMOD_CAPSLOCK, ALLEGRO_KEYMOD_CAPSLOCK },
    { ML_KEYMOD_INALTSEQ, ALLEGRO_KEYMOD_INALTSEQ },
    { ML_KEYMOD_ACCENT1, ALLEGRO_KEYMOD_ACCENT1 },
    { ML_KEYMOD_ACCENT2, ALLEGRO_KEYMOD_ACCENT2 },
    { ML_KEYMOD_ACCENT3, ALLEGRO_KEYMOD_ACCENT3 },
    { ML_KEYMOD_ACCENT4, ALLEGRO_KEYMOD_ACCENT4 },
};

value convert_keymod_from_c(int c_keymod)
{
    int keymod = convert_flags(c_keymod, keymod_conv, 1);
    return Val_int(keymod);
}

int convert_keymod_from_ml(value keymod)
{
    CAMLparam1(keymod);
    int keymod_int = Int_val(keymod);
    if (keymod_int == -1) {
        CAMLreturnT(int, -1);
    }
    CAMLreturnT(int, convert_flags(keymod_int, keymod_conv, 0));
}


#define KbState_val(v) (*((ALLEGRO_KEYBOARD_STATE *)Data_custom_val(v)))
#define KB_STATE_INDEX 1

static struct custom_operations allegro_kb_state_ops = {
  "org.allegro5.keyboard_state",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
  custom_fixed_length_default
};

CAMLprim value ml_al_get_keyboard_state(value unit)
{
    CAMLparam1(unit);
    CAMLlocal2(state, state_priv);
    ALLEGRO_KEYBOARD_STATE c_state;
    al_get_keyboard_state(&c_state);
    state = caml_alloc_tuple(2);
    Store_field(state, 0, Val_ptr(c_state.display));
    state_priv = caml_alloc_custom(&allegro_kb_state_ops, sizeof(ALLEGRO_KEYBOARD_STATE), 1, 4);
    KbState_val(state_priv) = c_state;
    Store_field(state, KB_STATE_INDEX, state_priv);
    CAMLreturn(state);
}

CAMLprim value ml_al_key_down(value state, value keycode)
{
    CAMLparam2(state, keycode);
    CAMLlocal1(state_priv);
    state_priv = Field(state, KB_STATE_INDEX);
    int c_keycode = convert_keycode_from_ml(keycode);
    bool pressed = al_key_down(&KbState_val(state_priv), c_keycode);
    CAMLreturn(Val_bool(pressed));
}

ml_function_1arg_ret(al_keycode_to_name, convert_keycode_from_ml, caml_copy_string)

#if ALLEGRO_VERSION_INT < 0x05020900
bool al_can_set_keyboard_leds()
{ return false; }
#endif

ml_function_noarg_ret(al_can_set_keyboard_leds, Val_bool)

ml_function_1arg(al_set_keyboard_leds, convert_keymod_from_ml)
