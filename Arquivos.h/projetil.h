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
    // cosntrutor
    Projetil (Personagem* personagem);

    // destrutor
    ~Projetil ();

    // getters e setters
    void set_sentido (bool paraEsquerda);
    void set_velocidade (sf::Vector2f velocidade);
    void set_colidiu (bool colidiu);
    bool ocorreuColisao ();

    // metodos da classe
    void inicializarAnimacao ();
    void desenhar ();
    void atualizar ();




};



#endif