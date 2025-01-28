#include "projetil.h"


// funcao que atualiza a animacao do projetil, ou para a esquerda ou para a direita
void Projetil::atualizarAnimacao()
{
    if (paraEsquerda)
    _animacao.atualizar (ESQUERDA,"ATACA");
    else    
    _animacao.atualizar (DIREITA,"ATACA");
}

// funcao que atualiza a posicao do projetil
void Projetil::atualizarPosicao()
{
    float tempo = gGrafico->get_tempo();
    sf::Vector2f posFinal(0.0f,0.0f);

    posFinal.x = _posicao.x + _velocidade.x * tempo;                            // deslocamento horizontal MU
    posFinal.y = NIVEL_DA_PLATAFORMA - TAMANHO_PROJETIL - 20.0f;                // seta a posicao no eixo y um pouco acima do nivel da plataforma

    
    set_posicao (posFinal);
}

void Projetil::verificaSaiuTela()
{
    sf::Vector2f posCentral = gGrafico->get_camera().getCenter();
    sf::Vector2f tamJanela (TAMANHO_TELA_X*5,TAMANHO_TELA_Y);

    if (_posicao.x < (posCentral.x - tamJanela.x/2.0f) || _posicao.x > (posCentral.x + tamJanela.x/2.0f )){
    set_velocidade(sf::Vector2f(0.0f,0.0f));
    set_colidiu (true);
    }

}

// construtor
Projetil::Projetil(Personagem *personagem) :
    Arma (Identificador::projetil_alma) , _animacao (&_corpo), _velocidade (sf::Vector2f(0.0f,0.0f)),
    colidiu (true) , paraEsquerda (false)

{
    set_posicao(sf::Vector2f(-1000.0f,-1000.0f));
    set_personagem (personagem);
    if (_personagem != nullptr) {
        inicializarAnimacao ();
    }
}

Projetil::~Projetil()
{
}

// funcao que inicializa tudo relacionado a animacao do projetil
void Projetil::inicializarAnimacao()
{
    if (_personagem != nullptr){
        set_tamanho (sf::Vector2f (TAMANHO_PROJETIL,TAMANHO_PROJETIL));
        switch (_personagem->get_id())
        {
            case (Identificador::alma): {
                sf::Vector2f escala (2.5f, 2.5f);
                sf::Vector2f origem (_tamanho.x * escala.x / 4.0f , _tamanho.y * escala.y / 2.5f);
                _animacao.adicionarAnimacao("ProjetilAlma.png", "ATACA" , 1 , 0.12 , escala, origem, true);
                _animacao.set_imagemAtual ("ATACA");
            }
            break;
    
    
        }
    }
}

void Projetil::set_sentido(bool paraEsquerda)
{
    this->paraEsquerda = paraEsquerda;
    _velocidade = paraEsquerda ? sf::Vector2f (_velocidade.x * -1,_velocidade.y) : _velocidade;
}

void Projetil::set_velocidade(sf::Vector2f velocidade)
{
    _velocidade = velocidade;
}

void Projetil::set_colidiu(bool colidiu)
{
    this->colidiu = colidiu;
    if ( colidiu ) 
    {
        set_posicao (sf::Vector2f(-1000.0f,-1000.0f));
        _velocidade = sf::Vector2f (0.0f,0.0f);
    }
}

bool Projetil::ocorreuColisao()
{
    return this->colidiu;
}

void Projetil::desenhar()
{
    gGrafico->desenhar (_corpo);
}

void Projetil::atualizar()
{
    if (!colidiu) {
        atualizarPosicao ();
        verificaSaiuTela ();
        atualizarAnimacao ();
        desenhar ();
    }
}
