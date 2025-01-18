#include "gerenciadorcolisao.h"
#include "obstaculo.h"
#include "porta.h"
#include <cmath>

// funcao que verifica as colisoes entre personagens
void GerenciadorColisao::verificaColisaoEntrePersonagens()
{
        for (int i = 0; i < _listaPersonagens->get_tamanhoLista() - 1; i++) {             // percorre a lista de personagens ate a penultima posicao
        Entidade* entidade1 = _listaPersonagens->get_entidades()[i]; 
            for (int j = i + 1; j < _listaPersonagens->get_tamanhoLista(); j++) {         // percorre a lista de personagens sempre pegando o proximo personagem, fazendo a verificacao entre todos os personagens
                Entidade* entidade2 = _listaPersonagens->get_entidades()[j];
                sf::Vector2f distancia = calculaColisao(entidade1, entidade2);            // calcula a colisao entre o personagem atual e todos os outros
                if (distancia.x < 0.0f && distancia.y < 0.0f) {                           // se a distancia entre eles for negativa em ambos os eixos, significa que ha colisao (sobreposicao)
                    entidade1->colisao(entidade2, distancia);                             // chama o metodo de colisao do primeiro personagem
                    entidade2->colisao(entidade1, distancia);                             // chama o metodo de colisao do segundo personagem
                }
            }
        }
}


// funcao que verifica as colisoes entre personagens e obstaculos
void GerenciadorColisao::verificaColisaoPersonagemObstaculo()
{
        for (int i = 0; i < _listaPersonagens->get_tamanhoLista(); i++) {                 // percorre a lista de personagens
        Entidade* personagem = _listaPersonagens->get_entidades()[i];
        if (!personagem) continue;  // Skip se a entidade for nula
            for (int j = 0; j < _listaObstaculos->get_tamanhoLista(); j++) {              // percorre a lista de obstaculos
                Entidade* obstaculo = _listaObstaculos->get_entidades()[j];
                 if (!obstaculo) continue;  // Skip se o obstáculo for nulo
                sf::Vector2f distancia = calculaColisao(personagem, obstaculo);           // calcula  a colisao entre o personagem atual e todos os obstaculos
                if (distancia.x < 0.0f && distancia.y < 0.0f) {                           // se a distancia entre eles for negativa em ambos os eixos, significa que ha colisao (sobreposicao)
                 // Se for uma porta e já estiver aberta, não processa a colisão
                    if (obstaculo->get_id() == Identificador::porta) {
                        Porta* porta = dynamic_cast<Porta*>(obstaculo);
                        if (porta && !porta->estaFechada()) {
                            continue;
                        }
                    }
                    obstaculo->colisao (personagem,distancia);                            // chama o metodo de colisao do obstaculo
                    }
                }
            }
}
 
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
    verificaColisaoEntrePersonagens();
    verificaColisaoPersonagemObstaculo();
}
