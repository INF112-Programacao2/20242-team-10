#include "jogo.h"

Jogo::Jogo() :
    gGrafico (gGrafico->get_grafico()), _personagens () , gEvento(gEvento->get_gEvento(gGrafico->get_grafico()))
{
    // aloca dinamicamente um jogador e um inimigo, ja chamando seus construtores e indicando os parametros
    Jogador *_jogador = new Jogador(sf::Vector2f(100.0f,200.0f), sf::Vector2f(50.0f,50.0f));
    Inimigo *_inimigo = new Inimigo(sf::Vector2f(200.0f,200.0f), sf::Vector2f(50.0f,50.0f),_jogador);

    // coloca o jogador no gerenciador de eventos
    gEvento->set_jogador(_jogador);

    // casting de jogador e inimigo, transformando-os em Personagem para adicionarem no vector
    Personagem *p1 = dynamic_cast < Personagem * > (_jogador);
    Personagem *p2 = dynamic_cast< Personagem * > (_inimigo);

    // coloca os personagens no vector
    _personagens.push_back(p1);
    _personagens.push_back(p2);

    executarJanela();
}

void Jogo::executarJanela () {

    while(gGrafico->janelaEstaAberta()){                        // loop do jogo
        gEvento->executar();                                    // gerencia os eventos
        gGrafico->limparJanela();                               // limpa a janela
        for( int i=0 ; i < _personagens.size(); i++){          
            _personagens[i]->movimentar();                          // polimorfismo do metodo movimentar
           gGrafico->desenhar(_personagens[i]->get_corpo());        // desenha os personagens
        }
        gGrafico->mostrarNaTela();                              // mostra na tela os personagens

    }
    _personagens.clear();   // limpa o vector de personagens
}

Jogo::~Jogo () {

}