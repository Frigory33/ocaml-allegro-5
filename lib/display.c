#include "al5.h"


CAMLprim value ml_al_create_display(value w, value h)
{
    CAMLparam2(w, h);
    ALLEGRO_DISPLAY *disp = al_create_display(Int_val(w), Int_val(h));
    if (disp == NULL) {
        caml_failwith("al_create_display");
    }
    CAMLreturn(caml_copy_nativeint((intnat)disp));
}

ml_function_1arg(al_destroy_display, (ALLEGRO_DISPLAY *)Nativeint_val)


ml_function_1arg(al_set_new_window_title, String_val)


ml_function_noarg(al_flip_display)
