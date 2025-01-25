#ifndef MENSAGEMBOX_H
#define MENSAGEMBOX_H

#include "texto.h"
#include "gerenciadorgrafico.h"
#include <queue>

class MensagemBox
{

private:
    GerenciadorGrafico* gGrafico;
    sf::RectangleShape _caixa;
    Texto* _texto;
    std::queue <std::string> _mensagens;
    sf::Clock _relogio;
    //sf::Vector2f _posicao;
    //sf::Vector2f _tamanho;
    float _tempoExibicao;
    bool visivel;


public:
    // construtor
    MensagemBox(sf::Font& fonte, sf::Vector2f posicao, sf::Vector2f tamanho);
    // destrutor
    ~MensagemBox();
    // getters e setters
   // void set_visivel (bool visivel);
    bool temMensagem ();
    bool estaVisivel ();

    // metodos da classe
    void limparMensagens ();
    void adicionarMensagem (const std::string& mensagem);
    void proximaMensagem ();
    void atualizar();
    void desenhar (sf::RenderWindow& janela);

};

#endif