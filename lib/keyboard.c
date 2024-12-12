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


value convert_keycode(int c_keycode)
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

value convert_keymod(int c_keymod)
{
    int const modifiers[][2] = {
        { ALLEGRO_KEYMOD_SHIFT, ML_KEYMOD_SHIFT },
        { ALLEGRO_KEYMOD_CTRL, ML_KEYMOD_CTRL },
        { ALLEGRO_KEYMOD_ALT, ML_KEYMOD_ALT },
        { ALLEGRO_KEYMOD_LWIN, ML_KEYMOD_LWIN },
        { ALLEGRO_KEYMOD_RWIN, ML_KEYMOD_RWIN },
        { ALLEGRO_KEYMOD_MENU, ML_KEYMOD_MENU },
        { ALLEGRO_KEYMOD_ALTGR, ML_KEYMOD_ALTGR },
        { ALLEGRO_KEYMOD_COMMAND, ML_KEYMOD_COMMAND },
        { ALLEGRO_KEYMOD_SCROLLLOCK, ML_KEYMOD_SCROLLLOCK },
        { ALLEGRO_KEYMOD_NUMLOCK, ML_KEYMOD_NUMLOCK },
        { ALLEGRO_KEYMOD_CAPSLOCK, ML_KEYMOD_CAPSLOCK },
        { ALLEGRO_KEYMOD_INALTSEQ, ML_KEYMOD_INALTSEQ },
        { ALLEGRO_KEYMOD_ACCENT1, ML_KEYMOD_ACCENT1 },
        { ALLEGRO_KEYMOD_ACCENT2, ML_KEYMOD_ACCENT2 },
        { ALLEGRO_KEYMOD_ACCENT3, ML_KEYMOD_ACCENT3 },
        { ALLEGRO_KEYMOD_ACCENT4, ML_KEYMOD_ACCENT4 },
    };
    int keymod = 0;
    for (int i = 0; i < sizeof(modifiers) / sizeof(*modifiers); ++i) {
        if ((c_keymod & modifiers[i][0]) == modifiers[i][0]) {
            keymod |= modifiers[i][1];
        }
    }
    return Val_int(keymod);
}


ml_function_noarg_ret(al_get_keyboard_event_source, Val_ptr)
