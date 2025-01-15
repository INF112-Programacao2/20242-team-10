#include "esqueleto.h"

void Esqueleto::inicializarAnimacao()
{
  sf::Vector2f origem (_tamanho.x / 12.0f , _tamanho.y / 10.0f);
  _animacao.adicionarAnimacao("EsqueletoParado.png" , "PARADO", 11 , 0.12f, sf::Vector2f(1.0f,1.0f), origem, true);
  _animacao.adicionarAnimacao("EsqueletoCorrendo.png" , "CORRER", 13 , 0.15f, sf::Vector2f(1.0f,1.0f), origem, true);
  _animacao.adicionarAnimacao("EsqueletoAtacando.png" , "ATACAR", 18 , 0.10f, sf::Vector2f(1.0f,1.0f), origem, true);
  _animacao.adicionarAnimacao("EsqueletoTomandoDano.png" , "TOMARDANO", 8 , 0.15f, sf::Vector2f(1.0f,1.0f), origem, true);
  _animacao.adicionarAnimacao("EsqueletoMorrendo.png" , "MORTE", 15 , 0.10f, sf::Vector2f(1.0f,1.0f), origem, true);
}


void Esqueleto::inicializarNivel()
{
    
}

Esqueleto::Esqueleto(sf::Vector2f posicao, Jogador *jogador) : 
Inimigo(posicao, sf::Vector2f(TAMANHO_ESQUELETO_X, TAMANHO_ESQUELETO_Y),
jogador, Identificador::esqueleto,TEMPO_MORTE_ESQUELETO,2.0f,XP_ESQUELETO) 
  {
    _experiencia.set_nivel(2);
    inicializarAnimacao();
    inicializarNivel();
  }

Esqueleto::~Esqueleto()
{
}
