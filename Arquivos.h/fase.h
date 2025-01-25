#ifndef FASE_H
#define FASE_H

#include "entidade.h"
#include "listaentidade.h"
#include "fundo.h"
#include "gerenciadorcolisao.h"
#include "mensagemBox.h"
#include "textosom.h"



class Jogador;
class Esqueleto;
class GerenciadorEvento;

class Fase {
protected:
    MensagemBox* _mensagem;
    TextoSom* _textoSom;
    GerenciadorGrafico* gGrafico;
    GerenciadorColisao* gColisao;
    GerenciadorEvento* gEvento;
   // Identificador _idFase;
   // std::vector < std::vector < char >> _mapa;
    ListaEntidade* _listaPersonagens;
    ListaEntidade* _listaObstaculos;
    Fundo _fundo;
    static Jogador* _jogador;

    //MensagemBox* _mensagem;

    //std::vector < Porta* > _portas;

    
    void criarPlataforma (sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo, sf::Vector2f escala);
    void criarParede (sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo);
    void criarEspinho (sf::Vector2f posicao, sf::Vector2f tamanho);
    //void criarEscada (sf::Vector2f posicao, sf::Vector2f tamanho);
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
    void reiniciarFase ();
    void criarPersonagem (sf::Vector2f posicao, Identificador id);
    void criarMapa();
    MensagemBox* get_mensagem ();
    //void inicializarPortas ();
    void criarFundo ();
    void executarFase ();
    void desenhar ();

};

#endif