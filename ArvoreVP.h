#ifndef ED2_ARVOREVP_H
#define ED2_ARVOREVP_H

#include "NoVP.h"

class ArvoreVP {
    private:
        NoVP *raiz;
        NoVP *rotacionarEsquerda(NoVP *no);
        NoVP *rotacionarDireita(NoVP *no);
        NoVP *inserirAux(NoVP *raiz, NoVP *novo_no, bool *resposta);
        NoVP *buscarAux(NoVP *no, string id);
        void destrutorAux(NoVP *no);
        void trocarCor(NoVP *no);

    public:
        ArvoreVP();
        ~ArvoreVP();
        NoVP *getRaiz();
        void setRaiz(NoVP *raiz);
        bool inserir(string id, int localizacao);
        NoVP *buscar(string id);
};

#endif //ED2_ARVOREVP_H
