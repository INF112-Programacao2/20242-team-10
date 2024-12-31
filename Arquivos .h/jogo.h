#ifndef JOGO_H
#define JOGO_h
#include <SFML/Graphics.hpp>
#include "jogador.h"
#include "personagem.h"
#include "inimigo.h"


class Jogo {
private:
    sf::RenderWindow _janela;
    std::vector < Personagem* > _personagens;

public:
    Jogo();
    ~Jogo();
    void executarJanela();
};

#endif