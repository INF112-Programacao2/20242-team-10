#include "gerenciadorcolisao.h"
#include <cmath>

// construtor
GerenciadorColisao::GerenciadorColisao(ListaEntidade *listaPersonagens, ListaEntidade *listaObstaculos) :
    _listaPersonagens(listaPersonagens) , _listaObstaculos (listaObstaculos) {}

// destrutor
GerenciadorColisao::~GerenciadorColisao()
{
}

// funcao que calula quanto colidiram duas entidades
sf::Vector2f GerenciadorColisao::calculaColisao(Entidade *entidade1, Entidade *entidade2)
{
    // pega a posicao e o tamanho de ambas entidades
    sf::Vector2f posicao_1 = entidade1->get_posicao();
    sf::Vector2f posicao_2 = entidade2->get_posicao();

    sf::Vector2f tamanho_1 = entidade1->get_tamanho();
    sf::Vector2f tamanho_2 = entidade2->get_tamanho ();

    // calcula a distancia entre os centros 
    float distanciaHorizontal (fabs((posicao_1.x + tamanho_1.x/2.0f) - (posicao_2.x + tamanho_2.x/2.0f))); // calcula a distancia dos centros horizontalmente em modulo
    float distanciaVertical (fabs((posicao_1.y + tamanho_1.y/2.0f) - (posicao_2.y + tamanho_2.y/2.0f)));   // calcula a distancia dos centros verticalmente em modulo
    sf::Vector2f distanciaEntreCentros (distanciaHorizontal,distanciaVertical);                            // calcula a distancia entre os centros 

    // pega o tamanho da distancia minima entre eles, que seria a soma da metade do tamanho de cada entidade
    sf::Vector2f distanciaMinima (tamanho_1.x/2.0f + tamanho_2.x/2.0f , tamanho_1.y/2.0f + tamanho_2.y/2.0f);   // soma a distancia minima no eixo x e y

    return sf::Vector2f (distanciaEntreCentros.x - distanciaMinima.x , distanciaEntreCentros.y - distanciaMinima.y);  // retorna a diferenca da distancia entre os centros e a distancia minima entre as entidades nos eixos x e y (se for negatico, significa que estao colidindo, se for 0 estao no limite de colisao e se for positivo nao estao colidindo)
}

//
void GerenciadorColisao::executar()
{

}
