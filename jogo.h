#ifndef JOGO_H
#define JOGO_h
#include <SFML/Graphics.hpp>
#include "personagem.h"


class Jogo {
private:
    sf::RenderWindow _janela;
    Personagem _personagem;

public:
    Jogo();
    ~Jogo();
    void executarJanela();
};

#endif