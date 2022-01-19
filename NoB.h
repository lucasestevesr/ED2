#ifndef ED2_NOB_H
#define ED2_NOB_H
#include <iostream>
#include <string>

using namespace std;

// definindo o tipo de cada Nó
struct InfoArvoreB{
    string id;
    int localizacao;
};

class NoB {
    private:
        InfoArvoreB *chaves; // array de chaves no nó
        int grau;             // grau mínimo
        int n;                // número de chaves atual
        bool folha;           // verifica se o nó é folha ou não
        NoB **filhos;         // ponteiro para um array de filhos
        int nfilhos;

    public:
        NoB(int grau, bool folha, int nfilhos);   // Constructor

        ~NoB();

        InfoArvoreB *getChaves();

        void setChaves(InfoArvoreB *chaves);

        int getGrau();

        void setGrau(int grau);

        int getN();

        void setN(int n);

        int getNfilhos();

        void setNfilhos(int nfilhos);

        bool isFolha();

        void setFolha(bool folha);

        NoB **getFilhos();

        void setFilhos(NoB **filhos);

        void insereNoComEspaco(string k, int localizacao, int *comparacoes);

        void particionaNoFilho(int i, NoB *y);

        void percorreNos();

        NoB *buscaNo(string k, int *comparacoes);

        friend class ArvoreB;
};

#endif