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


CAMLprim value ml_al_draw_line(value pos1, value pos2, value color, value thickness)
{
    CAMLparam4(pos1, pos2, color, thickness);
    al_draw_line(PosX_val(pos1), PosY_val(pos1), PosX_val(pos2), PosY_val(pos2),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_circle(value cpos, value r, value color)
{
    CAMLparam3(cpos, r, color);
    al_draw_filled_circle(PosX_val(cpos), PosY_val(cpos), Double_val(r), AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_circle(value cpos, value r, value color, value thickness)
{
    CAMLparam4(cpos, r, color, thickness);
    al_draw_circle(PosX_val(cpos), PosY_val(cpos), Double_val(r), AlColor_val(color),
        Double_val(thickness));
    CAMLreturn(Val_unit);
}
