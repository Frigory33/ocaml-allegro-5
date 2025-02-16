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


enum {
  ML_RESOURCES_PATH,
  ML_TEMP_PATH,
  ML_USER_HOME_PATH,
  ML_USER_DOCUMENTS_PATH,
  ML_USER_DATA_PATH,
  ML_USER_SETTINGS_PATH,
  ML_EXENAME_PATH,
};

int convert_standard_path_id_from_ml(value id)
{
    CAMLparam1(id);
    static int const standard_path_ids[] = {
        [ML_RESOURCES_PATH] = ALLEGRO_RESOURCES_PATH,
        [ML_TEMP_PATH] = ALLEGRO_TEMP_PATH,
        [ML_USER_HOME_PATH] = ALLEGRO_USER_HOME_PATH,
        [ML_USER_DOCUMENTS_PATH] = ALLEGRO_USER_DOCUMENTS_PATH,
        [ML_USER_DATA_PATH] = ALLEGRO_USER_DATA_PATH,
        [ML_USER_SETTINGS_PATH] = ALLEGRO_USER_SETTINGS_PATH,
        [ML_EXENAME_PATH] = ALLEGRO_EXENAME_PATH,
    };
    CAMLreturnT(int, standard_path_ids[Int_val(id)]);
}

CAMLprim value ml_al_get_standard_path(value id)
{
    CAMLparam1(id);
    CAMLlocal1(path);
    ALLEGRO_PATH *c_path = al_get_standard_path(convert_standard_path_id_from_ml(id));
    path = caml_copy_string(al_path_cstr(c_path, ALLEGRO_NATIVE_PATH_SEP));
    al_destroy_path(c_path);
    CAMLreturn(path);
}


ml_function_1arg(al_set_exe_name, String_val)

ml_function_1arg(al_set_app_name, String_val)

ml_function_1arg(al_set_org_name, String_val)

ml_function_noarg_ret(al_get_app_name, caml_copy_string)

ml_function_noarg_ret(al_get_org_name, caml_copy_string)


ml_function_noarg_ret(al_get_cpu_count, Val_int)

ml_function_noarg_ret(al_get_ram_size, Val_int)
