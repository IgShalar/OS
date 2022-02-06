all: main1 main2

main1: lib1.so lib2.so 1.cpp
	g++ 1.cpp -L. -ld1 -ld2 -o main1 -Wl,-rpath -Wl,.

main2: lib1.so libd2.so 2.cpp
	g++ 2.cpp -L. -ldl -o main2 -Wl,-rpath -Wl,.

lib1.so: d1.o 
	g++ -shared d1.o -o libd1.so 

lib2.so: d2.o 
	g++ -shared d2.o -o libd2.so 

d1.o: lib1.cpp
	g++ -fPIC -c lib1.cpp -o d1.o

d2.o: lib2.cpp
	g++ -fPIC -c lib2.cpp -o d2.o
clean:
	rm -r *.so *.o main1 main2