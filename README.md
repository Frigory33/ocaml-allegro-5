# OCaml Allegro 5

This is an OCaml binding for the [Allegro 5](https://liballeg.org/) C library.

You shall install it with:
```sh
opam install allegro5
```

Allegro 5 development libraries (including addons) must be installed on your system for OCaml Allegro 5 to work. For instance, on Arch Linux, they are provided by the `allegro` package. The minimum supported version is Allegro 5.2.7.

## Documentation

Available at https://frigory33.github.io/ocaml-allegro-5/.

It follows a structure close to the structure of the original C library’s documentation.

## Dune commands

```sh
dune build
dune build @doc
dune install
dune uninstall
```

## Contribute

Merge requests and bug reports are very welcome! Please join the project!

You can also create a bug report for a feature request.

A small repository for testing the binding is available at [ocaml-allegro-5-test](https://github.com/Frigory33/ocaml-allegro-5-test).
