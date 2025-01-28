#ifndef GERENCIADOREVENTOS_H
#define GERENCIADOREVENTOS_H
// gerencia todos os eventos externos, como entradas do teclado, clicks do mouse...

#include "gerenciadorgrafico.h"
#include "gerenciadormusica.h"
#include "menu.h"

class Fase;
class Jogador;

class GerenciadorEvento {
protected:
    GerenciadorGrafico* _gGrafico;
    GerenciadorMusica* gMusica;
    Jogador* _jogador;

    static GerenciadorEvento* _gEvento;

    Fase* _fase;

    Menu* _menu;         
    bool _jogoIniciado;    
    sf::Sprite _background; 
    sf::Texture _textura;  

public:
    // construtor
    GerenciadorEvento(GerenciadorGrafico* gGrafico, Jogador* jogador);

    // destutor
    ~GerenciadorEvento ();
    
    static GerenciadorEvento* get_gEvento(GerenciadorGrafico* gGrafico = nullptr);
    void verificarTeclaPressionada(sf::Keyboard::Key tecla);
    void verificarTeclaSolta(sf::Keyboard::Key tecla);
    void verificarClickMouse (sf::Event::MouseButtonEvent botaoMouse);

    void set_jogador(Jogador* jogador);
    void set_fase (Fase* fase);
    void executarLoopEvento();

    // metodos para o menu
    void set_menu(Menu* menu); 
    Menu* get_menu() const;
    void set_jogoIniciado(bool iniciado) ;
    bool get_jogoIniciado() const; 
    
    // metodos para o background
    void set_background(const std::string& caminho);
    void desenhar_background();
};



#endif