#include "fundo.h"
#include <iostream>

// construtor
Fundo::Fundo(Identificador id) :
        _id(id) , _camadas () , gGrafico (gGrafico->get_grafico()){}

// destrutor
Fundo::~Fundo()
{
    for (Camada* camada : _camadas) {
        delete camada;
    }
    _camadas.clear();

}

// funcao que adiciona uma camada ao fundo
void Fundo::adicionarCamada(const char *caminhoTextura,sf::Vector2f tamanhoTextura, sf::Vector2f origem)
{
    Camada* novaCamada = new Camada (gGrafico->carregarTextura(caminhoTextura), tamanhoTextura, origem);
    if (novaCamada== nullptr) {
        throw std::runtime_error ("Nao foi possivel criar a camda"); 
    }
    _camadas.push_back(novaCamada);
}

// funcao que desenha as camadas
void Fundo::desenhar()
{
    for ( int i=0 ; i<_camadas.size() ; i++) {
        Camada* camada = _camadas[i];
        camada->desenharCamada ();
    }
}

void Fundo::executar()
{
    desenhar ();
}
