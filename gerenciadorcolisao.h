#ifndef GERENCIADORCOLISAO_H
#define GERENCIADORCOLISAO_H

#include "listaentidade.h"

class GerenciadorColisao {
private:
    ListaEntidade* _listaPersonagens;
    ListaEntidade* _listaObstaculos;

    void verificaColisaoEntrePersonagens ();
    void verificaColisaoPersonagemObstaculo ();
    //void verificarColisaoArmas ();
public:
    GerenciadorColisao (ListaEntidade* listaPersonagens, ListaEntidade* listaObstaculos);
    ~GerenciadorColisao ();
    sf::Vector2f calculaColisao (Entidade* entidade1, Entidade* entidade2);
    void executar ();
};


#endif