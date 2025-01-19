#ifndef INIMIGO_H
#define INIMIGO_H
#include "personagem.h"
#include "jogador.h"
#include "listaentidade.h"
#include <cmath>           // funcao do modulo fabs

#define VELOCIDADE_DO_INIMIGO_EIXO_X 0.025f
#define VELOCIDADE_DO_INIMIGO_EIXO_Y 0.0f

#define RAIO_DE_COMBATE_X 250.0f
#define RAIO_DE_COMBATE_Y 250.0f

#define TEMPO_MOVIMENTACAO_ALEATORIA 1.0f

#define DURACAO_ANIMACAO_MORTE 1.5f


class Inimigo: public Personagem {
protected:
    bool inativo;
    float _tempoAtaque;
    sf::Clock _relogio;
    Jogador *_jogador;
    float _duracaoAnimacaoAtaque;
private:
    //ListaEntidade* _lista;
    //Jogador *_jogador;
    //sf::Clock _relogio;
    unsigned int movimentoAleatorio;

    bool podeAtacarJogador;


    //float _duracaoAnimacaoAtaque;
    //float _tempoAtaque;
    float XP;
    //virtual void inicializarAnimacao () = 0;
    //void inicializarBarraVida ();
    virtual void moverInimigo ();
    //void inicializarVelocidade();
    virtual void atualizarMovimentacao (); 
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
    //void set_lista (ListaEntidade* lista);
    bool estaInativo () const;
    //void perseguirJogador (sf::Vector2f posicaoJogador, sf::Vector2f posicaoInimigo);
    virtual void tomarDano (float dano);
    void atacar (bool atacar) override;
    virtual void atualizar();
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia);
    virtual void atualizarPosicao () override;
    virtual void desenhar () override;
};


#endif