#include "graphics.h"


static struct custom_operations allegro_color_ops = {
  "org.allegro5.color",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
  custom_fixed_length_default
};

static value alloc_color(ALLEGRO_COLOR c_color)
{
    CAMLparam0();
    CAMLlocal1(v);
    v = caml_alloc_custom(&allegro_color_ops, sizeof(c_color), 1, 256);
    AlColor_val(v) = c_color;
    CAMLreturn(v);
}

CAMLprim value ml_al_map_rgb(value r, value g, value b)
{
    CAMLparam3(r, g, b);
    ALLEGRO_COLOR c_color = al_map_rgb(Int_val(r), Int_val(g), Int_val(b));
    CAMLreturn(alloc_color(c_color));
}

CAMLprim value ml_al_map_rgba(value r, value g, value b, value a)
{
    CAMLparam4(r, g, b, a);
    ALLEGRO_COLOR c_color = al_map_rgba(Int_val(r), Int_val(g), Int_val(b), Int_val(a));
    CAMLreturn(alloc_color(c_color));
}

CAMLprim value ml_al_premul_rgba(value r, value g, value b, value a)
{
    CAMLparam4(r, g, b, a);
    ALLEGRO_COLOR c_color = al_premul_rgba(Int_val(r), Int_val(g), Int_val(b), Int_val(a));
    CAMLreturn(alloc_color(c_color));
}

CAMLprim value ml_al_map_rgb_f(value r, value g, value b)
{
    CAMLparam3(r, g, b);
    ALLEGRO_COLOR c_color = al_map_rgb_f(Double_val(r), Double_val(g), Double_val(b));
    CAMLreturn(alloc_color(c_color));
}

CAMLprim value ml_al_map_rgba_f(value r, value g, value b, value a)
{
    CAMLparam4(r, g, b, a);
    ALLEGRO_COLOR c_color = al_map_rgba_f(Double_val(r), Double_val(g), Double_val(b), Double_val(a));
    CAMLreturn(alloc_color(c_color));
}

CAMLprim value ml_al_premul_rgba_f(value r, value g, value b, value a)
{
    CAMLparam4(r, g, b, a);
    ALLEGRO_COLOR c_color = al_premul_rgba_f(Double_val(r), Double_val(g), Double_val(b), Double_val(a));
    CAMLreturn(alloc_color(c_color));
}

CAMLprim value ml_al_unmap_rgb(value color)
{
    CAMLparam1(color);
    unsigned char c_r, c_g, c_b;
    al_unmap_rgb(AlColor_val(color), &c_r, &c_g, &c_b);
    CAMLlocal1(rgb);
    rgb = caml_alloc_tuple(3);
    Store_field(rgb, 0, Val_int(c_r));
    Store_field(rgb, 1, Val_int(c_g));
    Store_field(rgb, 2, Val_int(c_b));
    CAMLreturn(rgb);
}

CAMLprim value ml_al_unmap_rgba(value color)
{
    CAMLparam1(color);
    unsigned char c_r, c_g, c_b, c_a;
    al_unmap_rgba(AlColor_val(color), &c_r, &c_g, &c_b, &c_a);
    CAMLlocal1(rgba);
    rgba = caml_alloc_tuple(4);
    Store_field(rgba, 0, Val_int(c_r));
    Store_field(rgba, 1, Val_int(c_g));
    Store_field(rgba, 2, Val_int(c_b));
    Store_field(rgba, 3, Val_int(c_a));
    CAMLreturn(rgba);
}

CAMLprim value ml_al_unmap_rgb_f(value color)
{
    CAMLparam1(color);
    float c_r, c_g, c_b;
    al_unmap_rgb_f(AlColor_val(color), &c_r, &c_g, &c_b);
    CAMLlocal1(rgb);
    rgb = caml_alloc_tuple(3);
    Store_field(rgb, 0, caml_copy_double(c_r));
    Store_field(rgb, 1, caml_copy_double(c_g));
    Store_field(rgb, 2, caml_copy_double(c_b));
    CAMLreturn(rgb);
}

CAMLprim value ml_al_unmap_rgba_f(value color)
{
    CAMLparam1(color);
    float c_r, c_g, c_b, c_a;
    al_unmap_rgba_f(AlColor_val(color), &c_r, &c_g, &c_b, &c_a);
    CAMLlocal1(rgba);
    rgba = caml_alloc_tuple(4);
    Store_field(rgba, 0, caml_copy_double(c_r));
    Store_field(rgba, 1, caml_copy_double(c_g));
    Store_field(rgba, 2, caml_copy_double(c_b));
    Store_field(rgba, 3, caml_copy_double(c_a));
    CAMLreturn(rgba);
}


enum {
    ML_ALLEGRO_FLIP_HORIZONTAL = 1 << 0,
    ML_ALLEGRO_FLIP_VERTICAL = 1 << 1,
};

static int convert_draw_bitmap_flags(value flags)
{
    CAMLparam1(flags);
    int flip_horiz = (Int_val(flags) & ML_ALLEGRO_FLIP_HORIZONTAL) == ML_ALLEGRO_FLIP_HORIZONTAL ? ALLEGRO_FLIP_HORIZONTAL : 0;
    int flip_vertic = (Int_val(flags) & ML_ALLEGRO_FLIP_VERTICAL) == ML_ALLEGRO_FLIP_VERTICAL ? ALLEGRO_FLIP_VERTICAL : 0;
    CAMLreturnT(int, flip_horiz | flip_vertic);
}

CAMLprim value ml_al_draw_bitmap(value bmp, value tint, value dpos, value flags)
{
    CAMLparam4(bmp, tint, dpos, flags);
    if (Is_none(tint)) {
        al_draw_bitmap(Ptr_val(bmp), PosX_val(dpos), PosY_val(dpos), convert_draw_bitmap_flags(flags));
    } else {
        al_draw_tinted_bitmap(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(dpos), PosY_val(dpos), convert_draw_bitmap_flags(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_bitmap_region(value bmp, value tint, value spos, value ssize, value dpos, value flags)
{
    CAMLparam5(bmp, tint, spos, ssize, dpos);
    CAMLxparam1(flags);
    if (Is_none(tint)) {
        al_draw_bitmap_region(Ptr_val(bmp),
            PosX_val(spos), PosY_val(spos),
            PosX_val(ssize), PosY_val(ssize),
            PosX_val(dpos), PosY_val(dpos), convert_draw_bitmap_flags(flags));
    } else {
        al_draw_tinted_bitmap_region(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(spos), PosY_val(spos),
            PosX_val(ssize), PosY_val(ssize),
            PosX_val(dpos), PosY_val(dpos), convert_draw_bitmap_flags(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_bitmap_region_bytecode(value * argv, int argc)
{
    return ml_al_draw_bitmap_region(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}


CAMLprim value ml_al_get_bitmap_width(value bmp)
{
    CAMLparam1(bmp);
    CAMLreturn(Val_int(al_get_bitmap_width(Ptr_val(bmp))));
}

CAMLprim value ml_al_get_bitmap_height(value bmp)
{
    CAMLparam1(bmp);
    CAMLreturn(Val_int(al_get_bitmap_height(Ptr_val(bmp))));
}


CAMLprim value ml_al_load_bitmap(value filename)
{
    CAMLparam1(filename);
    ALLEGRO_BITMAP *c_bmp = al_load_bitmap(String_val(filename));
    if (c_bmp == NULL) {
        char const *c_func = "al_load_bitmap",
            *c_filename = String_val(filename);
        char c_msg[strlen(c_func) + 1 + strlen(c_filename) + 1];
        sprintf(c_msg, "%s %s", c_func, c_filename);
        caml_failwith_value(caml_copy_string(c_msg));
    }
    CAMLreturn(Val_ptr(c_bmp));
}


ml_function_1arg(al_clear_to_color, AlColor_val)
