#include <stdio.h>

float ValidaIgualdade(char* stringOne, char* stringTwo){
    int i = 0;

    while(stringOne[i] != '\0' && stringTwo[i] != '\0'){

        if (stringOne[i] != stringTwo[i]) {
            return 0;
        } i++;
    }
   return 1; 
    
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
        printf("\t6 - Consultar extrado de um investidor\n");
        printf("\t7 - Atualizar cotação de criptomoedas\n");
        printf("\t0 - Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Cadastrando novo investidor...");
                break;
            case 2:
                printf("Excluindo investidor...");
                break;
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
                printf("Consultando extrado de um investidor...");
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
