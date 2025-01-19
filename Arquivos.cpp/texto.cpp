#include "texto.h"

// funcao que inicializa os textos do jogo
void Texto::inicializar()
{
    _texto.setString (_informacao);
    _texto.setCharacterSize(_tamanhoFonte);
    _texto.setFont (_fonte);
    _texto.setOutlineThickness (5.0f);
    _texto.setOutlineColor (_corBorda);
    _texto.setFillColor (_corTexto);

    _tamanho = sf::Vector2f (_texto.getGlobalBounds().width , _texto.getGlobalBounds().height);

}

// construtor
Texto::Texto(sf::Font fonte, std::string informacao, unsigned int tamanhoFonte) :
    _fonte (fonte) , _texto () , _informacao (informacao) , _tamanhoFonte (tamanhoFonte) , _corBorda (sf::Color::Black) , 
    _corTexto (sf::Color::White)
{
    inicializar ();
}

// destrutor da classe
Texto::~Texto()
{
}

// funcao que retorna o texto
sf::Text Texto::get_texto()
{
    return _texto;
}

// funcao que atualiza a posicao do texto
void Texto::set_posicao(sf::Vector2f posicao)
{
    _posicao = posicao;
    _texto.setPosition (_posicao);
}

// funcao que retorna a posicao do texto
sf::Vector2f Texto::get_posicao()
{
    return _posicao;
}

// funcao que retorna o tamanho do texto
sf::Vector2f Texto::get_tamanho()
{
    return _tamanho;
}

// funcao que retorna o conteudo, a informacao do texto
std::string Texto::get_informacao()
{
    return _texto.getString();
}

// funcao que atualiza o tamanho da borda do texto
void Texto::set_tamanhoBorda(float tamanhoBorda)
{
    _texto.setOutlineThickness (tamanhoBorda);
    _tamanho = sf::Vector2f (_texto.getGlobalBounds().width , _texto.getGlobalBounds().height);
}

// funcao que atualiza a cor do texto
void Texto::set_corTexto(sf::Color corTexto)
{
    _corTexto = corTexto;
    _texto.setFillColor (_corTexto);
}

// funcao que atualiza o tamanho da fonte do texto
void Texto::set_tamanhoFonte(unsigned int tamanhoFonte)
{
    _texto.setCharacterSize (tamanhoFonte);
    _tamanho = sf::Vector2f (_texto.getGlobalBounds().width , _texto.getGlobalBounds().height);
}

// funcao que atualiza a informacao, o conteudo do texto
void Texto::set_informacao(std::string informacao)
{
    _texto.setString (informacao);
    _tamanho = sf::Vector2f (_texto.getGlobalBounds().width , _texto.getGlobalBounds().height);
}

// funcao que atualiza o espacamento usado no texto
void Texto::set_espacamento(float tamanhoEspaco)
{
    _texto.setLetterSpacing (tamanhoEspaco);
    _tamanho = sf::Vector2f (_texto.getGlobalBounds().width , _texto.getGlobalBounds().height);
}
