#include "inimigo.h"
#include "plataforma.h"
#include "jogador.h"
#include "arma.h"
#include <iostream>

// funcao que atualiza todos os metodos da classe
void Inimigo::atualizar() 
{
    if (!inativo){
        atualizarTempoAtaque();         

        moverInimigo();
        atualizarPosicao();
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
        andaEsquerda = (posicaoJogador.x < posicaoInimigo.x);              // inimigo fica olhando para o lado que o personagem esta 
        parar();
    }
    else 
        atualizarMovimentacao();
    }
}

// funcao que verifica as colisoes dos inimigos com outras entidades
void Inimigo::colisao(Entidade *entidade, sf::Vector2f distancia)
{
    if (inativo) return;                                                          // verifica se nao esta inativo
    
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
            // Se não estiver já atacando, morrendo ou levando dano
            if (!atacando && !morrendo && !levandoDano) {
                atacar(true);
                // Se tiver arma, atualiza a posição dela
                if (_arma) {
                    _arma->atualizar();
                } 
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

// funcao que desenha as coisas do inimigo na tela
void Inimigo::desenhar()
{ 
    // Desenha enquanto não puder remover
    if (!inativo) {
        gGrafico->desenhar(_corpo);
        
        // Só desenha a barra de vida se não estiver morrendo
        if (!morrendo) {
            gGrafico->desenhar(_barraVida);
            gGrafico->desenhar(_textoNivel.get_texto());
        }

    }
    
}


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

// funcao que retorna se o inimigo esta inativo ou nao
bool Inimigo::estaInativo() const
{
    return inativo;
}

// construtor
Inimigo::Inimigo (sf::Vector2f posicao, sf::Vector2f tamanho, Jogador *jogador, Identificador id, float tempoMorte , float tempoAtaque , float experiencia) :
    Personagem (posicao,tamanho,sf::Vector2f(VELOCIDADE_DO_INIMIGO_EIXO_X, VELOCIDADE_DO_INIMIGO_EIXO_Y), id, tempoMorte , 0.6f),
    _relogio(),
    _jogador(jogador),
    _duracaoAnimacaoAtaque (tempoAtaque),
    XP (experiencia), 
    inativo (false),
    podeAtacarJogador(true) 
{
    // seta a duracao da animacao de morte
    set_duracaoAnimacaoMorte (DURACAO_ANIMACAO_MORTE);

    inicializarBarraVida ();
}

// funcao que atualiza quando o inimigo tomar dano
void Inimigo::tomarDano(float dano)
{
    if (inativo) return;                                                // verifica se nao esta morto

    if (!levandoDano && !_protegido) {
        // atualiza os estados
        _protegido = true;
        levandoDano = true;
        andando = false;
        atacando = false;
        _vida -= dano; 
        // se o inimigo morreu
        if (_vida <= 0.0f) {
            // atualiza os estados de morte
            morrendo = true;
            atacando = false;
            _vida = 0.0f;
        }
        _tempoDano = 0.0f;
        _tempoProtecaoAtaque = 0.0f;
    }
}

// funcao que sinaliza o ataque do inimigo
void Inimigo::atacar(bool atacar)
{
    if (atacar && !atacando && !morrendo && !levandoDano) {
        atacando = true;
        _tempoAtaque = 0.0f;
        
        // atualiza a arma para atacar
        if (_arma) {
            _arma->set_dano(_experiencia.get_forca());
            _arma->atualizar();
        }
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

// funcao que atualiza a barra de vida do inimigo
void Inimigo::atualizarBarraVida()
{
    sf::Vector2f posicaoAtual = _corpo.getPosition();                               // pega a posicao do corpo do inimigo
    sf::Vector2f posicaoBarraVida (posicaoAtual.x,posicaoAtual.y - 20.0f);          // atualiza a posicao da barra, sempre acima do personagem, de acordo com sua posicao 
    _barraVida.setPosition(posicaoBarraVida);                                                                                               // atualiza a posicao
    _barraVida.setSize(sf::Vector2f ((_vida/100.0f)*TAMANHO_BARRA_VIDA_EIXO_X, TAMANHO_BARRA_VIDA_EIXO_Y ));                                // atualiza o tamanho da barra de vida de acordo com a vida
}

// funcao que inicializa a barra de vida do inimigo
void Inimigo::inicializarBarraVida()
{
    _barraVida.setSize(sf::Vector2f(TAMANHO_BARRA_VIDA_EIXO_X,TAMANHO_BARRA_VIDA_EIXO_Y));          // seta o tamanho da barra de vida

    // cria e carrega a textura da barra
    sf::Texture* textura = new sf::Texture ();
    textura->loadFromFile("Vidainimigo.png");

    // seta a textura
    _barraVida.setTexture(textura);
}

// funcao que atualiza os tempos de animacao do ataque do inimigo
void Inimigo::atualizarTempoAtaque()
{
    if (atacando && !levandoDano) {
        _tempoAtaque += gGrafico->get_tempo();
        if (_tempoAtaque > _duracaoAnimacaoAtaque) {
            atacando = false;
            podeAtacarJogador = true;
            _tempoAtaque = 0.0f;
        }
    }
        
        else if (levandoDano) {
            _tempoAtaque = 0.0f;
            atacando = false;
            podeAtacarJogador = true;
            }
}


// funcao que atualiza a animacao dos inimigos, semelhantes as anteriores no codigo, atualiza a animacao dos estados do inimigo, correndo, atacando, andando...
void Inimigo::atualizarAnimacao()
{
    if (morrendo) {
        if (!andaEsquerda)
        _animacao.atualizar(DIREITA,"MORTE");
         else
        _animacao.atualizar(ESQUERDA, "MORTE");

        _tempoMorte += gGrafico->get_tempo();
        if (_tempoMorte >= _duracaoAnimacaoMorte && !inativo ){
            _jogador->adicionarXP(XP);
            inativo = true;          
            _corpo.setFillColor (sf::Color::Transparent);                   // desaparece com o corpo
        }
        return;
    }
        
    
    else if (levandoDano) {
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"TOMARDANO");
        else 
        _animacao.atualizar (ESQUERDA,"TOMARDANO"); 

        _tempoDano += gGrafico->get_tempo();
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
