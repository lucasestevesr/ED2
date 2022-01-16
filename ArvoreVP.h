#ifndef ED2_ARVOREVP_H
#define ED2_ARVOREVP_H

#include "NoVP.h"

class ArvoreVP {
    private:
        NoVP *raiz;
        NoVP *rotacionarEsquerda(NoVP *no);
        NoVP *rotacionarDireita(NoVP *no);
        NoVP *inserirAux(NoVP *raiz, NoVP *novo_no, bool *resposta, int *comparacoes);
        NoVP *buscarAux(NoVP *no, string id, int *comparacoes);
        void destrutorAux(NoVP *no);
        void trocarCor(NoVP *no);

    public:
        ArvoreVP();
        ~ArvoreVP();
        NoVP *getRaiz();
        void setRaiz(NoVP *raiz);
        bool inserir(string id, int localizacao, int *comparacoes);
        NoVP *buscar(string id, int *comparacoes);
};

#endif //ED2_ARVOREVP_H
