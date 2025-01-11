#include "obstaculo.h"

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
    // verifica se nao houver colisao, caso ambos os eixos nao sejam negativos, indica que nao ha sobreposicao, ou seja, que nao estao se colidindo
    if (distancia.x >= 0.0f || distancia.y >= 0.0f) {
        return;
    }

    sf::Vector2f posicaoPersonagem = personagem->get_posicao();
    sf::Vector2f velocidadePersonagem = personagem->get_velocidade();

    // verifica em qual eixo a colisao ocorre mais, ou seja, em qual eixo houve maior sobreposicao e retorna qual eixo possui a menor colisao 
    bool colisaoEixo_x = abs(distancia.x) < abs(distancia.y);

    // resolve as colisoes
    if (colisaoEixo_x){ 
        if (posicaoPersonagem.x < _posicao.x){                                  // indica que o persongem esta a esquerda do obstaculo
            posicaoPersonagem.x += distancia.x;                                 // move o personagem para a esquerda
        }
        else {                                                                  // indica que o personagem esta a direita do obstaculo
            posicaoPersonagem.x -= distancia.x;                                 // move o personagem para a direita 
        }
        velocidadePersonagem.x = 0.0f;                                          // o personagem para 
    }
    else {
        if (posicaoPersonagem.y < _posicao.y) {                                 // indica que o personagem esta acima do obstaculo       
            posicaoPersonagem.y += distancia.y;                                 // move o personagem para cima
            if (personagem->get_id() == Identificador::jogador){                // se esse personagem for um jogador
                Jogador* jogador = dynamic_cast < Jogador* > (personagem);
                jogador->podePular();                                           // sinaliza que ele pode pular pois nao tem nada acima
            }
        else {                                                                  // indica que o personagem esta abaixo do obstaculo
            posicaoPersonagem.y -= distancia.y;                                 // move o personagem para baixo
        }
        velocidadePersonagem.y = 0.0f;                                          // o personagem para 
    }

    // atualiza os atibutos do personagem
    personagem->set_posicao(posicaoPersonagem); 
    personagem->set_velocidade(velocidadePersonagem);

}


