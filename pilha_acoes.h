#pragma once

#include "carro.h"

using namespace std;

// ===================== PILHA DE AÇÕES - DESFAZER (R6) =====================
// Semântica LIFO: a última ação registrada é a primeira a ser desfeita,
// exatamente como o "Ctrl+Z". Por isso a pilha é a estrutura natural aqui.

enum TipoAcao { ACAO_CADASTRO, ACAO_REMOCAO, ACAO_VENDA };

// Uma ação registrada: o que foi feito e uma cópia do carro envolvido.
struct Acao {
    TipoAcao tipo;
    Carro carro;
};

struct NoPilha {
    Acao acao;
    NoPilha* abaixo;  // nó logo abaixo do topo
};

// Empilha uma ação (push) em O(1), alocando um novo nó com new.
// Parâmetros: topo - referência ao ponteiro do topo (será alterado);
//             acao - ação a registrar.
inline void empilhar(NoPilha*& topo, const Acao& acao) {
    NoPilha* novo = new NoPilha;

    novo->acao = acao;
    novo->abaixo = topo;
    topo = novo;
}

// Desempilha (pop) a ação do topo em O(1) e libera o nó com delete.
// Parâmetros: topo - referência ao topo; acao - saída por referência com a ação removida.
// Retorno: true se havia ação, false se a pilha estava vazia.
inline bool desempilhar(NoPilha*& topo, Acao& acao) {
    if (topo == nullptr) {
        return false;
    }

    NoPilha* removido = topo;
    acao = removido->acao;
    topo = removido->abaixo;

    delete removido;
    removido = nullptr;
    return true;
}

// RECURSIVA (R3): conta quantas ações existem na pilha.
// Parâmetro: no - nó atual (começa pelo topo).
inline int tamanhoPilha(const NoPilha* no) {
    if (no == nullptr) {
        return 0;
    }

    return 1 + tamanhoPilha(no->abaixo);
}

// Libera todos os nós da pilha e zera o topo.
// Parâmetro: topo - referência ao topo (vira nullptr no final).
inline void liberarPilha(NoPilha*& topo) {
    Acao descarte;

    while (desempilhar(topo, descarte)) {
        // desempilhar já faz o delete de cada nó
    }
}
