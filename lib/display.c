#include "al5.h"


enum {
   ML_WINDOWED                    = 1 << 0,
   ML_FULLSCREEN                  = 1 << 1,
   ML_OPENGL                      = 1 << 2,
   ML_DIRECT3D_INTERNAL           = 1 << 3,
   ML_RESIZABLE                   = 1 << 4,
   ML_FRAMELESS                   = 1 << 5,
   ML_GENERATE_EXPOSE_EVENTS      = 1 << 6,
   ML_OPENGL_3_0                  = 1 << 7,
   ML_OPENGL_FORWARD_COMPATIBLE   = 1 << 8,
   ML_FULLSCREEN_WINDOW           = 1 << 9,
   ML_MINIMIZED                   = 1 << 10,
   ML_PROGRAMMABLE_PIPELINE       = 1 << 11,
   ML_GTK_TOPLEVEL_INTERNAL       = 1 << 12,
   ML_MAXIMIZED                   = 1 << 13,
   ML_OPENGL_ES_PROFILE           = 1 << 14,
#if defined(ML_UNSTABLE)
   ML_OPENGL_CORE_PROFILE         = 1 << 15,
   ML_DRAG_AND_DROP               = 1 << 16,
#endif
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
    int c_flags = convert_flags(Int_val(flags), display_flags_conv, 0);
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


ml_function_1arg_ret(al_get_display_width, Ptr_val, Val_int)

ml_function_1arg_ret(al_get_display_height, Ptr_val, Val_int)

CAMLprim value ml_al_resize_display(value disp, value width, value height)
{
    CAMLparam3(disp, width, height);
    bool success = al_resize_display(Ptr_val(disp), Int_val(width), Int_val(height));
    CAMLreturn(Val_bool(success));
}

CAMLprim value ml_al_acknowledge_resize(value disp)
{
    CAMLparam1(disp);
    if (!al_acknowledge_resize(Ptr_val(disp))) {
        caml_failwith("al_acknowledge_resize");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_get_window_position(value disp)
{
    CAMLparam1(disp);
    int c_x, c_y;
    al_get_window_position(Ptr_val(disp), &c_x, &c_y);
    CAMLlocal1(pos);
    pos = caml_alloc_tuple(2);
    Store_field(pos, 0, Val_int(c_x));
    Store_field(pos, 1, Val_int(c_y));
    CAMLreturn(pos);
}

CAMLprim value ml_al_set_window_position(value disp, value x, value y)
{
    CAMLparam3(disp, x, y);
    al_set_window_position(Ptr_val(disp), Int_val(x), Int_val(y));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_get_window_constraints(value disp)
{
    CAMLparam1(disp);
    int c_min_w, c_min_h, c_max_w, c_max_h;
    al_get_window_constraints(Ptr_val(disp), &c_min_w, &c_min_h, &c_max_w, &c_max_h);
    CAMLlocal1(constr);
    constr = caml_alloc_tuple(4);
    Store_field(constr, 0, Val_int(c_min_w));
    Store_field(constr, 1, Val_int(c_min_h));
    Store_field(constr, 2, Val_int(c_max_w));
    Store_field(constr, 3, Val_int(c_max_h));
    CAMLreturn(constr);
}

CAMLprim value ml_al_set_window_constraints(value disp, value min_w, value min_h, value max_w, value max_h)
{
    CAMLparam5(disp, min_w, min_h, max_w, max_h);
    al_set_window_constraints(Ptr_val(disp), Int_val(min_w), Int_val(min_h), Int_val(max_w), Int_val(max_h));
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_apply_window_constraints(value disp, value onoff)
{
    CAMLparam2(disp, onoff);
    al_apply_window_constraints(Ptr_val(disp), Bool_val(onoff));
    CAMLreturn(Val_unit);
}

#if ALLEGRO_VERSION_INT < 0x05020A00
int al_get_display_adapter(ALLEGRO_DISPLAY *disp)
{ return -1; }
#endif

ml_function_1arg_ret(al_get_display_adapter, Ptr_val, Val_int)


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


CAMLprim value ml_al_get_display_mode(value index)
{
    CAMLparam1(index);
    ALLEGRO_DISPLAY_MODE c_mode;
    if (al_get_display_mode(Int_val(index), &c_mode) == NULL) {
        caml_failwith("al_get_display_mode");
    }
    CAMLlocal1(mode);
    mode = caml_alloc_tuple(4);
    Store_field(mode, 0, Val_int(c_mode.width));
    Store_field(mode, 1, Val_int(c_mode.height));
    Store_field(mode, 2, Val_int(c_mode.format));
    Store_field(mode, 3, Val_int(c_mode.refresh_rate));
    CAMLreturn(mode);
}

ml_function_noarg_ret(al_get_num_display_modes, Val_int)
