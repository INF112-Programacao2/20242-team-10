#include "animacao.h"

// construtor
Animacao::Animacao(sf::RectangleShape* corpo) :
    _corpo (corpo) , mapaImagem () , _imagemAtual (""), _relogio() {}

// destrutor
Animacao::~Animacao()
{
    for (auto& par : mapaImagem) {
        delete par.second;
    }
    mapaImagem.clear();
}

bool Animacao::animacaoCompleta() const
{
        // Verifica se existe uma animação atual
    auto it = mapaImagem.find(_imagemAtual);
    if (it != mapaImagem.end() && it->second != nullptr) {
        Imagem* img = it->second;
        // Verifica se o frame atual é o último frame
        return img->get_frameAtual() >= (img->get_quantidadeFrames() - 1);
    }
    return false;
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

    if (_imagemAtual != imagemAtual) {                          // se a imagem atual for diferente da imagem passada no parametro
        if (!_imagemAtual.empty()) {                           
            auto iterator = mapaImagem.find(_imagemAtual);      // procura pela imagem antiga
            if (iterator != mapaImagem.end()) {
                iterator->second->resetar();                    // reseta 
            }
        }
        _imagemAtual = imagemAtual;                                 // atualiza a nova imagem
    }
    
    float tempo = _relogio.restart().asSeconds();                   // pega o tempo em segundos
    
    auto iterator = mapaImagem.find(_imagemAtual);
    if (iterator != mapaImagem.end()) {                             // procura pela imagem atual (atualizada)
        Imagem* img = iterator->second;

        // atualiza o estado e as dimensoes 
        img->atualizar(direcao, tempo);
        _corpo->setTextureRect(img->get_tamanho());
        _corpo->setTexture(img->get_textura());
        _corpo->setOrigin(img->get_origem());
        _corpo->setScale(img->get_escala());
    }

}

// funcao que adiciona uma nova animacao no jogo
void Animacao::adicionarAnimacao(const char *textura, std::string nome, unsigned int quantidadeImagens, float tempoTroca, sf::Vector2f escala, sf::Vector2f origem, bool horizontal)
{   
    Imagem* novaImagem = new Imagem ( textura , quantidadeImagens , tempoTroca , escala , origem , horizontal);        // cria uma nova imagem
    mapaImagem.insert (std::pair < std::string , Imagem* > (nome, novaImagem));                                        // insere essa nova imagem e seu nome (no caso, um estado) no mapa de imagens
}   
