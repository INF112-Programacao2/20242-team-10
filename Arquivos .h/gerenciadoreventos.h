#ifndef GERENCIADOREVENTOS_H
#define GERENCIADOREVENTOS_H
// gerencia todos os eventos externos, como entradas do teclado, clicks do mouse...

#include "gerenciadorgrafico.h"
#include "jogador.h"

class GerenciadorEvento {
private:
    GerenciadorGrafico* _gGrafico;
    Jogador* _jogador;
    // construtor privado para garantir que exista apenas um gerenciador de eventos em todo o programa
    static GerenciadorEvento* _gEvento;
    GerenciadorEvento(GerenciadorGrafico* gGrafico, Jogador* jogador);
public:
    ~GerenciadorEvento ();
    static GerenciadorEvento* get_gEvento(GerenciadorGrafico* gGrafico = nullptr);
    void set_jogador(Jogador* jogador);
    void verificarTeclaPressionada(sf::Keyboard::Key tecla);
    void verificarTeclaSolta(sf::Keyboard::Key tecla);
    void executar();
};



#endif