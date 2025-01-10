#ifndef ESQUELETO_H
#define ESQUELETO_H 

#include "inimigo.h"

#define TAMANHO_ESQUELETO_X 50.0f
#define TAMANHO_ESQUELETO_Y 90.0f

class Esqueleto : public Inimigo {
private:
    virtual void inicializarAnimacao ();
    virtual void atualizarAnimacao ();

public:
    // construtor
    Esqueleto(sf::Vector2f posicao, Jogador* jogador);
    // destrutor
    ~Esqueleto ();
    
};


#endif
