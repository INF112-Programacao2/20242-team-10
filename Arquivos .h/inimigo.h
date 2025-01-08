#ifndef INIMIGO_H
#define INIMIGO_H
#include "personagem.h"
#include "jogador.h"
#include <cmath>           // funcao do modulo fabs

#define VELOCIDADE_DO_INIMIGO_EIXO_X 0.025f
#define VELOCIDADE_DO_INIMIGO_EIXO_Y 0.025f

#define RAIO_DE_PERSEGUICAO_X 200.0f
#define RAIO_DE_PERSEGUICAO_Y 200.0f

class Inimigo: public Personagem {
private:
    Jogador *_jogador;
    sf::Clock _relogio;
    int movimentoAleatorio;
    void inicializarVelocidade();

public: 
    Inimigo (const sf::Vector2f posicao, const sf::Vector2f tamanho, sf::Vector2f velocidade, Jogador* jogador, Identificador id);
    ~Inimigo();
    void perseguirJogador (sf::Vector2f posicaoJogador, sf::Vector2f posicaoInimigo);
    void movimentarAleatoriamente ();
    virtual void atualizar();
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia);
};


#endif