#ifndef ANIMACAO_H
#define ANIMACAO_H
#include <SFML/Graphics.hpp>
#include <map>
#include "imagem.h"

class Animacao {
private:
    sf::RectangleShape* _corpo;
    std::map<std::string, Imagem*> mapaImagem;                                  // a string sinaliza qual acao esta ocorrendo, como: parado, atacando, andando...
    sf::Clock _relogio;
    std::string _imagemAtual;               

public:
    // construtor
    Animacao (sf::RectangleShape* corpo);
    // destrutor
    ~Animacao ();
    // getters e setters
    std::string get_imagemAtual() const;
    void set_imagemAtual (std::string imagemAtual);
    unsigned int get_frameAtual();
    void set_frameAtual (unsigned int frameAtual);
    float get_tempoTotal ();
    void set_tempoTotal (float tempoTotal);
    // metodos da classe
    void atualizar (Direcao direcao, std::string imagemAtual);
    void adicionarAnimacao (const char* textura, std::string nome, unsigned int quantidadeImagens, float tempoTroca, sf::Vector2f escala, sf::Vector2f origem, bool horizontal);
};


#endif