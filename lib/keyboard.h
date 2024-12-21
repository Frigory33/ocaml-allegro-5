#ifndef OCAML_ALLEGRO_KEYBOARD_H
#define OCAML_ALLEGRO_KEYBOARD_H


#include "al5.h"


value convert_keycode_from_c(int c_keycode);
value convert_keymod_from_c(int c_keymod);


#endif
