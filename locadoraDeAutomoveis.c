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
    char cpfCliente[15];
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
    funcionarios[0].id = 0;
    strcpy(funcionarios[0].nome, "Admin");
    strcpy(funcionarios[0].usuario, "admin");
    strcpy(funcionarios[0].senha, "senha123");
    
    funcionarios[1].id = 1;
    strcpy(funcionarios[1].nome, "Funcionario 1");
    strcpy(funcionarios[1].usuario, "func1");
    strcpy(funcionarios[1].senha, "senha456");

    *totalFuncionarios = 2; 
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
    printf("\n=================================================\n");
    printf("|          MENU FUNCIONÁRIO - LOCAPRIME        |\n");
    printf("=================================================\n");
    printf("|  1. Cadastrar veículo                        |\n");
    printf("|  2. Listar veículos                          |\n");
    printf("|  3. Remover veículo                          |\n");
    printf("|  4. Cadastrar cliente                         |\n");
    printf("|  5. Listar clientes                           |\n");
    printf("|  6. Listar aluguéis                          |\n");
    printf("|  7. Remover locação                         |\n");
    printf("|  8. Finalizar locação                       |\n");
    printf("|  9. Buscar locações por veículo            |\n");
    printf("| 10. Sair                                      |\n");
    printf("=================================================\n");
    printf("Escolha uma opção: ");
}

void exibirMenuCliente() {
    printf("\n=================================================\n");
    printf("|            MENU CLIENTE - LOCAPRIME           |\n");
    printf("=================================================\n");
    printf("|  1. Listar veículos                          |\n");
    printf("|  2. Alugar veículo                           |\n");
    printf("|  3. Devolver veículo                         |\n");
    printf("|  4. Histórico de aluguéis                   |\n");
    printf("|  5. Simular locação                         |\n");
    printf("|  6. Sair                                      |\n");
    printf("=================================================\n");
    printf("Escolha uma opção: ");
}

const char* loginCliente(Cliente *clientes, int totalClientes) {
    char cpf[15];

    printf("\n--- LOGIN CLIENTE ---\n");
    printf("Digite seu CPF (somente números): ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            printf("Login bem-sucedido!!\n\n");
            return clientes[i].cpf; 
        }
    }
    return NULL;
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


            if (*totalAlugueis >= MAX_ALUGUEIS) {
                printf("Limite de aluguéis atingido.\n");
                return;
            }

            Aluguel novoAluguel;
            novoAluguel.idVeiculo = idVeiculo;
            printf("Digite o nome do cliente: ");
            fgets(novoAluguel.nomeCliente, sizeof(novoAluguel.nomeCliente), stdin);

            printf("Digite o CPF do cliente: ");
            fgets(novoAluguel.cpfCliente, sizeof(novoAluguel.cpfCliente), stdin);
            novoAluguel.cpfCliente[strcspn(novoAluguel.cpfCliente, "\n")] = '\0';

            printf("Digite o número de dias para o aluguel: ");
            scanf("%d", &novoAluguel.diasAluguel);
            getchar();  

            novoAluguel.valorTotal = veiculos[i].valorDiaria * novoAluguel.diasAluguel;

            alugueis[*totalAlugueis] = novoAluguel;  
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

void listarAlugueis(Aluguel *alugueis, int totalAlugueis, Veiculo *veiculos, int totalVeiculos) {
    if (totalAlugueis == 0) {
        printf("\nNenhum aluguel registrado.\n");
        return;
    }

    printf("\n--- LISTA DE ALUGUÉIS ---\n");
    for (int i = 0; i < totalAlugueis; i++) {
        printf("Aluguel #%d:\n", i + 1);
        printf("Nome do Cliente: %s\n", alugueis[i].nomeCliente);
        printf("ID do Veículo: %d\n", alugueis[i].idVeiculo);


        int veiculoEncontrado = 0;
        for (int j = 0; j < totalVeiculos; j++) {
            if (veiculos[j].id == alugueis[i].idVeiculo) {
                printf("Modelo do Veículo: %s\n", veiculos[j].modelo);
                printf("Ano do Veículo: %d\n", veiculos[j].ano);
                printf("Valor da Diária: R$ %.2f\n", veiculos[j].valorDiaria);
                veiculoEncontrado = 1;
                break;
            }
        }
        if (!veiculoEncontrado) {
            printf("Informações do veículo não encontradas.\n");
        }

        printf("Dias Alugados: %d\n", alugueis[i].diasAluguel);
        printf("Valor Total: R$ %.2f\n", alugueis[i].valorTotal);
        printf("\n----------------------\n");
    }
}

void removerLocacao(Aluguel *alugueis, int *totalAlugueis, Veiculo *veiculos, int totalVeiculos) {
    if (*totalAlugueis == 0) {
        printf("\nNenhuma locação registrada para remover.\n");
        return;
    }

    printf("\n--- LISTA DE LOCAÇÕES ---\n");
    for (int i = 0; i < *totalAlugueis; i++) {
        printf("ID Veículo: %d\n", alugueis[i].idVeiculo);
        printf("Nome Cliente: %s\n", alugueis[i].nomeCliente);
        printf("Dias de Aluguel: %d\n", alugueis[i].diasAluguel);
        printf("Valor Total: R$ %.2f\n", alugueis[i].valorTotal);
        printf("------------------------\n");
    }

    int idVeiculoRemover;
    printf("Digite o ID do veículo associado à locação que deseja remover: ");
    scanf("%d", &idVeiculoRemover);
    getchar();

    int encontrado = 0;

    for (int i = 0; i < *totalAlugueis; i++) {
        if (alugueis[i].idVeiculo == idVeiculoRemover) {
            encontrado = 1;

            for (int j = 0; j < totalVeiculos; j++) {
                if (veiculos[j].id == idVeiculoRemover) {
                    veiculos[j].disponivel = 0; 
                    break;
                }
            }

            for (int j = i; j < *totalAlugueis - 1; j++) {
                alugueis[j] = alugueis[j + 1];
            }

            (*totalAlugueis)--;

            printf("\nLocação do veículo com ID %d removida com sucesso.\n", idVeiculoRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("\nLocação com o ID do veículo %d não encontrada.\n", idVeiculoRemover);
    }
}

void finalizarLocacao(Aluguel *alugueis, int *totalAlugueis, Veiculo *veiculos, int totalVeiculos) {
    if (*totalAlugueis == 0) {
        printf("\nNenhuma locação registrada para finalizar.\n");
        return;
    }

    printf("\n--- LISTA DE LOCAÇÕES ATIVAS ---\n");
    for (int i = 0; i < *totalAlugueis; i++) {
        printf("ID Veículo: %d\n", alugueis[i].idVeiculo);
        printf("Nome Cliente: %s\n", alugueis[i].nomeCliente);
        printf("Dias de Aluguel: %d\n", alugueis[i].diasAluguel);
        printf("Valor Total: R$ %.2f\n", alugueis[i].valorTotal);
        printf("------------------------\n");
    }

    char cpfCliente[15];
    int idVeiculoFinalizar;
    
    printf("Digite o CPF do cliente associado à locação que deseja finalizar: ");
    fgets(cpfCliente, sizeof(cpfCliente), stdin);
    cpfCliente[strcspn(cpfCliente, "\n")] = '\0'; 

    printf("Digite o ID do veículo associado à locação que deseja finalizar: ");
    scanf("%d", &idVeiculoFinalizar);
    getchar();

    int encontrado = 0;

    for (int i = 0; i < *totalAlugueis; i++) {
        
        if (alugueis[i].idVeiculo == idVeiculoFinalizar && strcmp(alugueis[i].cpfCliente, cpfCliente) == 0) {
            encontrado = 1;

           
            for (int j = 0; j < totalVeiculos; j++) {
                if (veiculos[j].id == idVeiculoFinalizar) {
                    veiculos[j].disponivel = 0; 
                    break;
                }
            }

            for (int j = i; j < *totalAlugueis - 1; j++) {
                alugueis[j] = alugueis[j + 1];
            }

            (*totalAlugueis)--;

            printf("\nLocação do veículo com ID %d finalizada com sucesso.\n", idVeiculoFinalizar);
            break;
        }
    }

    if (!encontrado) {
        printf("\nLocação com o ID do veículo %d e CPF %s não encontrada.\n", idVeiculoFinalizar, cpfCliente);
    }
}

void devolverVeiculo(Aluguel *alugueis, int *totalAlugueis, Veiculo *veiculos, int totalVeiculos, const char *cpfCliente) {
    if (*totalAlugueis == 0) {
        printf("\nNenhuma locação registrada para devolver.\n");
        return;
    }

    printf("\n--- LISTA DE LOCAÇÕES ATIVAS ---\n");
    int encontrouLocacao = 0;
    for (int i = 0; i < *totalAlugueis; i++) {
        if (strcmp(alugueis[i].cpfCliente, cpfCliente) == 0) { 
            printf("ID Veículo: %d\n", alugueis[i].idVeiculo);
            printf("Nome Cliente: %s\n", alugueis[i].nomeCliente);
            printf("Dias de Aluguel: %d\n", alugueis[i].diasAluguel);
            printf("Valor Total: R$ %.2f\n", alugueis[i].valorTotal);
            printf("------------------------\n");
            encontrouLocacao = 1;
        }
    }

    if (!encontrouLocacao) {
        printf("Nenhuma locação ativa encontrada para o cliente.\n");
        return;
    }

    int idVeiculoDevolver;
    printf("Digite o ID do veículo que deseja devolver: ");
    scanf("%d", &idVeiculoDevolver);
    getchar();

    int encontrado = 0;

    for (int i = 0; i < *totalAlugueis; i++) {
        if (alugueis[i].idVeiculo == idVeiculoDevolver && strcmp(alugueis[i].cpfCliente, cpfCliente) == 0) {
            encontrado = 1;

            for (int j = 0; j < totalVeiculos; j++) {
                if (veiculos[j].id == idVeiculoDevolver) {
                    veiculos[j].disponivel = 0; 
                    break;
                }
            }
           
            for (int j = i; j < *totalAlugueis - 1; j++) {
                alugueis[j] = alugueis[j + 1];
            }

            (*totalAlugueis)--;

            printf("\nVeículo com ID %d devolvido com sucesso.\n", idVeiculoDevolver);
            break;
        }
    }

    if (!encontrado) {
        printf("\nLocação com o ID do veículo %d não encontrada ou não pertence ao cliente.\n", idVeiculoDevolver);
    }
}

void listarAlugueisPorCliente(Aluguel *alugueis, int totalAlugueis, Veiculo *veiculos, int totalVeiculos, const char *cpfCliente) {
    if (totalAlugueis == 0) {
        printf("\nNenhum aluguel registrado.\n");
        return;
    }

    printf("\n--- LISTA DE ALUGUÉIS ---\n");
    for (int i = 0; i < totalAlugueis; i++) {
        if (strcmp(alugueis[i].cpfCliente, cpfCliente) == 0) { 
            printf("Aluguel #%d:\n", i + 1);
            printf("Nome do Cliente: %s\n", alugueis[i].nomeCliente);
            printf("ID do Veículo: %d\n", alugueis[i].idVeiculo);

            int veiculoEncontrado = 0;
            for (int j = 0; j < totalVeiculos; j++) {
                if (veiculos[j].id == alugueis[i].idVeiculo) {
                    printf("Modelo do Veículo: %s\n", veiculos[j].modelo);
                    printf("Ano do Veículo: %d\n", veiculos[j].ano);
                    printf("Valor da Diária: R$ %.2f\n", veiculos[j].valorDiaria);
                    veiculoEncontrado = 1;
                    break;
                }
            }
            if (!veiculoEncontrado) {
                printf("Informações do veículo não encontradas.\n");
            }

            printf("Dias Alugados: %d\n", alugueis[i].diasAluguel);
            printf("Valor Total: R$ %.2f\n", alugueis[i].valorTotal);
            printf("\n----------------------\n");
        }
    }
}

void listarAlugueisPorVeiculo(Aluguel *alugueis, int totalAlugueis, Veiculo *veiculos, int totalVeiculos, int idVeiculo) {
    if (totalAlugueis == 0) {
        printf("\nNenhum aluguel registrado.\n");
        return;
    }

    printf("\n--- LISTA DE ALUGUÉIS PARA O VEÍCULO ID %d ---\n", idVeiculo);
    int encontrouAluguel = 0;

    for (int i = 0; i < totalAlugueis; i++) {
        if (alugueis[i].idVeiculo == idVeiculo) { 
            encontrouAluguel = 1;
            printf("Aluguel #%d:\n", i + 1);
            printf("Nome do Cliente: %s\n", alugueis[i].nomeCliente);
            printf("CPF do Cliente: %s\n", alugueis[i].cpfCliente);
            printf("Dias Alugados: %d\n", alugueis[i].diasAluguel);
            printf("Valor Total: R$ %.2f\n", alugueis[i].valorTotal);
            printf("------------------------\n");
        }
    }

    if (!encontrouAluguel) {
        printf("Nenhuma locação encontrada para o veículo ID %d.\n", idVeiculo);
    }
}

void simularLocacaoCliente(Veiculo *veiculos, int totalVeiculos) {
    int idVeiculo;
    int diasAluguel;

    listarVeiculos(veiculos, totalVeiculos);

    printf("\n--- SIMULAÇÃO DE LOCAÇÃO ---\n");
    printf("Digite o ID do veículo que deseja simular: ");
    scanf("%d", &idVeiculo);
    getchar();

    Veiculo *veiculoEncontrado = NULL;
    for (int i = 0; i < totalVeiculos; i++) {
        if (veiculos[i].id == idVeiculo) {
            veiculoEncontrado = &veiculos[i];
            break;
        }
    }

    if (veiculoEncontrado == NULL) {
        printf("Veículo com ID %d não encontrado.\n", idVeiculo);
        return;
    }

    printf("Digite o número de dias para a locação: ");
    scanf("%d", &diasAluguel);
    getchar();

    float valorTotal = veiculoEncontrado->valorDiaria * diasAluguel;

    printf("\n--- SIMULAÇÃO DE LOCAÇÃO ---\n");
    printf("Modelo do Veículo: %s\n", veiculoEncontrado->modelo);
    printf("Valor da Diária: R$ %.2f\n", veiculoEncontrado->valorDiaria);
    printf("Dias de Aluguel: %d\n", diasAluguel);
    printf("Valor Total: R$ %.2f\n", valorTotal);
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
    fwrite(&totalVeiculos, sizeof(int), 1, arquivo); 
    fwrite(veiculos, sizeof(Veiculo), totalVeiculos, arquivo); 
    fclose(arquivo);
    printf("Veículos salvos com sucesso!\n");
}

int carregarVeiculos(Veiculo *veiculos, int capacidade) {
    FILE *arquivo = fopen("veiculos.txt", "rb");  
    if (arquivo == NULL) {
        printf("Nenhum dado de veículos encontrado.\n");
        return 0;
    }

    int totalVeiculos;
    fread(&totalVeiculos, sizeof(int), 1, arquivo);
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

    fread(veiculos, sizeof(Veiculo), totalVeiculos, arquivo);  
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
    fwrite(&totalAlugueis, sizeof(int), 1, arquivo); 
    fwrite(alugueis, sizeof(Aluguel), totalAlugueis, arquivo); 
    fclose(arquivo);
    printf("Aluguéis salvos com sucesso!\n");
}

int carregarAlugueis(Aluguel *alugueis, int capacidade) {
    FILE *arquivo = fopen("alugueis.txt", "rb");  
    if (arquivo == NULL) {
        printf("Nenhum dado de aluguéis encontrado.\n");
        return 0;
    }

    int totalAlugueis;
    fread(&totalAlugueis, sizeof(int), 1, arquivo); 
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

    fread(alugueis, sizeof(Aluguel), totalAlugueis, arquivo); 
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
    fwrite(&totalClientes, sizeof(int), 1, arquivo); 
    fwrite(clientes, sizeof(Cliente), totalClientes, arquivo); 
    fclose(arquivo);
    printf("Clientes salvos com sucesso!\n");
}

int carregarClientes(Cliente *clientes, int capacidade) {
    FILE *arquivo = fopen("clientes.txt", "rb"); 
    if (arquivo == NULL) {
        printf("Nenhum dado de clientes encontrado.\n");
        return 0;
    }

    int totalClientes;
    fread(&totalClientes, sizeof(int), 1, arquivo); 
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

    fread(clientes, sizeof(Cliente), totalClientes, arquivo);
    fclose(arquivo);
    printf("Clientes carregados com sucesso!\n");
    return totalClientes;
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    
    Veiculo veiculos[MAX_VEICULOS];
    Aluguel alugueis[MAX_ALUGUEIS];
    Cliente clientes[MAX_CLIENTES];
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int totalVeiculos = 0;
    int totalAlugueis = 0;
    int totalClientes = 0;
    int totalFuncionarios = 0;
    int opcao, tipoLogin, opcao2;
    int idVeiculo;

    
    totalVeiculos = carregarVeiculos(veiculos, MAX_VEICULOS);
    totalAlugueis = carregarAlugueis(alugueis, MAX_ALUGUEIS);
    totalClientes = carregarClientes(clientes, MAX_CLIENTES);

    inicializarFuncionarios(funcionarios, &totalFuncionarios);

    do {
        system("cls");
        printf("\n=================================================\n");
        printf("|                LOGIN - LOCAPRIME              |\n");
        printf("=================================================\n");
        printf("|  1. Funcionário                              |\n");
        printf("|  2. Cliente                                   |\n");
        printf("|  3. Cadastrar Cliente                         |\n");
        printf("|  4. Sair                                      |\n");
        printf("=================================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &tipoLogin);
        getchar();

        if (tipoLogin == 1) {
            if (loginFuncionario(funcionarios, totalFuncionarios)) {
                system("cls");
                do {
                    exibirMenuFuncionario();
                    scanf("%d", &opcao);
                    getchar();

                    system("cls"); 
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
                            listarAlugueis(alugueis, totalAlugueis, veiculos, totalVeiculos);
                            break;
                        case 7:
                            removerLocacao(alugueis, &totalAlugueis, veiculos, totalVeiculos);
                            break;
                        case 8:
                            finalizarLocacao(alugueis, &totalAlugueis, veiculos, totalVeiculos);
                            break;
                        case 9: { 
                            printf("Digite o ID do veículo que deseja buscar: ");
                            scanf("%d", &idVeiculo);
                            getchar();
                            listarAlugueisPorVeiculo(alugueis, totalAlugueis, veiculos, totalVeiculos, idVeiculo);
                            break;
                        }
                        case 10:
                            printf("Encerrando o sistema...\n");
                            break;
                        default:
                            printf("Opção inválida! Tente novamente.\n");
                    }
                    printf("Pressione enter para continuar...");
                    getchar(); 
                } while (opcao != 10);
            } else {
                printf("Login falhou. Usuário ou senha inválidos.\n");
                printf("Pressione enter para continuar...");
                getchar(); 
            }
        } else if (tipoLogin == 2) {
            const char* cpfClienteLogado = loginCliente(clientes, totalClientes);
            if (cpfClienteLogado) {
                system("cls"); 
                do {
                    exibirMenuCliente();
                    scanf("%d", &opcao);
                    getchar();

                    system("cls"); 
                    switch (opcao) {
                        case 1:
                            listarVeiculos(veiculos, totalVeiculos);
                            break;
                        case 2:
                            alugarVeiculo(veiculos, totalVeiculos, alugueis, &totalAlugueis);
                            break;
                        case 3:
                            devolverVeiculo(alugueis, &totalAlugueis, veiculos, totalVeiculos, cpfClienteLogado);
                            break;
                        case 4:
                            listarAlugueisPorCliente(alugueis, totalAlugueis, veiculos, totalVeiculos, cpfClienteLogado);
                            break;
                        case 5:
                            simularLocacaoCliente(veiculos, totalVeiculos);
                            break;
                        case 6:
                            printf("Saindo...\n");
                            break;
                        default:
                            printf("Opção inválida! Tente novamente.\n");
                    }
                    printf("Pressione enter para continuar...");
                    getchar();
                } while (opcao != 6);
            } else {
                printf("Login falhou. CPF não encontrado.\n");
                printf("Pressione enter para continuar...");
                getchar(); 
            }
        } else if (tipoLogin == 3) {
            cadastrarCliente(clientes, &totalClientes);
            printf("Pressione enter para continuar...");
            getchar();  
        } else if (tipoLogin == 4) {
            printf("Encerrando o sistema...\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
            printf("Pressione enter para continuar...");
            getchar(); 
        }
    } while (tipoLogin != 4);

    salvarVeiculos(veiculos, totalVeiculos);
    salvarAlugueis(alugueis, totalAlugueis);
    salvarClientes(clientes, totalClientes);

    return 0;
}
