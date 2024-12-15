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


ml_function_1arg(al_clear_to_color, AlColor_val)
