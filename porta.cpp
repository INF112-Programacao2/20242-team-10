#include "porta.h"
#include "jogador.h"
#include <iostream>

void Porta::inicializarAnimacao()
{
    sf::Vector2f origem (0.0f,-10.0f);
    _animacao.adicionarAnimacao ("PortaFechada.png" , "PORTA_FECHADA" , 1 , 1.0f , sf::Vector2f (1.0f,1.0f) ,origem , false);
}

void Porta::atualizarAnimacao()
{
    if (_fechada) {
        _animacao.atualizar(DIREITA, "PORTA_FECHADA");
    }
    else  
        _corpo.setFillColor (sf::Color::Black);
}

// funcao que inicializa tudo relacionado aos textos da porta do jogo
void Porta::inicializarTexto(std::string texto)
{
       if (texto.empty()) {
        _mostrarTexto = false;
        return;
    }

    try {
        _textoPorta.set_informacao(texto);
        _textoPorta.set_tamanhoBorda(1);
        _textoPorta.set_espacamento(0.5f);
        
        sf::Vector2f posTexto(_posicao.x + _tamanho.x / 2.0f, _posicao.y - 30.0f);
        _textoPorta.set_posicao(posTexto);
        
        sf::Vector2f tamanhoTexto = _textoPorta.get_tamanho();
        caixaTexto.setSize({tamanhoTexto.x + 15.0f, tamanhoTexto.y + 15.0f});
        caixaTexto.setPosition(posTexto.x - (tamanhoTexto.x + 15.0f) / 2.0f, posTexto.y - 5.0f);
        caixaTexto.setFillColor(sf::Color(0, 0, 0, 100));
        
    } catch (const std::exception& e) {
        std::cout << "Erro ao inicializar texto: " << e.what() << std::endl;
        _mostrarTexto = false;
    }
}

// construtor
Porta::Porta(sf::Vector2f posicao, sf::Vector2f tamanho ,Identificador id) : 
    Obstaculo (posicao, tamanho,Identificador::porta), _animacao (&_corpo), _tempoAberturaPorta (0.0f) , 
    _fechada (true), _abrindo (false) , _mostrarTexto (false) , _coletou (false) , fundoPorta (), _textoPorta (gGrafico->carregarFonte("FonteNivel.ttf"),"",30), _completou (false)
{
    inicializarAnimacao ();
    
}

Porta::~Porta()
{
}

/*Chave *Porta::get_chave()
{
    return chave;
}*/

bool Porta::estaFechada()
{
    return _fechada;
}

bool Porta::completouTransicao() const
{
    return _completou;
}

// funcao que atualiza e verifica todas as variaveis quando houve uma colisao da porta com o jogador 
void Porta::colisaoJogador(Jogador *jogador)
{
    /*if (!jogador) return;

    try {
        _mostrarTexto = true;
        if (!chave) {
            inicializarTexto("Pressione 'E' para Entrar");
            return;
        }

        std::vector<Chave*> chavesJogador = jogador->get_chaves();
        bool temChave = false;

        for (size_t i = 0; i < chavesJogador.size(); i++) {
            if (chavesJogador[i] && chavesJogador[i] == this->chave) {
                temChave = true;
                break;
            }
        }

        if (_fechada) {
            if (temChave && jogador->estaAbrindoPorta()) {
                _fechada = false;
                _abrindo = true;
                jogador->removerChave(chave);
                _corpo.setFillColor(sf::Color::Transparent);
                chave = nullptr;
            } else if (temChave) {
                inicializarTexto("Pressione E para abrir");
            } else {
                inicializarTexto("Precisa de uma chave!");
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Erro na colisão com porta: " << e.what() << std::endl;
    }*/
        if (!jogador) return;

    if (!_coletou) {
        _mostrarTexto = true;
        inicializarTexto("Necessario uma chave!");
    }
    else {
        _mostrarTexto = true;
        if (_fechada && jogador->estaAbrindoPorta()) {
            _fechada = false;
            _abrindo = true;
            inicializarTexto("Pressione 'E' para Entrar");
            _corpo.setFillColor(sf::Color(128, 128, 128));
        }
        else if (_abrindo) {
            if (jogador->estaAbrindoPorta()) {
                _tempoAberturaPorta += gGrafico->get_tempo();
                if (_tempoAberturaPorta >= TEMPO_ENTRADA_NA_PORTA) {
                    _completou = true;
                    _mostrarTexto = false;
                    _tempoAberturaPorta = 0.0f;
                    jogador->set_abrirPorta(false);
                }
            }
            _mostrarTexto = false;
        }
    }
}

// metodo polimorfico que verifica as colisoes da porta
void Porta::colisao(Entidade *entidade, sf::Vector2f distancia)
{
    try {
        if (entidade && entidade->get_id() == Identificador::jogador) {
            Jogador* _jogador = dynamic_cast<Jogador*>(entidade);
            if (_jogador) {
                std::cout << "colidiu com porta" << std::endl;
                colisaoJogador(_jogador);
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Erro na colisão: " << e.what() << std::endl;
    }
}

// funcao responsavel por desenhar tudo da classe
void Porta::desenhar()
{
    if (_mostrarTexto) {
        gGrafico->desenhar (caixaTexto);
        gGrafico->desenhar (_textoPorta.get_texto());
    }

    gGrafico->desenhar(_corpo);
}

// funcao que atualiza tudo, metodos e variaveis da classe porta
void Porta::atualizar()
{
    atualizarAnimacao();
    desenhar ();
    _mostrarTexto = false;
}
