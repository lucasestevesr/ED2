#include <iostream>
#include <fstream>
#include <string>
#include "Review.h"

using namespace std;

const string nome_csv = "tiktok_app_reviews2.csv";
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

void selecionar(int selecao, ifstream &arquivo_processado) {
    switch (selecao) {
        case 0: {
            cout << "Programa finalizado!" << endl;
            arquivo_processado.close();
            exit(0);
            break;
        }
        case 1: {
            cout << "Digite o indice do registro: " << endl;
            int id;
            cin >> id;
            Review *review = Review::recuperarReviewPeloId(arquivo_processado, id);
            if (review != nullptr) {
                review->imprimir();
            } else {
                cout << "Erro: Registro não encontrado!" << endl;
            }
            break;
        }
        case 2: {
            cout << "[1]-Console      [2]-Arquivo de Texto" << endl;
            int opcao;
            cin >> opcao;
            if (opcao == 1) {
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

void mainMenu(ifstream &arquivo_processado) {
    int selecao = 1;
    while (selecao != 0) {
        selecao = menu();
        selecionar(selecao, arquivo_processado);
    }
}

bool buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual) {
    string dado = "";
    for (int i = 0; i < linha.size(); i++) {
        if (linha[i] == '"' && !entreAspas) {
            entreAspas = true;
        } else if (linha[i] == '"' && entreAspas) {
            entreAspas = false;
        }
        if (linha[i] == ',' && !entreAspas) {
            colunas[colunaAtual] += dado;
            dado = "";
            colunaAtual++;
        } else {
            dado += linha[i];
        }
        if (colunaAtual == 4) {
            dado = "";
            for (int j = linha.size(); j > 0; j--) {
                if (linha[j] == ',') {
                    colunas[colunaAtual] += dado;
                    return true;
                }
                dado = linha[j] + dado;
            }
            break;
        }
        if (i == linha.size() - 1) {
            colunas[colunaAtual] += dado;
            break;
        }
    }
    return false;
}

void salvarString(ofstream &arquivo_bin, string valor) {
    size_t tamanho = valor.size();
    arquivo_bin.write((char *) &tamanho, sizeof(tamanho));
//  arquivo_bin.write(reinterpret_cast<char*>(&tamanho), sizeof(size_t));
    arquivo_bin.write(valor.c_str(), tamanho);
}

void processar(ifstream &arquivo_csv, ofstream &arquivo_bin) {
    cout << "Processando csv para bin..." << endl;
    int qnt_linhas = 0;
    string linha = "";
    int colunaAtual;
    string *colunas;
    bool entreAspas;
    bool resposta;
    int upvotesAux;

    getline(arquivo_csv, linha, '\n');

    while (getline(arquivo_csv, linha, '\n')) {
        if (linha.size() > 0) {
            colunas = new string[5];
            entreAspas = false;
            colunaAtual = 0;

            resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);

            if (!resposta) {
                do {
                    getline(arquivo_csv, linha, '\n');
                    resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);
                } while (!resposta);
            }
            Review *review = new Review(colunas[0], colunas[1], stoi(colunas[2]), colunas[3], colunas[4]);
//            review->imprimir();
            salvarString(arquivo_bin, review->getId());
            salvarString(arquivo_bin, review->getText());
            upvotesAux = review->getUpvotes();
            arquivo_bin.write((char *) &upvotesAux, sizeof(int));
//            arquivo_bin.write(reinterpret_cast<char*>(&upvotesAux), sizeof(int));
            salvarString(arquivo_bin, review->getAppVersion());
            salvarString(arquivo_bin, review->getPostedDate());

            qnt_linhas++;
            delete[] colunas;
        }
    }
    arquivo_bin.close();
    cout << "Foram processadas " << qnt_linhas << " registros." << endl;
    cout << "Processamento finalizado!" << endl;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cout << "Erro: Esperando: ./<program_name> <diretorio_arquivos>" << endl;
        return 1;
    }

    ifstream arquivo_bin;
    arquivo_bin.open(argv[1] + nome_bin, ios::binary);

    if (arquivo_bin.is_open()) {
        mainMenu(arquivo_bin);
    } else {
        arquivo_bin.close();
        ifstream arquivo_csv;
        arquivo_csv.open(argv[1] + nome_csv);

        if (arquivo_csv.is_open()) {
            ofstream arquivo_bin;
            arquivo_bin.open(argv[1] + nome_bin, ios::binary | ios::trunc);

            processar(arquivo_csv, arquivo_bin);

            arquivo_csv.close();
            arquivo_bin.close();

            ifstream arquivo_processado;
            arquivo_processado.open(argv[1] + nome_bin, ios::binary);
            if (arquivo_processado.is_open()) {
                mainMenu(arquivo_processado);
            } else {
                cout << "Erro: Nao foi possivel abrir o arquivo bin '" << nome_bin << "'" << endl;
                exit(1);
            }
        } else {
            cout << "Erro: Nao foi possivel abrir o arquivo csv '" << nome_csv << "'" << endl;
            exit(1);
        }
    }

    return 0;
}