#ifndef PORTA_H
#define PORTA_H

#include "obstaculo.h"
#include "texto.h"



#define TEMPO_ABERTURA_PORTA 1.4f
#define TEMPO_ENTRADA_NA_PORTA 1.0f


class Jogador;

class Porta : public Obstaculo {
private:

    bool _fechada;
    bool _abrindo;
    bool _completou;
    float _tempoAberturaPorta;
    Animacao _animacao;
    Texto _textoPorta;
    sf::RectangleShape caixaTexto;
    bool _mostrarTexto;

    
    void inicializarAnimacao ();
    void atualizarAnimacao();
    void inicializarTexto (std::string texto);

public:
    // construtor
    Porta (sf::Vector2f posicao, sf::Vector2f tamanho, Identificador id);
    // destrutor
    ~Porta ();
    // getters e setters
    bool estaFechada ();
    bool completouTransicao () const;
    // metodos da classe
    void colisaoJogador (Jogador* jogador);
    void colisao (Entidade* entidade , sf::Vector2f distancia);
    void desenhar ();
    void atualizar ();
};



#endif