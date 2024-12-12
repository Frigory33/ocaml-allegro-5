(** {1 Types} *)

(** {2 Abstract types} *)

type color
type event_queue
type event_source
type display
type joystick
type timer

(** {2 Enumerations} *)

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

(** {2 Events} *)

module Event : sig
  type touch = {
    display: display;
    id: int;
    x: float;
    y: float;
    dx: float;
    dy: float;
  }

  type mouse_button = {
    x: int;
    y: int;
    z: int;
    w: int;
    button: int;
    pressure: float;
    display: display;
  }

  type mouse_move = {
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

  (** Note: currently, not all events are implemented. *)
  type t =
  | JOYSTICK_AXIS of joystick * int * int * float
  | JOYSTICK_BUTTON_DOWN of joystick * int
  | JOYSTICK_BUTTON_UP of joystick * int
  | JOYSTICK_CONFIGURATION
  | KEY_DOWN of Key.t * display
  | KEY_UP of Key.t * display
  | KEY_CHAR of Key.t * int * int * bool * display
  | MOUSE_AXES of mouse_move
  | MOUSE_BUTTON_DOWN of mouse_button
  | MOUSE_BUTTON_UP of mouse_button
  | MOUSE_WARPED of mouse_move
  | MOUSE_ENTER_DISPLAY of int * int * int * int * display
  | MOUSE_LEAVE_DISPLAY of int * int * int * int * display
  | TOUCH_BEGIN of touch
  | TOUCH_END of touch
  | TOUCH_MOVE of touch
  | TOUCH_CANCEL of touch
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

val create_display : int -> int -> display
val destroy_display : display -> unit

val flip_display : unit -> unit

val set_new_window_title : string -> unit

val get_display_event_source : display -> event_source


(** {1 Events} *)

(** {2 Event queue creation and registering} *)

val create_event_queue : unit -> event_queue
val destroy_event_queue : event_queue -> unit
val register_event_source : event_queue -> event_source -> unit
val unregister_event_source : event_queue -> event_source -> unit
val is_event_source_registered : event_queue -> event_source -> bool

(** {2 Event queue contents} *)

val pause_event_queue : event_queue -> bool -> unit
val is_event_queue_paused : event_queue -> bool
val is_event_queue_empty : event_queue -> bool
val get_next_event : event_queue -> Event.t option
val peek_next_event : event_queue -> Event.t option
val drop_next_event : event_queue -> bool
val flush_event_queue : event_queue -> unit
val wait_for_event : event_queue -> Event.t
val wait_for_event_timed : event_queue -> bool -> float -> Event.t option


(** {1 Graphics routines} *)

val map_rgb : int -> int -> int -> color
val clear_to_color : color -> unit


(** {1 Keyboard routines} *)

val install_keyboard : unit -> unit
val is_keyboard_installed : unit -> bool
val uninstall_keyboard : unit -> unit

val get_keyboard_event_source : unit -> event_source


(** {1 Mouse routines} *)

val install_mouse : unit -> unit
val is_mouse_installed : unit -> bool
val uninstall_mouse : unit -> unit

val get_mouse_event_source : unit -> event_source


(** {1 System routines} *)

val init : unit -> unit
val uninstall_system : unit -> unit


(** {1 Time} *)

val get_time : unit -> float

val rest : float -> unit
