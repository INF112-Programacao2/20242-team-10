



.PHONY: all compile link clean

all: compile link

compile:
	g++ -c main.cpp jogo.cpp jogador.cpp gerenciadormusica.cpp menu.cpp acessibilidade.cpp personagem.cpp inimigo.cpp gerenciadorgrafico.cpp mensagemBox.cpp gerenciadoreventos.cpp entidade.cpp animacao.cpp arma.cpp imagem.cpp camera.cpp camada.cpp fundo.cpp listaentidade.cpp gerenciadorcolisao.cpp fase.cpp experiencia.cpp esqueleto.cpp plataforma.cpp obstaculo.cpp morcego.cpp texto.cpp goblin.cpp espinho.cpp alma.cpp projetil.cpp chefao.cpp -I"C:\\Users\\Caio\\Documents\\SFML-2.6.2\\include" -g

link:
	g++ main.o jogo.o gerenciadormusica.o personagem.o acessibilidade.o menu.o jogador.o inimigo.o gerenciadorgrafico.o mensagemBox.o gerenciadoreventos.o entidade.o animacao.o imagem.o camera.o arma.o experiencia.o camada.o fundo.o listaentidade.o gerenciadorcolisao.o esqueleto.o fase.o morcego.o plataforma.o obstaculo.o texto.o goblin.o espinho.o alma.o projetil.o chefao.o -o main -L"C:\Users\Caio\Documents\SFML-2.6.2\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -mconsole -g

clean:
	rm -f *.o main.exe




##.PHONY: all compile link clean

#all: compile link

#compile:
#	g++ -c main.cpp jogo.cpp jogador.cpp menu.cpp personagem.cpp inimigo.cpp gerenciadorgrafico.cpp mensagemBox.cpp gerenciadoreventos.cpp gerenciadormusica.cpp entidade.cpp animacao.cpp arma.cpp imagem.cpp camera.cpp camada.cpp fundo.cpp listaentidade.cpp gerenciadorcolisao.cpp fase.cpp experiencia.cpp esqueleto.cpp plataforma.cpp obstaculo.cpp morcego.cpp texto.cpp goblin.cpp textosom.cpp espinho.cpp alma.cpp projetil.cpp chefao.cpp -I"C:\\Users\\Caio\\Documents\\SFML-2.6.2\\include" -DSFML_STATIC -g

#link:
#	g++ main.o jogo.o personagem.o menu.o jogador.o inimigo.o gerenciadorgrafico.o mensagemBox.o gerenciadoreventos.o gerenciadormusica.o entidade.o animacao.o imagem.o camera.o arma.o experiencia.o camada.o fundo.o listaentidade.o gerenciadorcolisao.o esqueleto.o fase.o morcego.o plataforma.o obstaculo.o texto.o goblin.o espinho.o alma.o projetil.o textosom.o chefao.o -o main -L"C:\Users\Caio\Documents\SFML-2.6.2\lib" -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lopenal32 -lvorbis -lvorbisenc -lvorbisfile -logg -lfreetype -lwinmm -lgdi32 -static-libgcc -static-libstdc++ -mconsole -g

#clean:
#	rm -f *.o main.exe


