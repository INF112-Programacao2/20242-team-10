#include "jogador.h"

// construtor que usa o construtor de Personagem
Jogador::Jogador (const sf::Vector2f posicao, const sf::Vector2f tamanho) :
    Personagem (posicao,tamanho) 
    {
        inicializarVelocidade ();
    }

// destrutor
Jogador::~Jogador () {

}

// funcao que inicializa a velocidade do jogador            
void Jogador::inicializarVelocidade () {
    _velocidade = sf::Vector2f (0.1f,0.1f);
}

// funcao que movimenta o jogador para as quatro direcoes
void Jogador::movimentar () {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {          // se a tecla pressionada for A ou seta para esquerda, move para esquerda
        _corpo.move(-_velocidade.x,0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){     // se a tecla pressionada for D ou seta para direita, move para direita
        _corpo.move(+_velocidade.x,0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){        // se a tecla pressionada for W ou seta para cima, move para cima
        _corpo.move(0.0f,-_velocidade.y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){      // se a tecla pressionada for S ou seta para baixo, move para baixo
        _corpo.move(0.0f,+_velocidade.y);
    }
}