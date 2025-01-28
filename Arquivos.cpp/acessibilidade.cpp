#include "acessibilidade.h"

// inicializacao do ponteiro de acessibilidade
Acessibilidade* Acessibilidade::gAcessibilidade = nullptr;

// funcao que adiciona a mensagem no map de acordo com id
void Acessibilidade::adicionarMensagem(Identificador idTexto, std::string mensagem)
{
        _mapMensagens[idTexto] = mensagem;
}

// funcao que inicializa fonte, tamanho, cor e todas as outras coisas relacionadas ao texto da acessibilidade
void Acessibilidade::inicializar()
{

    _texto.setFont(_fonte);
    _texto.setCharacterSize(30);
    _texto.setFillColor(sf::Color::White);
    _texto.setOutlineColor(sf::Color::Black);
    _texto.setOutlineThickness(2.0f);
    
    _visivel = false;
    _tempoExibicao = 0.0f;
}

// construtor
Acessibilidade::Acessibilidade() :
    _visivel (false),
    _tempoExibicao (0.0f),
    _fonte(gGrafico->carregarFonte("FonteNivel.ttf")),
    gGrafico(gGrafico->get_grafico())

{
    inicializar ();

    // inicializa as mensagens que serao utilizadas como acessibilidade
    adicionarMensagem(Identificador::texto_esqueleto, "Som de ossos quebrando");
    adicionarMensagem(Identificador::texto_goblin, "Som de goblin ferido");
    adicionarMensagem(Identificador::texto_morcego, "Som de morcego guinchando");
    adicionarMensagem(Identificador::texto_alma, "Som da alma ferida");
    adicionarMensagem(Identificador::texto_chefao, "Som do chefao tomando impacto");
    adicionarMensagem(Identificador::texto_jogador_dano, "Som jogador tomando dano");

    //adicionarMensagem (Identificador::texto_vitoria, "VOCE CONSEGUIU, RECUPEROU A COROA!");
}

// destrutor
Acessibilidade::~Acessibilidade()
{
    if (gAcessibilidade == this) {
        gAcessibilidade = nullptr;
    }
}

// funcao que retorna se o texto esta visivel ou nao 
bool Acessibilidade::estaVisivel()
{
    return _visivel;
}

// funcao que retorna o ponteiro da acessibilidade 
Acessibilidade *Acessibilidade::get_acessibilidade()
{
    if (gAcessibilidade == nullptr) {
        gAcessibilidade = new Acessibilidade();
    }
    return gAcessibilidade;
}

// funcao que a partir do id da mensagem, procura e adiciona o conteudo
void Acessibilidade::mostraMensagem(Identificador idMensagem, sf::Vector2f posicao)
{
    auto iterator = _mapMensagens.find(idMensagem);               // procura pelo id da mensagem

    if (iterator != _mapMensagens.end()) {                        // se achar o id 
        _texto.setString(iterator->second);                       // seta o conteudo
        _texto.setPosition(posicao);                              // seta a posicao
        _visivel = true;                                          // deixa visivel
        _tempoExibicao = 8.0f;                                   //  duração da mensagem em segundos
    }
}

// funcao que atualiza o tempo da acessibilidade
void Acessibilidade::atualizar(float tempo)
{
        if (_visivel) {                             // se ela for visivel
        _tempoExibicao -= tempo;                    // desconta o tepo passado no tempo de exibicao
        if (_tempoExibicao <= 0) {                  // se acabou o tempo de exibicao
            _visivel = false;                       // nao exibe mais
        }
    }
}

// funcao que desenha o texto na tela
void Acessibilidade::desenhar()
{
        if (_visivel) {
        gGrafico->desenhar(_texto);
    }
}
