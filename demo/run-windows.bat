wsl make -C .. OS=windows
wsl x86_64-w64-mingw32-gcc -o demo.exe main.c -L.. -lisodd-windows -lkernel32
demo.exe