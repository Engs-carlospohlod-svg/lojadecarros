#pragma once

#include <iostream>
#include "carro.h"

using namespace std;

// Cadastra um veículo e adiciona no início da lista.
inline void cadastrarCarro(NoCarro*& inicio, int codigo) {
    NoCarro* novo = new NoCarro;

    cout << "\nMarca: ";
    cin >> novo->carro.marca;

    cout << "Modelo: ";
    cin >> novo->carro.modelo;

    cout << "Ano: ";
    cin >> novo->carro.ano;

    cout << "Preco: ";
    cin >> novo->carro.preco;

    cout << "Quilometragem: ";
    cin >> novo->carro.quilometragem;

    cout << "Placa: ";
    cin >> novo->carro.placa;

    novo->carro.codigo = codigo;
    novo->carro.vendido = false;
    novo->proximo = inicio;
    inicio = novo;

    cout << "\nCarro cadastrado com sucesso!\n";
}

// Percorre a lista e exibe todos os veículos cadastrados.
inline void listarCarros(NoCarro* inicio) {
    NoCarro* atual = inicio;

    if (atual == nullptr) {
        cout << "\nNenhum carro cadastrado.\n";
        return;
    }

    while (atual != nullptr) {
        cout << "\nCodigo: " << atual->carro.codigo;
        cout << "\nMarca: " << atual->carro.marca;
        cout << "\nModelo: " << atual->carro.modelo;
        cout << "\nAno: " << atual->carro.ano;
        cout << "\nPreco: R$ " << atual->carro.preco;
        cout << "\nQuilometragem: "
             << atual->carro.quilometragem << " km";
        cout << "\nPlaca: " << atual->carro.placa;
        cout << "\nStatus: "
             << (atual->carro.vendido ? "Vendido" : "Disponivel");
        cout << "\n-----------------------------";

        atual = atual->proximo;
    }
}

// Libera todos os nós da lista encadeada.
inline void liberarLista(NoCarro*& inicio) {
    while (inicio != nullptr) {
        NoCarro* removido = inicio;
        inicio = inicio->proximo;

        delete removido;
        removido = nullptr;
    }
}
// Remove um veículo da lista utilizando seu código.
inline void removerCarro(NoCarro*& inicio, int codigo) {
    NoCarro* atual = inicio;
    NoCarro* anterior = nullptr;

    while (atual != nullptr && atual->carro.codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "\nCarro nao encontrado.\n";
        return;
    }

    if (anterior == nullptr) {
        inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual;
    atual = nullptr;

    cout << "\nCarro removido com sucesso!\n";
}
// Altera os dados de um veículo localizado pelo código.
inline void editarCarro(NoCarro* inicio, int codigo) {
    NoCarro* atual = inicio;

    while (atual != nullptr && atual->carro.codigo != codigo) {
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "\nCarro nao encontrado.\n";
        return;
    }

    int opcao;

    cout << "\n1 - Alterar marca";
    cout << "\n2 - Alterar modelo";
    cout << "\n3 - Alterar ano";
    cout << "\n4 - Alterar preco";
    cout << "\n5 - Alterar quilometragem";
    cout << "\n6 - Alterar placa";
    cout << "\nEscolha o dado que deseja alterar: ";
    cin >> opcao;

    switch (opcao) {
        case 1:
            cout << "Nova marca: ";
            cin >> atual->carro.marca;
            break;

        case 2:
            cout << "Novo modelo: ";
            cin >> atual->carro.modelo;
            break;

        case 3:
            cout << "Novo ano: ";
            cin >> atual->carro.ano;
            break;

        case 4:
            cout << "Novo preco: ";
            cin >> atual->carro.preco;
            break;

        case 5:
            cout << "Nova quilometragem: ";
            cin >> atual->carro.quilometragem;
            break;

        case 6:
            cout << "Nova placa: ";
            cin >> atual->carro.placa;
            break;

        default:
            cout << "\nOpcao invalida!\n";
            return;
    }

    cout << "\nVeiculo alterado com sucesso!\n";
}
inline void buscarCarro(NoCarro* inicio, int codigo) {
    NoCarro* atual = inicio;

    while (atual != nullptr) {
        if (atual->carro.codigo == codigo) {
            cout << "\nCarro encontrado!";
            cout << "\nCodigo: " << atual->carro.codigo;
            cout << "\nMarca: " << atual->carro.marca;
            cout << "\nModelo: " << atual->carro.modelo;
            cout << "\nAno: " << atual->carro.ano;
            cout << "\nPreco: R$ " << atual->carro.preco;
            cout << "\nQuilometragem: " << atual->carro.quilometragem;
            cout << "\nPlaca: " << atual->carro.placa;
            cout << "\nStatus: " << (atual->carro.vendido ? "Vendido" : "Disponivel");
            return;
        }

        atual = atual->proximo;
    }

    cout << "\nCarro nao encontrado.\n";
}
