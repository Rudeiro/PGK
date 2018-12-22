GCC = g++ -std=c++17 -g -lstdc++fs
GL = -lGLEW -lGL -lglfw
LIBS = -L../lib/ -L/home/anl/lib/
INCLUDES = -I../include/ -I/home/anl/include/

Terrain.out: terrain.o Camera.o Mesh.o GameObject.o DataReader.o
	$(GCC) -o Terrain.out terrain.o Camera.o Mesh.o GameObject.o DataReader.o $(GL) $(LIBS) -lcommon

terrain.o: terrain.cpp Mesh.hpp Camera.hpp
	$(GCC) -c $(INCLUDES) terrain.cpp

Mesh.o: Mesh.cpp Mesh.hpp Camera.hpp
	$(GCC) -c $(INCLUDES) Mesh.cpp

Camera.o: Camera.hpp Camera.hpp
	$(GCC) -c $(INCLUDES) Camera.cpp

GameObject.o: GameObject.cpp GameObject.hpp Mesh.hpp
	$(GCC) -c $(INCLUDES) GameObject.cpp

DataReader.o: DataReader.cpp DataReader.hpp
	$(GCC) -c $(INCLUDES) DataReader.cpp
clean:
	rm -f *.o *.out
