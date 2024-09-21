gcc pieces.c -o pieces.o -c
gcc LinkedList.c -o LinkedList.o -c
gcc Cetris.c -o Cetris.o -c
gcc Cetris.o pieces.o LinkedList.o -o Cetris.exe
Remove-Item *.o