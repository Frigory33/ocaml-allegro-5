let () =
  (* Test that al_rest doesn't block the current domain. *)
  Al5.init ();
  let value = ref 0 in
  let t =
    Thread.create
      (fun () ->
        Thread.delay 1.0;
        value := 99)
      ()
  in

  let before_rest = !value in
  Al5.rest 3.0;
  let after_rest = !value in
  Thread.join t;

  let result =
    if before_rest = 0 && after_rest = 99 then Result.ok ()
    else Result.error "al_rest blocked thread execution"
  in
  Format.printf "test_al_rest: %a"
    (Format.pp_print_result
       ~ok:(fun out _v -> Format.fprintf out "ok")
       ~error:Format.pp_print_string)
    result;

  exit (match result with Result.Ok _ -> 0 | _ -> 1)
