#include "gerenciadorgrafico.h"

// inicializa o gerenciador grafico statico com nulo
GerenciadorGrafico* GerenciadorGrafico::_grafico = nullptr;

// construtor
GerenciadorGrafico::GerenciadorGrafico() : 
    _janela(new sf::RenderWindow(sf::VideoMode(800.0f,600.0f), "Torre"))
    {
        if (_janela == nullptr)
            throw std::runtime_error ("Nao foi possivel criar a janela grafica");
    }

// destrutor
GerenciadorGrafico::~GerenciadorGrafico () {
    if (janelaEstaAberta())                                  // se a janela esta aberta
        delete (get_janela());                               // da o delete
        _janela = nullptr;                                   // coloca nulo
}


// funcao que retorna o gerenciador grafico
GerenciadorGrafico* GerenciadorGrafico::get_grafico() {
    if (_grafico == nullptr)                    // se o gerenciador grafico ainda nao foi criado
        return new GerenciadorGrafico();        // cria o gerenciador grafico

return _grafico;                                // se ja foi criado, simplesmente o retorna 
}

// funcao que retorna a janela criada
sf::RenderWindow* GerenciadorGrafico::get_janela() {
    return this->_janela;
}

// funcao que limpa a janela
void GerenciadorGrafico::limparJanela() {
    _janela->clear();
}

// funcao que desenha os elementos
void GerenciadorGrafico::desenhar (sf::RectangleShape desenho) {
    _janela->draw(desenho);
}

// funcao que mostra o desenho na tela
void GerenciadorGrafico::mostrarNaTela() {
    _janela->display();
}

// funcao que verifica se a janela esta aberta 
const bool GerenciadorGrafico::janelaEstaAberta() {
    return _janela->isOpen();
}

// funcao que fecha a janela
void GerenciadorGrafico::fecharJanela() {
    _janela->close();
}




