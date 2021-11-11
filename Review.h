#ifndef ED2_REVIEW_H
#define ED2_REVIEW_H

using namespace std;

class Review {
    private:
        int id;
        int text;
        int upvotes;
        int app_version;
        int posted_date; // depois trocar pra data

    public:
        Review(int id, int text, int upvotes, int app_version, int posted_date);
        ~Review();
        int getId();
        int setId(int id);
        int getText();
        int setText(int text);
        int getUpvotes();
        int setUpvotes(int upvotes);
        int getAppVersion();
        int setAppVersion(int app_version);
        int getPostedDate();
        int setPostedDate(int posted_date);
};

#endif //ED2_REVIEW_H
