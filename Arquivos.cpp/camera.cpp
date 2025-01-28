#include "camera.h"

// funcao que ajusta o centro da camera
void Camera::ajustarCentro(sf::Vector2f &novoCentro)

{
    // pega a metada do largura e da altura da janela
    float metadeLargura = _tamanhoJanela.x / 2.0f;
    float metadeAltura = _tamanhoJanela.y / 2.0f;

    // limita horizontalmente
    if (novoCentro.x - metadeLargura < _limiteCamera.left) {
        novoCentro.x = _limiteCamera.left + metadeLargura;                                                  // ajusta o limite pela esquerda
    } else if (novoCentro.x + metadeLargura > _limiteCamera.left + _limiteCamera.width) {
        novoCentro.x = _limiteCamera.left + _limiteCamera.width - metadeLargura;                            // ajusta o limite pela direita
    }

    // limita verticalmente
    if (novoCentro.y - metadeAltura < _limiteCamera.top) {                                                       
        novoCentro.y = _limiteCamera.top + metadeAltura;                                                        // ajusta o limite no topo
    } else if (novoCentro.y + metadeAltura > _limiteCamera.top + _limiteCamera.height) {
        novoCentro.y = _limiteCamera.top + _limiteCamera.height - metadeAltura;                                 // ajusta o limite embaixo
    }
}

       // construtor
       Camera::Camera(sf::Vector2f tamanhoJanela) : 
        _tamanhoJanela(tamanhoJanela)
       {
            // atualiza o tamanho da janela e do centro
           _camera.setSize(tamanhoJanela);
           _camera.setCenter(tamanhoJanela.x / 2.0, tamanhoJanela.y / 2.0);

           // zona morta comeca com 20% da largura da janela e 30% do altura
           _zonaMorta.width = tamanhoJanela.x * 0.3f;
           _zonaMorta.height = tamanhoJanela.y * 0.2f;

            // inicializa os limites da camera
            _limiteCamera.left = 0;
            _limiteCamera.top = 0;
            _limiteCamera.width = tamanhoJanela.x;
            _limiteCamera.height = tamanhoJanela.y;

        }

// destrutor
Camera::~Camera()
{

}

// funcao que retorna a camera
sf::View Camera::get_camera()
{
    return this->_camera;
}

// funcao que retorna os limites do mapa/fase
void Camera::set_limiteCamera(sf::IntRect limiteCamera)
{
        _limiteCamera = limiteCamera;
    
    // depois de atualizar o centro, chama a funcao para ajusta - lo e garantir que esta enquadrado
    sf::Vector2f centro = _camera.getCenter();
    ajustarCentro(centro);
    _camera.setCenter(centro);
}

// funcao que atualiza a posicao da camera de acordo com que o jogador sai da zona morta
void Camera::atualizar(sf::Vector2f posicaoJogador)
{
    // pega a posicao do centro da camera
    sf::Vector2f centroCamera = _camera.getCenter();
    bool precisaAtualizar = false;
    sf::Vector2f novoCentro = centroCamera;

    // atualiza a posição da zona morta
    _zonaMorta.left = centroCamera.x - _zonaMorta.width / 2.0f;
    _zonaMorta.top = centroCamera.y - _zonaMorta.height / 2.0f;

    // Verifica se o jogador saiu da zona morta
    if (posicaoJogador.x > _zonaMorta.left + _zonaMorta.width) {            // se saiu pela direita
        novoCentro.x = posicaoJogador.x - _zonaMorta.width / 2.0f;          // atualiza a posicao
        precisaAtualizar = true;                                            // sinaliza que a camera precisa mover
    }   
    else if (posicaoJogador.x < _zonaMorta.left) {                          // se saiu pela esquerda
        novoCentro.x = posicaoJogador.x + _zonaMorta.width / 2.0f;
        precisaAtualizar = true;
    }

    if (posicaoJogador.y > _zonaMorta.top + _zonaMorta.height) {            // se saiu por cima
        novoCentro.y = posicaoJogador.y - _zonaMorta.height / 2.0f;
        precisaAtualizar = true;
    }
    else if (posicaoJogador.y < _zonaMorta.top) {                           // se saiu por baixo
        novoCentro.y = posicaoJogador.y + _zonaMorta.height / 2.0f;     
        precisaAtualizar = true;
    }

    // se o jogador saiu da zona morta, atualiza a camera
    if (precisaAtualizar) {
        // ajusta o novo centro para respeitar os limites
        ajustarCentro(novoCentro);
        _camera.setCenter(novoCentro);

    }
}




