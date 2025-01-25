#ifndef JOGADOR_H
#define JOGADOR_H
#include "personagem.h"


#define TAMANHO_PULO -0.80f                             // negativa pois o eixo y é invertido na biblioteca (para subir = valores negativos)
#define DURACAO_ATAQUE_TOTAL 0.6f                         // sao 6 frames de ataque e o tempo de troca entre eles = 0.1f
#define TAMANHO_JOGADOR_X 50.0f   
#define TAMANHO_JOGADOR_Y 90.0f
#define VELOCIDADE_JOGADOR_X 0.35f
#define VELOCIDADE_JOGADOR_Y 0.0f

#define DURACAO_JOGADOR_MORTE 1.0f
#define DURACAO_JOGADOR_SOFRER_DANO 0.3f

#define DANO_JOGADOR 35.0f
#define DEFESA_JOGADOR 30.0f
#define FORCA_JOGADOR 20.0f

class Jogador : public Personagem {
private:
    bool estaNoChao;
    bool _congelaJogo;


    sf::RectangleShape _tuboBarraVida;
    sf::RectangleShape _tuboBarraXP;
    sf::RectangleShape _barraXP;
    
    Texto _textoXP;


    // metodos responsaveis pela animacao do jogador 
    void inicializarAnimacao ();
    void atualizarAnimacao ();
    // metodos responsaveis pela animacao barra de vida do jogador 
    void inicializarBarraVida ();
    void atualizarBarraVida ();
    // metodos responsaveis pela animacao do nivel do jogador 
    void inicializarNivel (); 
    void atualizarNivel ();
    void resetarEstado ();
    // metodos responsaveis pela experiencia do jogador 
    void inicializarBarraXP ();
    void atualizarBarraXP ();
    void inicializarXP ();
    void atualizarXP();



public:
    // construtor
    Jogador (sf::Vector2f posicao);
    // destrutor
    ~Jogador();
    // getters e setters
    bool get_estaNoChao ();
    bool estaAndando ();
    bool estaCongeladoJogo ();
    void set_vida (float vida);
    void adicionarXP (float experiencia);
    // metodos da classe
    //void tomarDano(float dano);
    void pular ();
    void podePular ();
    virtual void colisao (Entidade* entidade,sf::Vector2f distancia);
    virtual void atacar(bool atacar) override;
    virtual void atualizar() override;                                  // esquerda ou direita
    virtual void atualizarPosicao () override;
    void desenhar ();
};


#endif