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


enum {
    ML_ALIGN_LEFT = 0,
    ML_ALIGN_CENTRE = 1 << 0,
    ML_ALIGN_RIGHT = 1 << 1,
    ML_ALIGN_INTEGER = 1 << 2,
};

static int const text_flags_conv[][2] = {
    { ML_ALIGN_LEFT, ALLEGRO_ALIGN_LEFT },
    { ML_ALIGN_CENTRE, ALLEGRO_ALIGN_CENTRE },
    { ML_ALIGN_RIGHT, ALLEGRO_ALIGN_RIGHT },
    { ML_ALIGN_INTEGER, ALLEGRO_ALIGN_INTEGER },
};

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
    int c_flags = convert_flags(Int_val(flags), text_flags_conv, 0);
    al_draw_text(Ptr_val(font), AlColor_val(color),
        PosX_val(pos), PosY_val(pos), c_flags, String_val(text));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_justified_text(value font, value color, value pos, value x2, value diff, value flags, value text)
{
    CAMLparam5(font, color, pos, x2, diff);
    CAMLxparam2(flags, text);
    int c_flags = convert_flags(Int_val(flags), text_flags_conv, 0);
    al_draw_justified_text(Ptr_val(font), AlColor_val(color),
        PosX_val(pos), Double_val(x2), PosY_val(pos), Double_val(diff),
        c_flags, String_val(text));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_justified_text_bytecode(value *argv, int argc)
{
    return ml_al_draw_justified_text(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5], argv[6]);
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

CAMLprim value ml_al_get_font_ranges(value font)
{
    CAMLparam1(font);
    int ranges_count = al_get_font_ranges(Ptr_val(font), 0, NULL);
    int c_ranges[ranges_count][2];
    al_get_font_ranges(Ptr_val(font), ranges_count, (int *)c_ranges);
    CAMLlocal2(ranges, rg);
    ranges = caml_alloc_tuple(ranges_count);
    for (int i = 0; i < ranges_count; ++i) {
        rg = caml_alloc_tuple(2);
        Store_field(rg, 0, Val_int(c_ranges[i][0]));
        Store_field(rg, 1, Val_int(c_ranges[i][1]));
        Store_field(ranges, i, rg);
    }
    CAMLreturn(ranges);
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


CAMLprim value ml_al_grab_font_from_bitmap(value bmp, value ranges)
{
    CAMLparam2(bmp, ranges);
    int ranges_n = Wosize_val(ranges);
    int c_ranges[ranges_n][2];
    for (int i = 0; i < ranges_n; ++i) {
        c_ranges[i][0] = Int_val(Field(Field(ranges, i), 0));
        c_ranges[i][1] = Int_val(Field(Field(ranges, i), 1));
    }
    ALLEGRO_FONT *font = al_grab_font_from_bitmap(Ptr_val(bmp), ranges_n, (int *)c_ranges);
    CAMLreturn(Val_ptr(font));
}

ml_function_1arg_ret(al_load_bitmap_font, String_val, Val_ptr)

CAMLprim value ml_al_load_bitmap_font_flags(value filename, value flags)
{
    CAMLparam2(filename, flags);
    int c_flags = convert_load_bitmap_flags_from_ml(flags);
    ALLEGRO_FONT *font = al_load_bitmap_font_flags(String_val(filename), c_flags);
    CAMLreturn(Val_ptr(font));
}

ml_function_noarg_ret(al_create_builtin_font, Val_ptr)


enum {
    ML_TTF_NO_KERNING = 1 << 0,
    ML_TTF_MONOCHROME = 1 << 1,
    ML_TTF_NO_AUTOHINT = 1 << 2,
};

static int const ttf_flags_conv[][2] = {
    { ML_TTF_NO_KERNING, ALLEGRO_TTF_NO_KERNING },
    { ML_TTF_MONOCHROME, ALLEGRO_TTF_MONOCHROME },
    { ML_TTF_NO_AUTOHINT, ALLEGRO_TTF_NO_AUTOHINT },
};

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
    int c_flags = convert_flags(Int_val(flags), ttf_flags_conv, 0);
    ALLEGRO_FONT *font = al_load_ttf_font(String_val(filename), Int_val(size), c_flags);
    CAMLreturn(Val_ptr(font));
}

CAMLprim value ml_al_load_ttf_font_stretch(value filename, value w, value h, value flags)
{
    CAMLparam4(filename, w, h, flags);
    int c_flags = convert_flags(Int_val(flags), ttf_flags_conv, 0);
    ALLEGRO_FONT *font = al_load_ttf_font_stretch(
        String_val(filename), Int_val(w), Int_val(h), c_flags);
    CAMLreturn(Val_ptr(font));
}
