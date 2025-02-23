#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>

class Camera {
private:
    sf::View _camera; 
    sf::IntRect _limiteCamera;          // limite do mapa que no caso tambem e o limite da camera, ate onde ela vai
    sf::FloatRect _zonaMorta;           // area onde o jogador se move sem a camera se mover junto
    sf::Vector2f _tamanhoJanela;

    void ajustarCentro (sf::Vector2f& novoCentro);
public:
    // construtor
    Camera (sf::Vector2f tamanhoJanela);

    // destrutor
    ~Camera ();

    // getters e setters
    sf::View get_camera();
    void set_limiteCamera (sf::IntRect novoLimiteMapa);
    
    // metodos da classe
    void atualizar (sf::Vector2f posicaoJogador);
    
};


#endif