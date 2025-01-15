#include "personagem.h"
#include "arma.h"

// funcao que atualiza a animacao da barra de vida
void Personagem::atualizarBarraVida()
{
    /*sf::Vector2f posicaoBarraVida (sf::Vector2f (_posicao.x + _tamanho.x / 2.0f - _corpo.getSize().x / 2.0f, _posicao.y - 20.0f));          // atualiza a posicao da barra, sempre acima do personagem, de acordo com sua posicao 
    _barraVida.setPosition(posicaoBarraVida);                                                                                               // atualiza a posicao
    _barraVida.setSize(sf::Vector2f ((_vida/100.0f)*TAMANHO_BARRA_VIDA_EIXO_X, TAMANHO_BARRA_VIDA_EIXO_Y ));    */                            // atualiza o tamanho da barra de vida de acordo com a vida
}

// funcao que atualiza a animacao do nivel
void Personagem::atualizarNivel()
{
    sf::Vector2f posicaoBarraVida = _barraVida.getPosition();


}

// construtor
Personagem::Personagem (sf::Vector2f posicao, sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id, float duracaoMorte , float duracaoSofrerDano) :        // inicializa todos os parametros
    Entidade (posicao,tamanho,id) , _velocidade (velocidade) , andando (false) , andaEsquerda (false) , deltaTempo (0.0f),
    levandoDano (false) , atacando (false) , morrendo (false) , _vidaMaxima (100.0f) , _animacao(&_corpo) ,  _experiencia() , _arma (nullptr) , 
    _vida (100.0f) , _tempoMorte (0.0f) , _tempoDano (0.0f) , _duracaoAnimacaoSofrerDano(duracaoSofrerDano) , _duracaoAnimacaoMorte(duracaoMorte) {}
                               

// destrutor
Personagem::~Personagem () {

}

// funcao que retorna a velocidade do corpo
sf::Vector2f Personagem::get_velocidade()
{
    return this->_velocidade;
}

bool Personagem::estaAndandoParaEsquerda()
{
    return andaEsquerda;
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

float Personagem::get_forca()
{
    return _experiencia.get_forca();
}

bool Personagem::estaLevandoDano()
{
    return levandoDano;
}

// funcao que atualiza a arma do personagem
void Personagem::set_arma(Arma *arma)
{
    _arma = arma;
    _arma->set_personagem(this);
    _arma->set_tamanho(_tamanho);
    _arma->set_dano(_experiencia.get_forca());
}

Arma *Personagem::get_arma()
{
    return _arma;
}

// funcao que desenha na tela, vinda da classe gerenciador grafico
void Personagem::desenhar()
{
    gGrafico->desenhar(_corpo);
    gGrafico-> desenhar (_barraVida);
    
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

// funcao que atualiza quando o personagem sofre um ataque 
void Personagem::atualizarTomarDano()
{
    _tempoDano += gGrafico-> get_tempo();                                                   // incrementa o tempo do relogio do gerenciador na variavel que guarda o tempo de dano
    if (levandoDano && (_tempoDano > _duracaoAnimacaoSofrerDano)){                          // se o personagem estiver levando dano, so que ja acabou a animacao
        levandoDano = false;                                                                // para de sofrer o dano
        _tempoDano = 0.0f;                                                                   // reseta o tempo de dano
    }
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

// funcao que aplica de fato o dano sofrido
void Personagem::tomarDano(float dano)
{
    if (!levandoDano){                                                              // se nao estiver levando dano
        levandoDano = true;                                                         // atualiza a variavel para sinalizar que esta sendo atacado
        andando = false;                                                            // para de andar
         //float danoFinal = dano / (1.0f + (_experiencia.get_defesa() / 100.0f));
        _vida -= dano ;                                                               // diminui a vida de acordo com o dano sofrido
        if (_vida <= 0.0f) {                                                        // se o personagem morrer
            morrendo = true;                                                        // atualiza a variavel sinalizando a morte
            _vida = 0.0f;                                                           // atualiza a vida para 0.0f
        }   
        _tempoDano = 0.0f;                                                          // reseta o tempo de dano
    }
}
