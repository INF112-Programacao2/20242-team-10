#ifndef JOGADOR_H
#define JOGADOR_H
#include "personagem.h"

#define TAMANHO_PULO -0.5f                             // negativa pois o eixo y é invertido na biblioteca (para subir = valores negativos)
#define VELOCIDADE_JOGADOR 
#define DURACAO_ATAQUE_TOTAL 0.6f                         // sao 6 frames de ataque e o tempo de troca entre eles = 0.1f
#define TAMANHO_JOGADOR_X 75.0f   
#define TAMANHO_JOGADOR_Y 75.0f
#define VELOCIDADE_JOGADOR_X 0.12f
#define VELOCIDADE_JOGADOR_Y 0.0f

class Jogador : public Personagem {
private:
    bool estaNoChao;
    float _tempoAtaque;

    void inicializarAnimacao ();
    void atualizarAnimacao ();
    void inicializarBarraVida ();
    void atualizarBarraVida ();

public:
    // construtor
    Jogador (sf::Vector2f posicao);
    // destrutor
    ~Jogador();
    // getters e setters
    bool get_estaNoChao ();
    //void set_vida ();
    // metodos da classe
    void pular ();
    void podePular ();
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia);
    virtual void atacar(bool atacar) override;
    virtual void atualizar() override;                                  // esquerda ou direita
    virtual void atualizarPosicao () override;
    void desenhar ();
};


#endif