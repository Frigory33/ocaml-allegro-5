type color
type display
type event_queue
type event_source
type joystick
type timer

type keycode
type mouse_button
type orientation

type event =
| EVENT_JOYSTICK_AXIS of joystick * int * int * float
| EVENT_JOYSTICK_BUTTON_DOWN of joystick * int
| EVENT_JOYSTICK_BUTTON_UP of joystick * int
| EVENT_JOYSTICK_CONFIGURATION
| EVENT_KEY_DOWN of keycode * display
| EVENT_KEY_UP of keycode * display
| EVENT_KEY_CHAR of keycode * int * int * bool * display
| EVENT_MOUSE_AXES of int * int * int * int * int * int * int * int * float * display
| EVENT_MOUSE_BUTTON_DOWN of int * int * int * int * mouse_button * float * display
| EVENT_MOUSE_BUTTON_UP of int * int * int * int * mouse_button * float * display
| EVENT_MOUSE_WARPED of int * int * int * int * int * int * int * int * float * display
| EVENT_MOUSE_ENTER_DISPLAY of int * int * int * int * display
| EVENT_MOUSE_LEAVE_DISPLAY of int * int * int * int * display
| EVENT_TOUCH_BEGIN of display * int * float * float * float * float * bool
| EVENT_TOUCH_END of display * int * float * float * float * float * bool
| EVENT_TOUCH_MOVE of display * int * float * float * float * float * bool
| EVENT_TOUCH_CANCEL of display * int * float * float * float * float * bool
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


(* Displays *)
external create_display : int -> int -> display = "ml_al_create_display"
external destroy_display : display -> unit = "ml_al_destroy_display"

external flip_display : unit -> unit = "ml_al_flip_display"

external set_new_window_title : string -> unit = "ml_al_set_new_window_title"

external get_display_event_source : display -> event_source = "ml_al_get_display_event_source"


(* Events *)
external create_event_queue : unit -> event_queue = "ml_al_create_event_queue"
external destroy_event_queue : event_queue -> unit = "ml_al_destroy_event_queue"
external register_event_source : event_queue -> event_source -> unit = "ml_al_register_event_source"

external wait_for_event : event_queue -> event = "ml_al_wait_for_event"


(* Graphics routines *)
external map_rgb : int -> int -> int -> color = "ml_al_map_rgb"
external clear_to_color : color -> unit = "ml_al_clear_to_color"


(* System routines *)
external init : unit -> unit = "ml_al_init"
external uninstall_system : unit -> unit = "ml_al_uninstall_system"


(* Time *)
external rest : float -> unit = "ml_al_rest"
