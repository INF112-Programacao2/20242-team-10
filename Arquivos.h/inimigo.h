#ifndef INIMIGO_H
#define INIMIGO_H
#include "personagem.h"
#include "jogador.h"
#include <cmath>           // funcao do modulo fabs

#define VELOCIDADE_DO_INIMIGO_EIXO_X 0.025f
#define VELOCIDADE_DO_INIMIGO_EIXO_Y 0.0f

#define RAIO_DE_COMBATE_X 250.0f
#define RAIO_DE_COMBATE_Y 250.0f

#define TEMPO_MOVIMENTACAO_ALEATORIA 1.0f

#define TEMPO_RECUPERACAO_DANO 0.5f

class Inimigo: public Personagem {
private:
    Jogador *_jogador;
    sf::Clock _relogio;
    unsigned int movimentoAleatorio;

    float _tempoProtecaoAtaque;         // tempo que o inimigo fica protegido de outro ataque (evita que chame a funcao tomardano varias vezes em apenas um ataque )
    bool _protegido;                    // sinaliza se ele esta protegido de levar um ataque 

    float _duracaoAnimacaoAtaque;
    float _tempoAtaque;
    float XP;
    //virtual void inicializarAnimacao () = 0;
    //void inicializarBarraVida ();
    void moverInimigo ();
    //void inicializarVelocidade();
    void atualizarMovimentacao (); 
    virtual void inicializarAnimacao() = 0;
    void atualizarBarraVida ();
    void inicializarBarraVida ();
    virtual void atualizarTempoAtaque ();
    virtual void atualizarAnimacao ();
    virtual void inicializarNivel () = 0;

public: 
    // construtor
    Inimigo ( sf::Vector2f posicao,  sf::Vector2f tamanho, Jogador* jogador, Identificador id , float tempoMorte , float tempoAtaque , float experiencia);
    // destrutor
    ~Inimigo();
    // gettters e setters
    float get_experiencia ();
    //void perseguirJogador (sf::Vector2f posicaoJogador, sf::Vector2f posicaoInimigo);
    virtual void tomarDano (float dano);
    //void movimentarAleatoriamente ();
    virtual void atualizar();
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia);
    virtual void atualizarPosicao () override;
};


#endif