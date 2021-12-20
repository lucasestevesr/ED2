#ifndef ED2_HASHNO_H
#define ED2_HASHNO_H

#include <string>

using namespace std;

class HashNo {
    private:
        int frequencia;
        string app_version;
        HashNo *proximo;
    public:
        HashNo(string app_version, int frequencia);
        HashNo();
        ~HashNo();
        int getFrequencia();
        void setFrequencia(int frequencia);
        void incrementarFrequencia();
        string getAppVersion();
        void setAppVersion(string appVersion);
        HashNo *getProximo();
        void setProximo(HashNo *proximo);
};

#endif //ED2_HASHNO_H
