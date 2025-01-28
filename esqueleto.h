#ifndef ESQUELETO_H
#define ESQUELETO_H 

#include "inimigo.h"

#define  TEMPO_ENTRE_ATAQUES_ESQUELETO 1.8f

#define TAMANHO_ESQUELETO_X 50.0f
#define TAMANHO_ESQUELETO_Y 90.0f

#define TEMPO_MORTE_ESQUELETO 1.5f
#define XP_ESQUELETO 10.0f

class Esqueleto : public Inimigo {
private:
    void inicializarAnimacao ();
    void inicializarNivel ();

public:
    // construtor
    Esqueleto(sf::Vector2f posicao, Jogador* jogador);\

    // destrutor
    ~Esqueleto ();


    
};


#endif
