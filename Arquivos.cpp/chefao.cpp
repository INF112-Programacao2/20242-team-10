#include "chefao.h"
#include "arma.h"

void Chefao::inicializarAnimacao()
{
    sf::Vector2f escala (4.0f,4.0f);                                                            // aumento da escala pois o sprite e pequeno
    sf::Vector2f origem (_tamanho.x * escala.x / 10.5f , _tamanho.y * escala.y / 9.5);          // ajute da origem conforme a escala (formula, origem = tamanho_original * escala / divisor_de_ajuste )

    _animacao.adicionarAnimacao("ChefaoParado.png", "PARADO", 8, 0.12f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoCorrendo.png", "ANDA", 8, 0.15f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoMorrendo.png", "MORRE", 7, 0.20f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoAtacando.png", "ATACAR", 8, 0.15f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoAtacandoRaiva.png", "ATACAR_COM_RAIVA", 8, 0.20f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoTomandoDano.png", "TOMARDANO", 3, 0.15f, escala, origem, true);
}

void Chefao::inicializarNivel()
{
    _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));
    _textoNivel.set_tamanhoBorda(2);

}

void Chefao::atualizarAnimacao()
{
    if (morrendo) {
        if (!andaEsquerda)
        _animacao.atualizar(DIREITA,"MORRE");
         else
        _animacao.atualizar(ESQUERDA, "MORRE");

        _tempoMorte += gGrafico->get_tempo();
        if (_tempoMorte >= _duracaoAnimacaoMorte && !inativo ){
            _jogador->adicionarXP(XP);
            inativo = true;          
            _corpo.setFillColor (sf::Color::Transparent);                   // desaparece com o corpo
        }
        return;
    }
    else if (levandoDano) {
        if (!andaEsquerda)
        _animacao.atualizar (DIREITA,"TOMARDANO");
        else 
        _animacao.atualizar (ESQUERDA,"TOMARDANO"); 

        _tempoDano += gGrafico->get_tempo();
        if (_tempoDano >= TEMPO_RECUPERACAO_DANO) {
            levandoDano = false;
            _tempoDano = 0.0f;
        }
    }
    else if (atacando){
        _tempoAtaque += gGrafico->get_tempo();
        if (_tempoAtaque >= TEMPO_ATAQUE_CHEFAO){
            atacando = false;
            _tempoAtaque = 0.0f;
            return;
        }
        if (modoRaiva){
            if (!andaEsquerda)
            _animacao.atualizar (DIREITA,"ATACAR_COM_RAIVA");
            else 
            _animacao.atualizar (ESQUERDA,"ATACAR_COM_RAIVA"); 
        }
        else if (!andaEsquerda)
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

Chefao::Chefao(sf::Vector2f posicao, Jogador *jogador) :
    Inimigo (posicao, sf::Vector2f(TAMANHO_CHEFAO_X, TAMANHO_CHEFAO_Y),
     jogador, Identificador::chefao,TEMPO_MORTE_CHEFAO,TEMPO_ATAQUE_CHEFAO,XP_CHEFAO)
{
    _experiencia.set_nivel (5);
    inicializarAnimacao ();
    inicializarNivel ();

    _experiencia.set_forca (FORCA_CHEFAO);
    _experiencia.set_defesa (DEFESA_CHEFAO);

    Arma* cajadoChefao = new Arma (Identificador::cajado_chefao);
    if (cajadoChefao) {
        cajadoChefao->set_tamanho (sf::Vector2f(TAMANHO_CAJADO_CHEFAO,TAMANHO_CAJADO_CHEFAO));
        set_arma (cajadoChefao);
        if (_arma) {
            _arma->set_personagem(this);
            _arma->set_dano (_experiencia.get_forca());
        }
    }
}

Chefao::~Chefao()
{
    if (_arma) {
        _arma->remover();
    }
}

void Chefao::tomarDano(float dano)
{
    if (inativo) return;

    if (!levandoDano && !_protegido) {
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
        else if (_vida <= 50.0f){
            modoRaiva = true;
            _arma->set_dano (_experiencia.get_forca() + 20.0f);
            _corpo.setFillColor(sf::Color(138, 43, 226));                      // roxo vibrante escuro
        }
        //_corpo.setFillColor(sf::Color (110,110,110,110));
        _tempoDano = 0.0f;
        _tempoProtecaoAtaque = 0.0f;
    }
}
