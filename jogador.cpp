#include "jogador.h"
#include "inimigo.h"
#include "plataforma.h"
#include "arma.h"
#include "morcego.h"
#include <iostream>
#include "projetil.h"

void Jogador::inicializarAnimacao()
{
    sf::Vector2f origem = sf::Vector2f (_tamanho.x / 2.0f, _tamanho.y / 2.0f);
    //sf::Vector2f origemPulo = sf::Vector2f (_tamanho.x / 2.0f, _tamanho.y * 0.75f);

    _animacao.adicionarAnimacao("Correndo.png", "CORRER", 10 , 0.05f , sf::Vector2f(6,2),origem,true);
    _animacao.adicionarAnimacao("Parado.png", "PARADO", 10 , 0.10f , sf::Vector2f(6,2),origem,true);
    _animacao.adicionarAnimacao("Pulando.png", "PULAR", 3 , 0.10f , sf::Vector2f(6,2),origem,true);
    _animacao.adicionarAnimacao("Atacando.png", "ATACAR", 6 , 0.10f , sf::Vector2f(6,2),origem,true);
    _animacao.adicionarAnimacao("tomandoDano.png", "TOMARDANO" , 1 , 0.20f , sf::Vector2f(6,2), origem, true);
    _animacao.adicionarAnimacao("Morrendo.png", "MORTE", 10 , 0.20f , sf::Vector2f(6,2), origem, true);
    
}

// funcao que atualiza as animacoes do jogador: andar, parar, correr, morrer ...
void Jogador::atualizarAnimacao()
{

    if (morrendo) {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA,"MORTE");
        else 
            _animacao.atualizar(ESQUERDA,"MORTE");
    _tempoMorte += gGrafico->get_tempo ();
        if (_tempoMorte > DURACAO_JOGADOR_MORTE){
            _tempoMorte = 0.0f;
        }
    }
    else if (levandoDano) {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA,"TOMARDANO");
        else 
            _animacao.atualizar(ESQUERDA,"TOMARDANO");
        
        _tempoDano += gGrafico->get_tempo();
        if (_tempoDano >= DURACAO_JOGADOR_SOFRER_DANO) {
            levandoDano = false;
            _tempoDano = 0.0f;
        }
    }
    else if (andando){
        if (!andaEsquerda)
        _animacao.atualizar(DIREITA,"CORRER");
        else 
        _animacao.atualizar(ESQUERDA,"CORRER");
    }
    else if (!estaNoChao && _corpo.getPosition().y > NIVEL_DA_PLATAFORMA) {
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"PULAR");
        else 
        _animacao.atualizar (ESQUERDA,"PULAR"); 
    }
    else if (atacando){
              _tempoAtaque += gGrafico->get_tempo();
        if (_tempoAtaque >= DURACAO_ATAQUE_TOTAL){
            atacando = false;
            _tempoAtaque = 0.0f;
            return;
        }
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"ATACAR");
        else 
        _animacao.atualizar (ESQUERDA,"ATACAR"); 
    }
    else {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA,"PARADO");
        else 
            _animacao.atualizar(ESQUERDA,"PARADO");
    }
}

void Jogador::inicializarBarraVida()
{
    sf::Vector2f tamanhoTubo = sf::Vector2f (TAMANHO_BARRA_VIDA_EIXO_X,TAMANHO_BARRA_VIDA_EIXO_Y);           // pega o tamanho do tubo da barra de vida
    _tuboBarraVida.setSize (tamanhoTubo);                                                                    // define o tamanho do tubo de barra de vida
    _barraVida.setSize(tamanhoTubo);                                                                         // define o tamanho da barra de vida (interna ao tubo da vida)
    sf::Texture* texturaVida = new sf::Texture();                                                            // aloca um espaco para a textura da barra de vida
    sf::Texture* texturaTubo = new sf::Texture();                                                            // aloca um espaco para a textura do tudo da barra de vida 
    texturaVida-> loadFromFile("VidaJogador.png");                                                          // carrega a textura da barra de vida
    texturaTubo-> loadFromFile("BarraVida.png");                                                            // carrega a textura do tubo da barra de vida
    // atualiza as texturas
    _barraVida.setTexture(texturaVida);                                                                 
    _tuboBarraVida.setTexture(texturaTubo);
}

// funcao que atualiza a posicao e o tamanho e quanta vida o personagem possui
void Jogador::atualizarBarraVida()
{
    // pega a posicao e o tamanho da janela
    sf::Vector2f posicaoJanela = gGrafico->get_camera().getCenter();
    sf::Vector2f tamanhoJanela (TAMANHO_TELA_X,TAMANHO_TELA_Y);
    // atualiza a posicao da barra de vida
    sf::Vector2f posicaoBarra = sf::Vector2f (posicaoJanela.x - tamanhoJanela.x / 2.0f + 10.0f, posicaoJanela.y - tamanhoJanela.y / 2.0f + 30.0f);     
    _tuboBarraVida.setPosition(posicaoBarra);
    _barraVida.setSize(sf::Vector2f((TAMANHO_BARRA_VIDA_EIXO_X - 40.0f) * (_vida / 100.0f), TAMANHO_BARRA_VIDA_EIXO_Y - 13.0f));
    _barraVida.setPosition(sf::Vector2f(posicaoBarra.x + 7.0f, posicaoBarra.y + _tuboBarraVida.getSize().y / 2.0f - _barraVida.getSize().y / 2.0f));

}

// funcao que iniciliza tudo relacionado a experiencia / nivel do jogador
void Jogador::inicializarNivel()
{
    _textoNivel.set_tamanhoFonte(20);
    _textoNivel.set_informacao ("Lv." + std::to_string(_experiencia.get_nivel()));
    _textoNivel.set_tamanhoBorda (2);
    _experiencia.set_forca (FORCA_JOGADOR);
    _experiencia.set_defesa (DEFESA_JOGADOR);
}

// funcao que atualiza a o texto do nivel do jogador
void Jogador::atualizarNivel()
{
    sf::Vector2f posicao = _tuboBarraVida.getPosition();
    _textoNivel.set_posicao (sf::Vector2f (posicao.x + 5.0f, posicao.y - _textoNivel.get_tamanho().y - 12.0f));
}

void Jogador::resetarEstado()
{
    _velocidade = sf::Vector2f(VELOCIDADE_JOGADOR_X, VELOCIDADE_JOGADOR_Y);
    _vida = 100.0f;
    morrendo = false;
    andando = false;
    atacando = false;
    levandoDano = false;
    _congelaJogo = false;
}

void Jogador::inicializarBarraXP()
{
    // pega o tamanho do tubo da barra de vida
    sf::Vector2f tamanhoTubo = sf::Vector2f (TAMANHO_BARRA_VIDA_EIXO_X,TAMANHO_BARRA_VIDA_EIXO_Y);        
    // define o tamanho do tudo da barra de xp 
    _tuboBarraXP.setSize (tamanhoTubo);
    // aloca um espaco para as texturas da barra de xp e do tubo da barra de xp                                                                 
    sf::Texture* texturaXP = new sf::Texture();                                                            
    sf::Texture* texturaBarraXP = new sf::Texture();
    // carrega as texturas                                                            
    texturaXP-> loadFromFile("XPJogador.png");                                                         
    texturaBarraXP-> loadFromFile("BarraXP.png");                                                            
    // atualiza as texturas
    _barraXP.setTexture(texturaXP);                                                                 
    _tuboBarraXP.setTexture(texturaBarraXP);

}

void Jogador::atualizarBarraXP()
{
    // pega a posicao e o tamanho da janela
    sf::Vector2f posicaoJanela = gGrafico->get_camera().getCenter();
    sf::Vector2f tamanhoJanela (TAMANHO_TELA_X,TAMANHO_TELA_Y);
    // atualiza a posicao da barra de vida
    sf::Vector2f posicaoBarra = sf::Vector2f ((posicaoJanela.x + tamanhoJanela.x / 2.0f - _tuboBarraXP.getSize().x - 10.0f), posicaoJanela.y + tamanhoJanela.y / 2.0f - 30.0f);     
    _tuboBarraXP.setPosition(posicaoBarra);
    _barraXP.setSize(sf::Vector2f((TAMANHO_BARRA_VIDA_EIXO_X - 40.0f) * (_experiencia.get_experiencia() / PROXIMO_NIVEL), TAMANHO_BARRA_VIDA_EIXO_Y - 13.0f));
    _barraXP.setPosition(sf::Vector2f((posicaoBarra.x + _tuboBarraVida.getSize().x - _barraXP.getSize().x - 7.0f), posicaoBarra.y + _tuboBarraXP.getSize().y / 2.0f - _barraXP.getSize().y / 2.0f));
}

// funcao que inicializa tudo relacionado a experiencia do jogador
void Jogador::inicializarXP()
{
    std::string XPatual = std::to_string (_experiencia.get_experiencia());
    XPatual = XPatual.substr (0,XPatual.find(".") + 2);
     _textoXP.set_informacao(XPatual);
    //_textoXP.set_tamanhoBorda(2);
}

// funcao que atualiza a barra dexp do jogador
void Jogador::atualizarXP()
{
    sf::Vector2f posicaoBarraXP (_tuboBarraXP.getPosition());
    _textoXP.set_posicao(sf::Vector2f(posicaoBarraXP.x + _tuboBarraXP.getSize().x - _textoXP.get_tamanho().x - 5.0f, posicaoBarraXP.y - _textoXP.get_tamanho().y - 12.0f));

    inicializarXP();
}



// construtor 
Jogador::Jogador (sf::Vector2f posicao) :
    Personagem (posicao,sf::Vector2f (TAMANHO_JOGADOR_X,TAMANHO_JOGADOR_Y), sf::Vector2f(VELOCIDADE_JOGADOR_X,VELOCIDADE_JOGADOR_Y), Identificador::jogador , DURACAO_JOGADOR_MORTE, DURACAO_JOGADOR_SOFRER_DANO) ,
     estaNoChao (false) , _textoXP (gGrafico->carregarFonte("FonteNivel.ttf"),"",20) , _congelaJogo (false)
    {
       //resetarEstado ();
        std::cout << "vida jogador inicio: " << _vida << std::endl;

        inicializarAnimacao();
        inicializarBarraVida();
        inicializarBarraXP ();
        inicializarNivel ();
        inicializarXP ();

        Arma* espada = new Arma (Identificador::espada_jogador);
        espada->set_tamanho (sf::Vector2f(TAMANHO_ARMA, TAMANHO_ARMA));
        set_arma (espada);
        if (_arma){
        _arma->set_personagem(this);
        _arma->set_dano(_experiencia.get_forca());
        }


    }
    
// destrutor
Jogador::~Jogador () 
{
    // deleta as texturas utilizadas por meio de ponteiros
    if (_tuboBarraVida.getTexture ()){
        delete(_tuboBarraVida.getTexture());
    }
    if (_barraVida.getTexture ()){
        delete(_barraVida.getTexture());
    }
    if (_tuboBarraXP.getTexture ()){
        delete(_tuboBarraXP.getTexture());
    }
    if (_barraXP.getTexture ()){
        delete(_barraXP.getTexture());
    }
}

// funcao que retorna se o jogador esta no chao (na plataforma)
bool Jogador::get_estaNoChao()
{
    return estaNoChao;
}

// funcao que retorna se o jogador esta andando
bool Jogador::estaAndando()
{
    return andando;
}

// funcao que retorna se o jogador morreu e congelou a tela do jogo
bool Jogador::estaCongeladoJogo()
{
    return _congelaJogo;
}

// funcao que atualiza a vida do jogador
void Jogador::set_vida(float vida)
{
    _vida += vida;
    if (_vida >= 100.0f) {
        _vida = 100.0f;
    }
}

// funcao que adiciona experiencia ao jogador
void Jogador::adicionarXP(float experiencia)
{
    _experiencia.adicionarExperiencia(experiencia);
    _textoNivel.set_informacao ("Lv." + std::to_string(_experiencia.get_nivel()));

    inicializarXP();
}


void Jogador::pular()
{
    // verifica se pode pular 
    if (estaNoChao) {
        _velocidade.y = TAMANHO_PULO;
        estaNoChao = false;
        atacando = false;
    }

}

void Jogador::podePular()
{ 
    estaNoChao = true;
}


void Jogador::colisao(Entidade *entidade, sf::Vector2f distancia)
{
    static bool jaColidiu = false;

    switch (entidade->get_id()) {
        case (Identificador::plataforma): {
            Plataforma* plataforma = dynamic_cast<Plataforma*>(entidade);
            if (plataforma) {
                plataforma->colisaoObstaculo(distancia, this);
            }

        }
        break;

        case (Identificador::espada_esqueleto) : {
            Arma* arma = dynamic_cast < Arma* > (entidade);
            if (arma){
            tomarDano(arma->get_dano());
            //std::cout << "vida jogador: " << _vida << std::endl;
            }
        }
        break;

        case (Identificador::morcego) : {
            Morcego* morcego = dynamic_cast <Morcego*> (entidade);
            if (morcego->estaAtacando())
                tomarDano(morcego->get_forca());
            //std::cout << "vida jogador: " << _vida << std::endl;
            break;
        }
        case (Identificador::faca_goblin) : {
            Arma* arma = dynamic_cast < Arma* > (entidade);
            if (arma){
            tomarDano(arma->get_dano());
            //std::cout << "vida jogador: " << _vida << std::endl;
            }
        }
        break;

        case (Identificador::projetil_alma) : {
            Projetil* projetil = dynamic_cast <Projetil*> (entidade);
            tomarDano (projetil->get_dano());
            projetil->set_colidiu (true); 
        }
        break;

        case (Identificador::cajado_chefao) : {
            Arma* cajado = dynamic_cast <Arma*> (entidade);
            tomarDano (cajado->get_dano());
            //std::cout << "vida jogador: " << _vida << std::endl;
        }
        break;
    }
}

void Jogador::atacar(bool atacar)
{
    if (atacar && !morrendo){
        this->atacando = true;
        this->_tempoAtaque = 0.0f;
    }
}

// funcao que movimenta o jogador para as quatro direcoes
void Jogador::atualizar () {

        if (morrendo) {
            atualizarAnimacao();
            atualizarBarraVida();

            _congelaJogo = true;
        }
        else {
            atualizarTempoProtegido();
        
            if (!levandoDano){                  // evita de atualizar a posicao quando sofre ataques
            atualizarPosicao();
            }

            atualizarAnimacao();
            atualizarBarraVida();
            atualizarBarraXP();
            atualizarNivel();
            atualizarXP ();
        }

}

void Jogador::atualizarPosicao()
{
    // Movimento horizontal - Simplificado para evitar colisões falsas
    if (andando) {
        float deltaX = (andaEsquerda) ? -_velocidade.x : _velocidade.x;
        _corpo.move(deltaX, 0.0f);
    }
        // Se está no nível do chão mas não tem plataforma, começa a cair
    if (estaNoChao && _corpo.getPosition().y < NIVEL_DA_PLATAFORMA) {
        estaNoChao = false;
        _velocidade.y = 0.0f;
    }
    
    // Movimento vertical (pulo) - só aplica gravidade se não estiver no chão
    if (!estaNoChao) {
        _velocidade.y += GRAVIDADE;
        _corpo.move(0.0f, _velocidade.y);
    }

    // Colisão com o chão - apenas quando realmente estiver abaixo do nível
    if (_corpo.getPosition().y > NIVEL_DA_PLATAFORMA) {
        _corpo.setPosition(_corpo.getPosition().x, NIVEL_DA_PLATAFORMA);
        _velocidade.y = 0.0f;
        estaNoChao = true;
    }

    //std::cout << "posicao corpo: " << _corpo.getPosition ().x << " , "<< _corpo.getPosition ().y <<   std::endl;
    if (_corpo.getPosition ().x >= 4700.0f &&
        _corpo.getPosition().y >= 275.0f) {     // encontrou a coroa
        _congelaJogo = true;
    }       
}

void Jogador::desenhar()
{
    gGrafico->desenhar (_corpo);
    gGrafico-> desenhar (_tuboBarraVida);
    gGrafico-> desenhar (_barraVida);
    gGrafico-> desenhar (_tuboBarraXP);
    gGrafico-> desenhar (_barraXP);

}