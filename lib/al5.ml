(** {1 Types} *)

(** {2 Abstract types} *)

type color
type event_queue
type event_source
type display
type joystick
type timer

(** {2 Enumerations} *)

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

(** {2 Events} *)

module Event = struct
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

external create_display : int -> int -> display = "ml_al_create_display"
external destroy_display : display -> unit = "ml_al_destroy_display"

external flip_display : unit -> unit = "ml_al_flip_display"

external set_new_window_title : string -> unit = "ml_al_set_new_window_title"

external get_display_event_source : display -> event_source = "ml_al_get_display_event_source"


(** {1 Events} *)

external create_event_queue : unit -> event_queue = "ml_al_create_event_queue"
external destroy_event_queue : event_queue -> unit = "ml_al_destroy_event_queue"
external register_event_source : event_queue -> event_source -> unit = "ml_al_register_event_source"

external wait_for_event : event_queue -> Event.t = "ml_al_wait_for_event"


(** {1 Graphics routines} *)

external map_rgb : int -> int -> int -> color = "ml_al_map_rgb"
external clear_to_color : color -> unit = "ml_al_clear_to_color"


(** {1 Keyboard routines} *)

external install_keyboard : unit -> unit = "ml_al_install_keyboard"

external get_keyboard_event_source : unit -> event_source = "ml_al_get_keyboard_event_source"


(** {1 System routines} *)

external init : unit -> unit = "ml_al_init"
external uninstall_system : unit -> unit = "ml_al_uninstall_system"


(** {1 Time} *)

external rest : float -> unit = "ml_al_rest"
