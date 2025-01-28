#ifndef GERENCIADORMUSICA_H
#define GERENCIADORMUSICA_H

#include <SFML/Audio.hpp>
#include "identificadores.h"
#include <map>

class GerenciadorMusica {
private:
    std::map <Identificador, sf::Music*> mapMusicas;
    Identificador _musicaAtual;
    float _volumeMusica;

    void adicionarMusica (Identificador idMusica , const char* caminhoMusica, bool loop);
    //void adicionaMusica (Identificador idMusica , const char* caminhoMusica);

    // singleton
    static GerenciadorMusica* gMusica;
    // construtor privado para evitar de criar mais de um gerenciador musical
    GerenciadorMusica();

public:
    // destrutor
    ~GerenciadorMusica ();

    //getter e setters
    static GerenciadorMusica* get_gerenciadorMusical ();
    void set_volume (float volume);
    float get_volume ();

    // metodos da classe
    void limparMusicas ();
    void parar ();
    void tocar (Identificador idMusica);




};

#endif