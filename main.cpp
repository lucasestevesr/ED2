#include <iostream>
#include <fstream>
#include <string>
#include "Review.h"
#include "Arquivo.h"
#include "Ordenar.h"
#include "Hash.h"
#include "ArvoreVP.h"
#include <chrono>

using namespace std;

typedef Review *ReviewPonteiro;

// Definindo constantes para os nomes dos arquivos
const string nome_csv = "tiktok_app_reviews.csv";
const string nome_bin = "tiktok_app_reviews.bin";
const string nome_posicoes = "posicoes_reviews.bin";
const string nome_txt = "export_reviews.txt";
const string nome_input = "input.txt";
const string nome_saida = "saida.txt";
const string nome_testes = "teste.txt";

// Inicio funcao testar quickSort
void testarQuickSort(ReviewPonteiro *reviews, int n, int *tempo, int *comparacoes, int *movimentacoes) {
    // Zera as variaveis de analises
    (*tempo) = 0;
    (*comparacoes) = 0;
    (*movimentacoes) = 0;
    // Guarda o time que começou
    auto start = std::chrono::high_resolution_clock::now();
    // Chama a quickSort
    Ordenar::quickSort(reviews, 0, n - 1, comparacoes, movimentacoes);
    // Pega o tempo que acabou e salva
    auto end = std::chrono::high_resolution_clock::now();
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    (*tempo) = int_m.count();
}
// Fim funcao testar quickSort

// Inicio funcao testar heapSort
void testarHeapSort(ReviewPonteiro *reviews, int n, int *tempo, int *comparacoes, int *movimentacoes) {
    // Zera as variaveis de analises
    (*tempo) = 0;
    (*comparacoes) = 0;
    (*movimentacoes) = 0;
    // Guarda o time que começou
    auto start = std::chrono::high_resolution_clock::now();
    // Chama a heapSort
    Ordenar::heapSort(reviews, n, comparacoes, movimentacoes);
    // Pega o tempo que acabou e salva
    auto end = std::chrono::high_resolution_clock::now();
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    (*tempo) = int_m.count();
}
// Fim funcao testar heapSort

// Inicio funcao testar radixSort
void testarRadixSort(ReviewPonteiro *reviews, int n, int *tempo, int *comparacoes, int *movimentacoes) {
    // Zera as variaveis de analises
    (*tempo) = 0;
    (*comparacoes) = 0;
    (*movimentacoes) = 0;
    // Guarda o time que começou
    auto start = std::chrono::high_resolution_clock::now();
    // Chama a radixSort
    Ordenar::radixSort(reviews, n, comparacoes, movimentacoes);
    // Pega o tempo que acabou e salva
    auto end = std::chrono::high_resolution_clock::now();
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    (*tempo) = int_m.count();
}
// Fim funcao testar radixSort

// Inicio funcao testar hash
void testarHash(ReviewPonteiro *reviews, int n, int m, int *tempo) {
    // Zera as variaveis de analises
    (*tempo) = 0;
    string app_version;
    // Guarda o time que começou
    auto start = std::chrono::high_resolution_clock::now();
    Hash *tabelaHash = new Hash(1000);
    for (int i = 0; i < n; i++) {
        // Insere o app version no hash
        app_version = reviews[i]->getAppVersion().empty() ? "(NULL)" : reviews[i]->getAppVersion();
        tabelaHash->inserir(app_version);
    }
    // Imprimir Hash ordenadao
    tabelaHash->imprimirOrdenado(m);
    // Deleta a tabela hash
    delete tabelaHash;
    auto end = std::chrono::high_resolution_clock::now();
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    (*tempo) = int_m.count();
}
// Fim funcao testar hash

// Inicio funcao menu de opcoes
int menu() {
    int selecao;
    cout << "-------------------- MENU --------------------" << endl;
    cout << "[1] Analisar Algoritmos de Ordenacao" << endl;
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
    int quantidadeReviews = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);
    ReviewPonteiro *reviewsMaior = Arquivo::recuperarTodosReviews(arquivo_processado, posicoes_salvas);
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
            int medias[3][3]; // 0 => tempo, 1 => comparacoes, 2 => movimentacoes
            int mediaGeral[3][3];

            for (int i = 0; i < 3; i++) {
                mediaGeral[i][0] = 0;
                mediaGeral[i][1] = 0;
                mediaGeral[i][2] = 0;
            }

            ifstream arquivo_input;
            arquivo_input.open(diretorio + nome_input);

            ofstream arquivo_saida;
            arquivo_saida.open(diretorio + nome_saida, ios::trunc);

            int tempo = 0, comparacoes = 0, movimentacoes = 0;
            if (arquivo_input.is_open()) {
                while (arquivo_input >> n) {
                    if (n > 0 && n <= quantidadeReviews) {
                        for (int i = 0; i < 3; i++) {
                            medias[i][0] = 0;
                            medias[i][1] = 0;
                            medias[i][2] = 0;
                        }
                        arquivo_saida << "============================= N = " << n
                                      << " reviews =============================" << endl;
                        // QuickSort
                        for (int i = 0; i < m; i++) {
                            ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);
                            testarQuickSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
                            arquivo_saida << "Quick " << m << ": tempo = " << to_string(tempo)
                                          << " milissegundos, comparacoes = " << to_string(comparacoes)
                                          << ", movimentacoes = " << to_string(movimentacoes) << endl;
                            medias[0][0] += tempo / m;
                            medias[0][1] += comparacoes / m;
                            medias[0][2] += movimentacoes / m;
                            delete [] reviews;
                        }
                        // HeapSort
                        for (int i = 0; i < m; i++) {
                            ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);
                            testarHeapSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
                            arquivo_saida << "Heap " << m << ": tempo = " << to_string(tempo)
                                          << " milissegundos, comparacoes = " << to_string(comparacoes)
                                          << ", movimentacoes = " << to_string(movimentacoes) << endl;
                            medias[1][0] += tempo / m;
                            medias[1][1] += comparacoes / m;
                            medias[1][2] += movimentacoes / m;
                            delete [] reviews;
                        }
                        // RadixSort
                        for (int i = 0; i < m; i++) {
                            ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);
                            testarRadixSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
                            arquivo_saida << "Radix " << m << ": tempo = " << to_string(tempo)
                                          << " milissegundos, comparacoes = " << to_string(comparacoes)
                                          << ", movimentacoes = " << to_string(movimentacoes) << endl;
                            medias[2][0] += tempo / m;
                            medias[2][1] += comparacoes / m;
                            medias[2][2] += movimentacoes / m;
                            delete [] reviews;
                        }
                        for (int i = 0; i < 3; i++) {
                            if (i == 0)
                                arquivo_saida << "Media Quick: ";
                            else if (i == 1)
                                arquivo_saida << "Media Heap: ";
                            else
                                arquivo_saida << "Media Radix: ";
                            arquivo_saida << "tempo = " << to_string(medias[i][0]) << " milissegundos, comparacoes = "
                                          << to_string(medias[i][1]) << " movimentacoes = " << to_string(medias[i][2])
                                          << endl;
                        }
                        arquivo_saida << "============================================================================="
                                      << endl;
                    } else {
                        cout << "Erro: Valor de N lido e invalido!" << endl;
                    }
                }
                arquivo_saida.close();
                arquivo_input.close();
            } else {
                cout << "Erro: Nao foi possivel abrir o arquivo input.txt contendo os valores de N." << endl;
            }
            break;
        }
        case 2: {
            int n;
            cout << "Digite a quantidade de Reviews: " << endl;
            cin >> n;
            int m;
            cout << "Deseja visualizar quantas versoes mais frequentes? " << endl;
            cin >> m;
            ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);
            int tempo = 0;
            testarHash(reviews, n, m, &tempo);
            cout << "Tempo do Hash = " << to_string(tempo) << " milissegundos" << endl;
            delete [] reviews;
            break;
        }
        case 3: {
            ofstream arquivo_testes;
            arquivo_testes.open(diretorio + nome_testes, ios::trunc);

            // QuickSort
            int n = 100, tempo = 0, comparacoes = 0, movimentacoes = 0;
            ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);
            testarQuickSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
            arquivo_testes << "===================================== Quick Sort ====================================="
                           << endl;
            arquivo_testes << "Tempo = " << to_string(tempo) << " milissegundos, comparacoes = "
                           << to_string(comparacoes) << ", movimentacoes = " << to_string(movimentacoes) << endl;
            for (int i = 0; i < n; i++) {
                arquivo_testes << "Upvotes: " << reviews[i]->getUpvotes() << " Id: " << reviews[i]->getId() << endl;
            }
            arquivo_testes << endl << endl;
            delete [] reviews;

            // HeapSort
            tempo = 0, comparacoes = 0, movimentacoes = 0;
            reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);
            testarHeapSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
            arquivo_testes << "===================================== Heap Sort ====================================="
                           << endl;
            arquivo_testes << "Tempo = " << to_string(tempo) << " milissegundos, comparacoes = "
                           << to_string(comparacoes) << ", movimentacoes = " << to_string(movimentacoes) << endl;
            for (int i = 0; i < n; i++) {
                arquivo_testes << "Upvotes: " << reviews[i]->getUpvotes() << " Id: " << reviews[i]->getId() << endl;
            }
            arquivo_testes << endl << endl;
            delete [] reviews;

            // RadixSort
            tempo = 0, comparacoes = 0, movimentacoes = 0;
            reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);
            testarRadixSort(reviews, n, &tempo, &comparacoes, &movimentacoes);
            arquivo_testes << "===================================== Radix Sort ====================================="
                           << endl;
            arquivo_testes << "Tempo = " << to_string(tempo) << " milissegundos, comparacoes = "
                           << to_string(comparacoes) << ", movimentacoes = " << to_string(movimentacoes) << endl;
            for (int i = 0; i < n; i++) {
                arquivo_testes << "Upvotes: " << reviews[i]->getUpvotes() << " Id: " << reviews[i]->getId() << endl;
            }
            arquivo_testes << endl << endl;
            delete [] reviews;

            // Tabela Hash
            tempo = 0;
            reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);
            string app_version;
            // Guarda o time que começou
            auto start = std::chrono::high_resolution_clock::now();
            Hash *tabelaHash = new Hash(1000);
            for (int i = 0; i < n; i++) {
                app_version = reviews[i]->getAppVersion().empty() ? "(NULL)" : reviews[i]->getAppVersion();
                tabelaHash->inserir(app_version);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            tempo = int_m.count();
            arquivo_testes << "===================================== Tabela Hash ====================================="
                           << endl;
            arquivo_testes << "Tempo = " << to_string(tempo) << " milissegundos" << endl;
            tabelaHash->imprimirArquivo(arquivo_testes);
            delete tabelaHash;
            delete [] reviews;

            arquivo_testes.close();

            cout << "=================================================================" << endl;
            cout << "As informacoes do modulo de teste foram salvas do arquivo teste.txt" << endl;
            cout << "=================================================================" << endl;

            break;
        }
        default: {
            cout << "Erro: Opcao invalida!" << endl;
        }
    }
    Arquivo::desalocarVetorReviews(reviewsMaior, quantidadeReviews);
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
    srand((unsigned) time(NULL));
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
        cout << "================================================" << endl;
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
            if (arquivo_processado.is_open() && posicoes_salvas.is_open()) {
                mainMenu(arquivo_processado, posicoes_salvas, argv[1]);
            } else {
                cout << "Erro: Nao foi possivel abrir o arquivo bin '" << nome_bin << "'" << endl;
                exit(1);
            }
        } else {
            // tratando a exceção para o caso do arquivo csv apresentar problemas na abertura
            cout << "Erro: Nao foi possivel abrir o arquivo csv '" << nome_csv << "'" << endl;
            cout
                    << "Confira se o diretorio realmente existe e contem o arquivo. Atencao nas \\, necessario \\ no final."
                    << endl;
            exit(1);
        }
    }

    return 0;
}
// Fim funcao main