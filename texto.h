#ifndef TEXTO_H
#define TEXTO_H
#include <SFML/Graphics.hpp>
#include "gerenciadorgrafico.h"

class Texto {
private:
    sf::Font _fonte;
    std::string _informacao;

protected:
    sf::Vector2f _tamanho;
    sf::Vector2f _posicao;
    sf::Text _texto;
    unsigned int _tamanhoFonte;
    sf::Color _corBorda;
    sf::Color _corTexto;


    void inicializar ();

public:
    // construtor
    Texto (sf::Font fonte, std::string informacao, unsigned int tamanhoFonte);
    
    // destrutor
    ~Texto ();

    // getters e setters
    sf::Text get_texto ();
    void set_posicao (sf::Vector2f posicao);
    sf::Vector2f get_posicao ();
    sf::Vector2f get_tamanho ();
    std::string get_informacao ();
    void set_tamanhoBorda (float tamanhoBorda);
    void set_corTexto (sf::Color corTexto);
    void set_tamanhoFonte (unsigned int tamanhoFonte);
    void set_informacao (std::string informacao);
    void set_espacamento (float tamanhoEspaco);


    
};

#endif