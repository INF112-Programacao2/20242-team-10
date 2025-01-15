#include "arma.h"
#include "entidade.h"
#include "personagem.h"
#include "inimigo.h"
#include "jogador.h"

// construtor da classe
Arma::Arma(Identificador id) :
    Entidade (sf::Vector2f (-1000.0f, -1000.0f), sf::Vector2f (50.0f,90.0f), id) , _dano (0.0f), _personagem(nullptr)
{

}

// destrutor da classe
Arma::~Arma()
{
}

// funcao que atualiza o personagem em uso
void Arma::set_personagem(Personagem *personagem)
{
    _personagem = personagem;
    _dano = _personagem->get_forca();
}

// funcao que atualiza o dano da arma
void Arma::set_dano(float dano)
{
    _dano = dano;
}

// funcao que retorna o dano da arma
float Arma::get_dano()
{
    return _dano;
}

void Arma::set_tamanho(sf::Vector2f tamanho)
{
    _tamanho = tamanho;
}

// funcao que verifica as colisoes da arma com outras entidades
void Arma::colisao(Entidade *entidade, sf::Vector2f distancia)
{
    if (_personagem == nullptr) return;

    // Se a arma pertence ao jogador
    if (_personagem->get_id() == Identificador::jogador) {
        if (entidade->get_id() == Identificador::esqueleto) {
            Inimigo* inimigo = dynamic_cast<Inimigo*>(entidade);
            if (inimigo && !inimigo->estaLevandoDano() && !inimigo->estaMorrendo()) {
                inimigo->tomarDano(_dano);
                if (inimigo->estaMorrendo()) {
                    // Dá XP para o jogador se matou o inimigo
                    Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                    if (jogador) {
                        jogador->adicionarXP(inimigo->get_experiencia());
                    }
                }
            }
        }
    }
    // Se a arma pertence ao inimigo
    else if (_personagem->get_id() == Identificador::esqueleto) {
        if (entidade->get_id() == Identificador::jogador) {
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo()) {
                jogador->tomarDano(_dano);
            }
        }
    }
}

void Arma::atualizar()
{
    if (_personagem) {
        sf::Vector2f posicaoPersonagem = _personagem->get_corpo().getPosition();
        bool andaEsquerda = _personagem->estaAndandoParaEsquerda();
    
        if (_personagem->estaAtacando ()){
            if (andaEsquerda) {
                _corpo.setPosition (posicaoPersonagem.x - _tamanho.x, posicaoPersonagem.y);
            }
            else {
                _corpo.setPosition (posicaoPersonagem.x + _personagem->get_tamanho().x, posicaoPersonagem.y);
            }
        }
    }
    else {
        _corpo.setPosition (-1000,-1000);      // atualiza fora da tela quando nao estiver em combate
    }
}

void Arma::desenhar()
{
    if (_personagem && _personagem->estaAtacando()){
        _corpo.setFillColor(sf::Color::Red); // apenas para debug
        gGrafico->desenhar (_corpo);
    }
}
