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

// funcao que retorna o tamanho da lista
int ListaEntidade::get_tamanhoLista()
{
    return _entidades.size();
}

// funcao que adiciona uma entidade na lista
void ListaEntidade::adicionarEntidade(Entidade *novaEntidade)
{
    if (novaEntidade == nullptr) {
        throw std::invalid_argument ("Nao foi possivel adicionar a entidade no vector");
    }
    _entidades.push_back(novaEntidade);
}

// funcao que limpa as entidades mortas do jogo
void ListaEntidade::limparEntidadesMortas()
{
    for (int i=0 ; i < _entidades.size() ; i++){                                        // percorre a lista
    if (_entidades[i]->podeRemover()){                                                  // se estiver marcada para remover
        removerEntidade(_entidades[i]->get_id());                                       // chama o metodo de remover passando o id da entidade
    }
}
}

// funcao que remove qualquer entidade da lista de acordo com seu id
void ListaEntidade::removerEntidade(Identificador id)
{
    try {
        for (int i=0;i<_entidades.size();i++) {                                             // percorre a lista
            if (id == _entidades[i]->get_id()) {                                            // acha atraves do id a entidade a ser deletada
                delete _entidades[i];                           
                _entidades.erase(_entidades.begin() + i);                                   // desaloca e limpa do vetor
            } 
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
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
    try {
        for (auto& entidade : _entidades) {                                         // percorre toda a lista
            if (entidade) {                                                         // onde tiver uma entidade
                delete entidade;                                                    // delete e aloca null na posicao
                entidade = nullptr;
            }
        }
        _entidades.clear();                                                         // limpa o vector
        _jogador = nullptr;                                                         // jogador recebe null
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        throw;
    }
}

// funcao que executa as listas 
void ListaEntidade::executar()
{
   try {
        // Primeiro atualiza as entidades
        for (auto& entidade : _entidades) {
            if (entidade) {
                entidade->atualizar();
            }
        }

        // Desenha todas as entidades que não foram marcadas para remoção
        for (auto& entidade : _entidades) {
            if (entidade) {
                entidade->desenhar();
            }
        }      

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
}
