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


ml_function_1arg(al_clear_to_color, AlColor_val)
