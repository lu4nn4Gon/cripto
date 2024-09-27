# include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>



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
    char tipoTransacao = 'D';
    char moeda = 'C';

    extrato = fopen("extrato.bin", "ab");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);


    fwrite(&tipoTransacao, sizeof(char), 1, extrato);

    
    fwrite(&moeda, sizeof(char), 1, extrato);

    fwrite(cpfDigitado, sizeof(char), 11, extrato);

    fwrite(&valorDeposito, sizeof(float), 1, extrato);

    fwrite(&tm.tm_mday, sizeof(int), 1, extrato);   // Dia
    fwrite(&tm.tm_mon, sizeof(int), 1, extrato);    // Mês (
    fwrite(&tm.tm_year, sizeof(int), 1, extrato);   // Ano 
   
    fwrite(&tm.tm_hour, sizeof(int), 1, extrato);   // Hora
    fwrite(&tm.tm_min, sizeof(int), 1, extrato);    // Minuto
    fwrite(&tm.tm_sec, sizeof(int), 1, extrato);    // Segundo
    fclose(extrato);
    return 0;
}



int Login(char* cpfDigitado, char* senhaDigitada){
    FILE *usuarios;
    char cpf[12];
    char senha[5];

    usuarios = fopen("usuarios.bin", "rb");

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
    char criptoDesejada;
    float valorDeposito, valorSaque, valorCompra;
    char senha[5];
    float saldo;
    float bitcoin_preco = 10000.0;
    float ethereum_preco = 500.0;
    float ripple_preco = 1.0;
    float bitcoin_atualizado, ethereum_atualizado, ripple_atualizado;
    srand(time(NULL));
    float saldo_bitcoin, saldo_etherium, saldo_ripple;

    printf("\nDigite o CPF: ");
    scanf("%11s", cpfDigitado);  
    printf("Digite a senha: ");
    scanf("%5s", senhaDigitada); 

    int logado = Login(cpfDigitado, senhaDigitada);
    
    
    if(logado == 1){
        printf("Login invalido\n");
    } else {
        
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
            printf("\n Escolha uma opção: ");
            scanf("%d", &opcao);

            switch(opcao) {
                case 1: 
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
                    break;
                case 5: 
                    break;
                case 6: 
                    printf("Vender criptomoedas...");
                    break;
                case 7: 
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
