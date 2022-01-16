#ifndef ED2_NOB_H
#define ED2_NOB_H
#include <iostream>

class NoB {
    
    public:
        
        int *chaves;    // array de chaves no nó
        int grau;       // grau mínimo
        int n;          // número de chaves atual
        bool folha;     // verifica se o nó é folha ou não
        NoB **filhos;   // ponteiro para um array de filhos

        
        NoB(int grau, bool folha);   // Constructor
        ~NoB();
        void insereNoComEspaco(int k);
        void particionaNoFilho(int i, NoB *y);
        void percorreNos();
        NoB *buscaNo(int k);
        friend class ArvoreB; // permite acessar propriedades privadas desta classe a partir da classe ArvoreB
};

#endif