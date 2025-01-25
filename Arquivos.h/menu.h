#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu{
private:
    std::vector<sf::Text> _opcoes;
    int _opcaoSelecionada;
    sf::Font _fonte;
    sf::RenderWindow* _janela;
    bool _estaAtivo;

public:
    Menu(sf::RenderWindow* window);
    ~Menu();
    
    void desenhar();
    void moverCima();
    void moverBaixo();
    int get_Pressionar() const;
    bool get_EstaAtivo() const;
    void set_EstaAtivo(bool ativo);
};
#endif