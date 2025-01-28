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
     if (!personagem) return;

    sf::Vector2f posicaoPersonagem = personagem->get_posicao();
    sf::Vector2f velocidadePersonagem = personagem->get_velocidade();
    sf::Vector2f tamanhoPersonagem = personagem->get_tamanho();

    // Verifica se a colisão é mais forte no eixo X ou Y
    if (fabs(distancia.x) < fabs(distancia.y)) {
        // Colisão horizontal
        if (posicaoPersonagem.x < _posicao.x) {
            posicaoPersonagem.x = _posicao.x - tamanhoPersonagem.x;
        } else {
            // Personagem está à direita
            posicaoPersonagem.x = _posicao.x + _tamanho.x;
        }
    } else {
        // Colisão vertical
        if (posicaoPersonagem.y < _posicao.y) {
            // Personagem está acima
            posicaoPersonagem.y = _posicao.y - tamanhoPersonagem.y;
            // Permite pulo se for jogador
            if (personagem->get_id() == Identificador::jogador) {
                Jogador* jogador = dynamic_cast<Jogador*>(personagem);
                if (jogador) {
                    jogador->podePular();
                }
            }
        } else {
            // Personagem está abaixo
            posicaoPersonagem.y = _posicao.y + _tamanho.y;
        }
    }

    personagem->set_posicao(posicaoPersonagem);
    
    
    
    
    
    /*
     if (!personagem) return;

    sf::Vector2f posicaoPersonagem = personagem->get_posicao();
    sf::Vector2f velocidadePersonagem = personagem->get_velocidade();
    sf::Vector2f tamanhoPersonagem = personagem->get_tamanho();

    // Verifica se a colisão é mais forte no eixo X ou Y
    if (fabs(distancia.x) < fabs(distancia.y)) {
        // Colisão horizontal
        if (posicaoPersonagem.x < _posicao.x) {
            posicaoPersonagem.x = _posicao.x - tamanhoPersonagem.x;
        } else {
            // Personagem está à direita
            posicaoPersonagem.x = _posicao.x + _tamanho.x;
        }
    } else {
        // Colisão vertical
        if (posicaoPersonagem.y < _posicao.y) {
            // Personagem está acima
            posicaoPersonagem.y = _posicao.y - tamanhoPersonagem.y;
            // Permite pulo se for jogador
            if (personagem->get_id() == Identificador::jogador) {
                Jogador* jogador = dynamic_cast<Jogador*>(personagem);
                if (jogador) {
                    jogador->podePular();
                }
            }
        } else {
            // Personagem está abaixo
            posicaoPersonagem.y = _posicao.y + _tamanho.y;
        }
    }

    personagem->set_posicao(posicaoPersonagem);
    */
}


