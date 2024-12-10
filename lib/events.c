#include "al5.h"


CAMLprim value ml_al_create_event_queue(value unit)
{
    CAMLparam1(unit);
    ALLEGRO_EVENT_QUEUE *c_queue = al_create_event_queue();
    if (c_queue == NULL) {
        caml_failwith("al_create_event_queue");
    }
    CAMLreturn(Val_ptr(c_queue));
}

ml_function_1arg(al_destroy_event_queue, Ptr_val)

CAMLprim value ml_al_register_event_source(value queue, value source)
{
    CAMLparam2(queue, source);
    al_register_event_source(Ptr_val(queue), Ptr_val(source));
    CAMLreturn(Val_unit);
}


enum {
    ML_EVENT_JOYSTICK_AXIS,
    ML_EVENT_JOYSTICK_BUTTON_DOWN,
    ML_EVENT_JOYSTICK_BUTTON_UP,
    ML_EVENT_KEY_DOWN,
    ML_EVENT_KEY_UP,
    ML_EVENT_KEY_CHAR,
    ML_EVENT_MOUSE_AXES,
    ML_EVENT_MOUSE_BUTTON_DOWN,
    ML_EVENT_MOUSE_BUTTON_UP,
    ML_EVENT_MOUSE_WARPED,
    ML_EVENT_MOUSE_ENTER_DISPLAY,
    ML_EVENT_MOUSE_LEAVE_DISPLAY,
    ML_EVENT_TOUCH_BEGIN,
    ML_EVENT_TOUCH_END,
    ML_EVENT_TOUCH_MOVE,
    ML_EVENT_TOUCH_CANCEL,
    ML_EVENT_TIMER,
    ML_EVENT_DISPLAY_EXPOSE,
    ML_EVENT_DISPLAY_RESIZE,
    ML_EVENT_DISPLAY_CLOSE,
    ML_EVENT_DISPLAY_LOST,
    ML_EVENT_DISPLAY_FOUND,
    ML_EVENT_DISPLAY_SWITCH_OUT,
    ML_EVENT_DISPLAY_SWITCH_IN,
    ML_EVENT_DISPLAY_ORIENTATION,
    ML_EVENT_DISPLAY_CONNECTED,
    ML_EVENT_DISPLAY_DISCONNECTED,
    ML_EVENT_DROP,
    ML_EVENT_UNKNOWN,
};
enum {
    ML_EVENT_JOYSTICK_CONFIGURATION,
    ML_EVENT_DISPLAY_HALT_DRAWING,
    ML_EVENT_DISPLAY_RESUME_DRAWING,
};

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

static value convert_keycode(int c_keycode)
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

static value convert_keymod(int c_keymod)
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


static value convert_event(ALLEGRO_EVENT c_evt)
{
    CAMLparam0();
    CAMLlocal1(evt);
    switch (c_evt.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_KEY_UP:
            evt = caml_alloc(2, c_evt.type == ALLEGRO_EVENT_KEY_UP ? ML_EVENT_KEY_UP : ML_EVENT_KEY_DOWN);
            Store_field(evt, 0, convert_keycode(c_evt.keyboard.keycode));
            Store_field(evt, 1, Val_ptr(c_evt.keyboard.display));
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            evt = caml_alloc(5, ML_EVENT_KEY_CHAR);
            Store_field(evt, 0, convert_keycode(c_evt.keyboard.keycode));
            Store_field(evt, 1, Val_int(c_evt.keyboard.unichar));
            Store_field(evt, 2, convert_keymod(c_evt.keyboard.modifiers));
            Store_field(evt, 3, Val_bool(c_evt.keyboard.repeat));
            Store_field(evt, 4, Val_ptr(c_evt.keyboard.display));
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            evt = caml_alloc(1, ML_EVENT_DISPLAY_CLOSE);
            Store_field(evt, 0, caml_copy_nativeint((intnat)c_evt.display.source));
            break;
        default:
            evt = caml_alloc(1, ML_EVENT_UNKNOWN);
            Store_field(evt, 0, Val_int(c_evt.type));
    }
    CAMLreturn(evt);
}

CAMLprim value ml_al_wait_for_event(value queue)
{
    CAMLparam1(queue);
    ALLEGRO_EVENT c_evt;
    al_wait_for_event(Ptr_val(queue), &c_evt);
    CAMLreturn(convert_event(c_evt));
}
