#include "mensagemBox.h"
#include <iostream>

// construtor
MensagemBox::MensagemBox(sf::Font &fonte, sf::Vector2f posicao, sf::Vector2f tamanho) :
    _tempoExibicao(5.0f),
    visivel(true), // Force visível inicialmente para debug
    gGrafico(gGrafico->get_grafico())
{
    _caixa.setPosition(posicao);
    _caixa.setSize(tamanho);
    _caixa.setFillColor(sf::Color(0, 0, 0, 200));
    _caixa.setOutlineThickness(2.0f);
    _caixa.setOutlineColor(sf::Color::White);

    _texto = new Texto(fonte, "Texto Teste", 20); // Texto teste para debug
    _texto->set_posicao(sf::Vector2f(posicao.x + 10.0f, posicao.y + 10.0f));
    std::cout << "Mensagem box criada com posição: " << posicao.x << ", " << posicao.y << std::endl;
}

MensagemBox::~MensagemBox()
{
    if (_texto){
        delete _texto;
        _texto = nullptr;
    }
}

/*void MensagemBox::set_visivel(bool visivel)
{
    this->visivel = visivel;
}*/

bool MensagemBox::temMensagem()
{
    return (!_mensagens.empty() || visivel);
}

bool MensagemBox::estaVisivel()
{
    return visivel;
}

void MensagemBox::limparMensagens()
{
     while (!_mensagens.empty ()) {
        _mensagens.pop();
     }
}

void MensagemBox::adicionarMensagem(const std::string &mensagem)
{
        std::cout << "Adicionando mensagem: " << mensagem << std::endl;
    _mensagens.push(mensagem);
   if (!visivel){  
    proximaMensagem(); 
   }
}

void MensagemBox::proximaMensagem()
{
    if (!_mensagens.empty()){
        _texto->set_informacao (_mensagens.front());
        _mensagens.pop();
        visivel = true;
        _relogio.restart();
        } else {
            visivel=false;
        }
        
}


void MensagemBox::atualizar()
{
    if (visivel && _relogio.getElapsedTime().asSeconds() >= _tempoExibicao) {
        proximaMensagem ();
    }
}

void MensagemBox::desenhar(sf::RenderWindow &janela)
{ 
        if (visivel) {
        sf::RectangleShape debugRect = _caixa;
        debugRect.setFillColor(sf::Color::Red); // Cor visível para debug
        gGrafico->desenhar(debugRect);
        gGrafico->desenhar(_texto->get_texto());
        std::cout << "Desenhando na posição: " << _caixa.getPosition().x << ", " << _caixa.getPosition().y << std::endl;
    }
    /*
        std::cout << "Desenhando mensagem, visível: " << visivel << std::endl;
    if (visivel) {                                                      // utilizar o gerenciador grafico para isso
        gGrafico->desenhar(_caixa);
        gGrafico->desenhar(_texto->get_texto());
    }
    */
}
