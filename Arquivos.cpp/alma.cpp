#include "alma.h"
#include "projetil.h"

// funcao responsavel pela movimentacao da alma
void Alma::moverInimigo()
{
    if (!_jogador) return;                                                          // verificacao se o jogador nao e nulo
    
    if (!morrendo && !atacando) {

        // pega as posicoes do jogador e do inimigo
        sf::Vector2f posicaoJogador = _jogador->get_corpo().getPosition();          
        sf::Vector2f posicaoInimigo = _corpo.getPosition();
        
        // verifica se está na zona de combate
        if (fabs(posicaoJogador.x - posicaoInimigo.x) <= RAIO_DE_COMBATE_ALMA_X )
            {
            
            andaEsquerda = (posicaoJogador.x < posicaoInimigo.x);                       // verifica pra qual lado tem que andar
            
            if (invisivel) {
                // Se estiver invisível, foge do jogador
                andar(!andaEsquerda);
                _velocidade = sf::Vector2f(_velocidade.x * 1.5f, _velocidade.y);            // velocidade um pouco maior para fugir
            } else {
                // Se estiver visível, pode ser atacada e atacar
                parar();
                if (_arma != nullptr) {                                                             
                    Projetil* projetil = dynamic_cast<Projetil*>(_arma);                // cria o projetil da alma
                    if (projetil && projetil->ocorreuColisao()) {                       // verifica se ocorreu colisao desse projetil
                        // faz a verificacao do tempo da animacao de ataque para sincronizar o projetil na tela
                        _tempoAtaque += gGrafico->get_tempo();
                        if (_tempoAtaque > _duracaoAnimacaoAtaque) {
                            atacando = true;
                            _tempoAtaque = 0.0f;
                        }
                    }
                }
            }
        } else {
            atualizarMovimentacao();
            _tempoAtaque = 0.0f;
        }
    }
}

// funcao que inicializa as animacoes da alma
void Alma::inicializarAnimacao()
{
     sf::Vector2f origem = sf::Vector2f(_tamanho.x / 4.0f, _tamanho.y / 4.4f);                                              // seta a origem das texturas

     // adiciona as texturas
    _animacao.adicionarAnimacao("AlmaParado.png", "PARADO", 5, 0.12f, sf::Vector2f(2.5f, 1.5f), origem, false);
    _animacao.adicionarAnimacao("Anda.png", "ANDA", 8, 0.15f, sf::Vector2f(2.5f, 1.5f), origem, false);
    _animacao.adicionarAnimacao("Morre.png", "MORRE", 8, 0.2f, sf::Vector2f(2.5f, 1.5f), origem, false);
    _animacao.adicionarAnimacao("Ataca.png", "ATACAR", 10, 0.20f, sf::Vector2f(2.5f, 1.5f), origem, false);
}

// funcao que atualiza as animacoes da alma
void Alma::atualizarAnimacao()
{
    // verifica os estados da alma, se esta morrendo, atacando, andando ... e apos isso indica qual animacao usar e pra qual direcao

    if (morrendo) {                                                                     // se estiver morrendo
        if (!andaEsquerda)                                                              // se estiver andando para direita
        _animacao.atualizar(DIREITA,"MORRE");                                           // ativa a animacao de morte para a direita
         else
        _animacao.atualizar(ESQUERDA, "MORRE");                                         // se for para a esquerda, ativa para a esquerda

        // verifica o tempo
        _tempoMorte += gGrafico->get_tempo();
        if (_tempoMorte >= _duracaoAnimacaoMorte && !inativo ){
            _jogador->adicionarXP(XP);
            inativo = true;          
            _corpo.setFillColor (sf::Color::Transparent);                               // desaparece com o corpo
            if (_arma != nullptr){
                Projetil* projetil = dynamic_cast <Projetil*> (_arma);
                if (projetil->ocorreuColisao ()){
                    _arma->remover ();
                    _arma = nullptr;
                }
            }
        }
        return;
    }
    else if (atacando){
            _tempoAtaque += gGrafico->get_tempo();
        if (_tempoAtaque >= TEMPO_ATAQUE_ALMA){
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
        _animacao.atualizar(DIREITA,"ANDA");
        else 
        _animacao.atualizar(ESQUERDA,"ANDA");
    }
    else {
        if (!andaEsquerda)
            _animacao.atualizar(DIREITA,"PARADO");
        else 
            _animacao.atualizar(ESQUERDA,"PARADO");
    }
}

// funcao responsavel pela inicializacao as informacoes relacionadas ao nivel dos personagens
void Alma::inicializarNivel()
{
    _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));              // ajusta o texto
    _textoNivel.set_tamanhoBorda(2);                                                            // ajusta o tamanho da borda
}

// funcao que atualiza o tempo de ataque da alma
void Alma::atualizarTempoAtaque()
{
    float tempo = gGrafico->get_tempo();                                                                // pega o tempo

    if (atacando) {                                                                                     // se ela tiver atacando, sincroniza o tempo de ataque com a animacao
        _tempoAtaque += tempo;
        if (_tempoAtaque > _duracaoAnimacaoAtaque) {
            if (_arma == nullptr) {
                throw std::invalid_argument("Falta inicializar a arma primeiro");
            }

            Projetil* projetil = dynamic_cast<Projetil*>(_arma);
            if (projetil) {

                // Ajusta a posição do projétil para sair do topo da alma
                sf::Vector2f posicaoAlma = get_posicao();
                float alturaProjetil = posicaoAlma.y;  
                float xProjetil;
                
                // verifica qual a direcao que o projetiol esta indo
                if (andaEsquerda) {                                                      
                    xProjetil = posicaoAlma.x - TAMANHO_PROJETIL;
                } else {
                    xProjetil = posicaoAlma.x + _tamanho.x;
                }

                // atualiza a posicao, velocidade e sentido do projetil
                projetil->set_posicao(sf::Vector2f(xProjetil, alturaProjetil));
                projetil->set_colidiu(false);
                projetil->set_velocidade(sf::Vector2f(300.0f, 0.0f)); 
                projetil->set_sentido(andaEsquerda);
                atacando = true;
                _tempoAtaque = 0.0f;
            }
        }
    }

}

// construtor
Alma::Alma(sf::Vector2f posicao, Jogador *jogador) :
    Inimigo (posicao, sf::Vector2f (TAMANHO_ALMA_X,TAMANHO_ALMA_Y), jogador , Identificador::alma, TEMPO_MORTE_ALMA, TEMPO_ATAQUE_ALMA,EXPERIENCIA_ALMA),
    invisivel (false),
    _tempoInvisivel (0.0f)
{
    // inicializa o nivel do personagem
    _experiencia.set_nivel (4);
    
    inicializarAnimacao ();
    inicializarNivel ();   

    // atualiza a forca e a defesa da alma
    _experiencia.set_forca (FORCA_ALMA);
    _experiencia.set_defesa (DEFESA_ALMA);

    // cria a arma (no caso o projetil)
    Projetil* projetil = new Projetil (this);
    set_arma (projetil);

    if (_arma) {
        _arma->set_dano (_experiencia.get_forca());
    }

}

// destrutor 
Alma::~Alma()
{
    if (_arma) {
        _arma->remover ();
    }
}

// funcao que retorna se ela esta invisivel ou nao
bool Alma::estaInvisivel()
{
    return invisivel;
}

// funcao responsavel por sofrer dano 
void Alma::tomarDano(float dano)
{
    if (inativo) return;                                                    // verificacao para ver se nao morreu

    // se nao tiver levando dano e nao tiver invisivel e nao tiver protegida, entao pode tomar dano
    if (!levandoDano && !_protegido && !invisivel) {

        // atualiza os estados do inimigo
        _protegido = true;
        levandoDano = true;
        andando = false;
        atacando = false;
        _vida -= dano; 

        // se a vida for menor que 0
        if (_vida <= 0.0f) {
            morrendo = true;                // atualiza o estado de morte
            atacando = false;
            _vida = 0.0f;
        }

        // se foi atacada e nao morreu, atualiza os estados
        invisivel = true;
        _corpo.setFillColor(sf::Color (110,110,110,110));           // fica meio transparente

        // reseta os tempos
        _tempoDano = 0.0f;
        _tempoProtecaoAtaque = 0.0f;
        _tempoInvisivel = 0.0f;
    }
}

// funcao que atualiza todas as outras da alma
void Alma::atualizar()
{
        if (!inativo) {                                                     // verifica se esta vivo
        if (invisivel) {                                                    // se estiver invisivel
            _tempoInvisivel += gGrafico->get_tempo();                       // sincroniza o tempo que ele fica invisivel
            if (_tempoInvisivel >= TEMPO_INVISIVEL_ALMA) {

                // quando acabar o tempo invisivel, reseta os estados
                invisivel = false;
                _tempoInvisivel = 0.0f;
                _corpo.setFillColor(sf::Color(255, 255, 255, 255));          // retorna a cor normal
            }
        }

        // atualiza todos os metodos
        atualizarTempoAtaque();
        moverInimigo();
        atualizarPosicao();
        atualizarAnimacao();
        atualizarBarraVida();
        atualizarNivel();

        // se tiver protegido (cooldown)
        if (_protegido) {                                                               // sincroniza o tempo de cooldown para nao tomar multiplos ataques
            _tempoProtecaoAtaque += gGrafico->get_tempo();
            if (_tempoProtecaoAtaque >= TEMPO_RECUPERACAO_DANO_ALMA) {

                // quando acabar o tempo de cooldown, reseta os estados
                _protegido = false;
                levandoDano = false;
                _tempoProtecaoAtaque = 0.0f;
            }
        }
    }
}
