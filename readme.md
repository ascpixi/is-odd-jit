# is-odd-jit
the **is-odd-jit** library is a *blazing* fast way to tell whether a number is even or odd - now leveraging **just-in-time (JIT) compilation!** (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧

> [!TIP]
> you also may be interested in the previous, web version, [ascpixi/is-odd](https://github.com/ascpixi/is-odd)!

in order to use is-odd-jit, compile the library under Linux via `make OS=linux` or `make OS=windows` in the root repository directory - for Windows, you'll also need to run `sudo apt-get install gcc-mingw-w64`.

this will produce a static library named `libisodd-<os>.a` (where `<os>` is the OS the library was compiled for), that you can reference like any other! see the [demo](./demo/) for more details!

currently, the only supported architecture is **x86-64**, and the supported ABIs are System V (most Unices) and the Microsoft x64 (Windows).
