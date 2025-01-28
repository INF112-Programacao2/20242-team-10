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
#include "gerenciadorgrafico.h"


// construtor da classe
Arma::Arma(Identificador id) :
    Entidade (sf::Vector2f (-1000.0f, -1000.0f), sf::Vector2f (50.0f,90.0f), id),
     _dano (0.0f),
    _personagem(nullptr),
    textoSomAtaques (gGrafico->carregarFonte ("FonteNivel.ttf"), "", 15),
    gMusica (gMusica->get_gerenciadorMusical()),
    gAcessibilidade (gAcessibilidade->get_acessibilidade())
    
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

// funcao que atualiza o tamanho da arma
void Arma::set_tamanho(sf::Vector2f tamanho)
{
    _tamanho = tamanho;
}

// funcao que verifica as colisoes da arma com outras entidades
void Arma::colisao(Entidade *entidade, sf::Vector2f distancia)
{
    if (_personagem == nullptr) {
        throw std::invalid_argument ("Arma sem personagem");     
    }

    // se a arma pertence ao jogador
    if (_personagem->get_id() == Identificador::jogador) {
       // se colidiu com um esqueleto
        switch (entidade->get_id()) {
            case Identificador::esqueleto: {
                Inimigo* inimigo = dynamic_cast<Inimigo*>(entidade);
                if (inimigo && !inimigo->estaLevandoDano() && !inimigo->estaMorrendo()) {           // se o inimigo existe e nao ta tomando dano e nao ta morrendo
                    inimigo->tomarDano(_dano);                                                      // inimigo toma o dano             
                    gMusica->tocar(Identificador::som_esqueleto);                                   // toca o som do dano
                    gAcessibilidade->mostraMensagem(Identificador::texto_esqueleto, sf::Vector2f(_corpo.getPosition().x, NIVEL_DA_PLATAFORMA + 50.0f)); // mostra uma legenda do som 

                    // se o inimigo estiver morrendo
                    if (inimigo->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {
                            // jogador recebe o xp do inimigo
                            jogador->adicionarXP(inimigo->get_experiencia()); 
                        }
                    }
                }
                break;
            }
            // se colidiu com uma alma
            case Identificador::alma: {
                Alma* alma = dynamic_cast<Alma*>(entidade);
                if (alma && !alma->estaLevandoDano() && !alma->estaMorrendo() && !alma->estaInvisivel()) {          // verifica as condicoes para o inimigo poder sofrer dano
                    alma->tomarDano(_dano);                                                                         // inimigo toma dano
                    gMusica->tocar(Identificador::som_alma);                                                        // toca o som do dano
                    gAcessibilidade->mostraMensagem(Identificador::texto_alma, sf::Vector2f(_corpo.getPosition().x, NIVEL_DA_PLATAFORMA + 50.0f));      // mostra a legenda do som

                    // se o inimigo estiver morrendo
                    if (alma->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {

                            // jogador recebe o xp do inimigo
                            jogador->adicionarXP(alma->get_experiencia());
                        }
                    }
                }
                break;
            }
            // se colidiu com um morcego
            case Identificador::morcego: {
                Morcego* morcego = dynamic_cast<Morcego*>(entidade);
                if (morcego && !morcego->estaLevandoDano() && !morcego->estaMorrendo()) {                       // verifica as condicoes para o inimigo sofrer dano
                    morcego->tomarDano(_dano);                                                                  // inimigo toma dano
                    gMusica->tocar(Identificador::som_morcego);                                                 // toca a musica do dano
                    gAcessibilidade->mostraMensagem(Identificador::texto_morcego, sf::Vector2f(_corpo.getPosition().x, NIVEL_DA_PLATAFORMA + 50.0f));   // mostra a legenda do som 

                    // se o inimigo estiver morrendo
                    if (morcego->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {

                            // jogador recebe o xp do inimigo
                            jogador->adicionarXP(morcego->get_experiencia());
                        }
                    }
                }
                break;
            }
            // se colidiu com um goblin
            case Identificador::goblin: {
                Goblin* goblin = dynamic_cast<Goblin*>(entidade);
                if (goblin && !goblin->estaLevandoDano() && !goblin->estaMorrendo()) {                          // verifica as condicoes para o inimigo sofrer dano
                    goblin->tomarDano(_dano);                                                                   // inimigo toma dano
                    gMusica->tocar(Identificador::som_goblin);                                                  // toca a musica do dano
                    gAcessibilidade->mostraMensagem(Identificador::texto_goblin, sf::Vector2f(_corpo.getPosition().x, NIVEL_DA_PLATAFORMA + 50.0f));        // mostra a legenda do som

                    // se o inimigo esta morrendo
                    if (goblin->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {

                            // jogador recebe o xp do inimigo
                            jogador->adicionarXP(goblin->get_experiencia());
                        }
                    }
                }
                break;
            }
                // se colidiu com o chefao
                case Identificador::chefao: {
                Chefao* chefao = dynamic_cast<Chefao*>(entidade);
                if (chefao && !chefao->estaLevandoDano() && !chefao->estaMorrendo()) {                          // verifica as condicoes para o inimigo sofrer dano
                    chefao->tomarDano(_dano);                                                                   // inimigo toma o dano
                    gMusica->tocar(Identificador::som_chefao);                                                  // toca o som do dano
                    gAcessibilidade->mostraMensagem(Identificador::texto_chefao, sf::Vector2f(_corpo.getPosition().x, NIVEL_DA_PLATAFORMA + 50.0f));        // mostra a legenda do som

                    // se o inimigo estiver morrendo
                    if (chefao->estaMorrendo()) {
                        Jogador* jogador = dynamic_cast<Jogador*>(_personagem);
                        if (jogador) {

                            // jogador recebe o xp do inimigo
                            jogador->adicionarXP(chefao->get_experiencia());
                        }
                    }
                }
                break;
            }
        }
    }
    // se a arma pertence ao esqueleto
    else if (_personagem->get_id() == Identificador::esqueleto) {

        // se colidir com o jogador 
        if (entidade->get_id() == Identificador::jogador) {                         
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo() && _personagem->estaAtacando()) {      // verifica as condicoes para o jogador tomar dano
                jogador->tomarDano(_dano);                              // jogador toma dano
                gMusica->tocar(Identificador::som_jogador);             // toca o som do jogador tomando hit 
            }
        }
    }
    // se a arma pertence à alma
    else if (_personagem->get_id() == Identificador::alma) {

        // se colidir com o jogador 
        if (entidade->get_id() == Identificador::jogador) {
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo()) {                                       // verifica as condicoes para o jogador tomar dano
                jogador->tomarDano(_dano);                                  // jogador toma dano
                gMusica->tocar(Identificador::som_jogador);                 // toca o som do jogador tomando hit
            }
        }
    }
    // se a arma pertence ao goblin
    else if (_personagem->get_id() == Identificador::goblin) {

        // se colidir com o jogador 
        if (entidade->get_id() == Identificador::jogador) {
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo() && _personagem->estaAtacando()) {           // verifica as condicoes para o jogador tomar dano
                jogador->tomarDano(_dano);                                  // jogador toma dano
                gMusica->tocar(Identificador::som_jogador);                 // toca o som do jogador tomando hit
            }
        }
    }
    // se a arma pertence ao chefao
    else if (_personagem->get_id() == Identificador::chefao) {

        // se colidir com o jogador 
        if (entidade->get_id() == Identificador::jogador) {
            Jogador* jogador = dynamic_cast<Jogador*>(entidade);
            if (jogador && !jogador->estaLevandoDano() && !jogador->estaMorrendo() && _personagem->estaAtacando()) {            // verifica as condicoes para o jogador tomar dano
                jogador->tomarDano(_dano);                                   // jogador toma dano
                gMusica->tocar(Identificador::som_jogador);                  // toca o som do jogador tomando hit
            }
        }
    }
}

// funcao que atualiza as armas
void Arma::atualizar()
{
        if (_personagem) {

        // pega a posicao do personagem e a direcao que ele esta andando no momento
        sf::Vector2f posicaoPersonagem = _personagem->get_corpo().getPosition();
        bool andaEsquerda = _personagem->estaAndandoParaEsquerda();
    
        // se estiver atacando
        if (_personagem->estaAtacando()) {
            
            // atualiza a posição da arma
            if (andaEsquerda) {
                _corpo.setPosition(posicaoPersonagem.x - _tamanho.x, posicaoPersonagem.y);
            } else {
                _corpo.setPosition(posicaoPersonagem.x + _personagem->get_tamanho().x, posicaoPersonagem.y);
            }

        } else {
            // se nao estiver atacando, atualiza a posicao da arma para um local fora da tela
            _corpo.setPosition(-1000, -1000);
        }
    }

    gAcessibilidade->atualizar(gGrafico->get_tempo());           // atualiza o tempo dos textos de acessibilidade
}

// funcao que desenha na tela
void Arma::desenhar()
{
        gAcessibilidade->desenhar();                            // desenha os textos da acessibilidade
}
