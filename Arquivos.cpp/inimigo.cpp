#include "inimigo.h"

void Inimigo::atualizar() {

    moverInimigo ();
    atualizarPosicao ();
    atualizarAnimacao();
    desenhar ();

}
void Inimigo::moverInimigo () 
{
    if (!levandoDano && !morrendo && !atacando){
    sf::Vector2f posicaoJogador = _jogador->get_corpo().getPosition();             // pega a posicao do corpo do jogador
    sf::Vector2f posicaoInimigo = _corpo.getPosition();                            // pega a posicao do corpo do inimigo
    
    if (fabs(posicaoJogador.x - posicaoInimigo.x) <= RAIO_DE_COMBATE_X && fabs(posicaoJogador.y - posicaoInimigo.y) <= RAIO_DE_COMBATE_Y) {  // se estiver dentro do raio
        parar();
    }
    else 
        atualizarMovimentacao();
    }

    //atualizarPosicao ();
}

void Inimigo::colisao(Entidade *entidade, sf::Vector2f distancia)
{
}

void Inimigo::atualizarPosicao()
{
    if (andando) {
        if (andaEsquerda)
            _corpo.move(-VELOCIDADE_DO_INIMIGO_EIXO_X, 0.0f);
        else 
            _corpo.move(VELOCIDADE_DO_INIMIGO_EIXO_X, 0.0f);
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

// funcao que inicializa a velocidade do inimigo
void Inimigo::inicializarVelocidade() {
    _velocidade = sf::Vector2f (VELOCIDADE_DO_INIMIGO_EIXO_X,VELOCIDADE_DO_INIMIGO_EIXO_Y);
}

// destrutor
Inimigo::~Inimigo() {

}

// construtor
Inimigo::Inimigo (sf::Vector2f posicao, sf::Vector2f tamanho, sf::Vector2f velocidade, Jogador *jogador, Identificador id) :
    Personagem (posicao,tamanho,velocidade, Identificador::inimigo) , _relogio() , _jogador(jogador)
{
    _corpo.setFillColor (sf::Color::Blue);  // inicializa a cor do inimigo com azul
    inicializarVelocidade();
   // srand(time(NULL));                     // garante que os numeros seram diferentes a cada execucao do programa, pois usa o tempo atual como gerador
   // movimentoAleatorio = rand()%2;         // gera 1 numero aleatoriamente entre 0 e 2 (direita ou esquerda)
}

void Inimigo::tomarDano(float dano)
{
}

// metodo que atualiza o movimento de um lado para o outro dos inimigos quando nao estao no raio de combate 
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
