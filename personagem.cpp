#include "personagem.h"

// primeiro construtor 
Personagem::Personagem (const sf::Vector2f posicao, const sf::Vector2f tamanho) :
    _corpo (sf::RectangleShape (tamanho))                                             // criar um corpo com algum tamanho
    {
        _corpo.setPosition (posicao); _corpo.setFillColor (sf::Color::Red);           // indica a posicao e a cor desse corpo
        //inicializaVelocidade();                                                       // inicializa a velocidade do corpo
    } 

// funcao que retorna o corpo
const sf::RectangleShape Personagem::get_corpo () {
    return this->_corpo;
}

// destrutor
    Personagem::~Personagem () {

    }



