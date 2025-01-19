#ifndef MORECEGO_H
#define MORCEGO_H

#include "inimigo.h"

#define TAMANHO_MORCEGO_X 100.0f
#define TAMANHO_MORCEGO_Y 100.0f
#define TEMPO_MOVIMENTACAO_MORCEGO 4.5f

#define TEMPO_MORTE_MORCEGO 1.0f
#define XP_MORCEGO 50.0f


class Morcego : public Inimigo {
private:
    bool _podeAtacar;
    float _tempoAnimacao;

    void moverInimigo () override;
    void atualizarMovimentacao () override;
    void inicializarAnimacao ();
    virtual void atualizarAnimacao () override;
    void inicializarNivel ();

public: 
    // construtor
    Morcego (sf::Vector2f posicao, Jogador* jogador);
    // detrutor
    ~Morcego ();

    virtual void colisao (Entidade* entidade, sf::Vector2f distancia) override;

    //void atualizar () override;






};

#endif