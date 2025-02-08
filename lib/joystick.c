#include "al5.h"


CAMLprim value ml_al_install_joystick(value unit)
{
    CAMLparam1(unit);
    if (!al_install_joystick()) {
        caml_failwith("al_install_joystick");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_joystick_installed, Val_bool)

ml_function_noarg(al_uninstall_joystick)

ml_function_noarg_ret(al_get_joystick_event_source, Val_ptr)

ml_function_noarg_ret(al_reconfigure_joysticks, Val_bool)


ml_function_noarg_ret(al_get_num_joysticks, Val_int)

ml_function_1arg_ret(al_get_joystick, Int_val, Val_ptr)

ml_function_1arg(al_release_joystick, Ptr_val)

ml_function_1arg_ret(al_get_joystick_active, Ptr_val, Val_bool)

ml_function_1arg_ret(al_get_joystick_name, Ptr_val, caml_copy_string)

CAMLprim value ml_al_get_joystick_stick_name(value joy, value stick)
{
    CAMLparam2(joy, stick);
    char const * c_name = al_get_joystick_stick_name(Ptr_val(joy), Int_val(stick));
    if (c_name != NULL) {
        CAMLreturn(caml_alloc_some(caml_copy_string(c_name)));
    }
    CAMLreturn(Val_none);
}

CAMLprim value ml_al_get_joystick_axis_name(value joy, value stick, value axis)
{
    CAMLparam3(joy, stick, axis);
    char const * c_name = al_get_joystick_axis_name(Ptr_val(joy), Int_val(stick), Int_val(axis));
    if (c_name != NULL) {
        CAMLreturn(caml_alloc_some(caml_copy_string(c_name)));
    }
    CAMLreturn(Val_none);
}

CAMLprim value ml_al_get_joystick_button_name(value joy, value button)
{
    CAMLparam2(joy, button);
    char const * c_name = al_get_joystick_button_name(Ptr_val(joy), Int_val(button));
    if (c_name != NULL) {
        CAMLreturn(caml_alloc_some(caml_copy_string(c_name)));
    }
    CAMLreturn(Val_none);
}

CAMLprim value ml_al_is_joystick_stick_analogue(value joy, value stick)
{
    CAMLparam2(joy, stick);
    int c_flags = al_get_joystick_stick_flags(Ptr_val(joy), Int_val(stick));
    CAMLreturn(Val_bool((c_flags & ALLEGRO_JOYFLAG_ANALOGUE) == ALLEGRO_JOYFLAG_ANALOGUE));
}

ml_function_1arg_ret(al_get_joystick_num_sticks, Ptr_val, Val_int)

CAMLprim value ml_al_get_joystick_num_axes(value joy, value stick)
{
    CAMLparam2(joy, stick);
    int c_num_axes = al_get_joystick_num_axes(Ptr_val(joy), Int_val(stick));
    CAMLreturn(Val_int(c_num_axes));
}

ml_function_1arg_ret(al_get_joystick_num_buttons, Ptr_val, Val_int)


#define JoyState_val(v) (*((ALLEGRO_JOYSTICK_STATE *)Data_custom_val(v)))

static struct custom_operations allegro_joy_state_ops = {
  "org.allegro5.joystick_state",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
  custom_fixed_length_default
};

CAMLprim value ml_al_get_joystick_state(value joy)
{
    CAMLparam1(joy);
    CAMLlocal1(state);
    ALLEGRO_JOYSTICK_STATE c_state;
    al_get_joystick_state(Ptr_val(joy), &c_state);
    state = caml_alloc_custom(&allegro_joy_state_ops, sizeof(ALLEGRO_JOYSTICK_STATE), 1, 64);
    JoyState_val(state) = c_state;
    CAMLreturn(state);
}

CAMLprim value ml_al_get_joystick_state_axis(value state, value stick, value axis)
{
    CAMLparam3(state, stick, axis);
    float c_val = JoyState_val(state).stick[Int_val(stick)].axis[Int_val(axis)];
    CAMLreturn(caml_copy_double(c_val));
}

CAMLprim value ml_al_get_joystick_state_button(value state, value button)
{
    CAMLparam2(state, button);
    int c_val = JoyState_val(state).button[Int_val(button)];
    CAMLreturn(Val_int(c_val));
}
