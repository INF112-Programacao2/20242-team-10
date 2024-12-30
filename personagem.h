#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include <SFML/Graphics.hpp>

class Personagem {
private:
    sf::RectangleShape _corpo;
    sf::Vector2f _velocidade;
    void inicializaVelocidade();

public:
    Personagem (const sf::Vector2f posicao, const sf::Vector2f tamanho);
    Personagem (const sf::RectangleShape corpo);
    Personagem ();
    ~Personagem ();
    const sf::RectangleShape get_corpo();
    virtual void movimentar() = 0;
};

#endif  