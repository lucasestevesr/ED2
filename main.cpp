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
    cout << "[1] Arvore Vermelho-Preto" << endl;
    cout << "[2] Arvore B" << endl;
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
    int *posicoesReviews = Arquivo::recuperarTodasPosicoes(posicoes_salvas);
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
            int opcao;
            cout << "---------- Arvore Vermelho-Preto ----------" << endl;
            cout << "[1] Analises" << endl;
            cout << "[2] Buscar pelo ID" << endl;
            cout << "[0] Sair" << endl;
            cin >> opcao;

            if(opcao == 1) {
                int m = 3, n = 1000000, n_buscas = 100, intAleatorio = 0;

                double insercao_media = 0;
                double comparacoes_insercao_media = 0;
                double busca_media = 0;
                double comparacoes_busca_media = 0;

                for(int j = 0; j < m; j++) {
                    double insercao = 0;
                    int comparacoes_insercao = 0;
                    double busca = 0;
                    int comparacoes_busca = 0;

                    ArvoreVP *arvoreVp = new ArvoreVP();
                    int *posicoes = new int[n];
                    ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);
                    auto start = std::chrono::high_resolution_clock::now();
                    for(int i = 0; i < n; i++) {
                        arvoreVp->inserir(reviews[i]->getId(), posicoes[i], &comparacoes_insercao);
                    }
                    auto end = std::chrono::high_resolution_clock::now();
                    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    insercao = int_m.count();

                    auto start2 = std::chrono::high_resolution_clock::now();
                    for(int i = 0; i < n_buscas; i++) {
                        intAleatorio = rand()%(n) + 1;
                        arvoreVp->buscar(reviews[intAleatorio]->getId(), &comparacoes_busca);
                    }
                    auto end2 = std::chrono::high_resolution_clock::now();
                    auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
                    busca = int_m2.count();

                    insercao_media += insercao/m;
                    comparacoes_insercao_media += comparacoes_insercao/m;
                    busca_media += busca/m;
                    comparacoes_busca_media += comparacoes_busca/m;

                    delete arvoreVp;
                    delete [] reviews;
                    delete [] posicoes;
                }

                ofstream arquivo_saida;
                arquivo_saida.open(diretorio + nome_saida, ios::trunc);

                arquivo_saida << "============== Arvore Vermelho-Preto ==============" << endl;
                arquivo_saida << "Tempo de insercao de 1000000 reviews: " << insercao_media << endl;
                arquivo_saida << "Quantidade de comparacoes na insercao: " << comparacoes_insercao_media << endl;
                arquivo_saida << "Tempo de busca de 100 reviews: " << busca_media << endl;
                arquivo_saida << "Quantidade de comparacoes na busca: " << comparacoes_busca_media << endl;

                arquivo_saida.close();
            }else if(opcao == 2) {

            }
            break;
        }
        case 2: {
            int opcao;
            cout << "---------------- Arvore B -----------------" << endl;
            cout << "[1] Analises" << endl;
            cout << "[2] Buscar pelo ID" << endl;
            cout << "[0] Sair" << endl;
            cin >> opcao;

            if(opcao == 1) {

            }else if(opcao == 2) {

            }
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