#ifndef GOBLIN_H
#define GOBLIN_H

#include "inimigo.h"

#define TAMANHO_GOBLIN_X 50.0f
#define TAMANHO_GOBLIN_Y 90.0f

#define TEMPO_MORTE_GOBLIN 0.6f
#define XP_GOBLIN 30.0f

class Goblin : public Inimigo {
private:

    virtual void inicializarNivel ();
    virtual void inicializarAnimacao ();

public:
    // construtor
    Goblin (sf::Vector2f posicao, Jogador* jogador);
    // destrutor
    ~Goblin();
    

};


#endif