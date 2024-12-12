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

ml_function_noarg_ret(al_is_system_installed, Val_bool)

ml_function_noarg_ret(al_get_allegro_version, Val_int)


ml_function_1arg(al_set_app_name, String_val)

ml_function_1arg(al_set_org_name, String_val)

ml_function_noarg_ret(al_get_app_name, caml_copy_string)

ml_function_noarg_ret(al_get_org_name, caml_copy_string)


ml_function_noarg_ret(al_get_cpu_count, Val_int)

ml_function_noarg_ret(al_get_ram_size, Val_int)
