#include "textosom.h"


TextoSom::TextoSom(sf::Font& fonte) : _duracao(0.5f), _visivel(false) {
    _texto = new Texto(fonte, "", 24);
    _texto->set_corTexto(sf::Color::Yellow);
    _texto->set_tamanhoBorda(2.0f);
}

TextoSom::~TextoSom() {
    delete _texto;
}

void TextoSom::mostrarSom(const std::string& som, sf::Vector2f posicao) {
    _texto->set_informacao(som);
    _texto->set_posicao(sf::Vector2f(posicao.x, posicao.y - 50.0f)); // Aparece acima do inimigo
    _visivel = true;
    _relogio.restart();
}

void TextoSom::atualizar() {
    if (_visivel && _relogio.getElapsedTime().asSeconds() >= _duracao) {
        _visivel = false;
    }
}

void TextoSom::desenhar(sf::RenderWindow& janela) {
    if (_visivel) {
        _texto->get_texto().setRotation(_relogio.getElapsedTime().asSeconds() * 90.0f); // Efeito de rotação
        janela.draw(_texto->get_texto());
    }
}