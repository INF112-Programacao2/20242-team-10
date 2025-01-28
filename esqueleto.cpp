#include "esqueleto.h"
#include "arma.h"
#include <iostream>

// funcao que inicializa tudo relacionado a animacao do esqueleto
void Esqueleto::inicializarAnimacao()
{      

        sf::Vector2f origem(0.0f , 0.0f);               // seta a origem do esqueleto

        // Adiciona as animações
        _animacao.adicionarAnimacao("EsqueletoParado.png", "PARADO", 11, 0.12f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoCorrendo.png", "CORRER", 13, 0.15f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoAtacando.png", "ATACAR", 18, 0.10f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoTomandoDano.png", "TOMARDANO", 8, 0.15f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoMorrendo.png", "MORTE", 15, 0.10f, sf::Vector2f(1.0f, 1.0f), origem, true);   

}

// funcao que inicializa o nivel do esqueleto
void Esqueleto::inicializarNivel()
{
    _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));              // inicializa o texto do nivel
    _textoNivel.set_tamanhoBorda(2);                                                            // seta o tamanho da borda do texto do nivel
}

// construtor
Esqueleto::Esqueleto(sf::Vector2f posicao, Jogador *jogador) : 
    Inimigo(posicao, sf::Vector2f(TAMANHO_ESQUELETO_X, TAMANHO_ESQUELETO_Y),jogador, Identificador::esqueleto, TEMPO_MORTE_ESQUELETO, 2.0f, XP_ESQUELETO) 
{
    // seta o nivel do esqueleto
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

// destrutor
Esqueleto::~Esqueleto()
{

}


