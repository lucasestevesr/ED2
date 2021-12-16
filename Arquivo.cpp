#include "Arquivo.h"

// Inicio Recuperar N reviews aleatorios
ReviewPonteiro* Arquivo::recuperarReviewsAleatorios(ifstream &arquivo_processado, ifstream &posicoes_salvas, int n) {
    int qntReviews = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);
    int intAleatorio;
    if(n <= qntReviews) {
        cout << "Criando vetor..." << endl;
        ReviewPonteiro* reviews = new ReviewPonteiro[n];
        for(int i = 0; i < n; i++) {
            reviews[i] = new Review();
        }
        for(int i = 0; i < n; i++) {
            intAleatorio = rand()%(qntReviews) + 1;
            Review* review = Arquivo::recuperarReviewPeloId(arquivo_processado, posicoes_salvas, intAleatorio);
            reviews[i]->receberReview(review);
        }
        cout << "Vetor Criado!" << endl;
        return reviews;
    }else {
        cout << "Erro: Nao existe essa quantidade de Reviews para importar" << endl;
        return nullptr;
    }
}
// Fim Recuperar N reviews aleatorios


// Início função Buscar Colunas
bool Arquivo::buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual) {
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

void Arquivo::processar(ifstream &arquivo_csv, ofstream &arquivo_bin, ofstream &arquivo_posicoes) {
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
            review->salvarReview(arquivo_bin, arquivo_posicoes);

            // verificando a quantidade de registros lidos na operação
            qnt_linhas++;

            // deletando o vetor colunas
            delete[] colunas;
        }
    }
    // fechando o arquivo binário
    arquivo_bin.close();
    arquivo_posicoes.close();

    // registando o final da operação
    auto end = std::chrono::high_resolution_clock::now();
    // calculando o tempo total de execução
    auto int_m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // imprimindo resultados do processo
    cout << "O tempo de processamento do CSV para BIN foi de " << to_string(int_m.count()) << " milissegundos." << endl;
    cout << "Foram processadas " << qnt_linhas << " reviews." << endl;
    cout << "Processamento finalizado!" << endl;
}

// Recuperar quantidade de Reviews dentro do arquivo
int Arquivo::recuperarQuantidadeReviews(ifstream &posicoes_salvas) {
    // Declara variavel quantidade de Reviews
    int quantidade = 0;
    // Vai para o final do arquivo das posicoes
    posicoes_salvas.clear();
    posicoes_salvas.seekg(0, posicoes_salvas.end);
    // Pega a posicao do final
    int posicaoFinal = posicoes_salvas.tellg();
    // Divide pra saber quantos registros tem no binario
    quantidade = posicaoFinal / sizeof(int);

    return quantidade;
}
// Fim Recuperar quantidade de Reviews dentro do arquivo

// Recuperar Posição Review pelo índice
int Arquivo::recuperarPosicaoReviewPeloId(ifstream &posicoes_salvas, int id) {
    // Declara variaveis uteis de posicao
    int posicaoReview = -1;
    int posicaoCursor = (id - 1) * sizeof(int);

    // Move o cursor para o início do arquivo
    posicoes_salvas.clear();
    posicoes_salvas.seekg(posicaoCursor, posicoes_salvas.beg);

    // Le a posicao do review
    posicoes_salvas.read((char *) &posicaoReview, sizeof(int));

    return posicaoReview;
}
// Fim recuperar Posição Review pelo índice

// Recuperar Review pelo índice
Review* Arquivo::recuperarReviewPeloId(ifstream &arquivo_processado, ifstream &posicoes_salvas, int id) {
    // Declara variaveis auxiliares
    int intAux;
    int idAtual = 1;
    Review *review = new Review();

    // Recupera quantidade total de Reviews
    int total = Arquivo::recuperarQuantidadeReviews(posicoes_salvas);

    // Verificando se existe o review salvo
    if(id <= 0 || id > total) {
        return nullptr;
    }

    // Pegando posicao salva do registro
    int posicao = Arquivo::recuperarPosicaoReviewPeloId(posicoes_salvas, id);

    // Se a posicao for -1 o registro não existe
    if(posicao == -1) {
        return nullptr;
    }

    // Move o cursor para a posicao do review
    arquivo_processado.clear();
    arquivo_processado.seekg(posicao, arquivo_processado.beg);

    // Enquanto o arquivo não lançar excessão continua lendo
    while(arquivo_processado.good()) {
        // Le e seta os atributos da Review
        review->setId(Arquivo::recuperarString(arquivo_processado));
        review->setText(Arquivo::recuperarString(arquivo_processado));
        arquivo_processado.read((char *) &intAux, sizeof(int));
        review->setUpvotes(intAux);
        review->setAppVersion(Arquivo::recuperarString(arquivo_processado));
        review->setPostedDate(Arquivo::recuperarString(arquivo_processado));

        return review;
    }

    return nullptr;
}
// Fim Recuperar Review pelo índice


// Recuperar attributes do tipo string
string Arquivo::recuperarString(ifstream &arquivo_processado) {
    // Declara a variavel texto e a variavel tamanho
    string texto;
    string::size_type tamanho;
    // Le o tamanho da string no arquivo processado
    arquivo_processado.read((char *) &tamanho, sizeof(tamanho));
    // Le a string usando o tamanho lido
    texto.resize(tamanho);
    arquivo_processado.read(&texto[0], tamanho);

    return texto;
}
// Fim Recuperar atributos do tipo string

// Salvar atributos do tipo string
void Arquivo::salvarString(ofstream &arquivo_bin, string valor) {
    // Pega o tamanho da string
    size_t tamanho = valor.size();
    // Escreve o tamanho da string no arquivo
    arquivo_bin.write((char *) &tamanho, sizeof(tamanho));
    // Escreve a string com o tamanho dela no arquivo
    arquivo_bin.write(valor.c_str(), tamanho);
}
// Fim Salvar atributos do tipo string
