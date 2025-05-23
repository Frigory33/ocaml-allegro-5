let () =
  (* Test that al_wait_for_event_until doesn't block the current domain. *)
  Al5.init ();
  let event_queue = Al5.create_event_queue () in
  let timeout = Al5.init_timeout 3.0 in
  let value = ref 0 in
  let t =
    Thread.create
      (fun () ->
        Thread.delay 1.0;
        value := 99)
      ()
  in
  let before_wait = !value in
  let _ = Al5.wait_for_event_until event_queue false timeout in
  let after_wait = !value in
  Thread.join t;

  let result =
    if before_wait = 0 && after_wait = 99 then Result.ok ()
    else Result.error "al_wait_for_event_until blocked thread execution"
  in
  Format.printf "test_al_wait_for_event_until: %a"
    (Format.pp_print_result
       ~ok:(fun out _v -> Format.fprintf out "ok")
       ~error:Format.pp_print_string)
    result;

  exit (match result with Result.Ok _ -> 0 | _ -> 1)
