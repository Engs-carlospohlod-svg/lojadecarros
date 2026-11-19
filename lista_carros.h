#pragma once

#include <iomanip>
#include <iostream>
#include "carro.h"
#include "entrada.h"

using namespace std;

// ===================== LISTA ENCADEADA DO ESTOQUE (R2, R3, R4, R5) =====================
// Cada nó guarda um Carro e um ponteiro para o próximo nó. O estoque é
// representado apenas pelo ponteiro "inicio" (cabeça da lista).

// Lê do teclado os dados de um novo carro.
// Parâmetro: codigo - código já gerado pelo sistema (passagem por valor).
// Retorno: struct Carro preenchida e com vendido = false.
inline Carro lerCarro(int codigo) {
    Carro carro;

    carro.codigo = codigo;
    carro.marca = lerTexto("Marca: ");
    carro.modelo = lerTexto("Modelo: ");
    carro.ano = lerInteiro("Ano (1950-2100): ", 1950, 2100);
    carro.preco = lerDecimal("Preco (R$): ", 0.01);
    carro.quilometragem = lerInteiro("Quilometragem: ", 0);
    carro.placa = lerTexto("Placa: ");
    carro.vendido = false;

    return carro;
}

// Insere um carro no início da lista (O(1)), alocando um novo nó com new.
// Parâmetros: inicio - referência ao ponteiro da cabeça (será alterado);
//             carro - dados a copiar para o nó (referência const: evita cópia extra).
inline void inserirNoInicio(NoCarro*& inicio, const Carro& carro) {
    NoCarro* novo = new NoCarro;

    novo->carro = carro;
    novo->proximo = inicio;
    inicio = novo;
}

// Busca sequencial simples por código (versão sem contador, usada internamente).
// Parâmetros: inicio - cabeça da lista; codigo - código procurado.
// Retorno: ponteiro para o nó encontrado ou nullptr.
inline NoCarro* buscarNo(NoCarro* inicio, int codigo) {
    NoCarro* atual = inicio;

    while (atual != nullptr && atual->carro.codigo != codigo) {
        atual = atual->proximo;
    }

    return atual;
}

// Remove da lista o nó com o código informado e libera sua memória (delete).
// Parâmetros: inicio - referência à cabeça (pode mudar se o 1º nó for removido);
//             codigo - código do carro a remover.
// Retorno: true se removeu, false se o código não existe.
inline bool removerNo(NoCarro*& inicio, int codigo) {
    NoCarro* atual = inicio;
    NoCarro* anterior = nullptr;

    while (atual != nullptr && atual->carro.codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        return false;
    }

    if (anterior == nullptr) {
        inicio = atual->proximo;  // removeu a cabeça
    } else {
        anterior->proximo = atual->proximo;  // "pula" o nó removido
    }

    delete atual;
    atual = nullptr;
    return true;
}

// RECURSIVA (R3): conta quantos nós existem a partir de "no".
// Caso base: nó nulo vale 0. Passo: 1 + tamanho do restante da lista. Custo O(n).
// Parâmetro: no - nó atual (ponteiro para const: a função não altera a lista).
inline int contarCarros(const NoCarro* no) {
    if (no == nullptr) {
        return 0;
    }

    return 1 + contarCarros(no->proximo);
}

// RECURSIVA (R3): conta quantos carros já foram vendidos a partir de "no".
// Parâmetro: no - nó atual. Retorno: quantidade de carros com vendido = true.
inline int contarVendidos(const NoCarro* no) {
    if (no == nullptr) {
        return 0;
    }

    return (no->carro.vendido ? 1 : 0) + contarVendidos(no->proximo);
}

// Exibe o cabeçalho da tabela de carros.
inline void exibirCabecalho() {
    cout << "\n" << left << setw(6) << "COD" << setw(12) << "MARCA"
         << setw(14) << "MODELO" << setw(6) << "ANO" << setw(14) << "PRECO (R$)"
         << setw(10) << "KM" << setw(10) << "PLACA" << "STATUS\n";
    cout << string(80, '-') << "\n";
}

// Exibe um carro em uma linha da tabela.
// Parâmetro: carro - referência const (não copia nem altera o carro).
inline void exibirCarro(const Carro& carro) {
    cout << left << setw(6) << carro.codigo << setw(12) << carro.marca
         << setw(14) << carro.modelo << setw(6) << carro.ano
         << setw(14) << fixed << setprecision(2) << carro.preco
         << setw(10) << carro.quilometragem << setw(10) << carro.placa
         << (carro.vendido ? "Vendido" : "Disponivel") << "\n";
}

// Percorre a lista e exibe todos os carros em formato de tabela.
// Parâmetro: inicio - cabeça da lista.
inline void listarCarros(const NoCarro* inicio) {
    if (inicio == nullptr) {
        cout << "\nNenhum carro cadastrado.\n";
        return;
    }

    exibirCabecalho();

    for (const NoCarro* atual = inicio; atual != nullptr; atual = atual->proximo) {
        exibirCarro(atual->carro);
    }
}

// Altera um campo do carro escolhido pelo usuário.
// Parâmetro: carro - referência ao carro que será modificado.
inline void editarCampoCarro(Carro& carro) {
    cout << "\n1 - Marca\n2 - Modelo\n3 - Ano\n4 - Preco\n5 - Quilometragem\n6 - Placa";
    int opcao = lerInteiro("\nCampo que deseja alterar: ", 1, 6);

    switch (opcao) {
        case 1: carro.marca = lerTexto("Nova marca: "); break;
        case 2: carro.modelo = lerTexto("Novo modelo: "); break;
        case 3: carro.ano = lerInteiro("Novo ano: ", 1950, 2100); break;
        case 4: carro.preco = lerDecimal("Novo preco: ", 0.01); break;
        case 5: carro.quilometragem = lerInteiro("Nova quilometragem: ", 0); break;
        default: carro.placa = lerTexto("Nova placa: "); break;
    }

    cout << "\nVeiculo alterado com sucesso!\n";
}

// Libera todos os nós da lista (um delete para cada new) e zera a cabeça.
// Parâmetro: inicio - referência ao ponteiro da cabeça (vira nullptr no final).
inline void liberarLista(NoCarro*& inicio) {
    while (inicio != nullptr) {
        NoCarro* removido = inicio;
        inicio = inicio->proximo;

        delete removido;
        removido = nullptr;
    }
}
