#include "gerenciadormusica.h"
#include <iostream>
#include <utility>

// inicializacao do gerenciador musical
GerenciadorMusica* GerenciadorMusica::gMusica = nullptr;

// construtor da classe
GerenciadorMusica::GerenciadorMusica() :
    mapMusicas () , _volumeMusica (10.0f)
{
    adicionarMusica (Identificador::musica_background , "MusicaBackground.ogg", true);                  // adiciona a musica de fundo
    adicionarMusica (Identificador::musica_venceu_jogo , "somVencendo.ogg", true);                      // adiciona a musica de vencedor do jogo

    adicionarMusica (Identificador::som_goblin , "somTomandoDanoGoblin.ogg", false);                         // adiciona som do goblin tomando dano
    adicionarMusica (Identificador::som_esqueleto , "somEsqueletoTomandoDano.ogg", false);                         // adiciona som do esqueleto tomando dano
    adicionarMusica (Identificador::som_alma , "somAlmaTomandoDano.ogg",false);                              // adiciona som da alma tomando dano
    adicionarMusica (Identificador::som_chefao , "somChefaoTomandoDano.ogg",false);                         // adiciona som do chefao tomando dano
    adicionarMusica (Identificador::som_morcego , "somMorcegoTomandoDano.ogg",false);                         // adiciona som do morcego tomando dano
    adicionarMusica (Identificador::som_jogador , "somJogadorTomandoDano.ogg",false);                         // adiciona som do jogador tomando dano
    adicionarMusica (Identificador::som_jogador_espada , "somJogadorEspada.ogg",false);                         // adiciona som da espada do jogador


    _musicaAtual = Identificador::nada;                                                              // inicializa a musica atual com identificador vazio
}

// destrutor da classe
GerenciadorMusica::~GerenciadorMusica() 
{
        limparMusicas ();                                     // limpa o map das musicas
}

// funcao que retorna o gerenciador musical
GerenciadorMusica *GerenciadorMusica::get_gerenciadorMusical()
{
   if (gMusica == nullptr) {                            // se o gerenciador de musica ainda nao foi criado
    gMusica = new GerenciadorMusica ();                 // cria o gerenciador
   }

   return gMusica;                                      // retorna o gerenciador musical
}

// funcao que atualiza o volume da musica
void GerenciadorMusica::set_volume(float volume)
{
    _volumeMusica = volume;
}

// funcao que retorna o volume da musica
float GerenciadorMusica::get_volume()
{
    return _volumeMusica;
}

// funcao que para a musica atual
void GerenciadorMusica::parar()
{
    if (_musicaAtual != Identificador::nada && mapMusicas[_musicaAtual] != nullptr) {
        mapMusicas[_musicaAtual]->stop();
    }

    mapMusicas [Identificador::musica_background]->stop();                      // para a musica de fundo tambem
}

// funcao que toca as musicas 
void GerenciadorMusica::tocar(Identificador idMusica)
{
    auto iterator = mapMusicas.find (idMusica);                                 // procura a musica no map pelo id 

    if (iterator == mapMusicas.end()) {                                         // tratamento caso nao ache a musica
        throw std::runtime_error ("A musica ainda nao foi adicionada");
    }

    _musicaAtual = idMusica;
    mapMusicas[idMusica]->setVolume (_volumeMusica);                            // seta o volume da musica
    mapMusicas [idMusica]->play();                                              // toca a musica
}

// funcao que carrega a musica e adiciona ela no map de acordo com seu id
void GerenciadorMusica::adicionarMusica(Identificador idMusica, const char *caminhoMusica, bool loop)
{
    sf::Music* musica = new sf::Music ();
    if (!musica->openFromFile(caminhoMusica)) {                                             // verifica se foi possivel abrir a musica
        throw std::runtime_error ("Nao foi possivel carregar a musica");
    }
    musica->setLoop (loop);                                                                 // seta a musica para tocar em loop
    mapMusicas.insert(std::pair <Identificador,sf::Music*> (idMusica,musica));              // adiciona no map de musicas com seu id

}

// funcao que limpa as musicas do programa
void GerenciadorMusica::limparMusicas() {
    for (auto& [id, musica] : mapMusicas) {
        if (musica) {
            musica->stop();
            delete musica;
        }
    }
    mapMusicas.clear();
    _musicaAtual = Identificador::nada;
}


