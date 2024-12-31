#ifndef JOGADOR_H
#define JOGADOR_H
#include "personagem.h"

class Jogador : public Personagem {
public:
    Jogador (const sf::Vector2f posicao, const sf::Vector2f tamanho);
    ~Jogador();
    void inicializarVelocidade ();
    virtual void movimentar();
};


#endif