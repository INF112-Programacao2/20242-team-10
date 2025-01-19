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
    else if ( _tipo == "Teto"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_TETO);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "ParedeLisa"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_PAREDE_LISA);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Contorno1"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CONTORNO_1);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Contorno2"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CONTORNO_2);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Contorno3"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CONTORNO_3);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Contorno4"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CONTORNO_4);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Contorno5"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CONTORNO_5);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Contorno6"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CONTORNO_6);
        _corpo.setTexture (&textura);
    }
    else if ( _tipo == "Contorno7"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CONTORNO_7);
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
