#include "al5.h"


ml_function_noarg_ret(al_get_time, caml_copy_double)


static struct custom_operations allegro_timeout_ops = {
  "org.allegro5.timeout",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
  custom_fixed_length_default
};

CAMLprim value ml_al_init_timeout(value seconds)
{
    CAMLparam1(seconds);
    CAMLlocal1(timeout);
    timeout = caml_alloc_custom(&allegro_timeout_ops, sizeof(ALLEGRO_TIMEOUT), 1, 256);
    al_init_timeout(Data_custom_val(timeout), Double_val(seconds));
    CAMLreturn(timeout);
}


CAMLprim value ml_al_rest(value seconds)
{
    CAMLparam1(seconds);
    double c_secs = Double_val(seconds);

    caml_enter_blocking_section();
    al_rest(c_secs);
    caml_leave_blocking_section();

    CAMLreturn(Val_unit);
}
