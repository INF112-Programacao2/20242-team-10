#ifndef GERENCIADORGRAFICO_H
#define GERENCIADORGRAFICO_H
#include <SFML/Graphics.hpp>
#include "camera.h"
// gerencia todas as coisas relacionadas ao grafico, janela, texturas, sprites ...

#define TAMANHO_TELA_X 1200.0f
#define TAMANHO_TELA_Y 800.0f

class GerenciadorGrafico {
private:
    sf::RenderWindow* _janela;
    Camera _camera;
    sf::Clock _relogio;
    static float _tempo;

    static GerenciadorGrafico* _grafico;
    GerenciadorGrafico();                        // construtora privada para garantir que apenas um gerenciador sera criado, apenas 1 objeto

public:
    // destrutor
    ~GerenciadorGrafico();
    // getters e setters
    static GerenciadorGrafico* get_grafico();
    sf::RenderWindow* get_janela();
    float get_tempo () const;
    sf::View get_camera();
    void set_limiteCamera (sf::IntRect limiteCamera);
    void set_limiteObjeto (sf::IntRect objeto);
    // metodos da classe
    void limparJanela();
    void desenhar(sf::RectangleShape desenho);
    void mostrarNaTela ();
    void fecharJanela();
    sf::Texture carregarTextura(const char* textura);
    const bool janelaEstaAberta();
    void resetarRelogio ();
    void atualizaCamera (sf::Vector2f posicaoJogador);
    
};


#endif