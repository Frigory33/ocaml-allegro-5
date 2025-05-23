let () =
  (* Test that al_wait_for_event doesn't block the current domain. *)
  Al5.init ();
  let event_queue = Al5.create_event_queue () in
  let wakeup_timer = Al5.create_timer 3.0 in
  Al5.register_event_source event_queue (Al5.get_timer_event_source wakeup_timer) ;
  let value = ref 0 in
  let t =
    Thread.create
      (fun () ->
        Thread.delay 1.0;
        value := 99)
      ()
  in
  Al5.start_timer wakeup_timer;
  let before_wait = !value in
  let _ = Al5.wait_for_event event_queue in
  let after_wait = !value in
  Thread.join t;

  let result =
    if before_wait = 0 && after_wait = 99 then Result.ok ()
    else Result.error "al_wait_for_event blocked thread execution"
  in
  Format.printf "test_al_wait_for_event: %a"
    (Format.pp_print_result
       ~ok:(fun out _v -> Format.fprintf out "ok")
       ~error:Format.pp_print_string)
    result;

  exit (match result with Result.Ok _ -> 0 | _ -> 1)
