#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <climits>

using namespace std;

// Funções de leitura segura do teclado. Todas leem a linha inteira com getline,
// o que evita o problema clássico do cin (lixo no buffer após um número).
// Em caso de fim de entrada (EOF) retornam um valor padrão para não travar.

// Lê uma linha de texto não vazia.
// Parâmetro: mensagem - texto exibido ao usuário (referência const: só leitura).
// Retorno: texto digitado, ou "" se a entrada acabou (EOF).
inline string lerTexto(const string& mensagem) {
    string linha;

    do {
        cout << mensagem;
        if (!getline(cin, linha)) {
            return "";
        }
    } while (linha.empty());

    return linha;
}

// Lê um inteiro dentro de um intervalo, repetindo até o valor ser válido.
// Parâmetros: mensagem; minimo e maximo (parâmetros default = sem limite).
// Retorno: inteiro válido (ou o valor mais próximo de 0 dentro do intervalo no EOF).
inline int lerInteiro(const string& mensagem, int minimo = INT_MIN, int maximo = INT_MAX) {
    while (true) {
        string texto = lerTexto(mensagem);

        if (texto.empty()) {
            return min(max(0, minimo), maximo);  // EOF
        }

        try {
            size_t usados = 0;
            int valor = stoi(texto, &usados);

            if (usados == texto.size() && valor >= minimo && valor <= maximo) {
                return valor;
            }
        } catch (const exception&) {
            // texto não numérico ou grande demais: cai na mensagem abaixo
        }

        cout << "Valor invalido. Tente novamente.\n";
    }
}

// Lê um número decimal (aceita vírgula ou ponto) maior ou igual a minimo.
// Parâmetros: mensagem; minimo (default 0).
// Retorno: valor decimal válido (ou minimo no EOF).
inline double lerDecimal(const string& mensagem, double minimo = 0.0) {
    while (true) {
        string texto = lerTexto(mensagem);

        if (texto.empty()) {
            return minimo;  // EOF
        }

        replace(texto.begin(), texto.end(), ',', '.');

        try {
            size_t usados = 0;
            double valor = stod(texto, &usados);

            if (usados == texto.size() && valor >= minimo) {
                return valor;
            }
        } catch (const exception&) {
            // texto inválido: cai na mensagem abaixo
        }

        cout << "Valor invalido. Tente novamente.\n";
    }
}

// Faz uma pergunta de sim/não.
// Parâmetro: mensagem - pergunta exibida (o sufixo " (s/n): " é acrescentado).
// Retorno: true se o usuário respondeu 's' ou 'S'.
inline bool lerSimNao(const string& mensagem) {
    string resposta = lerTexto(mensagem + " (s/n): ");
    return resposta[0] == 's' || resposta[0] == 'S';
}
