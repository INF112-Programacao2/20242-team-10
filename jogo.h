#ifndef JOGO_H
#define JOGO_h
#include <SFML/Graphics.hpp>
#include "jogador.h"
#include "personagem.h"
#include "inimigo.h"
#include "gerenciadorgrafico.h"
#include "gerenciadoreventos.h"
#include "gerenciadormusica.h"
#include "fundo.h"
#include "esqueleto.h"
#include "fase.h"
#include "arma.h"


#define TEMPO_ESPERA_TRANSICAO 5.0f

class Jogo {
private:
    GerenciadorGrafico* gGrafico;
    GerenciadorEvento* gEvento;
    GerenciadorMusica* gMusica;
    Fase* faseAtual;

    Menu* menu;
    bool jogoIniciado;
    bool musicaIniciada;

public:
    Jogo();
    ~Jogo();
    void executarJanela();
    
};

#endif