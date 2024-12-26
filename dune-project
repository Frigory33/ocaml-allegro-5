(lang dune 3.11)
(using dune_site 0.1)

(name allegro5)

(generate_opam_files)

(source (github Frigory33/ocaml-allegro-5))

(authors "Sylvain Chiron")
(maintainers "Sylvain Chiron <chironsylvain@orange.fr>")

(license LGPL-3.0-or-later)

(package
 (name allegro5)
 (synopsis "OCaml Allegro 5")
 (description "An OCaml binding of the Allegro 5 game & multimedia C library")
 (depends ocaml dune conf-allegro5)
 (sites (share ocaml_allegro5)))
