#ifndef ED2_REVIEW_H
#define ED2_REVIEW_H

#include <string>

using namespace std;

class Review {
    private:
        string id;
        string text;
        int upvotes;
        string app_version;
        string posted_date;

    public:
        Review(string id, string text, int upvotes, string app_version, string posted_date);
        Review();
        ~Review();
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
        void imprimir();
        void salvarString(ofstream &arquivo_bin, string valor);
        void salvarReview(ofstream &arquivo_bin);
        static int recuperarQuantidadeReviews(ifstream &arquivo_processado);
        static string recuperarString(ifstream &arquivo_processado);
        static Review* recuperarReviewPeloId(ifstream &arquivo_processado, int id);
};

#endif //ED2_REVIEW_H
