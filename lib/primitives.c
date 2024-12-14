#include "graphics.h"

#include <allegro5/allegro_primitives.h>


ml_function_noarg_ret(al_get_allegro_primitives_version, Val_int)

CAMLprim value ml_al_init_primitives_addon(value unit)
{
    CAMLparam1(unit);
    if (!al_init_primitives_addon()) {
        caml_failwith("al_init_primitives_addon");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_primitives_addon_initialized, Val_bool)

ml_function_noarg(al_shutdown_primitives_addon)


CAMLprim value ml_al_draw_filled_circle(value c, value r, value color)
{
    CAMLparam3(c, r, color);
    al_draw_filled_circle(PosX_val(c), PosY_val(c), Double_val(r), AlColor_val(color));
    CAMLreturn(Val_unit);
}
