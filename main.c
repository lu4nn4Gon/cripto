# include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

//essa funcao
float StringViraNumero(char* string) {
    float resultado = 0.0;
    float fator = 1.0;
    int i = 0;
    int decimal = 0; 

    if (string[0] == '-' || string[0] == '+') {
        i++;
    }

    while (string[i] != '\0') {
        if (string[i] == '.') {
            decimal = 1; 
            i++;
            continue;
        }

        if (decimal) {
            fator = fator * 0.10;
            resultado = resultado + (string[i] - '0') * fator;
        } else {
            resultado = resultado * 10 + (string[i] - '0');
        }

        i++;
    }

    if (string[0] == '-') {
        resultado = -resultado;
    }

    return resultado;
}



float ValidaIgualdade(char* stringOne, char* stringTwo){
    int i = 0;

    while(stringOne[i] != '\0' && stringTwo[i] != '\0'){

        if (stringOne[i] != stringTwo[i]) {
            return 0;
        } i++;
    }
   return 1; 
    
}


char Depositar(float valorDeposito, char* cpfDigitado){
    FILE *extrato;
    int tamanho = 100000;
    char linha[tamanho];

    extrato = fopen("extrato.txt", "a");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

     fprintf(extrato, "%s|+%.2f;%02d/%02d/%d|%02d:%02d:%02d\n",cpfDigitado, valorDeposito,
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,  
            tm.tm_hour, tm.tm_min, tm.tm_sec);             

    fclose(extrato);
    return 0;
}

float VerificaSaldo(char* cpfDigitado) {
    FILE *extrato;
    int tamanho = 1000;
    char linha[tamanho];
    char cpf[12];
    char valor[11];

    extrato = fopen("extrato.txt", "r");

    float saldo = 0.0;

    while (fgets(linha, tamanho, extrato) != NULL) {
        int c = 0;
        while (linha[c] != '|') {
            cpf[c] = linha[c];
            c++;
        }
        cpf[c] = '\0'; 
        c++;

        if (ValidaIgualdade(cpf, cpfDigitado)) {
            int v = 0;

            while (linha[c] != ';') {
                valor[v] = linha[c];
                c++;
                v++;
            }
            
            valor[v] = '\0';
    
            float valor_numero = StringViraNumero(valor);
   
            saldo = saldo + valor_numero;
        }
    }
    
    fclose(extrato);

    return saldo;
}

int Sacar(float valorSaque, char*senhaDigitada, char* cpfDigitado){
    FILE *extrato;
    int saldo = VerificaSaldo(cpfDigitado);

    if (saldo >= valorSaque) {
        extrato = fopen("extrato.txt", "a");

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        fprintf(extrato, "%s|-%.2f;%02d/%02d/%d|%02d:%02d:%02d\n", cpfDigitado, valorSaque,
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
        
        fclose(extrato);

        printf("Saque de %.2f realizado com sucesso.\n", valorSaque);
        return 1; 
    } else {
        printf("Saldo insuficiente.\n");
        return 0; 
    }
}

    


int Login(char* cpfDigitado, char* senhaDigitada){
    FILE *usuarios;
    int t = 256;
    char linha[t];
    char cpf[12];
    char senha[5];
    int valorSaque;

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
    char senhaVerificacao[5];
    float valorDeposito;
    float valorSaque;
    char senha[5];
    float saldo;

    printf("\nDigite o CPF: ");
    scanf("%11s", cpfDigitado);  
    printf("Digite a senha: ");
    scanf("%5s", senhaDigitada); 

    int logado = Login(cpfDigitado, senhaDigitada);
    
    
    if(logado == 1){
        printf("Login invalido\n");
    } while(logado == 0) {
            int opcao;
            printf("\nMenu\n");
            printf("\t1 - Consultar saldo \n");
            printf("\t2 - Consultar extrato \n");
            printf("\t3 - Depositar \n");
            printf("\t4 - Sacar \n");
            printf("\t5 - Comprar criptomoedas \n");
            printf("\t6 - Vender criptomoedas \n");
            printf("\t7 - Atualizar cotação da criptomoeda \n");
            printf("\t0 - Sair \n");
            printf("\n Escolha uma opção:\n ");
            scanf("%d", &opcao);

            switch(opcao) {
                case 1: 
                    saldo = VerificaSaldo(cpfDigitado); 
                    printf("Seu saldo atual e: %.2f\n", saldo);
                    break;
                case 2: 
                    printf("Consultar extrato...");
                    break;
                case 3: 
                    printf("\nDigite o valor que deseja depositar em Reais: ");
                    scanf("%f", &valorDeposito);
                    if(valorDeposito > 0){
                    Depositar(valorDeposito, cpfDigitado);
                    }
                    printf("Valor depositado!\n");
                    break;
                case 4: 
                    printf("\nDigite o valor que deseja sacar em Reais: ");
                    scanf("%f", &valorSaque);
                    printf("Digite sua Senha: ");
                    scanf("%5s", senhaVerificacao); 
                    if (ValidaIgualdade(senhaDigitada, senhaVerificacao) == 1){
                        Sacar(valorSaque, senhaDigitada, cpfDigitado);
                    } else {
                        printf("Senha incorreta\n");
                    }
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
                    return 0;
                default:
                    printf("Opção inválida \n");
                    break;
        }
    }

    return 0;
}