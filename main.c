# include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>


float AtualizarCotacao(float valorAtual) {

    float variacao = ((rand() % 11) - 5) * (5.0 / 100.0);
    
    float novaCotacao = valorAtual * variacao;
    return novaCotacao;
}

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

    //C siginica moeda Real
     fprintf(extrato, "%s|#C+%.2f;%02d/%02d/%d|%02d:%02d:%02d\n",cpfDigitado, valorDeposito,
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,  
            tm.tm_hour, tm.tm_min, tm.tm_sec);             

    fclose(extrato);
    return 0;
}

float VerificaSaldo(char* cpfDigitado) {
    FILE *extrato;
    int tamanho = 100000;
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

            if (linha[c] == '#' && linha[c+1] == 'C') {
                c += 2; 

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
    
        }else if (linha[c] == '#' && linha[c+1] == 'B' || linha[c] == '#' && linha[c+1] == 'E' || linha[c] == '#' && linha[c+1] == 'R') {
            continue; 
        }
    }
    
    fclose(extrato);

    return saldo;
}

float VerificaSaldo_bitcoin(char* cpfDigitado) {
    FILE *extrato;
    int tamanho = 100000;
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

            if (linha[c] == '#' && linha[c+1] == 'B') {
                c += 2; 

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
    
        }else if (linha[c] == '#' && linha[c+1] == 'C' || linha[c] == '#' && linha[c+1] == 'E' || linha[c] == '#' && linha[c+1] == 'R') {
            continue; 
        }
    }
    
    fclose(extrato);

    return saldo;
}

float VerificaSaldo_etherium(char* cpfDigitado) {
    FILE *extrato;
    int tamanho = 100000;
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

            if (linha[c] == '#' && linha[c+1] == 'E') {
                c += 2; 

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
    
        }else if (linha[c] == '#' && linha[c+1] == 'B' || linha[c] == '#' && linha[c+1] == 'C' || linha[c] == '#' && linha[c+1] == 'R') {
            continue; 
        }
    }
    
    fclose(extrato);

    return saldo;
}

float VerificaSaldo_ripple(char* cpfDigitado) {
    FILE *extrato;
    int tamanho = 100000;
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

            //C para remeter ao Cruzeiro Real e nao confundir com R de Ripple
            if (linha[c] == '#' && linha[c+1] == 'R') {
                c += 2; 

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
    
        }else if (linha[c] == '#' && linha[c+1] == 'B' || linha[c] == '#' && linha[c+1] == 'E' || linha[c] == '#' && linha[c+1] == 'C') {
            continue; 
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

        //C siginica moeda Real
        fprintf(extrato, "%s|#C-%.2f;%02d/%02d/%d|%02d:%02d:%02d\n", cpfDigitado, valorSaque,
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
    char cripto_nome[9];

    extrato = fopen("extrato.txt", "a");

    if (saldo >= valorCompra) {

        if (criptoDesejada == 'B'){
            valorCripto = valorCompra / bitcoin_taxa;
            taxa = bitcoin_taxa;
            strcpy(cripto_nome, "Bitcoin");

            printf("Você comprou Bitcoin no valor de R$%.2f\n", resultado);
        } 
        else if (criptoDesejada == 'E'){
            valorCripto = valorCompra * etherium_taxa;
            taxa = etherium_taxa;
            strcpy(cripto_nome, "Etherium");

            printf("Você comprou Ethereum no valor de R$%.2f\n", resultado);
        } 
        else if (criptoDesejada == 'R'){
            valorCripto = valorCompra * ripple_taxa;
            taxa = ripple_taxa;
            strcpy(cripto_nome, "Riplle");

            printf("Você comprou Ripple no valor de R$%.2f\n", resultado);
        }  
        else {
            printf("Criptomoeda inválida!\n");
            fclose(extrato);
            return 0;
        }

        printf("\nVocê está prestes a comprar %.3f %s no valor de R$%.2f\n", valorCripto, cripto_nome, valorCompra);
        printf("Taxa cobrada: %.2f%%\n", taxa * 100.0);
        printf("Confirma a compra? (S/N): ");
        scanf(" %c", &confirmacao);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        if (confirmacao == 'S'){

            //adiciona a subtracao do saldo em reais
            fprintf(extrato, "%s|#C-%.2f;%02d/%02d/%d|%02d:%02d:%02d\n", 
                    cpfDigitado, valorCompra,
                    tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

            //adiciona a compra da criptomoeda escolhida
            fprintf(extrato, "%s|#%c+%.5f;|%02d/%02d/%d|%02d:%02d:%02d\n", 
                    cpfDigitado, criptoDesejada, valorCripto,
                    tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

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
                    saldo_bitcoin = VerificaSaldo_bitcoin(cpfDigitado); 
                    printf("Seu saldo atual em Bitcoin: %.2f\n", saldo_bitcoin);
                    saldo_etherium = VerificaSaldo_etherium(cpfDigitado); 
                    printf("Seu saldo atual em Etherium: %.2f\n", saldo_etherium);
                    saldo_ripple = VerificaSaldo_ripple(cpfDigitado); 
                    printf("Seu saldo atual em Ripple: %.2f\n", saldo_ripple);
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
                    }
                    break;
                case 6: 
                    printf("Vender criptomoedas...");
                    break;
                case 7: 
                    bitcoin_atualizado = AtualizarCotacao(bitcoin_preco);
                    ethereum_atualizado = AtualizarCotacao(ethereum_preco);
                    ripple_atualizado = AtualizarCotacao(ripple_preco);

                    printf("\nCotações atualizadas:\n");
                    printf("Bitcoin: R$%.2f\n", bitcoin_atualizado);
                    printf("Ethereum: R$%.2f\n", ethereum_atualizado);
                    printf("Ripple: R$%.2f\n", ripple_atualizado);
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