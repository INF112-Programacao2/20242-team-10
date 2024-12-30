#include "jogo.h"

Jogo::Jogo() :
    _janela(sf::VideoMode(800.0f,600.0f), "Torre") , _personagem (sf::Vector2f(50.0f,50.0f) , sf::Vector2f(50.0f,50.0f))
{
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
        _personagem.movimentar();
        _janela.draw(_personagem.get_corpo());
        _janela.display();

    }
}

Jogo::~Jogo () {

}