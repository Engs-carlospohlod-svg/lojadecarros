#include <iostream>
#include "menu.h"

using namespace std;

// Ponto de entrada: repete o menu até o usuário escolher 0 e então libera a memória.
int main() {
    Loja loja;
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha: ", 0, 17);
        executarOpcao(loja, opcao);
    } while (opcao != 0);

    liberarLoja(loja);  // todo new tem seu delete
    return 0;
}
