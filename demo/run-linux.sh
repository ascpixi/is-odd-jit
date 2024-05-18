(cd .. && make OS=linux)
gcc -o demo main.c -L.. -lisodd-linux
./demo
