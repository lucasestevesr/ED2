#include <iostream>
#include <fstream>
#include <string>
#include "Review.h"
#include "Arquivo.h"
#include "Ordenar.h"
#include <chrono>

using namespace std;

typedef Review* ReviewPonteiro;

// Definindo constantes para os nomes dos arquivos
const string nome_csv = "tiktok_app_reviews.csv";
const string nome_bin = "tiktok_app_reviews.bin";
const string nome_posicoes = "posicoes_reviews.bin";
const string nome_txt = "export_reviews.txt";
const string nome_input = "input.txt";

void testarQuickSort(ReviewPonteiro *reviews, int n, int *tempo, int *comparacoes, int *movimentacoes) {
    (*tempo) = 0;
    (*comparacoes) = 0;
    (*movimentacoes) = 0;
    auto start = std::chrono::high_resolution_clock::now();
    Ordenar::quickSort(reviews, 0, n-1, comparacoes, movimentacoes);
    auto end = std::chrono::high_resolution_clock::now();
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    (*tempo) = int_m.count();
}

void testarHeapSort(ReviewPonteiro *reviews, int n, int *tempo, int *comparacoes, int *movimentacoes) {
    (*tempo) = 0;
    (*comparacoes) = 0;
    (*movimentacoes) = 0;
    auto start = std::chrono::high_resolution_clock::now();
    Ordenar::heapSort(reviews, n, comparacoes, movimentacoes);
    auto end = std::chrono::high_resolution_clock::now();
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    (*tempo) = int_m.count();
}

void testarRadixSort(ReviewPonteiro *reviews, int n, int *tempo, int *comparacoes, int *movimentacoes) {
    (*tempo) = 0;
    (*comparacoes) = 0;
    (*movimentacoes) = 0;
    auto start = std::chrono::high_resolution_clock::now();
    Ordenar::radixSort(reviews, n, comparacoes, movimentacoes);
    auto end = std::chrono::high_resolution_clock::now();
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    (*tempo) = int_m.count();
}

// Inicio funcao menu de opcoes
int menu() {
    int selecao;
    cout << "-------------------- MENU --------------------" << endl;
    cout << "[1] Analisar Algoritmos de Ordenacao:" << endl;
    cout << "[2] Versoes do app mais frequentes - Hash" << endl;
    cout << "[3] Modulo de Teste" << endl;
    cout << "[0] Sair" << endl;
    cin >> selecao;
    // Retorna a opção escolhida pelo usuário
    return selecao;
}
// Fim funcao menu de opcoes

// Inicio funcao selecionar
void selecionar(int selecao, ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio) {
    // Função serve para fazer o switch da opção escolhida pelo usuário
    switch (selecao) {
        case 0: {
            // Caso escolha 0, fecha o arquivo e finaliza o programa
            cout << "Programa finalizado!" << endl;
            arquivo_processado.close();
            posicoes_salvas.close();
            exit(0);
            break;
        }
        case 1: {
            int m = 3, n = 0;
            int medias[m][3]; // 0 => tempo, 1 => comparacoes, 2 => movimentacoes
            int total = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);

            ifstream arquivo_input;
            arquivo_input.open(diretorio + nome_input);

            int tempo = 0, comparacoes = 0, movimentacoes = 0;
            while(arquivo_input >> n) {
                if(n > 0 && n <= total) {
                    // QuickSort
                    for(int i = 0; i < m; i++) {
                        ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatorios(arquivo_processado, posicoes_salvas, n);
                        testarQuickSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
                        cout << "Quick: tempo = " << to_string(tempo) << " milissegundos, comparacoes = " << to_string(comparacoes) << ", movimentacoes = " << to_string(movimentacoes) << endl;
                        medias[0][0] = tempo/m;
                        medias[0][1] = comparacoes/m;
                        medias[0][2] = movimentacoes/m;
                        Arquivo::desalocarVetorReviews(reviews, n);
                    }
                    // HeapSort
                    for(int i = 0; i < m; i++) {
                        ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatorios(arquivo_processado, posicoes_salvas, n);
                        testarHeapSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
                        cout << "Heap: tempo = " << to_string(tempo) << "milissegundos, comparacoes = " << to_string(comparacoes) << ", movimentacoes = " << to_string(movimentacoes) << endl;
                        medias[1][0] = tempo/m;
                        medias[1][1] = comparacoes/m;
                        medias[1][2] = movimentacoes/m;
                        Arquivo::desalocarVetorReviews(reviews, n);
                    }
                    // RadixSort
                    for(int i = 0; i < m; i++) {
                        ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatorios(arquivo_processado, posicoes_salvas, n);
                        testarHeapSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
                        cout << "Radix: tempo = " << to_string(tempo) << " milissegundos, comparacoes = " << to_string(comparacoes) << ", movimentacoes = " << to_string(movimentacoes) << endl;
                        medias[2][0] = tempo/m;
                        medias[2][1] = comparacoes/m;
                        medias[2][2] = movimentacoes/m;
                        Arquivo::desalocarVetorReviews(reviews, n);
                    }
                    for(int i = 0; i < m; i++) {
                        if(i == 0)
                            cout << "Media Quick: ";
                        else if(i == 1)
                            cout << "Media Heap: ";
                        else
                            cout << "Media Radix: ";
                        cout << "tempo=" << medias[i][0] << " milissegundos, comparacoes=" << medias[i][1] << " movimentacoes=" << medias[i][2] << endl;
                    }
                } else {
                    cout << "Erro: Valor de N lido e invalido!" << endl;
                }
            }
            break;
        }
        case 2: {

            break;
        }
        case 3: {

            break;
        }
        default: {
            cout << "Erro: Opcao invalida!" << endl;
        }
    }
}
// Fim funcao selecionar

// Inicio funcao main menu
void mainMenu(ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio) {
    int selecao = 1;
    while (selecao != 0) {
        selecao = menu();
        selecionar(selecao, arquivo_processado, posicoes_salvas, diretorio);
    }
}
// Fim funcao main menu

// Inicio funcao main
int main(int argc, char const *argv[]) {
    // verificando os parâmetro de input do usuário por linha de comando
    if (argc != 2) {
        cout << "Erro: Esperando: ./<program_name> <diretorio_arquivos>" << endl;
        return 1;
    }

    // declarando e abrindo um arquivo
    ifstream arquivo_bin;
    arquivo_bin.open(argv[1] + nome_bin, ios::binary);

    // abrindo para o modo leitura o arquivo das posicoes tambem
    ifstream posicoes_salvas;
    posicoes_salvas.open(argv[1] + nome_posicoes, ios::binary);

    // verificando se a abertura do arquivo ocorreu sem nenhum erro
    if (arquivo_bin.is_open() && posicoes_salvas.is_open()) {
        // quantidade de registros presentes no arquivo
        int total = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);
        // impressão padrão
        cout << "----------------------------------------------" << endl;
        cout << "Foi encontrado um arquivo bin com " << total << " reviews." << endl;

        // menu de opções para o usuário
        mainMenu(arquivo_bin, posicoes_salvas, argv[1]);

        // else representando um erro de abertura do arquivo
    } else {
        arquivo_bin.close();
        // abrindo o arquivo csv para ser processado
        ifstream arquivo_csv;
        arquivo_csv.open(argv[1] + nome_csv);

        // checando a abertura do arquivo csv antes de processar de o binário
        if (arquivo_csv.is_open()) {

            // abrindo para o modo de escrita
            ofstream arquivo_bin;
            // abrindo o arquivo binario para ser processado
            arquivo_bin.open(argv[1] + nome_bin, ios::binary | ios::trunc);

            //abrindo arquivo para salvar as posições modo de escrita
            ofstream arquivo_posicoes;
            arquivo_posicoes.open(argv[1] + nome_posicoes, ios::binary | ios::trunc);

            // chamando a função de processamento do arquivo
            Arquivo::processar(arquivo_csv, arquivo_bin, arquivo_posicoes);

            // fechando os arquivos abertos
            arquivo_csv.close();
            arquivo_bin.close();
            arquivo_posicoes.close();

            // abrindo para o modo leitura
            ifstream arquivo_processado;
            arquivo_processado.open(argv[1] + nome_bin, ios::binary);

            // abrindo para o modo leitura o arquivo das posicoes tambem
            ifstream posicoes_salvas;
            posicoes_salvas.open(argv[1] + nome_posicoes, ios::binary);

            // checando se o arquivo foi aberto com sucesso
            if (arquivo_processado.is_open()) {
                mainMenu(arquivo_processado, posicoes_salvas, argv[1]);
            } else {
                cout << "Erro: Nao foi possivel abrir o arquivo bin '" << nome_bin << "'" << endl;
                exit(1);
            }
        } else {
            // tratando a exceção para o caso do arquivo csv apresentar problemas na abertura
            cout << "Erro: Nao foi possivel abrir o arquivo csv '" << nome_csv << "'" << endl;
            cout << "Confira se o diretorio realmente existe e contem o arquivo. Atencao nas \\, necessario \\ no final." << endl;
            exit(1);
        }
    }

    return 0;
}
// Fim funcao main