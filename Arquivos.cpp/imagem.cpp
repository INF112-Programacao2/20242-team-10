#include "imagem.h"
// cosntrutor
Imagem::Imagem(const char *textura, unsigned int quantidadeFrames, float tempoTroca, sf::Vector2f escala, sf::Vector2f origem, bool horizontal) :
    gGrafico(gGrafico->get_grafico()),
    _quantidadeFrames(quantidadeFrames),
    _tempoTroca(tempoTroca),
    _tempoTotal (0.0f),
    _tamanho(0,0,0,0),
    _frameAtual (0),
    _textura (gGrafico->carregarTextura(textura)),
    _escala (escala),
    _origem (origem),
    horizontal(horizontal)
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

// destrutor
Imagem::~Imagem()
{

}

// funcao que retorna a quantidade de frames 
unsigned int Imagem::get_quantidadeFrames()
{
    return this->_quantidadeFrames;
}

// funcao que retorna o frame atual
unsigned int Imagem::get_frameAtual()
{
    return this->_frameAtual;
}

// funcao que atualiza o frame atual
void Imagem::set_frameAtual(unsigned int frameAtual)
{
    this->_frameAtual = frameAtual;
}

// funcao que retorna o tempo total das trocas de frame
float Imagem::get_tempoTotal()
{
    return this->_tempoTotal;
}

// funcao que atualiza o tempo total das trocas de frame
void Imagem::set_tempoTotal(float tempoTotal)
{
    this->_tempoTotal = tempoTotal;
}

// funcao que retorna a escala
sf::Vector2f Imagem::get_escala()
{
    return this->_escala;
}

// funcao que retorna a origem
sf::Vector2f Imagem::get_origem()
{
    return this->_origem;
}

// funcao que retorna o tamanho da imagem
sf::IntRect Imagem::get_tamanho()
{
    return this->_tamanho;
}

// funcao que retorna a textura
sf::Texture* Imagem::get_textura()
{
    return &_textura;
}

// funcao que reseta a imagem para o primeiro frame
void Imagem::resetar()
{
    _frameAtual = 0;
    _tempoTotal = 0.0f;
}

// funcao que atualiza os frames da imagem
void Imagem::atualizarFrame(float tempo)
{
    _tempoTotal += tempo;
    if (_tempoTotal >= _tempoTroca){                                    // se passar do tempo de troca
        _tempoTotal -= _tempoTroca;                                     // desconta do tempo total
        _frameAtual++;                                                  // passa para o proximo frama
        if (_frameAtual >= _quantidadeFrames)                           // se chegar ate o ultimo frame, recomeca
            _frameAtual = 0;
    }
}

// funcao que atualiza a imagem
void Imagem::atualizar(Direcao direcao, float tempo)
{
    atualizarFrame(tempo);                          // atualiza a o frame de acordo com o tempo

    // verifica qual o sentido do sprite e ajusta o recorte de acordo com o sentido e direcao desse sprite
    if (horizontal)                                 
        ajustarRecorteHorizontal(direcao);           
    else 
        ajustarRecorteVertical(direcao);

}

// funcao que ajusta a imagem horizontalmente
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

// funcao que ajusta verticalmente
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
