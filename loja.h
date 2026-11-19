#pragma once

#include <iostream>
#include "carro.h"
#include "lista_carros.h"
#include "pilha_acoes.h"
#include "fila_clientes.h"
#include "arvore_precos.h"

using namespace std;

// ===================== LOJA: junta todas as estruturas =====================
// Estoque ........ lista encadeada (dados principais)
// Historico ...... pilha de ações (desfazer)
// Fila ........... fila de clientes aguardando atendimento
// IndicePrecos ... árvore binária de busca por preço (reconstruída sob demanda)

struct Loja {
    NoCarro* estoque = nullptr;
    NoPilha* historico = nullptr;
    FilaClientes fila;
    NoArvore* indicePrecos = nullptr;
    int proximoCodigo = 1;
};

// Cadastra um carro novo, registra a ação na pilha e o insere no estoque.
// Parâmetro: loja - referência à loja (alterada).
inline void cadastrarCarro(Loja& loja) {
    Carro carro = lerCarro(loja.proximoCodigo);

    inserirNoInicio(loja.estoque, carro);
    empilhar(loja.historico, {ACAO_CADASTRO, carro});
    loja.proximoCodigo++;

    cout << "\nCarro cadastrado com sucesso! Codigo: " << carro.codigo << "\n";
}

// Remove um carro do estoque pelo código e registra a ação para poder desfazer.
// Parâmetros: loja - referência à loja; codigo - código do carro.
inline void removerCarro(Loja& loja, int codigo) {
    NoCarro* no = buscarNo(loja.estoque, codigo);

    if (no == nullptr) {
        cout << "\nCarro nao encontrado.\n";
        return;
    }

    empilhar(loja.historico, {ACAO_REMOCAO, no->carro});  // guarda cópia antes do delete
    removerNo(loja.estoque, codigo);
    cout << "\nCarro removido com sucesso!\n";
}

// Marca um carro como vendido e registra a ação na pilha.
// Parâmetros: loja - referência à loja; codigo - código do carro.
// Retorno: true se a venda foi feita, false se não existe ou já estava vendido.
inline bool venderCarro(Loja& loja, int codigo) {
    NoCarro* no = buscarNo(loja.estoque, codigo);

    if (no == nullptr || no->carro.vendido) {
        cout << "\nCarro inexistente ou ja vendido.\n";
        return false;
    }

    no->carro.vendido = true;
    empilhar(loja.historico, {ACAO_VENDA, no->carro});
    cout << "\nVenda registrada com sucesso!\n";
    return true;
}

// Desfaz a última ação (LIFO): cadastro, remoção ou venda.
// Parâmetro: loja - referência à loja.
inline void desfazerUltimaAcao(Loja& loja) {
    Acao acao;

    if (!desempilhar(loja.historico, acao)) {
        cout << "\nNao ha acoes para desfazer.\n";
        return;
    }

    if (acao.tipo == ACAO_CADASTRO) {
        removerNo(loja.estoque, acao.carro.codigo);
        cout << "\nDesfeito: cadastro do carro " << acao.carro.codigo << ".\n";
    } else if (acao.tipo == ACAO_REMOCAO) {
        inserirNoInicio(loja.estoque, acao.carro);
        cout << "\nDesfeito: remocao do carro " << acao.carro.codigo << " (restaurado).\n";
    } else {
        NoCarro* no = buscarNo(loja.estoque, acao.carro.codigo);
        if (no != nullptr) {
            no->carro.vendido = false;
        }
        cout << "\nDesfeito: venda do carro " << acao.carro.codigo << ".\n";
    }
}

// Coloca um novo cliente no fim da fila de atendimento.
// Parâmetro: loja - referência à loja.
inline void entrarNaFila(Loja& loja) {
    Cliente cliente;

    cliente.nome = lerTexto("Nome do cliente: ");
    cliente.codigoInteresse = lerInteiro("Codigo do carro de interesse (0 = nenhum): ", 0);
    enfileirar(loja.fila, cliente);

    cout << "\n" << cliente.nome << " entrou na fila (posicao " << loja.fila.tamanho << ").\n";
}

// Atende o primeiro da fila; se ele tem um carro de interesse disponível, oferece a venda.
// Parâmetro: loja - referência à loja.
inline void atenderProximoCliente(Loja& loja) {
    Cliente cliente;

    if (!desenfileirar(loja.fila, cliente)) {
        cout << "\nNinguem na fila de atendimento.\n";
        return;
    }

    cout << "\nAtendendo: " << cliente.nome << "\n";
    NoCarro* desejado = buscarNo(loja.estoque, cliente.codigoInteresse);

    if (desejado == nullptr || desejado->carro.vendido) {
        cout << "Cliente sem carro de interesse disponivel.\n";
        return;
    }

    exibirCabecalho();
    exibirCarro(desejado->carro);

    if (lerSimNao("Efetuar a venda deste carro")) {
        venderCarro(loja, cliente.codigoInteresse);
    }
}

// Libera TODA a memória da loja: lista, pilha, fila e árvore (todo new tem seu delete).
// Parâmetro: loja - referência à loja (todos os ponteiros viram nullptr).
inline void liberarLoja(Loja& loja) {
    liberarLista(loja.estoque);
    liberarPilha(loja.historico);
    liberarFila(loja.fila);
    liberarArvore(loja.indicePrecos);
}
