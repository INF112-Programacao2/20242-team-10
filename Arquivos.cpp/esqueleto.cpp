#include "esqueleto.h"
#include "arma.h"
#include <iostream>

void Esqueleto::inicializarAnimacao()
{      

    sf::Vector2f origem(0.0f , 0.0f);
    try {
        // Adiciona as animações
        _animacao.adicionarAnimacao("EsqueletoParado.png", "PARADO", 11, 0.12f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoCorrendo.png", "CORRER", 13, 0.15f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoAtacando.png", "ATACAR", 18, 0.10f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoTomandoDano.png", "TOMARDANO", 8, 0.15f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoMorrendo.png", "MORTE", 15, 0.10f, sf::Vector2f(1.0f, 1.0f), origem, true);   
    } catch (const std::exception& e) {
        std::cout << "Erro na inicialização da animação: " << e.what() << std::endl;
        throw;
    }
}


void Esqueleto::inicializarNivel()
{
    _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));
    _textoNivel.set_tamanhoBorda(2);
}

Esqueleto::Esqueleto(sf::Vector2f posicao, Jogador *jogador) : 
    Inimigo(posicao, sf::Vector2f(TAMANHO_ESQUELETO_X, TAMANHO_ESQUELETO_Y),
    jogador, Identificador::esqueleto, TEMPO_MORTE_ESQUELETO, 2.0f, XP_ESQUELETO) 
{
    
    _experiencia.set_nivel(1);
    inicializarAnimacao();
    inicializarNivel ();
    
    // Cria a arma do esqueleto
    Arma* espadaEsqueleto = new Arma(Identificador::espada_esqueleto);
    if (espadaEsqueleto) {
        espadaEsqueleto->set_tamanho(sf::Vector2f(TAMANHO_ARMA, TAMANHO_ARMA));
        set_arma(espadaEsqueleto);
        if (_arma) {
            _arma->set_personagem(this);
            _arma->set_dano(_experiencia.get_forca() * 0.5f);
        }
    }
    
}

Esqueleto::~Esqueleto()
{

}


