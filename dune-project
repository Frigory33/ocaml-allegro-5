(lang dune 3.11)
(using dune_site 0.1)

(name test_ocaml_allegro5)

(source (github Frigory33/ocaml-allegro-5-test))

(authors "Sylvain Chiron <chironsylvain@orange.fr>")
(maintainers "Sylvain Chiron <chironsylvain@orange.fr>")

(license WTFPL)

(package
 (name test_ocaml_allegro5)
 (synopsis "OCaml Allegro 5 Test")
 (description "OCaml Allegro 5 Test")
 (depends (ocaml (>= 4.12)) dune allegro5 dune-site)
 (sites (share test_ocaml_allegro5)))
