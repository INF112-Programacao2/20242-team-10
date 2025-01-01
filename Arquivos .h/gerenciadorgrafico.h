#ifndef GERENCIADORGRAFICO_H
#define GERENCIADORGRAFICO_H
#include <SFML/Graphics.hpp>
// gerencia todas as coisas relacionadas ao grafico, janela, texturas, sprites ...

class GerenciadorGrafico {
private:
    sf::RenderWindow* _janela;
    static GerenciadorGrafico* _grafico;
    GerenciadorGrafico();                        // construtora privada para garantir que apenas um gerenciador sera criado, apenas 1 objeto
public:
    ~GerenciadorGrafico();
    static GerenciadorGrafico* get_grafico();
    sf::RenderWindow* get_janela();
    void limparJanela();
    void desenhar(sf::RectangleShape desenho);
    void mostrarNaTela ();
    void fecharJanela();
    const bool janelaEstaAberta();
};


#endif