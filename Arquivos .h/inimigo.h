#ifndef INIMIGO_H
#define INIMIGO_H
#include "personagem.h"
#include "jogador.h"
#include <cmath>           // funcao do modulo fabs

#define VELOCIDADE_DO_INIMIGO_EIXO_X 0.025f
#define VELOCIDADE_DO_INIMIGO_EIXO_Y 0.0f

#define RAIO_DE_COMBATE_X 400.0f
#define RAIO_DE_COMBATE_Y 400.0f

#define TEMPO_MOVIMENTACAO_ALEATORIA 1.0f

class Inimigo: public Personagem {
private:
    Jogador *_jogador;
    sf::Clock _relogio;
    unsigned int movimentoAleatorio;
    //virtual void inicializarAnimacao () = 0;
    //void inicializarBarraVida ();
    void moverInimigo ();
    void inicializarVelocidade();
    void atualizarMovimentoAleatorio (); 

public: 
    Inimigo ( sf::Vector2f posicao,  sf::Vector2f tamanho, sf::Vector2f velocidade, Jogador* jogador, Identificador id);
    ~Inimigo();
    //void perseguirJogador (sf::Vector2f posicaoJogador, sf::Vector2f posicaoInimigo);
    virtual void tomarDano (float dano);
    //void movimentarAleatoriamente ();
    virtual void atualizar();
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia);
    virtual void atualizarPosicao () override;
};


#endif