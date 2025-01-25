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
     sf::Vector2f origem = sf::Vector2f(_tamanho.x / 4.0f, _tamanho.y / 4.4f);                                          // seta a origem das texturas
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

void Alma::inicializarNivel()
{
    _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));
    _textoNivel.set_tamanhoBorda(2);
}

void Alma::atualizarTempoAtaque()
{
    float tempo = gGrafico->get_tempo();
    if (atacando) {
        _tempoAtaque += tempo;
        if (_tempoAtaque > _duracaoAnimacaoAtaque) {
            if (_arma == nullptr) {
                throw std::invalid_argument("Falta inicializar a arma primeiro");
            }

            Projetil* projetil = dynamic_cast<Projetil*>(_arma);
            if (projetil) {
                // Ajusta a posição do projétil para sair do centro da alma
                sf::Vector2f posicaoAlma = get_posicao();
                float alturaProjeto = posicaoAlma.y;  // topo da alma
                float xProjeto;
                
                if (andaEsquerda) {
                    xProjeto = posicaoAlma.x - TAMANHO_PROJETIL;
                } else {
                    xProjeto = posicaoAlma.x + _tamanho.x;
                }

                projetil->set_posicao(sf::Vector2f(xProjeto, alturaProjeto));
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
    invisivel (false) , _tempoInvisivel (0.0f)
{
    _experiencia.set_nivel (4);
    
    inicializarAnimacao ();
    inicializarNivel ();   // corrigir


    _experiencia.set_forca (FORCA_ALMA);
    _experiencia.set_defesa (DEFESA_ALMA);


    Projetil* projetil = new Projetil (this);
    set_arma (projetil);

    if (_arma) {
        _arma->set_dano (_experiencia.get_forca());
    }

}

Alma::~Alma()
{
    if (_arma) {
        _arma->remover ();
    }
}

bool Alma::estaInvisivel()
{
    return invisivel;
}

void Alma::tomarDano(float dano)
{
    if (inativo) return;

    if (!levandoDano && !_protegido && !invisivel) {
        _protegido = true;
        levandoDano = true;
        andando = false;
        atacando = false;
        _vida -= dano; // apenas para simplificar, * (dano / _experiencia.get_defesa());
        if (_vida <= 0.0f) {
            morrendo = true;
            atacando = false;
            _vida = 0.0f;
        }
        invisivel = true;
        _corpo.setFillColor(sf::Color (110,110,110,110));
        _tempoDano = 0.0f;
        _tempoProtecaoAtaque = 0.0f;
        _tempoInvisivel = 0.0f;
    }
}

void Alma::atualizar()
{
        if (!inativo) {
        // Adicione esta verificação do tempo de invisibilidade
        if (invisivel) {
            _tempoInvisivel += gGrafico->get_tempo();
            if (_tempoInvisivel >= TEMPO_INVISIVEL_ALMA) {
                invisivel = false;
                _tempoInvisivel = 0.0f;
                _corpo.setFillColor(sf::Color(255, 255, 255, 255)); // Retorna à cor normal
            }
        }

        // Resto do código de atualização
        atualizarTempoAtaque();
        moverInimigo();
        atualizarPosicao();
        atualizarAnimacao();
        atualizarBarraVida();
        atualizarNivel();

        if (_protegido) {
            _tempoProtecaoAtaque += gGrafico->get_tempo();
            if (_tempoProtecaoAtaque >= TEMPO_RECUPERACAO_DANO_ALMA) {
                _protegido = false;
                levandoDano = false;
                _tempoProtecaoAtaque = 0.0f;
            }
        }
    }
}
