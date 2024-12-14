#ifndef OCAML_ALLEGRO_GRAPHICS_H
#define OCAML_ALLEGRO_GRAPHICS_H


#include "al5.h"


#define AlColor_val(v) (*((ALLEGRO_COLOR *)Data_custom_val(v)))

#define PosX_val(v) (Double_val(Field((v), 0)))
#define PosY_val(v) (Double_val(Field((v), 1)))


#endif
