#ifndef ED2_ARQUIVO_H
#define ED2_ARQUIVO_H

#include "Review.h"
#include <fstream>
#include <iostream>
#include <chrono>

typedef Review* ReviewPonteiro;

class Arquivo {
    public:
        // Processar os Reviews do arquivo csv para o arquivo bin
        static void processar(ifstream &arquivo_csv, ofstream &arquivo_bin, ofstream &arquivo_posicoes);
        // Analisar uma linha enquanto e extrair o Review de cada linha
        static bool buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual);
        // Salvar os atributos do tipo string da Review
        static void salvarString(ofstream &arquivo_bin, string valor);
        // Recuperar os atributos do tipo string da Review
        static string recuperarString(ifstream &arquivo_processado);
        // Recuperar a quantidade de Reviews salvas no arquivo bin
        static int recuperarQuantidadeReviews(ifstream &posicoes_salvas);
        // Recuperar em qual posicao do bin esta salvo o Review
        static int recuperarPosicaoReviewPeloId(ifstream &posicoes_salvas, int id);
        // Recuperar um determinado Review pelo indice
        static Review* recuperarReviewPeloId(ifstream &arquivo_processado, ifstream &posicoes_salvas, int id);
        // Recuperar N Reviews aleatorios do arquivo bin
        static ReviewPonteiro* recuperarReviewsAleatorios(ifstream &arquivo_processado, ifstream &posicoes_salvas, int n);
};

#endif //ED2_ARQUIVO_H
