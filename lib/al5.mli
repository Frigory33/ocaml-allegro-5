(** {1 Types} *)

(** {2 Abstract types} *)

type color
type event_queue
type event_source
type display
type joystick
type timer

(** {2 Enumerations} *)

type keycode =
| KEY_A
| KEY_B
| KEY_C
| KEY_D
| KEY_E
| KEY_F
| KEY_G
| KEY_H
| KEY_I
| KEY_J
| KEY_K
| KEY_L
| KEY_M
| KEY_N
| KEY_O
| KEY_P
| KEY_Q
| KEY_R
| KEY_S
| KEY_T
| KEY_U
| KEY_V
| KEY_W
| KEY_X
| KEY_Y
| KEY_Z
| KEY_0
| KEY_1
| KEY_2
| KEY_3
| KEY_4
| KEY_5
| KEY_6
| KEY_7
| KEY_8
| KEY_9
| KEY_PAD_0
| KEY_PAD_1
| KEY_PAD_2
| KEY_PAD_3
| KEY_PAD_4
| KEY_PAD_5
| KEY_PAD_6
| KEY_PAD_7
| KEY_PAD_8
| KEY_PAD_9
| KEY_F1
| KEY_F2
| KEY_F3
| KEY_F4
| KEY_F5
| KEY_F6
| KEY_F7
| KEY_F8
| KEY_F9
| KEY_F10
| KEY_F11
| KEY_F12
| KEY_ESCAPE
| KEY_TILDE
| KEY_MINUS
| KEY_EQUALS
| KEY_BACKSPACE
| KEY_TAB
| KEY_OPENBRACE
| KEY_CLOSEBRACE
| KEY_ENTER
| KEY_SEMICOLON
| KEY_QUOTE
| KEY_BACKSLASH
| KEY_BACKSLASH2
| KEY_COMMA
| KEY_FULLSTOP
| KEY_SLASH
| KEY_SPACE
| KEY_INSERT
| KEY_DELETE
| KEY_HOME
| KEY_END
| KEY_PGUP
| KEY_PGDN
| KEY_LEFT
| KEY_RIGHT
| KEY_UP
| KEY_DOWN
| KEY_PAD_SLASH
| KEY_PAD_ASTERISK
| KEY_PAD_MINUS
| KEY_PAD_PLUS
| KEY_PAD_DELETE
| KEY_PAD_ENTER
| KEY_PRINTSCREEN
| KEY_PAUSE
| KEY_ABNT_C1
| KEY_YEN
| KEY_KANA
| KEY_CONVERT
| KEY_NOCONVERT
| KEY_AT
| KEY_CIRCUMFLEX
| KEY_COLON2
| KEY_KANJI
| KEY_LSHIFT
| KEY_RSHIFT
| KEY_LCTRL
| KEY_RCTRL
| KEY_ALT
| KEY_ALTGR
| KEY_LWIN
| KEY_RWIN
| KEY_MENU
| KEY_SCROLLLOCK
| KEY_NUMLOCK
| KEY_CAPSLOCK
| KEY_PAD_EQUALS
| KEY_BACKQUOTE
| KEY_SEMICOLON2
| KEY_COMMAND
| KEY_BACK
| KEY_VOLUME_UP
| KEY_VOLUME_DOWN
| KEY_SEARCH
| KEY_DPAD_CENTER
| KEY_BUTTON_X
| KEY_BUTTON_Y
| KEY_DPAD_UP
| KEY_DPAD_DOWN
| KEY_DPAD_LEFT
| KEY_DPAD_RIGHT
| KEY_SELECT
| KEY_START
| KEY_L1
| KEY_R1

type orientation =
| DISPLAY_ORIENTATION_UNKNOWN
| DISPLAY_ORIENTATION_0_DEGREES
| DISPLAY_ORIENTATION_90_DEGREES
| DISPLAY_ORIENTATION_180_DEGREES
| DISPLAY_ORIENTATION_270_DEGREES
| DISPLAY_ORIENTATION_FACE_UP
| DISPLAY_ORIENTATION_FACE_DOWN

(** {2 Events} *)

type touch_event = {
  display: display;
  id: int;
  x: float;
  y: float;
  dx: float;
  dy: float;
}

type mouse_button_event = {
  x: int;
  y: int;
  z: int;
  w: int;
  button: int;
  pressure: float;
  display: display;
}

type mouse_move_event = {
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

type event =
| EVENT_JOYSTICK_AXIS of joystick * int * int * float
| EVENT_JOYSTICK_BUTTON_DOWN of joystick * int
| EVENT_JOYSTICK_BUTTON_UP of joystick * int
| EVENT_JOYSTICK_CONFIGURATION
| EVENT_KEY_DOWN of keycode * display
| EVENT_KEY_UP of keycode * display
| EVENT_KEY_CHAR of keycode * int * int * bool * display
| EVENT_MOUSE_AXES of mouse_move_event
| EVENT_MOUSE_BUTTON_DOWN of mouse_button_event
| EVENT_MOUSE_BUTTON_UP of mouse_button_event
| EVENT_MOUSE_WARPED of mouse_move_event
| EVENT_MOUSE_ENTER_DISPLAY of int * int * int * int * display
| EVENT_MOUSE_LEAVE_DISPLAY of int * int * int * int * display
| EVENT_TOUCH_BEGIN of touch_event
| EVENT_TOUCH_END of touch_event
| EVENT_TOUCH_MOVE of touch_event
| EVENT_TOUCH_CANCEL of touch_event
| EVENT_TIMER of timer * int64
| EVENT_DISPLAY_EXPOSE of display * int * int * int * int
| EVENT_DISPLAY_RESIZE of display * int * int * int * int
| EVENT_DISPLAY_CLOSE of display
| EVENT_DISPLAY_LOST of display
| EVENT_DISPLAY_FOUND of display
| EVENT_DISPLAY_SWITCH_OUT of display
| EVENT_DISPLAY_SWITCH_IN of display
| EVENT_DISPLAY_ORIENTATION of display * orientation
| EVENT_DISPLAY_HALT_DRAWING
| EVENT_DISPLAY_RESUME_DRAWING
| EVENT_DISPLAY_CONNECTED of display
| EVENT_DISPLAY_DISCONNECTED of display
| EVENT_DROP of int * int * (string * bool * int * bool) option
| EVENT_UNKNOWN of int


(** {1 Displays} *)

val create_display : int -> int -> display
val destroy_display : display -> unit

val flip_display : unit -> unit

val set_new_window_title : string -> unit

val get_display_event_source : display -> event_source


(** {1 Events} *)

val create_event_queue : unit -> event_queue
val destroy_event_queue : event_queue -> unit
val register_event_source : event_queue -> event_source -> unit

val wait_for_event : event_queue -> event


(** {1 Graphics routines} *)

val map_rgb : int -> int -> int -> color
val clear_to_color : color -> unit


(** {1 Keyboard routines} *)

val install_keyboard : unit -> unit

val get_keyboard_event_source : unit -> event_source


(** {1 System routines} *)

val init : unit -> unit
val uninstall_system : unit -> unit


(** {1 Time} *)

val rest : float -> unit
