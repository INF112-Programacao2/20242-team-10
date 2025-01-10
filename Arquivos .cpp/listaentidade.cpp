#include "listaentidade.h"

// construtor
ListaEntidade::ListaEntidade() :
    _jogador(nullptr) {}

// destrutor
ListaEntidade::~ListaEntidade()
{
    limparEntidades ();
}

// funcao que retorna o jogador
Jogador *ListaEntidade::get_jogador() const
{
    return this->_jogador;
}

// funcao que retorna uma referencia do vector, onde pode se acessar todas as entidades sem modifica-las por conta do const 
const std::vector<Entidade *>& ListaEntidade::get_entidades() const
{
    return _entidades;
}

// funcao que cria um jogador e adiciona ele no vector 
void ListaEntidade::adicionarJogador(const sf::Vector2f posicao, const sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id)
{
    // verifica se o jogador foi criado
    if (_jogador == nullptr)
    _jogador = new Jogador (posicao,tamanho,velocidade,Identificador::jogador);                     // caso nao tenha sido, cria o jogador
    // adiciona na lista
    _entidades.push_back(_jogador);                                                                 
}

// funcao que cria um inimigo e adiciona ele no vector 
void ListaEntidade::adicionarInimigo(const sf::Vector2f posicao, const sf::Vector2f tamanho, sf::Vector2f velocidade, Jogador *jogador, Identificador id)
{
    // verifica se o jogador esta criado
    if (_jogador == nullptr)
    throw std::runtime_error ("Nao foi possivel criar um inimigo, deve-se criar um jogador primeiro");
    // cria o inimigo e o adiciona na lista
    Inimigo* inimigo = new Inimigo (posicao, tamanho, velocidade, jogador, Identificador::inimigo);
    _entidades.push_back (inimigo); 
}

// funcao que cria uma plataforma e adiciona ela no vector 
void ListaEntidade::adicionarPlataforma(sf::Vector2f posicao, sf::Vector2f tamanho, Identificador id, std::string tipo)
{
    // cria a plataforma e adiciona na lista
    Plataforma* plataforma = new Plataforma (posicao, tamanho, tipo, Identificador::plataforma);        
    _entidades.push_back (plataforma);                                                                 
}   

// funcao que remove qualquer entidade da lista de acordo com seu id
void ListaEntidade::removerEntidade(Identificador id)
{
    for (auto identificador = _entidades.begin(); identificador != _entidades.end();){                // percorre a lista
        if ((*identificador)->get_id() == id){                                                        // se achar alguma entidade com o id desejado
            delete *identificador;                                                                    // desaloca a memoria
            identificador = _entidades.erase (identificador);                                         // remove do vector atualizando a variavel
        }
        else                                                                                          // caso nao seja o id procurado
            identificador++;                                                                          // avanca na lista
    }
}

// funcao que utiliza o metodo atualizar, presente em todas as subclasses de entidade, que atualiza todas as entidades do programa em uma so chamada (polimorfismo)
void ListaEntidade::atualizar()
{
        for (auto entidade : _entidades) {
            entidade->atualizar ();
        }
}

// funcao que utiliza o metodo desenhar, presente em todas as subclasses de entidade, que desenha todas as entidades do programa em uma so chamada (polimorfismo)
void ListaEntidade::desenhar()
{
    for (auto entidade : _entidades){
        entidade->desenhar ();
    }
}

// funcao que limpa a lista de entidades
void ListaEntidade::limparEntidades()
{
    for (auto entidade : _entidades) {
        delete entidade;
    }
    _entidades.clear();
    _jogador = nullptr;
}
