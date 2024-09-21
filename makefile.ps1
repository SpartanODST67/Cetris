gcc pieces.c -o pieces.o -c
gcc score.c -o score.o -c
gcc LinkedList.c -o LinkedList.o -c
gcc Cetris.c -o Cetris.o -c
gcc Cetris.o pieces.o LinkedList.o score.o -o Cetris.exe
Remove-Item *.o