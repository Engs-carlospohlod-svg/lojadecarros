#include <iostream>
#include "lista_carros.h"

using namespace std;

// Exibe o menu e controla as funcionalidades do sistema.
int main() {
    NoCarro* lista = nullptr;
    int opcao;
    int proximoCodigo = 1;

    do {
        cout << "\n==============================";
        cout << "\n     AUTOGESTAO - CARROS";
        cout << "\n==============================";
        cout << "\n1 - Cadastrar carro";
cout << "\n2 - Listar carros";
cout << "\n3 - Remover carro"
cout << "\n0 - Sair";
        cout << "\nEscolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarCarro(lista, proximoCodigo);
                proximoCodigo++;
                break;

            case 2:
                listarCarros(lista);
                break;
case 3: {
    int codigo;

    cout << "\nDigite o codigo do carro que deseja remover: ";
    cin >> codigo;

    removerCarro(lista, codigo);
    break;
}
            case 0:
                cout << "\nEncerrando sistema...\n";
                break;

            default:
                cout << "\nOpcao invalida!\n";
        }

    } while (opcao != 0);

    liberarLista(lista);

    return 0;
}
