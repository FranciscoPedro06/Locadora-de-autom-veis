// LOCADORA DE AUTOMÓVEIS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VEICULOS 100
#define MAX_CLIENTES 100

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

typedef struct {
    int id;
    char nome[50];
    char cpf[15];
    int idade;
    char telefone[15];
    char email[50];
    char endereco[200];
}Cliente;

void exibirMenu() {
    printf("\n--- LOCADORA DE AUTOMÓVEIS ---\n");
    printf("1. Cadastrar veículo\n");
    printf("2. Listar veículos\n");
    printf("3. Remover veículo\n");
    printf("4. Alugar veículo\n");
    printf("5. Cadastrar cliente\n");
    printf("6. Listar clientes\n");
    printf("7. Sair\n");
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
            printf("Ano inválido. Tente novamente.\n");
        }
    } while (novoVeiculo.ano < 1886 || novoVeiculo.ano > 2025);

    do {
        printf("Digite o valor da diária (em reais): ");
        scanf("%f", &novoVeiculo.valorDiaria);
        if (novoVeiculo.valorDiaria <= 0) {
            printf("Valor inválido. Tente novamente.\n");
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

int validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) return 0;
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) return 0;
    }
    return 1;
}

int validarTelefone(const char *telefone) {
    if (strlen(telefone) < 10 || strlen(telefone) > 11) return 0;
    for (int i = 0; i < strlen(telefone); i++) {
        if (!isdigit(telefone[i])) return 0;
    }
    return 1;
}

int validarEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return (at && dot && at < dot);
}

void cadastrarCliente(Cliente *clientes, int *totalClientes) {
    if (*totalClientes >= MAX_CLIENTES) {
        printf("\nLimite máximo de clientes atingido.\n");
        return;
    }

    Cliente novoCliente;
    novoCliente.id = *totalClientes + 1;

    printf("\n--- CADASTRO DE CLIENTE ---\n");

    printf("Nome completo: ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

    do {
        printf("CPF (somente números): ");
        fgets(novoCliente.cpf, sizeof(novoCliente.cpf), stdin);
        novoCliente.cpf[strcspn(novoCliente.cpf, "\n")] = '\0';
        if (!validarCPF(novoCliente.cpf)) {
            printf("Digite um CPF válido (11 números).\n");
        }
    } while (!validarCPF(novoCliente.cpf));

    do {
        printf("Idade: ");
        scanf("%d", &novoCliente.idade);
        getchar();  
        if (novoCliente.idade < 18) {
            printf("Idade mínima é 18 anos. Tente novamente.\n");
        }
    } while (novoCliente.idade < 18);

    do {
        printf("Telefone: ");
        fgets(novoCliente.telefone, sizeof(novoCliente.telefone), stdin);
        novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0';
        if (!validarTelefone(novoCliente.telefone)) {
            printf("Digite um telefone válido (10 a 11 números).\n");
        }
    } while (!validarTelefone(novoCliente.telefone));

    do {
        printf("Email: ");
        fgets(novoCliente.email, sizeof(novoCliente.email), stdin);
        novoCliente.email[strcspn(novoCliente.email, "\n")] = '\0';
        if (!validarEmail(novoCliente.email)) {
            printf("Digite um email válido.\n");
        }
    } while (!validarEmail(novoCliente.email));

    printf("Endereço: ");
    fgets(novoCliente.endereco, sizeof(novoCliente.endereco), stdin);
 novoCliente.endereco[strcspn(novoCliente.endereco, "\n")] = '\0';

    clientes[*totalClientes] = novoCliente;
    (*totalClientes)++;

    printf("\nCliente '%s' cadastrado com sucesso! ID: %d\n", novoCliente.nome, novoCliente.id);
}

void listarClientes(Cliente *clientes, int totalClientes) {
    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    printf("\n--- LISTA DE CLIENTES ---\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("ID: %d\n", clientes[i].id);
        printf("Nome completo: %s\n", clientes[i].nome);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Idade: %d\n", clientes[i].idade);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Email: %s\n", clientes[i].email);
        printf("Endereço: %s\n", clientes[i].endereco);
        printf("\n----------------------\n");
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");
    Veiculo veiculos[MAX_VEICULOS];
    Aluguel *alugueis = NULL;
    Cliente clientes[MAX_CLIENTES];
    int totalVeiculos = 0;
    int totalAlugueis = 0;
    int totalClientes = 0;
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
                cadastrarCliente(clientes, &totalClientes);
                break;
            case 6:
                listarClientes(clientes, totalClientes);
                break;                 
            case 7:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);
}
