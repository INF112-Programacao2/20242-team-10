#include "experiencia.h"
#include <iostream>
#include <cmath>

// construtor default
Experiencia::Experiencia() :
    _nivel (1) , _experiencia (20.0f) , _forca (10.0f), _defesa (20.0f)  {}


// construtor da classe
Experiencia::Experiencia(float forca, float defesa, float vida) :
    _nivel(1) , _experiencia (0.0f) ,  _forca(forca) , _defesa(defesa)  {}

// destrutor da classe
Experiencia::~Experiencia()
{
}

// funcao que altera o nivel do personagem
void Experiencia::set_nivel(unsigned int nivel)
{
    if(nivel < 1) {
        throw std::invalid_argument ("Nao foi possivel atualizar o nivel, nivel menor do que 1");
    }

    this->_nivel = nivel;
    this->_forca = _forca + (_nivel*5.0f);
    this->_defesa = _defesa + (_nivel*10.0f);

}

// funcao que retorna o nivel dos personagens 
unsigned int Experiencia::get_nivel()
{
    return _nivel;
}

// funcao que adiciona experiencia e atualiza caso o personagem tenha experiencia necessaria para atualizar de nivel
void Experiencia::adicionarExperiencia(float experiencia)
{
    if (_experiencia < 0) return;
    
    this->_experiencia += experiencia;                      // adiciona a experiencia

    if (_experiencia >= PROXIMO_NIVEL){                     // se tiver xp necessaria para atualizar o nivel
        float restoXP = _experiencia - PROXIMO_NIVEL;       // pega a xp que sobrou, ou nao
        set_nivel (_nivel + 1);                             // atualiza o nivel
        this->_experiencia = restoXP;                       // atualiza a xp com o que restou apos aumentar o nivel
    }
}

// funcao que retorna a experiencia do personagem
float Experiencia::get_experiencia()
{
    return _experiencia;
}

// funcao que retorna a forca do personagem
float Experiencia::get_forca()
{
    return _forca;
}

// funcao que retorna a defesa do personagem
float Experiencia::get_defesa()
{
    return _defesa;
}

// funcao que atualiza a forca do personagem, ja alterando o atributo
void Experiencia::set_forca(float forca)
{
    _forca = forca;                                                          
    _forca = _forca + (_nivel*5.0f);                                    
}

// funcao que atualiza a defesa do personagem, ja alterando o atributo
void Experiencia::set_defesa(float defesa)
{
    _defesa = defesa;
    _defesa = _defesa + (_nivel*10.0f);
}


