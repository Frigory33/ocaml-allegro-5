#include <allegro5/allegro.h>

#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>


#define Ptr_val(v) ((void *)Nativeint_val(v))
#define Val_ptr(p) (caml_copy_nativeint((intnat)p))

#define ml_function_noarg(func) \
    CAMLprim value ml_ ## func(value unit) \
    { \
        CAMLparam1(unit); \
        func(); \
        CAMLreturn(Val_unit); \
    }

#define ml_function_1arg(func, cast) \
  CAMLprim value ml_ ## func(value v) \
  { \
      CAMLparam1(v); \
      func(cast(v)); \
      CAMLreturn(Val_unit); \
  }


void finalize_with_free(value v);
