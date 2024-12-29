#include "jogo.h"

Jogo::Jogo() :
    janela(sf::VideoMode(800.0f,600.0f), "Torre")
{
    executarJanela();
}

void Jogo::executarJanela () {
    sf::RectangleShape jogador(sf::Vector2f(50.0f,50.0f));
    jogador.setFillColor(sf::Color::Green);

    while(janela.isOpen()){
        sf::Event evento;
        if (janela.pollEvent(evento)){
            if (evento.type==sf::Event::Closed){
                janela.close();
            }
            else if (evento.type == sf::Event::KeyPressed){
                if (evento.key.code == sf::Keyboard::Escape){
                    janela.close();
                }
            }
        }

        janela.clear();
        janela.draw(jogador);
        janela.display();

    }
}

Jogo::~Jogo () {

}