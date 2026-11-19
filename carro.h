#pragma once

#include <string>

using namespace std;

struct Carro {
    int codigo;
    string marca;
    string modelo;
    int ano;
    double preco;
    int quilometragem;
    string placa;
    bool vendido;
};

struct NoCarro {
    Carro carro;
    NoCarro* proximo;
};
