GCC = g++ -std=c++17 -g -lstdc++fs
GL = -lGLEW -lGL -lglfw
LIBS = -L../lib/ -L/home/anl/lib/
INCLUDES = -I../include/ -I/home/anl/include/

Texture.out: texture.o 
	$(GCC) -o Texture.out texture.o $(GL) $(LIBS) -lcommon 

texture.o: texture.cpp 
	$(GCC) -c $(INCLUDES) texture.cpp


clean:
	rm -f *.o *.out