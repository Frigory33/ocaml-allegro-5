external init : unit -> unit = "ml_al_init"
external uninstall_system : unit -> unit = "ml_al_uninstall_system"


type display

external create_display : int -> int -> display = "ml_al_create_display"
external destroy_display : display -> unit = "ml_al_destroy_display"

external flip_display : unit -> unit = "ml_al_flip_display"

external set_new_window_title : string -> unit = "ml_al_set_new_window_title"


type color

external map_rgb : int -> int -> int -> color = "ml_al_map_rgb"
external clear_to_color : color -> unit = "ml_al_clear_to_color"


external rest : float -> unit = "ml_al_rest"
