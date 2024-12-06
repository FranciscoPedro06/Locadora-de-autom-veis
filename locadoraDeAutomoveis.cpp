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

//globais
Veiculo veiculos[MAX_VEICULOS];
int totalVeiculos = 0;

void cadastrarVeiculo() {
    if (totalVeiculos >= MAX_VEICULOS) {
        printf("Limite máximo de veículos atingido.\n");
        return;
    }

    Veiculo novoVeiculo;
    novoVeiculo.id = totalVeiculos + 1;

    printf("Digite o modelo do veículo: ");
    fgets(novoVeiculo.modelo, sizeof(novoVeiculo.modelo), stdin);
    novoVeiculo.modelo[strcspn(novoVeiculo.modelo, "\n")] = '\0'; 
    
    
    do {
        printf("Digite o ano do veículo: ");
        scanf("%d", &novoVeiculo.ano);
        if (novoVeiculo.ano < 1886 || novoVeiculo.ano > 2024) {
            printf("Ano inválido. Tente novamente.\n");
        }
    } while (novoVeiculo.ano < 1886 || novoVeiculo.ano > 2024);


    do {
        printf("Digite o valor da diária (em reais): ");
        scanf("%f", &novoVeiculo.valorDiaria);
        if (novoVeiculo.valorDiaria <= 0) {
            printf("Valor inválido. Tente novamente.\n");
        }
    } while (novoVeiculo.valorDiaria <= 0);

    novoVeiculo.disponivel = 0;

    veiculos[totalVeiculos] = novoVeiculo;
    totalVeiculos++;

    printf("Veículo cadastrado com sucesso!\n");
}

void listarVeiculos() {
    if (totalVeiculos == 0) {
        printf("Nenhum veículo cadastrado.\n");
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


int main() {
    setlocale(LC_ALL, "portuguese");
    int opcao;

    do {
        printf("\n--- LOCADORA DE AUTOMÓVEIS ---\n");
        printf("1. Cadastrar Veículo\n");
        printf("2. Listar Veículos\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarVeiculo();
                break;
            case 2:
                listarVeiculos();
                break;
            case 3:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 3);
}
