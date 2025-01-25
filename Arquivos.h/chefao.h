#ifndef CHEFAO_H
#define CHEFAO_H


#define TAMANHO_CHEFAO_X 70.0f
#define TAMANHO_CHEFAO_Y 126.0f
#define TAMANHO_CAJADO_CHEFAO 70.0f

#define TEMPO_ATAQUE_CHEFAO 1.2f
#define TEMPO_MORTE_CHEFAO 1.4f

#define XP_CHEFAO 150.0f

#define FORCA_CHEFAO 35.0f
#define DEFESA_CHEFAO 35.0f

#include "inimigo.h"

class Chefao : public Inimigo {
private:
    bool modoRaiva;
    
    virtual void inicializarAnimacao ();
    virtual void inicializarNivel ();
    virtual void atualizarAnimacao () override;

public:
    // construtor
    Chefao (sf::Vector2f posicao, Jogador* jogador);
    // destrutor
    ~Chefao ();
    // metodos da classe
    virtual void tomarDano(float dano) override;
    // talvez fazer uma funcao para empurrar o jogador ao colidir com ele 
};

#endif