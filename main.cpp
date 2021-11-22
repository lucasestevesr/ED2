#include <iostream>
#include <fstream>
#include <string>
#include "Review.h"
#include <chrono>

using namespace std;

const string nome_csv = "tiktok_app_reviews.csv";
const string nome_bin = "tiktok_app_reviews.bin";
const string nome_txt = "export_reviews.txt";

int menu() {
    int selecao;
    cout << "-------------------- MENU --------------------" << endl;
    cout << "[1] acessarReview(i):" << endl;
    cout << "[2] testeImportacao():" << endl;
    cout << "[0] Sair" << endl;
    cin >> selecao;
    return selecao;
}

void selecionar(int selecao, ifstream &arquivo_processado, string diretorio) {
    switch (selecao) {
        case 0: {
            cout << "Programa finalizado!" << endl;
            arquivo_processado.close();
            exit(0);
            break;
        }
        case 1: {
            int total = Review::recuperarQuantidadeReviews(arquivo_processado);
            cout << "O arquivo contem " << total << " reviews, digite um indice:"  << endl;
            int id;
            cin >> id;
            auto start = std::chrono::high_resolution_clock::now();
            Review *review = Review::recuperarReviewPeloId(arquivo_processado, id);
            if (review != nullptr) {
                review->imprimir();
            } else {
                cout << "Erro: Review nao encontrado!" << endl;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            cout << "O tempo de busca do Id=" << id << " foi de " << to_string(int_m.count()) << " milissegundos." << endl;
            break;
        }
        case 2: {
            cout << "[1]-Console      [2]-Arquivo de Texto" << endl;
            int opcao;
            cin >> opcao;
            srand(time(0));
            int total = Review::recuperarQuantidadeReviews(arquivo_processado);
            if (opcao == 1) {
                auto start = std::chrono::high_resolution_clock::now();
                int n = 10;
                int intAleatorio;
                for(int i = 0; i < n; i++) {
                    intAleatorio = rand()%total;
                    cout << "Review ID = " << intAleatorio << " abaixo:" << endl;
                    Review *review = Review::recuperarReviewPeloId(arquivo_processado, intAleatorio);
                    if (review != nullptr) {
                        review->imprimir();
                    } else {
                        cout << "Erro: Review nao encontrado!" << endl;
                    }
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                cout << "O tempo para exibir " << n << " reviews aleatorios no console foi de " << to_string(int_m.count()) << " milissegundos." << endl;
            } else if(opcao == 2) {
                auto start = std::chrono::high_resolution_clock::now();
                int n = 100;
                cout << "Exportando " << n << " reviews para o arquivo " << nome_txt << endl;
                ofstream arquivo_txt;
                arquivo_txt.open(diretorio + nome_txt, ios::trunc);
                arquivo_txt << "Contêm " << n << " reviews neste arquivo." << endl << endl;
                int intAleatorio;
                for(int i = 0; i < n; i++) {
                    intAleatorio = rand()%total;
                    Review *review = Review::recuperarReviewPeloId(arquivo_processado, intAleatorio);
                    if (review != nullptr) {
                        arquivo_txt << "Index: " << intAleatorio << endl;
                        arquivo_txt << "Id: " << review->getId() << endl;
                        arquivo_txt << "Text: " << review->getText() << endl;
                        arquivo_txt << "Upvotes: " << to_string(review->getUpvotes()) << endl;
                        arquivo_txt << "App Version: " << review->getAppVersion() << endl;
                        arquivo_txt << "Posted Date: " << review->getPostedDate() << endl << endl;
                    } else {
                        cout << "Erro: Review " << intAleatorio << " nao encontrado!" << endl;
                    }
                }
                arquivo_txt.close();
                auto end = std::chrono::high_resolution_clock::now();
                auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                cout << "O tempo para exportar " << n << " reviews aleatorios foi de " << to_string(int_m.count()) << " milissegundos." << endl;
                cout << "Finalizado com sucesso!" << endl;
            } else {
                cout << "Resposta Invalida! Responda [1] ou [2]." << endl;
            }
            break;
        }
        default: {
            cout << "Erro: Opcao invalida!" << endl;
        }
    }
}

void mainMenu(ifstream &arquivo_processado, string diretorio) {
    int selecao = 1;
    while (selecao != 0) {
        selecao = menu();
        selecionar(selecao, arquivo_processado, diretorio);
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

void processar(ifstream &arquivo_csv, ofstream &arquivo_bin) {
    auto start = std::chrono::high_resolution_clock::now();
    cout << "Processando csv para bin..." << endl;
    int qnt_linhas = 0;
    string linha = "";
    int colunaAtual;
    string *colunas;
    bool entreAspas;
    bool resposta;

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
            review->salvarReview(arquivo_bin);

            qnt_linhas++;
            delete[] colunas;
        }
    }
    if(qnt_linhas > 0) {
        arquivo_bin.write((char *) &qnt_linhas, sizeof(int));
    }
    arquivo_bin.close();
    auto end = std::chrono::high_resolution_clock::now();
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "O tempo de processamento do CSV para BIN foi de " << to_string(int_m.count()) << " milissegundos." << endl;
    cout << "Foram processadas " << qnt_linhas << " reviews." << endl;
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
        int total = Review::recuperarQuantidadeReviews(arquivo_bin);
        cout << "----------------------------------------------" << endl;
        cout << "Foi encontrado um arquivo bin com " << total << " reviews." << endl;
        mainMenu(arquivo_bin, argv[1]);
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
                mainMenu(arquivo_processado, argv[1]);
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