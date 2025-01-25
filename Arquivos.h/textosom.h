#ifndef TEXTOSOM_H
#define TEXTOSOM_H
#include "texto.h"

class TextoSom {
private:
    Texto* _texto;
    sf::Clock _relogio;
    float _duracao;
    bool _visivel;
    
public:
    TextoSom(sf::Font& fonte);
    ~TextoSom();
    
    void mostrarSom(const std::string& som, sf::Vector2f posicao);
    void atualizar();
    void desenhar(sf::RenderWindow& janela);
};

#endif