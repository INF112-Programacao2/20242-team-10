#ifndef ENTIDADE_H
#define ENTIDADE_H
#include <SFML/Graphics.hpp>
#include "gerenciadorgrafico.h"
#include "identificadores.h"

class Entidade {
protected:
    sf::RectangleShape _corpo;
    sf::Vector2f _posicao;
    sf::Vector2f _tamanho;
    Identificador _id;

    static GerenciadorGrafico* gGrafico;

public:
    // construtor
    Entidade (sf::Vector2f posicao,sf::Vector2f tamanho, Identificador id);
    //destrutor
    virtual ~Entidade();
    // getters e setters
    sf::RectangleShape get_corpo() const;
    void set_posicao(sf::Vector2f posicao);
    sf::Vector2f get_posicao () const;
    void set_tamanho(sf::Vector2f tamanho);
    sf::Vector2f get_tamanho();
    Identificador get_id () const;
    float get_tempo ();
    // metodos virtuais
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia) = 0;
    virtual void atualizar() = 0;
    virtual void desenhar ();
};


#endif