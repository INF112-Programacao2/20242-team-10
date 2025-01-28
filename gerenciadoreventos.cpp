#include "gerenciadoreventos.h"
#include "fase.h"
#include "jogador.h"
#include <iostream>

// inicializacao do gerenciador estatico
GerenciadorEvento* GerenciadorEvento::_gEvento = nullptr;

// construtor
GerenciadorEvento::GerenciadorEvento(GerenciadorGrafico* gGrafico, Jogador* jogador):
    _gGrafico(gGrafico),
    _jogador(jogador),
    _fase(nullptr),
    gMusica(GerenciadorMusica::get_gerenciadorMusical()),
    _menu(nullptr),
    _jogoIniciado(false)
{

}   


// destrutor
GerenciadorEvento::~GerenciadorEvento()
{   
        if (_gEvento == this) {
        _gEvento = nullptr;
    }
    
    // limpa os ponteiros
    _gGrafico = nullptr;
    gMusica = nullptr;
    _jogador = nullptr;
    _fase = nullptr;
    _menu = nullptr;
}

// funcao que retorna o gerenciador de eventos
GerenciadorEvento *GerenciadorEvento::get_gEvento(GerenciadorGrafico* gGrafico)
{
    if (_gEvento == nullptr) {
        if (gGrafico == nullptr) {
            throw std::runtime_error("GerenciadorGrafico não pode ser nulo na primeira chamada");
        }
        _gEvento = new GerenciadorEvento(gGrafico, nullptr);
    }
    return _gEvento;
}

// funcao que verifica as teclas pressionadas no teclado
void GerenciadorEvento::verificarTeclaPressionada(sf::Keyboard::Key tecla)
{

    // verifica as teclas pressionadas no menu
        if (!_jogoIniciado && _menu != nullptr) {
        // controles do menu
        if (tecla == sf::Keyboard::Up) {
            _menu->moverCima();
        }
        else if (tecla == sf::Keyboard::Down) {
            _menu->moverBaixo();
        }
        else if (tecla == sf::Keyboard::Return) {
            // verifica qual opção está selecionada
            if (_menu->get_Pressionar() == 0) {  // novo Jogo
                _menu->set_EstaAtivo(false);
                _jogoIniciado = true;
            }
            else if (_menu->get_Pressionar() == 1) {  // sair
                _gGrafico->fecharJanela();
            }
        }
        return;
    }
    
    // metodo para reiniciar o jogo
    if (tecla == sf::Keyboard::R && _jogador && _jogador->estaCongeladoJogo()) {
        if (_fase) {
            _fase->reiniciarFase();
            _jogador = _fase->get_jogador();
            set_jogador (_jogador);
        }
        return;
    }
    else if( tecla == sf::Keyboard::A || tecla == sf::Keyboard::Left){
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

}

// funcao que verifica tecla solta
void GerenciadorEvento::verificarTeclaSolta(sf::Keyboard::Key tecla)
{  
    if ( tecla == sf::Keyboard::A || tecla == sf::Keyboard::D || tecla == sf::Keyboard::Left || tecla == sf::Keyboard::Right ){
    _jogador->parar();
    }
}

// funcao que atualiza os eventos que vem do mouse
void GerenciadorEvento::verificarClickMouse(sf::Event::MouseButtonEvent botaoMouse)
{
    if (botaoMouse.button == sf::Mouse::Left && _jogador && !_jogador->estaAtacando()) {
        _jogador->atacar(true);
        if (gMusica) {
            gMusica->tocar(Identificador::som_jogador_espada);
        }
    }
}

// funcao que atualiza o jogador 
void GerenciadorEvento::set_jogador(Jogador *jogador)
{
    this->_jogador = jogador;
}

// funcao que atualiza a fase atual do jogo
void GerenciadorEvento::set_fase(Fase *fase)
{
    _fase = fase;
}

// funcao que executa o loop de eventos do jogo
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

// funcao que atualiza o menu
void GerenciadorEvento::set_menu(Menu *menu)
{
    _menu = menu;
}

// funcao que retorna o menu
Menu *GerenciadorEvento::get_menu() const
{
    return _menu;
}

// funcao que atualiza se o jogo iniciou ou nao
void GerenciadorEvento::set_jogoIniciado(bool iniciado)
{
    _jogoIniciado = iniciado;
}

// booleano que retorna o estado do jogo se iniciou ou nao
bool GerenciadorEvento::get_jogoIniciado() const
{
    return _jogoIniciado;
}

// funcao que seta o background do menu
void GerenciadorEvento::set_background(const std::string& caminho) {
    if (!_textura.loadFromFile(caminho)) {
        throw std::runtime_error("Erro ao carregar textura do background");
    }

    //  seta a textura
    _background.setTexture(_textura);
    
    // ajusta a escala para preencher a tela
    sf::Vector2u windowSize = _gGrafico->get_janela()->getSize();
    sf::Vector2u textureSize = _textura.getSize();
    
    float escalaX = static_cast<float>(windowSize.x) / textureSize.x;
    float escalaY = static_cast<float>(windowSize.y) / textureSize.y;

    // seta a escala
    _background.setScale(escalaX, escalaY);
}

// funcao que desenha o background do menu
void GerenciadorEvento::desenhar_background() {
    if (_gGrafico && _gGrafico->get_janela()) {
        _gGrafico->get_janela()->draw(_background);
    }
}