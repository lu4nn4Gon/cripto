#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    char cpf[12];
    char senha[5];
} Investidor;

typedef struct {
    char nome[50];
    float cotacaoInicial;
    float taxaCompra;
    float taxaVenda;
} Criptomoeda;



// a mesma função do programa do investidor.
float AtualizarCotacao(float valorAtual) {
    float variacao = ((rand() % 11) - 5) * (5.0 / 100.0);
    float novaCotacao = valorAtual + (valorAtual * variacao);
    return novaCotacao;
}

void AtualizarCotacoesCriptomoedas() {
    FILE *arquivo = fopen("criptomoedas.bin", "rb+");
    Criptomoeda cripto;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas!\n");
        return;
    }

    while (fread(&cripto, sizeof(Criptomoeda), 1, arquivo) == 1) {
        float novaCotacao = AtualizarCotacao(cripto.cotacaoInicial);
        cripto.cotacaoInicial = novaCotacao;

        fseek(arquivo, -sizeof(Criptomoeda), SEEK_CUR);
        fwrite(&cripto, sizeof(Criptomoeda), 1, arquivo);

        printf("Criptomoeda: %s\nNova Cotação: %.2f\n", cripto.nome, cripto.cotacaoInicial);
        printf("----------------------------------\n");
    }

    fclose(arquivo);
    printf("Cotações de todas as criptomoedas atualizadas com sucesso!\n");
}

int VerificaCriptomoeda(const char* nome) {
    FILE *arquivo;
    Criptomoeda cripto;

    arquivo = fopen("criptomoedas.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas!\n");
        return -1;
    }

    while (fread(&cripto, sizeof(Criptomoeda), 1, arquivo) == 1) {
        if (strcmp(cripto.nome, nome) == 0) {
            fclose(arquivo);
            return 1; 
        }
    }

    fclose(arquivo);
    return 0; 
}

int ExibirCriptomoeda(const char* nomeCripto) {
    FILE *arquivo = fopen("criptomoedas.bin", "rb");
    Criptomoeda cripto;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas!\n");
        return -1;
    }

    while (fread(&cripto, sizeof(Criptomoeda), 1, arquivo) == 1) {
        if (strcmp(cripto.nome, nomeCripto) == 0) {
            printf("\nDados da Criptomoeda:\n");
            printf("Nome: %s\n", cripto.nome);
            printf("Cotação Inicial: %.2f\n", cripto.cotacaoInicial);
            printf("Taxa de Compra: %.2f\n", cripto.taxaCompra);
            printf("Taxa de Venda: %.2f\n", cripto.taxaVenda);
            printf("----------------------------------\n");
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0; 
}


int CadastrarCriptomoeda(const char* nome, float cotacaoInicial, float taxaCompra, float taxaVenda) {
    FILE *arquivo;
    Criptomoeda novaCripto;

    if (VerificaCriptomoeda(nome) == 1) {
        printf("Criptomoeda já está cadastrada!\n");
        return -1;  
    }

    strncpy(novaCripto.nome, nome, sizeof(novaCripto.nome) - 1);
    novaCripto.cotacaoInicial = cotacaoInicial;
    novaCripto.taxaCompra = taxaCompra;
    novaCripto.taxaVenda = taxaVenda;

    arquivo = fopen("criptomoedas.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas!\n");
        return -1;
    }


    fwrite(&novaCripto, sizeof(Criptomoeda), 1, arquivo);
    fclose(arquivo);

    printf("Criptomoeda cadastrada com sucesso!\n");
    return 0;
}

int ExcluirCriptomoeda(const char* nomeCripto) {
    FILE *arquivo, *arquivoTemp;
    Criptomoeda cripto;
    int encontrado = 0;

    arquivo = fopen("criptomoedas.bin", "rb");
    arquivoTemp = fopen("criptomoedas_temp.bin", "wb");
    if (arquivo == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas!\n");
        return -1;
    }

    while (fread(&cripto, sizeof(Criptomoeda), 1, arquivo) == 1) {
        if (strcmp(cripto.nome, nomeCripto) != 0) {
            fwrite(&cripto, sizeof(Criptomoeda), 1, arquivoTemp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("criptomoedas.bin");
    rename("criptomoedas_temp.bin", "criptomoedas.bin");

    if (encontrado) {
        return 0;
    } else {
        return -2;
    }
}


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
    
    while (fread(cpf, sizeof(char), 11, usuarios) == 11) {
        cpf[11] = '\0';
        fread(senha, sizeof(char), 4, usuarios); 
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



void ConsultarExtrato(char* cpfDigitado) {
    FILE *extrato;
    char cpf[12];
    char tipoTransacao;
    char moeda;
    float valor;
    int dia, mes, ano, hora, minuto, segundo;
    char* nomeMoeda;

    extrato = fopen("extrato.bin", "rb");
    if (extrato == NULL) {
        printf("Erro ao abrir o arquivo de extrato.\n");
        return;
    }

    printf("\nExtrato de transações para o CPF: %s\n", cpfDigitado);

    while (fread(&tipoTransacao, sizeof(char), 1, extrato) == 1) {
        fread(&moeda, sizeof(char), 1, extrato);
        fread(cpf, sizeof(char), 11, extrato);
        cpf[11] = '\0';
        fread(&valor, sizeof(float), 1, extrato);
        fread(&dia, sizeof(int), 1, extrato);
        fread(&mes, sizeof(int), 1, extrato);
        fread(&ano, sizeof(int), 1, extrato);
        fread(&hora, sizeof(int), 1, extrato);
        fread(&minuto, sizeof(int), 1, extrato);
        fread(&segundo, sizeof(int), 1, extrato);

        if (ValidaIgualdade(cpf, cpfDigitado)) {
            if (moeda == 'C') {
                nomeMoeda = "Reais";
            } else if (moeda == 'B') {
                nomeMoeda = "Bitcoin";
            } else if (moeda == 'E') {
                nomeMoeda = "Ethereum";
            } else if (moeda == 'R') {
                nomeMoeda = "Ripple";
            } 

        if (tipoTransacao == 'D') {
            printf("\nTipo de Transação: Depósito\n");
        } else {
            printf("\nTipo de Transação: Saque\n");
        }


            printf("Moeda: %s\n", nomeMoeda);
            printf("Valor: R$%.2f\n", valor);
            printf("Data e Hora: %02d/%02d/%04d %02d:%02d:%02d\n", dia, mes + 1, ano + 1900, hora, minuto, segundo);
            printf("----------------------------------\n");
        }
    }

    fclose(extrato);
}


int Login(char* cpfDigitado, char* senhaDigitada){
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
    char nomeCripto[50];
    float cotacaoInicial, taxaCompra, taxaVenda;

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
                // ExibirCriptomoedas();
                printf("\nDigite o nome da criptomoeda: ");
                scanf("%50s", nomeCripto);
                printf("Digite a cotação inicial da criptomoeda: ");
                scanf("%f", &cotacaoInicial);
                printf("Digite a taxa de compra: ");
                scanf("%f", &taxaCompra);
                printf("Digite a taxa de venda: ");
                scanf("%f", &taxaVenda);

                CadastrarCriptomoeda(nomeCripto, cotacaoInicial, taxaCompra, taxaVenda);
                break;

            case 4:
                printf("\nDigite o nome da criptomoeda que deseja excluir: ");
                scanf("%49s", nomeCripto);

                int e = ExibirCriptomoeda(nomeCripto);
                if (e == 0) {
                    printf("Criptomoeda não encontrada!\n");
                    break;
                } else if (e == -1) {
                    printf("Erro ao acessar o arquivo de criptomoedas!\n");
                    break;
                } 

                char confirmacao;
                printf("Deseja realmente excluir essa criptomoeda? (S/N): ");
                scanf(" %c", &confirmacao);

                if (confirmacao == 'S' || confirmacao == 's') {
                    int resultado = ExcluirCriptomoeda(nomeCripto);
                    if (resultado == 0) {
                        printf("Criptomoeda excluída com sucesso!\n");
                    } else if (resultado == -2) {
                        printf("Criptomoeda não encontrada!\n");
                    } else {
                        printf("Erro ao excluir criptomoeda!\n");
                    }
                } else if (confirmacao == 'N' || confirmacao == 'n') {
                    printf("Processo cancelado!\n");
                } else {
                    printf("Opção inválida.\n");
                }

                break;

            case 5:
                printf("Consultando saldo de um investidor...");
                break;
            case 6:
                printf("\nDigite o CPF do investidor para consultar o extrato: ");
                scanf("%11s", cpfDigitado);  
                ConsultarExtrato(cpfDigitado); 
                break;

            case 7:
                printf("\nAtualizando cotações de todas as criptomoedas...\n");
                AtualizarCotacoesCriptomoedas();
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