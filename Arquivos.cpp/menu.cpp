#include "Menu.h"

Menu::Menu(sf::RenderWindow* window) : _janela(window), _opcaoSelecionada(0), _estaAtivo(true) {
    if (!_fonte.loadFromFile("FonteNivel.ttf")) {
        throw std::runtime_error("Erro ao carregar fonte");
    }

    // Configuração das opções do menu
    std::vector<std::string> textos = {"Novo Jogo", "Sair"};
    float espacamentoY = 80.0f;
    
    for (size_t i = 0; i < textos.size(); i++) {
        sf::Text texto;
        texto.setFont(_fonte);
        texto.setString(textos[i]);
        texto.setCharacterSize(50);
        texto.setFillColor(sf::Color::White);
        
        // Centraliza o texto
        float posX = (_janela->getSize().x - texto.getLocalBounds().width) / 2.0f;
        float posY = (_janela->getSize().y / 2.0f) + (i * espacamentoY);
        texto.setPosition(posX, posY);
        
        _opcoes.push_back(texto);
    }
    
    // Destaca a primeira opção
    _opcoes[0].setFillColor(sf::Color::Yellow);
}

Menu::~Menu()
{
}

void Menu::moverCima() {
    if (_opcaoSelecionada > 0) {
        _opcoes[_opcaoSelecionada].setFillColor(sf::Color::White);
        _opcaoSelecionada--;
        _opcoes[_opcaoSelecionada].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moverBaixo() {
    if (_opcaoSelecionada < _opcoes.size() - 1) {
        _opcoes[_opcaoSelecionada].setFillColor(sf::Color::White);
        _opcaoSelecionada++;
        _opcoes[_opcaoSelecionada].setFillColor(sf::Color::Yellow);
    }
}

void Menu::desenhar() {
    for (const auto& opcao : _opcoes) {
        _janela->draw(opcao);
    }
}

int Menu::get_Pressionar() const { 
    return _opcaoSelecionada; 
}

bool Menu::get_EstaAtivo() const
{
    return _estaAtivo;
}

void Menu::set_EstaAtivo(bool ativo)
{
    _estaAtivo = ativo;
}
