#include <stdio.h>
#define ALLEGRO_NO_MAGIC_MAIN
#include <allegro5/allegro.h>

#define CAML_INTERNALS
#include "caml/misc.h"
#include "caml/mlvalues.h"
#include "caml/sys.h"
#include "caml/callback.h"

int mlmain(int argc, char_os **argv) {
    /* Before calling the OCaml runtime */
    caml_main(argv);
    caml_do_exit(0);
    return 0;
}

/* This is the new entry point */
int main(int argc, char_os **argv)
{
    return al_run_main(argc, argv, mlmain);
}
