#ifndef GERENCIADORCOLISAO_H
#define GERENCIADORCOLISAO_H

#include "listaentidade.h"

class GerenciadorColisao {
private:
    ListaEntidade* _listaPersonagens;
    ListaEntidade* _listaObstaculos;

    void verificaColisaoEntrePersonagens ();
    void verificaColisaoPersonagemObstaculo ();
public:
    // construtor
    GerenciadorColisao (ListaEntidade* listaPersonagens, ListaEntidade* listaObstaculos);

    // destrutor
    ~GerenciadorColisao ();

    // metodos da classe
    sf::Vector2f calculaColisao (Entidade* entidade1, Entidade* entidade2);
    void executar ();
};


#endif