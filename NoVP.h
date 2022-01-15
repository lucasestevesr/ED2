#ifndef ED2_NOVP_H
#define ED2_NOVP_H

#include <string>

using namespace std;

class NoVP {
    private:
        // Atributos
        string id;
        int localizacao;
        bool cor;       // preto é false e vermelho é true
        NoVP *pai;
        NoVP *esquerdo;
        NoVP *direito;
        // Fim Atributos

    public:
        // Construtor
        NoVP(string id, int localizacao);
        // Destrutor
        ~NoVP();
        // Getters e Setters
        string getId();
        void setId(string id);
        int getLocalizacao();
        void setLocalizacao(int localizacao);
        bool isVermelho();
        bool isPreto();
        void setVermelho();
        void setPreto();
        void setCor(bool cor);
        NoVP *getPai();
        void setPai(NoVP *pai);
        NoVP *getEsquerdo();
        void setEsquerdo(NoVP *esquerdo);
        NoVP *getDireito();
        void setDireito(NoVP *direito);
        // Fim Getters e Setters

        // Função trocar cor do No
        void trocarCor();
};

#endif //ED2_NOVP_H
