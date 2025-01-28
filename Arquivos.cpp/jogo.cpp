#include "jogo.h"
#include <iostream>

Jogo::Jogo() :
    gGrafico (gGrafico->get_grafico()),
    gEvento(gEvento->get_gEvento(gGrafico->get_grafico())),
    gMusica(gMusica->get_gerenciadorMusical()),
    faseAtual (nullptr),
    musicaIniciada (false) 
    
    {
        try {
        // Cria o menu
        Menu* menu = new Menu(gGrafico->get_janela());
        gEvento->set_menu(menu);
        
        // Configura o background
        gEvento->set_background("fundoInterior.png");
        
    } catch (const std::exception& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }
        // Define os limites do mapa
        sf::IntRect limiteCamera(0.0f,0.0f,TAMANHO_TELA_X*4,TAMANHO_TELA_Y);
        gGrafico->set_limiteCamera(limiteCamera);

        faseAtual = new Fase();                            // cria a fase
        
        if (faseAtual) {
            Jogador* jogador = faseAtual->get_jogador();                            // pega o jogador da fase
            if (jogador) {
                gEvento->set_jogador(jogador);                                      // seta esse jogador no loop de eventos
                gEvento->set_fase (faseAtual);                                      // seta a fase no loop de eventos
            }
            executarJanela();                                                       // executa a janela
        }
    }

void Jogo::executarJanela () {

    while(gGrafico->janelaEstaAberta()){                                    // loop do jogo
        gGrafico->resetarRelogio();                                         // reinicia o relogio do jogo
        gEvento->executarLoopEvento();                                     // gerencia os eventos
        gGrafico->limparJanela();                                           // limpa a janela

        // se o jogo nao foi iniciado ainda
        if (!gEvento->get_jogoIniciado()) {
            gMusica->parar();                                           // para a música quando voltar para o menu
            musicaIniciada = false;
            // Desenha o background e o menu
            gEvento->desenhar_background();
            gEvento->get_menu()->desenhar();
        } else {
            // se o jogo ja comecou
            if (faseAtual) {
                if (!musicaIniciada) {
                    // inicia a musica
                    gMusica->tocar(Identificador::musica_background);
                    musicaIniciada = true;
                }
                // executa a fase
                faseAtual->executarFase();
            }
        }

        // mostra na tela (display)
        gGrafico->mostrarNaTela();
    }
}

// destrutor
Jogo::~Jogo () {
    if (gMusica) {
        gMusica->parar();  // para a música antes de destruir
    }
    if (faseAtual) {
        delete faseAtual;
        faseAtual = nullptr;
    }

}