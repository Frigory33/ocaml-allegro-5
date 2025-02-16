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


#define Ptr_val(v) ((void *)Nativeint_val(v))
#define Val_ptr(p) (caml_copy_nativeint((intnat)p))


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


int convert_flags_(int flags_from, int flags_num, int const flags_conv[][2], int from_index);
#define convert_flags(flags_from, flags_conv, from_index) \
    convert_flags_(flags_from, sizeof(flags_conv) / sizeof(*(flags_conv)), flags_conv, from_index)


#endif
