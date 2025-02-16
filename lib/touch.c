#include "al5.h"


CAMLprim value ml_al_install_touch_input(value unit)
{
    CAMLparam1(unit);
    if (!al_install_touch_input()) {
        caml_failwith("al_install_touch_input");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_touch_input_installed, Val_bool)

ml_function_noarg(al_uninstall_touch_input)

ml_function_noarg_ret(al_get_touch_input_event_source, Val_ptr)


CAMLprim value ml_al_get_touch_input_state(value unit)
{
    CAMLparam1(unit);
    ALLEGRO_TOUCH_INPUT_STATE c_state;
    al_get_touch_input_state(&c_state);
    int valid_count = 0;
    for (int i = 0; i < ALLEGRO_TOUCH_INPUT_MAX_TOUCH_COUNT; ++i) {
        if (c_state.touches[i].id >= 0) {
            ++valid_count;
        }
    }
    CAMLlocal2(state, touch);
    state = caml_alloc_tuple(valid_count);
    valid_count = 0;
    for (int i = 0; i < ALLEGRO_TOUCH_INPUT_MAX_TOUCH_COUNT; ++i) {
        ALLEGRO_TOUCH_STATE c_touch = c_state.touches[i];
        if (c_touch.id >= 0) {
            touch = caml_alloc_tuple(7);
            Store_field(touch, 0, Val_int(c_touch.id));
            Store_field(touch, 1, caml_copy_double(c_touch.x));
            Store_field(touch, 2, caml_copy_double(c_touch.y));
            Store_field(touch, 3, caml_copy_double(c_touch.dx));
            Store_field(touch, 4, caml_copy_double(c_touch.dy));
            Store_field(touch, 5, Val_bool(c_touch.primary));
            Store_field(touch, 6, Val_ptr(c_touch.display));
            Store_field(state, valid_count, touch);
            ++valid_count;
        }
    }
    CAMLreturn(state);
}
