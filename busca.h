#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include "carro.h"
#include "ordenacao.h"

using namespace std;

// ===================== BUSCA SEQUENCIAL x BINÁRIA (R3, R10) =====================

// BUSCA SEQUENCIAL na lista encadeada: percorre nó a nó até achar.
// Complexidade: O(n) (pior caso: percorre tudo). Não exige lista ordenada.
// Parâmetros: inicio - cabeça; codigo - procurado;
//             comparacoes - saída por referência (soma 1 a cada nó visitado).
// Retorno: nó encontrado ou nullptr.
inline NoCarro* buscaSequencial(NoCarro* inicio, int codigo, long& comparacoes) {
    for (NoCarro* atual = inicio; atual != nullptr; atual = atual->proximo) {
        comparacoes++;

        if (atual->carro.codigo == codigo) {
            return atual;
        }
    }

    return nullptr;
}

// BUSCA BINÁRIA RECURSIVA em vetor de ponteiros ORDENADO por código.
// A cada chamada olha o elemento do meio e descarta metade do intervalo.
// Complexidade: O(log n). Exige vetor ordenado e acesso direto por índice
// (por isso não funciona na lista encadeada, que só permite acesso sequencial).
// Parâmetros: vetor; baixo e alto - limites do intervalo atual; codigo - procurado;
//             comparacoes - saída por referência (1 por passo, no elemento do meio).
// Retorno: índice do elemento ou -1 se não existe.
inline int buscaBinaria(NoCarro** vetor, int baixo, int alto, int codigo, long& comparacoes) {
    if (baixo > alto) {  // caso base: intervalo vazio
        return -1;
    }

    int meio = baixo + (alto - baixo) / 2;  // evita overflow de (baixo + alto)
    int codigoMeio = vetor[meio]->carro.codigo;
    comparacoes++;

    if (codigoMeio == codigo) {
        return meio;
    }

    if (codigo < codigoMeio) {
        return buscaBinaria(vetor, baixo, meio - 1, codigo, comparacoes);
    }

    return buscaBinaria(vetor, meio + 1, alto, codigo, comparacoes);
}

// Resultado de uma medição: quantas comparações e quanto tempo médio por busca.
struct Medicao {
    long comparacoes;
    double nanosegundos;
};

const int REPETICOES = 1000;  // repete a busca para o tempo ser mensurável
static volatile int sumidouro = 0;  // impede o compilador de eliminar as buscas

// Mede a busca sequencial (comparações de 1 busca + tempo médio de REPETICOES buscas).
// Parâmetros: inicio - cabeça da lista; codigo - procurado.
inline Medicao medirSequencial(NoCarro* inicio, int codigo) {
    Medicao medicao = {0, 0.0};
    buscaSequencial(inicio, codigo, medicao.comparacoes);  // 1 busca só para contar

    auto comeco = chrono::steady_clock::now();
    for (int i = 0; i < REPETICOES; i++) {
        long descarte = 0;
        sumidouro = sumidouro + (buscaSequencial(inicio, codigo, descarte) != nullptr);
    }
    auto fim = chrono::steady_clock::now();

    medicao.nanosegundos = chrono::duration<double, nano>(fim - comeco).count() / REPETICOES;
    return medicao;
}

// Mede a busca binária (mesmo formato de medirSequencial).
// Parâmetros: vetor ordenado; tamanho - nº de elementos; codigo - procurado.
inline Medicao medirBinaria(NoCarro** vetor, int tamanho, int codigo) {
    Medicao medicao = {0, 0.0};
    buscaBinaria(vetor, 0, tamanho - 1, codigo, medicao.comparacoes);

    auto comeco = chrono::steady_clock::now();
    for (int i = 0; i < REPETICOES; i++) {
        long descarte = 0;
        sumidouro = sumidouro + (buscaBinaria(vetor, 0, tamanho - 1, codigo, descarte) >= 0);
    }
    auto fim = chrono::steady_clock::now();

    medicao.nanosegundos = chrono::duration<double, nano>(fim - comeco).count() / REPETICOES;
    return medicao;
}

// Imprime uma linha da tabela comparativa para um código-alvo.
// Parâmetros: descricao - nome do caso; codigo - alvo; seq e bin - medições.
inline void imprimirLinhaComparacao(const string& descricao, int codigo,
                                    const Medicao& seq, const Medicao& bin) {
    cout << left << setw(16) << descricao << setw(8) << codigo
         << right << setw(12) << seq.comparacoes << setw(14) << fixed << setprecision(0)
         << seq.nanosegundos << setw(12) << bin.comparacoes << setw(14)
         << bin.nanosegundos << "\n";
}

// Compara as duas buscas em 4 casos: menor código, código do meio, maior código
// e código inexistente (pior caso). O vetor auxiliar é ordenado por código com Bubble Sort.
// Parâmetro: estoque - cabeça da lista (a ordem da lista NÃO é alterada).
inline void compararBuscas(NoCarro* estoque) {
    int tamanho = 0;
    NoCarro** vetor = montarVetor(estoque, tamanho);

    if (vetor == nullptr) {
        cout << "\nEstoque vazio. Cadastre ou gere carros de teste primeiro.\n";
        return;
    }

    bubbleSort(vetor, tamanho, maiorCodigo);

    cout << "\nEstoque com " << tamanho << " carro(s). Tempo = media de " << REPETICOES << " buscas.\n";
    cout << left << setw(16) << "CASO" << setw(8) << "CODIGO" << right << setw(12) << "SEQ.comp"
         << setw(14) << "SEQ.ns" << setw(12) << "BIN.comp" << setw(14) << "BIN.ns" << "\n";

    int alvos[4] = {vetor[0]->carro.codigo, vetor[tamanho / 2]->carro.codigo,
                    vetor[tamanho - 1]->carro.codigo, -1};
    const char* nomes[4] = {"menor codigo", "codigo do meio", "maior codigo", "inexistente"};

    for (int i = 0; i < 4; i++) {
        imprimirLinhaComparacao(nomes[i], alvos[i], medirSequencial(estoque, alvos[i]),
                                medirBinaria(vetor, tamanho, alvos[i]));
    }

    liberarVetor(vetor);
}
