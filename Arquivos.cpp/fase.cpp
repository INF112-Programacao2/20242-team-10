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

// funcao que cria o espinho do jogo
void Fase::criarEspinho(sf::Vector2f posicao, sf::Vector2f tamanho)
{
    Espinho* espinho = new Espinho (posicao, tamanho);
    if (espinho == nullptr) {
        throw std::runtime_error ("Nao foi possivel criar o espinho");
    }

    _listaObstaculos->adicionarEntidade(espinho);
    std::cout << "Espinho adicionado a lista " << std::endl;
}

void Fase::reiniciarFase()
{

        gGrafico->resetarRelogio();
    
    // Limpa entidades mas mantém as estruturas
    
        _listaPersonagens->limparEntidades();
    
    
   
        _listaObstaculos->limparEntidades();
    
    
    // Reseta jogador
    _jogador = nullptr;
    
    // Limpa mensagens
    if (_mensagem) {
        _mensagem->limparMensagens();
    }

    // Recria apenas o mapa e personagens
    criarMapa();
/*
       gGrafico->resetarRelogio();
    
    // Limpa e deleta as listas
    if (_listaObstaculos) {
        _listaObstaculos->limparEntidades();
        delete _listaObstaculos;
        _listaObstaculos = nullptr;
    }
    
    if (_listaPersonagens) {
        _listaPersonagens->limparEntidades(); 
        delete _listaPersonagens;
        _listaPersonagens = nullptr;
    }
    
    if (gColisao) {
        delete gColisao;
        gColisao = nullptr;
    }

    // Reseta estado
    _jogador = nullptr;
    
    // Limpa mensagens
    if (_mensagem) {
        _mensagem->limparMensagens();
    }

    // Recria estruturas
    _listaObstaculos = new ListaEntidade();
    _listaPersonagens = new ListaEntidade();
    gColisao = new GerenciadorColisao(_listaPersonagens, _listaObstaculos);

    criarMapa();*/
    
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
    else if (id == Identificador::goblin) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o goblin - jogador nulo");
            }
            Goblin* goblin = new Goblin (posicao,_jogador);
            if (!goblin){
                throw std::runtime_error("Falha ao alocar memória para o goblin");
            }
            _listaPersonagens->adicionarEntidade (goblin);
            
            if (goblin->get_arma()) {
           _listaPersonagens->adicionarEntidade(goblin->get_arma());
            }
    }
    else if (id == Identificador::alma) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o alma - jogador nulo");
            }
            
            Alma* alma = new Alma(posicao, _jogador);
            if (!alma) {
                throw std::runtime_error("Falha ao alocar memória para a alma");
            }
           // alma->set_lista(_listaPersonagens);
            _listaPersonagens->adicionarEntidade(alma);
            
            std::cout << "alma criado na posição: " << posicao.x << ", " << posicao.y << std::endl;

            if (alma->get_arma()) {
                _listaPersonagens->adicionarEntidade(alma->get_arma());
            }
        }
    else if (id == Identificador::chefao) {
            if (!_jogador) {
                throw std::runtime_error("Não foi possível criar o chefao - jogador nulo");
            }
            
            Chefao* chefao = new Chefao(posicao, _jogador);
            if (!chefao) {
                throw std::runtime_error("Falha ao alocar memória para o chefao");
            }
           // chefao->set_lista(_listaPersonagens);
            _listaPersonagens->adicionarEntidade(chefao);
            
            std::cout << "chefao criado na posição: " << posicao.x << ", " << posicao.y << std::endl;

            if (chefao->get_arma()) {
                _listaPersonagens->adicionarEntidade(chefao->get_arma());
            }
        }
}

void Fase::criarMapa()
{
    for (int i=0 ; i < TAMANHO_TELA_X * 4 / 75.0f ; i++){
        if (i == 17 || i == 18 || i == 19){
            criarEspinho (sf::Vector2f(i*75.f, TAMANHO_TELA_Y - 40.0f), sf::Vector2f (75.0f,40.0f));
        }
        else if ( i < 50) {
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA),sf::Vector2f(75.0f,125.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
        }
        else if (i >= 52) {
            criarPlataforma(sf::Vector2f(i*75.0f,NIVEL_DA_PLATAFORMA - 150.0f),sf::Vector2f(75.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
        } 

        //criarEscada (sf::Vector2f(500.0f, NIVEL_DA_PLATAFORMA - 150.0f), // ajuste a posição
        //sf::Vector2f(100.0f, 150.0f));

        criarPlataforma(sf::Vector2f(75*50.0f,NIVEL_DA_PLATAFORMA - 50.0f),sf::Vector2f(50.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(76*50.0f,NIVEL_DA_PLATAFORMA - 2*50.0f ),sf::Vector2f(50.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
        criarPlataforma(sf::Vector2f(77*50.0f,NIVEL_DA_PLATAFORMA - 3*50.0f),sf::Vector2f(50.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));

        criarPlataforma(sf::Vector2f(4650.0f,NIVEL_DA_PLATAFORMA - 150.0f - 35.0f),sf::Vector2f(75.0f,35.0f),"Banco",sf::Vector2f(1.0f,1.0f));              // banco da coroa
        //criarPlataforma(sf::Vector2f(103*50.0f,NIVEL_DA_PLATAFORMA - 4*50.0f),sf::Vector2f(50.0f,50.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));
    }

   // criarPlataforma(sf::Vector2f(320.0f,NIVEL_DA_PLATAFORMA - 200.0f),sf::Vector2f(75.0f,75.0f),"CarpeteRocha",sf::Vector2f(1.0f,1.0f));  // apenas para teste

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

MensagemBox *Fase::get_mensagem()
{
    return _mensagem;
}

// construtor
Fase::Fase() :
         _fundo(Identificador::fundoPrincipal) , _listaPersonagens (new ListaEntidade()) , _listaObstaculos (new ListaEntidade()),
        gColisao (nullptr) , gGrafico(gGrafico->get_grafico()) , _mensagem (nullptr), gEvento (gEvento->get_gEvento())

{
    sf::Font fonte;
    fonte.loadFromFile("FonteNivel.ttf");
    _mensagem = new MensagemBox (fonte, sf::Vector2f(100, 100), sf::Vector2f(600, 150));
    _textoSom = new TextoSom(fonte);

    //gEvento->get_gEvento()->set_mensagem (_mensagem);
    

    _mensagem->adicionarMensagem("Bem-vindo ao nosso reino!");
    _mensagem->adicionarMensagem("Uma antiga maldição assola nossas terras...");
    _mensagem->adicionarMensagem("Apenas você pode nos salvar!");                        


    gColisao = new GerenciadorColisao (_listaPersonagens,_listaObstaculos);
    criarFundo();
    criarMapa();


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

    _fundo.adicionarCamada ("fundoInterior.png" , sf::Vector2f (TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(0.0f,0.0f));

    _fundo.adicionarCamada("Fundo1.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(1200.0f,0.0f));
    _fundo.adicionarCamada ("Fundo2.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(1200.0f,0.0f));

    _fundo.adicionarCamada ("fundoInterior.png" , sf::Vector2f (TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(2400.0f,0.0f));

    _fundo.adicionarCamada("Fundo1.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(3600.0f,0.0f));
    _fundo.adicionarCamada ("Fundo2.png",sf::Vector2f(TAMANHO_TELA_X,TAMANHO_TELA_Y),sf::Vector2f(3600.0f,0.0f));

    _fundo.adicionarCamada("Coroa.png" , sf::Vector2f (50.0f,40.0f) , sf::Vector2f (4662.0f,315.0f));          // cria a coroa

}

void Fase::executarFase()

{
    _jogador = get_jogador();
    if (!_jogador) return;
    
    _fundo.executar();
    gGrafico->atualizaCamera(_jogador->get_posicao());

    // Atualiza mensagens sempre
    if (_mensagem) {
        _mensagem->atualizar();
    }

    // Se jogador estiver congelado
    if (_jogador->estaCongeladoJogo()) {
        static bool mensagemAdicionada = false;
        if (!mensagemAdicionada) {
            _mensagem->adicionarMensagem("Voce morreu! Pressione 'R' para reiniciar o jogo.");
            mensagemAdicionada = true;
        }
        if (!_jogador->estaMorrendo()) {
            mensagemAdicionada = false;
        }
        return;
    } 

    // Executa lógica do jogo
    _listaObstaculos->executar();
    _listaPersonagens->executar();
    gColisao->executar();
    /*
    _jogador = get_jogador();
    if (_jogador) {
        _fundo.executar();
        gGrafico->atualizaCamera(_jogador->get_posicao());
        
        if (!_jogador->estaCongeladoJogo()) {
            _listaObstaculos->executar();
            _listaPersonagens->executar();
            gColisao->executar();
        } else {
            static bool mensagemAdicionada = false;
            if (!mensagemAdicionada) {
                _mensagem->adicionarMensagem("Voce morreu! Pressione 'R' para reiniciar o jogo.");
                mensagemAdicionada = true;
            }
            // Reseta a flag quando o jogo reiniciar
            if (!_jogador->estaMorrendo()) {
                mensagemAdicionada = false;
            }
        }

        if (_mensagem->temMensagem()) {
            _mensagem->atualizar();
            return;
        }
    }*/

}

void Fase::desenhar()
{
    _fundo.executar();
    _listaPersonagens->desenhar();
    _listaObstaculos->desenhar();

        _textoSom->desenhar(*gGrafico->get_janela());
        _mensagem->desenhar(*gGrafico->get_janela());
   
}
