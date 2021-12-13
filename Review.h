#ifndef ED2_REVIEW_H
#define ED2_REVIEW_H

#include <string>

using namespace std;

class Review {
    private:
        // Atributos
        char* id;
        char* text;
        int upvotes;
        char* app_version;
        char* posted_date;
        // Fim Atributos

    public:
        static const int tamanho_id = 90;
        static const int tamanho_text = 3553;
        static const int tamanho_app_version = 11;
        static const int tamanho_posted_date = 21;

    // Construtor com atributos
        Review(char* id, char* text, int upvotes, char* app_version, char* posted_date);
        // Construtor vazio
        Review();
        // Destrutor
        ~Review();
        // Getters e Setters
        string getId();
        void setId(char* id);
        string getText();
        void setText(char* text);
        int getUpvotes();
        void setUpvotes(int upvotes);
        string getAppVersion();
        void setAppVersion(char* app_version);
        string getPostedDate();
        void setPostedDate(char* posted_date);
        // Fim Getters e Setters
        // Imprimir Review
        void imprimir();
        // Salvar atributos do tipo string
        void salvarString(ofstream &arquivo_bin, string valor);
        void salvarId(ofstream &arquivo_bin, char* valor);
        void salvarText(ofstream &arquivo_bin, char* valor);
        void salvarAppVersion(ofstream &arquivo_bin, char* valor);
        void salvarPostedDate(ofstream &arquivo_bin, char* valor);
        // Salvar todos atributos do Review
        void salvarReview(ofstream &arquivo_bin);
        // Recuperar quantidade de Reviews dentro do arquivo
        static int recuperarQuantidadeReviews(ifstream &arquivo_processado);
        // Recuperar atributos do tipo string
        static string recuperarString(ifstream &arquivo_processado);
        static char* recuperarChar(ifstream &arquivo_processado, int tamanho);
        // Recuperar Review pelo índice
        static Review* recuperarReviewPeloId(ifstream &arquivo_processado, int id);
};

#endif //ED2_REVIEW_H
