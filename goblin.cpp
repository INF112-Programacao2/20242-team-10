#include "goblin.h"
#include "arma.h"

// funcao que inicializa o nivel do goblin
void Goblin::inicializarNivel()
{
    _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));          // inicia o texto o nivel do goblin
    _textoNivel.set_tamanhoBorda(2);                                                        // inicia o tamannho da borda do texto
}

// funcao que inicializa a animacao do golin
void Goblin::inicializarAnimacao()
{   
    sf::Vector2f escala (4.0f, 4.0f);                                                           // seta a escala do goblin
    sf::Vector2f origem (_tamanho.x * escala.x/11.5f, _tamanho.y * escala.y/9.5f);              // seta a origem do goblin

    // inicializa as animacoes
    _animacao.adicionarAnimacao("GoblinParado.png", "PARADO", 4, 0.15f, escala, origem, true);
    _animacao.adicionarAnimacao("GoblinCorrendo.png", "CORRER", 8, 0.15f, escala, origem, true);
    _animacao.adicionarAnimacao("GoblinAtacando.png", "ATACAR", 8, 0.08f, escala, origem, true);
    _animacao.adicionarAnimacao("GoblinTomarDano.png", "TOMARDANO", 8, 0.15f, escala, origem, true);
    _animacao.adicionarAnimacao("GoblinMorrendo.png", "MORTE", 4, 0.15f, escala, origem, true);
}

// construtor
Goblin::Goblin(sf::Vector2f posicao, Jogador *jogador) :
    Inimigo (posicao, sf::Vector2f (TAMANHO_GOBLIN_X,TAMANHO_GOBLIN_Y), jogador, Identificador::goblin , TEMPO_MORTE_GOBLIN, 1.0f , XP_GOBLIN)
{
    // seta o nivel do goblin
    _experiencia.set_nivel (3);

    inicializarAnimacao ();
    inicializarNivel();

    // cria a arma do goblin
    Arma* facaGoblin = new Arma (Identificador::faca_goblin);
    if (facaGoblin) {
        facaGoblin->set_tamanho (sf::Vector2f (TAMANHO_ARMA,TAMANHO_ARMA));
        set_arma (facaGoblin);
        if (_arma) {
            _arma->set_personagem(this);
            _arma->set_dano (_experiencia.get_forca () * 0.5f);
        }
    }
}

// destrutor
Goblin::~Goblin()
{
}
