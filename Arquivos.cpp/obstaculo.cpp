#include "obstaculo.h"
#include "jogador.h"


// construtor
Obstaculo::Obstaculo(sf::Vector2f posicao, sf::Vector2f tamanho, Identificador id) :
    Entidade (posicao,tamanho,id) {}

// destrutor
Obstaculo::~Obstaculo()
{
}

// funcao que desenha o obstaculo na tela
void Obstaculo::atualizar()
{
        desenhar();
}

// funcao que verifica a colisao do personagem com os obstaculos
void Obstaculo::colisaoObstaculo(sf::Vector2f distancia, Personagem *personagem)
{
     if (!personagem) return;                                       // verifica se o personagem nao e nulo

    // pega a posicao, velocidade e tamanho do personagem
    sf::Vector2f posicaoPersonagem = personagem->get_posicao();
    sf::Vector2f velocidadePersonagem = personagem->get_velocidade();
    sf::Vector2f tamanhoPersonagem = personagem->get_tamanho();

    // verifica se a colisao é mais forte no eixo X ou Y (onde ha mais sobreposicao)
    if (fabs(distancia.x) < fabs(distancia.y)) {
        // Colisão horizontal
        if (posicaoPersonagem.x < _posicao.x) {                                                     // se o personagem estiver a esquerda do obstaculo
            posicaoPersonagem.x = _posicao.x - tamanhoPersonagem.x;                                 // atualiza a posicao
        } else {
            // se o personagem estiver a direita
            posicaoPersonagem.x = _posicao.x + _tamanho.x;                                          // atualiza a posicao
        }
    } else {
        // Colisão vertical
        if (posicaoPersonagem.y < _posicao.y) {
            // se o personagem estiver acima
            posicaoPersonagem.y = _posicao.y - tamanhoPersonagem.y;       // atuializa a posicao
            // permite pular se for jogador
            if (personagem->get_id() == Identificador::jogador) {
                Jogador* jogador = dynamic_cast<Jogador*>(personagem);
                if (jogador) {
                    jogador->podePular();
                }
            }
        } else {
            // se estiver abaixo
            posicaoPersonagem.y = _posicao.y + _tamanho.y;   // atualiza a posicao
        }
    }

    // atribui a nova posicao
    personagem->set_posicao(posicaoPersonagem);
    
}


