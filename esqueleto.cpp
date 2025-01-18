#include "esqueleto.h"
#include "arma.h"
#include <iostream>

void Esqueleto::inicializarAnimacao()
{        std::cout << "Inicializando animação do esqueleto..." << std::endl;
    
    _corpo.setFillColor(sf::Color::White);  // Garante que é visível
    
    sf::Vector2f origem(_tamanho.x / 12.0f, _tamanho.y / 10.0f);
    try {
        // Verifica e carrega as texturas
        const char* arquivos[] = {
            "EsqueletoParado.png",
            "EsqueletoCorrendo.png",
            "EsqueletoAtacando.png",
            "EsqueletoTomandoDano.png",
            "EsqueletoMorrendo.png"
        };

        for (const char* arquivo : arquivos) {
            sf::Texture& tex = gGrafico->carregarTextura(arquivo);
            std::cout << "Textura carregada: " << arquivo << std::endl;
        }

        // Adiciona as animações
        _animacao.adicionarAnimacao("EsqueletoParado.png", "PARADO", 11, 0.12f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoCorrendo.png", "CORRER", 13, 0.15f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoAtacando.png", "ATACAR", 18, 0.10f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoTomandoDano.png", "TOMARDANO", 8, 0.15f, sf::Vector2f(1.0f, 1.0f), origem, true);
        _animacao.adicionarAnimacao("EsqueletoMorrendo.png", "MORTE", 15, 0.10f, sf::Vector2f(1.0f, 1.0f), origem, true);

        // Inicia com a animação parada
        _animacao.atualizar(DIREITA, "PARADO");
        
    } catch (const std::exception& e) {
        std::cout << "Erro na inicialização da animação: " << e.what() << std::endl;
        throw;
    }
}


void Esqueleto::inicializarNivel()
{
    
}

Esqueleto::Esqueleto(sf::Vector2f posicao, Jogador *jogador) : 
    Inimigo(posicao, sf::Vector2f(TAMANHO_ESQUELETO_X, TAMANHO_ESQUELETO_Y),
    jogador, Identificador::esqueleto, TEMPO_MORTE_ESQUELETO, 2.0f, XP_ESQUELETO) 
{
    std::cout << "Construindo esqueleto na posição: " << posicao.x << ", " << posicao.y << std::endl;
    
    // Garante que o esqueleto é visível
    _corpo.setFillColor(sf::Color::White);
    
    inicializarAnimacao();
    
    atacando = false;
    _tempoAtaque = 0.0f;
    
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
    
    _experiencia.set_nivel(2);
}

Esqueleto::~Esqueleto()
{

}

// apenas para testes
void Esqueleto::desenhar()
{
    
    // Verifica se a textura está carregada
    if (_corpo.getTexture() == nullptr) {
        std::cout << "AVISO: Esqueleto sem textura!" << std::endl;
    }
    
    // Verifica se o esqueleto está visível
    if (_corpo.getFillColor().a == 0) {
        std::cout << "AVISO: Esqueleto transparente!" << std::endl;
    }
    
    // Desenha o corpo
    gGrafico->desenhar(_corpo);
    
    // Se tiver arma, desenha ela também
    if (_arma) {
        _arma->desenhar();
    }
    
    // Se o esqueleto não estiver morto, desenha a barra de vida
    if (!morrendo) {
        gGrafico->desenhar(_barraVida);
    }

}
