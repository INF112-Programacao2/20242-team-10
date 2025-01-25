#include "gerenciadoreventos.h"
#include "fase.h"
#include "jogador.h"
#include <iostream>

GerenciadorEvento* GerenciadorEvento::_gEvento = nullptr;

GerenciadorEvento::GerenciadorEvento(GerenciadorGrafico* gGrafico, Jogador* jogador):
    _gGrafico(gGrafico) , _jogador(jogador) , _fase (nullptr) , _mensagem (nullptr) {}  


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

        if (!_jogoIniciado && _menu != nullptr) {
        // Controles do menu
        if (tecla == sf::Keyboard::Up) {
            _menu->moverCima();
        }
        else if (tecla == sf::Keyboard::Down) {
            _menu->moverBaixo();
        }
        else if (tecla == sf::Keyboard::Return) {
            // Verifica qual opção está selecionada
            if (_menu->get_Pressionar() == 0) {  // Novo Jogo
                _menu->set_EstaAtivo(false);
                _jogoIniciado = true;
            }
            else if (_menu->get_Pressionar() == 1) {  // Sair
                _gGrafico->fecharJanela();
            }
        }
        return;
    }
    
    if (tecla == sf::Keyboard::R && _jogador && _jogador->estaCongeladoJogo()) {
        if (_fase) {
            _fase->reiniciarFase();
            _jogador = _fase->get_jogador();
            set_jogador (_jogador);
        }
        return;
    }

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
    else if ( tecla == sf::Keyboard::L && _mensagem && _mensagem->estaVisivel()) {
        _mensagem->proximaMensagem();
    }
    else if (tecla == sf::Keyboard::Space && _fase && _fase->get_mensagem()->estaVisivel()) {
        _fase->get_mensagem()->proximaMensagem();
}
    

}

void GerenciadorEvento::verificarTeclaSolta(sf::Keyboard::Key tecla)
{  
    if ( tecla == sf::Keyboard::A || tecla == sf::Keyboard::D || tecla == sf::Keyboard::Left || tecla == sf::Keyboard::Right ){
    _jogador->parar();
    }
}

void GerenciadorEvento::verificarClickMouse(sf::Event::MouseButtonEvent botaoMouse)
{
    if (botaoMouse.button == sf::Mouse::Left && !_jogador->estaAtacando())
        _jogador->atacar(true);
}

void GerenciadorEvento::set_mensagem(MensagemBox *mensagem)
{
    _mensagem = mensagem;
}

void GerenciadorEvento::set_jogador(Jogador *jogador)
{
    this->_jogador = jogador;
}

void GerenciadorEvento::set_fase(Fase *fase)
{
    _fase = fase;
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
        else if (evento.type == sf::Event::Closed) {
            _gGrafico->fecharJanela();
        }
    }
}

void GerenciadorEvento::set_menu(Menu *menu)
{
    _menu = menu;
}

Menu *GerenciadorEvento::get_menu() const
{
    return _menu;
}

void GerenciadorEvento::set_jogoIniciado(bool iniciado)
{
    _jogoIniciado = iniciado;
}

bool GerenciadorEvento::get_jogoIniciado() const
{
    return _jogoIniciado;
}

void GerenciadorEvento::set_background(const std::string& caminho) {
    if (!_textura.loadFromFile(caminho)) {
        throw std::runtime_error("Erro ao carregar textura do background");
    }
    _background.setTexture(_textura);
    
    // Ajusta a escala para preencher a tela
    sf::Vector2u windowSize = _gGrafico->get_janela()->getSize();
    sf::Vector2u textureSize = _textura.getSize();
    
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    _background.setScale(scaleX, scaleY);
}

void GerenciadorEvento::desenhar_background() {
    if (_gGrafico && _gGrafico->get_janela()) {
        _gGrafico->get_janela()->draw(_background);
    }
}