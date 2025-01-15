#include "chegadaCastelo.h"

// construtor
ChegadaCastelo::ChegadaCastelo(std::vector < std::vector < char >> mapa) :
    Fase(Identificador::chegadaCastelo, Identificador::fundo_chegadaCastelo)
    {
        set_mapa(mapa);
        criarFundo ();
        criarMapa ();
    }

// destrutor
ChegadaCastelo::~ChegadaCastelo()
{
}

// funcao que criar o fundo da fase
void ChegadaCastelo::criarFundo()
{
    _fundo.adicionarCamada("Fundo1.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(0.0f,0.0f));
    _fundo.adicionarCamada ("Fundo2.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(0.0f,0.0f));
}

void ChegadaCastelo::criarMapa()
{

    if (!_mapa.empty() && !_mapa[0].empty()){            // verifica se a matriz do mapa nao esta vazia, tanto na coluna quanto nas linhas
        int linhas = _mapa.size();                       // pega o tamanho das linhas
        int colunas = _mapa[0].size();                   // pega o tamanho da coluna

        for (int i=0 ; i< linhas; i++) {
            for (int j=0; j < colunas; j++){
                if (_mapa[i][j] == '#'){
                    criarPlataforma(sf::Vector2f(j*100.0f,NIVEL_DA_PLATAFORMA + 75.0f),sf::Vector2f(100.0f,100.0f),"Chao de madeira",sf::Vector2f(1.0f,1.0f));
                }
                else if (_mapa[i][j] == '%'){
                    criarPlataforma (sf::Vector2f(j*100.0f,i*100.0f),sf::Vector2f(100.0f,175.0f),"Chao de madeira",sf::Vector2f(1.0f,1.0f));
                }
            }
        }
    }

    criarPersonagem(sf::Vector2f(200.0f,NIVEL_DA_PLATAFORMA), Identificador::jogador);
    criarPersonagem(sf::Vector2f(500.0f,NIVEL_DA_PLATAFORMA ),Identificador::esqueleto);

}
