#include "al5.h"


CAMLprim value ml_al_create_display(value w, value h)
{
    CAMLparam2(w, h);
    ALLEGRO_DISPLAY *c_disp = al_create_display(Int_val(w), Int_val(h));
    if (c_disp == NULL) {
        caml_failwith("al_create_display");
    }
    CAMLreturn(Val_ptr(c_disp));
}

ml_function_1arg(al_destroy_display, Ptr_val)


ml_function_1arg_ret(al_get_display_event_source, Ptr_val, Val_ptr)

ml_function_1arg_ret(al_get_backbuffer, Ptr_val, Val_ptr)

ml_function_noarg(al_flip_display)


ml_function_1arg_ret(al_get_display_width, Ptr_val, Int_val)

ml_function_1arg_ret(al_get_display_height, Ptr_val, Int_val)


CAMLprim value ml_al_set_window_title(value disp, value title)
{
    CAMLparam2(disp, title);
    al_set_window_title(Ptr_val(disp), String_val(title));
    CAMLreturn(Val_unit);
}

ml_function_1arg(al_set_new_window_title, String_val)

ml_function_noarg_ret(al_get_new_window_title, caml_copy_string)

CAMLprim value ml_al_set_display_icon(value disp, value icon)
{
    CAMLparam2(disp, icon);
    al_set_display_icon(Ptr_val(disp), Ptr_val(icon));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_set_display_icons(value disp, value icons)
{
    CAMLparam2(disp, icons);
    int num_icons = Wosize_val(icons);
    ALLEGRO_BITMAP *c_icons[num_icons];
    for (int i = 0; i < num_icons; ++i) {
        c_icons[i] = Ptr_val(Field(icons, i));
    }
    al_set_display_icons(Ptr_val(disp), num_icons, c_icons);
    CAMLreturn(Val_unit);
}
