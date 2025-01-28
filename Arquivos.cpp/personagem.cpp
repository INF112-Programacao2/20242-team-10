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
    sf::Vector2f posicaoBarraVida = _barraVida.getPosition();   // pega a posicao da barra de vida
    _textoNivel.set_posicao (sf::Vector2f(posicaoBarraVida.x - _textoNivel.get_tamanho().x, posicaoBarraVida.y - _textoNivel.get_tamanho().y / 2.0f));  // seta a posicao
}

// construtor
Personagem::Personagem (sf::Vector2f posicao, sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id, float duracaoMorte , float duracaoSofrerDano) :        // inicializa todos os parametros
    Entidade (posicao,tamanho,id),
    _velocidade (velocidade),
    andando (false),
    andaEsquerda (false),
    deltaTempo (0.0f),
    levandoDano (false),
    atacando (false),
    morrendo (false),
    _vidaMaxima (100.0f),
    _animacao(&_corpo),
    _experiencia(),
    _arma (nullptr), 
    _vida (100.0f),
    _tempoMorte (0.0f),
     _tempoDano (0.0f),
    _duracaoAnimacaoSofrerDano(duracaoSofrerDano),
    _duracaoAnimacaoMorte(duracaoMorte),
    _tempoProtecaoAtaque(0.0f),
    _protegido(false),
    _textoNivel (gGrafico->carregarFonte ("FonteNivel.ttf"), "", 15) ,
    _tempoAtaque (0.0f) 

     {
    
     }
                               

// destrutor
Personagem::~Personagem () {

}

// funcao que retorna a velocidade do corpo
sf::Vector2f Personagem::get_velocidade()
{
    return this->_velocidade;
}

// funcao que retorna para que lado o personagem esta andando
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

// funcao que retorna se esta atacando ou nao
bool Personagem::estaAtacando() const
{
    return atacando;
}

// funcao que retorna a forca do personagem
float Personagem::get_forca()
{
    return _experiencia.get_forca();
}

// funcao que retorna se esta levando dano ou nao
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

// funcao que retorna a arma do personagem
Arma *Personagem::get_arma()
{
    return _arma;
}

// funcao que atualiza a variavel protegido (cooldown dos combates)
void Personagem::set_protegido(bool protegido)
{
    _protegido = protegido;
}

// funcao que retorna a variavel protegido
bool Personagem::get_protegido()
{
    return _protegido;
}

// funcao que retorna o tempo de protecao contra ataques
float Personagem::get_tempoProtecaoAtaque()
{
    return _tempoProtecaoAtaque;
}

// funcao que atualiza a duracao da animacao de morte
void Personagem::set_duracaoAnimacaoMorte(float duracao)
{
    _duracaoAnimacaoMorte = duracao;
}

// funcao que retorna a vida do personagem
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

// funcao que atualiza os estados para andar
void Personagem::andar(bool andaEsquerda)
{
    atacando = false;
    andando = true;
    if(andaEsquerda)
        this->andaEsquerda = true;
    else
        this->andaEsquerda = false; 
}

// funcao que atualiza o estado para parar
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
    if (_protegido) {                                                                       // se estiver protegido
        _tempoProtecaoAtaque += gGrafico->get_tempo();
        if (_tempoProtecaoAtaque >= TEMPO_RECUPERACAO_DANO) {                               // fica protegido ate o tempo de recuperacao de dano    
            _protegido = false;                                                             // apos esse tempo, reseta os estados e pode sofrer outro ataque
            _tempoProtecaoAtaque = 0.0f;
        }
    }
}

// funcao que atualiza os estados para o personagem atacar
void Personagem::atacar(bool atacando)
{
    this->atacando = atacando;   
    if (atacando && _arma) {
        _arma->atualizar();
    }  
}

// funcao que aplica de fato o dano sofrido
void Personagem::tomarDano(float dano)
{
    
    if (!levandoDano && !_protegido) {               // verifica se o personagem pode levar dano

        // atualiza os estados para tomar o dano
        levandoDano = true;
        _protegido = true;
        andando = false;
        atacando = false;
        _vida -= dano;
        
        // se o personagem morrer
        if (_vida <= 0.0f) {

            // atualiza os estados de morte
            morrendo = true;
            _vida = 0.0f;
        }
        
        _tempoDano = 0.0f;
        _tempoProtecaoAtaque = 0.0f;
    }
}

    