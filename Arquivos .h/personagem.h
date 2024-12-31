#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include <SFML/Graphics.hpp>

class Personagem {
protected:
    sf::RectangleShape _corpo;
    sf::Vector2f _velocidade;
    
public:
    Personagem (const sf::Vector2f posicao, const sf::Vector2f tamanho);
    ~Personagem ();
    const sf::RectangleShape get_corpo();
    virtual void movimentar() = 0;
};

#endif  