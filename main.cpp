#include <iostream>
#include "Review.h"

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cout << "Erro: Esperando: ./<program_name> <arquivo_entrada>" << endl;
        return 1;
    }

    Review *r1 = new Review(1,2,3,4,5);

    cout << "ID: " << r1->getId() << endl;
    cout << "text: " << r1->getText() << endl;
    cout << "votes: " << r1->getUpvotes() << endl;
    cout << "version: " << r1->getAppVersion() << endl;
    cout << "date: " << r1->getPostedDate() << endl;

    return 0;
}
