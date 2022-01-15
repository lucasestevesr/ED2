#include "ArvoreVP.h"
#include <iostream>

using namespace std;

// Construtor
ArvoreVP::ArvoreVP() {
    this->raiz = nullptr;
}

// Destrutor
ArvoreVP::~ArvoreVP() {
    ArvoreVP::destrutorAux(this->raiz);
}

// Destrutor Auxliar
void ArvoreVP::destrutorAux(NoVP *no) {
    if(no != nullptr) {
        ArvoreVP::destrutorAux(no->getEsquerdo());
        ArvoreVP::destrutorAux(no->getDireito());
        delete no;
    }
}

// Getters e Setters
NoVP *ArvoreVP::getRaiz() {
    return this->raiz;
}

void ArvoreVP::setRaiz(NoVP *raiz) {
    this->raiz = raiz;
}
// Fim Getters e Setters

// Rotacionar para esquerda
NoVP* ArvoreVP::rotacionarEsquerda(NoVP *no) {
    NoVP *no_dir = no->getDireito();
    no->setDireito(no_dir->getEsquerdo());
    no_dir->setEsquerdo(no);
    no_dir->setCor(no->isVermelho());
    no->setVermelho();

    return no_dir;
}

// Rotacionar para direita
NoVP* ArvoreVP::rotacionarDireita(NoVP *no) {
    NoVP *no_esq = no->getEsquerdo();
    no->setEsquerdo(no_esq->getDireito());
    no_esq->setDireito(no);
    no_esq->setCor(no->isVermelho());
    no->setVermelho();

    return no_esq;
}

// Trocar Cor
void ArvoreVP::trocarCor(NoVP *no) {
    no->trocarCor();
    if(no->getEsquerdo() != nullptr) {
        no->getEsquerdo()->trocarCor();
    }
    if(no->getDireito() != nullptr) {
        no->getDireito()->trocarCor();
    }
}

// Inserir novo no
bool ArvoreVP::inserir(string id, int localizacao) {
    bool resposta = false;

    NoVP *novo_no = new NoVP(id, localizacao);

    this->raiz = ArvoreVP::inserirAux(this->raiz, novo_no, &resposta);

    if(resposta) {
        this->raiz->setCor(false);
    }else {
        delete novo_no;
    }

    return resposta;
}

// Inserir Aux
NoVP* ArvoreVP::inserirAux(NoVP *raiz, NoVP *novo_no, bool *resposta) {
    if(raiz == nullptr) {
        (*resposta) = true;
        return novo_no;
    }
    if(novo_no->getId() == raiz->getId()) {
        (*resposta) = false;
    }else {
        if(novo_no->getId() < raiz->getId()) {
            raiz->setEsquerdo(ArvoreVP::inserirAux(raiz->getEsquerdo(), novo_no, resposta));
            raiz->getEsquerdo()->setPai(raiz);
        }else {
            raiz->setDireito(ArvoreVP::inserirAux(raiz->getDireito(), novo_no, resposta));
            raiz->getDireito()->setPai(raiz);
        }
    }

    if(raiz->getDireito()->isVermelho() && raiz->getEsquerdo()->isPreto()) {
        raiz = ArvoreVP::rotacionarEsquerda(raiz);
    }
    if(raiz->getEsquerdo()->isVermelho() && raiz->getEsquerdo()->getEsquerdo()->isVermelho()) {
        raiz = ArvoreVP::rotacionarDireita(raiz);
    }
    if(raiz->getEsquerdo()->isVermelho() && raiz->getDireito()->isVermelho()) {
        ArvoreVP::trocarCor(raiz);
    }

    return raiz;
}

// Buscar
NoVP *ArvoreVP::buscar(string id) {
    if(this->raiz != nullptr) {
        NoVP *no = ArvoreVP::buscarAux(this->raiz, id);
        if(no != nullptr) {
            return no;
        }else{
            cout << "Erro: Id nao encontrado!" << endl;
            return nullptr;
        }
    }else {
        cout << "Erro: Arvore Vazia!" << endl;
        return nullptr;
    }
}

// Buscar Aux
NoVP *ArvoreVP::buscarAux(NoVP *no, string id) {
    if(no != nullptr) {
        if(id == no->getId()) {
            return no;
        }
        if(id > no->getId()) {
            return ArvoreVP::buscarAux(no->getDireito(), id);
        }

        return ArvoreVP::buscarAux(no->getEsquerdo(), id);
    }else {
        return nullptr;
    }
}