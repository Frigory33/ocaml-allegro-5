#include "al5.h"


enum {
    ML_VERTEX_SHADER,
    ML_PIXEL_SHADER,
};

enum {
    ML_SHADER_AUTO,
    ML_SHADER_GLSL,
    ML_SHADER_HLSL,
    ML_SHADER_AUTO_MINIMAL,
    ML_SHADER_GLSL_MINIMAL,
    ML_SHADER_HLSL_MINIMAL,
    ML_SHADER_HLSL_SM_3_0,
};

static int convert_shader_type_from_ml(value type)
{
    CAMLparam1(type);
    static int const type_conv[] = {
        [ML_VERTEX_SHADER] = ALLEGRO_VERTEX_SHADER,
        [ML_PIXEL_SHADER] = ALLEGRO_PIXEL_SHADER,
    };
    CAMLreturnT(int, type_conv[Int_val(type)]);
}

static value convert_shader_platform_from_c(int c_platform)
{
    int platform;
    switch (c_platform) {
        case ALLEGRO_SHADER_AUTO: platform = ML_SHADER_AUTO; break;
        case ALLEGRO_SHADER_GLSL: platform = ML_SHADER_GLSL; break;
        case ALLEGRO_SHADER_HLSL: platform = ML_SHADER_HLSL; break;
        case ALLEGRO_SHADER_AUTO_MINIMAL: platform = ML_SHADER_AUTO_MINIMAL; break;
        case ALLEGRO_SHADER_GLSL_MINIMAL: platform = ML_SHADER_GLSL_MINIMAL; break;
        case ALLEGRO_SHADER_HLSL_MINIMAL: platform = ML_SHADER_HLSL_MINIMAL; break;
        case ALLEGRO_SHADER_HLSL_SM_3_0: platform = ML_SHADER_HLSL_SM_3_0; break;
        default: platform = -1;
    }
    return Val_int(platform);
}

static int convert_shader_platform_from_ml(value platform)
{
    CAMLparam1(platform);
    static int const platform_conv[] = {
        [ML_SHADER_AUTO] = ALLEGRO_SHADER_AUTO,
        [ML_SHADER_GLSL] = ALLEGRO_SHADER_GLSL,
        [ML_SHADER_HLSL] = ALLEGRO_SHADER_HLSL,
        [ML_SHADER_AUTO_MINIMAL] = ALLEGRO_SHADER_AUTO_MINIMAL,
        [ML_SHADER_GLSL_MINIMAL] = ALLEGRO_SHADER_GLSL_MINIMAL,
        [ML_SHADER_HLSL_MINIMAL] = ALLEGRO_SHADER_HLSL_MINIMAL,
        [ML_SHADER_HLSL_SM_3_0] = ALLEGRO_SHADER_HLSL_SM_3_0,
    };
    CAMLreturnT(int, platform_conv[Int_val(platform)]);
}

ml_function_1arg_ret(al_create_shader, convert_shader_platform_from_ml, Val_ptr)

CAMLprim value ml_al_attach_shader_source(value shader, value type, value source)
{
    CAMLparam3(shader, type, source);
    bool success = al_attach_shader_source(Ptr_val(shader),
        convert_shader_type_from_ml(type), String_val(source));
    if (!success) {
        caml_failwith("al_attach_shader_source");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_attach_shader_source_file(value shader, value type, value filename)
{
    CAMLparam3(shader, type, filename);
    bool success = al_attach_shader_source_file(Ptr_val(shader),
        convert_shader_type_from_ml(type), String_val(filename));
    if (!success) {
        caml_failwith("al_attach_shader_source_file");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_build_shader(value shader)
{
    CAMLparam1(shader);
    if (!al_build_shader(Ptr_val(shader))) {
        caml_failwith("al_build_shader");
    }
    CAMLreturn(Val_unit);
}

ml_function_1arg_ret(al_get_shader_log, Ptr_val, caml_copy_string)

ml_function_1arg_ret(al_get_shader_platform, Ptr_val, convert_shader_platform_from_c)

CAMLprim value ml_al_use_shader(value shader)
{
    CAMLparam1(shader);
    bool success = al_use_shader(Is_none(shader) ? NULL : Ptr_val(Some_val(shader)));
    if (!success) {
        caml_failwith("al_use_shader");
    }
    CAMLreturn(Val_unit);
}

ml_function_noarg_ret(al_get_current_shader, Val_ptr)

ml_function_1arg(al_destroy_shader, Ptr_val)

CAMLprim value ml_al_get_default_shader_source(value platform, value type)
{
    CAMLparam2(platform, type);
    char const * source = al_get_default_shader_source(
        convert_shader_platform_from_ml(platform), convert_shader_type_from_ml(type));
    if (source == NULL) {
        caml_failwith("al_get_default_shader_source");
    }
    CAMLreturn(caml_copy_string(source));
}


CAMLprim value ml_al_set_shader_sampler(value name, value bitmap, value unit)
{
    CAMLparam3(name, bitmap, unit);
    bool success = al_set_shader_sampler(String_val(name), Ptr_val(bitmap), Int_val(unit));
    if (!success) {
        caml_failwith("al_set_shader_sampler");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_set_shader_matrix(value name, value matrix)
{
    CAMLparam2(name, matrix);
    bool success = al_set_shader_matrix(String_val(name), Data_custom_val(matrix));
    if (!success) {
        caml_failwith("al_set_shader_matrix");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_set_shader_int(value name, value i)
{
    CAMLparam2(name, i);
    bool success = al_set_shader_int(String_val(name), Int_val(i));
    if (!success) {
        caml_failwith("al_set_shader_int");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_set_shader_float(value name, value f)
{
    CAMLparam2(name, f);
    bool success = al_set_shader_float(String_val(name), Double_val(f));
    if (!success) {
        caml_failwith("al_set_shader_float");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_set_shader_bool(value name, value b)
{
    CAMLparam2(name, b);
    bool success = al_set_shader_bool(String_val(name), Bool_val(b));
    if (!success) {
        caml_failwith("al_set_shader_bool");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_set_shader_int_vector(value name, value i)
{
    CAMLparam2(name, i);
    int num_elems = Wosize_val(i),
        num_components = num_elems == 0 ? 1 : Wosize_val(Field(i, 0));
    if (num_components < 0 || 4 < num_components) {
        caml_invalid_argument("Al5.set_shader_int_vector: component size is invalid");
    }
    int c_i[num_elems][num_components];
    for (int elem = 0; elem < num_elems; ++elem) {
        if (Wosize_val(Field(i, elem)) != num_components) {
            caml_invalid_argument("Al5.set_shader_int_vector: components are not of equal size");
        }
        for (int comp = 0; comp < num_components; ++comp) {
            c_i[elem][comp] = Int_val(Field(Field(i, elem), comp));
        }
    }
    bool success = al_set_shader_int_vector(
        String_val(name), num_components, (int *)c_i, num_elems);
    if (!success) {
        caml_failwith("al_set_shader_int_vector");
    }
    CAMLreturn(Val_unit);
}

CAMLprim value ml_al_set_shader_float_vector(value name, value f)
{
    CAMLparam2(name, f);
    int num_elems = Wosize_val(f),
        num_components = num_elems == 0 ? 1 : Wosize_val(Field(f, 0));
    if (num_components < 0 || 4 < num_components) {
        caml_invalid_argument("Al5.set_shader_float_vector: component size is invalid");
    }
    float c_f[num_elems][num_components];
    for (int elem = 0; elem < num_elems; ++elem) {
        if (Wosize_val(Field(f, elem)) != num_components) {
            caml_invalid_argument("Al5.set_shader_float_vector: components are not of equal size");
        }
        for (int comp = 0; comp < num_components; ++comp) {
            c_f[elem][comp] = Double_array_field(Field(f, elem), comp);
        }
    }
    bool success = al_set_shader_float_vector(
        String_val(name), num_components, (float *)c_f, num_elems);
    if (!success) {
        caml_failwith("al_set_shader_float_vector");
    }
    CAMLreturn(Val_unit);
}
