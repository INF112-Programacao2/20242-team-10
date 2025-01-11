#include "esqueleto.h"

void Esqueleto::inicializarAnimacao()
{
}

void Esqueleto::atualizarAnimacao()
{
}

Esqueleto::Esqueleto(sf::Vector2f posicao, Jogador *jogador) : Inimigo(posicao, sf::Vector2f(TAMANHO_ESQUELETO_X, TAMANHO_ESQUELETO_Y), sf::Vector2f(VELOCIDADE_DO_INIMIGO_EIXO_X, VELOCIDADE_DO_INIMIGO_EIXO_Y), jogador, Identificador::esqueleto)
{
}

Esqueleto::~Esqueleto()
{
}
