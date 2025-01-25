#include "jogo.h"
#include <iostream>

Jogo::Jogo() :
    gGrafico (gGrafico->get_grafico()), gEvento(gEvento->get_gEvento(gGrafico->get_grafico())) , faseAtual (nullptr) 
    
    {
            try {
        // Cria o menu
        Menu* menu = new Menu(gGrafico->get_janela());
        gEvento->set_menu(menu);
        
        // Configura o background - substitua pelo caminho do seu arquivo
        gEvento->set_background("fundoInterior.png");
        
        // ... resto do código do construtor ...
    } catch (const std::exception& e) {
        std::cout << "Erro na inicializacao do jogo: " << e.what() << std::endl;
        // ... tratamento de erro ...
    }
   try {
        // Define os limites do mapa
        sf::IntRect limiteCamera(0.0f,0.0f,TAMANHO_TELA_X*4,TAMANHO_TELA_Y);
        gGrafico->set_limiteCamera(limiteCamera);
       /* // Cria o mapa
        std::vector<std::vector<char>> mapa = {
            {'$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$','$'},
            {'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@'},
            {'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {'@','@','@','1','2','3','@','@','@','@','1','2','3','@','@','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {'@','@','@','4',' ','5','@','@','@','@','4',' ','5','@','@','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {'@','@','@','6',' ','7','@','@','@','@','6',' ','7','@','@','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {'@','@','@','6',' ','7','@','@','@','@','6',' ','7','@','@','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {'@','@','@','6',' ','7','@','@','@','@','6',' ','7','@','@','@','P',' ',' ','P',' ',' ','P',' ',' ',' '},
            {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
        };*/

        faseAtual = new Fase();
        
        if (faseAtual) {
            Jogador* jogador = faseAtual->get_jogador();
            if (jogador) {
                gEvento->set_jogador(jogador);
                gEvento->set_fase (faseAtual);
            }
            executarJanela();
        }
    } catch (const std::exception& e) {
        std::cout << "Erro na inicialização do jogo: " << e.what() << std::endl;
        if (faseAtual) {
            delete faseAtual;
            faseAtual = nullptr;
        }
    }
}

void Jogo::executarJanela () {

    while(gGrafico->janelaEstaAberta()){                        // loop do jogo
        gGrafico->resetarRelogio();
        gEvento->executarLoopEvento();                                    // gerencia os eventos
        gGrafico->limparJanela();                               // limpa a janela

        if (!gEvento->get_jogoIniciado()) {
            // Desenha o background e o menu
            gEvento->desenhar_background();
            gEvento->get_menu()->desenhar();
        } else {
            if (faseAtual) {
                faseAtual->executarFase();
            }
        }

        gGrafico->mostrarNaTela();
    }
}

Jogo::~Jogo () {
   if (faseAtual){ 
    delete faseAtual;
    faseAtual = nullptr;
   } 

}