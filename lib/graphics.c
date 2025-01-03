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


CAMLprim value ml_al_create_bitmap(value w, value h)
{
    CAMLparam2(w, h);
    ALLEGRO_BITMAP *c_bmp = al_create_bitmap(Int_val(w), Int_val(h));
    CAMLreturn(Val_ptr(c_bmp));
}

CAMLprim value ml_al_create_sub_bitmap(value parent, value x, value y, value w, value h)
{
    CAMLparam5(parent, x, y, w, h);
    ALLEGRO_BITMAP *c_bmp = al_create_sub_bitmap(Ptr_val(parent),
        Int_val(x), Int_val(y), Int_val(w), Int_val(h));
    CAMLreturn(Val_ptr(c_bmp));
}

ml_function_1arg_ret(al_clone_bitmap, Ptr_val, Val_ptr)

ml_function_1arg(al_convert_bitmap, Ptr_val)

ml_function_noarg(al_convert_memory_bitmaps)

ml_function_1arg(al_destroy_bitmap, Ptr_val)


ml_function_1arg_ret(al_get_bitmap_width, Ptr_val, Val_int)

ml_function_1arg_ret(al_get_bitmap_height, Ptr_val, Val_int)


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

ml_function_1arg(al_clear_to_color, AlColor_val)

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

CAMLprim value ml_al_draw_rotated_bitmap(value bmp, value tint, value cpos, value dpos, value angle, value flags)
{
    CAMLparam5(bmp, tint, cpos, dpos, angle);
    CAMLxparam1(flags);
    if (Is_none(tint)) {
        al_draw_rotated_bitmap(Ptr_val(bmp),
            PosX_val(cpos), PosY_val(cpos), PosX_val(dpos), PosY_val(dpos),
            Double_val(angle), convert_draw_bitmap_flags(flags));
    } else {
        al_draw_tinted_rotated_bitmap(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(cpos), PosY_val(cpos), PosX_val(dpos), PosY_val(dpos),
            Double_val(angle), convert_draw_bitmap_flags(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_rotated_bitmap_bytecode(value * argv, int argc)
{
    return ml_al_draw_rotated_bitmap(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value ml_al_draw_scaled_bitmap(value bmp, value tint, value spos, value ssize, value dpos, value dsize, value flags)
{
    CAMLparam5(bmp, tint, spos, ssize, dpos);
    CAMLxparam2(dsize, flags);
    if (Is_none(tint)) {
        al_draw_scaled_bitmap(Ptr_val(bmp),
            PosX_val(spos), PosY_val(spos), PosX_val(ssize), PosY_val(ssize),
            PosX_val(dpos), PosY_val(dpos), PosX_val(dsize), PosY_val(dsize),
            convert_draw_bitmap_flags(flags));
    } else {
        al_draw_tinted_scaled_bitmap(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(spos), PosY_val(spos), PosX_val(ssize), PosY_val(ssize),
            PosX_val(dpos), PosY_val(dpos), PosX_val(dsize), PosY_val(dsize),
            convert_draw_bitmap_flags(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_scaled_bitmap_bytecode(value * argv, int argc)
{
    return ml_al_draw_scaled_bitmap(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5], argv[6]);
}

CAMLprim value ml_al_draw_scaled_rotated_bitmap(value bmp, value tint, value cpos, value dpos, value scale, value angle, value flags)
{
    CAMLparam5(bmp, tint, cpos, dpos, scale);
    CAMLxparam2(angle, flags);
    if (Is_none(tint)) {
        al_draw_scaled_rotated_bitmap(Ptr_val(bmp),
            PosX_val(cpos), PosY_val(cpos), PosX_val(dpos), PosY_val(dpos),
            PosX_val(scale), PosY_val(scale),
            Double_val(angle), convert_draw_bitmap_flags(flags));
    } else {
        al_draw_tinted_scaled_rotated_bitmap(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(cpos), PosY_val(cpos), PosX_val(dpos), PosY_val(dpos),
            PosX_val(scale), PosY_val(scale),
            Double_val(angle), convert_draw_bitmap_flags(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_scaled_rotated_bitmap_bytecode(value * argv, int argc)
{
    return ml_al_draw_scaled_rotated_bitmap(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5], argv[6]);
}

CAMLprim value ml_al_draw_scaled_rotated_bitmap_region(
    value bmp, value spos, value ssize, value tint, value cpos, value dpos, value scale, value angle, value flags)
{
    CAMLparam5(bmp, spos, ssize, tint, cpos);
    CAMLxparam4(dpos, scale, angle, flags);
    al_draw_tinted_scaled_rotated_bitmap_region(Ptr_val(bmp),
        PosX_val(spos), PosY_val(spos), PosX_val(ssize), PosY_val(ssize),
        Is_none(tint) ? al_map_rgb(255, 255, 255) : AlColor_val(Some_val(tint)),
        PosX_val(cpos), PosY_val(cpos), PosX_val(dpos), PosY_val(dpos),
        PosX_val(scale), PosY_val(scale),
        Double_val(angle), convert_draw_bitmap_flags(flags));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_scaled_rotated_bitmap_region_bytecode(value * argv, int argc)
{
    return ml_al_draw_scaled_rotated_bitmap_region(argv[0], argv[1], argv[2],
        argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}


ml_function_noarg_ret(al_get_target_bitmap, Val_ptr)

ml_function_1arg(al_set_target_bitmap, Ptr_val)

ml_function_1arg(al_set_target_backbuffer, Ptr_val)

ml_function_noarg_ret(al_get_current_display, Val_ptr)


enum {
    ML_NO_PREMULTIPLIED_ALPHA = 1 << 0,
    ML_KEEP_INDEX = 1 << 1,
    ML_KEEP_BITMAP_FORMAT = 1 << 2,
};

static int const load_flags_conv[][2] = {
    { ML_NO_PREMULTIPLIED_ALPHA, ALLEGRO_NO_PREMULTIPLIED_ALPHA },
    { ML_KEEP_INDEX, ALLEGRO_KEEP_INDEX },
    { ML_KEEP_BITMAP_FORMAT, ALLEGRO_KEEP_BITMAP_FORMAT },
};

int convert_load_bitmap_flags_from_ml(value flags)
{
    CAMLparam1(flags);
    CAMLreturnT(int, convert_flags(Int_val(flags), load_flags_conv, 0));
}

CAMLprim value ml_al_load_bitmap_flags(value filename, value flags)
{
    CAMLparam2(filename, flags);
    int c_flags = convert_load_bitmap_flags_from_ml(flags);
    ALLEGRO_BITMAP *c_bmp = al_load_bitmap_flags(String_val(filename), c_flags);
    if (c_bmp == NULL) {
        char const *c_func = "al_load_bitmap",
            *c_filename = String_val(filename);
        char c_msg[strlen(c_func) + 1 + strlen(c_filename) + 1];
        sprintf(c_msg, "%s %s", c_func, c_filename);
        caml_failwith_value(caml_copy_string(c_msg));
    }
    CAMLreturn(Val_ptr(c_bmp));
}

CAMLprim value ml_al_load_bitmap(value filename)
{
    CAMLparam1(filename);
    CAMLreturn(ml_al_load_bitmap_flags(filename, Val_int(0)));
}
