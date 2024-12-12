#include "al5.h"


CAMLprim value ml_al_install_mouse(value unit)
{
    CAMLparam1(unit);
    if (!al_install_mouse()) {
        caml_failwith("al_install_mouse");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_is_mouse_installed, Val_bool)

ml_function_noarg(al_uninstall_mouse)


ml_function_noarg_ret(al_get_mouse_event_source, Val_ptr)
