#ifndef PROJETIL_H
#define PROJETIL_H

#include "arma.h"

#define TAMANHO_PROJETIL 50.0f

class Projetil : public Arma {
private:
    bool paraEsquerda;
    sf::Vector2f _velocidade;
    Animacao _animacao;
    bool colidiu;

    void atualizarAnimacao ();
    void atualizarPosicao ();
    void verificaSaiuTela ();

public:
    Projetil (Personagem* personagem);
    ~Projetil ();

    void inicializarAnimacao ();
    void set_sentido (bool paraEsquerda);
    void set_velocidade (sf::Vector2f velocidade);
    void set_colidiu (bool colidiu);
    bool ocorreuColisao ();

    void desenhar ();
    void atualizar ();




};



#endif