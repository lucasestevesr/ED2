#ifndef ED2_NOB_H
#define ED2_NOB_H
#include <iostream>

class NoB {

    private:
        int *chaves;    // cada nó possui um array de com até m-1 chaves de capacidade
        NoB **filhos;   // cada filho pode ter até um total de max outros filhos
        int totalNos;   // total de chaves que o nó possui
        bool ehFolha;   // verifica se o nó eh folha
        int grau; 
    public:
        NoB(int grau, bool ehFolha);
        ~NoB();
        NoB* buscaNo(int indice);
        void insereNo(int info);
        bool getEhFolha();
        int getTotalNos();
        void incrementaTotalNos();
        int buscaChaveNo(int indice);
};

#endif