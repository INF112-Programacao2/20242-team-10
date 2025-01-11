#ifndef GERENCIADOREVENTOS_H
#define GERENCIADOREVENTOS_H
// gerencia todos os eventos externos, como entradas do teclado, clicks do mouse...

#include "gerenciadorgrafico.h"
#include "jogador.h"

class GerenciadorEvento {
protected:
    GerenciadorGrafico* _gGrafico;
    Jogador* _jogador;
    static GerenciadorEvento* _gEvento;

public:
    GerenciadorEvento(GerenciadorGrafico* gGrafico, Jogador* jogador);
    ~GerenciadorEvento ();
    static GerenciadorEvento* get_gEvento(GerenciadorGrafico* gGrafico = nullptr);
    void verificarTeclaPressionada(sf::Keyboard::Key tecla);
    void verificarTeclaSolta(sf::Keyboard::Key tecla);
    void verificarClickMouse (sf::Event::MouseButtonEvent botaoMouse);
    //void verificarClickSolto (sf::Event::MouseButtonEvent botaoSolto);
    void set_jogador(Jogador* jogador);
    void executarLoopEvento();
};



#endif