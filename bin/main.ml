module ClickShape = struct
  type shape =
  | Disc
  | Triangle

  type t = {
    pos : Al5.pos;
    shape : shape;
    time : float;
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
  | Image

  type t = {
    pos1 : Al5.pos;
    pos2 : Al5.pos;
    shape : shape;
    time : float;
  }

  let delay = 0.5

  let img = ref None

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
    | Image ->
        let alleg_img = Option.get !img in
        let cx = float_of_int (Al5.get_bitmap_width alleg_img) /. 2.
        and cy = float_of_int (Al5.get_bitmap_height alleg_img) /. 2. in
        let angle = atan2 (y2 -. y1) (x2 -. x1) in
        Al5.draw_rotated_bitmap alleg_img ~tint:(Al5.premul_rgba_f 1. 1. 1. alpha) (cx, cy) line.pos2 angle 0;
        ()
end

type data = {
  disp : Al5.display option;
  font : Al5.font;
  music: Al5.audio_stream;
  sound: Al5.sample;
  queue : Al5.event_queue;
  quit : bool;
  cur_style : int;
  last_event_time : float;
  click_shapes : ClickShape.t list;
  mouse_lines : MouseLine.t list;
  timer_value : int;
}

let quitting_delay = 5.


let draw data =
  let version = Al5.get_allegro_version () in
  let major = version lsr 24
  and minor = (version lsr 16) land 0xFF
  and revision = (version lsr 8) land 0xFF
  and release = version land 0xFF in

  Al5.clear_to_color (Al5.map_rgb 128 128 128);
  Al5.draw_polyline [|100., 200.; 200., 100.; 400., 300.; 500., 200.|]
    (Al5.LineJoin.MITER 2.) Al5.LineCap.ROUND (Al5.map_rgb 0 224 0) 10.;
  Printf.sprintf "OCaml Allegro 5 ~~ %d ~~ Allegro %d.%d.%d[%d]" data.timer_value major minor revision release
  |> Al5.draw_text data.font (Al5.map_rgb 0 0 0) (320., 10.) Al5.Text.align_centre;
  List.iter ClickShape.draw (List.rev data.click_shapes);
  List.iter MouseLine.draw (List.rev data.mouse_lines);
  Al5.flip_display ();
  ()


let events data =
  let rec process_event data evt =
    let last_event_time =
      match evt with
      | Al5.Event.TIMER _ -> data.last_event_time
      | _ -> Al5.get_time ()
    in
    let data =
      match evt with

      | Al5.Event.KEY_CHAR (keycode, _, modifiers, _, _) ->
          let modifiers = modifiers land (Al5.Keymod.ctrl lor Al5.Keymod.shift lor Al5.Keymod.alt) in
          let data =
            match keycode with
            | Al5.Key.ESCAPE ->
                if modifiers = 0 then { data with quit = true } else data
            | _ -> data
          in
          data

      | Al5.Event.MOUSE_AXES move ->
          if move.dx <> 0 || move.dy <> 0 then (
            let mouse_line = MouseLine.{
                pos1 = float_of_int (move.x - move.dx), float_of_int (move.y - move.dy);
                pos2 = float_of_int move.x, float_of_int move.y;
                shape = (match data.cur_style with 0 -> Line | _ -> Image);
                time = data.last_event_time;
              } in
            { data with mouse_lines = mouse_line :: data.mouse_lines }
          ) else if move.dz <> 0 then (
            let nb_styles = 2 in
            let cur_style = ((data.cur_style + move.dz) mod nb_styles + nb_styles) mod nb_styles in
            begin
              match cur_style with
              | 0 ->
                  ignore @@ Al5.set_audio_stream_playing data.music false;
                  ignore @@ Al5.play_sample data.sound 1. 0. 1. Al5.Playmode.ONCE;
              | 1 ->
                  ignore @@ Al5.rewind_audio_stream data.music;
                  ignore @@ Al5.set_audio_stream_playing data.music true;
              | _ -> ()
            end;
            { data with cur_style }
          ) else (
            data
          )

      | Al5.Event.MOUSE_BUTTON_DOWN button ->
          if button.button = Al5.MouseButton.left then (
            let click_shape = ClickShape.{
                pos = float_of_int button.x, float_of_int button.y;
                shape = (match data.cur_style with 0 -> Disc | _ -> Triangle);
                time = data.last_event_time;
              } in
            { data with click_shapes = click_shape :: data.click_shapes }
          ) else (
            data
          )

      | Al5.Event.TIMER _ -> { data with timer_value = data.timer_value + 1 }

      | Al5.Event.DISPLAY_CLOSE _ -> { data with quit = true }

      | _ -> data
    in
    let data = { data with last_event_time } in
    process_next_event data

  and process_next_event data =
    match Al5.get_next_event data.queue with
    | Some evt -> process_event data evt
    | None -> data
  in

  process_next_event data


let rec main_loop data =
  if not data.quit && Al5.get_time () -. data.last_event_time < quitting_delay then (
    if data.disp <> None then (
      draw data;
    );

    let data = events data in

    let click_shapes = List.filter ClickShape.is_visible data.click_shapes
    and mouse_lines = List.filter MouseLine.is_visible data.mouse_lines in

    main_loop { data with click_shapes; mouse_lines };
  );
  ()


let () =

  Al5.init ();
  Al5.install_audio ();
  Al5.init_acodec_addon ();
  Al5.init_font_addon ();
  Al5.init_image_addon ();
  Al5.init_primitives_addon ();

  let queue = Al5.create_event_queue () in

  let () =
    try
      Al5.install_keyboard ();
      Al5.register_event_source queue (Al5.get_keyboard_event_source ());
    with
    | Failure _ -> ()
  in

  let () =
    try
      Al5.install_mouse ();
      Al5.register_event_source queue (Al5.get_mouse_event_source ());
    with
    | Failure _ -> ()
  in

  let rsrc_folder = List.hd Sites.Sites.ocaml_allegro5_test in
  let img = Al5.load_bitmap (Filename.concat rsrc_folder "image.png") in
  MouseLine.img := Some img;
  let font = Al5.create_builtin_font () in
  let music = Al5.load_audio_stream (Filename.concat rsrc_folder "music.ogg") 4 2048 in
  let sound = Al5.load_sample (Filename.concat rsrc_folder "sound.wav") in

  begin
    try
      Al5.reserve_samples 1;
      ignore @@ Al5.set_audio_stream_playing music false;
      ignore @@ Al5.set_audio_stream_playmode music Al5.Playmode.LOOP;
      ignore @@ Al5.attach_audio_stream_to_mixer music (Al5.get_default_mixer ());
    with
    | Failure _ -> ()
  end;

  let disp =
    try
      Al5.set_new_window_title "OCaml Allegro 5 test";
      let disp = Al5.create_display 640 480 in
      Al5.set_display_icon disp img;
      Al5.register_event_source queue (Al5.get_display_event_source disp);
      Some disp
    with
    | Failure _ -> None
  in

  let timer = Al5.create_timer 0.1 in
  Al5.register_event_source queue (Al5.get_timer_event_source timer);
  Al5.start_timer timer;

  main_loop {
      disp; font; music; sound; queue;
      quit = false;
      cur_style = 0;
      last_event_time = Al5.get_time ();
      click_shapes = [];
      mouse_lines = [];
      timer_value = 0;
    };

  Al5.destroy_bitmap img;
  Al5.destroy_font font;
  Al5.destroy_audio_stream music;
  Al5.destroy_sample sound;

  Al5.destroy_event_queue queue;
  Option.iter Al5.destroy_display disp;

  ()
