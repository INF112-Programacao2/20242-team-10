#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "obstaculo.h"
#include "jogador.h"

#define TEXTURA_CHAO_DE_MADEIRA "Chao de madeira.png"

class Plataforma : public Obstaculo {
private:
    std::string _tipo;
    sf::Vector2f _escala;
    void inicializarAnimacao();
public:
    // construtor
    Plataforma (sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo, Identificador id);
    // destrutor
    ~Plataforma ();
    // metodos da classe
    void set_escala(sf::Vector2f escala);
    virtual void colisao (Entidade* entidade, sf::Vector2f distancia);
};

#endif