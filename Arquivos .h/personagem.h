#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include <SFML/Graphics.hpp>
#include "entidade.h"
#include "animacao.h"

#define GRAVIDADE  0.0004f               // positiva, pois o eixo y e invertido na biblioteca em uso
#define NIVEL_DA_PLATAFORMA 500.0f

class Personagem : public Entidade {
protected:
    sf::Vector2f _velocidade;
    sf::RectangleShape _barraVida;
    Animacao _animacao;
    bool andando;
    bool andaEsquerda;
    bool levandoDano;
    bool atacando;
    bool morrendo;
    //bool estaAtacando;
    float vidaMaxima;
    float deltaTempo;

    // metodos privados para evitar de serem chamados de qualquer lugar do programa, metodos da barra de vida
    //virtual void inicializarBarraVida();
    //virtual void atualizarBarraVida();
    
public:
    // construtor
    Personagem (const sf::Vector2f posicao, const sf::Vector2f tamanho,sf::Vector2f velocidade, Identificador id);
    // destrutor
    virtual ~Personagem ();
    // getters e setters
    sf::Vector2f get_velocidade();
    void set_velocidade(sf::Vector2f velocidade);
    bool estaMorrendo();
    bool estaAtacando() const;
    // metodos virtuais
    virtual void atualizar() = 0;
    virtual void desenhar(sf::RectangleShape desenho);
    // metodos da classe
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia) = 0;
    void andar(bool andaEsquerda);
    void parar();
    virtual void atacar(bool atacando);
    virtual void atualizarPosicao ();

};

#endif  