#include "plataforma.h"

void Plataforma::inicializarAnimacao()
{
    if ( _tipo == "Chao de madeira"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CHAO_DE_MADEIRA);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Carpete"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CHAO_CARPETE_AZUL);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "CarpeteRocha"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CHAO_CARPETE_AZUL_ROCHA);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "ChaoRocha"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CHAO_PEDRA);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Banco"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_BANCO);
        _corpo.setTexture (&textura);
    }

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
     if (entidade->get_id() == Identificador::jogador ||
        entidade->get_id() == Identificador::esqueleto) {
        Personagem* personagem = dynamic_cast<Personagem*>(entidade);
        if (personagem) {
            colisaoObstaculo(distancia, personagem);
        }
    }
}
