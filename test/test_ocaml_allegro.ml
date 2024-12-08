let () =

  Al5.init ();

  Al5.set_new_window_title "OCaml Allegro 5 test";
  let disp = Al5.create_display 640 480 in
  let queue = Al5.create_event_queue () in
  Al5.register_event_source queue (Al5.get_display_event_source disp);

  let quit = ref false in
  while not !quit do
    Al5.clear_to_color (Al5.map_rgb 128 128 128);
    Al5.flip_display ();

    match Al5.wait_for_event queue with
    | Al5.EVENT_DISPLAY_CLOSE _ -> quit := true;
    | _ -> ()
  done;

  Al5.destroy_display disp;

  ()
