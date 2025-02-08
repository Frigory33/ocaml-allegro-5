#include "keyboard.h"

#include <allegro5/allegro_audio.h>


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

CAMLprim value ml_al_unregister_event_source(value queue, value source)
{
    CAMLparam2(queue, source);
    al_unregister_event_source(Ptr_val(queue), Ptr_val(source));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_is_event_source_registered(value queue, value source)
{
    CAMLparam2(queue, source);
    bool registered = al_is_event_source_registered(Ptr_val(queue), Ptr_val(source));
    CAMLreturn(Val_bool(registered));
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
    ML_EVENT_AUDIO_STREAM_FRAGMENT,
    ML_EVENT_AUDIO_STREAM_FINISHED,
};


static value convert_event(ALLEGRO_EVENT c_evt)
{
    CAMLparam0();
    CAMLlocal2(evt, info);
    switch (c_evt.type) {
        case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
            evt = Val_int(ML_EVENT_JOYSTICK_CONFIGURATION);
            break;
        case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING:
            evt = Val_int(ML_EVENT_DISPLAY_HALT_DRAWING);
            break;
        case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING:
            evt = Val_int(ML_EVENT_DISPLAY_RESUME_DRAWING);
            break;
        case ALLEGRO_EVENT_AUDIO_STREAM_FRAGMENT:
            evt = Val_int(ML_EVENT_AUDIO_STREAM_FRAGMENT);
            break;
        case ALLEGRO_EVENT_AUDIO_STREAM_FINISHED:
            evt = Val_int(ML_EVENT_AUDIO_STREAM_FINISHED);
            break;
        case ALLEGRO_EVENT_JOYSTICK_AXIS:
            evt = caml_alloc(4, ML_EVENT_JOYSTICK_AXIS);
            Store_field(evt, 0, Val_ptr(c_evt.joystick.id));
            Store_field(evt, 1, Val_int(c_evt.joystick.stick));
            Store_field(evt, 2, Val_int(c_evt.joystick.axis));
            Store_field(evt, 3, caml_copy_double(c_evt.joystick.pos));
            break;
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
            evt = caml_alloc(2,
                c_evt.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP ?
                    ML_EVENT_JOYSTICK_BUTTON_UP : ML_EVENT_JOYSTICK_BUTTON_DOWN);
            Store_field(evt, 0, Val_ptr(c_evt.joystick.id));
            Store_field(evt, 1, Val_int(c_evt.joystick.button));
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_KEY_UP:
            evt = caml_alloc(2, c_evt.type == ALLEGRO_EVENT_KEY_UP ? ML_EVENT_KEY_UP : ML_EVENT_KEY_DOWN);
            Store_field(evt, 0, convert_keycode_from_c(c_evt.keyboard.keycode));
            Store_field(evt, 1, Val_ptr(c_evt.keyboard.display));
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            evt = caml_alloc(5, ML_EVENT_KEY_CHAR);
            Store_field(evt, 0, convert_keycode_from_c(c_evt.keyboard.keycode));
            Store_field(evt, 1, Val_int(c_evt.keyboard.unichar));
            Store_field(evt, 2, convert_keymod_from_c(c_evt.keyboard.modifiers));
            Store_field(evt, 3, Val_bool(c_evt.keyboard.repeat));
            Store_field(evt, 4, Val_ptr(c_evt.keyboard.display));
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
        case ALLEGRO_EVENT_MOUSE_WARPED:
            evt = caml_alloc(1,
                c_evt.type == ALLEGRO_EVENT_MOUSE_AXES ? ML_EVENT_MOUSE_AXES : ML_EVENT_MOUSE_WARPED);
            info = caml_alloc_tuple(10);
            Store_field(info, 0, Val_int(c_evt.mouse.x));
            Store_field(info, 1, Val_int(c_evt.mouse.y));
            Store_field(info, 2, Val_int(c_evt.mouse.z));
            Store_field(info, 3, Val_int(c_evt.mouse.w));
            Store_field(info, 4, Val_int(c_evt.mouse.dx));
            Store_field(info, 5, Val_int(c_evt.mouse.dy));
            Store_field(info, 6, Val_int(c_evt.mouse.dz));
            Store_field(info, 7, Val_int(c_evt.mouse.dw));
            Store_field(info, 8, caml_copy_double(c_evt.mouse.pressure));
            Store_field(info, 9, Val_ptr(c_evt.mouse.display));
            Store_field(evt, 0, info);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            evt = caml_alloc(1,
                c_evt.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ? ML_EVENT_MOUSE_BUTTON_UP : ML_EVENT_MOUSE_BUTTON_DOWN);
            info = caml_alloc_tuple(7);
            Store_field(info, 0, Val_int(c_evt.mouse.x));
            Store_field(info, 1, Val_int(c_evt.mouse.y));
            Store_field(info, 2, Val_int(c_evt.mouse.z));
            Store_field(info, 3, Val_int(c_evt.mouse.w));
            Store_field(info, 4, Val_int(c_evt.mouse.button));
            Store_field(info, 5, caml_copy_double(c_evt.mouse.pressure));
            Store_field(info, 6, Val_ptr(c_evt.mouse.display));
            Store_field(evt, 0, info);
            break;
        case ALLEGRO_EVENT_TIMER:
            evt = caml_alloc(2, ML_EVENT_TIMER);
            Store_field(evt, 0, Val_ptr(c_evt.timer.source));
            Store_field(evt, 1, caml_copy_int64(c_evt.timer.count));
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

CAMLprim value ml_al_pause_event_queue(value queue, value pause)
{
    CAMLparam2(queue, pause);
    al_pause_event_queue(Ptr_val(queue), Bool_val(pause));
    CAMLreturn(Val_unit);
}

ml_function_1arg_ret(al_is_event_queue_paused, Ptr_val, Val_bool)

ml_function_1arg_ret(al_is_event_queue_empty, Ptr_val, Val_bool)

CAMLprim value ml_al_get_next_event(value queue)
{
    CAMLparam1(queue);
    ALLEGRO_EVENT c_evt;
    if (!al_get_next_event(Ptr_val(queue), &c_evt)) {
        CAMLreturn(Val_none);
    }
    CAMLreturn(caml_alloc_some(convert_event(c_evt)));
}

CAMLprim value ml_al_peek_next_event(value queue)
{
    CAMLparam1(queue);
    ALLEGRO_EVENT c_evt;
    if (!al_peek_next_event(Ptr_val(queue), &c_evt)) {
        CAMLreturn(Val_none);
    }
    CAMLreturn(caml_alloc_some(convert_event(c_evt)));
}

ml_function_1arg_ret(al_drop_next_event, Ptr_val, Val_bool)

ml_function_1arg(al_flush_event_queue, Ptr_val);

CAMLprim value ml_al_wait_for_event(value queue)
{
    CAMLparam1(queue);
    ALLEGRO_EVENT c_evt;
    al_wait_for_event(Ptr_val(queue), &c_evt);
    CAMLreturn(convert_event(c_evt));
}

CAMLprim value ml_al_wait_for_event_timed(value queue, value get, value secs)
{
    CAMLparam3(queue, get, secs);
    if (!Bool_val(get)) {
        al_wait_for_event_timed(Ptr_val(queue), NULL, Double_val(secs));
        CAMLreturn(Val_none);
    }
    ALLEGRO_EVENT c_evt;
    if (!al_wait_for_event_timed(Ptr_val(queue), &c_evt, Double_val(secs))) {
        CAMLreturn(Val_none);
    }
    CAMLreturn(caml_alloc_some(convert_event(c_evt)));
}

CAMLprim value ml_al_wait_for_event_until(value queue, value get, value timeout)
{
    CAMLparam3(queue, get, timeout);
    if (!Bool_val(get)) {
        al_wait_for_event_until(Ptr_val(queue), NULL, Data_custom_val(timeout));
        CAMLreturn(Val_none);
    }
    ALLEGRO_EVENT c_evt;
    if (!al_wait_for_event_until(Ptr_val(queue), &c_evt, Data_custom_val(timeout))) {
        CAMLreturn(Val_none);
    }
    CAMLreturn(caml_alloc_some(convert_event(c_evt)));
}
