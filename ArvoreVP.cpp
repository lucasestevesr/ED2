#include "ArvoreVP.h"
#include <iostream>

using namespace std;

// Construtor
ArvoreVP::ArvoreVP() {
    this->raiz = nullptr;
}

// Destrutor
ArvoreVP::~ArvoreVP() {
    this->raiz = ArvoreVP::destrutorAux(this->raiz);
}

// Destrutor Auxiliar
NoVP * ArvoreVP::destrutorAux(NoVP *no) {
    // Destrutor auxiliar que vai chamando as subarvores
    // da esquerda e da direita recursivamente
    if(no != nullptr) {
        no->setEsquerdo(ArvoreVP::destrutorAux(no->getEsquerdo()));
        no->setDireito(ArvoreVP::destrutorAux(no->getDireito()));
        delete no;
    }
    return nullptr;
}

// Getters e Setters
NoVP *ArvoreVP::getRaiz() {
    return this->raiz;
}

void ArvoreVP::setRaiz(NoVP *raiz) {
    this->raiz = raiz;
}
// Fim Getters e Setters

// Função para rotacionar subarvore para esquerda
NoVP* ArvoreVP::rotacionarEsquerda(NoVP *no) {
    NoVP *no_dir = no->getDireito();
    no->setDireito(no_dir->getEsquerdo());
    no_dir->setEsquerdo(no);
    no_dir->setCor(no->isVermelho());
    no->setVermelho();

    return no_dir;
}

// Função para rotacionar subarvore para direita
NoVP* ArvoreVP::rotacionarDireita(NoVP *no) {
    NoVP *no_esq = no->getEsquerdo();
    no->setEsquerdo(no_esq->getDireito());
    no_esq->setDireito(no);
    no_esq->setCor(no->isVermelho());
    no->setVermelho();

    return no_esq;
}

// Função para trocar cor de um No e dos seus filhos
void ArvoreVP::trocarCor(NoVP *no) {
    no->trocarCor();
    if(no->getEsquerdo() != nullptr) {
        no->getEsquerdo()->trocarCor();
    }
    if(no->getDireito() != nullptr) {
        no->getDireito()->trocarCor();
    }
}

// Função para inserir novo No, retorna se inseriu ou não
bool ArvoreVP::inserir(string id, int localizacao, int *comparacoes) {
    bool resposta = false;

    NoVP *novo_no = new NoVP(id, localizacao);

    this->raiz = ArvoreVP::inserirAux(this->raiz, novo_no, &resposta, comparacoes);

    // Se tiver inserido garante a cor certa da raiz
    // Se não tiver inserido exclui o No
    if(resposta) {
        this->raiz->setCor(false);
    }else {
        delete novo_no;
    }

    return resposta;
}

// Inserir Aux
NoVP* ArvoreVP::inserirAux(NoVP *raiz, NoVP *novo_no, bool *resposta, int *comparacoes) {
    (*comparacoes)++;
    if(raiz == nullptr) {
        (*resposta) = true;
        return novo_no;
    }
    (*comparacoes)++;
    if(novo_no->getId() == raiz->getId()) {
        (*resposta) = false;
    }else {
        (*comparacoes)++;
        // se for menor insere na esquerda
        if(novo_no->getId() < raiz->getId()) {
            raiz->setEsquerdo(ArvoreVP::inserirAux(raiz->getEsquerdo(), novo_no, resposta, comparacoes));
            raiz->getEsquerdo()->setPai(raiz);
        }else {
            // se for maior insere na direita
            raiz->setDireito(ArvoreVP::inserirAux(raiz->getDireito(), novo_no, resposta, comparacoes));
            raiz->getDireito()->setPai(raiz);
        }
    }

    // correções das propriedades
    // caso 1: filho da direita é vermelho e filho da esquerda é preto
    // solução: rotacionar para esquerda
    if(raiz->getDireito()->isVermelho() && raiz->getEsquerdo()->isPreto()) {
        raiz = ArvoreVP::rotacionarEsquerda(raiz);
    }
    // caso 2: filho da esquerda é vermelho e o filho do filho da esquerda tambem é vermelho
    // solução: rotacionar para direita
    if(raiz->getEsquerdo()->isVermelho() && raiz->getEsquerdo()->getEsquerdo()->isVermelho()) {
        raiz = ArvoreVP::rotacionarDireita(raiz);
    }
    // caso 3: ambos os filhos sao vermelhos
    // solucao: trocar as cores
    if(raiz->getEsquerdo()->isVermelho() && raiz->getDireito()->isVermelho()) {
        ArvoreVP::trocarCor(raiz);
    }

    return raiz;
}

// Buscar
NoVP *ArvoreVP::buscar(string id, int *comparacoes) {
    if(this->raiz != nullptr) {
        // Chama recursivamente até encontrar o No, ou percorrer tudo e não encontrar
        NoVP *no = ArvoreVP::buscarAux(this->raiz, id, comparacoes);
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
NoVP *ArvoreVP::buscarAux(NoVP *no, string id, int *comparacoes) {
    if(no != nullptr) {
        (*comparacoes)++;
        // Se achar o no retorna ele
        if(id == no->getId()) {
            return no;
        }

        (*comparacoes)++;
        // Se não achou ainda e o atual for menor que o que ta procurando,
        // tem que ir para direita
        if(id > no->getId()) {
            return ArvoreVP::buscarAux(no->getDireito(), id, comparacoes);
        }

        // Se não, vai para esquerda
        return ArvoreVP::buscarAux(no->getEsquerdo(), id, comparacoes);
    }else {
        return nullptr;
    }
}