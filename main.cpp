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
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

typedef Review *ReviewPonteiro;

// Definindo constantes para os nomes dos arquivos
const string nome_csv = "tiktok_app_reviews.csv";
const string nome_bin = "tiktok_app_reviews.bin";
const string nome_posicoes = "posicoes_reviews.bin";
const string nome_comprimido = "reviewsComp.bin";
const string nome_descomprimido = "reviewsOrig.bin";
const string nome_saida = "saida.txt";

int menu() {
    int selecao;
    cout << "-------------------- MENU --------------------" << endl;
    cout << "[1] Comprimir e Descomprimir" << endl;
    cout << "[2] Modulo de analises" << endl;
    cout << "[0] Sair" << endl;
    cin >> selecao;

    // Retorna a opção escolhida pelo usuário
    return selecao;
}

void selecionar(int selecao, ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, ReviewPonteiro *reviewsMaior, int *posicoesReviews, int quantidadeReviews) {
    // Função serve para fazer o switch da opção escolhida pelo usuário
    if(selecao == 0) {
        // Caso escolha 0, fecha o arquivo e finaliza o programa
        cout << "Programa finalizado!" << endl;
        arquivo_processado.close();
        posicoes_salvas.close();
        delete [] posicoesReviews;
        Arquivo::desalocarVetorReviews(reviewsMaior, quantidadeReviews);
        exit(0);
    }else if(selecao == 1) {
        // Recuperando N reviews aleatorios
        int n = 0;
        cout << "Comprimir N reviews_texts aleatorios e salva-los em um arquivo reviewsComp.bin" << endl;
        cout << "Digite o valor de N: " << endl;
        cin >> n;
        ReviewPonteiro *reviews_menor = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);

        auto start = std::chrono::high_resolution_clock::now();
        // Concatenando o review text dos reviews aleatorios
        string reviews_texts = "", str = "";
        for(int i = 0; i < n; i++) {
            str = " ";
            for(int j = 0; j < reviews_menor[i]->getText().length(); j++) {
                str += reviews_menor[i]->getText()[j];
                if(j == 50) {
                    break;
                }
            }
            reviews_texts += str;
        }

        // Criando vetor das letras e sua respectivas frequencias zeradas
        int qntMaxLetras = 300;
        char *letras = new char[qntMaxLetras];
        long *frequencias = new long[qntMaxLetras];
        for(int i = 0; i < qntMaxLetras; i++) {
            letras[i] = '$';
            frequencias[i] = 0;
        }

        // Percorre letra por letra e vai incrementando sua frequencia
        long qntChars = reviews_texts.length();
        char letraAtual;
        for(long i = 0; i < qntChars; i++) {
            letraAtual = reviews_texts[i];
            for(int j = 0; j < qntMaxLetras; j++) {
                // Cifrão real que está na string
                if(letras[j] == '$' && letraAtual == '$' && frequencias[j] > 0) {
                    frequencias[j] += 1;
                }else if(letras[j] == '$') { // Cifrão que representa vazio
                    letras[j] = letraAtual;
                    frequencias[j] += 1;
                    break;
                }else if(letraAtual == letras[j]) { // Incrementar outras letras
                    frequencias[j] += 1;
                    break;
                }
            }
        }

        // Soma a quantidade de letras encontradas
        int qntLetrasEncontradas = 0;
        for(int i = 0; i < qntMaxLetras; i++) {
            if(frequencias[i] > 0) {
                qntLetrasEncontradas++;
//                    cout << letras[i] << " : " << frequencias[i] << endl;
            }
        }

        // Comprimindo texto
        int comparacoes = 0;
        HuffmanArvore *arvore = new HuffmanArvore(reviews_texts.length());
        arvore->codificar(letras, frequencias, qntLetrasEncontradas, &comparacoes);
        bool *review_text_comprimido = arvore->comprimirHuffman(letras, frequencias, reviews_texts);
        ofstream comprimidoBin;
//            comprimidoBin.open(diretorio + nome_comprimido, ios::binary | ios::trunc);
        comprimidoBin.open(diretorio + nome_comprimido, ios::trunc);
        for(int i = 0; i < arvore->getTamanhoComprimido(); i++) {
            comprimidoBin << review_text_comprimido[i];
        }

//            comprimidoBin.write((char*)&review_text_comprimido, sizeof(review_text_comprimido));
        comprimidoBin.close();

        auto end = std::chrono::high_resolution_clock::now();
        auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        double tempo_comprimir = int_m.count();

        delete [] letras;
        delete [] frequencias;

        cout << "---------------------------------------------------------------------------------------" << endl;
        cout << "Sucesso! Conjunto de " << n << " reviews aleatorios comprimidos e salvos no arquivo " << nome_comprimido << endl;
        cout << "Quantidade de comparacoes: " << comparacoes << endl;
        cout << "Tempo para comprimir: " << to_string(tempo_comprimir) << " milisegundos" << endl;
        cout << "---------------------------------------------------------------------------------------" << endl;
        cout << "[1] Descomprimir" << endl;
        cout << "[0] Sair" << endl;

        int descomprimir;
        cin >> descomprimir;
        if(descomprimir) {
            auto start2 = std::chrono::high_resolution_clock::now();

            string descomprimido = arvore->descomprimirHuffman(review_text_comprimido);
            ofstream descomprimidoBin;
//            comprimidoBin.open(diretorio + nome_comprimido, ios::binary | ios::trunc);
            descomprimidoBin.open(diretorio + nome_descomprimido, ios::trunc);
            descomprimidoBin << descomprimido;
            descomprimidoBin.close();

            auto end2 = std::chrono::high_resolution_clock::now();
            auto int_m2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
            double tempo_descomprimir = int_m2.count();

            cout << "---------------------------------------------------------------------------------------" << endl;
            cout << "Sucesso! Conjunto de " << n << " reviews aleatorios descomprimidos e salvos no arquivo " << nome_descomprimido << endl;
            cout << "Tempo para descomprimir: " << to_string(tempo_descomprimir) << " milisegundos" << endl;
            cout << "---------------------------------------------------------------------------------------" << endl;
        }

        delete [] reviews_menor;
        delete arvore;
    }else if(selecao == 2) {
        int m = 0, n = 0;
        int ns[] = {10000, 100000, 1000000, 10000, 100000, 1000000, 10000, 100000, 1000000};
        int nAtualIdx = 0;

        cout << "Modulo de testes! Resultados disponiveis no arquivo " << nome_saida << endl;

        ofstream arquivo_saida;
        arquivo_saida.open(diretorio + nome_saida, ios::out | ios::trunc);

        arquivo_saida << "Modulo de testes! Testes realizados com 10000, 100000 e 1000000 reviews." << endl;

        double mediaTempo1 = 0;
        double mediaComparacoes1 = 0;
        double mediaTempo2 = 0;
        double mediaComparacoes2 = 0;
        double mediaTempo3 = 0;
        double mediaComparacoes3 = 0;
        while(m < 9) {
            // Recuperando N reviews aleatorios
            n = ns[nAtualIdx];

            ReviewPonteiro *reviews_menor = Arquivo::recuperarReviewsAleatoriosDoVetor(reviewsMaior, quantidadeReviews, n);

            auto start = std::chrono::high_resolution_clock::now();
            // Concatenando o review text dos reviews aleatorios
            string reviews_texts = "", str = "";
            for(int i = 0; i < n; i++) {
                str = " ";
                for(int j = 0; j < reviews_menor[i]->getText().length(); j++) {
                    str += reviews_menor[i]->getText()[j];
                    if(j == 50) {
                        break;
                    }
                }
                reviews_texts += str;
            }

            // Criando vetor das letras e sua respectivas frequencias zeradas
            int qntMaxLetras = 300;
            char *letras = new char[qntMaxLetras];
            long *frequencias = new long[qntMaxLetras];
            for(int i = 0; i < qntMaxLetras; i++) {
                letras[i] = '$';
                frequencias[i] = 0;
            }

            // Percorre letra por letra e vai incrementando sua frequencia
            long qntChars = reviews_texts.length();
            char letraAtual;
            for(long i = 0; i < qntChars; i++) {
                letraAtual = reviews_texts[i];
                for(int j = 0; j < qntMaxLetras; j++) {
                    // Cifrão real que está na string
                    if(letras[j] == '$' && letraAtual == '$' && frequencias[j] > 0) {
                        frequencias[j] += 1;
                    }else if(letras[j] == '$') { // Cifrão que representa vazio
                        letras[j] = letraAtual;
                        frequencias[j] += 1;
                        break;
                    }else if(letraAtual == letras[j]) { // Incrementar outras letras
                        frequencias[j] += 1;
                        break;
                    }
                }
            }

            // Soma a quantidade de letras encontradas
            int qntLetrasEncontradas = 0;
            for(int i = 0; i < qntMaxLetras; i++) {
                if(frequencias[i] > 0) {
                    qntLetrasEncontradas++;
//                    cout << letras[i] << " : " << frequencias[i] << endl;
                }
            }

            // Comprimindo texto
            int comparacoes = 0;
            HuffmanArvore *arvore = new HuffmanArvore(reviews_texts.length());
            arvore->codificar(letras, frequencias, qntLetrasEncontradas, &comparacoes);
            // Como está no módulo de teste não é necessário criar a string comprimida
            // Porque não vai usa-la para descomprimir e vai alocar memoria atoa
            //bool *review_text_comprimido = arvore->comprimirHuffman(letras, frequencias, reviews_texts);

            auto end = std::chrono::high_resolution_clock::now();
            auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            double tempo_comprimir = int_m.count();

            if(n == ns[0] || n == ns[3] || n == ns[6]) {
                mediaTempo1 += tempo_comprimir/3;
                mediaComparacoes1 += comparacoes/3;
            }else if(n == ns[1] || n == ns[4] || n == ns[7]){
                mediaTempo2 += tempo_comprimir/3;
                mediaComparacoes2 += comparacoes/3;
            }else if(n == ns[2] || n == ns[5] || n == ns[8]){
                mediaTempo3 += tempo_comprimir/3;
                mediaComparacoes3 += comparacoes/3;
            }
            arquivo_saida << "Teste para n=" << n << " comparacoes: " << comparacoes << " tempo: " << to_string(tempo_comprimir) << " milisegundos" << endl;

            delete [] letras;
            delete [] frequencias;
            delete [] reviews_menor;
            delete arvore;
            m++;
            nAtualIdx++;
        }
        cout << "Testes finalizados com sucesso. Os resultados estao disponiveis no arquivo " << nome_saida << endl;
        arquivo_saida << "--------------------------------------------------------------------------------" << endl;
        arquivo_saida << "Media de tempo para 10000 reviews: " << to_string(mediaTempo1) << " milisegundos." << endl;
        arquivo_saida << "Media de comparacoes para 10000 reviews: " << to_string(mediaComparacoes1) << " comparacoes." << endl;
        arquivo_saida << "Media de tempo para 100000 reviews: " << to_string(mediaTempo2) << " milisegundos." << endl;
        arquivo_saida << "Media de comparacoes para 100000 reviews: " << to_string(mediaComparacoes2) << " comparacoes." << endl;
        arquivo_saida << "Media de tempo para 1000000 reviews: " << to_string(mediaTempo3) << " milisegundos." << endl;
        arquivo_saida << "Media de comparacoes para 1000000 reviews: " << to_string(mediaComparacoes3) << " comparacoes." << endl;
    }else {
        cout << "Erro: Opcao invalida!" << endl;
    }
}

void mainMenu(ifstream &arquivo_processado, ifstream &posicoes_salvas, string diretorio, ReviewPonteiro *reviewsMaior, int *posicoesReviews, int quantidadeReviews) {
    int selecao = 1;
    while (selecao != 0) {
        selecao = menu();
        selecionar(selecao, arquivo_processado, posicoes_salvas, diretorio, reviewsMaior, posicoesReviews, quantidadeReviews);
    }
    arquivo_processado.close();
    posicoes_salvas.close();
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