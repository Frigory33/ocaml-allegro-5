#ifndef OCAML_ALLEGRO_AL5_H
#define OCAML_ALLEGRO_AL5_H


#include <allegro5/allegro.h>

#include <caml/alloc.h>
#include <caml/callback.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <caml/version.h>


#if OCAML_VERSION < 41200
#define Some_val(v) Field(v, 0)
#define Val_none Val_int(0)
#define Is_none(v) (v == Val_none)

value caml_alloc_some(value v);
#endif

value alloc_option_ptr(void *ptr, const char *func);
value alloc_nonnull_ptr(void *ptr, const char *func);

#define Ptr_val(v) ((void *)Nativeint_val(v))
#define Val_ptr(p) (caml_copy_nativeint((intnat)p))
#define Val_option_ptr(v) (alloc_option_ptr(v, __func__))
#define Val_nonnull_ptr(v) (alloc_nonnull_ptr(v, __func__))


#define ml_function_noarg(func) \
    CAMLprim value ml_ ## func(value unit) \
    { \
        CAMLparam1(unit); \
        func(); \
        CAMLreturn(Val_unit); \
    }

#define ml_function_noarg_ret(func, cast) \
    CAMLprim value ml_ ## func(value unit) \
    { \
        CAMLparam1(unit); \
        CAMLreturn(cast(func())); \
    }

#define ml_function_1arg(func, cast) \
    CAMLprim value ml_ ## func(value v) \
    { \
        CAMLparam1(v); \
        func(cast(v)); \
        CAMLreturn(Val_unit); \
    }

#define ml_function_1arg_ret(func, castarg, castret) \
    CAMLprim value ml_ ## func(value v) \
    { \
        CAMLparam1(v); \
        CAMLreturn(castret(func(castarg(v)))); \
    }

#define ml_function_2arg(func, cast1, cast2) \
    CAMLprim value ml_ ## func(value v1, value v2) \
    { \
        CAMLparam2(v1, v2); \
        func(cast1(v1), cast2(v2)); \
        CAMLreturn(Val_unit); \
    }

#define ml_function_2arg_ret(func, castarg1, castarg2, castret) \
    CAMLprim value ml_ ## func(value v1, value v2) \
    { \
        CAMLparam2(v1, v2); \
        CAMLreturn(castret(func(castarg1(v1), castarg2(v2)))); \
    }

#define ml_function_3arg(func, cast1, cast2, cast3) \
    CAMLprim value ml_ ## func(value v1, value v2, value v3) \
    { \
        CAMLparam3(v1, v2, v3); \
        func(cast1(v1), cast2(v2), cast3(v3)); \
        CAMLreturn(Val_unit); \
    }

#define ml_function_3arg_ret(func, castarg1, castarg2, castarg3, castret) \
    CAMLprim value ml_ ## func(value v1, value v2, value v3) \
    { \
        CAMLparam3(v1, v2, v3); \
        CAMLreturn(castret(func(castarg1(v1), castarg2(v2), castarg3(v3)))); \
    }

#define ml_function_noarg_blocking(func) \
    CAMLprim value ml_ ## func(value unit) \
    { \
        CAMLparam1(unit); \
        caml_enter_blocking_section(); \
        func(); \
        caml_leave_blocking_section(); \
        CAMLreturn(Val_unit); \
    }

#define ml_function_noarg_ret_blocking(func, typeret, cast) \
    CAMLprim value ml_ ## func(value unit) \
    { \
        CAMLparam1(unit); \
        typeret result; \
        caml_enter_blocking_section(); \
        result = func(); \
        caml_leave_blocking_section(); \
        CAMLreturn(cast(result)); \
    }

#define ml_function_1arg_blocking(func, type, cast) \
    CAMLprim value ml_ ## func(value v) \
    { \
        CAMLparam1(v); \
        type arg = cast(v); \
        caml_enter_blocking_section(); \
        func(arg); \
        caml_leave_blocking_section(); \
        CAMLreturn(Val_unit); \
    }

#define ml_function_1arg_ret_blocking(func, typearg, castarg, typeret, castret) \
    CAMLprim value ml_ ## func(value v) \
    { \
        CAMLparam1(v); \
        typearg arg = castarg(v); \
        caml_enter_blocking_section(); \
        typeret result = func(arg); \
        caml_leave_blocking_section(); \
        CAMLreturn(castret(result)); \
    }

#define ml_function_2arg_blocking(func, typearg1, castarg1, typearg2, castarg2) \
    CAMLprim value ml_ ## func(value v1, value v2) \
    { \
        CAMLparam2(v1, v2); \
        typearg1 arg1 = castarg1(v1); \
        typearg2 arg2 = castarg2(v2); \
        caml_enter_blocking_section();; \
        func(arg1, arg2); \
        caml_leave_blocking_section();; \
        CAMLreturn(Val_unit); \
    }

#define ml_function_2arg_ret_blocking(func, typearg1, castarg1, typearg2, castarg2, typeret, castret) \
    CAMLprim value ml_ ## func(value v1, value v2) \
    { \
        CAMLparam2(v1, v2); \
        typearg1 arg1 = castarg1(v1); \
        typearg2 arg2 = castarg2(v2); \
        caml_enter_blocking_section(); \
        typeret result = func(arg1, arg2); \
        caml_leave_blocking_section(); \
        CAMLreturn(castret(result)); \
    }

#define ml_function_3arg_blocking(func, typearg1, castarg1, typearg2, castarg2, typearg3, castarg3) \
    CAMLprim value ml_ ## func(value v1, value v2, value v3) \
    { \
        CAMLparam3(v1, v2, v3); \
        typearg1 arg1 = castarg1(v1); \
        typearg2 arg2 = castarg2(v2); \
        typearg3 arg3 = castarg3(v3); \
        caml_enter_blocking_section(); \
        func(arg1, arg2, arg3); \
        caml_leave_blocking_section(); \
        CAMLreturn(Val_unit); \
    }

#define ml_function_3arg_ret_blocking(func, typearg1, castarg1, typearg2, castarg2, typearg3, castarg3, typeret, castret) \
    CAMLprim value ml_ ## func(value v1, value v2, value v3) \
    { \
        CAMLparam3(v1, v2, v3); \
        typearg1 arg1 = castarg1(v1); \
        typearg2 arg2 = castarg2(v2); \
        typearg3 arg3 = castarg3(v3); \
        caml_enter_blocking_section(); \
        typeret result = func(arg1, arg2, arg3); \
        caml_leave_blocking_section(); \
        CAMLreturn(castret(result)); \
    }

int convert_flags_(int flags_from, int flags_num, int const flags_conv[][2], int from_index);
#define convert_flags(flags_from, flags_conv, from_index) \
    convert_flags_(flags_from, sizeof(flags_conv) / sizeof(*(flags_conv)), flags_conv, from_index)


#endif
