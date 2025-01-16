(** {1 Types and constants} *)

(** {2 Abstract types} *)

type bitmap
type color
type event_queue
type event_source
type display
type font
type joystick
type timeout
type timer

(** {2 Aggregation types} *)

type pos = float * float

module KeyboardState = struct
  type priv

  type t = {
    display : display;
    priv : priv;
  }
end

module MouseState = struct
  type priv

  type t = {
    x : int;
    y : int;
    z : int;
    w : int;
    buttons : int;
    pressure : float;
    priv : priv;
  }
end

(** {2 Enumerations} *)

module Display = struct
  let windowed = 1 lsl 0
  let fullscreen_window = 1 lsl 1
  let fullscreen = 1 lsl 2
  let resizable = 1 lsl 3
  let maximized = 1 lsl 4
  let opengl = 1 lsl 5
  let opengl_3_0 = 1 lsl 6
  let opengl_forward_compatible = 1 lsl 7
  let opengl_es_profile = 1 lsl 8
  let opengl_core_profile = 1 lsl 9
  let direct3d = 1 lsl 10
  let programmable_pipeline = 1 lsl 11
  let frameless = 1 lsl 12
  let generate_expose_events = 1 lsl 13
  let gtk_toplevel = 1 lsl 14
  let drag_and_drop = 1 lsl 15
end

module Bitmap = struct
  let no_premultiplied_alpha = 1 lsl 0
  let keep_index = 1 lsl 1
  let keep_bitmap_format = 1 lsl 2
end

module Key = struct
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

module Keymod = struct
  let shift = 1 lsl 0
  let ctrl = 1 lsl 1
  let alt = 1 lsl 2
  let lwin = 1 lsl 3
  let rwin = 1 lsl 4
  let menu = 1 lsl 5
  let altgr = 1 lsl 6
  let command = 1 lsl 7
  let scrolllock = 1 lsl 8
  let numlock = 1 lsl 9
  let capslock = 1 lsl 10
  let inaltseq = 1 lsl 11
  let accent1 = 1 lsl 12
  let accent2 = 1 lsl 13
  let accent3 = 1 lsl 14
  let accent4 = 1 lsl 15
end

module MouseButton = struct
  let left = 1
  let right = 2
  let middle = 3
end

module DisplayOrientation = struct
  type t =
  | UNKNOWN
  | DEGREES_0
  | DEGREES_90
  | DEGREES_180
  | DEGREES_270
  | FACE_UP
  | FACE_DOWN
end

module Flip = struct
  let horizontal = 1 lsl 0
  let vertical = 1 lsl 1
end

module LineJoin = struct
  type t =
  | NONE
  | BEVEL
  | ROUND
  | MITER of float
end

module LineCap = struct
  type t =
  | NONE
  | SQUARE
  | ROUND
  | TRIANGLE
  | CLOSED
end

module Text = struct
  let align_left = 1 lsl 0
  let align_centre = 1 lsl 1
  let align_right = 1 lsl 2
  let align_integer = 1 lsl 3
end

module Ttf = struct
  let no_kerning = 1 lsl 0
  let monochrome = 1 lsl 1
  let no_autohint = 1 lsl 2
end

(** {2 Events} *)

module Event = struct
  module Touch = struct
    type t = {
      display : display;
      id : int;
      x : float;
      y : float;
      dx : float;
      dy : float;
    }
  end

  module MouseButton = struct
    type t = {
      x : int;
      y : int;
      z : int;
      w : int;
      button : int;
      pressure : float;
      display : display;
    }
  end

  module MouseMove = struct
    type t = {
      x : int;
      y : int;
      z : int;
      w : int;
      dx : int;
      dy : int;
      dz : int;
      dw : int;
      pressure : float;
      display : display;
    }
  end

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

external get_keyboard_state : unit -> KeyboardState.t = "ml_al_get_keyboard_state"
external key_down : KeyboardState.t -> Key.t -> bool = "ml_al_key_down"
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
external get_mouse_state : unit -> MouseState.t = "ml_al_get_mouse_state"
external get_mouse_state_axis : MouseState.t -> int -> int = "ml_al_get_mouse_state_axis"
external mouse_button_down : MouseState.t -> int -> bool = "ml_al_mouse_button_down"
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
