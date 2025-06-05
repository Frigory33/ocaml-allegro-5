# 0.3 (2025-06)

- Creation of the OCaml Allegro 5 Main package to make the library work on OS X.
- Fix blocking functions (`Al5.wait_for_event`…) not working in threaded programs.
- Improve soundness of flags by using `flags` types.
- Fix `Al5.key_down`.


# 0.2 (2025-03)

- Audio: support for a basic API.
- Displays: support for size and position.
- Fullscreen modes: full support (put in the Displays module).
- Graphics: various new supported functions.
- Joystick: full support.
- Shader: full support.
- System: support for standard paths.
- Touch input: full support.
- Primitives addon: support for spline and ribbon.


# 0.1 (2025-02)

First release. Includes elements of the following Allegro 5 modules:

- Displays
- Events
- Graphics
- Keyboard (full support)
- Mouse (full support)
- System
- Time (full support)
- Timer (full support)
- Font addons
- Image addon (full support)
- Primitives addon
