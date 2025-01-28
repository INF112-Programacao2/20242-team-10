#ifndef IMAGEM_H
#define IMAGEM_H
#include "gerenciadorgrafico.h"

enum Direcao {
    DIREITA,
    ESQUERDA
};

class Imagem {
private:
    GerenciadorGrafico* gGrafico;
    sf::Vector2f _escala;
    sf::Vector2f _origem;
    sf::Texture _textura;
    sf::IntRect _tamanho;
    bool horizontal;
    unsigned int _quantidadeFrames;
    unsigned int _frameAtual;
    float _tempoTroca;
    float _tempoTotal;

public:
    // construtor
    Imagem (const char* textura, unsigned int quantidadeFrames, float tempoTroca, sf::Vector2f escala, sf::Vector2f origem, bool horizontal);

    // destrutor
    ~Imagem ();

    // getters e setters
    unsigned int get_quantidadeFrames ();
    unsigned int get_frameAtual ();
    void set_frameAtual (unsigned int frameAtual);
    float get_tempoTotal ();
    void set_tempoTotal (float tempoTotal);
    sf::Vector2f get_escala ();
    sf::Vector2f get_origem ();
    sf::IntRect get_tamanho ();
    sf::Texture* get_textura ();
    
    // metodos da classe
    void resetar ();
    void atualizarFrame (float tempo);
    void atualizar (Direcao direcao, float tempo);
    void ajustarRecorteHorizontal (Direcao direcao);
    void ajustarRecorteVertical (Direcao direcao);

};


#endif