(** {1 Allegro main}

    This package includes a [main] function coded in C that calls [al_run_main] of the Allegro library. It is necessary for Allegro
    to work on some systems. If you or a library you are using needs another C [main] function, then you should not use this library
    and write your own [main] function calling [al_run_main] instead (use our [main.c] file as an example).
*)
