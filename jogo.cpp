#include "jogo.h"
#include <iostream>

Jogo::Jogo() :
    gGrafico (gGrafico->get_grafico()), gEvento(gEvento->get_gEvento(gGrafico->get_grafico())) , faseAtual (nullptr)
{
   try {
        // Define os limites do mapa
        sf::IntRect limiteCamera(0.0f,0.0f,TAMANHO_TELA_X*2,TAMANHO_TELA_Y);
        gGrafico->set_limiteCamera(limiteCamera);

        // Cria o mapa
        std::vector<std::vector<char>> mapa = {
            {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','%',' '},
            {'#','#','#','#','#','#','#','#','#','#','#','#'}
        };

        faseAtual = new ChegadaCastelo(mapa);
        
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
        /*// atualiza a movimentacao dos personagens 
        for( int i=0 ; i < _personagens.size(); i++){          
            _personagens[i]->atualizar();                          // polimorfismo do metodo movimentar
        }

        // faz uma copia do jogador principal, colocado sempre na primeira posicao do vector
        if (!_personagens.empty()) {                                            // verificacao se o vector nao esta vazio
            Jogador* jogador = dynamic_cast < Jogador* > (_personagens[0]);     // cria uma copia do jogador principal com o downcasting
            if (jogador) {                                                      // verifica se foi possivel realizar o downcasting
                sf::Vector2f posicaoJogador = jogador->get_posicao();           // pega a posicao do jogador 
                                // Debug - imprime posição do jogador
                std::cout << "Posicao do Jogador - X: " << posicaoJogador.x 
                         << " Y: " << posicaoJogador.y << std::endl;

                // Debug - imprime posição da câmera antes da atualização
                sf::View viewAtual = gGrafico->get_camera();
                std::cout << "Camera antes - X: " << viewAtual.getCenter().x 
                         << " Y: " << viewAtual.getCenter().y << std::endl;

                gGrafico->atualizaCamera(posicaoJogador);

                // Debug - imprime posição da câmera depois da atualização
                viewAtual = gGrafico->get_camera();
                std::cout << "Camera depois - X: " << viewAtual.getCenter().x 
                         << " Y: " << viewAtual.getCenter().y << std::endl;
                gGrafico->atualizaCamera(posicaoJogador);                       // atualiza a posicao da camera de acordo com a posicao do jogador principal
            }
        }
        _fundo->executar();
        for( int i=0 ; i < _personagens.size(); i++){          
           gGrafico->desenhar(_personagens[i]->get_corpo());        // desenha os personagens
        }
        gGrafico->mostrarNaTela();                              // mostra na tela os personagens

    }
    _personagens.clear();   // limpa o vector de personagens
}*/

void Jogo::mudarFase(Identificador idFase){
      if (faseAtual){ 
        delete faseAtual;
        faseAtual = nullptr;
   } 

   switch (idFase) {
    case Identificador::chegadaCastelo: {
        std::vector < std::vector < char >> mapa = {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','%',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','%',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','%',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','%',' ',' '},
        {'#','#','#','#','#','#','#','#','#','#','#','#'}
    };

    faseAtual = new ChegadaCastelo(mapa);
    break;
    }
    // adicionar as outras fases
   }

}

Jogo::~Jogo () {
   if (faseAtual){ 
    delete faseAtual;
    faseAtual = nullptr;
   } 

}