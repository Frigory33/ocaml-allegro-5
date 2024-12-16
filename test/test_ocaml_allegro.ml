module ClickShape = struct
  type shape =
  | Disc
  | Triangle

  type t = {
    pos: Al5.pos;
    shape: shape;
    time: float;
  }

  let delay = 5.

  let is_visible shape =
    Al5.get_time () -. shape.time <= delay

  let draw shape =
    let time_diff = Al5.get_time () -. shape.time in
    let alpha = 1. -. time_diff /. delay in
    let x, y = shape.pos in
    match shape.shape with
    | Disc ->
        Al5.draw_filled_circle shape.pos 20. (Al5.premul_rgba_f 1. 0. 0. alpha);
        ()
    | Triangle ->
        Al5.draw_filled_triangle (x -. 20., y +. 10.) (x +. 20., y +. 10.) (x, y -. 10.)
          (Al5.premul_rgba_f 0. 0. 1. alpha);
        ()
end

module MouseLine = struct
  type shape =
  | Line
  | Allegator

  type t = {
    pos1: Al5.pos;
    pos2: Al5.pos;
    shape: shape;
    time: float;
  }

  let delay = 0.5

  let alleg_img = ref None

  let is_visible line =
    Al5.get_time () -. line.time <= delay

  let draw line =
    let x1, y1 = line.pos1
    and x2, y2 = line.pos2 in
    let alpha = 1. -. (Al5.get_time () -. line.time) /. delay in
    match line.shape with
    | Line ->
        Al5.draw_line line.pos1 line.pos2 (Al5.map_rgba_f 0. 0. 0. alpha) 1.;
        ()
    | Allegator ->
        let alleg_img = Option.get !alleg_img in
        let cx = float_of_int (Al5.get_bitmap_width alleg_img) /. 2.
        and cy = float_of_int (Al5.get_bitmap_height alleg_img) /. 2. in
        let angle = atan2 (y2 -. y1) (x2 -. x1) in
        Al5.draw_rotated_bitmap alleg_img ~tint:(Al5.premul_rgba_f 1. 1. 1. alpha) (cx, cy) line.pos2 angle 0;
        ()
end

let quitting_delay = 10.


let () =

  Al5.init ();
  Al5.init_image_addon ();
  Al5.init_primitives_addon ();

  Al5.install_keyboard ();
  Al5.install_mouse ();

  let rsrc_folder = List.hd Sites.Sites.ocaml_allegro5 in
  let alleg_img = Al5.load_bitmap (Filename.concat rsrc_folder "allegator.png") in
  MouseLine.alleg_img := Some alleg_img;

  Al5.set_new_window_title "OCaml Allegro 5 test";
  let disp = Al5.create_display 640 480 in
  Al5.set_display_icon disp alleg_img;

  let queue = Al5.create_event_queue () in
  Al5.register_event_source queue (Al5.get_display_event_source disp);
  Al5.register_event_source queue (Al5.get_keyboard_event_source ());
  Al5.register_event_source queue (Al5.get_mouse_event_source ());

  let quit = ref false in
  let cur_style = ref 0 in
  let last_event_time = ref (Al5.get_time ()) in
  let click_shapes = ref [] in
  let mouse_lines = ref [] in
  while not !quit && Al5.get_time () -. !last_event_time < quitting_delay do

    Al5.clear_to_color (Al5.map_rgb 128 128 128);
    Al5.draw_polyline [|100., 200.; 200., 100.; 400., 300.; 500., 200.|]
      (Al5.LineJoin.MITER 2.) Al5.LineCap.ROUND (Al5.map_rgb 0 224 0) 10.;
    click_shapes := List.filter ClickShape.is_visible !click_shapes;
    mouse_lines := List.filter MouseLine.is_visible !mouse_lines;
    List.iter ClickShape.draw (List.rev !click_shapes);
    List.iter MouseLine.draw (List.rev !mouse_lines);
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
                if move.dx <> 0 || move.dy <> 0 then (
                  mouse_lines := {
                      pos1 = float_of_int (move.x - move.dx), float_of_int (move.y - move.dy);
                      pos2 = float_of_int move.x, float_of_int move.y;
                      shape = (match !cur_style with 0 -> Line | _ -> Allegator);
                      time = !last_event_time;
                    } :: !mouse_lines;
                ) else if move.dz <> 0 then (
                  let nb_styles = 2 in
                  cur_style := ((!cur_style + move.dz) mod nb_styles + nb_styles) mod nb_styles;
                );

            | Al5.Event.MOUSE_BUTTON_DOWN button ->
                if button.button = Al5.MouseButton.left then
                  click_shapes := {
                      pos = float_of_int button.x, float_of_int button.y;
                      shape = (match !cur_style with 0 -> Disc | _ -> Triangle);
                      time = !last_event_time;
                    } :: !click_shapes;

            | Al5.Event.DISPLAY_CLOSE _ -> quit := true;

            | _ -> ()
          end;
          process_event (Al5.get_next_event queue);
        ) evt_or_none;
    in
    process_event (Al5.get_next_event queue);

  done;

  Al5.destroy_bitmap alleg_img;

  Al5.destroy_event_queue queue;
  Al5.destroy_display disp;

  ()
