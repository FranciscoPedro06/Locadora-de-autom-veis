#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VEICULOS 100
#define MAX_CLIENTES 100
#define MAX_ALUGUEIS 100
#define MAX_FUNCIONARIOS 10

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

typedef struct {
    int id;
    char nome[50];
    char usuario[50];
    char senha[50];
} Funcionario;

int contadorVeiculo = 1; 
int contadorCliente = 1;
int contadorFuncionario = 1;
Funcionario funcionarios[MAX_FUNCIONARIOS];

void inicializarFuncionarios(Funcionario funcionarios[], int *totalFuncionarios) {
    // Funcionários pré-cadastrados
    funcionarios[0].id = 0;
    strcpy(funcionarios[0].nome, "Admin");
    strcpy(funcionarios[0].usuario, "admin");
    strcpy(funcionarios[0].senha, "senha123");
    
    funcionarios[1].id = 1;
    strcpy(funcionarios[1].nome, "Funcionario 1");
    strcpy(funcionarios[1].usuario, "func1");
    strcpy(funcionarios[1].senha, "senha456");

    *totalFuncionarios = 2; // Inicializa com 2 funcionários
}

int loginFuncionario(Funcionario funcionarios[], int totalFuncionarios) {
    char usuario[50], senha[50];
    
    printf("\n--- LOGIN FUNCIONÁRIO ---\n");
    printf("Usuário: ");
    fgets(usuario, sizeof(usuario), stdin);
    usuario[strcspn(usuario, "\n")] = '\0';

    printf("Senha: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0';

    for (int i = 0; i < totalFuncionarios; i++) {
        if (strcmp(funcionarios[i].usuario, usuario) == 0 && strcmp(funcionarios[i].senha, senha) == 0) {
            printf("Login bem-sucedido!!\n\n");
            return 1; 
        }
    }
    return 0; 
}


void exibirMenuFuncionario() {
    printf("\n--- MENU FUNCIONÁRIO ---\n");
    printf("1. Cadastrar veículo\n");
    printf("2. Listar veículos\n");
    printf("3. Remover veículo\n");
    printf("4. Cadastrar cliente\n");
    printf("5. Listar clientes\n");
    printf("6. Sair\n");
    printf("\nEscolha uma opção: ");
}

void exibirMenuCliente() {
    printf("\n--- MENU CLIENTE ---\n");
    printf("1. Listar veículos\n");
    printf("2. Alugar veículo\n");
    printf("3. Sair\n");
    printf("\nEscolha uma opção: ");
}

int loginCliente(Cliente *clientes, int totalClientes) {
    char cpf[15];

    printf("\n--- LOGIN CLIENTE ---\n");
    printf("Digite seu CPF (somente números): ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            printf("Login bem-sucedido!!\n\n");
            return 1;
        }
    }
    return 0;
}

void cadastrarVeiculo(Veiculo *veiculos, int *totalVeiculos) {
    if (*totalVeiculos >= MAX_VEICULOS) {
        printf("\nLimite máximo de veículos atingido.\n");
        return;
    }

    Veiculo novoVeiculo;
    novoVeiculo.id = contadorVeiculo++;

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

void alugarVeiculo(Veiculo *veiculos, int totalVeiculos, Aluguel *alugueis, int *totalAlugueis) {
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

            // Verifica se há espaço para mais aluguéis
            if (*totalAlugueis >= MAX_ALUGUEIS) {
                printf("Limite de aluguéis atingido.\n");
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

            alugueis[*totalAlugueis] = novoAluguel;  // Adiciona o novo aluguel no array fixo
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
    novoCliente.id = contadorCliente++;

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

void salvarVeiculos(Veiculo *veiculos, int totalVeiculos) {
    FILE *arquivo = fopen("veiculos.txt", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar veículos.\n");
        return;
    }
    fwrite(&totalVeiculos, sizeof(int), 1, arquivo); // Salva a quantidade de veículos
    fwrite(veiculos, sizeof(Veiculo), totalVeiculos, arquivo); // Salva os veículos
    fclose(arquivo);
    printf("Veículos salvos com sucesso!\n");
}

int carregarVeiculos(Veiculo *veiculos, int capacidade) {
    FILE *arquivo = fopen("veiculos.txt", "rb");  // Usando "rb" para leitura binária
    if (arquivo == NULL) {
        printf("Nenhum dado de veículos encontrado.\n");
        return 0;
    }

    int totalVeiculos;
    fread(&totalVeiculos, sizeof(int), 1, arquivo);  // Lê a quantidade de veículos
    if (totalVeiculos == 0) {
        printf("Não há veículos cadastrados.\n");
        fclose(arquivo);
        return 0;
    }

    if (totalVeiculos > capacidade) {
        printf("Capacidade insuficiente para carregar veículos. Temos %d veículos, mas a capacidade é %d.\n", totalVeiculos, capacidade);
        fclose(arquivo);
        return 0;
    }

    fread(veiculos, sizeof(Veiculo), totalVeiculos, arquivo);  // Lê os veículos
    fclose(arquivo);
    printf("Veículos carregados com sucesso!\n");
    return totalVeiculos;
}

void salvarAlugueis(Aluguel *alugueis, int totalAlugueis) {
    FILE *arquivo = fopen("alugueis.txt", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar aluguéis.\n");
        return;
    }
    fwrite(&totalAlugueis, sizeof(int), 1, arquivo); // Salva a quantidade de aluguéis
    fwrite(alugueis, sizeof(Aluguel), totalAlugueis, arquivo); // Salva os aluguéis
    fclose(arquivo);
    printf("Aluguéis salvos com sucesso!\n");
}

int carregarAlugueis(Aluguel *alugueis, int capacidade) {
    FILE *arquivo = fopen("alugueis.txt", "rb");  // Usando "rb" para leitura binária
    if (arquivo == NULL) {
        printf("Nenhum dado de aluguéis encontrado.\n");
        return 0;
    }

    int totalAlugueis;
    fread(&totalAlugueis, sizeof(int), 1, arquivo);  // Lê a quantidade de aluguéis
    if (totalAlugueis == 0) {
        printf("Não há aluguéis cadastrados.\n");
        fclose(arquivo);
        return 0;
    }

    if (totalAlugueis > capacidade) {
        printf("Capacidade insuficiente para carregar aluguéis. Temos %d aluguéis, mas a capacidade é %d.\n", totalAlugueis, capacidade);
        fclose(arquivo);
        return 0;
    }

    fread(alugueis, sizeof(Aluguel), totalAlugueis, arquivo);  // Lê os aluguéis
    fclose(arquivo);
    printf("Aluguéis carregados com sucesso!\n");
    return totalAlugueis;
}

void salvarClientes(Cliente *clientes, int totalClientes) {
    FILE *arquivo = fopen("clientes.txt", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar clientes.\n");
        return;
    }
    fwrite(&totalClientes, sizeof(int), 1, arquivo); // Salva a quantidade de clientes
    fwrite(clientes, sizeof(Cliente), totalClientes, arquivo); // Salva os clientes
    fclose(arquivo);
    printf("Clientes salvos com sucesso!\n");
}

int carregarClientes(Cliente *clientes, int capacidade) {
    FILE *arquivo = fopen("clientes.txt", "rb"); // Abrindo em modo binário para leitura
    if (arquivo == NULL) {
        printf("Nenhum dado de clientes encontrado.\n");
        return 0;
    }

    int totalClientes;
    fread(&totalClientes, sizeof(int), 1, arquivo); // Lê a quantidade de clientes
    if (totalClientes == 0) {
        printf("Não há clientes cadastrados.\n");
        fclose(arquivo);
        return 0;
    }

    if (totalClientes > capacidade) {
        printf("Capacidade insuficiente para carregar clientes. Temos %d clientes, mas a capacidade é %d.\n", totalClientes, capacidade);
        fclose(arquivo);
        return 0;
    }

    fread(clientes, sizeof(Cliente), totalClientes, arquivo); // Lê os clientes
    fclose(arquivo);
    printf("Clientes carregados com sucesso!\n");
    return totalClientes;
}

int main() {
    setlocale(LC_ALL, "portuguese");
    
    Veiculo veiculos[MAX_VEICULOS];
    Aluguel alugueis[MAX_ALUGUEIS];
    Cliente clientes[MAX_CLIENTES];
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int totalVeiculos = 0;
    int totalAlugueis = 0;
    int totalClientes = 0;
    int totalFuncionarios = 0;
    int opcao, tipoLogin;

    // Carregar dados existentes
    totalVeiculos = carregarVeiculos(veiculos, MAX_VEICULOS);
    totalAlugueis = carregarAlugueis(alugueis, MAX_ALUGUEIS);
    totalClientes = carregarClientes(clientes, MAX_CLIENTES);

    inicializarFuncionarios(funcionarios, &totalFuncionarios);

    do {
        printf("\nEscolha o tipo de login:\n");
        printf("1. Funcionário\n");
        printf("2. Cliente\n");
        printf("3. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &tipoLogin);
        getchar();

        if (tipoLogin == 1) {
            if (loginFuncionario(funcionarios, totalFuncionarios)) {
                do {
                    exibirMenuFuncionario();
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
                            cadastrarCliente(clientes, &totalClientes);
                            break;
                        case 5:
                            listarClientes(clientes, totalClientes);
                            break;
                        case 6:
                            printf("Encerrando o sistema...\n");
                            break;
                        default:
                            printf("Opção inválida! Tente novamente.\n");
                    }
                } while (opcao != 6);
            } else {
                printf("Login falhou. Usuário ou senha inválidos.\n");
            }
        } else if (tipoLogin == 2) {
            if (loginCliente(clientes, totalClientes)) {
                do {
                    exibirMenuCliente();
                    scanf("%d", &opcao);
                    getchar();

                    switch (opcao) {
                        case 1:
                            listarVeiculos(veiculos, totalVeiculos);
                            break;
                        case 2:
                            alugarVeiculo(veiculos, totalVeiculos, alugueis, &totalAlugueis);
                            break;
                        case 3:
                            printf("Saindo...\n");
                            break;
                        default:
                            printf("Opção inválida! Tente novamente.\n");
                    }
                } while (opcao != 3);
            } else {
                printf("Login falhou. CPF não encontrado.\n");
            }
        } else if (tipoLogin != 3) {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (tipoLogin != 3);

    // Salvar dados
    salvarVeiculos(veiculos, totalVeiculos);
    salvarAlugueis(alugueis, totalAlugueis);
    salvarClientes(clientes, totalClientes);
    return 0;
}
