#ifndef FUNDO_H
#define FUNDO_H
#include <vector>
#include "camada.h"
#include "identificadores.h"

class Fundo {
private:
    GerenciadorGrafico* gGrafico;
    std::vector < Camada* > _camadas;
    Identificador _id;

public:
    // construtor
    Fundo (Identificador id);
    // destrutor
    ~Fundo();
    // metodos da classe
    void adicionarCamada (const char* caminhoTextura, sf::Vector2f tamanhoTextura, sf::Vector2f origem);
    void desenhar ();
    void executar ();
};



#endif