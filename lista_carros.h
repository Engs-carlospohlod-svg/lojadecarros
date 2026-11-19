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
