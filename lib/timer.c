#include "al5.h"


CAMLprim value ml_al_create_timer(value speed_secs)
{
    CAMLparam1(speed_secs);
    ALLEGRO_TIMER *c_timer = al_create_timer(Double_val(speed_secs));
    if (c_timer == NULL) {
        caml_failwith("al_create_timer");
    }
    CAMLreturn(Val_ptr(c_timer));
}

ml_function_1arg(al_start_timer, Ptr_val)

ml_function_1arg(al_resume_timer, Ptr_val)

ml_function_1arg(al_stop_timer, Ptr_val)

ml_function_1arg_ret(al_get_timer_started, Ptr_val, Val_bool)

ml_function_1arg(al_destroy_timer, Ptr_val)

ml_function_1arg_ret(al_get_timer_count, Ptr_val, caml_copy_int64)

CAMLprim value ml_al_set_timer_count(value timer, value new_count)
{
    CAMLparam2(timer, new_count);
    al_set_timer_count(Ptr_val(timer), Int64_val(new_count));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_add_timer_count(value timer, value diff)
{
    CAMLparam2(timer, diff);
    al_add_timer_count(Ptr_val(timer), Int64_val(diff));
    CAMLreturn(Val_unit);
}

ml_function_1arg_ret(al_get_timer_speed, Ptr_val, caml_copy_double)

CAMLprim value ml_al_set_timer_speed(value timer, value new_speed_secs)
{
    CAMLparam2(timer, new_speed_secs);
    al_set_timer_speed(Ptr_val(timer), Double_val(new_speed_secs));
    CAMLreturn(Val_unit);
}

ml_function_1arg_ret(al_get_timer_event_source, Ptr_val, Val_ptr)
