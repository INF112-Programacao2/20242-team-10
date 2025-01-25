#ifndef ESPINHO_H
#define ESPINHO_H

#include "obstaculo.h"

#define DANO_ESPINHO 15.0f
#define TEXTURA_ESPINHO "Espinho.png"  

class Espinho : public Obstaculo {
private:
    float _dano;

    void inicializarAnimacao ();

public:
    // construtor
    Espinho(sf::Vector2f posicao, sf::Vector2f tamanho);
    // destrutor
    ~Espinho ();
    // getters e setters
    void set_dano (float dano);
    float get_dano () const;
    // metodos da classe
    void colisao (Entidade* entidade , sf::Vector2f distancia);



};


#endif