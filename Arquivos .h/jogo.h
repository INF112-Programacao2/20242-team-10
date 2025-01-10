#ifndef JOGO_H
#define JOGO_h
#include <SFML/Graphics.hpp>
#include "jogador.h"
#include "personagem.h"
#include "inimigo.h"
#include "gerenciadorgrafico.h"
#include "gerenciadoreventos.h"
#include "fundo.h"
#include "esqueleto.h"


class Jogo {
private:
    GerenciadorGrafico* gGrafico;
    GerenciadorEvento* gEvento;
    std::vector < Personagem* > _personagens;
    Fundo* _fundo;

public:
    Jogo();
    ~Jogo();
    void executarJanela();
};

#endif