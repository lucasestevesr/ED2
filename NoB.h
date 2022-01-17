#ifndef ED2_NOB_H
#define ED2_NOB_H
#include <iostream>
#include <string>

using namespace std;

class NoB {
private:
    string *chaves; // array de chaves no nó
    int grau;       // grau mínimo
    int n;          // número de chaves atual
    bool folha;     // verifica se o nó é folha ou não
    NoB **filhos;   // ponteiro para um array de filhos
    int localizacao; // localização dentro do arq binário

public:
    string *getChaves();

    void setChaves(string *chaves);

    int getGrau();

    void setGrau(int grau);

    int getN();

    void setN(int n);

    bool isFolha();

    void setFolha(bool folha);

    NoB **getFilhos();

    void setFilhos(NoB **filhos);

    int getLocalizacao();

    void setLocalizacao(int localizacao);

    NoB(int grau, bool folha);   // Constructor

    ~NoB();

    void insereNoComEspaco(string k);

    void particionaNoFilho(int i, NoB *y);

    void percorreNos();

    NoB *buscaNo(string k);
};

#endif