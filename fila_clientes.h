#pragma once

#include <iostream>
#include <string>

using namespace std;

// ===================== FILA DE ATENDIMENTO (R7) =====================
// Semântica FIFO: o primeiro cliente a chegar é o primeiro a ser atendido.
// Guardamos ponteiros para a frente (de onde sai) e para trás (onde entra),
// assim enfileirar e desenfileirar são ambos O(1).

struct Cliente {
    string nome;
    int codigoInteresse;  // código do carro desejado (0 = sem preferência)
};

struct NoFila {
    Cliente cliente;
    NoFila* proximo;
};

struct FilaClientes {
    NoFila* frente = nullptr;
    NoFila* tras = nullptr;
    int tamanho = 0;
};

// Coloca um cliente no final da fila (enqueue), alocando um nó com new.
// Parâmetros: fila - referência à fila (alterada); cliente - dados do cliente.
inline void enfileirar(FilaClientes& fila, const Cliente& cliente) {
    NoFila* novo = new NoFila;

    novo->cliente = cliente;
    novo->proximo = nullptr;

    if (fila.tras == nullptr) {
        fila.frente = novo;  // fila estava vazia
    } else {
        fila.tras->proximo = novo;
    }

    fila.tras = novo;
    fila.tamanho++;
}

// Retira o cliente da frente da fila (dequeue) e libera o nó com delete.
// Parâmetros: fila - referência à fila; cliente - saída por referência.
// Retorno: true se havia cliente, false se a fila estava vazia.
inline bool desenfileirar(FilaClientes& fila, Cliente& cliente) {
    if (fila.frente == nullptr) {
        return false;
    }

    NoFila* removido = fila.frente;
    cliente = removido->cliente;
    fila.frente = removido->proximo;

    if (fila.frente == nullptr) {
        fila.tras = nullptr;  // fila ficou vazia: não pode sobrar ponteiro solto
    }

    delete removido;
    removido = nullptr;
    fila.tamanho--;
    return true;
}

// Exibe os clientes da frente para o fim, com a posição na fila.
// Parâmetro: fila - referência const (só leitura).
inline void exibirFila(const FilaClientes& fila) {
    if (fila.frente == nullptr) {
        cout << "\nNinguem na fila de atendimento.\n";
        return;
    }

    cout << "\nFila de atendimento (" << fila.tamanho << " cliente(s)):\n";
    int posicao = 1;

    for (const NoFila* atual = fila.frente; atual != nullptr; atual = atual->proximo) {
        cout << posicao++ << ". " << atual->cliente.nome;

        if (atual->cliente.codigoInteresse > 0) {
            cout << " (interesse no carro " << atual->cliente.codigoInteresse << ")";
        }

        cout << "\n";
    }
}

// Libera todos os nós restantes da fila.
// Parâmetro: fila - referência à fila (frente e tras viram nullptr).
inline void liberarFila(FilaClientes& fila) {
    Cliente descarte;

    while (desenfileirar(fila, descarte)) {
        // desenfileirar já faz o delete de cada nó
    }
}
