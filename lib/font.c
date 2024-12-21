#include "graphics.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


CAMLprim value ml_al_init_font_addon(value unit)
{
    CAMLparam1(unit);
    if (!al_init_font_addon()) {
        caml_failwith("al_init_font_addon");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_font_addon_initialized, Val_bool)

ml_function_noarg(al_shutdown_font_addon)

ml_function_noarg_ret(al_get_allegro_font_version, Val_int)


CAMLprim value ml_al_load_font(value filename, value size, value flags)
{
    CAMLparam3(filename, size, flags);
    ALLEGRO_FONT *font = al_load_font(String_val(filename), Int_val(size), Int_val(flags));
    CAMLreturn(Val_ptr(font));
}

ml_function_1arg(al_destroy_font, Ptr_val)

ml_function_1arg_ret(al_get_font_line_height, Ptr_val, Val_int)

ml_function_1arg_ret(al_get_font_ascent, Ptr_val, Val_int)

ml_function_1arg_ret(al_get_font_descent, Ptr_val, Val_int)

CAMLprim value ml_al_get_text_width(value font, value str)
{
    CAMLparam2(font, str);
    int width = al_get_text_width(Ptr_val(font), String_val(str));
    CAMLreturn(Val_int(width));
}

CAMLprim value ml_al_draw_text(value font, value color, value pos, value flags, value text)
{
    CAMLparam5(font, color, pos, flags, text);
    al_draw_text(Ptr_val(font), AlColor_val(color),
        PosX_val(pos), PosY_val(pos), Int_val(flags), String_val(text));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_get_text_dimensions(value font, value text)
{
    CAMLparam2(font, text);
    int bbx, bby, bbw, bbh;
    al_get_text_dimensions(Ptr_val(font), String_val(text), &bbx, &bby, &bbw, &bbh);
    CAMLlocal1(bb);
    bb = caml_alloc_tuple(4);
    Store_field(bb, 0, Val_int(bbx));
    Store_field(bb, 1, Val_int(bby));
    Store_field(bb, 2, Val_int(bbw));
    Store_field(bb, 3, Val_int(bbh));
    CAMLreturn(bb);
}

CAMLprim value ml_al_set_fallback_font(value font, value fallback)
{
    CAMLparam2(font, fallback);
    if (Is_none(fallback)) {
        al_set_fallback_font(Ptr_val(font), NULL);
    } else {
        al_set_fallback_font(Ptr_val(font), Ptr_val(Some_val(fallback)));
    }
    CAMLreturn(Val_unit);
}

ml_function_1arg_ret(al_get_fallback_font, Ptr_val, Val_ptr)


ml_function_noarg_ret(al_create_builtin_font, Val_ptr)


CAMLprim value ml_al_init_ttf_addon(value unit)
{
    CAMLparam1(unit);
    if (!al_init_ttf_addon()) {
        caml_failwith("al_init_ttf_addon");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_ttf_addon_initialized, Val_bool)

ml_function_noarg(al_shutdown_ttf_addon)

ml_function_noarg_ret(al_get_allegro_ttf_version, Val_int)

CAMLprim value ml_al_load_ttf_font(value filename, value size, value flags)
{
    CAMLparam3(filename, size, flags);
    ALLEGRO_FONT *font = al_load_ttf_font(String_val(filename), Int_val(size), Int_val(flags));
    CAMLreturn(Val_ptr(font));
}

CAMLprim value ml_al_load_ttf_font_stretch(value filename, value w, value h, value flags)
{
    CAMLparam4(filename, w, h, flags);
    ALLEGRO_FONT *font = al_load_ttf_font_stretch(
        String_val(filename), Int_val(w), Int_val(h), Int_val(flags));
    CAMLreturn(Val_ptr(font));
}
