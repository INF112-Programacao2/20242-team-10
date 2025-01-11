#include "plataforma.h"

void Plataforma::inicializarAnimacao()
{
    if ( _tipo == "Chao de madeira"){
        _textura = gGrafico->carregarTextura(TEXTURA_CHAO_DE_MADEIRA);
    }

    _corpo.setTexture (&_textura);
    _corpo.setScale(_escala);

}

Plataforma::Plataforma(sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo, Identificador id) :
    Obstaculo(posicao, tamanho, id) , _tipo(tipo) , _escala (sf::Vector2f(1.0f,1.0f))
{
    inicializarAnimacao ();
}

Plataforma::~Plataforma()
{

}

void Plataforma::set_escala(sf::Vector2f escala)
{
    this->_escala = escala;
    _corpo.setScale (_escala);
}

void Plataforma::colisao(Entidade* entidade, sf::Vector2f distancia)
{
    if (entidade->get_id() == Identificador::jogador){
        colisaoObstaculo (distancia,dynamic_cast < Personagem* > (entidade));
    }
}
