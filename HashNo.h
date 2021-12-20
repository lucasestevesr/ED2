#ifndef ED2_HASHNO_H
#define ED2_HASHNO_H

#include <string>

using namespace std;

class HashNo {
    private:
        // Atributos
        int frequencia;
        string app_version;
        HashNo *proximo;
        // Fim Atributos
    public:
        // Construtor
        HashNo(string app_version, int frequencia);
        // Construtor
        HashNo();
        // Destrutor
        ~HashNo();
        // Getters e Setters
        int getFrequencia();
        void setFrequencia(int frequencia);
        // Incrementar frequencia de um No
        void incrementarFrequencia();
        string getAppVersion();
        void setAppVersion(string appVersion);
        HashNo *getProximo();
        void setProximo(HashNo *proximo);
        // Fim Getters e Setters
};

#endif //ED2_HASHNO_H
