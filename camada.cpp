#include "camada.h"

// construtor
Camada::Camada(sf::Texture textura, sf::Vector2f tamanhoTextura, sf::Vector2f origem) :
    _textura (textura),
    gGrafico(gGrafico->get_grafico()),
    _tamanhoTextura(tamanhoTextura),
    _origem (origem)
{  
    // atualiza o tamanho, a textura e a posicao da camada
    _camada.setSize(_tamanhoTextura);
    _camada.setTexture (&_textura);
    _camada.setPosition (origem);

}

// destrutor
Camada::~Camada()
{
}

// funcao que desenhar a camada na tela
void Camada::desenharCamada()
{
    gGrafico->desenhar (_camada);
}

