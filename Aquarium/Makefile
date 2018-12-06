GCC = g++ -std=c++11 -g
GL = -lGLEW -lGL -lglfw
LIBS = -L../lib/ -L/home/anl/lib/
INCLUDES = -I../include/ -I/home/anl/include/

Aquarium.out: aquarium.o Light.o Camera.o Mesh.o game_object.o PlayerControler.o BubbleControler.o 
	$(GCC) -o Aquarium.out Light.o aquarium.o Camera.o Mesh.o game_object.o PlayerControler.o BubbleControler.o $(GL) $(LIBS) -lcommon

aquarium.o: aquarium.cpp Mesh.hpp game_object.hpp Light.hpp Camera.hpp
	$(GCC) -c $(INCLUDES) aquarium.cpp

Mesh.o: Mesh.cpp Mesh.hpp Camera.hpp Light.hpp
	$(GCC) -c $(INCLUDES) Mesh.cpp

game_object.o: game_object.cpp game_object.hpp Mesh.hpp Camera.hpp Light.hpp
	$(GCC) -c $(INCLUDES) game_object.cpp

PlayerControler.o: PlayerControler.cpp Camera.hpp PlayerControler.hpp game_object.hpp Mesh.hpp Light.hpp
	$(GCC) -c $(INCLUDES) PlayerControler.cpp

BubbleControler.o: BubbleControler.cpp BubbleControler.hpp game_object.hpp Light.hpp
	$(GCC) -c $(INCLUDES) BubbleControler.cpp

Camera.o: Camera.cpp Camera.hpp
	$(GCC) -c $(INCLUDES) Camera.cpp

Light.o: Light.cpp Light.hpp
	$(GCC) -c $(INCLUDES) Light.cpp
clean:
	rm -f *.o *.out
