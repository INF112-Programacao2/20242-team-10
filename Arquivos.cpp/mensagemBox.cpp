#include "mensagemBox.h"

// construtor
MensagemBox::MensagemBox(sf::Font &fonte, sf::Vector2f posicao, sf::Vector2f tamanho) :
    _posicao (posicao) ,
    _tamanho (tamanho) ,
    visivel (false),
    gGrafico(gGrafico->get_grafico())
{
    // configuracoes da caixa de mensagem 
    _caixa.setPosition (_posicao);
    _caixa.setSize(_tamanho);
    _caixa.setFillColor (sf::Color(0,0,0,200));             // fundo semi transparente
    _caixa.setOutlineThickness (2.0f);
    _caixa.setOutlineColor (sf::Color::White);

    // configuracoes do texto
    _texto = new Texto (fonte,"",20);
    _texto->set_posicao (sf::Vector2f(_posicao.x + 10.0f, _posicao.y + 10.0f));
    _texto->set_corTexto(sf::Color::White);
}

MensagemBox::~MensagemBox()
{
    if (_texto){
        delete _texto;
        _texto = nullptr;
    }
}

void MensagemBox::set_visivel(bool visivel)
{
    this->visivel = visivel;
}

bool MensagemBox::temMensagem()
{
    return !_mensagens.empty();
}

bool MensagemBox::estaVisivel()
{
    return visivel;
}

void MensagemBox::adicionarMensagem(const std::string &mensagem)
{
    _mensagens.push(mensagem);
    if (!visivel && temMensagem ()){
        visivel = true;
        _texto->set_informacao(_mensagens.front());
    }
}

void MensagemBox::proximaMensagem()
{
    if (temMensagem()){
        _mensagens.pop();
        if (temMensagem()){
            _texto->set_informacao(_mensagens.front());
            
        } else {
                visivel=false;
        }
        
    }
}

void MensagemBox::atualizar()
{
    // animacoes ou efeitos
}

void MensagemBox::desenhar(sf::RenderWindow &janela)
{
    if (visivel) {                                                      // utilizar o gerenciador grafico para isso
        gGrafico->desenhar(_caixa);
        gGrafico->desenhar(_texto->get_texto());
    }
}
