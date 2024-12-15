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

CAMLprim value ml_al_draw_triangle(value pos1, value pos2, value pos3, value color, value thickness)
{
    CAMLparam5(pos1, pos2, pos3, color, thickness);
    al_draw_triangle(
        PosX_val(pos1), PosY_val(pos1),
        PosX_val(pos2), PosY_val(pos2),
        PosX_val(pos3), PosY_val(pos3),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_triangle(value pos1, value pos2, value pos3, value color)
{
    CAMLparam4(pos1, pos2, pos3, color);
    al_draw_filled_triangle(
        PosX_val(pos1), PosY_val(pos1),
        PosX_val(pos2), PosY_val(pos2),
        PosX_val(pos3), PosY_val(pos3),
        AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_rectangle(value pos1, value pos2, value color, value thickness)
{
    CAMLparam4(pos1, pos2, color, thickness);
    al_draw_rectangle(PosX_val(pos1), PosY_val(pos1), PosX_val(pos2), PosY_val(pos2),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_rectangle(value pos1, value pos2, value color)
{
    CAMLparam3(pos1, pos2, color);
    al_draw_filled_rectangle(PosX_val(pos1), PosY_val(pos1), PosX_val(pos2), PosY_val(pos2),
        AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_rounded_rectangle(value pos1, value pos2, value r, value color, value thickness)
{
    CAMLparam5(pos1, pos2, r, color, thickness);
    al_draw_rounded_rectangle(
        PosX_val(pos1), PosY_val(pos1),
        PosX_val(pos2), PosY_val(pos2),
        PosX_val(r), PosY_val(r),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_rounded_rectangle(value pos1, value pos2, value r, value color)
{
    CAMLparam4(pos1, pos2, r, color);
    al_draw_filled_rounded_rectangle(
        PosX_val(pos1), PosY_val(pos1),
        PosX_val(pos2), PosY_val(pos2),
        PosX_val(r), PosY_val(r),
        AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_pieslice(value cpos, value r, value start_theta, value delta_theta, value color, value thickness)
{
    CAMLparam5(cpos, r, start_theta, delta_theta, color);
    CAMLxparam1(thickness);
    al_draw_pieslice(PosX_val(cpos), PosY_val(cpos), Double_val(r),
        Double_val(start_theta), Double_val(delta_theta),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_pieslice_bytecode(value * argv, int argc)
{
    return ml_al_draw_pieslice(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value ml_al_draw_filled_pieslice(value cpos, value r, value start_theta, value delta_theta, value color)
{
    CAMLparam5(cpos, r, start_theta, delta_theta, color);
    al_draw_filled_pieslice(PosX_val(cpos), PosY_val(cpos), Double_val(r),
        Double_val(start_theta), Double_val(delta_theta), AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_ellipse(value cpos, value r, value color, value thickness)
{
    CAMLparam4(cpos, r, color, thickness);
    al_draw_ellipse(PosX_val(cpos), PosY_val(cpos), PosX_val(r), PosY_val(r),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_ellipse(value cpos, value r, value color)
{
    CAMLparam3(cpos, r, color);
    al_draw_filled_ellipse(PosX_val(cpos), PosY_val(cpos), PosX_val(r), PosY_val(r), AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_circle(value cpos, value r, value color, value thickness)
{
    CAMLparam4(cpos, r, color, thickness);
    al_draw_circle(PosX_val(cpos), PosY_val(cpos), Double_val(r), AlColor_val(color),
        Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_filled_circle(value cpos, value r, value color)
{
    CAMLparam3(cpos, r, color);
    al_draw_filled_circle(PosX_val(cpos), PosY_val(cpos), Double_val(r), AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_arc(value cpos, value r, value start_theta, value delta_theta, value color, value thickness)
{
    CAMLparam5(cpos, r, start_theta, delta_theta, color);
    CAMLxparam1(thickness);
    al_draw_arc(PosX_val(cpos), PosY_val(cpos), Double_val(r),
        Double_val(start_theta), Double_val(delta_theta),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_arc_bytecode(value * argv, int argc)
{
    return ml_al_draw_arc(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value ml_al_draw_elliptical_arc(value cpos, value r, value start_theta, value delta_theta, value color, value thickness)
{
    CAMLparam5(cpos, r, start_theta, delta_theta, color);
    CAMLxparam1(thickness);
    al_draw_elliptical_arc(PosX_val(cpos), PosY_val(cpos), PosX_val(r), PosY_val(r),
        Double_val(start_theta), Double_val(delta_theta),
        AlColor_val(color), Double_val(thickness));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_elliptical_arc_bytecode(value * argv, int argc)
{
    return ml_al_draw_elliptical_arc(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}
