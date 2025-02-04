(lang dune 2.9)

(name allegro5)

(generate_opam_files)

(source (github Frigory33/ocaml-allegro-5))

(authors "Sylvain Chiron <chironsylvain@orange.fr>")
(maintainers "Sylvain Chiron <chironsylvain@orange.fr>")

(license LGPL-3.0-or-later)

(documentation https://frigory33.github.io/ocaml-allegro-5/)

(package
 (name allegro5)
 (synopsis "OCaml Allegro 5")
 (description "An OCaml binding of the Allegro 5 game & multimedia C library")
 (depends (ocaml (>= 4.08)) dune conf-allegro5)
 (sites (share ocaml_allegro5)))
