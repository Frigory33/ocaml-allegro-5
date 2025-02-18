(lang dune 2.9)
(using dune_site 0.1)

(name ocaml_allegro5_test)

(source (github Frigory33/ocaml-allegro-5-test))

(authors "Sylvain Chiron <chironsylvain@orange.fr>")
(maintainers "Sylvain Chiron <chironsylvain@orange.fr>")

(license WTFPL)

(package
 (name ocaml_allegro5_test)
 (synopsis "OCaml Allegro 5 Test")
 (description "OCaml Allegro 5 Test")
 (depends (ocaml (>= 4.08)) dune allegro5 dune-site)
 (sites (share files)))
