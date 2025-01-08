#include "imagem.h"

Imagem::Imagem(const char *textura, unsigned int quantidadeFrames, float tempoTroca, sf::Vector2f escala, sf::Vector2f origem, bool horizontal) :
    gGrafico(gGrafico->get_grafico()), _quantidadeFrames(quantidadeFrames) , _tempoTroca(tempoTroca) , _tempoTotal (0.0f),
    _tamanho(0,0,0,0), _frameAtual (0), _textura (gGrafico->carregarTextura(textura)), _escala (escala), _origem (origem) , horizontal(horizontal)
{
    if (horizontal) {
        _tamanho.width = _textura.getSize().x / (float) _quantidadeFrames;   // divide o comprimento do sprite todo pela quantidade de imagens que tem, para saber o comprimento de 1 imagem
        _tamanho.height = _textura.getSize().y;
    }
    else {
        _tamanho.width = _textura.getSize().x;
        _tamanho.height = _textura.getSize().y / (float) _quantidadeFrames; // divide a altura do sprite todo pela quantidade de imagens que tem, para saber a altura de 1 imagem
    }

}

Imagem::~Imagem()
{

}

unsigned int Imagem::get_quantidadeFrames()
{
    return this->_quantidadeFrames;
}

unsigned int Imagem::get_frameAtual()
{
    return this->_frameAtual;
}

void Imagem::set_frameAtual(unsigned int frameAtual)
{
    this->_frameAtual = frameAtual;
}

float Imagem::get_tempoTotal()
{
    return this->_tempoTotal;
}

void Imagem::set_tempoTotal(float tempoTotal)
{
    this->_tempoTotal = tempoTotal;
}

sf::Vector2f Imagem::get_escala()
{
    return this->_escala;
}

sf::Vector2f Imagem::get_origem()
{
    return this->_origem;
}

sf::IntRect Imagem::get_tamanho()
{
    return this->_tamanho;
}

sf::Texture* Imagem::get_textura()
{
    return &_textura;
}

void Imagem::resetar()
{
    _frameAtual = 0;
    _tempoTotal = 0.0f;
}

void Imagem::atualizarFrame(float tempo)
{
    _tempoTotal += tempo;
    if (_tempoTotal >= _tempoTroca){
        _tempoTotal -= _tempoTroca;
        _frameAtual++;
        if (_frameAtual >= _quantidadeFrames)
            _frameAtual = 0;
    }
}

void Imagem::atualizar(Direcao direcao, float tempo)
{
    atualizarFrame(tempo);                          // atualiza a o frame de acordo com o tempo

    // verifica qual o sentido do sprite e ajusta o recorte de acordo com o sentido e direcao desse sprite
    if (horizontal)                                 
        ajustarRecorteHorizontal(direcao);           
    else 
        ajustarRecorteVertical(direcao);

}

void Imagem::ajustarRecorteHorizontal(Direcao direcao)
{
    if (direcao == Direcao::ESQUERDA) {
        _tamanho.width = -std::abs (_tamanho.width);                        // inverte a imagem (espelha)
        _tamanho.left = (_frameAtual + 1) * std::abs (_tamanho.width);     // frameAtual + 1 para garantir que esta no frame correto apos a inversao
    }
    else {
        // mantem normal, sem espelhamento
        _tamanho.width = std::abs (_tamanho.width);                      // mantem normal, sem espelhar o sprite   
        _tamanho.left = _frameAtual * _tamanho.width;                   // recorta no inicio do frame da imagem atual
    }
}

void Imagem::ajustarRecorteVertical(Direcao direcao)
{
    _tamanho.top = _frameAtual * _tamanho.width;         // ajusta a linha que esta baseado no frame atual
    if (direcao == Direcao::ESQUERDA) {
        _tamanho.width = -std::abs (_tamanho.width);        // inverte o sprite (espelha)
        _tamanho.left = std::abs (_tamanho.width);          // recorta no tamanho da largura
    }
    else {
        _tamanho.width = std::abs(_tamanho.width);          // mantem normal, sem espelhar o sprite
        _tamanho.left = 0.0f;                               // recorta no primeiro frame
    }       
}
