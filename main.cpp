#include <iostream>
#include <fstream>
#include "Review.h"

using namespace std;

const string nome_csv = "tiktok_app_reviews.csv";
const string nome_bin = "tiktok_app_reviews.bin";

int menu() {
    int selecao;
    cout << "--------------- MENU ---------------" << endl;
    cout << "[1] acessaRegistro(i):" << endl;
    cout << "[2] testeImportacao():" << endl;
    cout << "[0] Sair" << endl;
    cin >> selecao;
    return selecao;
}

void selecionar(int selecao) {
    switch (selecao) {
        case 0: {
            cout << "Programa finalizado!" << endl;
            exit(0);
            break;
        }
        case 1: {
            cout << "Digite o indice do registro: " << endl;
            int id;
            cin >> id;
            cout << "Funcao para acessar o registro " << id << " ainda nao implementada!" << endl;
            break;
        }
        case 2: {
            cout << "[1]-Console      [2]-Arquivo de Texto" << endl;
            int opcao;
            cin >> opcao;
            if(opcao == 1) {
                cout << "Importar para console com N = 10" << endl;
            } else {
                cout << "Importar para texto com N = 100" << endl;
            }
            break;
        }
        default: {
            cout << "Erro: Opcao invalida!" << endl;
        }
    }
}

void mainMenu() {
    int selecao = 1;
    while(selecao != 0)
    {
        selecao = menu();
        selecionar(selecao);
    }
}

void processar(ifstream &arquivo_csv, ofstream &arquivo_bin) {
    cout << "Processando csv para bin..." << endl;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cout << "Erro: Esperando: ./<program_name> <diretorio_arquivos>" << endl;
        return 1;
    }

    ifstream arquivo_bin;
    arquivo_bin.open(argv[1] + nome_bin, ios::in);

    if(arquivo_bin.is_open()) {
        mainMenu();
    } else {
        arquivo_bin.close();
        ifstream arquivo_csv;
        arquivo_csv.open(argv[1] + nome_csv, ios::in);

        if(arquivo_csv.is_open()) {
            ofstream arquivo_bin;
            arquivo_bin.open(argv[1] + nome_bin, ios::binary | fstream::trunc);

            processar(arquivo_csv, arquivo_bin);
            arquivo_bin.close();

            mainMenu();
        } else {
            cout << "Erro: Nao foi possivel abrir o arquivo csv '" << nome_csv << "'" << endl;
            exit(1);
        }
    }

    return 0;
}