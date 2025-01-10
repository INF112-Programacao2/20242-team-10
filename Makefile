.PHONY: all compile link clean

all: compile link

compile:
	g++ -c main.cpp jogo.cpp personagem.cpp jogador.cpp inimigo.cpp gerenciadorgrafico.cpp gerenciadoreventos.cpp entidade.cpp animacao.cpp imagem.cpp camera.cpp camada.cpp fundo.cpp esqueleto.cpp -I"C:\\Users\\Caio\\Documents\\SFML-2.6.2\\include" -DSFML_STATIC -g

link:
	g++ main.o jogo.o personagem.o jogador.o inimigo.o gerenciadorgrafico.o gerenciadoreventos.o entidade.o animacao.o imagem.o camera.o camada.o fundo.o esqueleto.o -o main -L"C:\Users\Caio\Documents\SFML-2.6.2\lib" -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++ -mconsole -g

clean:
	rm -f *.o main.exe



