#include "jogador.h"
#include <iostream>

void Jogador::inicializarAnimacao()
{
    sf::Vector2f origem = sf::Vector2f (_tamanho.x / 2.0f, _tamanho.y / 2.0f);
    //sf::Vector2f origemPulo = sf::Vector2f (_tamanho.x / 2.0f, _tamanho.y * 0.75f);

    _animacao.adicionarAnimacao("C:/Users/Caio/Desktop/Projeto Final INF112/Correndo.png", "CORRER", 10 , 0.05f , sf::Vector2f(6,2),origem,true);
    _animacao.adicionarAnimacao("C:/Users/Caio/Desktop/Projeto Final INF112/Parado.png", "PARADO", 10 , 0.10f , sf::Vector2f(6,2),origem,true);
    _animacao.adicionarAnimacao("C:/Users/Caio/Desktop/Projeto Final INF112/Pulando.png", "PULAR", 3 , 0.10f , sf::Vector2f(6,2),origem,true);
    _animacao.adicionarAnimacao("C:/Users/Caio/Desktop/Projeto Final INF112/Atacando.png", "ATACAR", 6 , 0.10f , sf::Vector2f(6,2),origem,true);
    
}

void Jogador::atualizarAnimacao()
{


    if (andando && estaNoChao && !atacando) {
    //try{
        if (!andaEsquerda)
        _animacao.atualizar(DIREITA,"CORRER");
        else 
        _animacao.atualizar(ESQUERDA,"CORRER");
    }
    else if (!andando && estaNoChao && !atacando) {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA,"PARADO");
        else 
            _animacao.atualizar(ESQUERDA,"PARADO");
    }
    else if (!estaNoChao && !atacando){
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"PULAR");
        else 
        _animacao.atualizar (ESQUERDA,"PULAR"); 
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
    
    //catch (const std::exception& e) {
    //    std::cout << "ERRO na animacao: " << e.what() << std::endl;*/
 
}

// construtor que usa o construtor de Personagem
Jogador::Jogador (const sf::Vector2f posicao, const sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id) :
    Personagem (posicao,tamanho,velocidade, Identificador::jogador) , estaNoChao (true) , _tempoAtaque(0.0f)
    {
        inicializarAnimacao();
    }
    
// destrutor
Jogador::~Jogador () {

}

void Jogador::pular()
{
    // verifica se pode pular 
    if (estaNoChao) {
        _velocidade.y = TAMANHO_PULO;
        estaNoChao = false;
        atacando = false;
    }

    // verifica se o corpo esta no chao
    if (_corpo.getPosition().y == NIVEL_DA_PLATAFORMA)    // esta no chao 
        estaNoChao = true;
}

void Jogador::podePular()
{ 
    estaNoChao = true;
}

void Jogador::colisao(Entidade *entidade, sf::Vector2f distancia)
{
}

void Jogador::atacar(bool atacar)
{
    if (atacar){
        this->atacando = true;
        this->_tempoAtaque = 0.0f;
    }
}

// funcao que movimenta o jogador para as quatro direcoes
void Jogador::atualizar () {
        atualizarPosicao();
        atualizarAnimacao();

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {          // se a tecla pressionada for A ou seta para esquerda, move para esquerda
        _corpo.move(-_velocidade.x,0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){     // se a tecla pressionada for D ou seta para direita, move para direita
        _corpo.move(+_velocidade.x,0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){        // se a tecla pressionada for W ou seta para cima, move para cima
        _corpo.move(0.0f,-_velocidade.y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){      // se a tecla pressionada for S ou seta para baixo, move para baixo
        _corpo.move(0.0f,+_velocidade.y);
    }*/
}

void Jogador::atualizarPosicao()
{
    // Movimento horizontal
    if (andando) {
        if (andaEsquerda)
            _corpo.move(-_velocidade.x, 0.0f);
        else 
            _corpo.move(_velocidade.x, 0.0f);
    }
    
    // Movimento vertical (pulo)
    _velocidade.y += GRAVIDADE;
    _corpo.move(0.0f, _velocidade.y);

    // Colisão com o chão
    if (_corpo.getPosition().y >= NIVEL_DA_PLATAFORMA) {
        _corpo.setPosition(_corpo.getPosition().x, NIVEL_DA_PLATAFORMA);
        _velocidade.y = 0;
        estaNoChao = true;
    }
}


/*void Jogador::atualizarPosicao()
{
    // movimentacao com base no movimento uniforme
    deltaTempo = gGrafico->get_tempo ();                   // variacao do tempo
    sf::Vector2f deltaDistancia (0.0f,0.0f);               // variacao da distancia

    // movimentacao no eixo horizontal
    if (andando && !morrendo){                                  // se estiver andando e nao estiver morrendo
        deltaDistancia.x = _velocidade.x * deltaTempo;          // se move para a direita no eixo x
        if (andaEsquerda)                                       // se estiver andando para esquerda
            deltaDistancia.x *= -1;                             // apenas multiplica por -1 para inverter o sentido e andar para a esquerda
    }

    // movimentacao na vertical, baseada no movimento uniformemente variado vertical
    float velocidadeInicial = _velocidade.y;
    _velocidade.y += (GRAVIDADE * deltaTempo);
    deltaDistancia.y = (velocidadeInicial * deltaTempo) + (_velocidade.y * deltaTempo * deltaTempo) / 2.0f;
    /*if (andando && !morrendo){
        if (andaEsquerda)
            _corpo.move(-_velocidade.x,0.0f);
        else 
            _corpo.move(+_velocidade.x,0.0f);
    }
    
    // movimentacao do pulo
    _velocidade.y += GRAVIDADE;                     // sofre acao da gravidade
    _corpo.move (0.0f,_velocidade.y);              // move o corpo

    // verificacao se ja chegou ao solo novamente
    if (_corpo.getPosition().y >= NIVEL_DA_PLATAFORMA){
        _corpo.setPosition(_corpo.getPosition().x,NIVEL_DA_PLATAFORMA);
        _velocidade.y = 0;
        estaNoChao = true;
    }
}*/

