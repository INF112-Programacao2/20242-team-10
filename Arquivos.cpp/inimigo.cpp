#include "inimigo.h"
#include "plataforma.h"
#include "jogador.h"
#include "arma.h"
#include <iostream>

// funcao que atualiza todos os metodos da classe
void Inimigo::atualizar() 
{
        moverInimigo();
        atualizarPosicao();
        atualizarTempoAtaque();
        atualizarAnimacao();
        atualizarBarraVida ();
        atualizarNivel();

    // reset do tempo de protecao de ataque e da variavel booleana protegido 
    if (_protegido){
        _tempoProtecaoAtaque += gGrafico->get_tempo();
        if (_tempoProtecaoAtaque >= TEMPO_RECUPERACAO_DANO) {
            _protegido = false;
            _tempoProtecaoAtaque = 0.0f;
        }
    }
}

// funcao responsavel pela movimentacao do inimigo
void Inimigo::moverInimigo () 
{
    // se nao houver jogador, entao acaba a movimentacao
    if (!_jogador) return;
    // se o inimigo nao tiver sofrendo ataque nem morrendo e nem atacando
    if (!levandoDano && !morrendo && !atacando){
    sf::Vector2f posicaoJogador = _jogador->get_corpo().getPosition();             // pega a posicao do corpo do jogador
    sf::Vector2f posicaoInimigo = _corpo.getPosition();                            // pega a posicao do corpo do inimigo
    
    // verifica se o jogador entrou no raio de combate, se entrar o inimigo fica parado, senao atualiza sua movimentacao (anda de um lado para o outro)
    if (fabs(posicaoJogador.x - posicaoInimigo.x) <= RAIO_DE_COMBATE_X && fabs(posicaoJogador.y - posicaoInimigo.y) <= RAIO_DE_COMBATE_Y) {  // se estiver dentro do raio
        parar();
    }
    else 
        atualizarMovimentacao();
    }
}

// funcao que verifica as colisoes dos inimigos com outras entidades
void Inimigo::colisao(Entidade *entidade, sf::Vector2f distancia)
{
      switch (entidade->get_id()) {
        case (Identificador::plataforma): {
            Plataforma* plataforma = dynamic_cast<Plataforma*>(entidade);
            if (plataforma) {
                plataforma->colisaoObstaculo(distancia, this);
            }
            break;
        }

        case (Identificador::jogador): {
            // Colisão com o jogador
            /*sf::Vector2f posicaoAtual = get_posicao();
            sf::Vector2f posicaoJogador = entidade->get_posicao();

            // Empurra o inimigo para fora do jogador
            if (fabs(distancia.x) < fabs(distancia.y)) {
                posicaoAtual.x += (posicaoAtual.x < posicaoJogador.x) ? -2.0f : 2.0f;
            } else {
                posicaoAtual.y += (posicaoAtual.y < posicaoJogador.y) ? -2.0f : 2.0f;
            }
            set_posicao(posicaoAtual);*/

            // Inicia ataque quando colide com jogador
            if (!atacando && !morrendo){
                atacar(true);    
            }
            break;
        }
        case (Identificador::espada_jogador) : {
            Arma* arma = dynamic_cast < Arma* > (entidade);
            if (arma && _jogador->estaAtacando()){
            tomarDano (arma->get_dano());
            std::cout << _vida << std::endl;
            }
            break;
        }
    }
}

// funcao que atualiza a posicao do inimigo
void Inimigo::atualizarPosicao()
{
    if (andando) {                                                                  // se estiver andando
        if (andaEsquerda)                                                           // se estiver andando para a esquerda
            _corpo.move(-VELOCIDADE_DO_INIMIGO_EIXO_X, 0.0f);                       // atualiza o inimigo para a esquerda
        else                                                    
            _corpo.move(VELOCIDADE_DO_INIMIGO_EIXO_X, 0.0f);                        // senao, atualiza o inimigo para a direita
    }
}

// funcao que faz o inimigo perseguir o jogador principal
/*void Inimigo::perseguirJogador (sf::Vector2f posicaoJogador, sf::Vector2f posicaoInimigo) {
    if (posicaoJogador.x - posicaoInimigo.x > 0.0f) {            // se a posicao do jogador menos a posicao do inimigo no eixo x for maior que 0 significa que o jogador esta a direita do inimigo
        _corpo.move(_velocidade.x,0.0f);                         // move o inimigo para a direita
    }
    else {                                                       // senao, o jogador esta a esquerda do inimigo
        _corpo.move(-_velocidade.x,0.0f);                        // move o inimigo para a esquerda
    }

    if (posicaoJogador.y - posicaoInimigo.y > 0.0f) {            // se a posicao do jogador menos a posicao do inimigo no eixo y for maior que 0 significa que o o jogador esta acima do inimigo
        _corpo.move(0.0f,_velocidade.y);                         // move o inimigo para cima
    } 
    else {                                                       // senao, o jogador esta abaixo do inimigo
        _corpo.move(0.0f,-_velocidade.y);                        // move o inimigo para baixo
    }
}*/


// destrutor
Inimigo::~Inimigo() 
{
    // deleta as texturas alocadas com ponteiros
    if (_barraVida.getTexture()){
        delete (_barraVida.getTexture());
    }
}

// funcao que retorna a experiencia do inimigo
float Inimigo::get_experiencia()
{
    return XP;
}

// construtor
Inimigo::Inimigo (sf::Vector2f posicao, sf::Vector2f tamanho, Jogador *jogador, Identificador id, float tempoMorte , float tempoAtaque , float experiencia) :
    Personagem (posicao,tamanho,sf::Vector2f(VELOCIDADE_DO_INIMIGO_EIXO_X, VELOCIDADE_DO_INIMIGO_EIXO_Y), Identificador::inimigo, tempoMorte , 0.6f),
    _relogio() , _jogador(jogador) , _duracaoAnimacaoAtaque (tempoAtaque) , XP (experiencia), _tempoAtaque(0.0f) , _tempoProtecaoAtaque(0.0f), _protegido(false)
{
    //_corpo.setFillColor (sf::Color::Blue);  // inicializa a cor do inimigo com azul
    inicializarBarraVida ();
}

// funcao que atualiza quando o inimigo tomar dano
void Inimigo::tomarDano(float dano)
{
    if (!levandoDano && !_protegido) {
        _protegido = true;
        levandoDano = true;
        andando = false;
        _vida -= dano; // apenas para simplificar, * (dano / _experiencia.get_defesa());
        if (_vida <= 0.0f) {
            morrendo = true;
            _vida = 0.0f;
        }
        _tempoDano = 0.0f;
        _tempoProtecaoAtaque = 0.0f;
    }
}
// metodo que atualiza o movimento de um lado para o outro dos inimigos  
void Inimigo::atualizarMovimentacao()
{
    float tempo = _relogio.getElapsedTime().asSeconds();                            // pega o tempo em segundos

    // movimentacao de um lado para o outro 
    if (tempo >= TEMPO_MOVIMENTACAO_ALEATORIA) {                                  // se tiver passado o tempo de movimentacao em segundos
        andaEsquerda = !andaEsquerda;                                             // muda o sentido que esta andando
        _relogio.restart();                                                       // reinicia o relogio
    }

    andar (andaEsquerda);                                                         // anda para o lado atualizado
}

void Inimigo::atualizarBarraVida()
{
    sf::Vector2f posicaoAtual = _corpo.getPosition();
    sf::Vector2f posicaoBarraVida (posicaoAtual.x,posicaoAtual.y - 20.0f);          // atualiza a posicao da barra, sempre acima do personagem, de acordo com sua posicao 
    _barraVida.setPosition(posicaoBarraVida);                                                                                               // atualiza a posicao
    _barraVida.setSize(sf::Vector2f ((_vida/100.0f)*TAMANHO_BARRA_VIDA_EIXO_X, TAMANHO_BARRA_VIDA_EIXO_Y ));                                // atualiza o tamanho da barra de vida de acordo com a vida
}

// funcao que inicializa a barra de vida do inimigo
void Inimigo::inicializarBarraVida()
{
    _barraVida.setSize(sf::Vector2f(TAMANHO_BARRA_VIDA_EIXO_X,TAMANHO_BARRA_VIDA_EIXO_Y));
    sf::Texture* textura = new sf::Texture ();
    textura->loadFromFile("Vidainimigo.png");
    _barraVida.setTexture(textura);
}

// funcao que atualiza os tempos de animacao do ataque do inimigo
void Inimigo::atualizarTempoAtaque()
{
    if (atacando && !levandoDano){
        _tempoAtaque += gGrafico->get_tempo();
        if (_tempoAtaque > _duracaoAnimacaoAtaque) {
            atacando = false;
            _tempoAtaque = 0.0f;
        }
    }
    else if (levandoDano){
        _tempoAtaque = 0.0f;
        atacando = false;
    }
}

void Inimigo::atualizarAnimacao()
{
    if (morrendo) {
        if (!andaEsquerda)
        _animacao.atualizar(DIREITA,"MORTE");
        _tempoMorte += gGrafico->get_tempo();
        if (_tempoMorte > _duracaoAnimacaoMorte){
            // podeRemover
            _tempoMorte = 0.0f;

        }
    }
    else if (levandoDano) {
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"TOMARDANO");
        else 
        _animacao.atualizar (ESQUERDA,"TOMARDANO"); 

        _tempoDano += TEMPO_RECUPERACAO_DANO;
        if (_tempoDano >= TEMPO_RECUPERACAO_DANO) {
            levandoDano = false;
            _tempoDano = 0.0f;
        }
    }
    else if (atacando){
            _tempoAtaque += gGrafico->get_tempo();
        if (_tempoAtaque >= DURACAO_ATAQUE_TOTAL){
            atacando = false;
            _tempoAtaque = 0.0f;
            return;
        }
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"ATACAR");
        else 
        _animacao.atualizar (ESQUERDA,"ATACAR"); 
    }
    else if (andando){
        if (!andaEsquerda)
        _animacao.atualizar(DIREITA,"CORRER");
        else 
        _animacao.atualizar(ESQUERDA,"CORRER");
    }
    else {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA,"PARADO");
        else 
            _animacao.atualizar(ESQUERDA,"PARADO");
    }
}
