#ifndef JOGADOR_H
#define JOGADOR_H
#include "personagem.h"

#define TAMANHO_PULO -0.5f                             // negativa pois o eixo y é invertido na biblioteca (para subir = valores negativos)
#define VELOCIDADE_JOGADOR 
#define DURACAO_ATAQUE_TOTAL 0.6f                         // sao 6 frames de ataque e o tempo de troca entre eles = 0.1f

class Jogador : public Personagem {
private:
    bool estaNoChao;
    float _tempoAtaque;

    void inicializarAnimacao ();
    void atualizarAnimacao ();
public:
    Jogador (const sf::Vector2f posicao, const sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id);
    ~Jogador();
    void pular ();
    void podePular ();
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia);
    virtual void atacar(bool atacar) override;
    virtual void atualizar() override;                                  // esquerda ou direita
    virtual void atualizarPosicao () override;
};


#endif