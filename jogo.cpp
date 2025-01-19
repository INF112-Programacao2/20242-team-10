#include "jogo.h"
#include <iostream>

Jogo::Jogo() :
    gGrafico (gGrafico->get_grafico()), gEvento(gEvento->get_gEvento(gGrafico->get_grafico())) , faseAtual (nullptr) 
    
    {
   try {
        // Define os limites do mapa
        sf::IntRect limiteCamera(0.0f,0.0f,TAMANHO_TELA_X*3,TAMANHO_TELA_Y);
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

        if (faseAtual){
            faseAtual->executarFase();
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