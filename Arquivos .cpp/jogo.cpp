#include "jogo.h"
#include <iostream>

Jogo::Jogo() :
    gGrafico (gGrafico->get_grafico()), _personagens (), gEvento(gEvento->get_gEvento(gGrafico->get_grafico())) , _fundo(new Fundo(Identificador::fundo))
{
    // define os limite do mapa
    sf::FloatRect limiteMapa (0.0f,0.0f,TAMANHO_TELA_X*3,TAMANHO_TELA_Y*2);
    //gGrafico->set_limiteMapa(limiteMapa);

    // cria o fundo
    sf::Vector2f tamanhoTextura (1200.0f,800.0f), origem (0.0f,0.0f);
    sf::Vector2f tamanhoTextura2 (1200.0f,100.0f), origem2 (0.0f,700.0f);
    _fundo->adicionarCamada ("C:/Users/Caio/Desktop/Projeto Final INF112/Fundo1.png",tamanhoTextura,origem);
    _fundo->adicionarCamada ("C:/Users/Caio/Desktop/Projeto Final INF112/Fundo2.png",tamanhoTextura,origem);
    _fundo->adicionarCamada ("C:/Users/Caio/Desktop/Projeto Final INF112/Fundo3.png",tamanhoTextura2,origem2);

    // aloca dinamicamente um jogador e um inimigo, ja chamando seus construtores e indicando os parametros
    Jogador *_jogador = new Jogador(sf::Vector2f(600.0f,NIVEL_DA_PLATAFORMA));
    Esqueleto* _esqueleto = new Esqueleto(sf::Vector2f(200.0f,NIVEL_DA_PLATAFORMA), _jogador);

    // inicializa o gerenciador de eventos com o jogador
    gEvento->set_jogador(_jogador);    

    // casting de jogador e inimigo, transformando-os em Personagem para adicionarem no vector
    Personagem *p1 = dynamic_cast < Personagem * > (_jogador);
    Personagem *p2 = dynamic_cast < Personagem * > (_esqueleto);

    // coloca os personagens no vector
    _personagens.push_back(p1);
    _personagens.push_back(p2);

    executarJanela();
}

void Jogo::executarJanela () {

    while(gGrafico->janelaEstaAberta()){                        // loop do jogo
        gGrafico->resetarRelogio();
        gEvento->executarLoopEvento();                                    // gerencia os eventos
        gGrafico->limparJanela();                               // limpa a janela
        // atualiza a movimentacao dos personagens 
        for( int i=0 ; i < _personagens.size(); i++){          
            _personagens[i]->atualizar();                          // polimorfismo do metodo movimentar
        }

        // faz uma copia do jogador principal, colocado sempre na primeira posicao do vector
        if (!_personagens.empty()) {                                            // verificacao se o vector nao esta vazio
            Jogador* jogador = dynamic_cast < Jogador* > (_personagens[0]);     // cria uma copia do jogador principal com o downcasting
            if (jogador) {                                                      // verifica se foi possivel realizar o downcasting
                sf::Vector2f posicaoJogador = jogador->get_posicao();           // pega a posicao do jogador 
                               /* // Debug - imprime posição do jogador
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
                         << " Y: " << viewAtual.getCenter().y << std::endl;*/
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
}

Jogo::~Jogo () {
    for (Personagem* p : _personagens) {
        delete p;
    }
    delete _fundo;

}