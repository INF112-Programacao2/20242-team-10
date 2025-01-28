#include "morcego.h"
#include "arma.h"
#include "plataforma.h"
#include "jogador.h"

// funcao responsavel pela movimentacao do morcego 
void Morcego::moverInimigo()
{
    if  (!morrendo && !atacando){
    atualizarMovimentacao ();                                   // chama o metodo de atualizar posicao se nao estiver morrendo nem atacando
    }

    sf::Vector2f posicaoMorcego = _corpo.getPosition ();                                    // limite o mapa para nao sair da janela
    if (posicaoMorcego.x < 0.0f) {
        posicaoMorcego.x = 0.0f;
        andaEsquerda = false;
    }
}

// funcao que atualiza a movimentacao do morcego
void Morcego::atualizarMovimentacao()
{
    float tempo = _relogio.getElapsedTime().asSeconds();                                // pega o tempo em segundos

    if ( tempo >= TEMPO_MOVIMENTACAO_MORCEGO){                                          // quando esse tempo exceder o tempo de movimentacao
        unsigned int direcaoAleatoria = std::rand() % 2;                                // se move aleatoriamente para direita ou para a esquerda
        andaEsquerda = (direcaoAleatoria == 0);

        _relogio.restart();                                                             // reinicia o relogio

        andando = true;                                                                 // atualiza o estado andando

    }
}

// funcao que inicializa as animacoes do morcego
void Morcego::inicializarAnimacao()
{
        sf::Vector2f escala (3.5f,3.5f);                                                                    // define a escala do sprite
        sf::Vector2f origem (_tamanho.x * escala.x/10.0f , _tamanho.y * escala.y/8.0f);                     // define a origem do sprite seguindo a conta: origem = tamanho_original * escala / divisor_de_ajuste
      
        // incializa as animacoes
        _animacao.adicionarAnimacao("MorcegoVoando.png", "CORRER", 8, 0.12f, escala, origem, true);
        _animacao.adicionarAnimacao("MorcegoAtaque.png", "ATACAR", 8, 0.10f, escala, origem, true);
        _animacao.adicionarAnimacao("MorcegoTomarDano.png", "TOMARDANO", 4, 0.12f, escala, origem, true);
        _animacao.adicionarAnimacao("MorcegoMorte.png", "MORTE", 4, 0.15f, escala, origem, true);
}

// funcao que atualiza a animacao do morcego de acordo com seu estado, voando, parado, atacando ... assim como nos demais personagens
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

// funcao que inicializa o nivel do morcego
void Morcego::inicializarNivel()
{
     _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));         // seta o nivel na tela
    _textoNivel.set_tamanhoBorda(2);                                                        // seta o tamanho da borda do escrito
}

// construtor
Morcego::Morcego(sf::Vector2f posicao, Jogador* jogador) :
    Inimigo (posicao, sf::Vector2f(TAMANHO_MORCEGO_X, TAMANHO_MORCEGO_Y) , jogador , Identificador::morcego, TEMPO_MORTE_MORCEGO, 1.0f , XP_MORCEGO),
    _podeAtacar (true),
    _tempoAnimacao (0.0f) 
{
    // inicializa a semente para a cada execucao possuir uma diferente
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    inicializarNivel ();
    inicializarAnimacao ();

    // atualiza os estados
    atacando = false;
    _tempoAtaque = 0.0f;

    // seta o nivel do morcego
    _experiencia.set_nivel (1);

    // inicializa andando para alguma direcao (esquerda ou direita)
    andaEsquerda = (std::rand() % 2 == 0);
    andando = true;
}

// destrutor
Morcego::~Morcego()
{
}

// funcao que verifica as colisoes do morcego com outras entidades
void Morcego::colisao(Entidade *entidade, sf::Vector2f distancia)
{
        if (inativo) return;                                // verifica se esta vivo (ou ativo)
    
    // se colidir com a plataforma
    switch (entidade->get_id()) {
        case (Identificador::plataforma): {
            Plataforma* plataforma = dynamic_cast<Plataforma*>(entidade);
            if (plataforma) {
                // chama o metodo de colisao da plataforma
                plataforma->colisaoObstaculo(distancia, this);
            }
            break;
        }
        // se colidir com o jogador
        case (Identificador::jogador): {
            if (!atacando && !morrendo && !levandoDano) {                   // verifica se pode atacar
                // ataca o jogador
                atacar(true);
            }
            break;
        }
    }
}

