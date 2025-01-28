#include "entidade.h"
#include <iostream>


// cria o gerenciador grafico 
GerenciadorGrafico* Entidade::gGrafico = GerenciadorGrafico::get_grafico();

// construtor
Entidade::Entidade(sf::Vector2f posicao, sf::Vector2f tamanho, Identificador id) :
    _corpo(sf::RectangleShape (tamanho)),
    _tamanho(tamanho),
    _posicao(posicao),
    _id(id),
    _podeRemover (false)    
{
     // seta a posicao e a cor do corpo
    _corpo.setPosition(posicao);                                                  
}

// destrutor
Entidade::~Entidade()
{
}


// funcao que retorna o corpo
sf::RectangleShape Entidade::get_corpo() const
{
    return this->_corpo;
}

// funcao que seta a nova posicao do corpo
void Entidade::set_posicao(sf::Vector2f posicao)
{
    _corpo.setPosition(posicao);
    this->_posicao = posicao;
   
}
// funcao que retorna a posicao do corpo
sf::Vector2f Entidade::get_posicao() const
{
    return _corpo.getPosition();
}

// funcao que seta o tamanho do corpo
void Entidade::set_tamanho(sf::Vector2f tamanho)
{   
    _corpo.setSize(tamanho);
    this->_tamanho = tamanho;
}

// funcao que retorna o tamanho
sf::Vector2f Entidade::get_tamanho()
{
    return this->_tamanho;
}

// funcao que retorna o id da entidade 
Identificador Entidade::get_id() const
{
    return this->_id;
}

// funcao que retorna o tempo do relogio do gerenciador grafico
float Entidade::get_tempo()
{
    return gGrafico->get_tempo();
}

// funcao que retorna o estado se pode remover ou nao a entidade
bool Entidade::podeRemover()
{
    return _podeRemover;
}

// funcao que desenha na tela, utilizando o metodo da classe gerenciador grafico
void Entidade::desenhar()
{
    gGrafico->desenhar(_corpo);
}

// funcao que atualiza o estado se pode remover ou nao a entidade
void Entidade::remover()
{
    _podeRemover = true;
}
