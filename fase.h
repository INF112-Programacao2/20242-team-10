#ifndef FASE_H
#define FASE_H

#include "entidade.h"
#include "listaentidade.h"
#include "fundo.h"
#include "gerenciadorcolisao.h"


class Jogador;
class Esqueleto;

class Fase {
protected:
    GerenciadorGrafico* gGrafico;
    GerenciadorColisao* gColisao;
    Identificador _idFase;
    std::vector < std::vector < char >> _mapa;
    ListaEntidade* _listaPersonagens;
    ListaEntidade* _listaObstaculos;
    Fundo _fundo;
    static Jogador* _jogador;
    
    void criarPlataforma (sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo, sf::Vector2f escala);
    void criarParede ();
    void criarPorta (sf::Vector2f posicao, sf::Vector2f tamanho);


public:
    // construtor
    Fase (Identificador idFase, Identificador idFundo);
    // destrutor
    ~Fase ();
    //  getters e setters
    void set_limiteCamera (sf::IntRect limiteCamera);
    void set_mapa(std::vector < std::vector < char >> mapa);
    //sf::IntRect get_limiteCamera ();
    Jogador* get_jogador();
    // metodos da classe
    void criarPersonagem (sf::Vector2f posicao, Identificador id);
    //void mudarFase (Identificador id = Identificador::comeco);
    virtual void criarMapa() = 0;
    virtual void criarFundo () = 0;
    void executarFase ();
    void desenhar ();

};

#endif