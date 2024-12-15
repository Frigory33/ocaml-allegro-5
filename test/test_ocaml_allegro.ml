module MouseDisc = struct
  type t = {
    pos: Al5.pos;
    time: float;
  }

  let delay = 5.

  let is_visible disc =
    Al5.get_time () -. disc.time <= delay

  let draw disc =
    let time_diff = Al5.get_time () -. disc.time in
    let disc_alpha = 1. -. time_diff /. delay in
    Al5.draw_filled_circle disc.pos 20. (Al5.premul_rgba_f 1. 0. 0. disc_alpha);
    ()
end

module MouseLine = struct
  type t = {
    pos1: Al5.pos;
    pos2: Al5.pos;
    time: float;
  }

  let delay = 0.5

  let is_visible line =
    Al5.get_time () -. line.time <= delay

  let draw line =
    Al5.draw_line line.pos1 line.pos2 (Al5.map_rgb 0 0 0) 1.;
    ()
end

let quitting_delay = 10.


let () =

  Al5.init ();

  Al5.install_keyboard ();
  Al5.install_mouse ();

  Al5.set_new_window_title "OCaml Allegro 5 test";
  let disp = Al5.create_display 640 480 in

  let queue = Al5.create_event_queue () in
  Al5.register_event_source queue (Al5.get_display_event_source disp);
  Al5.register_event_source queue (Al5.get_keyboard_event_source ());
  Al5.register_event_source queue (Al5.get_mouse_event_source ());

  let quit = ref false in
  let last_event_time = ref (Al5.get_time ()) in
  let mouse_discs = ref [] in
  let mouse_lines = ref [] in
  while not !quit && Al5.get_time () -. !last_event_time < quitting_delay do

    Al5.clear_to_color (Al5.map_rgb 128 128 128);
    mouse_discs := List.filter MouseDisc.is_visible !mouse_discs;
    mouse_lines := List.filter MouseLine.is_visible !mouse_lines;
    List.iter MouseDisc.draw !mouse_discs;
    List.iter MouseLine.draw !mouse_lines;
    Al5.flip_display ();

    let rec process_event evt_or_none =
      Option.iter (fun evt ->
          last_event_time := Al5.get_time ();
          begin
            match evt with

            | Al5.Event.KEY_CHAR (keycode, _, modifiers, _, _) ->
                let modifiers = modifiers land (Al5.Keymod.ctrl lor Al5.Keymod.shift lor Al5.Keymod.alt) in
                begin
                  match keycode with
                  | Al5.Key.ESCAPE ->
                      if modifiers = 0 then
                        quit := true;
                  | _ -> ()
                end

            | Al5.Event.MOUSE_AXES move ->
                mouse_lines := {
                    pos1 = float_of_int (move.x - move.dx), float_of_int (move.y - move.dy);
                    pos2 = float_of_int move.x, float_of_int move.y;
                    time = !last_event_time;
                  } :: !mouse_lines;

            | Al5.Event.MOUSE_BUTTON_DOWN button ->
                if button.button = Al5.MouseButton.left then
                  mouse_discs := {
                      pos = float_of_int button.x, float_of_int button.y;
                      time = !last_event_time
                    } :: !mouse_discs;

            | Al5.Event.DISPLAY_CLOSE _ -> quit := true;

            | _ -> ()
          end;
          process_event (Al5.get_next_event queue);
        ) evt_or_none;
    in
    process_event (Al5.get_next_event queue);

  done;

  Al5.destroy_event_queue queue;
  Al5.destroy_display disp;

  ()
