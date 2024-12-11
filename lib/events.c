#include "keyboard.h"


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
