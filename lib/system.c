#include "al5.h"


CAMLprim value ml_al_init(value unit)
{
    CAMLparam1(unit);
    if (!al_init()) {
        caml_failwith("al_init");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg(al_uninstall_system)
