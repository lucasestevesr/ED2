#ifndef ED2_ARQUIVO_H
#define ED2_ARQUIVO_H

#include "Review.h"
#include <fstream>
#include <iostream>
#include <chrono>

typedef Review* ReviewPonteiro;

class Arquivo {
    public:
        static ReviewPonteiro* recuperarReviewsAleatorios(ifstream &arquivo_processado, ifstream &posicoes_salvas, int n);
        static bool buscarColunas(string linha, string *colunas, bool &entreAspas, int &colunaAtual);
        static void processar(ifstream &arquivo_csv, ofstream &arquivo_bin, ofstream &arquivo_posicoes);
        static int recuperarQuantidadeReviews(ifstream &posicoes_salvas);
        static int recuperarPosicaoReviewPeloId(ifstream &posicoes_salvas, int id);
        static Review* recuperarReviewPeloId(ifstream &arquivo_processado, ifstream &posicoes_salvas, int id);
        static string recuperarString(ifstream &arquivo_processado);
        static void salvarString(ofstream &arquivo_bin, string valor);
};

#endif //ED2_ARQUIVO_H
