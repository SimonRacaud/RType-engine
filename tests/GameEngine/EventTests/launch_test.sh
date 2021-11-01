g++ -I. -fPIC -c main.cpp PrintingSystem.cpp AbstractEvent.cpp global.cpp
g++ -I. main.o PrintingSystem.o AbstractEvent.o global.o
./a.out
rm *.o
