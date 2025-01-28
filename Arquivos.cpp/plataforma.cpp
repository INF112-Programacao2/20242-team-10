#include "plataforma.h"


// funcao que inicializa as plataformas
void Plataforma::inicializarAnimacao()
{

    // verifica o tipo da plataforma a ser criada, e carrega sua textura de acordo com seu nome
    if ( _tipo == "Chao de madeira"){
        sf::Texture& textura = gGrafico->carregarTextura(TEXTURA_CHAO_DE_MADEIRA);                      // carrega a textura
        _corpo.setTexture (&textura);                                                                   // seta a textura
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

    // seta a escala no corpo da plataforma
    _corpo.setScale(_escala);

}

// construtor
Plataforma::Plataforma(sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo, Identificador id) :
    Obstaculo(posicao, tamanho, id),
    _tipo(tipo),
    _escala (sf::Vector2f(1.0f,1.0f))
{
    inicializarAnimacao ();
}

// destrutor
Plataforma::~Plataforma()
{

}

// funcao que atualiza a escala da plataforma
void Plataforma::set_escala(sf::Vector2f escala)
{
    this->_escala = escala;
    _corpo.setScale (_escala);
}

// funcao que verifica as colisoes da plataforma com outras entidades
void Plataforma::colisao(Entidade* entidade, sf::Vector2f distancia)
{
     if (entidade->get_id() == Identificador::jogador ||
        entidade->get_id() == Identificador::esqueleto||
        entidade->get_id () == Identificador::goblin  ||
        entidade->get_id () == Identificador::morcego ||
        entidade->get_id () == Identificador::chefao  ||
        entidade->get_id () == Identificador::alma) {
        Personagem* personagem = dynamic_cast<Personagem*>(entidade);
        if (personagem) {
            colisaoObstaculo(distancia, personagem);
        }
    }
}
