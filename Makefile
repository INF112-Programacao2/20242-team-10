all: compile link

compile:
	g++ -c main.cpp jogo.cpp -I"C:\\Users\\Caio\\Documents\\SFML-2.6.2\\include" -DSFML_STATIC 

link:
	g++ main.o jogo.o -o main -L"C:\Users\Caio\Documents\SFML-2.6.2\lib" -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++ -mwindows -lsfml-main

clean:
	rm -f main *.o