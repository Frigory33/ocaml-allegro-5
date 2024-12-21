#include "al5.h"


enum {
    ML_WINDOWED = 1 << 0,
    ML_FULLSCREEN_WINDOW = 1 << 1,
    ML_FULLSCREEN = 1 << 2,
    ML_RESIZABLE = 1 << 3,
    ML_MAXIMIZED = 1 << 4,
    ML_OPENGL = 1 << 5,
    ML_OPENGL_3_0 = 1 << 6,
    ML_OPENGL_FORWARD_COMPATIBLE = 1 << 7,
    ML_OPENGL_ES_PROFILE = 1 << 8,
    ML_OPENGL_CORE_PROFILE = 1 << 9,
    ML_DIRECT3D = 1 << 10,
    ML_PROGRAMMABLE_PIPELINE = 1 << 11,
    ML_FRAMELESS = 1 << 12,
    ML_GENERATE_EXPOSE_EVENTS = 1 << 13,
    ML_GTK_TOPLEVEL = 1 << 14,
    ML_DRAG_AND_DROP = 1 << 15,
};

static int const display_flags_conv[][2] = {
    { ML_WINDOWED, ALLEGRO_WINDOWED },
    { ML_FULLSCREEN_WINDOW, ALLEGRO_FULLSCREEN_WINDOW },
    { ML_FULLSCREEN, ALLEGRO_FULLSCREEN },
    { ML_RESIZABLE, ALLEGRO_RESIZABLE },
    { ML_MAXIMIZED, ALLEGRO_MAXIMIZED },
    { ML_OPENGL, ALLEGRO_OPENGL },
    { ML_OPENGL_3_0, ALLEGRO_OPENGL_3_0 },
    { ML_OPENGL_FORWARD_COMPATIBLE, ALLEGRO_OPENGL_FORWARD_COMPATIBLE },
    { ML_OPENGL_ES_PROFILE, ALLEGRO_OPENGL_ES_PROFILE },
    //{ ML_OPENGL_CORE_PROFILE, ALLEGRO_OPENGL_CORE_PROFILE },
    //{ ML_DIRECT3D, ALLEGRO_DIRECT3D },
    { ML_PROGRAMMABLE_PIPELINE, ALLEGRO_PROGRAMMABLE_PIPELINE },
    { ML_FRAMELESS, ALLEGRO_FRAMELESS },
    { ML_GENERATE_EXPOSE_EVENTS, ALLEGRO_GENERATE_EXPOSE_EVENTS },
    //{ ML_GTK_TOPLEVEL, ALLEGRO_GTK_TOPLEVEL },
    //{ ML_DRAG_AND_DROP, ALLEGRO_DRAG_AND_DROP },
};

static int convert_display_flags_from_ml(value flags)
{
    CAMLparam1(flags);
    int c_flags = convert_flags(Val_int(flags), display_flags_conv, 0);
    CAMLreturnT(int, c_flags);
}

static value convert_display_flags_from_c(int c_flags)
{
    int flags = convert_flags(c_flags, display_flags_conv, 1);
    return Val_int(flags);
}

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

ml_function_noarg_ret(al_get_new_display_flags, convert_display_flags_from_c)

ml_function_1arg(al_set_new_display_flags, convert_display_flags_from_ml)


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
