// LOCADORA DE AUTOMÓVEIS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEICULOS 20

typedef struct {
    int id;
    char modelo[50];
    int ano;
    int disponivel;
    float valorDiaria;
} Veiculo;

typedef struct {
    int idVeiculo;
    char nomeCliente[50];
    int diasAluguel;
    float valorTotal;
} Aluguel;

void exibirMenu() {
    printf("\n--- LOCADORA DE AUTOMÓVEIS ---\n");
    printf("1. Cadastrar Veículo\n");
    printf("2. Listar Veículos\n");
    printf("3. Remover Veículo\n");
    printf("4. Alugar Veículo\n");
    printf("5. Sair\n");
    printf("\nEscolha uma opção: ");
}

void cadastrarVeiculo(Veiculo *veiculos, int *totalVeiculos) {
    if (*totalVeiculos >= MAX_VEICULOS) {
        printf("\nLimite máximo de veículos atingido.\n");
        return;
    }

    Veiculo novoVeiculo;
    novoVeiculo.id = *totalVeiculos + 1;

    printf("\nDigite o modelo do veículo: ");
    fgets(novoVeiculo.modelo, sizeof(novoVeiculo.modelo), stdin);
    novoVeiculo.modelo[strcspn(novoVeiculo.modelo, "\n")] = '\0';

    do {
        printf("Digite o ano do veículo (1886 a 2025): ");
        scanf("%d", &novoVeiculo.ano);
        if (novoVeiculo.ano < 1886 || novoVeiculo.ano > 2025) {
            printf("\nAno inválido. Tente novamente.");
        }
    } while (novoVeiculo.ano < 1886 || novoVeiculo.ano > 2025);

    do {
        printf("Digite o valor da diária (em reais): ");
        scanf("%f", &novoVeiculo.valorDiaria);
        if (novoVeiculo.valorDiaria <= 0) {
            printf("\nValor inválido. Tente novamente.");
        }
    } while (novoVeiculo.valorDiaria <= 0);

    novoVeiculo.disponivel = 0;

    veiculos[*totalVeiculos] = novoVeiculo;
    (*totalVeiculos)++;

    printf("\nVeículo cadastrado com sucesso!\n");
    getchar();
}

void listarVeiculos(Veiculo *veiculos, int totalVeiculos) {
    if (totalVeiculos == 0) {
        printf("\nNenhum veículo cadastrado.\n");
        return;
    }

    printf("\n--- LISTA DE VEÍCULOS ---\n");
    for (int i = 0; i < totalVeiculos; i++) {
        printf("ID: %d\n", veiculos[i].id);
        printf("Modelo: %s\n", veiculos[i].modelo);
        printf("Ano: %d\n", veiculos[i].ano);
        printf("Valor da diária: R$ %.2f\n", veiculos[i].valorDiaria);
        printf("Disponível: %s\n\n", veiculos[i].disponivel == 0 ? "Sim" : "Não");
    }
}

void removerVeiculo(Veiculo *veiculos, int *totalVeiculos) {
    int idRemover;
    int encontrado = 0;

    if (*totalVeiculos == 0) {
        printf("\nNenhum veículo cadastrado para remover.\n");
        return;
    }

    listarVeiculos(veiculos, *totalVeiculos);

    printf("Digite o ID do veículo que deseja remover: ");
    scanf("%d", &idRemover);

    for (int i = 0; i < *totalVeiculos; i++) {
        if (veiculos[i].id == idRemover) {
            encontrado = 1;

            for (int j = i; j < *totalVeiculos - 1; j++) {
                veiculos[j] = veiculos[j + 1];
            }

            (*totalVeiculos)--;

            printf("\nVeículo com ID %d removido com sucesso.\n", idRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("\nVeículo com ID %d não encontrado.\n", idRemover);
    }
    getchar();
}

void alugarVeiculo(Veiculo *veiculos, int totalVeiculos, Aluguel **alugueis, int *totalAlugueis) {
    int idVeiculo;
    listarVeiculos(veiculos, totalVeiculos);

    printf("\nDigite o ID do veículo que deseja alugar: ");
    scanf("%d", &idVeiculo);
    getchar();  

    int veiculoEncontrado = 0;
    for (int i = 0; i < totalVeiculos; i++) {
        if (veiculos[i].id == idVeiculo) {
            veiculoEncontrado = 1;

            if (veiculos[i].disponivel == 1) {
                printf("\nVeículo não está disponível para aluguel.\n");
                return;
            }

            Aluguel novoAluguel;
            novoAluguel.idVeiculo = idVeiculo;
            printf("Digite o nome do cliente: ");
            fgets(novoAluguel.nomeCliente, sizeof(novoAluguel.nomeCliente), stdin);

            printf("Digite o número de dias para o aluguel: ");
            scanf("%d", &novoAluguel.diasAluguel);
            getchar();  

            novoAluguel.valorTotal = veiculos[i].valorDiaria * novoAluguel.diasAluguel;

            *alugueis = realloc(*alugueis, (*totalAlugueis + 1) * sizeof(Aluguel));
            (*alugueis)[*totalAlugueis] = novoAluguel;
            (*totalAlugueis)++;

            veiculos[i].disponivel = 1;

            printf("\nAluguel realizado com sucesso! Valor total: R$ %.2f\n", novoAluguel.valorTotal);
            break;
        }
    }

    if (!veiculoEncontrado) {
        printf("\nVeículo não encontrado.\n");
    }
}


int main() {
    setlocale(LC_ALL, "portuguese");
    Veiculo veiculos[MAX_VEICULOS];
    Aluguel *alugueis = NULL;
    int totalVeiculos = 0;
    int totalAlugueis = 0;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarVeiculo(veiculos, &totalVeiculos);
                break;
            case 2:
                listarVeiculos(veiculos, totalVeiculos);
                break;
            case 3:
                removerVeiculo(veiculos, &totalVeiculos);
                break; 
             case 4:
                alugarVeiculo(veiculos, totalVeiculos, &alugueis, &totalAlugueis);
                break;         
            case 5:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);
}
