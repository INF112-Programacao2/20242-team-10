#include "inimigo.h"

void Inimigo::movimentar() {
    sf::Vector2f posicaoJogador = _jogador->get_corpo().getPosition();             // pega a posicao do corpo do jogador
    sf::Vector2f posicaoInimigo = _corpo.getPosition();             // pega a posicao do corpo do inimigo
    
    if (fabs(posicaoJogador.x - posicaoInimigo.x) <= RAIO_DE_PERSEGUICAO_X && fabs(posicaoJogador.y - posicaoInimigo.y) <= RAIO_DE_PERSEGUICAO_Y) {  // se estiver dentro do raio
        perseguirJogador(posicaoJogador,posicaoInimigo);
    }
    else 
        movimentarAleatoriamente();

}


// funcao que faz o inimigo perseguir o jogador principal
void Inimigo::perseguirJogador (sf::Vector2f posicaoJogador, sf::Vector2f posicaoInimigo) {
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
}

// funcao que inicializa a velocidade do inimigo
void Inimigo::inicializarVelocidade() {
    _velocidade = sf::Vector2f (VELOCIDADE_DO_INIMIGO_EIXO_X,VELOCIDADE_DO_INIMIGO_EIXO_Y);
}

// destrutor
Inimigo::~Inimigo() {

}

// construtor
Inimigo::Inimigo (const sf::Vector2f posicao, const sf::Vector2f tamanho, Jogador *jogador) :
    Personagem (posicao,tamanho) , _relogio() , _jogador(jogador)
{
    _corpo.setFillColor (sf::Color::Blue);  // inicializa a cor do inimigo com azul
    inicializarVelocidade();
    srand(time(NULL));                     // garante que os numeros seram diferentes a cada execucao do programa, pois usa o tempo atual como gerador
    movimentoAleatorio = rand()%4;         // gera 1 numero aleatoriamente entre 0 e 3
}


void Inimigo::movimentarAleatoriamente () {
    float tempo = _relogio.getElapsedTime().asSeconds();              // pega o tempo em segundos

    if (movimentoAleatorio == 0) {                // se o movimento for 0 indica que deve se mover para esquerda
        _corpo.move(-_velocidade.x,0.0f);
    }
    else if (movimentoAleatorio == 1) {           // se o movimento for 1 indica que deve se mover para direita
        _corpo.move(_velocidade.x,0.0f);
    }
    else if (movimentoAleatorio == 2) {           // se o movimento for 2 indica que deve se mover para cima
        _corpo.move(0.0f,-_velocidade.y);
    }
    else                                          // se o movimento for 3 indica que deve se mover para baixo
        _corpo.move(0.0f,_velocidade.y);   

    // movimentar para outra direcao apos a posicao inicializada no construtor
    if (tempo >= 1.0f) {                                                            // se tiver passado 1 segundo
        movimentoAleatorio = rand()%4;                                              // gera um novo movimento aleatorio
        _relogio.restart();                                                         // reinicia o relogio
    }
}
