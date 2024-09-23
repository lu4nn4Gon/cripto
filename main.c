# include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int ValidaIgualdade(char* stringOne, char* stringTwo){
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
    int t = 256;
    char linha[t];
    char cpf[12];
    char senha[5];

    usuarios = fopen("usuarios.txt", "r");
    while (fgets(linha, t, usuarios) != NULL) {
        
        int c = 0;
        int s = 0;

        while (linha[c] != '-') {
            cpf[c] = linha[c]; 
            c++;
        }
        cpf[c] = '\0'; 

        c++;

        while (linha[c] != '\0') {
            senha[s] = linha[c];
            c++;
            s++;
        }
        senha[s] = '\0';

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

    printf("Digite o CPF: ");
    scanf("%11s", cpfDigitado);  
    printf("Digite a senha: ");
    scanf("%5s", senhaDigitada); 

    const int resultado = Login(cpfDigitado, senhaDigitada);
    
    if(resultado == 1){
        printf("Login inválido\n");
    } else {
        int opcao;
        printf("Menu\n");
        printf("\t1 - Consultar saldo \n");
        printf("\t2 - Consultar extrato \n");
        printf("\t3 - Depositar \n");
        printf("\t4 - Sacar \n");
        printf("\t5 - Comprar criptomoedas \n");
        printf("\t6 - Vender criptomoedas \n");
        printf("\t7 - Atualizar cotação da criptomoeda \n");
        printf("\t0 - Sair \n");
        printf("\n Escolha uma opção ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                printf("Consultar Saldo...");
                break;
            case 2: 
                printf("Consultar extrato...");
                break;
            case 3: 
                printf("Depositar...");
                break;
            case 4: 
                printf("Sacar...");
                break;
            case 5: 
                printf("Comprar criptomoedas...");
                break;
            case 6: 
                printf("Vender criptomoedas...");
                break;
            case 7: 
                printf("Atualizar cotação...");
                break;
            case 0:
                printf("Saindo...\n"); 
                break;
            default:
                printf("Opção inválida \n");
                break;
    }
    }

    return 0;
}