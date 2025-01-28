#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "entidade.h"
#include "personagem.h"
#include <cmath>

class Obstaculo : public Entidade {
protected:
    sf::Texture _textura;
    virtual void inicializarAnimacao () = 0;

public:
    // construtor
    Obstaculo (sf::Vector2f posicao , sf::Vector2f tamanho, Identificador id);
    
    // destrutor
    ~Obstaculo ();

    // metodos da classe
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia) = 0;
    virtual void atualizar ();
    virtual void colisaoObstaculo (sf::Vector2f distancia, Personagem* personagem);

};



#endif