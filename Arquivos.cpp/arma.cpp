#include "arma.h"
#include "entidade.h"
#include "personagem.h"
#include "inimigo.h"
#include "jogador.h"
#include <iostream>
#include "morcego.h"
#include "alma.h"
#include "goblin.h"
#include "chefao.h"


// construtor da classe
Arma::Arma(Identificador id) :
    Entidade (sf::Vector2f (-1000.0f, -1000.0f), sf::Vector2f (50.0f,90.0f), id) , _dano (0.0f), _personagem(nullptr), textoSomAtaques (gGrafico->carregarFonte ("FonteNivel.ttf"), "", 15)
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
    if (_personagem == nullptr) {
        std::cout << "Debug - Arma sem personagem" << std::endl;      // exption
        return;
    }

    // Se a arma pertence ao jogador
    if (_personagem->get_id() == Identificador::jogador) {
        // Verifica se o jogador está atacando
        if (!_personagem->estaAtacando()) {
            return;
        }

        switch (entidade->get_id()) {
            case Identificador::esqueleto: {
                Inimigo* inimigo = dynamic_cast<Inimigo*>(entidade);
                if (inimigo && !inimigo->estaLevandoDano() && !inimigo->estaMorrendo()) {
                    inimigo->tomarDano(_dano);
                    if (inimigo->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {
                            jogador->adicionarXP(inimigo->get_experiencia());
                        }
                    }
                }
                break;
            }
            case Identificador::alma: {
                Alma* alma = dynamic_cast<Alma*>(entidade);
                if (alma && !alma->estaLevandoDano() && !alma->estaMorrendo() && !alma->estaInvisivel()) {
                    alma->tomarDano(_dano);
                    //std::cout <<"Vida alma: " << alma->get_vida ();
                    if (alma->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {
                            jogador->adicionarXP(alma->get_experiencia());
                        }
                    }
                }
                break;
            }
            case Identificador::morcego: {
                Morcego* morcego = dynamic_cast<Morcego*>(entidade);
                if (morcego && !morcego->estaLevandoDano() && !morcego->estaMorrendo()) {
                    morcego->tomarDano(_dano);
                    if (morcego->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {
                            jogador->adicionarXP(morcego->get_experiencia());
                        }
                    }
                }
                break;
            }

            case Identificador::goblin: {
                Goblin* goblin = dynamic_cast<Goblin*>(entidade);
                if (goblin && !goblin->estaLevandoDano() && !goblin->estaMorrendo()) {
                    goblin->tomarDano(_dano);
                    if (goblin->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {
                            jogador->adicionarXP(goblin->get_experiencia());
                        }
                    }
                }
                break;
            }

                case Identificador::chefao: {
                Chefao* chefao = dynamic_cast<Chefao*>(entidade);
                if (chefao && !chefao->estaLevandoDano() && !chefao->estaMorrendo()) {
                    chefao->tomarDano(_dano);
                    if (chefao->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {
                            jogador->adicionarXP(chefao->get_experiencia());
                        }
                    }
                }
                break;
            }
        }
    }
    // Se a arma pertence ao esqueleto
    else if (_personagem->get_id() == Identificador::esqueleto) {
        if (entidade->get_id() == Identificador::jogador) {
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo() && _personagem->estaAtacando()) {
                jogador->tomarDano(_dano);
            }
        }
    }
    // Se a arma pertence à alma
    else if (_personagem->get_id() == Identificador::alma) {
        if (entidade->get_id() == Identificador::jogador) {
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo()) {
                jogador->tomarDano(_dano);
            }
        }
    }
    // Se a arma pertence ao goblin
    else if (_personagem->get_id() == Identificador::goblin) {
        if (entidade->get_id() == Identificador::jogador) {
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo() && _personagem->estaAtacando()) {
                jogador->tomarDano(_dano);
            }
        }
    }
    // Se a arma pertence ao chefao
    else if (_personagem->get_id() == Identificador::chefao) {
        if (entidade->get_id() == Identificador::jogador) {
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo() && _personagem->estaAtacando()) {
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
    
        if (_personagem->estaAtacando()) {
            
            // Atualiza a posição da arma
            if (andaEsquerda) {
                _corpo.setPosition(posicaoPersonagem.x - _tamanho.x, posicaoPersonagem.y);
            } else {
                _corpo.setPosition(posicaoPersonagem.x + _personagem->get_tamanho().x, posicaoPersonagem.y);
            }
            
            // Garante que a arma tenha dano durante o ataque
            if (_personagem->get_id() == Identificador::esqueleto) {
                _dano = _personagem->get_forca();
            }
        } else {
            _corpo.setPosition(-1000, -1000);
            if (_personagem->get_id() == Identificador::esqueleto) {
                _dano = 0;  // Zera o dano quando não está atacando
            }
        }
    }
    /*if (_personagem) {
        sf::Vector2f posicaoPersonagem = _personagem->get_corpo().getPosition();
        bool andaEsquerda = _personagem->estaAndandoParaEsquerda();
    
        if (_personagem->estaAtacando ()){
            std::cout << "Arma atacando! ID: " << (int)_id << std::endl; // Debug
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
    }*/
}

void Arma::desenhar()
{
    if (_personagem && _personagem->estaAtacando()){
        _corpo.setFillColor(sf::Color::Red);    // apenas para debug
        gGrafico->desenhar (_corpo);
    }
}
