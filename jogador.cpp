#include "jogador.h"
#include "inimigo.h"
#include "plataforma.h"
#include "arma.h"
#include <iostream>

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
    else if (!estaNoChao) {
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"PULAR");
        else 
        _animacao.atualizar (ESQUERDA,"PULAR"); 
    }
    else if (levandoDano) {
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"TOMARDANO");
        else 
        _animacao.atualizar (ESQUERDA,"TOMARDANO"); 
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
    else if (andando){
        if (!andaEsquerda)
        _animacao.atualizar(DIREITA,"CORRER");
        else 
        _animacao.atualizar(ESQUERDA,"CORRER");
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
    _textoNivel.set_informacao ("Level" + std::to_string(_experiencia.get_nivel()));
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
    XPatual = XPatual.substr (0,XPatual.find("v") + 4);
   // _textoXP.set_informacao(XPatual);
    //_textoXP.set_tamanhoBorda(2);
}

// funcao que atualiza a barra dexp do jogador
void Jogador::atualizarXP()
{
    sf::Vector2f posicaoBarraXP (_tuboBarraXP.getPosition());
    //_textoXP.set_posicao(sf::Vector2f(posicaoBarraXP.x + _tuboBarraXP.getSize().x - _textoXP.get_tamanho().x - 5.0f, posicaoBarraXP.y - _textoXP.get_tamanho().y - 12.0f));
}

// metodo que atualiza as chaves do jogo
void Jogador::atualizarChaves()    // talvez nao precise
{

}

// construtor 
Jogador::Jogador (sf::Vector2f posicao) :
    Personagem (posicao,sf::Vector2f (TAMANHO_JOGADOR_X,TAMANHO_JOGADOR_Y), sf::Vector2f(VELOCIDADE_JOGADOR_X,VELOCIDADE_JOGADOR_Y), Identificador::jogador , DURACAO_JOGADOR_MORTE, DURACAO_JOGADOR_SOFRER_DANO) ,
     estaNoChao (false) , _tempoAtaque(0.0f) 
    {
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
        /*if (_arma != nullptr){
            set_arma(arma);
            _arma->set_dano()
        }*/
       //gGrafico->set_limiteObjeto(sf::IntRect(_posicao.x,_posicao.y,_tamanho.x,_tamanho.y));
       
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

// funcao que atualiza caso o jogador esteja colidindo com uma porta ou nao
void Jogador::set_colidirPorta(bool colidindoPorta)
{
    this->colisaoPorta = colidindoPorta;
}

// funcao que retorna se o jogador esta colidindo ou nao com uma porta 
bool Jogador::estaColidindoPorta()
{
    return colisaoPorta;
}

// funcao que atualiza caso o jogador esteja abrindo uma porta ou nao
void Jogador::set_abrirPorta(bool abrirPorta)
{
    this->abrirPorta = abrirPorta;
}

// funcao que retorna se o personagem esta ou nao abrindo uma porta
bool Jogador::estaAbrindoPorta()
{
    return abrirPorta;
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
    _textoNivel.set_informacao ("Level" + std::to_string(_experiencia.get_nivel()));
    inicializarXP();
}

// funcao que retorna as chaves coletadas pelo jogador 
/*std::vector<Chave *> Jogador::get_chaves()
{
    return _chaves;
}

// funcao que adiciona uma chave coletada no vector de chaves
void Jogador::adicionarChave(Chave *chave)
{
    if (chave && !chave->get_coletou ()){
    _chaves.push_back(chave);
    chave->set_coletar (true);
    }
}

// funcao que remove uma chave ja utilizada do vector de chaves
void Jogador::removerChave(Chave *chave)
{
    if (!chave) return;

    for (int i=0 ; i < _chaves.size(); i++){                    // percorre o vector
        if (_chaves[i] == chave){                               // se achar a chave passada no parametro
            _chaves.erase(_chaves.begin() + i);                 // remover ela do vector
            return;                                             // encerra o programa
        }
    }
}*/

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
            break;
        }
        case (Identificador::espada_esqueleto) : {
            Arma* arma = dynamic_cast < Arma* > (entidade);
            if (arma){
            tomarDano(arma->get_dano());
            std::cout << "vida jogador: " << _vida << std::endl;
            }
            break;
        }
        case (Identificador::esqueleto): {
            // Colisão com o inimigo
           /*sf::Vector2f posicaoAtual = get_posicao();
            sf::Vector2f posicaoInimigo = entidade->get_posicao();

            // Empurra o jogador para fora do inimigo
            if (fabs(distancia.x) < fabs(distancia.y)) {
                posicaoAtual.x += (posicaoAtual.x < posicaoInimigo.x) ? -2.0f : 2.0f;
            } else {
                posicaoAtual.y += (posicaoAtual.y < posicaoInimigo.y) ? -2.0f : 2.0f;
            }
            set_posicao(posicaoAtual);*/
            /*sf::Vector2f posicaoInimigo = entidade->get_posicao();
            Inimigo* inimigo = dynamic_cast < Inimigo* > (entidade);
            if (_posicao.x < posicaoInimigo.x){
                distancia.x *= -1;
            }*/
            
            break;
        }

        case (Identificador::porta): {
            if (!jaColidiu){
            set_colidirPorta(true);
            jaColidiu = true;
            }
            break;
        }
        /*case (Identificador::chave) : {
        if (!jaColidiu){
            Chave* chave = dynamic_cast < Chave* > (entidade);
            if (chave && !chave->get_coletou()){
                adicionarChave(chave);
            } 
            jaColidiu = true;
        }
            break;
        }
    }

        if (entidade->get_id() == Identificador::porta || entidade->get_id() == Identificador::chave) {
        jaColidiu = false;*/
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

        atualizarTempoProtegido();
        
        if (!levandoDano){                  // evita de atualizar a posicao quando sofre ataques
        atualizarPosicao();
        }

        atualizarAnimacao();
        atualizarBarraVida();
        atualizarBarraXP();
        atualizarNivel();
        atualizarXP ();

        set_colidirPorta (false);


    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {          // se a tecla pressionada for A ou seta para esquerda, move para esquerda
        _corpo.move(-_velocidade.x,0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){     // se a tecla pressionada for D ou seta para direita, move para direita
        _corpo.move(+_velocidade.x,0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){        // se a tecla pressionada for W ou seta para cima, move para cima
        _corpo.move(0.0f,-_velocidade.y);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){      // se a tecla pressionada for S ou seta para baixo, move para baixo
        _corpo.move(0.0f,+_velocidade.y);
    }*/
}

void Jogador::atualizarPosicao()
{
    // Salva a posição antiga
    sf::Vector2f posicaoAntiga = _corpo.getPosition(); // ttemporario

    // Movimento horizontal
    if (andando) {
        if (andaEsquerda)
            _corpo.move(-_velocidade.x, 0.0f);
        else 
            _corpo.move(_velocidade.x, 0.0f);
    }
    
    // Movimento vertical (pulo)
    _velocidade.y += GRAVIDADE;
    _corpo.move(0.0f, _velocidade.y);

    // Colisão com o chão
    if (_corpo.getPosition().y >= NIVEL_DA_PLATAFORMA) {
        _corpo.setPosition(_corpo.getPosition().x, NIVEL_DA_PLATAFORMA);
        _velocidade.y = 0;
        estaNoChao = true;
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

/*void Jogador::atualizarPosicao()
{
    // movimentacao com base no movimento uniforme
    deltaTempo = gGrafico->get_tempo ();                   // variacao do tempo
    sf::Vector2f deltaDistancia (0.0f,0.0f);               // variacao da distancia

    // movimentacao no eixo horizontal
    if (andando && !morrendo){                                  // se estiver andando e nao estiver morrendo
        deltaDistancia.x = _velocidade.x * deltaTempo;          // se move para a direita no eixo x
        if (andaEsquerda)                                       // se estiver andando para esquerda
            deltaDistancia.x *= -1;                             // apenas multiplica por -1 para inverter o sentido e andar para a esquerda
    }

    // movimentacao na vertical, baseada no movimento uniformemente variado vertical
    float velocidadeInicial = _velocidade.y;
    _velocidade.y += (GRAVIDADE * deltaTempo);
    deltaDistancia.y = (velocidadeInicial * deltaTempo) + (_velocidade.y * deltaTempo * deltaTempo) / 2.0f;
    /*if (andando && !morrendo){
        if (andaEsquerda)
            _corpo.move(-_velocidade.x,0.0f);
        else 
            _corpo.move(+_velocidade.x,0.0f);
    }
    
    // movimentacao do pulo
    _velocidade.y += GRAVIDADE;                     // sofre acao da gravidade
    _corpo.move (0.0f,_velocidade.y);              // move o corpo

    // verificacao se ja chegou ao solo novamente
    if (_corpo.getPosition().y >= NIVEL_DA_PLATAFORMA){
        _corpo.setPosition(_corpo.getPosition().x,NIVEL_DA_PLATAFORMA);
        _velocidade.y = 0;
        estaNoChao = true;
    }
}*/

