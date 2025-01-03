#include "gerenciadoreventos.h"

GerenciadorEvento* GerenciadorEvento::_gEvento = nullptr;

GerenciadorEvento::GerenciadorEvento(GerenciadorGrafico* gGrafico, Jogador* jogador):
    _gGrafico(gGrafico) , _jogador(jogador) {}

GerenciadorEvento::~GerenciadorEvento()
{   
    _jogador = nullptr;
    _gGrafico = nullptr;
}

GerenciadorEvento *GerenciadorEvento::get_gEvento(GerenciadorGrafico* gGrafico)
{
    if (_gEvento == nullptr)
        _gEvento = new GerenciadorEvento(gGrafico,nullptr);

    return _gEvento;
}

void GerenciadorEvento::set_jogador(Jogador *jogador)
{
    this->_jogador = jogador;
}

void GerenciadorEvento::verificarTeclaPressionada(sf::Keyboard::Key tecla)
{
    if( tecla == sf::Keyboard::A || tecla == sf::Keyboard::Left){
        _jogador->andar(false);
    }
    else if ( tecla == sf::Keyboard::D || tecla == sf::Keyboard::Right){
        _jogador->andar(true);
    }
    else if ( tecla == sf::Keyboard::Escape){
        _gGrafico->fecharJanela();
    }

}

void GerenciadorEvento::verificarTeclaSolta(sf::Keyboard::Key tecla)
{
    if ( tecla == sf::Keyboard::A || tecla == sf::Keyboard::D || tecla == sf::Keyboard::Left || tecla == sf::Keyboard::Right ){
        _jogador->parar();
    }
}

void GerenciadorEvento::executar() {
    sf::Event evento;
    while(_gGrafico->get_janela()->pollEvent(evento)){
        if (evento.type == sf::Event::KeyPressed){
            verificarTeclaPressionada(evento.key.code);
        }
        else if (evento.type == sf::Event::KeyReleased){
            verificarTeclaSolta(evento.key.code);
        }
        else if (evento.type == sf::Event::Closed) {
            _gGrafico->fecharJanela();
        }
    }
}
