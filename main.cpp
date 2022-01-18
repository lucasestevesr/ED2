#include <iostream>
#include <fstream>
#include <string>
#include "Review.h"
#include "Arquivo.h"
#include "Ordenar.h"
#include "Hash.h"
#include "ArvoreVP.h"
#include "ArvoreB.h"
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

void selecionar(int selecao, ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, ReviewPonteiro *reviewsMaior, int *posicoesReviews, int quantidadeReviews) {
    // Função serve para fazer o switch da opção escolhida pelo usuário
    switch (selecao) {
        case 0: {
            // Caso escolha 0, fecha o arquivo e finaliza o programa
            cout << "Programa finalizado!" << endl;
            arquivo_processado.close();
            posicoes_salvas.close();
            delete [] posicoesReviews;
            Arquivo::desalocarVetorReviews(reviewsMaior, quantidadeReviews);
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
                int m = 3, n = 1000000, b = 100, intAleatorio = 0;

                // Metricas das médias
                double insercao_media = 0;
                double comparacoes_insercao_media = 0;
                double busca_media = 0;
                double comparacoes_busca_media = 0;

                for(int j = 0; j < m; j++) {
                    // Zerando métricas locais
                    double insercao = 0;
                    int comparacoes_insercao = 0;
                    double busca = 0;
                    int comparacoes_busca = 0;

                    // Criando árvore, vetor de reviews aleatorios e suas respectivas posicoes
                    ArvoreVP *arvoreVp = new ArvoreVP();
                    int *posicoes = new int[n];
                    ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);

                    // Testes de inserção
                    auto start = std::chrono::high_resolution_clock::now();
                    cout << "Inserindo " << n << " reviews..." << endl;
                    for(int i = 0; i < n; i++) {
                        arvoreVp->inserir(reviews[i]->getId(), posicoes[i], &comparacoes_insercao);
                    }
                    auto end = std::chrono::high_resolution_clock::now();
                    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    insercao = int_m.count();
                    cout << "Tempo Insercao: " << to_string(insercao) << " milisegundos     Comparacoes: " << comparacoes_insercao << endl;

                    // Testes de busca
                    auto start2 = std::chrono::high_resolution_clock::now();
                    cout << "Buscando " << b << " reviews..." << endl;
                    for(int i = 0; i < b; i++) {
                        intAleatorio = rand()%(n) + 1;
                        arvoreVp->buscar(reviews[intAleatorio]->getId(), &comparacoes_busca);
                    }
                    auto end2 = std::chrono::high_resolution_clock::now();
                    auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
                    busca = int_m2.count();
                    cout << "Tempo Busca: " << to_string(busca) << " milisegundos     Comparacoes: " << comparacoes_busca << endl;

                    // Calculando médias das métricas
                    insercao_media += insercao/m;
                    comparacoes_insercao_media += comparacoes_insercao/m;
                    busca_media += busca/m;
                    comparacoes_busca_media += comparacoes_busca/m;

                    // Desalocando memorias
                    delete arvoreVp;
                    delete [] reviews;
                    delete [] posicoes;
                }

                ofstream arquivo_saida;
                arquivo_saida.open(diretorio + nome_saida, ios::trunc);

                arquivo_saida << "============== Arvore Vermelho-Preto ==============" << endl;
                arquivo_saida << "Tempo de insercao de " << n << " reviews: " << insercao_media << " milisegundos" << endl;
                arquivo_saida << "Quantidade de comparacoes na insercao: " << comparacoes_insercao_media << endl;
                arquivo_saida << "Tempo de busca de " << b << " reviews: " << busca_media << " milisegundos" << endl;
                arquivo_saida << "Quantidade de comparacoes na busca: " << comparacoes_busca_media << endl;

                arquivo_saida.close();
            }else if(opcao == 2) {
                int n = 0;
                double insercao = 0, busca = 0;
                int comparacoes_insercao = 0, comparacoes_busca = 0;

                cout << "Deseja importar quantos Reviews para a Arvore?" << endl;
                cin >> n;

                // Criando árvore, vetor de reviews aleatorios e suas respectivas posicoes
                ArvoreVP *arvoreVp = new ArvoreVP();
                int *posicoes = new int[n];
                ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);

                // Testes de inserção
                auto start = std::chrono::high_resolution_clock::now();
                cout << "Inserindo " << n << " reviews..." << endl;
                for(int i = 0; i < n; i++) {
                    arvoreVp->inserir(reviews[i]->getId(), posicoes[i], &comparacoes_insercao);
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                insercao = int_m.count();
                cout << "Tempo Insercao: " << to_string(insercao) << " milisegundos     Comparacoes: " << comparacoes_insercao << endl;

                int continuar = 1;

                do {
                    string id_busca;
                    cout << "Qual ID deseja buscar na Arvore?" << endl;
                    cin >> id_busca;

                    // Teste de busca
                    auto start2 = std::chrono::high_resolution_clock::now();
                    cout << "Buscando o review..." << endl;
                    NoVP *no = arvoreVp->buscar(id_busca, &comparacoes_busca);
                    auto end2 = std::chrono::high_resolution_clock::now();
                    auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
                    busca = int_m2.count();
                    cout << "Tempo Busca: " << to_string(busca) << " milisegundos     Comparacoes: " << comparacoes_busca << endl;

                    if(no != nullptr) {
                        cout << "ID encontrado:" << endl;
                        cout << "ID: " << no->getId() << endl;
                        cout << "Localizacao: " << no->getLocalizacao() << endl;
                    }else {
                        cout << "ID nao encontrado" << endl;
                    }

                    cout << "Deseja buscar outro ID?  [0]-NAO   [1]-SIM" << endl;
                    cin >> continuar;
                }while(continuar == 1);

                // Desalocando memorias
                delete arvoreVp;
                delete [] reviews;
                delete [] posicoes;
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
                cout << "Você selecionou o modulo Analises. Aguarde o resultado..." << endl;
                int n = 10;
                int b1 = 20;
                int b2 = 200;
                int m = 3;
                int intAleatorio = 0;
                int comparacoes = 0;
                //================================================================================
                 ArvoreB *arvoreB = new ArvoreB((int)(b1+1)/2, b1);
                int *posicoes = new int[n];
                ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);
                for (int i = 0; i<n; i++)
                {
                    arvoreB->insereNoArvore(reviews[i]->getId(), posicoes[i], &comparacoes);
                }
                arvoreB->insereNoArvore("gp:AOqpTOEx7_3L-70CUZHq9z_GZPidQ89dzjsV6HUTAeg-v8GFsRiymZXD_0GtBuAw9bzzqvko-xo5lgOriuS2nA", 100, &comparacoes);
                string id;
                cout << "Id?" <<endl;
                cin >> id;
                NoB *noB = arvoreB->buscaNo(id, &comparacoes);
                if (noB != nullptr)
                    cout << "Encontrou o no" << endl;
                else
                    cout << "Nao encontrou o No" << endl;
                delete arvoreB;
                delete [] posicoes;
                delete [] reviews;
               /* // Metricas das médias
                double insercao_media = 0;
                double comparacoes_insercao_media = 0;
                double busca_media = 0;
                double comparacoes_busca_media = 0;

                for(int k = 0; k < m; k++) {
                    // Zerando métricas locais
                    double insercao = 0;
                    int comparacoes_insercao = 0;
                    double busca = 0;
                    int comparacoes_busca = 0;

                    // Criando árvore, vetor de reviews aleatorios e suas respectivas posicoes (Ordem 20)
                    ArvoreB *arvoreB = new ArvoreB((int)(b1+1)/2, b1);
                    int *posicoes = new int[n];
                    ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);

                    // Testes de inserção (Ordem 20)
                    auto start = std::chrono::high_resolution_clock::now();
                    cout << "Inserindo " << n << " reviews..." << endl;
                    for(int i = 0; i < n; i++) {
                        arvoreB->insereNoArvore(reviews[i]->getId(), posicoes[i], &comparacoes_insercao);
                    }
                    auto end = std::chrono::high_resolution_clock::now();
                    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    insercao = int_m.count();
                    cout << "Tempo Insercao: " << to_string(insercao) << " milisegundos     Comparacoes: " << comparacoes_insercao << endl;

                    // Testes de busca ( Ordem 20)
                    auto start2 = std::chrono::high_resolution_clock::now();
                    cout << "Buscando " << b1 << " reviews..." << endl;
                    for(int i = 0; i < b1; i++) {
                        intAleatorio = rand()%(n) + 1;
                        arvoreB->buscaNo(reviews[intAleatorio]->getId(), &comparacoes_busca);
                    }
                    auto end2 = std::chrono::high_resolution_clock::now();
                    auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
                    busca = int_m2.count();
                    cout << "Tempo Busca: " << to_string(busca) << " milisegundos     Comparacoes: " << comparacoes_busca << endl;

                    // Calculando médias das métricas
                    insercao_media += insercao/m;
                    comparacoes_insercao_media += comparacoes_insercao/m;
                    busca_media += busca/m;
                    comparacoes_busca_media += comparacoes_busca/m;

                    // Desalocando memorias
                    delete arvoreB;
                    delete [] reviews;
                    delete [] posicoes;
                }

                ofstream arquivo_saida;
                arquivo_saida.open(diretorio + nome_saida, ios::trunc);

                arquivo_saida << "============== ArvoreB (Ordem = 20) ==============" << endl;
                arquivo_saida << "Tempo de insercao de " << n << " reviews: " << insercao_media << " milisegundos" << endl;
                arquivo_saida << "Quantidade de comparacoes na insercao: " << comparacoes_insercao_media << endl;
                arquivo_saida << "Tempo de busca de " << b1 << " reviews: " << busca_media << " milisegundos" << endl;
                arquivo_saida << "Quantidade de comparacoes na busca: " << comparacoes_busca_media << endl;

                arquivo_saida.close();

                //=================================================================================
                
                */
            }else if(opcao == 2) {
                cout << "Você selecionou o modulo de busca pelo id..." << endl;
                int n = 0, ordem = 0;
                double insercao = 0, busca = 0;
                int comparacoes_insercao = 0, comparacoes_busca = 0;

                cout << "Deseja importar quantos Reviews para a Arvore?" << endl;
                cin >> n;

                cout << "Qual a ordem da Arvore?" << endl;
                cin >> ordem;

                if(ordem < 0) {
                    cout << "Valor invalido para Ordem!" << endl;
                    return;
                }

                // Criando árvore, vetor de reviews aleatorios e suas respectivas posicoes
                ArvoreB *arvoreB = new ArvoreB((int)(ordem=+1)/2, ordem);
                int *posicoes = new int[n];
                ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);

                // Testes de inserção
                auto start = std::chrono::high_resolution_clock::now();
                cout << "Inserindo " << n << " reviews..." << endl;
                for(int i = 0; i < n; i++) {
                    arvoreB->insereNoArvore(reviews[i]->getId(), posicoes[i], &comparacoes_insercao);
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                insercao = int_m.count();
                cout << "Tempo Insercao: " << to_string(insercao) << " milisegundos     Comparacoes: " << comparacoes_insercao << endl;

                int continuar = 1;

                do {
                    string id_busca;
                    cout << "Qual ID deseja buscar na Arvore?" << endl;
                    cin >> id_busca;

                    // Teste de busca
                    auto start2 = std::chrono::high_resolution_clock::now();
                    cout << "Buscando o review..." << endl;
                    NoB *noB = arvoreB->buscaNo(id_busca, &comparacoes_busca);
                    auto end2 = std::chrono::high_resolution_clock::now();
                    auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
                    busca = int_m2.count();
                    cout << "Tempo Busca: " << to_string(busca) << " milisegundos     Comparacoes: " << comparacoes_busca << endl;

                    if(noB != nullptr) {
                        cout << "ID encontrado:" << endl;
                       // cout << "ID: " << noB->getId() << endl;
                       // cout << "Localizacao: " << noB->getLocalizacao() << endl;
                    }else {
                        cout << "ID nao encontrado" << endl;
                    }

                    cout << "Deseja buscar outro ID?  [0]-NAO   [1]-SIM" << endl;
                    cin >> continuar;
                }while(continuar == 1);

                // Desalocando memorias
                delete arvoreB;
                delete [] reviews;
                delete [] posicoes;
                /*
                ArvoreB *arvoreB = new ArvoreB((int)(b1+1)/2, b1);
                int *posicoes = new int[n];
                ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetorComPosicao(reviewsMaior, posicoes, posicoesReviews, quantidadeReviews, n);
                for (int i = 0; i<n; i++)
                {
                    arvoreB->insereNoArvore(reviews[i]->getId(), posicoes[i], 0);
                }
                arvoreB->insereNoArvore("gp:AOqpTOEx7_3L-70CUZHq9z_GZPidQ89dzjsV6HUTAeg-v8GFsRiymZXD_0GtBuAw9bzzqvko-xo5lgOriuS2nA", 100, 0);
                string id;
                cout << "Id?" <<endl;
                cin >> id;
                NoB *noB = arvoreB->buscaNo(id, 0);
                if (noB != nullptr)
                    cout << "Encontrou o no" << endl;
                else
                    cout << "Nao encontrou o No" << endl;
                delete arvoreB;
                delete [] posicoes;
                delete [] reviews; */
            }
            break;
        }
        default: {
            cout << "Erro: Opcao invalida!" << endl;
        }
    }
    delete [] posicoesReviews;
    Arquivo::desalocarVetorReviews(reviewsMaior, quantidadeReviews);
}

void mainMenu(ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, ReviewPonteiro *reviewsMaior, int *posicoesReviews, int quantidadeReviews) {
    int selecao = 1;
    while (selecao != 0) {
        selecao = menu();
        selecionar(selecao, arquivo_processado, posicoes_salvas, diretorio, reviewsMaior, posicoesReviews, quantidadeReviews);
    }
}

int main(int argc, char const *argv[]) {
    // Verificando os parâmetro de input
    srand((unsigned) time(NULL));
    if (argc != 2) {
        cout << "Erro: Esperando: ./<program_name> <diretorio_arquivos>" << endl;
        return 1;
    }

    // Abrindo o arquivo binario e o de posições
    ifstream arquivo_bin;
    arquivo_bin.open(argv[1] + nome_bin, ios::binary);
    ifstream posicoes_salvas;
    posicoes_salvas.open(argv[1] + nome_posicoes, ios::binary);

    // Verificando se abriu os arquivos
    if (arquivo_bin.is_open() && posicoes_salvas.is_open()) {

        // Importando os binarios para vetor
        int quantidadeReviews = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);
        cout << "Foi encontrado um arquivo bin com " << quantidadeReviews << " reviews." << endl;
        ReviewPonteiro *reviewsMaior = Arquivo::recuperarTodosReviews(arquivo_bin, posicoes_salvas);
        int *posicoesReviews = Arquivo::recuperarTodasPosicoes(posicoes_salvas);

        mainMenu(arquivo_bin, posicoes_salvas, argv[1], reviewsMaior, posicoesReviews, quantidadeReviews);
    } else {
        arquivo_bin.close();

        // Abrindo o arquivo csv
        ifstream arquivo_csv;
        arquivo_csv.open(argv[1] + nome_csv);

        // Checando a abertura do arquivo
        if (arquivo_csv.is_open()) {

            // Abrindo o arquivo bin
            ofstream arquivo_bin;
            arquivo_bin.open(argv[1] + nome_bin, ios::binary | ios::trunc);

            // Abrindo arquivo salvar as posições
            ofstream arquivo_posicoes;
            arquivo_posicoes.open(argv[1] + nome_posicoes, ios::binary | ios::trunc);

            // Função para processar o arquivo
            Arquivo::processar(arquivo_csv, arquivo_bin, arquivo_posicoes);

            // Fechando os arquivos abertos
            arquivo_csv.close();
            arquivo_bin.close();
            arquivo_posicoes.close();

            // Abrindo para o modo leitura
            ifstream arquivo_processado;
            arquivo_processado.open(argv[1] + nome_bin, ios::binary);

            // Abrindo para o modo leitura o arquivo das posicoes tambem
            ifstream posicoes_salvas;
            posicoes_salvas.open(argv[1] + nome_posicoes, ios::binary);

            // Checando se o arquivo foi aberto com sucesso
            if (arquivo_processado.is_open() && posicoes_salvas.is_open()) {

                // Importando binários para vetor
                int quantidadeReviews = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);
                ReviewPonteiro *reviewsMaior = Arquivo::recuperarTodosReviews(arquivo_processado, posicoes_salvas);
                int *posicoesReviews = Arquivo::recuperarTodasPosicoes(posicoes_salvas);

                mainMenu(arquivo_processado, posicoes_salvas, argv[1], reviewsMaior, posicoesReviews, quantidadeReviews);
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