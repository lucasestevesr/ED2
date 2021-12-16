#ifndef ED2_REVIEW_H
#define ED2_REVIEW_H

#include <string>

using namespace std;

class Review {
    private:
        // Atributos
        string id;
        string text;
        int upvotes;
        string app_version;
        string posted_date;
        // Fim Atributos

    public:
        // Construtor com atributos
        Review(string id, string text, int upvotes, string app_version, string posted_date);
        // Construtor vazio
        Review();
        // Destrutor
        ~Review();
        // Getters e Setters
        string getId();
        void setId(string id);
        string getText();
        void setText(string text);
        int getUpvotes();
        void setUpvotes(int upvotes);
        string getAppVersion();
        void setAppVersion(string app_version);
        string getPostedDate();
        void setPostedDate(string posted_date);
        // Fim Getters e Setters
        // Imprimir Review
        void imprimir();
        // Receber todos campos do review
        void receberReview(Review* review);
        // Salvar todos atributos do Review
        void salvarReview(ofstream &arquivo_bin, ofstream &arquivo_posicoes);
};

#endif //ED2_REVIEW_H