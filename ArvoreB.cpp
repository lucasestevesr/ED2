
#include "ArvoreB.h"
#include "NoB.h"
#include <iostream>

using namespace std;

// construtor da ÁrvoreB

ArvoreB::ArvoreB(int grau) {
    raiz = NULL;
    grauArvore = grau;
}


// Destrutor Arvore B

ArvoreB::~ArvoreB() { }

// Verifica se a Arvore está vazia

bool ArvoreB::vazia() {

    return raiz == NULL;
}

// Percorre a Arvore a partir de sua raiz

void ArvoreB::percorreArvore(int indiceBusca) {

    if(vazia()) {

        cout << "Arvore Vazia!!" << endl;
        exit(1);
    }
        
    // raiz->percorreNos();
}

void ArvoreB::insereNo(int indice) {

    if(vazia()) {

        raiz = new NoB(grauArvore, true);
        //raiz->chaves[0] = indice;
        raiz->incrementaTotalNos();
    }
}
