#ifndef LISTAENTIDADE_H
#define LISTAENTIDADE_H

#include <iostream>
#include <vector>
#include "jogador.h"
#include "entidade.h"
#include "inimigo.h"
#include "obstaculo.h"
#include "plataforma.h"

class ListaEntidade {
private:
    std::vector < Entidade* > _entidades;
    Jogador* _jogador;

public:
    // construtor
    ListaEntidade();
    // destrutor
    ~ListaEntidade();
    // getters e setters
    Jogador* get_jogador () const;
    const std::vector < Entidade* >& get_entidades() const;
    int get_tamanhoLista();
    // metodos da classe
    //void adicionarJogador (const sf::Vector2f posicao, const sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id);
    //void adicionarInimigo (const sf::Vector2f posicao, const sf::Vector2f tamanho, sf::Vector2f velocidade, Jogador* jogador, Identificador id);
    //void adicionarPlataforma (sf::Vector2f posicao , sf::Vector2f tamanho, Identificador id, std::string tipo);
    void adicionarEntidade (Entidade* novaEntidade);
    void removerEntidade (Identificador id);
    void atualizar ();
    void desenhar ();
    void limparEntidades ();
    void executar ();
    
};



#endif