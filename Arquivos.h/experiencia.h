#ifndef EXPERIENCIA_H
#define EXPERIENCIA_H


#define PROXIMO_NIVEL 50.0f

class Experiencia {
private:
    unsigned int _nivel;
    float _experiencia;
    //float _proximoNivel;
    float _forca;
    float _defesa;
    float _vida;

public:
    // construtor default
    Experiencia();
    // construtor "personalizado"
    Experiencia (float forca, float defesa, float vida);
    // destrutor
    ~Experiencia();
    // getters e setters
    void set_nivel (unsigned int nivel);
    unsigned int get_nivel ();
    void adicionarExperiencia (float experiencia);
    float get_experiencia ();
    float get_forca();
    float get_defesa();
    float get_vida();
    void set_forca(float forca);
    void set_defesa(float defesa);
    void set_vida(float vida);

};








#endif