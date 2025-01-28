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

void ListaEntidade::adicionarEntidade(Entidade *novaEntidade)
{
    if (novaEntidade == nullptr) {
        throw std::invalid_argument ("Nao foi possivel adicionar a entidade no vector");
    }
    _entidades.push_back(novaEntidade);
}

// coloca no vector de remocao de entidades, a entidade a ser removida
/*void ListaEntidade::marcarRemocao(Entidade *entidade)
{
    if (entidade) {
        _entidadesRemocao.push_back(entidade);
    }
}*/

// limpa as entidades mortas do jogo
/*void ListaEntidade::limparEntidadesMortas()
{
       std::vector<Entidade*> novasEntidades;
    
    // Mantém apenas as entidades que não estão marcadas para remoção
    for (auto& entidade : _entidades) {
        if (entidade != nullptr) {
            bool deveRemover = false;
            
            // Verifica se está na lista de remoção
            for (auto& remover : _entidadesRemocao) {
                if (entidade == remover) {
                    deveRemover = true;
                    break;
                }
            }
            
            if (!deveRemover) {
                novasEntidades.push_back(entidade);
            } else {
                std::cout << "Removendo entidade..." << std::endl;
                delete entidade;
            }
        }
    }
    
    // Limpa a lista de remoção
    _entidadesRemocao.clear();
    
    // Atualiza a lista principal
    _entidades = std::move(novasEntidades);
}*/

void ListaEntidade::limparEntidadesMortas()
{
    for (int i=0 ; i < _entidades.size() ; i++){
    if (_entidades[i]->podeRemover()){
        removerEntidade(_entidades[i]->get_id());
    }
}
}

// funcao que remove qualquer entidade da lista de acordo com seu id
void ListaEntidade::removerEntidade(Identificador id)
{
    try {
        for (int i=0;i<_entidades.size();i++) {
            if (id == _entidades[i]->get_id()) {
                delete _entidades[i];
                _entidades.erase(_entidades.begin() + i);
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
    try {
        for (auto& entidade : _entidades) {
            if (entidade) {
                delete entidade;
                entidade = nullptr;
            }
        }
        _entidades.clear();
        _jogador = nullptr;                     // 
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        throw;
    }
}

void ListaEntidade::executar()
{
   try {
        // Primeiro atualiza e desenha todas as entidades
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

        // Remove as entidades no final da execução
        //limparEntidadesMortas();
        
    } catch (const std::exception& e) {
        std::cerr << "Erro na execução da lista de entidades: " << e.what() << std::endl;
    }
}
