#ifndef ARMA_H
#define ARMA_H

#include "entidade.h"
#include "personagem.h"

#define TAMANHO_ARMA 25.0f

class Arma : public Entidade {
private:
    float _dano;
    Personagem* _personagem;

public:
    // construtor
    Arma (Identificador id);
    // destrutor
    ~Arma();
    // getters e setters
    void set_personagem (Personagem* personagem);
    void set_dano (float dano);
    float get_dano ();
    void set_tamanho (sf::Vector2f tamanho);
    // metodos da classe
    void colisao (Entidade* entidade, sf::Vector2f distancia);
    void atualizar () ;
    virtual void desenhar () override;




};


#endif