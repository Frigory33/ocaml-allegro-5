#include "al5.h"


CAMLprim value ml_al_install_keyboard(value unit)
{
    CAMLparam1(unit);
    if (!al_install_keyboard()) {
        caml_failwith("al_install_keyboard");
    }
    CAMLreturn(Val_unit);
}


ml_function_noarg_ret(al_get_keyboard_event_source, Val_ptr)
