#ifndef LISTAENTIDADE_H
#define LISTAENTIDADE_H

#include <iostream>
#include <vector>
#include "jogador.h"
#include "entidade.h"


class Arma;

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
    void adicionarEntidade (Entidade* novaEntidade);
    void limparEntidadesMortas ();
    void removerEntidade (Identificador id);
    void atualizar ();
    void desenhar ();
    void limparEntidades ();
    void executar ();
    
};



#endif