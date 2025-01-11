#include "animacao.h"

// construtor
Animacao::Animacao(sf::RectangleShape* corpo) :
    _corpo (corpo) , mapaImagem () , _imagemAtual (""), _relogio() {}

// destrutor
Animacao::~Animacao()
{

}

// funcao que retorna o imagem atual do estado (correndo, atacando, parado...)
std::string Animacao::get_imagemAtual() const
{
    return this->_imagemAtual;
}

// funcao que altera a imagem atual do estado
void Animacao::set_imagemAtual(std::string imagemAtual)
{
    this->_imagemAtual = imagemAtual;
}

// funcao que retorna o frame atual do estado atual (retorna o frame atual do estado atacando por exemplo)
unsigned int Animacao::get_frameAtual()
{
    return mapaImagem[this->_imagemAtual]->get_frameAtual();        // ultiliza o get da funcao imagem
}

// funcao que altera o frame atual do estado atual (altera o frame atual do estado pulando por exemplo)
void Animacao::set_frameAtual(unsigned int frameAtual)
{
    mapaImagem[this->_imagemAtual]->set_frameAtual(frameAtual);     // utiliza o set da funcao imagem
}

// funcao que retorna o tempo total da animacao do estado atual (retorna o tempo total da animacao andar por exemplo)
float Animacao::get_tempoTotal()
{
    return mapaImagem[this->_imagemAtual]->get_tempoTotal();        // utiliza o get da funcao imagem
}

// funcao que altera o tempo total da animacao do estado atual (altera o tempo total da animacao pular por exemplo)
void Animacao::set_tempoTotal(float tempoTotal)
{
    mapaImagem[this->_imagemAtual]->set_tempoTotal(tempoTotal);     // utiliza o set da funcao imagem
}

// funcao que atualiza a animacao do estado atual ( atualiza as animacoes quando o jogador esta atacando o inimigo por exemplo)
void Animacao::atualizar(Direcao direcao, std::string imagemAtual)
{   
    // verifica se o estado atual e igual ao esta do parametro
    if ( _imagemAtual != imagemAtual) {                 // se o estado for diferente, mas existe um estado ocorrendo
        if (_imagemAtual != ""){                        
            mapaImagem[_imagemAtual]->resetar ();       // reseta o estado atual
        }
        _imagemAtual = imagemAtual;                     // atribui o novo estado
    }

    float tempo = _relogio.getElapsedTime().asSeconds();                // pega o tempo atual em segundos
    _relogio.restart();                                                 // reinicia o relogio

    Imagem* img = mapaImagem[_imagemAtual];                             // faz uma copia da imagem do estado atual
    sf::Vector2f tamanhoCorpo = _corpo->getSize();                      // pega o tamanho do corpo da imagem
    sf::Vector2f escala = img->get_escala();                            // pega a escala da imagem

    img-> atualizar (direcao, tempo);                                   // atualiza o frame da copia de acordo com a direcao e sentido 
    _corpo->setTextureRect(img->get_tamanho());                         // seta a textura, origem, escala, tamanho
    _corpo->setTexture(img->get_textura());
    _corpo->setOrigin(img->get_origem());
    _corpo->setScale(escala.x,escala.y);



}

// funcao que adiciona uma nova animacao no jogo
void Animacao::adicionarAnimacao(const char *textura, std::string nome, unsigned int quantidadeImagens, float tempoTroca, sf::Vector2f escala, sf::Vector2f origem, bool horizontal)
{   
    Imagem* novaImagem = new Imagem ( textura , quantidadeImagens , tempoTroca , escala , origem , horizontal);        // cria uma nova imagem
    mapaImagem.insert (std::pair < std::string , Imagem* > (nome, novaImagem));                                        // insere essa nova imagem e seu nome (no caso, um estado) no mapa de imagens
}   
