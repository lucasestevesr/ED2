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
    // Salvar atributos do tipo string
    void salvarString(ofstream &arquivo_bin, string valor);
    // Salvar todos atributos do Review
    void salvarReview(ofstream &arquivo_bin);
    // Recuperar quantidade de Reviews dentro do arquivo
    static int recuperarQuantidadeReviews(ifstream &arquivo_processado);
    // Recuperar atributos do tipo string
    static string recuperarString(ifstream &arquivo_processado);
    // Recuperar Review pelo índice
    static Review* recuperarReviewPeloId(ifstream &arquivo_processado, int id);
};

#endif //ED2_REVIEW_H