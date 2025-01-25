#include "personagem.h"
#include "arma.h"
#include <iostream>


// funcao que atualiza a animacao da barra de vida
void Personagem::atualizarBarraVida()
{
    sf::Vector2f posicaoBarraVida (sf::Vector2f (_posicao.x + _tamanho.x / 2.0f - _corpo.getSize().x / 2.0f, _posicao.y - 20.0f));          // atualiza a posicao da barra, sempre acima do personagem, de acordo com sua posicao 
    _barraVida.setPosition(posicaoBarraVida);                                                                                               // atualiza a posicao
    _barraVida.setSize(sf::Vector2f ((_vida/100.0f)*TAMANHO_BARRA_VIDA_EIXO_X, TAMANHO_BARRA_VIDA_EIXO_Y ));                               // atualiza o tamanho da barra de vida de acordo com a vida
}

// funcao que atualiza a animacao do nivel
void Personagem::atualizarNivel()
{
    sf::Vector2f posicaoBarraVida = _barraVida.getPosition();
    _textoNivel.set_posicao (sf::Vector2f(posicaoBarraVida.x - _textoNivel.get_tamanho().x, posicaoBarraVida.y - _textoNivel.get_tamanho().y / 2.0f));
}

// construtor
Personagem::Personagem (sf::Vector2f posicao, sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id, float duracaoMorte , float duracaoSofrerDano) :        // inicializa todos os parametros
    Entidade (posicao,tamanho,id) , _velocidade (velocidade) , andando (false) , andaEsquerda (false) , deltaTempo (0.0f),
    levandoDano (false) , atacando (false) , morrendo (false) , _vidaMaxima (100.0f) , _animacao(&_corpo) ,  _experiencia() , _arma (nullptr) , 
    _vida (100.0f) , _tempoMorte (0.0f) , _tempoDano (0.0f) , _duracaoAnimacaoSofrerDano(duracaoSofrerDano) , _duracaoAnimacaoMorte(duracaoMorte),
     _tempoProtecaoAtaque(0.0f), _protegido(false) , _textoNivel (gGrafico->carregarFonte ("FonteNivel.ttf"), "", 15) , _tempoAtaque (0.0f) {}
                               

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

void Personagem::set_protegido(bool protegido)
{
    _protegido = protegido;
}

bool Personagem::get_protegido()
{
    return _protegido;
}

float Personagem::get_tempoProtecaoAtaque()
{
    return _tempoProtecaoAtaque;
}

void Personagem::set_duracaoAnimacaoMorte(float duracao)
{
    _duracaoAnimacaoMorte = duracao;
}

float Personagem::get_vida()
{
    return _vida;
}

// funcao que desenha na tela, vinda da classe gerenciador grafico
void Personagem::desenhar()
{
    gGrafico->desenhar(_corpo);
    gGrafico-> desenhar (_barraVida);
    gGrafico-> desenhar (_textoNivel.get_texto());
    
}

void Personagem::andar(bool andaEsquerda)
{
    atacando = false;
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

// funcao que atualiza o tempo sob protecao dos personagens ao sofrerem ataques
void Personagem::atualizarTempoProtegido()
{
    if (_protegido) {
        _tempoProtecaoAtaque += gGrafico->get_tempo();
        if (_tempoProtecaoAtaque >= TEMPO_RECUPERACAO_DANO) {
            _protegido = false;
            _tempoProtecaoAtaque = 0.0f;
        }
    }
}

void Personagem::atacar(bool atacando)
{
    /*this->atacando = atacando; */
    this->atacando = atacando;   
    if (atacando && _arma) {
        _arma->atualizar();
    }  
}

// funcao que aplica de fato o dano sofrido
void Personagem::tomarDano(float dano)
{
    //std::cout << "Debug - Vida antes: " << _vida << std::endl;
    
    if (!levandoDano && !_protegido) {
        levandoDano = true;
        _protegido = true;
        andando = false;
        atacando = false;
        _vida -= dano;
        
        if (_vida <= 0.0f) {
            morrendo = true;
            _vida = 0.0f;
        }
        
        _tempoDano = 0.0f;
        _tempoProtecaoAtaque = 0.0f;
       // std::cout << "Debug - Vida depois: " << _vida << std::endl;
    }

    /*
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
    }*/
}
