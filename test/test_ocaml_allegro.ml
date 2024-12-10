let () =

  Al5.init ();

  Al5.install_keyboard ();

  Al5.set_new_window_title "OCaml Allegro 5 test";
  let disp = Al5.create_display 640 480 in

  let queue = Al5.create_event_queue () in
  Al5.register_event_source queue (Al5.get_display_event_source disp);
  Al5.register_event_source queue (Al5.get_keyboard_event_source ());

  let quit = ref false in
  while not !quit do
    Al5.clear_to_color (Al5.map_rgb 128 128 128);
    Al5.flip_display ();

    match Al5.wait_for_event queue with
    | Al5.Event.KEY_CHAR (keycode, _, _, _, _) ->
        (match keycode with
        | Al5.Key.ESCAPE -> quit := true;
        | _ -> ()
        )
    | Al5.Event.DISPLAY_CLOSE _ -> quit := true;
    | _ -> ()
  done;

  Al5.destroy_event_queue queue;
  Al5.destroy_display disp;

  ()
