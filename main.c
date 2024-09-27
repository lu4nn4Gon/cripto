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

float VerificaSaldo(char* cpfDigitado) {
    FILE *extrato;
    char cpf[12];
    char tipoTransacao;
    char moeda;
    float valor;
    int dia, mes, ano, hora, minuto, segundo;
    float saldo = 0.0;

    extrato = fopen("extrato.bin", "rb");


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


        if (ValidaIgualdade(cpf, cpfDigitado) && moeda == 'C') {
            if (tipoTransacao == 'D') {
                saldo = saldo + valor; 
            } else if (tipoTransacao == 'S') {
                saldo = saldo - valor;  
            }
        }
    }

    fclose(extrato);

    return saldo; 

}


int Sacar(float valorSaque, char*senhaDigitada, char* cpfDigitado){
    FILE *extrato;
    float saldo = VerificaSaldo(cpfDigitado);
 

    if (saldo >= valorSaque) {
        extrato = fopen("extrato.bin", "ab");

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        char tipoTransacao = 'S';  
        char moeda = 'C';         

        fwrite(&tipoTransacao, sizeof(char), 1, extrato); 
        fwrite(&moeda, sizeof(char), 1, extrato);         
        fwrite(cpfDigitado, sizeof(char), 11, extrato);   
        fwrite(&valorSaque, sizeof(float), 1, extrato);   

        fwrite(&tm.tm_mday, sizeof(int), 1, extrato);   
        fwrite(&tm.tm_mon, sizeof(int), 1, extrato);    
        fwrite(&tm.tm_year, sizeof(int), 1, extrato);   
        fwrite(&tm.tm_hour, sizeof(int), 1, extrato);   
        fwrite(&tm.tm_min, sizeof(int), 1, extrato);    
        fwrite(&tm.tm_sec, sizeof(int), 1, extrato);   
        
        fclose(extrato);

        printf("Saque de %.2f realizado com sucesso.\n", valorSaque);
        return 1; 
    } else {
        printf("Saldo insuficiente.\n");
        return 0; 
    }
}


float CompraCripto(float valorCompra, char criptoDesejada, char* cpfDigitado) {
    float saldo = VerificaSaldo(cpfDigitado); 
    FILE *extrato;
    float taxa = 0.0;
    float bitcoin_taxa = 2.0 / 100.0;
    float etherium_taxa = 1.0 / 100.0;
    float ripple_taxa = 1.0 / 100.0;
    float resultado = 0.0;
    char confirmacao;
    float valorCripto = 0.0;
    char *cripto_nome;
    char tipoTransacaoReais = 'S';  
    char moedaReais = 'C';
    char tipoTransacaoCripto = 'D';
    float bitcoinCotacao = 350000.0;
    float ethereumCotacao = 14000.0;
    float rippleCotacao = 3.20; 


    extrato = fopen("extrato.bin", "ab");
    if (extrato == NULL) {
        printf("Erro ao abrir o arquivo de extrato.\n");
        return 0;
    }

    if (saldo >= valorCompra) {

        if (criptoDesejada == 'B'){
            valorCripto = (valorCompra * (1 - bitcoin_taxa)) / bitcoinCotacao;
            taxa = bitcoin_taxa;
            cripto_nome = "Bitcoin"; 

            printf("Você comprou Bitcoin no valor de R$%.5f\n", valorCompra);
        } 
        else if (criptoDesejada == 'E'){
            valorCripto = (valorCompra * (1 - etherium_taxa)) / ethereumCotacao;
            taxa = etherium_taxa;
            cripto_nome = "Ethereum"; 

            printf("Você comprou Ethereum no valor de R$%.3f\n", valorCompra);
        } 
        else if (criptoDesejada == 'R'){
            valorCripto = (valorCompra * (1 - ripple_taxa)) / rippleCotacao;
            taxa = ripple_taxa;
            cripto_nome = "Ripple"; 

            printf("Você comprou Ripple no valor de R$%.3f\n", valorCompra);
        }  
        else {
            printf("Criptomoeda inválida!\n");
            fclose(extrato);
            return 0;
        }

        printf("\nVocê está prestes a comprar %.5f %s no valor de R$%.2f\n", valorCripto, cripto_nome, valorCompra);
        printf("Taxa cobrada: %.2f%%\n", taxa * 100.0);
        printf("Confirma a compra? (S/N): ");
        scanf(" %c", &confirmacao);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        if (confirmacao == 'S') {

            // Registra a subtração do saldo em reais
            fwrite(&tipoTransacaoReais, sizeof(char), 1, extrato);
            fwrite(&moedaReais, sizeof(char), 1, extrato);
            fwrite(cpfDigitado, sizeof(char), 11, extrato);
            fwrite(&valorCompra, sizeof(float), 1, extrato);
            fwrite(&tm.tm_mday, sizeof(int), 1, extrato);
            fwrite(&tm.tm_mon, sizeof(int), 1, extrato);
            fwrite(&tm.tm_year, sizeof(int), 1, extrato);
            fwrite(&tm.tm_hour, sizeof(int), 1, extrato);
            fwrite(&tm.tm_min, sizeof(int), 1, extrato);
            fwrite(&tm.tm_sec, sizeof(int), 1, extrato);

            // Registra a compra da criptomoeda
            fwrite(&tipoTransacaoCripto, sizeof(char), 1, extrato);
            fwrite(&criptoDesejada, sizeof(char), 1, extrato);
            fwrite(cpfDigitado, sizeof(char), 11, extrato);
            fwrite(&valorCripto, sizeof(float), 1, extrato);
            fwrite(&tm.tm_mday, sizeof(int), 1, extrato);
            fwrite(&tm.tm_mon, sizeof(int), 1, extrato);
            fwrite(&tm.tm_year, sizeof(int), 1, extrato);
            fwrite(&tm.tm_hour, sizeof(int), 1, extrato);
            fwrite(&tm.tm_min, sizeof(int), 1, extrato);
            fwrite(&tm.tm_sec, sizeof(int), 1, extrato);

            fclose(extrato);  
            printf("Compra realizada!\n");
        } else {
            printf("Compra cancelada.\n");
        }
    } else {
        printf("Saldo insuficiente para a compra!\n");
        fclose(extrato);
        return 0;
    }
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
                    saldo = VerificaSaldo(cpfDigitado); 
                    printf("\nSeu saldo atual em Reais: %.2f\n", saldo);
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
                    printf("\nCriptomoedas disponiveis para compra\n");
                    printf("B -> Bitcoin\n");
                    printf("E -> Ethereum\n");
                    printf("R -> Ripple\n");

                    printf("\nDigite qual criptomoeda deseja comprar (B ou E ou R): ");
                    scanf(" %c", &criptoDesejada);

                    printf("\nDigite o valor que deseja comprar em Reais: ");
                    scanf("%f", &valorCompra);

                    printf("Digite sua Senha: ");
                    scanf("%5s", senhaVerificacao); 

                    if (ValidaIgualdade(senhaDigitada, senhaVerificacao) == 1){
                        CompraCripto(valorCompra, criptoDesejada, cpfDigitado);
                    } else {
                        printf("Senha incorreta\n");
                    // }
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
}