#include "morcego.h"
#include "arma.h"
#include "plataforma.h"
#include "jogador.h"

void Morcego::moverInimigo()
{
    if  (!morrendo && !atacando){
    atualizarMovimentacao ();
    }

    sf::Vector2f posicaoMorcego = _corpo.getPosition ();
    if (posicaoMorcego.x < 0.0f) {
        posicaoMorcego.x = 0.0f;
        andaEsquerda = false;
    }
}

void Morcego::atualizarMovimentacao()
{
    float tempo = _relogio.getElapsedTime().asSeconds();

    if ( tempo >= TEMPO_MOVIMENTACAO_MORCEGO){
        unsigned int direcaoAleatoria = std::rand() % 2;
        andaEsquerda = (direcaoAleatoria == 0);

        _relogio.restart();

        andando = true;

    }
}

void Morcego::inicializarAnimacao()
{
        sf::Vector2f escala (3.5f,3.5f);                                                                    // define a escala do sprite
        sf::Vector2f origem (_tamanho.x * escala.x/10.0f , _tamanho.y * escala.y/8.0f);                     // define a origem do sprite seguindo a conta: 
      
        _animacao.adicionarAnimacao("MorcegoVoando.png", "CORRER", 8, 0.12f, escala, origem, true);
        _animacao.adicionarAnimacao("MorcegoAtaque.png", "ATACAR", 8, 0.10f, escala, origem, true);
        _animacao.adicionarAnimacao("MorcegoTomarDano.png", "TOMARDANO", 4, 0.12f, escala, origem, true);
        _animacao.adicionarAnimacao("MorcegoMorte.png", "MORTE", 4, 0.15f, escala, origem, true);
}

void Morcego::atualizarAnimacao()
{
     if (morrendo) {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA, "MORTE");
        else
            _animacao.atualizar(ESQUERDA, "MORTE");

        _tempoMorte += gGrafico->get_tempo();
        if (_tempoMorte >= _duracaoAnimacaoMorte) {
            inativo = true;
            _corpo.setPosition(-1000.0f, -1000.0f);
        }
    }
    else if (levandoDano) {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA, "TOMARDANO");
        else
            _animacao.atualizar(ESQUERDA, "TOMARDANO");

        _tempoDano += gGrafico->get_tempo();
        if (_tempoDano >= TEMPO_RECUPERACAO_DANO) {
            levandoDano = false;
            _tempoDano = 0.0f;
        }
    }
    else if (atacando) {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA, "ATACAR");
        else
            _animacao.atualizar(ESQUERDA, "ATACAR");

        _tempoAtaque += gGrafico->get_tempo();
        if (_tempoAtaque >= _duracaoAnimacaoAtaque) {
            atacando = false;
            _tempoAtaque = 0.0f;
            _podeAtacar = true;
        }
    }
    else {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA, "CORRER");
        else
            _animacao.atualizar(ESQUERDA, "CORRER");
    }
}

void Morcego::inicializarNivel()
{
     _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));
    _textoNivel.set_tamanhoBorda(2);
}

Morcego::Morcego(sf::Vector2f posicao, Jogador* jogador) :
    Inimigo (posicao, sf::Vector2f(TAMANHO_MORCEGO_X, TAMANHO_MORCEGO_Y) , jogador , Identificador::morcego, TEMPO_MORTE_MORCEGO, 1.0f , XP_MORCEGO) ,
    _podeAtacar (true) , _tempoAnimacao (0.0f) 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    inicializarNivel ();
    inicializarAnimacao ();
    atacando = false;
    _tempoAtaque = 0.0f;


    _experiencia.set_nivel (1);

    andaEsquerda = (std::rand() % 2 == 0);
    andando = true;
}

Morcego::~Morcego()
{
}

void Morcego::colisao(Entidade *entidade, sf::Vector2f distancia)
{
        if (inativo) return;
    
    switch (entidade->get_id()) {
        case (Identificador::plataforma): {
            Plataforma* plataforma = dynamic_cast<Plataforma*>(entidade);
            if (plataforma) {
                plataforma->colisaoObstaculo(distancia, this);
            }
            break;
        }
        case (Identificador::espada_jogador): {
            Arma* arma = dynamic_cast<Arma*>(entidade);
            if (arma && !levandoDano && !morrendo && _jogador->estaAtacando()) {
                tomarDano(arma->get_dano());
                //std::cout << "Vida do morcego após dano: " << _vida << std::endl;
            }
            break;
        }
        case (Identificador::jogador): {
            if (!atacando && !morrendo && !levandoDano) {
                atacar(true);
            }
            break;
        }
    }
}

/*void Morcego::atualizar()
{
    moverInimigo ();
    atualizarMovimentacao ();
}*/
