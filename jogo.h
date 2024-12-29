#ifndef JOGO_H
#define JOGO_h
#include <SFML/Graphics.hpp>


class Jogo {
private:
    sf::RenderWindow janela;

public:
    Jogo();
    ~Jogo();
    void executarJanela();
};

#endif