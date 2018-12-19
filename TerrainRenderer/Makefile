GCC = g++ -std=c++11 -g
GL = -lGLEW -lGL -lglfw
LIBS = -L../lib/ -L/home/anl/lib/
INCLUDES = -I../include/ -I/home/anl/include/

Aquarium.out: aquarium.o Camera.o Mesh.o 
	$(GCC) -o Aquarium.out aquarium.o Camera.o Mesh.o $(GL) $(LIBS) -lcommon

aquarium.o: aquarium.cpp Mesh.hpp Camera.hpp
	$(GCC) -c $(INCLUDES) aquarium.cpp

Mesh.o: Mesh.cpp Mesh.hpp Camera.hpp
	$(GCC) -c $(INCLUDES) Mesh.cpp

Camera.o: Camera.cpp Camera.hpp
	$(GCC) -c $(INCLUDES) Camera.cpp


clean:
	rm -f *.o *.out
