#include "listaentidade.h"
#include "inimigo.h"

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

int ListaEntidade::get_tamanhoLista()
{
    return _entidades.size();
}

// funcao que cria um jogador e adiciona ele no vector 
/*void ListaEntidade::adicionarJogador(const sf::Vector2f posicao, const sf::Vector2f tamanho, sf::Vector2f velocidade, Identificador id)
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
}*/

// funcao que verifica quais entidades foram mortas ao longo do programa
/*void ListaEntidade::verificarEntidadesMortas()
{
    for (int i=0 ; i< _entidades.size() ; i ++) {
        Inimigo* inimigo = dynamic_cast < Inimigo* > (_entidades[i]);
        if (inimigo && inimigo->podeRemover ()) {
            removerEntidade (i);
        }
    }
\}*/

void ListaEntidade::adicionarEntidade(Entidade *novaEntidade)
{
    if (novaEntidade == nullptr) {
        throw std::invalid_argument ("Nao foi possivel adicionar a entidade no vector");
    }
    _entidades.push_back(novaEntidade);
}

// funcao que remove qualquer entidade da lista de acordo com seu id
void ListaEntidade::removerEntidade(Identificador id)
{
        try {
        for (auto it = _entidades.begin(); it != _entidades.end();) {
            if ((*it)->get_id() == id) {
                delete *it;
                it = _entidades.erase(it);
            } else {
                ++it;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao remover entidade: " << e.what() << std::endl;
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
        if (entidade && entidade != _jogador) {  // Não deletar o jogador aqui
            delete entidade;
        }
    }
    _entidades.clear();
}

void ListaEntidade::executar()
{
  {
    try {
        // Primeiro atualiza todas as entidades
        for (auto it = _entidades.begin(); it != _entidades.end();) {
            (*it)->atualizar();
            
            // Verifica se é um inimigo e se pode ser removido
            Inimigo* inimigo = dynamic_cast<Inimigo*>(*it);
            if (inimigo && inimigo->podeRemover()) {
                delete *it;  // Libera a memória
                it = _entidades.erase(it);  // Remove da lista e atualiza o iterador
            } else {
                ++it;  // Avança o iterador
            }
        }

        // Depois desenha as entidades restantes
        for (auto entidade : _entidades) {
            entidade->desenhar();
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro na execução da lista de entidades: " << e.what() << std::endl;
    }
}
}
