#include "fase.h"
#include "jogador.h"
#include "esqueleto.h"
#include "arma.h"
#include "morcego.h"
#include "plataforma.h"
#include "goblin.h"
#include "espinho.h"
#include "chefao.h"
#include "alma.h"
#include "gerenciadoreventos.h"



// inicializacao dos membros estaticos
Jogador* Fase::_jogador = nullptr;

// funcao que cria as plataforma do jogo
void Fase::criarPlataforma(sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo, sf::Vector2f escala)
{
    // cria a plataforma
    Plataforma* plataforma = new Plataforma (posicao, tamanho, tipo, Identificador::plataforma);
    if (plataforma == nullptr){
        throw std::runtime_error ("Nao foi possivel criar a plataforma");
    }

    // atualiza a escala e adiciona na lista de obstaculos
    plataforma->set_escala (escala);
    _listaObstaculos->adicionarEntidade(plataforma);
}

// funcao que cria as paredes do jogo
void Fase::criarParede(sf::Vector2f posicao, sf::Vector2f tamanho, std::string tipo)
{
    // cria a parede
    Plataforma* parede = new Plataforma (posicao, tamanho, tipo , Identificador::parede);
    if (parede == nullptr) {
        throw std::runtime_error ("Nao foi possivel criar a parede");
    }

    // atualiza a escala e adiciona na lista de obstaculos
    parede->set_escala (sf::Vector2f(1.0f,1.0f));
    _listaObstaculos->adicionarEntidade(parede);
}

// funcao que cria o espinho do jogo
void Fase::criarEspinho(sf::Vector2f posicao, sf::Vector2f tamanho)
{
    // cria o espinho
    Espinho* espinho = new Espinho (posicao, tamanho);
    if (espinho == nullptr) {
        throw std::runtime_error ("Nao foi possivel criar o espinho");
    }

    // adiciona o espinho na lista de entidade
    _listaObstaculos->adicionarEntidade(espinho);
}

// funcao que reinicia a fase quando o jogador morre ou quando vence o jogo
void Fase::reiniciarFase()
{

    // para a música
     gMusica->parar();

    // reseta o relogio
    gGrafico->resetarRelogio();
   

    // limpa as listas de entidades
    if (_listaPersonagens) {
        _listaPersonagens->limparEntidades();
    }
    if (_listaObstaculos) {
        _listaObstaculos->limparEntidades();
    }

    // reseta o jogador 
    _jogador = nullptr;

    try {
        // recria o mapa e personagens
        criarMapa();
        
        // atualiza o jogador no gerenciador de eventos
        if (gEvento && _jogador) {
            gEvento->set_jogador(_jogador);
        }

        // reinicia a música de fundo
        if (gMusica) {
            gMusica->tocar(Identificador::musica_background);
        }
    }
    catch (const std::exception& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }
}

// funcao que cria os personagens do jogo
void Fase::criarPersonagem(sf::Vector2f posicao, Identificador id)
{
    // se for um jogador
    if (id == Identificador::jogador) {
        if (_jogador != nullptr) {
            throw std::invalid_argument("O jogador ja existe, nao foi possivel cria-lo");
        }
        
        // cria o jogador
        _jogador = new Jogador(posicao);
        
        // adiciona na lista
        _listaPersonagens->adicionarEntidade(_jogador);

        //se ele tiver arma, pega a arma e coloca na lista
        if (_jogador->get_arma()) {
            _listaPersonagens->adicionarEntidade(_jogador->get_arma());
        }
    }

    // se for um esqueleto
    else if (id == Identificador::esqueleto) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o esqueleto - jogador nulo");
            }
            
            // cria o esqueleto
            Esqueleto* esqueleto = new Esqueleto(posicao, _jogador);
            if (!esqueleto) {
                throw std::runtime_error("Falha ao alocar memória para o esqueleto");
            }

            // adiciona o esqueleto na lista
            _listaPersonagens->adicionarEntidade(esqueleto);

            // se ele tiver uma arma, adiciona ela na lista
            if (esqueleto->get_arma()) {
                _listaPersonagens->adicionarEntidade(esqueleto->get_arma());
            }
    }

    // se for um morcego
    else if (id == Identificador::morcego) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o morcego - jogador nulo");
            }

            // cria o morcego
            Morcego* morcego = new Morcego (posicao,_jogador);
            if (!morcego){
                throw std::runtime_error("Falha ao alocar memória para o morcego");
            }

            // adiciona ele na lista
            _listaPersonagens->adicionarEntidade (morcego);
    }

    // se for um goblin
    else if (id == Identificador::goblin) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o goblin - jogador nulo");
            }

            // cria o goblin
            Goblin* goblin = new Goblin (posicao,_jogador);
            if (!goblin){
                throw std::runtime_error("Falha ao alocar memória para o goblin");
            }

            // adiciona ele na lista
            _listaPersonagens->adicionarEntidade (goblin);
            
            // se ele tiver uma arma, adiciona ela na lista
            if (goblin->get_arma()) {
                _listaPersonagens->adicionarEntidade(goblin->get_arma());
            }
    }

    // se for uma alma
    else if (id == Identificador::alma) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o alma - jogador nulo");
            }
            
            // cria a alma
            Alma* alma = new Alma(posicao, _jogador);
            if (!alma) {
                throw std::runtime_error("Falha ao alocar memória para a alma");
            }

            // adiciona ela na lista 
            _listaPersonagens->adicionarEntidade(alma);
        
            // se tiver uma arma, adiciona ela na lista
            if (alma->get_arma()) {
                _listaPersonagens->adicionarEntidade(alma->get_arma());
            }
        }

    // se for o chefao
    else if (id == Identificador::chefao) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o chefao - jogador nulo");
            }
            
            // cria o chefao
            Chefao* chefao = new Chefao(posicao, _jogador);
            if (!chefao) {
                throw std::runtime_error("Falha ao alocar memória para o chefao");
            }

            // adiciona ele na lista
            _listaPersonagens->adicionarEntidade(chefao);
            
            // se ele tiver uma arma, adiciona ela na lista
            if (chefao->get_arma()) {
                _listaPersonagens->adicionarEntidade(chefao->get_arma());
            }
        }
}

// funcao que cria o mapa do jogo
void Fase::criarMapa()
{

    // cria as plataformas do jogo
    for (int i=0 ; i < TAMANHO_TELA_X * 4 / 75.0f ; i++){
        if (i == 17 || i == 18 || i == 19){
            criarEspinho (sf::Vector2f(i*75.f, TAMANHO_TELA_Y - 40.0f), sf::Vector2f (75.0f,40.0f));
        }
        else if ( i < 50) {
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA),sf::Vector2f(75.0f,125.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
        }
        else if (i >= 52) {
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA - 150.0f),sf::Vector2f(75.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA),sf::Vector2f(75.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA - 100),sf::Vector2f(75.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA - 50),sf::Vector2f(75.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA + 50),sf::Vector2f(75.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA + 100),sf::Vector2f(75.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        } 

        // escada
        criarPlataforma(sf::Vector2f(75*50.0f,NIVEL_DA_PLATAFORMA - 50.0f),sf::Vector2f(50.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(76*50.0f,NIVEL_DA_PLATAFORMA - 2*50.0f ),sf::Vector2f(50.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(77*50.0f,NIVEL_DA_PLATAFORMA - 3*50.0f),sf::Vector2f(50.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));

        // conteudo embaixo da escada
        criarPlataforma(sf::Vector2f(76*50.0f,NIVEL_DA_PLATAFORMA - 50.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(77*50.0f,NIVEL_DA_PLATAFORMA - 50.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(77*50.0f,NIVEL_DA_PLATAFORMA - 2*50.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(77*50.0f,NIVEL_DA_PLATAFORMA ),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(77*50.0f,NIVEL_DA_PLATAFORMA + 50.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(77*50.0f,NIVEL_DA_PLATAFORMA + 100.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));

        criarPlataforma(sf::Vector2f(76*50.0f,NIVEL_DA_PLATAFORMA ),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(76*50.0f,NIVEL_DA_PLATAFORMA + 50.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(76*50.0f,NIVEL_DA_PLATAFORMA + 100.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));

        criarPlataforma(sf::Vector2f(75*50.0f,NIVEL_DA_PLATAFORMA ),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(75*50.0f,NIVEL_DA_PLATAFORMA + 50.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(75*50.0f,NIVEL_DA_PLATAFORMA + 100.0f),sf::Vector2f(50.0f,50.0f),"ChaoRocha",sf::Vector2f(1.0f,1.0f));

        // banco da coroa
        criarPlataforma(sf::Vector2f(4650.0f,NIVEL_DA_PLATAFORMA - 150.0f - 35.0f),sf::Vector2f(75.0f,35.0f),"Banco",sf::Vector2f(1.0f,1.0f));             

    }


    // cria os personagens da fase
    criarPersonagem(sf::Vector2f(200.0f,NIVEL_DA_PLATAFORMA - TAMANHO_JOGADOR_Y), Identificador::jogador);
    criarPersonagem(sf::Vector2f(500.0f,NIVEL_DA_PLATAFORMA - TAMANHO_ESQUELETO_Y),Identificador::esqueleto);

    criarPersonagem(sf::Vector2f(800.0f,300.0f),Identificador::morcego);
    criarPersonagem(sf::Vector2f(1800.0f,300.0f),Identificador::morcego);
    criarPersonagem(sf::Vector2f(2800.0f,300.0f),Identificador::morcego);
    criarPersonagem(sf::Vector2f(3300.0f,300.0f),Identificador::morcego);

    criarPersonagem(sf::Vector2f(1800.0f,NIVEL_DA_PLATAFORMA - TAMANHO_GOBLIN_Y), Identificador::goblin);
    criarPersonagem(sf::Vector2f(3000.0f,NIVEL_DA_PLATAFORMA - TAMANHO_ALMA_Y), Identificador::alma);
    criarPersonagem(sf::Vector2f(4250.0f,NIVEL_DA_PLATAFORMA - TAMANHO_CHEFAO_Y - 150.0f ), Identificador::chefao);
}


// construtor
Fase::Fase() :
        _fundo(Identificador::fundoPrincipal),
        _listaPersonagens (new ListaEntidade()),
        _listaObstaculos (new ListaEntidade()),
        gColisao (nullptr),
        gGrafico(gGrafico->get_grafico()),
        gEvento (gEvento->get_gEvento()),
        gMusica(gMusica->get_gerenciadorMusical())

{
    // carrega a fonte
    sf::Font fonte;
    fonte.loadFromFile("FonteNivel.ttf");
    
    // cria o gerenciador de colisao
    gColisao = new GerenciadorColisao (_listaPersonagens,_listaObstaculos);

    criarFundo();
    criarMapa();

}

// destrutor
Fase::~Fase()
{

    if (gMusica){
        delete gMusica;
        gMusica = nullptr;
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

// funcao que atualiza os limites da camera
void Fase::set_limiteCamera(sf::IntRect limiteCamera)
{
    gGrafico->set_limiteCamera(limiteCamera);
}

// funcao que retorna o jogador
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

// funcao que cria o fundo do jogo
void Fase::criarFundo()
{
    // adiciona as camadas
    _fundo.adicionarCamada ("fundoInterior.png" , sf::Vector2f (TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(0.0f,0.0f));

    _fundo.adicionarCamada("Fundo1.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(1200.0f,0.0f));
    _fundo.adicionarCamada ("Fundo2.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(1200.0f,0.0f));

    _fundo.adicionarCamada ("fundoInterior.png" , sf::Vector2f (TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(2400.0f,0.0f));

    _fundo.adicionarCamada("Fundo1.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(3600.0f,0.0f));
    _fundo.adicionarCamada ("Fundo2.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(3600.0f,0.0f));

    _fundo.adicionarCamada("Coroa.png" , sf::Vector2f (50.0f,40.0f) , sf::Vector2f (4662.0f,315.0f));          // cria a coroa

}

// funcao que executa a fase 
void Fase::executarFase()

{
    _jogador = get_jogador();
    if (!_jogador) return;                                      // verifica se tem o jogador principal
    
    _fundo.executar();                                          // executa o fundo
    gGrafico->atualizaCamera(_jogador->get_posicao());          // atualiza a camera    


    if (!_jogador->estaCongeladoJogo()) {                       // se o jogo nao estiver congelado, atualiza o jogo normalmente
            _listaObstaculos->executar();
            _listaPersonagens->executar();
            gColisao->executar();
    }
}

// funcao que desenha as entidades da fase
void Fase::desenhar()
{
    _fundo.executar();
    _listaPersonagens->desenhar();
    _listaObstaculos->desenhar();

   
}
