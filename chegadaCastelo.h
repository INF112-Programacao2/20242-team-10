#ifndef CHEGADACASTELO_H
#define CHEGADACASTELO_H

#include "fase.h"
#include "personagem.h"

class ChegadaCastelo : public Fase {
public:
    // construtor
    ChegadaCastelo (std::vector < std::vector < char >> mapa);
    // destrutor
    ~ChegadaCastelo ();
    // metodods virtuais
    void criarFundo ();
    void criarMapa ();
};

#endif