let () =

  Al5.init ();

  Al5.set_new_window_title "OCaml Allegro 5 test";
  let disp = Al5.create_display 640 480 in

  Al5.clear_to_color (Al5.map_rgb 128 128 128);
  Al5.flip_display ();

  Al5.rest 3.;

  Al5.destroy_display disp;

  ()
