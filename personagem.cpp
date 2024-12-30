#include "personagem.h"

// primeiro construtor 
Personagem::Personagem (const sf::Vector2f posicao, const sf::Vector2f tamanho) :
    _corpo (sf::RectangleShape (tamanho))                                             // criar um corpo com algum tamanho
    {
        _corpo.setPosition (posicao); _corpo.setFillColor (sf::Color::Red);           // indica a posicao e a cor desse corpo
        inicializaVelocidade();                                                       // inicializa a velocidade do corpo
    } 

// segundo construtor
Personagem::Personagem (const sf::RectangleShape corpo) : 
    _corpo(corpo)                                                                     // ja recebe um corpo
    {
        inicializaVelocidade();                                                       // incializa a velocidade desse corpo
    }

// terceiro construtor
Personagem::Personagem () :                                                           // nao recebe parametros
    _corpo()                                                                          // cria um corpo vazio
    {
        inicializaVelocidade();
    }

// funcao que inicializa a velocidade do personagem
void Personagem::inicializaVelocidade () {
    _velocidade = sf::Vector2f (0.1f,0.1f);              // velocidade igual a 0.1 no eixo X e Y
}

// funcao que retornna o corpo
const sf::RectangleShape Personagem::get_corpo () {
    return this->_corpo;
}

// funcao que movimenta o persongame para as quatro direcoes
void Personagem::movimentar () {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {              // se a tecla pressionada for A ou seta para esquerda, move para esquerda
        _corpo.move(-_velocidade.x,0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){         // se a tecla pressionada for D ou seta para direita, move para direita
        _corpo.move(+_velocidade.x,0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){            // se a tecla pressionada for W ou seta para cima, move para cima
        _corpo.move(0.0f,-_velocidade.y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){          // se a tecla pressionada for S ou seta para baixo, move para baixo
        _corpo.move(0.0f,+_velocidade.y);
    }
}

// destrutor
    Personagem::~Personagem () {

    }



