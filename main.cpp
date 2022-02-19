#include <iostream>
#include <fstream>
#include <string>
#include "Review.h"
#include "Arquivo.h"
#include "Ordenar.h"
#include "Hash.h"
#include "ArvoreVP.h"
#include "ArvoreB.h"
#include "HuffmanArvore.h"
#include <chrono>

using namespace std;

typedef Review *ReviewPonteiro;

// Definindo constantes para os nomes dos arquivos
const string nome_csv = "tiktok_app_reviews2.csv";
const string nome_bin = "tiktok_app_reviews.bin";
const string nome_posicoes = "posicoes_reviews.bin";
const string nome_txt = "export_reviews.txt";
const string nome_input = "input.txt";
const string nome_saida = "saida.txt";
const string nome_testes = "teste.txt";

int menu() {
    int selecao;
    cout << "-------------------- MENU --------------------" << endl;
    cout << "[1] Comprimir" << endl;
    cout << "[2] Descomprimir" << endl;
    cout << "[3] Modulo de analises" << endl;
    cout << "[0] Sair" << endl;
    cin >> selecao;

    // Retorna a opção escolhida pelo usuário
    return selecao;
}

void selecionar(int selecao, ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, ReviewPonteiro *reviewsMaior, int *posicoesReviews, int quantidadeReviews, ofstream &arquivo_saida) {
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
            // Recuperando N reviews aleatorios
            int n = 0;
            cout << "Comprimir N reviews_texts aleatorios e salva-los em um arquivo reviewsComp.bin" << endl;
            cout << "Digite o valor de N: " << endl;
            cin >> n;
            //ReviewPonteiro *reviews = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);

            // Concatenando o review text dos reviews aleatorios
            string reviews_texts = "";
            for(int i = 0; i < n; i++) {
                reviews_texts += + " " + reviewsMaior[i]->getText();
            }

            // Criando vetor das letras e sua respectivas frequencias zeradas
            int qntMaxLetras = 300;
            char *letras = new char[qntMaxLetras];
            int *frequencias = new int[qntMaxLetras];
            for(int i = 0; i < qntMaxLetras; i++) {
                letras[i] = '$';
                frequencias[i] = 0;
            }

            // Percorre letra por letra e vai incrementando sua frequencia
            int qntChars = reviews_texts.length();
            char letraAtual;
            int freqCifrao = 0;
            for(int i = 0; i < qntChars; i++) {
                letraAtual = reviews_texts[i];
                if(letraAtual == '$') {
                    freqCifrao += 1;
                } else {
                    for(int j = 1; j < qntMaxLetras; j++) {
                        // Cifrão real que está na string
                        if(letras[j] == '$') { // Cifrão que representa vazio
                            letras[j] = letraAtual;
                            frequencias[j] += 1;
                            break;
                        }else if(letraAtual == letras[j]) { // Incrementar outras letras
                            frequencias[j] += 1;
                            break;
                        }
                    }
                }
            }
            letras[0] = '$';
            frequencias[0] = freqCifrao;

            // Soma a quantidade de letras encontradas
            int qntLetrasEncontradas = 0;
            for(int i = 0; i < qntMaxLetras; i++) {
                if(frequencias[i] > 0) {
                    qntLetrasEncontradas++;
                    cout << "Letra: " << letras[i] << " freq: " << frequencias[i] << endl;
                }
            }
            cout << "Tem: " << qntLetrasEncontradas << " letras" << endl;
            break;
        }
        case 2: {
            string reviews_texts = "geeksforgeeks";

            // Criando vetor das letras e sua respectivas frequencias zeradas
            int qntMaxLetras = 300;
            char *letras = new char[qntMaxLetras];
            int *frequencias = new int[qntMaxLetras];
            for(int i = 0; i < qntMaxLetras; i++) {
                letras[i] = '$';
                frequencias[i] = 0;
            }

            // Percorre letra por letra e vai incrementando sua frequencia
            int qntChars = reviews_texts.length();
            char letraAtual;
            int freqCifrao = 0;
            for(int i = 0; i < qntChars; i++) {
                letraAtual = reviews_texts[i];
                if(letraAtual == '$') {
                    freqCifrao += 1;
                } else {
                    for(int j = 1; j < qntMaxLetras; j++) {
                        // Cifrão real que está na string
                        if(letras[j] == '$') { // Cifrão que representa vazio
                            letras[j] = letraAtual;
                            frequencias[j] += 1;
                            break;
                        }else if(letraAtual == letras[j]) { // Incrementar outras letras
                            frequencias[j] += 1;
                            break;
                        }
                    }
                }
            }
            letras[0] = '$';
            frequencias[0] = freqCifrao;

            // Soma a quantidade de letras encontradas
            int qntLetrasEncontradas = 0;
            for(int i = 0; i < qntMaxLetras; i++) {
                if(frequencias[i] > 0) {
                    qntLetrasEncontradas++;
                }
            }

            HuffmanArvore *arvore = new HuffmanArvore(reviews_texts.length());
            arvore->codificar(letras, frequencias, qntLetrasEncontradas);
            bool *review_text_comprimido = arvore->comprimirHuffman(letras, frequencias, reviews_texts);
//            cout << "Comprimido: ";
//            for(int i = 0; i < arvore->getTamanhoComprimido(); i++) {
//                cout << review_text_comprimido[i];
//            }
//            cout << endl;
            string descomprimido = arvore->descomprimirHuffman(review_text_comprimido);
            cout << "descomprimido: " << descomprimido << endl;
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

void mainMenu(ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, ReviewPonteiro *reviewsMaior, int *posicoesReviews, int quantidadeReviews) {
    // Abrindo arquivo de saida
    ofstream arquivo_saida;
    arquivo_saida.open(diretorio + nome_saida, ios::trunc);
    int selecao = 1;
    while (selecao != 0) {
        selecao = menu();
        selecionar(selecao, arquivo_processado, posicoes_salvas, diretorio, reviewsMaior, posicoesReviews, quantidadeReviews, arquivo_saida);
    }
    delete [] posicoesReviews;
    Arquivo::desalocarVetorReviews(reviewsMaior, quantidadeReviews);
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