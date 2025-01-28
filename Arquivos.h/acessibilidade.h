#ifndef ACESSIBILIDADE_H
#define ACESSIBILIDADE_H

#include <SFML/Graphics.hpp>

#include "gerenciadorgrafico.h"
#include "identificadores.h"


class Acessibilidade {
private:
    GerenciadorGrafico* gGrafico;
    std::map<Identificador, std::string> _mapMensagens;
    sf::Text _texto;
    sf::Font _fonte;
    float _tempoExibicao;
    bool _visivel;

    void adicionarMensagem(Identificador idTexto, std::string mensagem);
    void inicializar();
    
public:
    // construtor
    Acessibilidade ();

    // destrutor
    ~Acessibilidade ();

    //getters e setters
    bool estaVisivel ();
    static Acessibilidade* get_acessibilidade();
    
    static Acessibilidade* gAcessibilidade;

    // metodos da classe
    void mostraMensagem (Identificador idMensagem, sf::Vector2f posicao);
    void atualizar (float tempo);
    void desenhar ();


};



#endif