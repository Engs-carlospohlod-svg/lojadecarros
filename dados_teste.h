#pragma once

#include <string>
#include "loja.h"

using namespace std;

// ===================== GERADOR DE CARROS DE TESTE =====================
// Cria muitos carros automaticamente para a demonstração de desempenho
// (busca sequencial x binária e ordenação). Usa um gerador congruencial linear
// com semente fixa, então os dados são "aleatórios" porém repetíveis.

// Gera o próximo número pseudoaleatório a partir da semente.
// Parâmetro: semente - referência ao estado do gerador (é atualizada).
inline unsigned int proximoAleatorio(unsigned int& semente) {
    semente = semente * 1664525u + 1013904223u;
    return semente >> 8;  // descarta bits baixos, que são menos aleatórios
}

// Monta um carro de teste com dados variados.
// Parâmetros: codigo - código do carro; semente - estado do gerador (atualizado).
// Retorno: Carro pronto para inserir no estoque.
inline Carro criarCarroTeste(int codigo, unsigned int& semente) {
    static const char* marcas[] = {"Fiat", "Ford", "Honda", "Toyota", "VW", "Chevrolet"};
    static const char* modelos[] = {"Sedan", "Hatch", "SUV", "Picape", "Esportivo", "Compacto"};

    Carro carro;
    carro.codigo = codigo;
    carro.marca = marcas[proximoAleatorio(semente) % 6];
    carro.modelo = modelos[proximoAleatorio(semente) % 6];
    carro.ano = 2005 + proximoAleatorio(semente) % 21;
    carro.preco = 20000 + proximoAleatorio(semente) % 180000 + 0.99;
    carro.quilometragem = proximoAleatorio(semente) % 200000;
    carro.placa = "TST" + to_string(1000 + codigo % 9000);
    carro.vendido = false;
    return carro;
}

// Insere "quantidade" carros de teste no estoque (sem registrar na pilha de desfazer).
// Parâmetros: loja - referência à loja; quantidade - quantos carros gerar.
inline void gerarCarrosTeste(Loja& loja, int quantidade) {
    unsigned int semente = 12345u + loja.proximoCodigo;

    for (int i = 0; i < quantidade; i++) {
        inserirNoInicio(loja.estoque, criarCarroTeste(loja.proximoCodigo, semente));
        loja.proximoCodigo++;
    }

    cout << "\n" << quantidade << " carros de teste gerados.\n";
}
