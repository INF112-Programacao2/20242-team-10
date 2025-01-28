#ifndef CAMADA_H
#define CAMADA_H
#include <SFML/Graphics.hpp>
#include "gerenciadorgrafico.h"

class Camada {
protected:
    GerenciadorGrafico* gGrafico;
    sf::Vector2f _tamanhoTextura;
    sf::Vector2f _origem;
    sf::Texture _textura;
    sf::RectangleShape _camada;
    

public:
    // construtor
    Camada(sf::Texture textura, sf::Vector2f tamanhoTextura, sf::Vector2f origem);
    // destrutor
    ~Camada ();

    // metodos da classe
    void desenharCamada ();


};


#endif