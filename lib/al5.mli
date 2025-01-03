(** {1 Types and constants} *)

(** {2 Abstract types} *)

type bitmap
type color
type event_queue
type event_source
type display
type font
type joystick
type keyboard_state
type mouse_state
type timeout
type timer

(** {2 Aggregation types} *)

type pos = float * float

(** {2 Enumerations} *)

module Display : sig
  val windowed : int
  val fullscreen_window : int
  val fullscreen : int
  val resizable : int
  val maximized : int
  val opengl : int
  val opengl_3_0 : int
  val opengl_forward_compatible : int
  val opengl_es_profile : int
  val opengl_core_profile : int
  val direct3d : int
  val programmable_pipeline : int
  val frameless : int
  val generate_expose_events : int
  val gtk_toplevel : int
  val drag_and_drop : int
end

module Bitmap : sig
  val no_premultiplied_alpha : int
  val keep_index : int
  val keep_bitmap_format : int
end

module Key : sig
  type t =
  | A
  | B
  | C
  | D
  | E
  | F
  | G
  | H
  | I
  | J
  | K
  | L
  | M
  | N
  | O
  | P
  | Q
  | R
  | S
  | T
  | U
  | V
  | W
  | X
  | Y
  | Z
  | N_0
  | N_1
  | N_2
  | N_3
  | N_4
  | N_5
  | N_6
  | N_7
  | N_8
  | N_9
  | PAD_0
  | PAD_1
  | PAD_2
  | PAD_3
  | PAD_4
  | PAD_5
  | PAD_6
  | PAD_7
  | PAD_8
  | PAD_9
  | F1
  | F2
  | F3
  | F4
  | F5
  | F6
  | F7
  | F8
  | F9
  | F10
  | F11
  | F12
  | ESCAPE
  | TILDE
  | MINUS
  | EQUALS
  | BACKSPACE
  | TAB
  | OPENBRACE
  | CLOSEBRACE
  | ENTER
  | SEMICOLON
  | QUOTE
  | BACKSLASH
  | BACKSLASH2
  | COMMA
  | FULLSTOP
  | SLASH
  | SPACE
  | INSERT
  | DELETE
  | HOME
  | END
  | PGUP
  | PGDN
  | LEFT
  | RIGHT
  | UP
  | DOWN
  | PAD_SLASH
  | PAD_ASTERISK
  | PAD_MINUS
  | PAD_PLUS
  | PAD_DELETE
  | PAD_ENTER
  | PRINTSCREEN
  | PAUSE
  | ABNT_C1
  | YEN
  | KANA
  | CONVERT
  | NOCONVERT
  | AT
  | CIRCUMFLEX
  | COLON2
  | KANJI
  | LSHIFT
  | RSHIFT
  | LCTRL
  | RCTRL
  | ALT
  | ALTGR
  | LWIN
  | RWIN
  | MENU
  | SCROLLLOCK
  | NUMLOCK
  | CAPSLOCK
  | PAD_EQUALS
  | BACKQUOTE
  | SEMICOLON2
  | COMMAND
  | BACK
  | VOLUME_UP
  | VOLUME_DOWN
  | SEARCH
  | DPAD_CENTER
  | BUTTON_X
  | BUTTON_Y
  | DPAD_UP
  | DPAD_DOWN
  | DPAD_LEFT
  | DPAD_RIGHT
  | SELECT
  | START
end

module Keymod : sig
  val shift : int
  val ctrl : int
  val alt : int
  val lwin : int
  val rwin : int
  val menu : int
  val altgr : int
  val command : int
  val scrolllock : int
  val numlock : int
  val capslock : int
  val inaltseq : int
  val accent1 : int
  val accent2 : int
  val accent3 : int
  val accent4 : int
end

module MouseButton : sig
  val left : int
  val right : int
  val middle : int
end

module DisplayOrientation : sig
  type t =
  | UNKNOWN
  | DEGREES_0
  | DEGREES_90
  | DEGREES_180
  | DEGREES_270
  | FACE_UP
  | FACE_DOWN
end

module Flip : sig
  val horizontal : int
  val vertical : int
end

module LineJoin : sig
  type t =
  | NONE
  | BEVEL
  | ROUND
  | MITER of float
end

module LineCap : sig
  type t =
  | NONE
  | SQUARE
  | ROUND
  | TRIANGLE
  | CLOSED
end

module Text : sig
  val align_left : int
  val align_centre : int
  val align_right : int
  val align_integer : int
end

module Ttf : sig
  val no_kerning : int
  val monochrome : int
  val no_autohint : int
end

(** {2 Events} *)

module Event : sig
  module Touch : sig
    type t = {
      display: display;
      id: int;
      x: float;
      y: float;
      dx: float;
      dy: float;
    }
  end

  module MouseButton : sig
    type t = {
      x: int;
      y: int;
      z: int;
      w: int;
      button: int;
      pressure: float;
      display: display;
    }
  end

  module MouseMove : sig
    type t = {
      x: int;
      y: int;
      z: int;
      w: int;
      dx: int;
      dy: int;
      dz: int;
      dw: int;
      pressure: float;
      display: display;
    }
  end

  (** Note: currently, not all events are implemented. *)
  type t =
  | JOYSTICK_AXIS of joystick * int * int * float
  | JOYSTICK_BUTTON_DOWN of joystick * int
  | JOYSTICK_BUTTON_UP of joystick * int
  | JOYSTICK_CONFIGURATION
  | KEY_DOWN of Key.t * display
  | KEY_UP of Key.t * display
  | KEY_CHAR of Key.t * int * int * bool * display
  | MOUSE_AXES of MouseMove.t
  | MOUSE_BUTTON_DOWN of MouseButton.t
  | MOUSE_BUTTON_UP of MouseButton.t
  | MOUSE_WARPED of MouseMove.t
  | MOUSE_ENTER_DISPLAY of int * int * int * int * display
  | MOUSE_LEAVE_DISPLAY of int * int * int * int * display
  | TOUCH_BEGIN of Touch.t
  | TOUCH_END of Touch.t
  | TOUCH_MOVE of Touch.t
  | TOUCH_CANCEL of Touch.t
  | TIMER of timer * int64
  | DISPLAY_EXPOSE of display * int * int * int * int
  | DISPLAY_RESIZE of display * int * int * int * int
  | DISPLAY_CLOSE of display
  | DISPLAY_LOST of display
  | DISPLAY_FOUND of display
  | DISPLAY_SWITCH_OUT of display
  | DISPLAY_SWITCH_IN of display
  | DISPLAY_ORIENTATION of display * DisplayOrientation.t
  | DISPLAY_HALT_DRAWING
  | DISPLAY_RESUME_DRAWING
  | DISPLAY_CONNECTED of display
  | DISPLAY_DISCONNECTED of display
  | DROP of int * int * (string * bool * int * bool) option
  | UNKNOWN of int
end


(** {1 Displays} *)

(** {2 Display creation} *)

external create_display : int -> int -> display = "ml_al_create_display"
external destroy_display : display -> unit = "ml_al_destroy_display"
external get_new_display_flags : unit -> int = "ml_al_get_new_display_flags"
external set_new_display_flags : int -> unit = "ml_al_set_new_display_flags"

(** {2 Display operations} *)

external get_display_event_source : display -> event_source = "ml_al_get_display_event_source"
external flip_display : unit -> unit = "ml_al_flip_display"
external get_backbuffer : display -> bitmap = "ml_al_get_backbuffer"

(** {2 Display size and position} *)

external get_display_width : display -> int = "ml_al_get_display_width"
external get_display_height : display -> int = "ml_al_get_display_height"

(** {2 Display settings} *)

external set_window_title : display -> string -> unit = "ml_al_set_window_title"
external set_new_window_title : string -> unit = "ml_al_set_new_window_title"
external get_new_window_title : unit -> string = "ml_al_get_new_window_title"
external set_display_icon : display -> bitmap -> unit = "ml_al_set_display_icon"
external set_display_icons : display -> bitmap array -> unit = "ml_al_set_display_icons"


(** {1 Events} *)

external create_event_queue : unit -> event_queue = "ml_al_create_event_queue"
external destroy_event_queue : event_queue -> unit = "ml_al_destroy_event_queue"
external register_event_source : event_queue -> event_source -> unit = "ml_al_register_event_source"
external unregister_event_source : event_queue -> event_source -> unit = "ml_al_unregister_event_source"
external is_event_source_registered : event_queue -> event_source -> bool = "ml_al_is_event_source_registered"

(** {2 Event queue contents} *)

external pause_event_queue : event_queue -> bool -> unit = "ml_al_pause_event_queue"
external is_event_queue_paused : event_queue -> bool = "ml_al_is_event_queue_paused"
external is_event_queue_empty : event_queue -> bool = "ml_al_is_event_queue_empty"
external get_next_event : event_queue -> Event.t option = "ml_al_get_next_event"
external peek_next_event : event_queue -> Event.t option = "ml_al_peek_next_event"
external drop_next_event : event_queue -> bool = "ml_al_drop_next_event"
external flush_event_queue : event_queue -> unit = "ml_al_flush_event_queue"
external wait_for_event : event_queue -> Event.t = "ml_al_wait_for_event"
external wait_for_event_timed : event_queue -> bool -> float -> Event.t option = "ml_al_wait_for_event_timed"
external wait_for_event_until : event_queue -> bool -> timeout -> Event.t option = "ml_al_wait_for_event_until"


(** {1 Graphics routines} *)

(** {2 Colors} *)

external map_rgb : int -> int -> int -> color = "ml_al_map_rgb"
external map_rgba : int -> int -> int -> int -> color = "ml_al_map_rgba"
external premul_rgba : int -> int -> int -> int -> color = "ml_al_premul_rgba"
external map_rgb_f : float -> float -> float -> color = "ml_al_map_rgb_f"
external map_rgba_f : float -> float -> float -> float -> color = "ml_al_map_rgba_f"
external premul_rgba_f : float -> float -> float -> float -> color = "ml_al_premul_rgba_f"
external unmap_rgb : color -> int * int * int = "ml_al_unmap_rgb"
external unmap_rgba : color -> int * int * int * int = "ml_al_unmap_rgba"
external unmap_rgb_f : color -> float * float * float = "ml_al_unmap_rgb_f"
external unmap_rgba_f : color -> float * float * float * float = "ml_al_unmap_rgba_f"

(** {2 Bitmap creation} *)

external create_bitmap : int -> int -> bitmap = "ml_al_create_bitmap"
external create_sub_bitmap : bitmap -> int -> int -> int -> int -> bitmap = "ml_al_create_sub_bitmap"
external clone_bitmap : bitmap -> bitmap = "ml_al_clone_bitmap"
external convert_bitmap : bitmap -> unit = "ml_al_convert_bitmap"
external convert_memory_bitmaps : unit -> unit = "ml_al_convert_memory_bitmaps"
external destroy_bitmap : bitmap -> unit = "ml_al_destroy_bitmap"

(** {2 Bitmap properties} *)

external get_bitmap_width : bitmap -> int = "ml_al_get_bitmap_width"
external get_bitmap_height : bitmap -> int = "ml_al_get_bitmap_height"

(** {2 Drawing operations} *)

external clear_to_color : color -> unit = "ml_al_clear_to_color"
external draw_bitmap : bitmap -> ?tint: color -> pos -> int -> unit = "ml_al_draw_bitmap"
external draw_bitmap_region : bitmap -> ?tint: color -> pos -> pos -> pos -> int -> unit =
  "ml_al_draw_bitmap_region_bytecode" "ml_al_draw_bitmap_region"
external draw_rotated_bitmap : bitmap -> ?tint: color -> pos -> pos -> float -> int -> unit =
  "ml_al_draw_rotated_bitmap_bytecode" "ml_al_draw_rotated_bitmap"
external draw_scaled_bitmap : bitmap -> ?tint: color -> pos -> pos -> pos -> pos -> int -> unit =
  "ml_al_draw_scaled_bitmap_bytecode" "ml_al_draw_scaled_bitmap"
external draw_scaled_rotated_bitmap : bitmap -> ?tint: color -> pos -> pos -> pos -> float -> int -> unit =
  "ml_al_draw_scaled_rotated_bitmap_bytecode" "ml_al_draw_scaled_rotated_bitmap"
external draw_scaled_rotated_bitmap_region : bitmap -> pos -> pos -> ?tint: color -> pos -> pos -> pos -> float -> int -> unit =
  "ml_al_draw_scaled_rotated_bitmap_region_bytecode" "ml_al_draw_scaled_rotated_bitmap_region"

(** {2 Target bitmap} *)

external get_target_bitmap : unit -> bitmap = "al_get_target_bitmap"
external set_target_bitmap : bitmap -> unit = "al_set_target_bitmap"
external set_target_backbuffer : display -> unit = "al_set_target_backbuffer"
external get_current_display : unit -> display = "al_get_current_display"

(** {2 Image I/O} *)

external load_bitmap : string -> bitmap = "ml_al_load_bitmap"


(** {1 Keyboard routines} *)

external install_keyboard : unit -> unit = "ml_al_install_keyboard"
external is_keyboard_installed : unit -> bool = "ml_al_is_keyboard_installed"
external uninstall_keyboard : unit -> unit = "ml_al_uninstall_keyboard"
external get_keyboard_event_source : unit -> event_source = "ml_al_get_keyboard_event_source"

(** {2 Keyboard information} *)

external get_keyboard_state : unit -> keyboard_state = "ml_al_get_keyboard_state"
external key_down : keyboard_state -> Key.t = "ml_al_key_down"
external get_keyboard_state_display : keyboard_state -> display = "ml_al_get_keyboard_state_display"
external keycode_to_name : Key.t -> string = "ml_al_keycode_to_name"
external can_set_keyboard_leds : unit -> bool = "ml_al_can_set_keyboard_leds"
external set_keyboard_leds : int -> unit = "ml_al_set_keyboard_leds"


(** {1 Mouse routines} *)

external install_mouse : unit -> unit = "ml_al_install_mouse"
external is_mouse_installed : unit -> bool = "ml_al_is_mouse_installed"
external uninstall_mouse : unit -> unit = "ml_al_uninstall_mouse"
external get_mouse_event_source : unit -> event_source = "ml_al_get_mouse_event_source"

(** {2 Mouse information} *)

external get_mouse_num_axis : unit -> int = "ml_al_get_mouse_num_axes"
external get_mouse_num_buttons : unit -> int = "ml_al_get_mouse_num_buttons"
external get_mouse_state : unit -> mouse_state = "ml_al_get_mouse_state"
external get_mouse_state_axis : mouse_state -> int -> int = "ml_al_get_mouse_state_axis"
external mouse_button_down : mouse_state -> int -> bool = "ml_al_mouse_button_down"
external get_mouse_state_pressure : mouse_state -> float = "ml_al_get_mouse_state_pressure"
external set_mouse_xy : display -> int -> int -> bool = "ml_al_set_mouse_xy"
external set_mouse_z : int -> bool = "ml_al_set_mouse_z"
external set_mouse_w : int -> bool = "ml_al_set_mouse_w"
external set_mouse_axis : int -> int -> bool = "ml_al_set_mouse_axis"
external set_mouse_wheel_precision : int -> unit = "ml_al_set_mouse_wheel_precision"
external get_mouse_wheel_precision : unit -> int = "ml_al_get_mouse_wheel_precision"


(** {1 System routines} *)

external init : unit -> unit = "ml_al_init"
external uninstall_system : unit -> unit = "ml_al_uninstall_system"
external is_system_installed : unit -> bool = "ml_al_is_system_installed"
external get_allegro_version : unit -> int = "ml_al_get_allegro_version"

external set_app_name : string -> unit = "ml_al_set_app_name"
external set_org_name : string -> unit = "ml_al_set_org_name"
external get_app_name : unit -> string = "ml_al_get_app_name"
external get_org_name : unit -> string = "ml_al_get_org_name"

external get_cpu_count : unit -> int = "ml_al_get_cpu_count"
external get_ram_size : unit -> int = "ml_al_get_ram_size"


(** {1 Time} *)

external get_time : unit -> float = "ml_al_get_time"
external init_timeout : float -> timeout = "ml_al_init_timeout"
external rest : float -> unit = "ml_al_rest"


(** {1 Timer} *)

external create_timer : float -> timer = "ml_al_create_timer"
external start_timer : timer -> unit = "ml_al_start_timer"
external resume_timer : timer -> unit = "ml_al_resume_timer"
external stop_timer : timer -> unit = "ml_al_stop_timer"
external get_timer_started : timer -> bool = "ml_al_get_timer_started"
external destroy_timer : timer -> unit = "ml_al_destroy_timer"
external get_timer_count : timer -> int64 = "ml_al_get_timer_count"
external set_timer_count : timer -> int64 -> unit = "ml_al_set_timer_count"
external add_timer_count : timer -> int64 -> unit = "ml_al_add_timer_count"
external get_timer_speed : timer -> float = "ml_al_get_timer_speed"
external set_timer_speed : timer -> float -> unit = "ml_al_set_timer_speed"
external get_timer_event_source : timer -> event_source = "ml_al_get_timer_event_source"


(** {1 Image I/O addon} *)

external init_image_addon : unit -> unit = "ml_al_init_image_addon"
external is_image_addon_initialized : unit -> bool = "ml_al_is_image_addon_initialized"
external shutdown_image_addon : unit -> unit = "ml_al_shutdown_image_addon"
external get_allegro_image_version : unit -> int = "ml_al_get_allegro_image_version"


(** {1 Font addons} *)

external init_font_addon : unit -> unit = "ml_al_init_font_addon"
external is_font_addon_initialized : unit -> bool = "ml_al_is_font_addon_initialized"
external shutdown_font_addon : unit -> unit = "ml_al_shutdown_font_addon"
external get_allegro_font_version : unit -> int = "ml_al_get_allegro_font_version"

(** {2 General font routines} *)

external destroy_font : font -> unit = "ml_al_destroy_font"
external get_font_line_height : font -> int = "ml_al_get_font_line_height"
external get_font_ascent : font -> int = "ml_al_get_font_ascent"
external get_font_descent : font -> int = "ml_al_get_font_descent"
external get_text_width : font -> string -> int = "ml_al_get_text_width"
external draw_text : font -> color -> pos -> int -> string -> unit = "ml_al_draw_text"
external draw_justified_text : font -> color -> pos -> float -> float -> int -> string -> unit =
  "ml_al_draw_justified_text_bytecode" "ml_al_draw_justified_text"
external get_text_dimensions : font -> string -> int * int * int * int = "ml_al_get_text_dimensions"
external set_fallback_font : font -> font option -> unit = "ml_al_set_fallback_font"
external get_fallback_font : font -> font = "ml_al_get_fallback_font"

(** {2 Bitmap fonts} *)

external grab_font_from_bitmap : bitmap -> (int * int) array -> font = "ml_al_grab_font_from_bitmap"
external load_bitmap_font : string -> font = "ml_al_load_bitmap_font"
external load_bitmap_font_flags : string -> int -> font = "ml_al_load_bitmap_font_flags"
external create_builtin_font : unit -> font = "ml_al_create_builtin_font"

(** {2 TTF fonts} *)

external init_ttf_addon : unit -> unit = "ml_al_init_ttf_addon"
external is_ttf_addon_initialized : unit -> bool = "ml_al_is_ttf_addon_initialized"
external shutdown_ttf_addon : unit -> unit = "ml_al_shutdown_ttf_addon"
external get_allegro_ttf_version : unit -> int = "ml_al_get_allegro_ttf_version"
external load_ttf_font : string -> int -> int -> font = "ml_al_load_ttf_font"
external load_ttf_font_stretch : string -> int -> int -> int -> font = "ml_al_load_ttf_font_stretch"


(** {1 Primitives addon} *)

external init_primitives_addon : unit -> unit = "ml_al_init_primitives_addon"
external is_primitives_addon_initialized : unit -> bool = "ml_al_is_primitives_addon_initialized"
external shutdown_primitives_addon : unit -> unit = "ml_al_shutdown_primitives_addon"
external get_allegro_primitives_version : unit -> int = "ml_al_get_allegro_primitives_version"

(** {2 High level drawing routines} *)

external draw_line : pos -> pos -> color -> float -> unit = "ml_al_draw_line"
external draw_triangle : pos -> pos -> pos -> color -> float -> unit = "ml_al_draw_triangle"
external draw_filled_triangle : pos -> pos -> pos -> color -> unit = "ml_al_draw_filled_triangle"
external draw_rectangle : pos -> pos -> color -> float -> unit = "ml_al_draw_rectangle"
external draw_filled_rectangle : pos -> pos -> color -> unit = "ml_al_draw_filled_rectangle"
external draw_rounded_rectangle : pos -> pos -> pos -> color -> float -> unit = "ml_al_draw_rounded_rectangle"
external draw_filled_rounded_rectangle : pos -> pos -> pos -> color -> unit = "ml_al_draw_filled_rounded_rectangle"
external draw_pieslice : pos -> float -> float -> float -> color -> float -> unit = "ml_al_draw_pieslice_bytecode" "ml_al_draw_pieslice"
external draw_filled_pieslice : pos -> float -> float -> float -> color -> unit = "ml_al_draw_filled_pieslice"
external draw_ellipse : pos -> pos -> color -> float -> unit = "ml_al_draw_ellipse"
external draw_filled_ellipse : pos -> pos -> color -> unit = "ml_al_draw_filled_ellipse"
external draw_circle : pos -> float -> color -> float -> unit = "ml_al_draw_circle"
external draw_filled_circle : pos -> float -> color -> unit = "ml_al_draw_filled_circle"
external draw_arc : pos -> float -> float -> float -> color -> float -> unit = "ml_al_draw_arc_bytecode" "ml_al_draw_arc"
external draw_elliptical_arc : pos -> pos -> float -> float -> color -> float -> unit = "ml_al_draw_elliptical_arc_bytecode" "ml_al_draw_elliptical_arc"

(** {2 Polygon routines} *)

external draw_polyline : pos array -> LineJoin.t -> LineCap.t -> color -> float -> unit = "ml_al_draw_polyline"
external draw_polygon : pos array -> LineJoin.t -> color -> float -> unit = "ml_al_draw_polygon"
external draw_filled_polygon : pos array -> color -> unit = "ml_al_draw_filled_polygon"
external draw_filled_polygon_with_holes : pos array -> pos array list -> color -> unit = "ml_al_draw_filled_polygon_with_holes"
