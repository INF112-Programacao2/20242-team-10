#include "fase.h"
#include "jogador.h"
#include "esqueleto.h"
#include "arma.h"
#include "plataforma.h"
#include "porta.h"

// inicializacao dos membros estaticos
Jogador* Fase::_jogador = nullptr;

void Fase::criarPlataforma(sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo, sf::Vector2f escala)
{
    Plataforma* plataforma = new Plataforma (posicao, tamanho, tipo, Identificador::plataforma);
    if (plataforma == nullptr){
        throw std::runtime_error ("Nao foi possivel criar a plataforma");
    }

    plataforma->set_escala (escala);
    _listaObstaculos->adicionarEntidade(plataforma);
}

void Fase::criarParede()
{
}

// funcao que criar a porta junto a chave
void Fase::criarPorta(sf::Vector2f posicao, sf::Vector2f tamanho)
{
    
    
    Porta* porta = new Porta (posicao, tamanho, Identificador::porta); 
    if (porta == nullptr){
        throw std::runtime_error ("Nao foi possivel criar a porta");
    }

    _listaObstaculos->adicionarEntidade(porta);
}

void Fase::criarPersonagem(sf::Vector2f posicao, Identificador id)
{
    if (id == Identificador::jogador) {
        if (_jogador != nullptr) {
            throw std::invalid_argument("O jogador ja existe, nao foi possivel cria-lo");
        }
        
        _jogador = new Jogador(posicao);
        
        _listaPersonagens->adicionarEntidade(_jogador);
        if (_jogador->get_arma()) {
            _listaPersonagens->adicionarEntidade(_jogador->get_arma());
        }
    }
    else if (id == Identificador::esqueleto) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o esqueleto - jogador nulo");
            }
            
            Esqueleto* esqueleto = new Esqueleto(posicao, _jogador);
            if (!esqueleto) {
                throw std::runtime_error("Falha ao alocar memória para o esqueleto");
            }

            _listaPersonagens->adicionarEntidade(esqueleto);
            
            std::cout << "Esqueleto criado na posição: " << posicao.x << ", " << posicao.y << std::endl;

            if (esqueleto->get_arma()) {
                _listaPersonagens->adicionarEntidade(esqueleto->get_arma());
            }
        }
}

// construtor
Fase::Fase(Identificador idFase, Identificador idFundo) :
        _idFase (idFase) , _fundo(idFundo) , _listaPersonagens (new ListaEntidade()) , _listaObstaculos (new ListaEntidade()),
        gColisao (nullptr) , gGrafico(gGrafico->get_grafico()), _mapa()

{
    if (_listaObstaculos == nullptr|| _listaPersonagens == nullptr) {
        throw std::runtime_error ("Nao foi possivel criar a lista de entidades para a fase");
    }
    
    gColisao = new GerenciadorColisao (_listaPersonagens,_listaObstaculos);
    
    if (gColisao == nullptr) {
        throw std::runtime_error ("Nao foi possivel criar o gerenciador de colisao para a fase");
    }
}

// destrutor
Fase::~Fase()
{
    if (_listaObstaculos) {
        delete _listaObstaculos;
        _listaObstaculos = nullptr;
    }

    if (_listaPersonagens) {
        delete _listaPersonagens;
        _listaPersonagens = nullptr;
    }

    if (gColisao) {
        delete gColisao;
        gColisao = nullptr;
    }
}

void Fase::set_limiteCamera(sf::IntRect limiteCamera)
{
    gGrafico->set_limiteCamera(limiteCamera);
}

void Fase::set_mapa(std::vector<std::vector<char>> mapa)
{
    _mapa = std::move(mapa);
}

Jogador *Fase::get_jogador()
{
    for (int i=0; i < _listaPersonagens->get_tamanhoLista(); i++) {
        Entidade* entidade = _listaPersonagens->get_entidades()[i];
        if (entidade->get_id() == Identificador::jogador){
            return dynamic_cast< Jogador* >(entidade);
        }
    }

    return nullptr;
}

/*sf::IntRect Fase::get_limiteCamera()
{
    gGrafico->get_limiteCamera (); 
}*/

/*void Fase::mudarFase(Identificador id = Identificador::comeco)
{

}*/

void Fase::executarFase()
{
    _jogador = get_jogador();
    if (_jogador){
        _fundo.executar();

        gGrafico->atualizaCamera(_jogador->get_posicao());
        
        _listaObstaculos->executar();

        _listaPersonagens->executar();

    
        gColisao->executar();
    }
    else 
    {
        // jogador morreu
    }
}

void Fase::desenhar()
{
    _fundo.executar();
    _listaPersonagens-> desenhar();
    _listaObstaculos->desenhar();
}
