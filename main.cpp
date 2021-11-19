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
            exit(0);
            break;
        }
        case 1: {
            cout << "Digite o indice do registro: " << endl;
            int id;
            cin >> id;
            Review *review = Review::recuperarReviewPeloId(arquivo_processado, id);
            if(review != nullptr) {
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

void mainMenu(ifstream &arquivo_processado) {
    int selecao = 1;
    while(selecao != 0)
    {
        selecao = menu();
        selecionar(selecao, arquivo_processado);
    }
}

bool buscarColunas(string linha, string* colunas, bool &entreAspas, int &colunaAtual) {
    string dado = "";
    for(int i = 0; i < linha.size(); i++) {
        if(linha[i] == '"' && !entreAspas) {
            entreAspas = true;
        }else if(linha[i] == '"' && entreAspas) {
            entreAspas = false;
        }
        if(linha[i] == ',' && !entreAspas) {
            colunas[colunaAtual] += dado;
            dado = "";
            colunaAtual++;
        }else {
            dado += linha[i];
        }
        if(colunaAtual == 4) {
            dado = "";
            for(int j = linha.size(); j > 0; j--) {
                if(linha[j] == ',') {
                    colunas[colunaAtual] += dado;
                    return true;
                }
                dado = linha[j] + dado;
            }
            break;
        }
        if(i == linha.size() - 1) {
            colunas[colunaAtual] += dado;
            break;
        }
    }
    return false;
}

void processar(ifstream &arquivo_csv, ofstream &arquivo_bin) {
    cout << "Processando csv para bin..." << endl;
    // Declara variaveis de controle
    int qnt_linhas = 0;
    string linha = "";
    int colunaAtual;
    string* colunas;
    bool entreAspas;
    bool resposta;
    // Remove a linha do header
    getline(arquivo_csv, linha, '\n');
    // Percorre o arquivo csv
    while (getline(arquivo_csv, linha, '\n')) {
//        while (! inFile.eof() ) {
        colunas = new string[5];
        entreAspas = false;
        colunaAtual = 0;
        // Busca os 5 atributos de cada linha
        resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);
        // Se a linha ainda não terminou
        if(!resposta) {
            // Fica chamando a proxima linha para completar o objeto enquanto ele não terminar
            // de preencher com 5 atributos
            do {
                getline(arquivo_csv, linha, '\n');
                resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);
            }while(!resposta);
        }
        // Cria o review com os atributos
        Review *review = new Review(colunas[0], colunas[1], stoi(colunas[2]), colunas[3], colunas[4]);
        // Escreve o review no arquivo bin
        arquivo_bin.write((char*)review, sizeof(Review));
//        arquivo_bin.write(reinterpret_cast<char *>(review), sizeof(Review));
        // Incrementa as linhas e limpa o vetor de colunas
        qnt_linhas++;
        delete [] colunas;
    }
    cout << "Foram processadas " << qnt_linhas << " registros." << endl;
    cout << "Processamento finalizado!" << endl;
}

int main(int argc, char const *argv[]) {
    // Verifica se passou como argumento o diretorio dos arquivos
    if (argc != 2) {
        cout << "Erro: Esperando: ./<program_name> <diretorio_arquivos>" << endl;
        return 1;
    }

    // Declara e abre o arquivo binário
    ifstream arquivo_bin;
    arquivo_bin.open(argv[1] + nome_bin, ios::binary);

    // Se o arquivo binário processado já existe vai para o menu
    if(arquivo_bin.is_open()) {
        mainMenu(arquivo_bin);
    } else {
        // Se o arquivo ainda não existe, vem processa-lo
        arquivo_bin.close();
        // Declara e abre o arquivo csv fonte dos dados
        ifstream arquivo_csv;
        arquivo_csv.open(argv[1] + nome_csv);

        if(arquivo_csv.is_open()) {
            // Declara e abre o arquivo bin que vai receber os dados
            ofstream arquivo_bin;
            arquivo_bin.open(argv[1] + nome_bin, ios::binary | ios::trunc);

            // Chama a função processar passando os dois arquivos
            processar(arquivo_csv, arquivo_bin);

            // Fecha os dois arquivos após processar
            arquivo_csv.close();
            arquivo_bin.close();

            // Abre o arquivo processado
            ifstream arquivo_processado;
            arquivo_processado.open(argv[1] + nome_bin, ios::binary);
            if(arquivo_processado.is_open()) {
                // Se abriu o arquivo chama o menu
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