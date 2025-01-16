#include "al5.h"


CAMLprim value ml_al_install_mouse(value unit)
{
    CAMLparam1(unit);
    if (!al_install_mouse()) {
        caml_failwith("al_install_mouse");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_mouse_installed, Val_bool)

ml_function_noarg(al_uninstall_mouse)

ml_function_noarg_ret(al_get_mouse_event_source, Val_ptr)


#define MouseState_val(v) (*((ALLEGRO_MOUSE_STATE *)Data_custom_val(v)))
#define MOUSE_STATE_INDEX 6

static struct custom_operations allegro_mouse_state_ops = {
  "org.allegro5.mouse_state",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
  custom_fixed_length_default
};

ml_function_noarg_ret(al_get_mouse_num_axes, Val_int);

ml_function_noarg_ret(al_get_mouse_num_buttons, Val_int);

CAMLprim value ml_al_get_mouse_state(value unit)
{
    CAMLparam1(unit);
    CAMLlocal2(state, state_priv);
    ALLEGRO_MOUSE_STATE c_state;
    al_get_mouse_state(&c_state);
    state = caml_alloc_tuple(7);
    Store_field(state, 0, Val_int(c_state.x));
    Store_field(state, 1, Val_int(c_state.y));
    Store_field(state, 2, Val_int(c_state.z));
    Store_field(state, 3, Val_int(c_state.w));
    Store_field(state, 4, Val_int(c_state.buttons));
    Store_field(state, 5, caml_copy_double(c_state.pressure));
    state_priv = caml_alloc_custom(&allegro_mouse_state_ops, sizeof(ALLEGRO_MOUSE_STATE), 1, 64);
    MouseState_val(state_priv) = c_state;
    Store_field(state, MOUSE_STATE_INDEX, state_priv);
    CAMLreturn(state);
}

CAMLprim value ml_al_get_mouse_state_axis(value state, value axis)
{
    CAMLparam2(state, axis);
    CAMLlocal1(state_priv);
    state_priv = Field(state, MOUSE_STATE_INDEX);
    int c_pos = al_get_mouse_state_axis(&MouseState_val(state_priv), Int_val(axis));
    CAMLreturn(Val_int(c_pos));
}

CAMLprim value ml_al_mouse_button_down(value state, value button)
{
    CAMLparam2(state, button);
    CAMLlocal1(state_priv);
    state_priv = Field(state, MOUSE_STATE_INDEX);
    bool c_down = al_mouse_button_down(&MouseState_val(state_priv), Int_val(button));
    CAMLreturn(Val_bool(c_down));
}


CAMLprim value ml_al_set_mouse_xy(value display, value x, value y)
{
    CAMLparam3(display, x, y);
    bool success = al_set_mouse_xy(Ptr_val(display), Int_val(x), Int_val(y));
    CAMLreturn(Val_bool(success));
}

ml_function_1arg_ret(al_set_mouse_z, Int_val, Val_bool)

ml_function_1arg_ret(al_set_mouse_w, Int_val, Val_bool)

CAMLprim value ml_al_set_mouse_axis(value which, value pos)
{
    CAMLparam2(which, pos);
    bool success = al_set_mouse_axis(Int_val(which), Int_val(pos));
    CAMLreturn(Val_bool(success));
}

ml_function_1arg(al_set_mouse_wheel_precision, Int_val)

ml_function_noarg_ret(al_get_mouse_wheel_precision, Val_int)
