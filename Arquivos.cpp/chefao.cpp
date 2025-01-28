#include "chefao.h"
#include "arma.h"

// funcao que inicializa a animacao do chefao
void Chefao::inicializarAnimacao()
{
    sf::Vector2f escala (4.0f,4.0f);                                                            // aumento da escala pois o sprite e pequeno
    sf::Vector2f origem (_tamanho.x * escala.x / 10.5f , _tamanho.y * escala.y / 9.5);          // ajute da origem conforme a escala (formula, origem = tamanho_original * escala / divisor_de_ajuste )

    // inicializa as animacoes do chefao
    _animacao.adicionarAnimacao("ChefaoParado.png", "PARADO", 8, 0.12f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoCorrendo.png", "ANDA", 8, 0.15f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoMorrendo.png", "MORRE", 7, 0.20f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoAtacando.png", "ATACAR", 8, 0.15f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoAtacandoRaiva.png", "ATACAR_COM_RAIVA", 8, 0.20f, escala, origem, true);
    _animacao.adicionarAnimacao("ChefaoTomandoDano.png", "TOMARDANO", 3, 0.15f, escala, origem, true);
}

// inicializa o texto e o tamanho da borda do nivel do chefao
void Chefao::inicializarNivel()
{
    _textoNivel.set_informacao("Lv." + std::to_string (_experiencia.get_nivel()));
    _textoNivel.set_tamanhoBorda(2);

}

// funcao que atualiza as animacoes de acordo com os estados, se esta morrendo, correndo, atacando...
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
            _corpo.setFillColor (sf::Color::Transparent);                       // desaparece com o corpo
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

// construtor
Chefao::Chefao(sf::Vector2f posicao, Jogador *jogador) :
    Inimigo (posicao, sf::Vector2f(TAMANHO_CHEFAO_X, TAMANHO_CHEFAO_Y),jogador, Identificador::chefao,TEMPO_MORTE_CHEFAO,TEMPO_ATAQUE_CHEFAO,XP_CHEFAO)
{
    // inicializa o nivel do chefao
    _experiencia.set_nivel (5);

    inicializarAnimacao ();
    inicializarNivel ();

    // atualioza a forca e a defesa do chefao
    _experiencia.set_forca (FORCA_CHEFAO);
    _experiencia.set_defesa (DEFESA_CHEFAO);

    // cria a rma do chefao, atualizando o dano e o tamanho
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

// destrutor 
Chefao::~Chefao()
{
    if (_arma) {
        _arma->remover();
    }
}

// funcao responsavel pela mecanica de tomar dano do chefao
void Chefao::tomarDano(float dano)
{
    if (inativo) return;                                    // verifica se ele nao morreu

    if (!levandoDano && !_protegido) {                      // se puder tomar dano

        // atualiza os estados
        _protegido = true;
        levandoDano = true;
        andando = false;
        atacando = false;
        _vida -= dano; 

        // se o chefao morreu
        if (_vida <= 0.0f) {
            // atualiza os estados de morte
            morrendo = true;
            atacando = false;
            _vida = 0.0f;
        }
        // se a vida do chefao chegou na metada
        else if (_vida <= 50.0f){
            // ativa o modo raiva
            modoRaiva = true;                                                   
            _arma->set_dano (_experiencia.get_forca() + 20.0f);                // aumenta a forca em 20.0f
            _corpo.setFillColor(sf::Color(138, 43, 226));                      // muda a cor para um roxo vibrante escuro
        }
        
        _tempoDano = 0.0f;
        _tempoProtecaoAtaque = 0.0f;
    }
}
