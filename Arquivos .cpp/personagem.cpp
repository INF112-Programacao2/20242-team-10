#include "personagem.h"

// construtor 
Personagem::Personagem (sf::Vector2f posicao, sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id) :
    Entidade (posicao,tamanho,id) , _velocidade (velocidade) , andando (false) , andaEsquerda (false) ,
    levandoDano (false) , atacando (false) , morrendo (false) , vidaMaxima (100.0f) , _animacao(&_corpo) {}                                   // inicializa todos os parametros

// destrutor
Personagem::~Personagem () {

}

// funcao que retorna a velocidade do corpo
sf::Vector2f Personagem::get_velocidade()
{
    return this->_velocidade;
}

// funcao que seta a velocidade do corpo
void Personagem::set_velocidade(sf::Vector2f velocidade)
{
    this->_velocidade = velocidade;
}

// funcao que retorna se esta morrendo ou nao
bool Personagem::estaMorrendo()
{
    return morrendo;
}

bool Personagem::estaAtacando() const
{
    return atacando;
}

// funcao que desenha na tela, vinda da classe gerenciador grafico
void Personagem::desenhar()
{
    gGrafico->desenhar(_corpo);
}

void Personagem::andar(bool andaEsquerda)
{
    andando = true;
    if(andaEsquerda)
        this->andaEsquerda = true;
    else
        this->andaEsquerda = false; 
}

void Personagem::parar()
{
    this->andando = false;
}

void Personagem::atacar(bool atacando)
{
    this->atacando = atacando;   
}

void Personagem::atualizarPosicao()
{/*   
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

    //atualiza as posicao
    _corpo.move(sf::Vector2f(_posicao.x + deltaDistancia.x,_posicao.y + deltaDistancia.y));

    /*
    // movimentacao do pulo
    _velocidade.y += GRAVIDADE;                     // sofre acao da gravidade
    _corpo.move (0.0f,_velocidade.y);              // move o corpo

    // verificacao se ja chegou ao solo novamente
    if (_corpo.getPosition().y >= NIVEL_DA_PLATAFORMA){
        _corpo.setPosition(_corpo.getPosition().x,NIVEL_DA_PLATAFORMA);
        _velocidade.y = 0;
    }*/
}
