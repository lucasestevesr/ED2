#include <iostream>
#include <fstream>
#include <string>
#include "Review.h"
#include "Arquivo.h"
#include "Ordenar.h"
#include <chrono>

using namespace std;

typedef Review* ReviewP;

// Definindo constantes para os nomes dos arquivos
const string nome_csv = "tiktok_app_reviews.csv";
const string nome_bin = "tiktok_app_reviews.bin";
const string nome_posicoes = "posicoes_reviews.bin";
const string nome_txt = "export_reviews.txt";

// Inicio funcao menu de opcoes
int menu() {
    int selecao;
    cout << "-------------------- MENU --------------------" << endl;
    cout << "[1] acessarReview(i):" << endl;
    cout << "[2] testeImportacao():" << endl;
    cout << "[3] importarVetor():" << endl;
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
            // Recupera quantidade total de reviews para exibir a faixa para o usuário
            int total = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);
            // Pergunta e le qual id de review ele quer acessar
            cout << "O arquivo contem " << total << " reviews, digite um indice:"  << endl;
            int id;
            cin >> id;
            // Starta o cronometro
            auto start = std::chrono::high_resolution_clock::now();
            // Chama a função para recuperar o Review pelo id
            Review *review = Arquivo::recuperarReviewPeloId(arquivo_processado, posicoes_salvas, id);
            // Se o review retornado for diferente de nullptr vai imprimi-lo
            if (review != nullptr) {
                review->imprimir();
            } else {
                // Se não encontrar o review exibe um erro
                cout << "Erro: Review nao encontrado!" << endl;
            }
            // Finaliza cronometro e exibe o tempo em milissegundos
            auto end = std::chrono::high_resolution_clock::now();
            auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            cout << "O tempo de busca do Id=" << id << " foi de " << to_string(int_m.count()) << " milissegundos." << endl;
            break;
        }
        case 2: {
            // Exibe as opções para o usuário e le
            cout << "[1]-Console      [2]-Arquivo de Texto" << endl;
            int opcao;
            cin >> opcao;
            // Seta a seed do aleatório
            srand(time(0));
            // Recupera a quantidade de reviews salva dentro do arquivo binário
            int total = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);
            // Se a opção do usuário for 1 é pra exibir n=10 reviews no console
            if (opcao == 1) {
                // Starta cronometro
                auto start = std::chrono::high_resolution_clock::now();
                // Declara quantidade de Reviews
                int n = 10;
                int intAleatorio;
                // Loop de 0 a n-1 para pegar N reviews aleatórios
                for(int i = 0; i < n; i++) {
                    // Pega o int aleatório
                    intAleatorio = rand()%(total) + 1;
                    // Escreve seu id
                    cout << "Review ID = " << intAleatorio << " abaixo:" << endl;
                    // Recupera o Review
                    Review *review = Arquivo::recuperarReviewPeloId(arquivo_processado, posicoes_salvas, intAleatorio);
                    // Se for diferente de null, escreve o Review, se for null escreve erro
                    if (review != nullptr) {
                        review->imprimir();
                    } else {
                        cout << "Erro: Review nao encontrado!" << endl;
                    }
                }
                // Finaliza cronometro e exibe o tempo em milissegundos
                auto end = std::chrono::high_resolution_clock::now();
                auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                cout << "O tempo para exibir " << n << " reviews aleatorios no console foi de " << to_string(int_m.count()) << " milissegundos." << endl;
            } else if(opcao == 2) {
                // Starta cronometro
                auto start = std::chrono::high_resolution_clock::now();
                int n = 100;
                cout << "Exportando " << n << " reviews para o arquivo " << nome_txt << endl;
                // Abre o arquivo txt para exportar os reviews
                ofstream arquivo_txt;
                arquivo_txt.open(diretorio + nome_txt, ios::trunc);
                // Escreve um cabeçalho com a quantidade de reviews exportados no arquivo txt
                arquivo_txt << "Contêm " << n << " reviews neste arquivo." << endl << endl;
                int intAleatorio;
                // Loop para pegar N registros aleatórios
                for(int i = 0; i < n; i++) {
                    // Pega um int aleatório e busca seu Review correspondente
                    intAleatorio = rand()%(total) + 1;
                    Review *review = Arquivo::recuperarReviewPeloId(arquivo_processado, posicoes_salvas, intAleatorio);
                    if (review != nullptr) {
                        // Escreve o review no arquivo txt
                        arquivo_txt << "Index: " << intAleatorio << endl;
                        arquivo_txt << "Id: " << review->getId() << endl;
                        arquivo_txt << "Text: " << review->getText() << endl;
                        arquivo_txt << "Upvotes: " << to_string(review->getUpvotes()) << endl;
                        arquivo_txt << "App Version: " << review->getAppVersion() << endl;
                        arquivo_txt << "Posted Date: " << review->getPostedDate() << endl << endl;
                    } else {
                        // Se não encontrar da erro
                        cout << "Erro: Review " << intAleatorio << " nao encontrado!" << endl;
                    }
                }
                // Fecha o arquivo txt
                arquivo_txt.close();
                // Finaliza cronometro e exibe o tempo em milissegundos
                auto end = std::chrono::high_resolution_clock::now();
                auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                cout << "O tempo para exportar " << n << " reviews aleatorios foi de " << to_string(int_m.count()) << " milissegundos." << endl;
                cout << "Finalizado com sucesso!" << endl;
            } else {
                cout << "Resposta Invalida! Responda [1] ou [2]." << endl;
            }
            break;
        }
        case 3: {
            cout << "Digite o valor de N: " << endl;
            int n = 0;
            cin >> n;
            ReviewP* reviews = Arquivo::recuperarReviewsAleatorios(arquivo_processado, posicoes_salvas, n);
            for(int u = 0; u < n; u++) {
                cout << reviews[u]->getUpvotes() << ", ";
            }
            cout << endl;
            int comparacoes = 0;
            int movimentacoes = 0;
            //Ordenar::quickSort(reviews, 0, n-1, &comparacoes, &movimentacoes);
            Ordenar::radixSort(reviews, n);
            for(int u = 0; u < n; u++) {
                cout << reviews[u]->getUpvotes() << ", ";
            }
            cout << endl;
            cout << "Vetor ordenado com: " << comparacoes << " comparacoes e " << movimentacoes << " movimentacoes." << endl;
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