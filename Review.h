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
};

#endif //ED2_REVIEW_H
