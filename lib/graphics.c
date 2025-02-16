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

CAMLprim value ml_al_get_pixel(value bitmap, value x, value y)
{
    CAMLparam3(bitmap, x, y);
    ALLEGRO_COLOR c_color = al_get_pixel(Ptr_val(bitmap), Int_val(x), Int_val(y));
    CAMLreturn(alloc_color(c_color));
}


enum {
    ML_ALLEGRO_FLIP_HORIZONTAL = 1 << 0,
    ML_ALLEGRO_FLIP_VERTICAL = 1 << 1,
};

static int convert_draw_bitmap_flags_from_ml(value flags)
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
        al_draw_bitmap(Ptr_val(bmp), PosX_val(dpos), PosY_val(dpos),
            convert_draw_bitmap_flags_from_ml(flags));
    } else {
        al_draw_tinted_bitmap(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(dpos), PosY_val(dpos), convert_draw_bitmap_flags_from_ml(flags));
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
            PosX_val(dpos), PosY_val(dpos), convert_draw_bitmap_flags_from_ml(flags));
    } else {
        al_draw_tinted_bitmap_region(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(spos), PosY_val(spos),
            PosX_val(ssize), PosY_val(ssize),
            PosX_val(dpos), PosY_val(dpos), convert_draw_bitmap_flags_from_ml(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_bitmap_region_bytecode(value *argv, int argc)
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
            Double_val(angle), convert_draw_bitmap_flags_from_ml(flags));
    } else {
        al_draw_tinted_rotated_bitmap(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(cpos), PosY_val(cpos), PosX_val(dpos), PosY_val(dpos),
            Double_val(angle), convert_draw_bitmap_flags_from_ml(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_rotated_bitmap_bytecode(value *argv, int argc)
{
    return ml_al_draw_rotated_bitmap(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5]);
}

CAMLprim value ml_al_draw_scaled_bitmap(
    value bmp, value tint, value spos, value ssize, value dpos, value dsize, value flags)
{
    CAMLparam5(bmp, tint, spos, ssize, dpos);
    CAMLxparam2(dsize, flags);
    if (Is_none(tint)) {
        al_draw_scaled_bitmap(Ptr_val(bmp),
            PosX_val(spos), PosY_val(spos), PosX_val(ssize), PosY_val(ssize),
            PosX_val(dpos), PosY_val(dpos), PosX_val(dsize), PosY_val(dsize),
            convert_draw_bitmap_flags_from_ml(flags));
    } else {
        al_draw_tinted_scaled_bitmap(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(spos), PosY_val(spos), PosX_val(ssize), PosY_val(ssize),
            PosX_val(dpos), PosY_val(dpos), PosX_val(dsize), PosY_val(dsize),
            convert_draw_bitmap_flags_from_ml(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_scaled_bitmap_bytecode(value *argv, int argc)
{
    return ml_al_draw_scaled_bitmap(argv[0], argv[1],
        argv[2], argv[3], argv[4], argv[5], argv[6]);
}

CAMLprim value ml_al_draw_scaled_rotated_bitmap(
    value bmp, value tint, value cpos, value dpos, value scale, value angle, value flags)
{
    CAMLparam5(bmp, tint, cpos, dpos, scale);
    CAMLxparam2(angle, flags);
    if (Is_none(tint)) {
        al_draw_scaled_rotated_bitmap(Ptr_val(bmp),
            PosX_val(cpos), PosY_val(cpos), PosX_val(dpos), PosY_val(dpos),
            PosX_val(scale), PosY_val(scale),
            Double_val(angle), convert_draw_bitmap_flags_from_ml(flags));
    } else {
        al_draw_tinted_scaled_rotated_bitmap(Ptr_val(bmp), AlColor_val(Some_val(tint)),
            PosX_val(cpos), PosY_val(cpos), PosX_val(dpos), PosY_val(dpos),
            PosX_val(scale), PosY_val(scale),
            Double_val(angle), convert_draw_bitmap_flags_from_ml(flags));
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_scaled_rotated_bitmap_bytecode(value *argv, int argc)
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
        Double_val(angle), convert_draw_bitmap_flags_from_ml(flags));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_draw_scaled_rotated_bitmap_region_bytecode(value *argv, int argc)
{
    return ml_al_draw_scaled_rotated_bitmap_region(argv[0], argv[1], argv[2],
        argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}

CAMLprim value ml_al_put_pixel(value x, value y, value color)
{
    CAMLparam3(x, y, color);
    al_put_pixel(Int_val(x), Int_val(y), AlColor_val(color));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_put_blended_pixel(value x, value y, value color)
{
    CAMLparam3(x, y, color);
    al_put_blended_pixel(Int_val(x), Int_val(y), AlColor_val(color));
    CAMLreturn(Val_unit);
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
    int c_flags = convert_flags(Int_val(flags), load_flags_conv, 0);
    CAMLreturnT(int, c_flags);
}

value convert_load_bitmap_flags_from_c(int c_flags)
{
    int flags = convert_flags(c_flags, load_flags_conv, 1);
    return Val_int(flags);
}


static struct {
    char extension[16];
    value loader;
} bitmap_loaders[64] = {};

static struct {
    char extension[16];
    value saver;
} bitmap_savers[64] = {};

static ALLEGRO_BITMAP *bitmap_loader(char const *filename, int flags)
{
    CAMLparam0();
    char const *extension = strrchr(filename, '.');
    if (extension == NULL) {
        CAMLreturnT(ALLEGRO_BITMAP *, NULL);
    }
    CAMLlocal1(bitmap);
    for (int i = 0; i < sizeof(bitmap_loaders) / sizeof(*bitmap_loaders); ++i) {
        if (strcmp(extension, bitmap_loaders[i].extension) == 0) {
            bitmap = caml_callback2(
                bitmap_loaders[i].loader, caml_copy_string(filename),
                convert_load_bitmap_flags_from_c(flags));
            CAMLreturnT(ALLEGRO_BITMAP *, Is_none(bitmap) ? NULL : Ptr_val(bitmap));
        }
    }
    CAMLreturnT(ALLEGRO_BITMAP *, NULL);
}

static bool bitmap_saver(char const *filename, ALLEGRO_BITMAP *bmp)
{
    CAMLparam0();
    char const *extension = strrchr(filename, '.');
    if (extension == NULL) {
        CAMLreturnT(bool, false);
    }
    CAMLlocal1(success);
    for (int i = 0; i < sizeof(bitmap_savers) / sizeof(*bitmap_savers); ++i) {
        if (strcmp(extension, bitmap_savers[i].extension) == 0) {
            success = caml_callback2(
                bitmap_savers[i].saver, caml_copy_string(filename), Val_ptr(bmp));
            CAMLreturnT(bool, Bool_val(success));
        }
    }
    CAMLreturnT(bool, false);
}

CAMLprim value ml_al_register_bitmap_loader(value extension, value loader)
{
    CAMLparam2(extension, loader);
    char const *c_extension = String_val(extension);
    if (strlen(c_extension) > 15) {
        caml_failwith("al_register_bitmap_loader: extension too long");
    }
    for (int i = 0; i < sizeof(bitmap_loaders) / sizeof(*bitmap_loaders); ++i) {
        if (strcmp(c_extension, bitmap_loaders[i].extension) == 0) {
            if (Is_none(loader)) {
                al_register_bitmap_loader(c_extension, NULL);
                bitmap_loaders[i].extension[0] = '\0';
                caml_remove_generational_global_root(&bitmap_loaders[i].loader);
            } else {
                bitmap_loaders[i].loader = Some_val(loader);
            }
            CAMLreturn(Val_unit);
        }
    }
    if (Is_none(loader)) {
        caml_failwith("al_register_bitmap_loader");
    }
    for (int i = 0; i < sizeof(bitmap_loaders) / sizeof(*bitmap_loaders); ++i) {
        if (bitmap_loaders[i].extension[0] == '\0') {
            strcpy(bitmap_loaders[i].extension, c_extension);
            bitmap_loaders[i].loader = Some_val(loader);
            caml_register_generational_global_root(&bitmap_loaders[i].loader);
            al_register_bitmap_loader(c_extension, bitmap_loader);
            CAMLreturn(Val_unit);
        }
    }
    caml_failwith("al_register_bitmap_loader: limit of 64 loaders reached");
}

CAMLprim value ml_al_register_bitmap_saver(value extension, value saver)
{
    CAMLparam2(extension, saver);
    char const *c_extension = String_val(extension);
    if (strlen(c_extension) > 15) {
        caml_failwith("al_register_bitmap_saver: extension too long");
    }
    for (int i = 0; i < sizeof(bitmap_savers) / sizeof(*bitmap_savers); ++i) {
        if (strcmp(c_extension, bitmap_savers[i].extension) == 0) {
            if (Is_none(saver)) {
                al_register_bitmap_saver(c_extension, NULL);
                bitmap_savers[i].extension[0] = '\0';
                caml_remove_generational_global_root(&bitmap_savers[i].saver);
            } else {
                bitmap_savers[i].saver = Some_val(saver);
            }
            CAMLreturn(Val_unit);
        }
    }
    if (Is_none(saver)) {
        caml_failwith("al_register_bitmap_saver");
    }
    for (int i = 0; i < sizeof(bitmap_savers) / sizeof(*bitmap_savers); ++i) {
        if (bitmap_savers[i].extension[0] == '\0') {
            strcpy(bitmap_savers[i].extension, c_extension);
            bitmap_savers[i].saver = Some_val(saver);
            caml_register_generational_global_root(&bitmap_savers[i].saver);
            al_register_bitmap_saver(c_extension, bitmap_saver);
            CAMLreturn(Val_unit);
        }
    }
    caml_failwith("al_register_bitmap_saver: limit of 64 savers reached");
}


static void failwith_filename(char const *func, char const *filename)
{
    char msg[strlen(func) + 1 + strlen(filename) + 1];
    sprintf(msg, "%s %s", func, filename);
    caml_failwith(msg);
}

CAMLprim value ml_al_load_bitmap_flags(value filename, value flags)
{
    CAMLparam2(filename, flags);
    int c_flags = convert_load_bitmap_flags_from_ml(flags);
    ALLEGRO_BITMAP *c_bmp = al_load_bitmap_flags(String_val(filename), c_flags);
    if (c_bmp == NULL) {
        failwith_filename("al_load_bitmap_flags", String_val(filename));
    }
    CAMLreturn(Val_ptr(c_bmp));
}

CAMLprim value ml_al_load_bitmap(value filename)
{
    CAMLparam1(filename);
    ALLEGRO_BITMAP *c_bmp = al_load_bitmap(String_val(filename));
    if (c_bmp == NULL) {
        failwith_filename("al_load_bitmap", String_val(filename));
    }
    CAMLreturn(Val_ptr(c_bmp));
}

CAMLprim value ml_al_save_bitmap(value filename, value bitmap)
{
    CAMLparam2(filename, bitmap);
    bool success = al_save_bitmap(String_val(filename), Ptr_val(bitmap));
    if (!success) {
        failwith_filename("al_save_bitmap", String_val(filename));
    }
    CAMLreturn(Val_unit);
}

ml_function_1arg_ret(al_identify_bitmap, String_val, caml_copy_string)
