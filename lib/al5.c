#include "al5.h"


#if OCAML_VERSION < 41200
value caml_alloc_some(value v)
{
    CAMLparam1(v);
    CAMLlocal1(some);
    some = caml_alloc(1, 0);
    Store_field(some, 0, v);
    CAMLreturn(some);
}
#endif

value alloc_nonnull_ptr(void *ptr, const char *fn)
{
    CAMLparam0();
    if (ptr == NULL) {
        caml_failwith(fn);
    } else {
        CAMLreturn(Val_ptr(ptr));
    }
}
value alloc_option_ptr(void *ptr, const char *fn)
{
    CAMLparam0();
    if (ptr == NULL) {
        CAMLreturn(Val_none);
    } else {
        CAMLreturn(caml_alloc_some(Val_ptr(ptr)));
    }
}

int convert_flags_(int flags_from, int flags_num, int const flags_conv[][2], int from_index)
{
    int flags_to = 0;
    for (int i = 0; i < flags_num; ++i) {
        if ((flags_from & flags_conv[i][from_index]) == flags_conv[i][from_index]) {
            flags_to |= flags_conv[i][1 - from_index];
        }
    }
    return flags_to;
}
