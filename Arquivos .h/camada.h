#ifndef CAMADA_H
#define CAMADA_H
#include <SFML/Graphics.hpp>
#include "gerenciadorgrafico.h"

class Camada {
protected:
    GerenciadorGrafico* gGrafico;
   //sf::Vector2f _tamanhoJanela;
    sf::Vector2f _tamanhoTextura;
    sf::Vector2f _origem;
    //sf::IntRect _dimensao;
    //float _velocidade;
    sf::Texture _textura;
    sf::RectangleShape _camada;
    

public:
    // construtor
    Camada(sf::Texture textura, sf::Vector2f tamanhoTextura, sf::Vector2f origem);
    // destrutor
    ~Camada ();
    //getters e setter
    //sf::Vector2f get_tamanhoJanela();
    // metodos da classe
    void desenharCamada ();
    //void atualizar (sf::Vector2f distancia);

};


#endif