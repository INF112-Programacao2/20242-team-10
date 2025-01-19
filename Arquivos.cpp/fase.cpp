#include "fase.h"
#include "jogador.h"
#include "esqueleto.h"
#include "arma.h"
#include "morcego.h"
#include "plataforma.h"


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

void Fase::criarParede(sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo)
{
    Plataforma* parede = new Plataforma (posicao, tamanho, tipo , Identificador::parede);
    if (parede == nullptr) {
         throw std::runtime_error ("Nao foi possivel criar a parede");
    }
    parede->set_escala (sf::Vector2f(1.0f,1.0f));
    _listaObstaculos->adicionarEntidade(parede);
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
           // esqueleto->set_lista(_listaPersonagens);
            _listaPersonagens->adicionarEntidade(esqueleto);
            
            std::cout << "Esqueleto criado na posição: " << posicao.x << ", " << posicao.y << std::endl;

            if (esqueleto->get_arma()) {
                _listaPersonagens->adicionarEntidade(esqueleto->get_arma());
            }
        }
    else if (id == Identificador::morcego) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o morcego - jogador nulo");
            }
            Morcego* morcego = new Morcego (posicao,_jogador);
            if (!morcego){
                throw std::runtime_error("Falha ao alocar memória para o morcego");
            }
            _listaPersonagens->adicionarEntidade (morcego);
    }
}

void Fase::criarMapa()
{
    for (int i=0 ; i < TAMANHO_TELA_X * 3 / 75.0f ; i++){
        criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA),sf::Vector2f(75.0f,125.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
    }

   // criarPlataforma(sf::Vector2f(320.0f,NIVEL_DA_PLATAFORMA - 200.0f),sf::Vector2f(75.0f,75.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));  // apenas para teste

    criarPersonagem(sf::Vector2f(200.0f,NIVEL_DA_PLATAFORMA - TAMANHO_JOGADOR_Y), Identificador::jogador);
    criarPersonagem(sf::Vector2f(500.0f,NIVEL_DA_PLATAFORMA - TAMANHO_ESQUELETO_Y),Identificador::esqueleto);
    criarPersonagem(sf::Vector2f(800.0f,300.0f),Identificador::morcego);
}

// construtor
Fase::Fase() :
         _fundo(Identificador::fundoPrincipal) , _listaPersonagens (new ListaEntidade()) , _listaObstaculos (new ListaEntidade()),
        gColisao (nullptr) , gGrafico(gGrafico->get_grafico()) , _mensagem (nullptr), gEvento (gEvento->get_gEvento())

{
    sf::Font fonte;
    fonte.loadFromFile("FonteNivel.ttf");
    _mensagem = new MensagemBox (fonte, sf::Vector2f(50.0f, TAMANHO_TELA_Y - 150.0f),
                                    sf::Vector2f (TAMANHO_TELA_X - 100.0f,100.0f));

    gEvento->get_gEvento()->set_mensagem (_mensagem);
    

                              


    gColisao = new GerenciadorColisao (_listaPersonagens,_listaObstaculos);
    criarFundo();
    criarMapa();

    _mensagem->adicionarMensagem ("Olá, viajante!");  
    _mensagem->adicionarMensagem("Bem-vindo ao jogo!");    

}

// destrutor
Fase::~Fase()
{
    if (_mensagem){
        delete _mensagem;
        _mensagem = nullptr;
    }
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

void Fase::criarFundo()
{
    _fundo.adicionarCamada("Fundo1.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(0.0f,0.0f));
    _fundo.adicionarCamada ("Fundo2.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(0.0f,0.0f));

    _fundo.adicionarCamada ("fundoInterior.png" , sf::Vector2f (TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(1200.0f,0.0f));

    _fundo.adicionarCamada("Fundo1.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(2400.0f,0.0f));
    _fundo.adicionarCamada ("Fundo2.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(2400.0f,0.0f));

}

void Fase::executarFase()
{
    _jogador = get_jogador();
    if (_jogador){
        _fundo.executar();

        gGrafico->atualizaCamera(_jogador->get_posicao());
        
        _listaObstaculos->executar();

        _listaPersonagens->executar();

    
        gColisao->executar();

        if (_mensagem) {
           _mensagem->atualizar ();
        }
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

    if (_mensagem) {
        _mensagem->desenhar (*gGrafico->get_janela());
    }
}
