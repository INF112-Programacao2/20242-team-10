#include "fase.h"

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

void Fase::criarPorta()
{
}

// construtor
Fase::Fase(Identificador idFase, Identificador idFundo) :
        _idFase (idFase) , _fundo(idFundo) , _listaPersonagens (new ListaEntidade()) , _listaObstaculos (new ListaEntidade()),
        gColisao (new GerenciadorColisao(_listaPersonagens,_listaObstaculos)) , gGrafico(gGrafico->get_grafico())

{
    if (_listaObstaculos == nullptr|| _listaPersonagens == nullptr) {
        throw std::runtime_error ("Nao foi possivel criar a lista de entidades para a fase");
    }
    if (gColisao == nullptr) {
        throw std::runtime_error ("Nao foi possivel criar o gerenciador de colisao para a fase");
    }
}

// destrutor
Fase::~Fase()
{
    if (_listaObstaculos != nullptr) {
        delete (_listaObstaculos);
        _listaObstaculos = nullptr;
    }

    if (_listaPersonagens != nullptr) {
        if (_jogador != nullptr){
            delete (_listaPersonagens);
            _jogador = nullptr;
        }
        else {
            delete (_listaPersonagens);
        }

        _listaPersonagens = nullptr;
    }

    if (gColisao != nullptr){
        delete (gColisao);
        gColisao = nullptr;
    }
}

void Fase::set_limiteCamera(sf::IntRect limiteCamera)
{
    gGrafico->set_limiteCamera(limiteCamera);
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

void Fase::mudarFase(Identificador id = Identificador::comeco)
{

}

void Fase::executarFase()
{
    _jogador = get_jogador();
    if (_jogador){
        _fundo.executar();

        _listaPersonagens->executar();
        _listaObstaculos->executar();

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
