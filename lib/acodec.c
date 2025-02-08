#include "al5.h"

#include <allegro5/allegro_acodec.h>


CAMLprim value ml_al_init_acodec_addon(value unit)
{
    CAMLparam1(unit);
    if (!al_init_acodec_addon()) {
        caml_failwith("al_init_acodec_addon");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_acodec_addon_initialized, Val_bool)

ml_function_noarg_ret(al_get_allegro_acodec_version, Val_int)
