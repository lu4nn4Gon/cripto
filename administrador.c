#include <stdio.h>
#include <string.h>

typedef struct {
    char cpf[12];
    char senha[5];
} Investidor;


float ValidaIgualdade(const char* stringOne, const char* stringTwo) {
    int i = 0;

    while (stringOne[i] != '\0' && stringTwo[i] != '\0') {
        if (stringOne[i] != stringTwo[i]) {
            return 0;
        }
        i++;
    }
    return 1; 
}

int VerificaCPF(const char *cpfDigitado) {
    FILE *usuarios;
    char cpf[12];
    char senha[5];
    
    usuarios = fopen("usuarios.bin", "rb");
    if (usuarios == NULL) {
        return -1;
    }
    
    // Verifica se o CPF já existe
    while (fread(cpf, sizeof(char), 11, usuarios) == 11) {
        cpf[11] = '\0';
        fread(senha, sizeof(char), 4, usuarios); // Lê a senha associada ao CPF
        senha[4] = '\0';
        
        if (ValidaIgualdade(cpf, cpfDigitado)) {
            fclose(usuarios);
            return 1;
        }
    }

    fclose(usuarios);
    return 0;
}

int Cadastro(const char* cpfDigitado, const char* senhaDigitada, char* nomeDigitado) {
    FILE *usuarios;
    FILE *nomes;

    if (VerificaCPF(cpfDigitado) == 1) {
        printf("CPF já cadastrado!\n");
        return -1;
    }

    usuarios = fopen("usuarios.bin", "ab");
    if (usuarios == NULL) {
        return -1;
    }
    
    fwrite(cpfDigitado, sizeof(char), 11, usuarios);  
    fwrite(senhaDigitada, sizeof(char), 4, usuarios); 


    fclose(usuarios);

    nomes = fopen("nomes.bin", "ab");
    if (usuarios == NULL) {
        return -1;
    }

    fwrite(cpfDigitado, sizeof(char), 11, nomes);
    fwrite(nomeDigitado, sizeof(char), 49, nomes);  

    fclose(nomes);


    return 0;
}

int Excluir(char* cpfDigitado) {
    FILE *usuarios, *usuariosTemp, *nomes, *nomesTemp;
    char cpf[12];
    char senha[5];
    int encontrado = 0;

    usuarios = fopen("usuarios.bin", "rb");
    usuariosTemp = fopen("usuarios_temp.bin", "wb");
    if (usuarios == NULL || usuariosTemp == NULL) {
        return -1;
    }

    while (fread(cpf, sizeof(char), 11, usuarios) == 11 && fread(senha, sizeof(char), 4, usuarios) == 4) {
        cpf[11] = '\0';
        senha[4] = '\0';

        if (ValidaIgualdade(cpf, cpfDigitado) == 0) {
            fwrite(cpf, sizeof(char), 11, usuariosTemp);
            fwrite(senha, sizeof(char), 4, usuariosTemp);
        } else {
            encontrado = 1;
        }
    }

    fclose(usuarios);
    fclose(usuariosTemp);

    remove("usuarios.bin");
    rename("usuarios_temp.bin", "usuarios.bin");

    nomes = fopen("nomes.bin", "rb");
    nomesTemp = fopen("nomes_temp.bin", "wb");
    if (nomes == NULL || nomesTemp == NULL) {
        return -1;
    }

    char nome[50];
    while (fread(cpf, sizeof(char), 11, nomes) == 11 && fread(nome, sizeof(char), 49, nomes) == 49) {
        cpf[11] = '\0';

        if (ValidaIgualdade(cpf, cpfDigitado) == 0) {
            fwrite(cpf, sizeof(char), 11, nomesTemp);
            fwrite(nome, sizeof(char), 49, nomesTemp);
        }
    }

    fclose(nomes);
    fclose(nomesTemp);

    remove("nomes.bin");
    rename("nomes_temp.bin", "nomes.bin");

    if (encontrado) {
        return 0;
    } else {
        return -2 ;
    }
}

char *ExibirInformacoesInvestidor(const char *cpfDigitado) {
    FILE *usuarios;
    FILE *nomes;
    char cpf[12];
    char senha[5];
    char nome[50];
    static char resultado[200];  

    usuarios = fopen("usuarios.bin", "rb");
    nomes = fopen("nomes.bin", "rb");

    if (usuarios == NULL || nomes == NULL) {
        snprintf(resultado, sizeof(resultado), "Erro ao abrir arquivos!\n");
        return resultado;
    }

    while (fread(cpf, sizeof(char), 11, usuarios) == 11 && fread(senha, sizeof(char), 4, usuarios) == 4) {
        cpf[11] = '\0';
        senha[4] = '\0';

        if (ValidaIgualdade(cpf, cpfDigitado)) {
            while (fread(cpf, sizeof(char), 11, nomes) == 11 && fread(nome, sizeof(char), 49, nomes) == 49) {
                cpf[11] = '\0';
                nome[49] = '\0';
                
                if (ValidaIgualdade(cpf, cpfDigitado)) {
                    snprintf(resultado, sizeof(resultado), 
                             "Informações do Investidor:\nCPF: %s\nSenha: %s\nNome: %s\n", 
                             cpf, senha, nome);
                    fclose(usuarios);
                    fclose(nomes);
                    return resultado;
                }
            }
        }
    }

    fclose(usuarios);
    fclose(nomes);
    snprintf(resultado, sizeof(resultado), "Investidor não encontrado.\n");
    return resultado;
}


int Login(char* cpfDigitado, char* senhaDigitada) {
    FILE *usuarios;
    char cpf[12];
    char senha[5];

    usuarios = fopen("administradores.bin", "rb");

    while (fread(cpf, sizeof(char), 11, usuarios) == 11 && fread(senha, sizeof(char), 4, usuarios) == 4) {
        cpf[11] = '\0';   
        senha[4] = '\0';  

        if (ValidaIgualdade(cpf, cpfDigitado) && ValidaIgualdade(senha, senhaDigitada)) {
            fclose(usuarios);
            return 0; 
        }
    }

    fclose(usuarios);
    return 1; 
}


int main(void) {
    char cpfDigitado[12];
    char senhaDigitada[5];
    char senhaVerificacao[5];
    char nomeDigitado[50];

    int logado = 1;  

    if (logado == 1) {
        printf("\nDigite o CPF: ");
        scanf("%11s", cpfDigitado);
        printf("Digite a senha: ");
        scanf("%5s", senhaDigitada);

        logado = Login(cpfDigitado, senhaDigitada);

        if (logado == 1) {
            printf("Login inválido.\n");
            return 1; 
        } else {
            printf("Login realizado com sucesso!\n");
        }
    }

    int opcao = 1;
    while (opcao != 0) {
        printf("\nMenu\n");
        printf("\t1 - Cadastrar novo investidor\n");
        printf("\t2 - Excluir investidor\n");
        printf("\t3 - Cadastrar criptomoeda\n");
        printf("\t4 - Excluir criptomoeda\n");
        printf("\t5 - Consultar saldo de um investidor\n");
        printf("\t6 - Consultar extrato de um investidor\n");
        printf("\t7 - Atualizar cotação de criptomoedas\n");
        printf("\t0 - Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nDigite o CPF do investidor que deseja cadastrar: ");
                scanf("%11s", cpfDigitado);
                int a = VerificaCPF(cpfDigitado);
                if (a == 0) {
                    printf("Digite a senha do investidor: ");
                    scanf("%5s", senhaDigitada);
                    printf("Digite o nome do investidor: ");
                    scanf("%50s", nomeDigitado);
                    int b = Cadastro(cpfDigitado, senhaDigitada, nomeDigitado);
                    if (b == 0) {
                        printf("Cadastro realizado com sucesso!\n");
                    } else {
                        printf("Erro ao realizar o cadastro!\n");
                    }
                } else if (a == -1) {
                    printf("Erro ao abrir arquivo!\n");
                } else {
                    printf("CPF já cadastrado!\n");
                }
                break;
            case 2: {
                char confirmacao;  
                printf("\nDigite o CPF do investidor que deseja excluir: ");
                scanf("%11s", cpfDigitado);
                int c = VerificaCPF(cpfDigitado);
                if (c == 1) {
                    char *info = ExibirInformacoesInvestidor(cpfDigitado);
                    printf("----------------------------------\n");
                    printf("%s", info);
                    
                    printf("\nDeseja excluir esse investidor? (S/N): ");
                    scanf(" %c", &confirmacao);  

                    if (confirmacao == 'S' || confirmacao == 's') {
                        if (Excluir(cpfDigitado) == 0) {  
                            printf("Investidor excluído com sucesso!\n");
                        } else {
                            printf("Erro ao excluir investidor!\n");
                        }
                    } else if (confirmacao == 'N' || confirmacao == 'n') {
                        printf("Processo cancelado!\n");
                    } else {
                        printf("Opção inválida\n");
                    }
                } else if (c == -1) {
                    printf("Erro ao abrir arquivo!\n");
                } else {
                    printf("CPF não tem cadastro!\n");
                }
                break;
            }

            case 3:
                printf("Cadastrando criptomoeda...");
                break;
            case 4:
                printf("Excluindo criptomoeda...");
                break;
            case 5:
                printf("Consultando saldo de um investidor...");
                break;
            case 6:
                printf("Consultando extrato de um investidor...");
                break;
            case 7:
                printf("Atualizando cotação de criptomoedas...");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }

    return 0;
}