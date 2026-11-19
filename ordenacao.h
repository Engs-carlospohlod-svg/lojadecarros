#pragma once

#include "carro.h"
#include "lista_carros.h"

using namespace std;

// ===================== ORDENAÇÃO (R2, R9) =====================
// Em vez de trocar structs inteiras (com strings), ordenamos um vetor de
// PONTEIROS para os nós da lista: trocar dois ponteiros é muito mais barato
// que copiar dois Carros. Depois, a lista é religada na nova ordem.

// Tipo "ponteiro para função": recebe dois carros e diz se estão fora de ordem.
typedef bool (*Criterio)(const Carro&, const Carro&);

// Critérios de ordenação crescente: retornam true se "a" deve ir DEPOIS de "b".
inline bool maiorCodigo(const Carro& a, const Carro& b) { return a.codigo > b.codigo; }
inline bool maiorPreco(const Carro& a, const Carro& b) { return a.preco > b.preco; }
inline bool maiorAno(const Carro& a, const Carro& b) { return a.ano > b.ano; }

// Copia os ponteiros dos nós da lista para um vetor alocado com new[].
// Parâmetros: inicio - cabeça da lista; tamanho - saída por referência (nº de nós).
// Retorno: vetor de ponteiros (quem chamou deve liberar com liberarVetor) ou nullptr se vazia.
inline NoCarro** montarVetor(NoCarro* inicio, int& tamanho) {
    tamanho = contarCarros(inicio);

    if (tamanho == 0) {
        return nullptr;
    }

    NoCarro** vetor = new NoCarro*[tamanho];
    NoCarro* atual = inicio;

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = atual;
        atual = atual->proximo;
    }

    return vetor;
}

// Libera o vetor criado por montarVetor (delete[]) e zera o ponteiro.
// Não apaga os nós da lista, apenas o vetor auxiliar.
inline void liberarVetor(NoCarro**& vetor) {
    delete[] vetor;
    vetor = nullptr;
}

// BUBBLE SORT com parada antecipada.
// Complexidade: pior e médio caso O(n²) (n(n-1)/2 comparações); melhor caso O(n)
// (vetor já ordenado: uma passada sem trocas). Espaço extra O(1). É estável, pois
// só troca quando o elemento da esquerda é ESTRITAMENTE maior.
// Parâmetros: vetor - ponteiros para os nós; tamanho - quantidade;
//             deveTrocar - critério (ponteiro para função) que define a ordem.
inline void bubbleSort(NoCarro** vetor, int tamanho, Criterio deveTrocar) {
    for (int fim = tamanho - 1; fim > 0; fim--) {  // o maior "flutua" para a posição fim
        bool trocou = false;

        for (int i = 0; i < fim; i++) {
            if (deveTrocar(vetor[i]->carro, vetor[i + 1]->carro)) {
                NoCarro* temporario = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = temporario;
                trocou = true;
            }
        }

        if (!trocou) {
            break;  // nenhuma troca => já está ordenado
        }
    }
}

// Religa os nós da lista na ordem em que aparecem no vetor.
// Parâmetros: inicio - referência à cabeça da lista (passa a apontar para vetor[0]);
//             vetor e tamanho - nós já ordenados.
inline void religarLista(NoCarro*& inicio, NoCarro** vetor, int tamanho) {
    if (tamanho == 0) {
        inicio = nullptr;
        return;
    }

    inicio = vetor[0];

    for (int i = 0; i < tamanho - 1; i++) {
        vetor[i]->proximo = vetor[i + 1];
    }

    vetor[tamanho - 1]->proximo = nullptr;  // último nó termina a lista
}

// Ordena o estoque pelo critério escolhido (monta vetor, ordena, religa, libera vetor).
// Parâmetros: inicio - referência à cabeça da lista; criterio - função de comparação.
inline void ordenarLista(NoCarro*& inicio, Criterio criterio) {
    int tamanho = 0;
    NoCarro** vetor = montarVetor(inicio, tamanho);

    bubbleSort(vetor, tamanho, criterio);
    religarLista(inicio, vetor, tamanho);
    liberarVetor(vetor);
}
