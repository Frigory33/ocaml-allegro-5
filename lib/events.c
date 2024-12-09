#include "al5.h"


CAMLprim value ml_al_create_event_queue(value unit)
{
    CAMLparam1(unit);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (queue == NULL) {
        caml_failwith("al_create_event_queue");
    }
    CAMLreturn(Val_ptr(queue));
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

static value convert_keycode(int keycode)
{
    int _keycode;
    switch (keycode) {
        case ALLEGRO_KEY_A: _keycode = ML_KEY_A; break;
        case ALLEGRO_KEY_B: _keycode = ML_KEY_B; break;
        case ALLEGRO_KEY_C: _keycode = ML_KEY_C; break;
        case ALLEGRO_KEY_D: _keycode = ML_KEY_D; break;
        case ALLEGRO_KEY_E: _keycode = ML_KEY_E; break;
        case ALLEGRO_KEY_F: _keycode = ML_KEY_F; break;
        case ALLEGRO_KEY_G: _keycode = ML_KEY_G; break;
        case ALLEGRO_KEY_H: _keycode = ML_KEY_H; break;
        case ALLEGRO_KEY_I: _keycode = ML_KEY_I; break;
        case ALLEGRO_KEY_J: _keycode = ML_KEY_J; break;
        case ALLEGRO_KEY_K: _keycode = ML_KEY_K; break;
        case ALLEGRO_KEY_L: _keycode = ML_KEY_L; break;
        case ALLEGRO_KEY_M: _keycode = ML_KEY_M; break;
        case ALLEGRO_KEY_N: _keycode = ML_KEY_N; break;
        case ALLEGRO_KEY_O: _keycode = ML_KEY_O; break;
        case ALLEGRO_KEY_P: _keycode = ML_KEY_P; break;
        case ALLEGRO_KEY_Q: _keycode = ML_KEY_Q; break;
        case ALLEGRO_KEY_R: _keycode = ML_KEY_R; break;
        case ALLEGRO_KEY_S: _keycode = ML_KEY_S; break;
        case ALLEGRO_KEY_T: _keycode = ML_KEY_T; break;
        case ALLEGRO_KEY_U: _keycode = ML_KEY_U; break;
        case ALLEGRO_KEY_V: _keycode = ML_KEY_V; break;
        case ALLEGRO_KEY_W: _keycode = ML_KEY_W; break;
        case ALLEGRO_KEY_X: _keycode = ML_KEY_X; break;
        case ALLEGRO_KEY_Y: _keycode = ML_KEY_Y; break;
        case ALLEGRO_KEY_Z: _keycode = ML_KEY_Z; break;
        case ALLEGRO_KEY_0: _keycode = ML_KEY_0; break;
        case ALLEGRO_KEY_1: _keycode = ML_KEY_1; break;
        case ALLEGRO_KEY_2: _keycode = ML_KEY_2; break;
        case ALLEGRO_KEY_3: _keycode = ML_KEY_3; break;
        case ALLEGRO_KEY_4: _keycode = ML_KEY_4; break;
        case ALLEGRO_KEY_5: _keycode = ML_KEY_5; break;
        case ALLEGRO_KEY_6: _keycode = ML_KEY_6; break;
        case ALLEGRO_KEY_7: _keycode = ML_KEY_7; break;
        case ALLEGRO_KEY_8: _keycode = ML_KEY_8; break;
        case ALLEGRO_KEY_9: _keycode = ML_KEY_9; break;
        case ALLEGRO_KEY_PAD_0: _keycode = ML_KEY_PAD_0; break;
        case ALLEGRO_KEY_PAD_1: _keycode = ML_KEY_PAD_1; break;
        case ALLEGRO_KEY_PAD_2: _keycode = ML_KEY_PAD_2; break;
        case ALLEGRO_KEY_PAD_3: _keycode = ML_KEY_PAD_3; break;
        case ALLEGRO_KEY_PAD_4: _keycode = ML_KEY_PAD_4; break;
        case ALLEGRO_KEY_PAD_5: _keycode = ML_KEY_PAD_5; break;
        case ALLEGRO_KEY_PAD_6: _keycode = ML_KEY_PAD_6; break;
        case ALLEGRO_KEY_PAD_7: _keycode = ML_KEY_PAD_7; break;
        case ALLEGRO_KEY_PAD_8: _keycode = ML_KEY_PAD_8; break;
        case ALLEGRO_KEY_PAD_9: _keycode = ML_KEY_PAD_9; break;
        case ALLEGRO_KEY_F1: _keycode = ML_KEY_F1; break;
        case ALLEGRO_KEY_F2: _keycode = ML_KEY_F2; break;
        case ALLEGRO_KEY_F3: _keycode = ML_KEY_F3; break;
        case ALLEGRO_KEY_F4: _keycode = ML_KEY_F4; break;
        case ALLEGRO_KEY_F5: _keycode = ML_KEY_F5; break;
        case ALLEGRO_KEY_F6: _keycode = ML_KEY_F6; break;
        case ALLEGRO_KEY_F7: _keycode = ML_KEY_F7; break;
        case ALLEGRO_KEY_F8: _keycode = ML_KEY_F8; break;
        case ALLEGRO_KEY_F9: _keycode = ML_KEY_F9; break;
        case ALLEGRO_KEY_F10: _keycode = ML_KEY_F10; break;
        case ALLEGRO_KEY_F11: _keycode = ML_KEY_F11; break;
        case ALLEGRO_KEY_F12: _keycode = ML_KEY_F12; break;
        case ALLEGRO_KEY_ESCAPE: _keycode = ML_KEY_ESCAPE; break;
        case ALLEGRO_KEY_TILDE: _keycode = ML_KEY_TILDE; break;
        case ALLEGRO_KEY_MINUS: _keycode = ML_KEY_MINUS; break;
        case ALLEGRO_KEY_EQUALS: _keycode = ML_KEY_EQUALS; break;
        case ALLEGRO_KEY_BACKSPACE: _keycode = ML_KEY_BACKSPACE; break;
        case ALLEGRO_KEY_TAB: _keycode = ML_KEY_TAB; break;
        case ALLEGRO_KEY_OPENBRACE: _keycode = ML_KEY_OPENBRACE; break;
        case ALLEGRO_KEY_CLOSEBRACE: _keycode = ML_KEY_CLOSEBRACE; break;
        case ALLEGRO_KEY_ENTER: _keycode = ML_KEY_ENTER; break;
        case ALLEGRO_KEY_SEMICOLON: _keycode = ML_KEY_SEMICOLON; break;
        case ALLEGRO_KEY_QUOTE: _keycode = ML_KEY_QUOTE; break;
        case ALLEGRO_KEY_BACKSLASH: _keycode = ML_KEY_BACKSLASH; break;
        case ALLEGRO_KEY_BACKSLASH2: _keycode = ML_KEY_BACKSLASH2; break;
        case ALLEGRO_KEY_COMMA: _keycode = ML_KEY_COMMA; break;
        case ALLEGRO_KEY_FULLSTOP: _keycode = ML_KEY_FULLSTOP; break;
        case ALLEGRO_KEY_SLASH: _keycode = ML_KEY_SLASH; break;
        case ALLEGRO_KEY_SPACE: _keycode = ML_KEY_SPACE; break;
        case ALLEGRO_KEY_INSERT: _keycode = ML_KEY_INSERT; break;
        case ALLEGRO_KEY_DELETE: _keycode = ML_KEY_DELETE; break;
        case ALLEGRO_KEY_HOME: _keycode = ML_KEY_HOME; break;
        case ALLEGRO_KEY_END: _keycode = ML_KEY_END; break;
        case ALLEGRO_KEY_PGUP: _keycode = ML_KEY_PGUP; break;
        case ALLEGRO_KEY_PGDN: _keycode = ML_KEY_PGDN; break;
        case ALLEGRO_KEY_LEFT: _keycode = ML_KEY_LEFT; break;
        case ALLEGRO_KEY_RIGHT: _keycode = ML_KEY_RIGHT; break;
        case ALLEGRO_KEY_UP: _keycode = ML_KEY_UP; break;
        case ALLEGRO_KEY_DOWN: _keycode = ML_KEY_DOWN; break;
        case ALLEGRO_KEY_PAD_SLASH: _keycode = ML_KEY_PAD_SLASH; break;
        case ALLEGRO_KEY_PAD_ASTERISK: _keycode = ML_KEY_PAD_ASTERISK; break;
        case ALLEGRO_KEY_PAD_MINUS: _keycode = ML_KEY_PAD_MINUS; break;
        case ALLEGRO_KEY_PAD_PLUS: _keycode = ML_KEY_PAD_PLUS; break;
        case ALLEGRO_KEY_PAD_DELETE: _keycode = ML_KEY_PAD_DELETE; break;
        case ALLEGRO_KEY_PAD_ENTER: _keycode = ML_KEY_PAD_ENTER; break;
        case ALLEGRO_KEY_PRINTSCREEN: _keycode = ML_KEY_PRINTSCREEN; break;
        case ALLEGRO_KEY_PAUSE: _keycode = ML_KEY_PAUSE; break;
        case ALLEGRO_KEY_ABNT_C1: _keycode = ML_KEY_ABNT_C1; break;
        case ALLEGRO_KEY_YEN: _keycode = ML_KEY_YEN; break;
        case ALLEGRO_KEY_KANA: _keycode = ML_KEY_KANA; break;
        case ALLEGRO_KEY_CONVERT: _keycode = ML_KEY_CONVERT; break;
        case ALLEGRO_KEY_NOCONVERT: _keycode = ML_KEY_NOCONVERT; break;
        case ALLEGRO_KEY_AT: _keycode = ML_KEY_AT; break;
        case ALLEGRO_KEY_CIRCUMFLEX: _keycode = ML_KEY_CIRCUMFLEX; break;
        case ALLEGRO_KEY_COLON2: _keycode = ML_KEY_COLON2; break;
        case ALLEGRO_KEY_KANJI: _keycode = ML_KEY_KANJI; break;
        case ALLEGRO_KEY_LSHIFT: _keycode = ML_KEY_LSHIFT; break;
        case ALLEGRO_KEY_RSHIFT: _keycode = ML_KEY_RSHIFT; break;
        case ALLEGRO_KEY_LCTRL: _keycode = ML_KEY_LCTRL; break;
        case ALLEGRO_KEY_RCTRL: _keycode = ML_KEY_RCTRL; break;
        case ALLEGRO_KEY_ALT: _keycode = ML_KEY_ALT; break;
        case ALLEGRO_KEY_ALTGR: _keycode = ML_KEY_ALTGR; break;
        case ALLEGRO_KEY_LWIN: _keycode = ML_KEY_LWIN; break;
        case ALLEGRO_KEY_RWIN: _keycode = ML_KEY_RWIN; break;
        case ALLEGRO_KEY_MENU: _keycode = ML_KEY_MENU; break;
        case ALLEGRO_KEY_SCROLLLOCK: _keycode = ML_KEY_SCROLLLOCK; break;
        case ALLEGRO_KEY_NUMLOCK: _keycode = ML_KEY_NUMLOCK; break;
        case ALLEGRO_KEY_CAPSLOCK: _keycode = ML_KEY_CAPSLOCK; break;
        case ALLEGRO_KEY_PAD_EQUALS: _keycode = ML_KEY_PAD_EQUALS; break;
        case ALLEGRO_KEY_BACKQUOTE: _keycode = ML_KEY_BACKQUOTE; break;
        case ALLEGRO_KEY_SEMICOLON2: _keycode = ML_KEY_SEMICOLON2; break;
        case ALLEGRO_KEY_COMMAND: _keycode = ML_KEY_COMMAND; break;
        case ALLEGRO_KEY_BACK: _keycode = ML_KEY_BACK; break;
        case ALLEGRO_KEY_VOLUME_UP: _keycode = ML_KEY_VOLUME_UP; break;
        case ALLEGRO_KEY_VOLUME_DOWN: _keycode = ML_KEY_VOLUME_DOWN; break;
        case ALLEGRO_KEY_SEARCH: _keycode = ML_KEY_SEARCH; break;
        case ALLEGRO_KEY_DPAD_CENTER: _keycode = ML_KEY_DPAD_CENTER; break;
        case ALLEGRO_KEY_BUTTON_X: _keycode = ML_KEY_BUTTON_X; break;
        case ALLEGRO_KEY_BUTTON_Y: _keycode = ML_KEY_BUTTON_Y; break;
        case ALLEGRO_KEY_DPAD_UP: _keycode = ML_KEY_DPAD_UP; break;
        case ALLEGRO_KEY_DPAD_DOWN: _keycode = ML_KEY_DPAD_DOWN; break;
        case ALLEGRO_KEY_DPAD_LEFT: _keycode = ML_KEY_DPAD_LEFT; break;
        case ALLEGRO_KEY_DPAD_RIGHT: _keycode = ML_KEY_DPAD_RIGHT; break;
        case ALLEGRO_KEY_SELECT: _keycode = ML_KEY_SELECT; break;
        case ALLEGRO_KEY_START: _keycode = ML_KEY_START; break;
        default: _keycode = -1;
    }
    return Val_int(_keycode);
}

static value convert_event(ALLEGRO_EVENT _evt)
{
    CAMLparam0();
    CAMLlocal1(evt);
    switch (_evt.type) {
        case ALLEGRO_EVENT_KEY_CHAR:
            evt = caml_alloc(5, ML_EVENT_KEY_CHAR);
            Store_field(evt, 0, convert_keycode(_evt.keyboard.keycode));
            Store_field(evt, 1, Val_int(_evt.keyboard.unichar));
            Store_field(evt, 2, Val_int(_evt.keyboard.modifiers));
            Store_field(evt, 3, Val_bool(_evt.keyboard.repeat));
            Store_field(evt, 4, Val_ptr(_evt.keyboard.display));
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            evt = caml_alloc(1, ML_EVENT_DISPLAY_CLOSE);
            Store_field(evt, 0, caml_copy_nativeint((intnat)_evt.display.source));
            break;
        default:
            evt = caml_alloc(1, ML_EVENT_UNKNOWN);
            Store_field(evt, 0, Val_int(_evt.type));
    }
    CAMLreturn(evt);
}

CAMLprim value ml_al_wait_for_event(value queue)
{
    CAMLparam1(queue);
    ALLEGRO_EVENT evt;
    al_wait_for_event(Ptr_val(queue), &evt);
    CAMLreturn(convert_event(evt));
}
