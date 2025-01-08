#include "camera.h"

        // constutor 
        Camera::Camera(sf::Vector2f tamanhoJanela):
            _limiteCamera(sf::IntRect(-1, -1, -1, -1)), _tamanhoJanela(tamanhoJanela),                       // inicializacao do limite da camera e do objeto iguais, sinalizando que eles estao centralizados, no caso a sinalizacao se da pelo -1
            _camera(sf::Vector2f(tamanhoJanela.x / 2.0f, tamanhoJanela.y / 2.0f), tamanhoJanela),
            _limiteObjeto(sf::IntRect(-1, -1, -1, -1)) {}
        
        // destrutor
        Camera::~Camera()
        {

        }
        
        // funcao que altera o limite da camera
        void Camera::set_limiteCamera(sf::IntRect limiteCamera){
            this->_limiteCamera = limiteCamera;
            ajustarLimite();
        }

        // funcao que retorna a camera 
        sf::View Camera::get_camera(){
            return _camera;
        }

        // funcao que reinicia o centro da camera
        void Camera::resetar(sf::Vector2f possicaoCentro){
            _camera.setCenter(possicaoCentro);
        }

        // funcao que ajusta os limites entre o objeto e a camera horizontalmente e verticalmente 
        void Camera::ajustarLimite(){
            if(_limiteCamera.width != -1 && _limiteObjeto.width != -1){            // indica que precisa atualizar limites 
                // verificacao das janelas na vertical
                if(_limiteObjeto.top < _limiteCamera.top){                         // se o limite do objeto esta acima do limite da camera 
                    _limiteObjeto.top = _limiteCamera.top;                         // entao o limite do objeto recebe o limite da camera 
                } else if(_limiteObjeto.top + _limiteObjeto.height > _limiteCamera.top + _limiteCamera.height){              // se o limite do objeto esta abaixo do limite da camera 
                    float diferencaAltura = _limiteObjeto.top + _limiteObjeto.height - (_limiteCamera.top + _limiteCamera.height);  // pega a diferenca entre a altura da zona do limite do objeto e a altura do limite da camera
                    _limiteObjeto.top -= diferencaAltura;                                                        // subtrai a diferenca do topo, igualando assim as alturas e o ponto de inicio (igualando os limites verticalmente)
                }
                // verificacao das janelas na horizontal
                if(_limiteObjeto.left < _limiteCamera.left){                                    // se o limite do objeto esta a esquerda do limite da camera
                    _limiteObjeto.left = _limiteCamera.left;                                    // limite do objeto vira o limite da camera    
                } else if(_limiteObjeto.left + _limiteObjeto.width > _limiteCamera.left + _limiteCamera.width){                          // se o limite do objeto esta a direita do limite da camera
                     float diferencaLargura = _limiteObjeto.left + _limiteObjeto.width - (_limiteCamera.left + _limiteCamera.width);     // subtrai a direnca de comprimento entre o limite do objeto e o limite da camera
                    _limiteObjeto.left -= diferencaLargura;                                                                              // subtrai essa diferenca do inicio do comprimeto a esquerda do limite do objeto, igualando assim o comprimento e o ponto de inicio entre eles (igualando os limites horizontalmente)
                }
                _camera.setCenter(sf::Vector2f(_limiteObjeto.left + _limiteObjeto.width / 2.0f, _limiteObjeto.top + _limiteObjeto.height / 2.0f));      // centraliza a camera junto ao limite do objeto
            }
        }

        // funcao que altera os limites do objeto
        void Camera::set_limiteObjeto(sf::IntRect objeto){
            if(objeto.width != -1){                                                 // significa que ele nao possui o limite de -1 e que queremos criar um, novo limite
                sf::Vector2f posicao(objeto.left, objeto.top);                      // faz uma copia da posicao e do tamanho desse objeto
                sf::Vector2f tamanho(objeto.width, objeto.height);
                _limiteObjeto.width = _tamanhoJanela.x / 5.0f;                                      // ajusta o comprimento do limite do objeto como 20% do comprimento da janela
                _limiteObjeto.height = _tamanhoJanela.y / 3.0f;                                     // ajusta a altura do limite do objeto como 33% da altura da janela 
                _limiteObjeto.left = posicao.x - _limiteObjeto.width / 2.0f + tamanho.x / 2.0f;     // ajusta a largura do limite do objeto de acordo com o novo objeto (centraliza o limite do objeto em relacao ao jogador no eixo horizontal)
                _limiteObjeto.top = posicao.y - _limiteObjeto.height / 2.0f + tamanho.y / 2.0f;     // ajusta a altura do limite do objeto de acordo com o novo objeto (centraliza o limite do objeto em relacao ao jogador no eixo vertical)
                ajustarLimite();                                                                    // chama a funcao para ajustar os limites do objeto novo com os limites da camera 
            } else {
                this->_limiteObjeto = objeto;                                 // significa que possui o limite de -1, entao so copia
            }
        }
        
        void Camera::atualizar(sf::Vector2f posicaoJogador){
            _camera.setCenter(posicaoJogador);
        }

        void Camera::atualizar(sf::Vector2f possicaoJogador, sf::Vector2f tamanho){

           /* //seguir jogador
            sf::Vector2f ds(0.0f, 0.0f);
            sf::Vector2f center = camera.getCenter();
            bool atualizarCamera = false;
            if(pos.x + tam.x > limiteObjeto.left + limiteObjeto.width
                && limiteObjeto.left + limiteObjeto.width < limiteCamera.left + limiteCamera.width){
                ds.x = (pos.x + tam.x) - (limiteObjeto.left + limiteObjeto.width);
                center.x = pos.x + tam.x - limiteObjeto.width / 2.0f;
                atualizarCamera = true;
            } else if((pos.x < limiteObjeto.left) && (limiteObjeto.left > limiteCamera.left)){
                ds.x = pos.x  - limiteObjeto.left;
                center.x = pos.x + limiteObjeto.width / 2.0f;
                atualizarCamera = true;
            }
            if(pos.y + tam.y > limiteObjeto.top + limiteObjeto.height
                && limiteObjeto.top + limiteObjeto.height < limiteCamera.top + limiteCamera.height){
                ds.y = (pos.y + tam.y) - (limiteObjeto.top + limiteObjeto.height);
                center.y = pos.y + tam.y - limiteObjeto.height / 2.0f;
                atualizarCamera = true;
            } else if((pos.y < limiteObjeto.top) && (limiteObjeto.top > limiteCamera.top)){
                ds.y = pos.y - limiteObjeto.top;
                center.y = pos.y + limiteObjeto.height / 2.0f;
                atualizarCamera = true;
            }
            if(atualizarCamera){
                limiteObjeto.left += ds.x;
                limiteObjeto.top += ds.y;
                camera.setCenter(center);
            }*/
        }

    


/*
// construtor
Camera::Camera(sf::Vector2f tamanhoJanela) :
    _tamanhoJanela(tamanhoJanela) 
    { 
    _camera.setSize (tamanhoJanela);
    _camera.setCenter (tamanhoJanela.x/2.0 , tamanhoJanela.y/2.0);

    // zona morta comeca com 20% da largura da janela e 30% do altura
    _zonaMorta.width = tamanhoJanela.x * 0.3f; 
    _zonaMorta.height = tamanhoJanela.y * 0.2f;

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
void Camera::set_limiteMapa(sf::FloatRect novoLimiteMapa)
{
    this->_limiteMapa = novoLimiteMapa;
}

// funcao que atualiza a posicao da camera de acordo com que o jogador sai da zona morta
void Camera::atualizarCamera(sf::Vector2f posicaoJogador)
{
    sf::Vector2f centroCamera = _camera.getCenter();                                   // pega o centro da camera\

    // atualiza a posicao da zona morta, deixando ela centralizada na camera
    _zonaMorta.left = centroCamera.x - _zonaMorta.width / 2.0f;      // pega o centro da camera e subtrai pela metada da largura total da zona morta e atualiza a posicao do lado esquerdo da zona morta, fazendo com que ela fique centralizada em relacao ao eixo x da visao da camera
    _zonaMorta.top = centroCamera.y - _zonaMorta.height / 2.0f;      // pega o centro da camera e subtrai pela metada da altura total da zona morta e atualiza a posicao do lado de cima da zona morta, fazendo com que ela fique centralizada em relacao ao eixo y da visao da camera

    bool precisaMover = false;
    sf::Vector2f novoCentro = centroCamera;

    // verifica se o jogador saiu da zona morta no eixo horizontal
    if (posicaoJogador.x > _zonaMorta.left + _zonaMorta.width) {                  // se o jogador esta a direita da zona morta
        novoCentro.x = posicaoJogador.x - _zonaMorta.width / 2.0f;                // redefine a zona morta com o jogador no centro dela 
        precisaMover = true;                                            
    }
    else if (posicaoJogador.x < _zonaMorta.left) {                                // se o jogador esta a esquerda da zona morta
        novoCentro.x = posicaoJogador.x + _zonaMorta.width / 2.0f;                // redefine a zona morta com o jogador no centro dela
        precisaMover = true;
    }

    // verifica se o jogador saiu da zona morta no eixo vertical 
    if (posicaoJogador.y > _zonaMorta.top + _zonaMorta.height) {                   // se o jogador esta abaixo da zona morta
        novoCentro.y = posicaoJogador.y - _zonaMorta.height / 2.0f;                // redefine a zona morta com o jogador no centro dela
        precisaMover = true;
    }
    else if (posicaoJogador.y < _zonaMorta.top) {                                  // se o jogador esta acima da zona morta
        novoCentro.y = posicaoJogador.y + _zonaMorta.height / 2.0f;                // redefine a zona morta com o jogador no centro dela
        precisaMover = true;
    }

    // se precisa mover, verifica os limites do mapa/fase
    if (precisaMover) {
        // limitando a area da camera horizontalmente 
        float metadeDaLarguraTela = _tamanhoJanela.x / 2.0f;                                    // pega a metade da largura da tela
        if (novoCentro.x - metadeDaLarguraTela < _limiteMapa.left) {                            // se o centro da camera estiver a esquerda do limite do mapa
            novoCentro.x = _limiteMapa.left + metadeDaLarguraTela;                              // atualiza o centro da camera para o centro do mapa
        }
        else if (novoCentro.x + metadeDaLarguraTela > _limiteMapa.left + _limiteMapa.width) {   // se o centro da camera estiver a direita do limite do mapa
            novoCentro.x = _limiteMapa.left + _limiteMapa.width - metadeDaLarguraTela;          // atualiza o centro da camera para o centro do mapa
        }

        // limitando a area da camera verticalmente
        float metadeDaAlturaTela = _tamanhoJanela.y / 2.0f;                                     // pega a metade da largura da tela
        if (novoCentro.y - metadeDaAlturaTela < _limiteMapa.top) {                              // se o centro da camera estiver acima do limite do mapa
            novoCentro.y = _limiteMapa.top + metadeDaAlturaTela;                                // atualiza o centro da camera para o centro do mapa
        }
        else if (novoCentro.y + metadeDaAlturaTela > _limiteMapa.top + _limiteMapa.height) {    // se o centro da camera estiver abaixo do limite do mapa
            novoCentro.y = _limiteMapa.top + _limiteMapa.height - metadeDaAlturaTela;           // atualiza o centro da camera para o centro do mapa
        }

        _camera.setCenter(novoCentro);                                                          // atualiza o novo centro da camera
    }
}




*/