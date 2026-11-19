#pragma once

#include "carro.h"
#include "lista_carros.h"

using namespace std;

// ===================== ÁRVORE BINÁRIA DE BUSCA POR PREÇO (R2, R3, R8) =====================
// Índice que mantém os carros organizados por preço. Cada nó aponta para o nó
// da lista (não copia o carro), então não há dados duplicados.
// Regra da BST: esquerda tem preço MENOR; direita tem preço IGUAL ou MAIOR.
// Custo médio de inserir/buscar: O(log n); pior caso (preços já ordenados): O(n).

struct NoArvore {
    NoCarro* carro;       // ponteiro para o nó da lista encadeada
    NoArvore* esquerda;
    NoArvore* direita;
};

// RECURSIVA: insere um carro na árvore pelo preço.
// Parâmetros: raiz - referência ao ponteiro da raiz da (sub)árvore;
//             carro - nó da lista a indexar.
inline void inserirNaArvore(NoArvore*& raiz, NoCarro* carro) {
    if (raiz == nullptr) {  // caso base: achou o lugar vazio
        raiz = new NoArvore;
        raiz->carro = carro;
        raiz->esquerda = nullptr;
        raiz->direita = nullptr;
        return;
    }

    if (carro->carro.preco < raiz->carro->carro.preco) {
        inserirNaArvore(raiz->esquerda, carro);
    } else {
        inserirNaArvore(raiz->direita, carro);
    }
}

// RECURSIVA: busca um carro pelo preço exato.
// Parâmetros: raiz - nó atual; preco - preço procurado.
// Retorno: nó da árvore encontrado ou nullptr. Descarta metade da árvore a cada passo.
inline const NoArvore* buscarPrecoExato(const NoArvore* raiz, double preco) {
    if (raiz == nullptr) {
        return nullptr;
    }

    double precoAtual = raiz->carro->carro.preco;

    if (preco == precoAtual) {
        return raiz;
    }

    return buscarPrecoExato(preco < precoAtual ? raiz->esquerda : raiz->direita, preco);
}

// RECURSIVA: travessia in-ordem (esquerda, raiz, direita) => preços em ordem crescente.
// Parâmetro: raiz - nó atual. Custo O(n).
inline void listarEmOrdem(const NoArvore* raiz) {
    if (raiz == nullptr) {
        return;
    }

    listarEmOrdem(raiz->esquerda);
    exibirCarro(raiz->carro->carro);
    listarEmOrdem(raiz->direita);
}

// RECURSIVA: lista (in-ordem) apenas os carros com preço entre minimo e maximo.
// A BST permite "podar": só desce para um lado se ele puder conter valores da faixa.
// Retorno: quantidade de carros encontrados na faixa.
inline int listarFaixaPreco(const NoArvore* raiz, double minimo, double maximo) {
    if (raiz == nullptr) {
        return 0;
    }

    double preco = raiz->carro->carro.preco;
    int encontrados = 0;

    if (minimo < preco) {
        encontrados += listarFaixaPreco(raiz->esquerda, minimo, maximo);
    }

    if (preco >= minimo && preco <= maximo) {
        exibirCarro(raiz->carro->carro);
        encontrados++;
    }

    if (maximo >= preco) {
        encontrados += listarFaixaPreco(raiz->direita, minimo, maximo);
    }

    return encontrados;
}

// RECURSIVA: calcula a altura da árvore (nº de níveis). Árvore vazia tem altura 0.
// Parâmetro: raiz - nó atual.
inline int alturaArvore(const NoArvore* raiz) {
    if (raiz == nullptr) {
        return 0;
    }

    int alturaEsq = alturaArvore(raiz->esquerda);
    int alturaDir = alturaArvore(raiz->direita);

    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}

// RECURSIVA (pós-ordem): libera todos os nós da árvore com delete.
// Filhos são liberados antes do pai. NÃO apaga os carros (pertencem à lista).
// Parâmetro: raiz - referência ao ponteiro da raiz (vira nullptr).
inline void liberarArvore(NoArvore*& raiz) {
    if (raiz == nullptr) {
        return;
    }

    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);

    delete raiz;
    raiz = nullptr;
}

// Reconstrói o índice do zero a partir da lista atual do estoque.
// Necessário antes de consultar porque cadastros, remoções e edições de preço
// podem deixar a árvore desatualizada (ou com ponteiros inválidos).
// Parâmetros: raiz - referência à raiz do índice; estoque - cabeça da lista.
inline void reconstruirArvore(NoArvore*& raiz, NoCarro* estoque) {
    liberarArvore(raiz);

    for (NoCarro* atual = estoque; atual != nullptr; atual = atual->proximo) {
        inserirNaArvore(raiz, atual);
    }
}
