#include "jogo.h"

Jogo::Jogo() :
    _janela(sf::VideoMode(800.0f,600.0f), "Torre") , _personagens ()
{
    // aloca dinamicamente um jogador e um inimigo, ja chamando seus construtores e indicando os parametros
    Jogador *_jogador = new Jogador(sf::Vector2f(100.0f,200.0f), sf::Vector2f(50.0f,50.0f));
    Inimigo *_inimigo = new Inimigo(sf::Vector2f(200.0f,200.0f), sf::Vector2f(50.0f,50.0f),_jogador);

    // casting de jogador e inimigo, transformando-os em Personagem para adicionarem no vector
    Personagem *p1 = dynamic_cast < Personagem * > (_jogador);
    Personagem *p2 = dynamic_cast< Personagem * > (_inimigo);

    // coloca os personagens no vector
    _personagens.push_back(p1);
    _personagens.push_back(p2);

    executarJanela();
}

void Jogo::executarJanela () {

    while(_janela.isOpen()){
        sf::Event evento;
        if (_janela.pollEvent(evento)){
            if (evento.type==sf::Event::Closed){
                _janela.close();
            }
            else if (evento.type == sf::Event::KeyPressed){
                if (evento.key.code == sf::Keyboard::Escape){
                    _janela.close();
                }
            }
        }

        _janela.clear();
        for( int i=0 ; i < _personagens.size(); i++){ 
            _personagens[i]->movimentar();                          // polimorfismo do metodo movimentar
            _janela.draw(_personagens[i]->get_corpo());             // desenha os personagens
        }
        _janela.display();

    }
    _personagens.clear();   // limpa o vector de personagens
}

Jogo::~Jogo () {

}