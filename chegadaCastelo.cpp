#include "chegadaCastelo.h"
#include "esqueleto.h"

// construtor
ChegadaCastelo::ChegadaCastelo(std::vector < std::vector < char >> mapa) :
    Fase(Identificador::chegadaCastelo, Identificador::fundo_chegadaCastelo)
    {
        set_mapa(mapa);
        criarFundo ();
        criarMapa ();
        inicializarPortas ();
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

    //sf::Vector2f centro (TAMANHO_TELA_X/2.0f - 250.0f , NIVEL_DA_PLATAFORMA - 380.0f);
    //_fundo.adicionarCamada("casteloJogo.png", sf::Vector2f(500.0f,500.0f), centro);
}

void ChegadaCastelo::criarMapa()
{
        std::cout << "Iniciando criação do mapa..." << std::endl;

    if (!_mapa.empty() && !_mapa[0].empty()){            // verifica se a matriz do mapa nao esta vazia, tanto na coluna quanto nas linhas
        int linhas = _mapa.size();                       // pega o tamanho das linhas
        int colunas = _mapa[0].size();                   // pega o tamanho da coluna

        for (int i=0 ; i< linhas; i++) {
            for (int j=0; j < colunas; j++){
                if (_mapa[i][j] == '#'){
                    criarPlataforma(sf::Vector2f(j*75.0f,NIVEL_DA_PLATAFORMA),sf::Vector2f(75.0f,75.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
                }
                else if (_mapa[i][j] == '$'){
                    criarPlataforma(sf::Vector2f(j*75.0f,0.0f),sf::Vector2f(75.0f,75.0f),"Teto",sf::Vector2f(1.0f,1.0f));
                }
                else if (_mapa[i][j] == '@'){
                    criarParede(sf::Vector2f(j*75.0f,i*75.0f),sf::Vector2f(75.0f,75.0f),"ParedeLisa");
                }
                else if (_mapa[i][j] == '1'){
                    criarParede(sf::Vector2f(j*75.0f,i*75.0f),sf::Vector2f(75.0f,75.0f),"Contorno1");
                }
                else if (_mapa[i][j] == '2'){
                    criarParede(sf::Vector2f(j*75.0f,i*75.0f),sf::Vector2f(75.0f,75.0f),"Contorno2");
                }
                else if (_mapa[i][j] == '3'){
                    criarParede(sf::Vector2f(j*75.0f,i*75.0f),sf::Vector2f(75.0f,75.0f),"Contorno3");
                }
                else if (_mapa[i][j] == '4'){
                    criarParede(sf::Vector2f(j*75.0f,i*75.0f),sf::Vector2f(75.0f,75.0f),"Contorno4");
                }
                else if (_mapa[i][j] == '5'){
                    criarParede(sf::Vector2f(j*75.0f,i*75.0f),sf::Vector2f(75.0f,75.0f),"Contorno5");
                }
                else if (_mapa[i][j] == '6'){
                    criarParede(sf::Vector2f(j*75.0f,i*75.0f),sf::Vector2f(75.0f,75.0f),"Contorno6");
                }
                else if (_mapa[i][j] == '7'){
                    criarParede(sf::Vector2f(j*75.0f,i*75.0f),sf::Vector2f(75.0f,75.0f),"Contorno7");
                }
                else if (_mapa[i][j] == 'P'){
                    criarPorta (sf::Vector2f(j*75.0f,NIVEL_DA_PLATAFORMA - 225.0f),sf::Vector2f(150.0f,225.0f));
                }
                    //criarPorta (sf::Vector2f(j*75.0f,NIVEL_DA_PLATAFORMA - 30.0f),sf::Vector2f(50.0f,100.0f));
                
            }
        }
    }

    criarPersonagem(sf::Vector2f(200.0f,NIVEL_DA_PLATAFORMA - TAMANHO_JOGADOR_Y), Identificador::jogador);
    std::cout << "Criando esqueleto..." << std::endl;
    //criarPersonagem(sf::Vector2f(500.0f,NIVEL_DA_PLATAFORMA - TAMANHO_ESQUELETO_Y),Identificador::esqueleto);
    std::cout << "Esqueleto criado com sucesso" << std::endl;

    std::cout << "Total de entidades após criação: " << _listaPersonagens->get_tamanhoLista() << std::endl;

}
