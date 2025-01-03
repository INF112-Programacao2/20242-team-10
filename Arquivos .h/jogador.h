#ifndef JOGADOR_H
#define JOGADOR_H
#include "personagem.h"

class Jogador : public Personagem {
private:
    bool podeAndar;
    bool andarDireita;
public:
    Jogador (const sf::Vector2f posicao, const sf::Vector2f tamanho);
    ~Jogador();
    void andar(const bool direita);
    void parar();
    void inicializarVelocidade ();
    virtual void movimentar();           // esquerda ou direita
    void atualizarPosicao();
};


#endif