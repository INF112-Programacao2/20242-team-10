#include "gerenciadorgrafico.h"
#include <iostream>

// inicializa o gerenciador grafico statico com nulo
GerenciadorGrafico* GerenciadorGrafico::_grafico = nullptr;
// inicializa o tempo em 0
float GerenciadorGrafico::_tempo = 0.0f;

// construtor
GerenciadorGrafico::GerenciadorGrafico() : 
    _janela(new sf::RenderWindow(sf::VideoMode(TAMANHO_TELA_X,TAMANHO_TELA_Y), "Corredor")) , _relogio(), _camera (sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y))
    {
        if (_janela == nullptr)
            throw std::runtime_error ("Nao foi possivel criar a janela grafica");

        _janela->setVerticalSyncEnabled (true);                     // ativa a sincronizacao vertical para melhorar a perfomance
        _janela->setFramerateLimit(0);                                                                  // limita o framerate a 60 fps
    }

// destrutor
GerenciadorGrafico::~GerenciadorGrafico () {
    if (_janela->isOpen())                                  // se a janela esta aberta
        _janela->close();                                   // fecha a janela

    delete (get_janela());                                   // da o delete
    _janela = nullptr;                                       // coloca nulo
}


// funcao que retorna o gerenciador grafico
GerenciadorGrafico* GerenciadorGrafico::get_grafico() {
    if (_grafico == nullptr)                        // se o gerenciador grafico ainda nao foi criado
        _grafico = new GerenciadorGrafico();        // cria o gerenciador grafico

return _grafico;                                    // se ja foi criado, simplesmente o retorna 
}

// funcao que retorna a janela criada
sf::RenderWindow* GerenciadorGrafico::get_janela() {
    return this->_janela;
}

// funcao que limpa a janela
void GerenciadorGrafico::limparJanela() {
    _janela->clear(sf::Color(100,100,100)); // temporario
}

// funcao que desenha os elementos
void GerenciadorGrafico::desenhar (sf::RectangleShape desenho) {
    _janela->draw(desenho);
}

// funcao que desenha os textos na tela
void GerenciadorGrafico::desenhar(sf::Text texto)
{
    _janela->draw (texto);
}

// funcao que mostra o desenho na tela
void GerenciadorGrafico::mostrarNaTela() {
    _janela->display();
}

// funcao que verifica se a janela esta aberta 
const bool GerenciadorGrafico::janelaEstaAberta() {
    return _janela->isOpen();
}

// funcao que reinicia o relogio do gerenciador
void GerenciadorGrafico::resetarRelogio()
{
    _tempo = _relogio.getElapsedTime().asSeconds();
    _relogio.restart();
}

// funcao que atualiza a camera, vinda da classe camera 
void GerenciadorGrafico::atualizaCamera(sf::Vector2f posicaoJogador)
{
    _camera.atualizar (posicaoJogador);
    _janela->setView (_camera.get_camera());                // atualiza a janela de visualizacao com a camera atualizada
}

// funcao que retorna o tempo do relogio
float GerenciadorGrafico::get_tempo() const
{
    return _tempo;
}

// funcao que retorna a camera
sf::View GerenciadorGrafico::get_camera()
{
    return _camera.get_camera();
}

// funcao que retorna os limites da camera ou dos mapas/fases
void GerenciadorGrafico::set_limiteCamera(sf::IntRect limiteCamera)
{
    _camera.set_limiteCamera(limiteCamera);
}


// funcao que fecha a janela
void GerenciadorGrafico::fecharJanela() {
    _janela->close();
}

// funcao que carrega as texturas do programa 
 sf::Texture& GerenciadorGrafico::carregarTextura(const char* caminho)
{
  std::string _caminho(caminho);
    
    // Se a textura já existe, retorna uma referência para ela
    if (_texturas.find(_caminho) != _texturas.end()) {
        return _texturas[_caminho];
    }

    // Carrega a nova textura
    if (!_texturas[_caminho].loadFromFile(caminho)) {
        throw std::runtime_error("Erro ao carregar textura: " + std::string(caminho));
    }

    // Deixa mais fluida a textura
    _texturas[_caminho].setSmooth(true);
    
    return _texturas[_caminho];                  // retorna a textura
}

// funcao que carrega as fontes de textos do jogo
sf::Font GerenciadorGrafico::carregarFonte(const char *caminhoFonte)
{
    sf::Font fonte;
    if (!fonte.loadFromFile (caminhoFonte)){
        throw std::invalid_argument ("Nao foi possivel carregar a fonte! ");
    }
    return fonte;
}
