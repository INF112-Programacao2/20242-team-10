#include "camada.h"

Camada::Camada(sf::Texture textura, sf::Vector2f tamanhoTextura, sf::Vector2f origem) :
     _textura (textura)  , gGrafico(gGrafico->get_grafico()) , _tamanhoTextura(tamanhoTextura) , _origem (origem)
{  
    _camada.setSize(_tamanhoTextura);
    _camada.setTexture (&_textura);
    _camada.setPosition (origem);

}

Camada::~Camada()
{
}

/*sf::Vector2f Camada::get_tamanhoJanela()
{
    return this->_tamanhoJanela;
}*/

void Camada::desenharCamada()
{
    gGrafico->desenhar (_camada);
}

/*void Camada::atualizar(sf::Vector2f distancia)
{
}
*/