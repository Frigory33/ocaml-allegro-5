#include "al5.h"

#include <allegro5/allegro_image.h>


ml_function_noarg_ret(al_get_allegro_image_version, Val_int)

CAMLprim value ml_al_init_image_addon(value unit)
{
    CAMLparam1(unit);
    if (!al_init_image_addon()) {
        caml_failwith("al_init_image_addon");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_image_addon_initialized, Val_bool)

ml_function_noarg(al_shutdown_image_addon)
