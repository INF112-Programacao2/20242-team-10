#ifndef ALMA_H
#define ALMA_H

#include "inimigo.h"

#define TEMPO_MORTE_ALMA 1.5f
#define TEMPO_ATAQUE_ALMA 0.5f
#define TEMPO_INVISIVEL_ALMA 4.0f
#define TEMPO_RECUPERACAO_DANO_ALMA 1.0f

#define TAMANHO_ALMA_X 50.0f
#define TAMANHO_ALMA_Y 90.0f

#define EXPERIENCIA_ALMA 100.0f

#define RAIO_DE_COMBATE_ALMA_X 350.0f
#define FORCA_ALMA 25.0f
#define DEFESA_ALMA 20.0f

class Alma : public Inimigo {
private:
    bool invisivel;
    float _tempoInvisivel;

    virtual void moverInimigo () override;
    void inicializarAnimacao ();
    virtual void atualizarAnimacao () override;
    void inicializarNivel ();
    virtual void atualizarTempoAtaque () override;

public:
    // construtor
    Alma (sf::Vector2f posicao, Jogador* jogador);

    // destrutor
    ~Alma ();

    // getters e setters
    bool estaInvisivel ();
    
    // metodos da classe
    virtual void tomarDano (float dano) override;
    virtual void atualizar () override;


};




#endif 