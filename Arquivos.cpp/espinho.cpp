#include "espinho.h"
#include "jogador.h"


// funcao que inicializa tudo relacionado a animacao do espinho no jogo
void Espinho::inicializarAnimacao()
{
    _textura = gGrafico->carregarTextura (TEXTURA_ESPINHO);
    _corpo.setTexture (&_textura);
}

// construtor
Espinho::Espinho(sf::Vector2f posicao, sf::Vector2f tamanho) :
    Obstaculo (posicao, tamanho, Identificador::espinho) , _dano(DANO_ESPINHO)
{
    inicializarAnimacao();
    //_corpo.setFillColor (sf::Color::Blue);   debug

}

// destrutor
Espinho::~Espinho()
{
}

// funcao que atualiza o dano do espinho
void Espinho::set_dano(float dano)
{
    _dano = dano;
}

// funcao que retorna o dano do espinho
float Espinho::get_dano() const
{
    return _dano;
}

// funcao que verifica as colisoes do espinho com outras entidades
void Espinho::colisao(Entidade *entidade, sf::Vector2f distancia)
{
    if (entidade->get_id () == Identificador::jogador) {
        Jogador* jogador = dynamic_cast <Jogador*> (entidade);
        jogador->tomarDano (_dano);
    }
}
