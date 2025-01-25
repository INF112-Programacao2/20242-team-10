#ifndef GERENCIADOREVENTOS_H
#define GERENCIADOREVENTOS_H
// gerencia todos os eventos externos, como entradas do teclado, clicks do mouse...

#include "gerenciadorgrafico.h"
#include "mensagemBox.h"
#include "menu.h"

class Fase;
class Jogador;

class GerenciadorEvento {
protected:
    GerenciadorGrafico* _gGrafico;
    Jogador* _jogador;
    MensagemBox* _mensagem;
    static GerenciadorEvento* _gEvento;

    Fase* _fase;

    Menu* _menu;         
    bool _jogoIniciado;    
    sf::Sprite _background; 
    sf::Texture _textura;  

public:
    GerenciadorEvento(GerenciadorGrafico* gGrafico, Jogador* jogador);
    ~GerenciadorEvento ();
    static GerenciadorEvento* get_gEvento(GerenciadorGrafico* gGrafico = nullptr);
    void verificarTeclaPressionada(sf::Keyboard::Key tecla);
    void verificarTeclaSolta(sf::Keyboard::Key tecla);
    void verificarClickMouse (sf::Event::MouseButtonEvent botaoMouse);
    //void verificarClickSolto (sf::Event::MouseButtonEvent botaoSolto);
    void set_mensagem (MensagemBox* mensagem);
    void set_jogador(Jogador* jogador);
    void set_fase (Fase* fase);
    void executarLoopEvento();

    // Novos métodos para o menu
    void set_menu(Menu* menu); 
    Menu* get_menu() const;
    void set_jogoIniciado(bool iniciado) ;
    bool get_jogoIniciado() const; 
    
    // Métodos para o background
    void set_background(const std::string& caminho);
    void desenhar_background();
};



#endif