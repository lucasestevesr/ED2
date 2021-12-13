#include <iostream>
#include <fstream>
#include <string>
#include "Review.h"
#include <chrono>

using namespace std;

// Definindo constantes para os nomes dos arquivos
const string nome_csv = "tiktok_app_reviews.csv";
const string nome_bin = "tiktok_app_reviews.bin";
const string nome_txt = "export_reviews.txt";

// Inicio função menu de opções
int menu() {
    int selecao;
    cout << "-------------------- MENU --------------------" << endl;
    cout << "[1] acessarReview(i):" << endl;
    cout << "[2] testeImportacao():" << endl;
    cout << "[0] Sair" << endl;
    cin >> selecao;
    // Retorna a opção escolhida pelo usuário
    return selecao;
}
// Fim função menu de opções

// Início função selecionar
void selecionar(int selecao, ifstream &arquivo_processado, string diretorio) {
    // Função serve para fazer o switch da opção escolhida pelo usuário
    switch (selecao) {
        case 0: {
            // Caso escolha 0, fecha o arquivo e finaliza o programa
            cout << "Programa finalizado!" << endl;
            arquivo_processado.close();
            exit(0);
            break;
        }
        case 1: {
            // Recupera quantidade total de reviews para exibir a faixa para o usuário
            int total = Review::recuperarQuantidadeReviews(arquivo_processado);
            // Pergunta e le qual id de review ele quer acessar
            cout << "O arquivo contem " << total << " reviews, digite um indice:"  << endl;
            int id;
            cin >> id;
            // Starta o cronometro
            auto start = std::chrono::high_resolution_clock::now();
            // Chama a função para recuperar o Review pelo id
            Review *review = Review::recuperarReviewPeloId(arquivo_processado, id);
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
            int total = Review::recuperarQuantidadeReviews(arquivo_processado);
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
                    Review *review = Review::recuperarReviewPeloId(arquivo_processado, intAleatorio);
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
                    Review *review = Review::recuperarReviewPeloId(arquivo_processado, intAleatorio);
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
        default: {
            cout << "Erro: Opcao invalida!" << endl;
        }
    }
}
// Fim função selecionar

void mainMenu(ifstream &arquivo_processado, string diretorio) {
    int selecao = 1;
    while (selecao != 0) {
        selecao = menu();
        selecionar(selecao, arquivo_processado, diretorio);
    }
}

// Início função Buscar Colunas
bool buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual) {
    // String aux para o dado atual que tiver lendo
    string dado = "";
    // Percorre caracter por caracter da linha
    for (int i = 0; i < linha.size(); i++) {
        // Se encontrar uma " e não tiver entre aspas, define a variavel entre aspas como true
        if (linha[i] == '"' && !entreAspas) {
            entreAspas = true;
        } else if (linha[i] == '"' && entreAspas) {
            // Se encontrar uma " e tiver entre aspas, define a variavel entre aspas como false
            entreAspas = false;
        }
        // Se encontrar uma vírgula e ela não tiver entre aspas chegou no final da coluna
        if (linha[i] == ',' && !entreAspas) {
            // Armazena o dado na coluna atual
            colunas[colunaAtual] += dado;
            // Limpa o dado
            dado = "";
            // Incrementa a coluna atual
            colunaAtual++;
        } else {
            // Vai alimentando a variavel dado com os caracteres
            dado += linha[i];
        }
        // Se tiver na última coluna
        if (colunaAtual == 4) {
            // Limpa a variavel dado
            dado = "";
            // Começa percorrer a linha de trás pra frente pra pegar a ultima coluna
            for (int j = linha.size(); j > 0; j--) {
                // Se achar a vírgula chegou no final
                if (linha[j] == ',') {
                    colunas[colunaAtual] += dado;
                    // Retorna que acabou de ler o registro
                    return true;
                }
                // Incrementa o dado
                dado = linha[j] + dado;
            }
            break;
        }
        // Se chegar no final da linha e ainda não terminou o registro.
        // Volta para a função processar e pega a proxima linha
        if (i == linha.size() - 1) {
            colunas[colunaAtual] += dado;
            break;
        }
    }
    return false;
}
// Fim função Buscar Colunas

void processar(ifstream &arquivo_csv, ofstream &arquivo_bin) {
    // iniciando a marcação do tempo
    auto start = std::chrono::high_resolution_clock::now();
    // mensagem de inicialização
    cout << "Processando csv para bin..." << endl;
    int qnt_linhas = 0;
    string linha = "";
    int colunaAtual;
    string *colunas;
    bool entreAspas;
    bool resposta;

    // retirando o header dos registros
    getline(arquivo_csv, linha, '\n');

    // percorrendo os registros e armazenando seus caracteres até encontrar um delimitador
    while (getline(arquivo_csv, linha, '\n')) {
        // verificando a captura de um registro no arquivo
        if (linha.size() > 0) {
            colunas = new string[5];    // colunas do registro
            entreAspas = false;
            colunaAtual = 0;

            // recuperando as colunas do registro
            resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);
            // o loop executa até que o delimitador do registro seja encontrado. Em cada iteração a função buscarColunas trata as condições que definem o inicio de uma nova coluna
            if (!resposta) {
                do {
                    getline(arquivo_csv, linha, '\n');
                    resposta = buscarColunas(linha, colunas, entreAspas, colunaAtual);
                } while (!resposta);
            }
            // ao fim do registro, é criada uma nova instância de Review com os dados do mesmo
            Review *review = new Review(colunas[0], colunas[1], stoi(colunas[2]), colunas[3], colunas[4]);
//            review->imprimir();
            // Convertendo o registro encontrado para o arquivo binário
            review->salvarReview(arquivo_bin);

            // verificando a quantidade de registros lidos na operação
            qnt_linhas++;

            // deletando o vetor colunas
            delete[] colunas;
        }
    }
    // Salvando a quantidade de reviews no final do arquivo
    if(qnt_linhas > 0) {
        arquivo_bin.write((char *) &qnt_linhas, sizeof(int));
    }

    // fechando o arquivo binário
    arquivo_bin.close();
    // registando o final da operação
    auto end = std::chrono::high_resolution_clock::now();
    // calculando o tempo total de execução
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // imprimindo resultados do processo
    cout << "O tempo de processamento do CSV para BIN foi de " << to_string(int_m.count()) << " milissegundos." << endl;
    cout << "Foram processadas " << qnt_linhas << " reviews." << endl;
    cout << "Processamento finalizado!" << endl;
}

int main(int argc, char const *argv[]) {

    // verificando os parâmetro de input do usuário por linha de comando
    if (argc != 2) {
        cout << "Erro: Esperando: ./<program_name> <diretorio_arquivos>" << endl;
        return 1;
    }

    // declarando e abrindo um arquivo
    ifstream arquivo_bin;
    arquivo_bin.open(argv[1] + nome_bin, ios::binary);

    // verificando se a abertura do arquivo ocorreu sem nenhum erro
    if (arquivo_bin.is_open()) {

        // quantidade de registros presentes no arquivo
        int total = Review::recuperarQuantidadeReviews(arquivo_bin);
        // impressão padrão
        cout << "----------------------------------------------" << endl;
        cout << "Foi encontrado um arquivo bin com " << total << " reviews." << endl;

        // menu de opções para o usuário
        mainMenu(arquivo_bin, argv[1]);

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

            // chamando a função de processamento do arquivo
            processar(arquivo_csv, arquivo_bin);

            // fechando os arquivos abertos
            arquivo_csv.close();
            arquivo_bin.close();

            // abrindo para o modo leitura
            ifstream arquivo_processado;
            arquivo_processado.open(argv[1] + nome_bin, ios::binary);

            // checando se o arquivo foi aberto com sucesso
            if (arquivo_processado.is_open()) {
                mainMenu(arquivo_processado, argv[1]);
            } else {
                cout << "Erro: Nao foi possivel abrir o arquivo bin '" << nome_bin << "'" << endl;
                exit(1);
            }

            // tratando a exceção para o caso do arquivo csv apresentar problemas na abertura
        } else {
            cout << "Erro: Nao foi possivel abrir o arquivo csv '" << nome_csv << "'" << endl;
            cout << "Confira se o diretorio realmente existe e contem o arquivo. Atencao nas \\, necessario \\ no final." << endl;
            exit(1);
        }
    }

    return 0;
}