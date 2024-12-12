let () =

  Al5.init ();

  Al5.install_keyboard ();

  Al5.set_new_window_title "OCaml Allegro 5 test";
  let disp = Al5.create_display 640 480 in

  let queue = Al5.create_event_queue () in
  Al5.register_event_source queue (Al5.get_display_event_source disp);
  Al5.register_event_source queue (Al5.get_keyboard_event_source ());

  let quit = ref false in
  let quitting_delay = 5. in
  let last_event_time = ref (Al5.get_time ()) in
  while not !quit && Al5.get_time () -. !last_event_time < quitting_delay do

    Al5.clear_to_color (Al5.map_rgb 128 128 128);
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

            | Al5.Event.DISPLAY_CLOSE _ -> quit := true;

            | _ -> ()
          end;
          process_event (Al5.get_next_event queue);
        ) evt_or_none;
    in
    process_event (Al5.wait_for_event_timed queue true quitting_delay);

  done;

  Al5.destroy_event_queue queue;
  Al5.destroy_display disp;

  ()
