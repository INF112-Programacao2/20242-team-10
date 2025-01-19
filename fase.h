#ifndef FASE_H
#define FASE_H

#include "entidade.h"
#include "listaentidade.h"
#include "fundo.h"
#include "gerenciadorcolisao.h"
#include "gerenciadoreventos.h"
#include "mensagemBox.h"



class Jogador;
class Esqueleto;

class Fase {
protected:
    MensagemBox* _mensagem;
    GerenciadorGrafico* gGrafico;
    GerenciadorColisao* gColisao;
    GerenciadorEvento* gEvento;
   // Identificador _idFase;
   // std::vector < std::vector < char >> _mapa;
    ListaEntidade* _listaPersonagens;
    ListaEntidade* _listaObstaculos;
    Fundo _fundo;
    static Jogador* _jogador;

    //std::vector < Porta* > _portas;

    
    void criarPlataforma (sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo, sf::Vector2f escala);
    void criarParede (sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo);
   // void criarPorta (sf::Vector2f posicao, sf::Vector2f tamanho);


public:
    // construtor
    Fase ();
    // destrutor
    ~Fase ();
    //  getters e setters
    void set_limiteCamera (sf::IntRect limiteCamera);
    Jogador* get_jogador();
    // metodos da classe
    void criarPersonagem (sf::Vector2f posicao, Identificador id);
    void criarMapa();
    //void inicializarPortas ();
    void criarFundo ();
    void executarFase ();
    void desenhar ();

};

#endif