#include "gerenciadoreventos.h"
#include <iostream>

GerenciadorEvento* GerenciadorEvento::_gEvento = nullptr;

GerenciadorEvento::GerenciadorEvento(GerenciadorGrafico* gGrafico, Jogador* jogador):
    _gGrafico(gGrafico) , _jogador(jogador) {}  


GerenciadorEvento::~GerenciadorEvento()
{   
    _gGrafico = nullptr;
}

GerenciadorEvento *GerenciadorEvento::get_gEvento(GerenciadorGrafico* gGrafico)
{
    if (_gEvento == nullptr)
        _gEvento = new GerenciadorEvento(gGrafico,nullptr);

    return _gEvento;
}

void GerenciadorEvento::verificarTeclaPressionada(sf::Keyboard::Key tecla)
{
    if( tecla == sf::Keyboard::A || tecla == sf::Keyboard::Left){
        _jogador->andar(true);
    }
    else if ( tecla == sf::Keyboard::D || tecla == sf::Keyboard::Right){
        _jogador->andar(false);
    }
    else if ( (tecla == sf::Keyboard::Space || tecla == sf::Keyboard::W) ){
        _jogador->pular ();
    }
    else if ( tecla == sf::Keyboard::Escape){
        _gGrafico->fecharJanela();
    }
    else if ( tecla == sf::Keyboard::E) {
        if (_jogador->estaColidindoPorta ()){
            _jogador->set_abrirPorta(true);
        }
    }

}

void GerenciadorEvento::verificarTeclaSolta(sf::Keyboard::Key tecla)
{  
    if ( tecla == sf::Keyboard::A || tecla == sf::Keyboard::D || tecla == sf::Keyboard::Left || tecla == sf::Keyboard::Right ){
    _jogador->parar();
    }
    else if (tecla == sf::Keyboard::E) {
        _jogador->set_abrirPorta(true);
    }
}

void GerenciadorEvento::verificarClickMouse(sf::Event::MouseButtonEvent botaoMouse)
{
    if (botaoMouse.button == sf::Mouse::Left && !_jogador->estaAtacando())
        _jogador->atacar(true);
}

/*void GerenciadorEvento::verificarClickSolto(sf::Event::MouseButtonEvent botaoSolto)
{
    if (botaoSolto.button == sf::Mouse::Left)
        _jogador->atacar(false);
}*/

void GerenciadorEvento::set_jogador(Jogador *jogador)
{
    this->_jogador = jogador;
}

void GerenciadorEvento::executarLoopEvento() {
    sf::Event evento;
    while(_gGrafico->get_janela()->pollEvent(evento)){
        if (evento.type == sf::Event::KeyPressed){
            verificarTeclaPressionada(evento.key.code);
        }
        else if (evento.type == sf::Event::KeyReleased){
            verificarTeclaSolta(evento.key.code);
        }
        else if (evento.type == sf::Event::MouseButtonPressed){
            verificarClickMouse (evento.mouseButton);
        }
        /*else if (evento.type == sf::Event::MouseButtonReleased){
            verificarClickSolto (evento.mouseButton);
        }*/
        else if (evento.type == sf::Event::Closed) {
            _gGrafico->fecharJanela();
        }
    }
}
