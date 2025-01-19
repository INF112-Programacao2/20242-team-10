#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include <SFML/Graphics.hpp>
#include "entidade.h"
#include "animacao.h"
#include "experiencia.h"
#include "texto.h"


#define GRAVIDADE  0.0004f               // positiva, pois o eixo y e invertido na biblioteca em uso
#define NIVEL_DA_PLATAFORMA 550.0f

#define TAMANHO_BARRA_VIDA_EIXO_X 60.0f
#define TAMANHO_BARRA_VIDA_EIXO_Y 6.0f

#define TEMPO_RECUPERACAO_DANO 0.5f
#define TEMPO_RECUPERACAO_DANO_ESQUELETO 1.8f
#define TEMPO_PROTECAO_JOGADOR 1.0f  // Tempo de protecao após tomar dano

// Em personagem.h
class Arma;  // Forward declaration

class Personagem : public Entidade {
protected:
    sf::Vector2f _velocidade;
    sf::RectangleShape _barraVida;
    Experiencia _experiencia;
    Arma* _arma;
    Animacao _animacao;
    bool andando;
    bool andaEsquerda;
    bool levandoDano;
    bool atacando;
    bool morrendo;
    //bool estaAtacando;
    float _vidaMaxima;
    float _vida;
    float deltaTempo;
    float _duracaoAnimacaoMorte;
    float _tempoMorte;
    float _tempoDano;
    float _duracaoAnimacaoSofrerDano;


    float _tempoProtecaoAtaque;         // tempo que o inimigo fica protegido de outro ataque (evita que chame a funcao tomardano varias vezes em apenas um ataque )
    bool _protegido;                    // sinaliza se ele esta protegido de levar um ataque 

    Texto _textoNivel;


    // metodos privados para evitar de serem chamados de qualquer lugar do programa
    virtual void inicializarAnimacao () = 0;
    virtual void atualizarAnimacao () = 0;
    virtual void inicializarBarraVida() = 0;
    virtual void atualizarBarraVida();
    virtual void inicializarNivel () = 0;
    virtual void atualizarNivel ();
    
public:
    // construtor
    Personagem (sf::Vector2f posicao,sf::Vector2f tamanho,sf::Vector2f velocidade, Identificador id, float duracaoMorte , float duracaoSofrerDano);
    // destrutor
    virtual ~Personagem ();
    // getters e setters
    sf::Vector2f get_velocidade();
    bool estaAndandoParaEsquerda ();
    void set_velocidade(sf::Vector2f velocidade);
    bool estaMorrendo();
    bool estaAtacando() const;
    float get_forca();
    bool estaLevandoDano();
    void set_arma (Arma* arma);
    Arma* get_arma ();
    void set_protegido (bool protegido);
    bool get_protegido ();
    float get_tempoProtecaoAtaque ();
    void set_duracaoAnimacaoMorte (float duracao);
    // metodos virtuais
    virtual void atualizar() = 0;
    virtual void desenhar();
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia) = 0;
    virtual void atacar(bool atacando);
    virtual void atualizarPosicao () = 0;
    virtual void tomarDano(float dano);
    // metodos da classe
    void andar(bool andaEsquerda);
    void parar();
    void atualizarTomarDano ();

    void atualizarTempoProtegido ();



};

#endif  