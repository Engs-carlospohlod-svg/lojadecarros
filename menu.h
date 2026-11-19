#pragma once

#include <iostream>
#include "loja.h"
#include "ordenacao.h"
#include "busca.h"
#include "dados_teste.h"

using namespace std;

// ===================== MENU E OPÇÕES =====================
// Cada opção do menu é uma função pequena de responsabilidade única.

// Exibe o menu principal.
inline void exibirMenu() {
    cout << "\n==================================================";
    cout << "\n            AUTOGESTAO - LOJA DE CARROS";
    cout << "\n==================================================";
    cout << "\n 1 - Cadastrar carro            10 - Atender proximo cliente";
    cout << "\n 2 - Listar estoque             11 - Ver fila de clientes";
    cout << "\n 3 - Remover carro              12 - Listar por preco (arvore)";
    cout << "\n 4 - Editar carro               13 - Faixa de preco (arvore)";
    cout << "\n 5 - Buscar carro por codigo    14 - Buscar preco exato (arvore)";
    cout << "\n 6 - Ordenar estoque            15 - Comparar buscas";
    cout << "\n 7 - Vender carro               16 - Gerar carros de teste";
    cout << "\n 8 - Desfazer ultima acao       17 - Estatisticas";
    cout << "\n 9 - Entrar na fila de clientes  0 - Sair";
    cout << "\n";
}

// Pede um código e remove o carro.
inline void opcaoRemover(Loja& loja) {
    removerCarro(loja, lerInteiro("Codigo do carro a remover: ", 1));
}

// Pede um código e edita um campo do carro.
inline void opcaoEditar(Loja& loja) {
    NoCarro* no = buscarNo(loja.estoque, lerInteiro("Codigo do carro a editar: ", 1));

    if (no == nullptr) {
        cout << "\nCarro nao encontrado.\n";
        return;
    }

    editarCampoCarro(no->carro);
}

// Busca um carro por código (sequencial) e mostra quantas comparações foram feitas.
inline void opcaoBuscar(Loja& loja) {
    long comparacoes = 0;
    int codigo = lerInteiro("Codigo do carro: ", 1);
    NoCarro* no = buscaSequencial(loja.estoque, codigo, comparacoes);

    if (no == nullptr) {
        cout << "\nCarro nao encontrado (" << comparacoes << " comparacoes).\n";
        return;
    }

    exibirCabecalho();
    exibirCarro(no->carro);
    cout << "(encontrado com " << comparacoes << " comparacoes)\n";
}

// Pergunta o critério e ordena o estoque com Bubble Sort.
inline void opcaoOrdenar(Loja& loja) {
    cout << "\n1 - Por codigo\n2 - Por preco\n3 - Por ano";
    int escolha = lerInteiro("\nOrdenar por: ", 1, 3);
    Criterio criterio = (escolha == 1) ? maiorCodigo : (escolha == 2) ? maiorPreco : maiorAno;

    ordenarLista(loja.estoque, criterio);
    cout << "\nEstoque ordenado!\n";
    listarCarros(loja.estoque);
}

// Registra a venda de um carro informado pelo usuário.
inline void opcaoVender(Loja& loja) {
    venderCarro(loja, lerInteiro("Codigo do carro vendido: ", 1));
}

// Lista o estoque em ordem crescente de preço usando a travessia in-ordem da BST.
inline void opcaoListarPorPreco(Loja& loja) {
    reconstruirArvore(loja.indicePrecos, loja.estoque);

    if (loja.indicePrecos == nullptr) {
        cout << "\nNenhum carro cadastrado.\n";
        return;
    }

    exibirCabecalho();
    listarEmOrdem(loja.indicePrecos);
}

// Lista os carros dentro de uma faixa de preço usando a BST.
inline void opcaoFaixaPreco(Loja& loja) {
    double minimo = lerDecimal("Preco minimo: ", 0);
    double maximo = lerDecimal("Preco maximo: ", minimo);

    reconstruirArvore(loja.indicePrecos, loja.estoque);
    exibirCabecalho();
    int total = listarFaixaPreco(loja.indicePrecos, minimo, maximo);
    cout << "\n" << total << " carro(s) na faixa.\n";
}

// Busca na BST um carro com o preço exato informado.
inline void opcaoPrecoExato(Loja& loja) {
    double preco = lerDecimal("Preco exato: ", 0);

    reconstruirArvore(loja.indicePrecos, loja.estoque);
    const NoArvore* achado = buscarPrecoExato(loja.indicePrecos, preco);

    if (achado == nullptr) {
        cout << "\nNenhum carro com esse preco.\n";
        return;
    }

    exibirCabecalho();
    exibirCarro(achado->carro->carro);
}

// Gera carros de teste para a demonstração de desempenho.
inline void opcaoGerarTeste(Loja& loja) {
    gerarCarrosTeste(loja, lerInteiro("Quantos carros gerar (1-20000): ", 1, 20000));
}

// Mostra números gerais do sistema (usa funções recursivas).
inline void opcaoEstatisticas(Loja& loja) {
    int total = contarCarros(loja.estoque);
    int vendidos = contarVendidos(loja.estoque);

    reconstruirArvore(loja.indicePrecos, loja.estoque);
    cout << "\nCarros cadastrados: " << total;
    cout << "\nVendidos: " << vendidos << " | Disponiveis: " << total - vendidos;
    cout << "\nAltura da arvore de precos: " << alturaArvore(loja.indicePrecos);
    cout << "\nClientes na fila: " << loja.fila.tamanho;
    cout << "\nAcoes que podem ser desfeitas: " << tamanhoPilha(loja.historico) << "\n";
}

// Executa a opção escolhida no menu.
// Parâmetros: loja - referência à loja; opcao - número digitado.
inline void executarOpcao(Loja& loja, int opcao) {
    switch (opcao) {
        case 1: cadastrarCarro(loja); break;
        case 2: listarCarros(loja.estoque); break;
        case 3: opcaoRemover(loja); break;
        case 4: opcaoEditar(loja); break;
        case 5: opcaoBuscar(loja); break;
        case 6: opcaoOrdenar(loja); break;
        case 7: opcaoVender(loja); break;
        case 8: desfazerUltimaAcao(loja); break;
        case 9: entrarNaFila(loja); break;
        case 10: atenderProximoCliente(loja); break;
        case 11: exibirFila(loja.fila); break;
        case 12: opcaoListarPorPreco(loja); break;
        case 13: opcaoFaixaPreco(loja); break;
        case 14: opcaoPrecoExato(loja); break;
        case 15: compararBuscas(loja.estoque); break;
        case 16: opcaoGerarTeste(loja); break;
        case 17: opcaoEstatisticas(loja); break;
        case 0: cout << "\nEncerrando sistema...\n"; break;
    }
}
