# include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];
    float cotacaoInicial;
    float taxaCompra;
    float taxaVenda;
} Criptomoeda;



void ListarCriptomoedas() {
    FILE *arquivo = fopen("criptomoedas.bin", "rb");
    Criptomoeda cripto;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas!\n");
        return;
    }

    printf("\nCriptomoedas disponíveis para compra:\n");
    while (fread(&cripto, sizeof(Criptomoeda), 1, arquivo) == 1) {
        printf("- Nome: %s\n", cripto.nome);
        printf("  Cotação Atual: R$%.2f\n", cripto.cotacaoInicial);
        printf("  Taxa de Compra: %.2f%%\n", cripto.taxaCompra * 100);
        printf("  Taxa de Venda: %.2f%%\n", cripto.taxaVenda * 100);
        printf("----------------------------------\n");
    }

    fclose(arquivo);
}


int BuscarCriptomoeda(const char *nomeCripto, Criptomoeda *cripto) {
    FILE *arquivo = fopen("criptomoedas.bin", "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas!\n");
        return 0;
    }

    while (fread(cripto, sizeof(Criptomoeda), 1, arquivo) == 1) {
        if (strcmp(cripto->nome, nomeCripto) == 0) {
            fclose(arquivo);
            return 1;  
        }
    }

    fclose(arquivo);
    return 0;  
}




float AtualizarCotacao(float valorAtual) {

    float variacao = ((rand() % 11) - 5) * (5.0 / 100.0);
    
    float novaCotacao = valorAtual + (valorAtual * variacao);
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

float VerificaSaldo_bitcoin(char* cpfDigitado) {
    FILE *extrato;
    char cpf[12];
    char tipoTransacao;
    char moeda;
    float valor;
    int dia, mes, ano, hora, minuto, segundo;

    extrato = fopen("extrato.bin", "rb");

    float saldo = 0.0;
   
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

        if (ValidaIgualdade(cpf, cpfDigitado) && moeda == 'B') {
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


float VerificaSaldo_etherium(char* cpfDigitado) {
    FILE *extrato;
    char cpf[12];
    char tipoTransacao;
    char moeda;
    float valor;
    int dia, mes, ano, hora, minuto, segundo;

    extrato = fopen("extrato.bin", "rb");

    float saldo = 0.0;

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

        if (ValidaIgualdade(cpf, cpfDigitado) && moeda == 'E') {
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

float VerificaSaldo_ripple(char* cpfDigitado) {
    FILE *extrato;
    char cpf[12];
    char tipoTransacao;
    char moeda;
    float valor;
    int dia, mes, ano, hora, minuto, segundo;

    extrato = fopen("extrato.bin", "rb");

    float saldo = 0.0;

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

        if (ValidaIgualdade(cpf, cpfDigitado) && moeda == 'R') {
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


 char *ConsultarSaldo(char * cpfDigitado){
    float saldo = VerificaSaldo(cpfDigitado); 
    float saldo_bitcoin = VerificaSaldo_bitcoin(cpfDigitado); 
    float saldo_etherium = VerificaSaldo_etherium(cpfDigitado); 
    float saldo_ripple = VerificaSaldo_ripple(cpfDigitado); 
    char* resultado = (char*)malloc(500 * sizeof(char));

    sprintf(resultado,
            "\nUsuario: %.11s\n"
            "Seu saldo atual em Reais: %.2f\n"
            "Seu saldo atual em Bitcoin: %.6f\n"
            "Seu saldo atual em Etherium: %.6f\n"
            "Seu saldo atual em Ripple: %.6f\n",
            cpfDigitado, saldo, saldo_bitcoin, saldo_etherium, saldo_ripple);

    return resultado;
}

float CompraCripto(float valorCompra, const char *nomeCripto, char *cpfDigitado) {
    Criptomoeda cripto;
    if (!BuscarCriptomoeda(nomeCripto, &cripto)) {
        printf("Criptomoeda '%s' não encontrada!\n", nomeCripto);
        return 0;
    }

    float saldo = VerificaSaldo(cpfDigitado);
    float valorCripto = (valorCompra * (1 - cripto.taxaCompra)) / cripto.cotacaoInicial;
    char confirmacao;

    if (saldo >= valorCompra) {
        printf("\nVocê está prestes a comprar %.6f %s por R$%.2f\n", valorCripto, cripto.nome, valorCompra);
        printf("Taxa de Compra: %.2f%%\n", cripto.taxaCompra * 100);
        printf("Confirma a compra? (S/N): ");
        scanf(" %c", &confirmacao);

        if (confirmacao == 'S' || confirmacao == 's') {
            FILE *extrato = fopen("extrato.bin", "ab");
            if (extrato == NULL) {
                printf("Erro ao abrir o arquivo de extrato!\n");
                return 0;
            }

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            // Registra a subtração do saldo em reais
            char tipoTransacaoReais = 'S';
            char moedaReais = 'C';
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
            char tipoTransacaoCripto = 'D';
            fwrite(&tipoTransacaoCripto, sizeof(char), 1, extrato);
            fwrite(cripto.nome, sizeof(char), sizeof(cripto.nome), extrato);
            fwrite(cpfDigitado, sizeof(char), 11, extrato);
            fwrite(&valorCripto, sizeof(float), 1, extrato);
            fwrite(&tm.tm_mday, sizeof(int), 1, extrato);
            fwrite(&tm.tm_mon, sizeof(int), 1, extrato);
            fwrite(&tm.tm_year, sizeof(int), 1, extrato);
            fwrite(&tm.tm_hour, sizeof(int), 1, extrato);
            fwrite(&tm.tm_min, sizeof(int), 1, extrato);
            fwrite(&tm.tm_sec, sizeof(int), 1, extrato);

            fclose(extrato);
            printf("Compra de %s realizada com sucesso!\n", cripto.nome);
            return valorCripto;
        } else {
            printf("Compra cancelada.\n");
            return 0;
        }
    } else {
        printf("Saldo insuficiente para a compra!\n");
        return 0;
    }
}



float VenderCripto(float valorVenda, char criptoDesejada, char* cpfDigitado) {
    float saldoCripto = 0.0;
    FILE *extrato;
    float taxa = 0.0;
    float bitcoin_taxa = 3.0 / 100.0;
    float etherium_taxa = 2.0 / 100.0;
    float ripple_taxa = 1.0 / 100.0;
    float valorReais = 0.0;
    char confirmacao;
    char tipoTransacaoReais = 'D';  
    char moedaReais = 'C';
    char tipoTransacaoCripto = 'S';
    float bitcoinCotacao = 350000.0;
    float ethereumCotacao = 14000.0;
    float rippleCotacao = 3.20;

    bitcoinCotacao = AtualizarCotacao(bitcoinCotacao);
    ethereumCotacao = AtualizarCotacao(ethereumCotacao);
    rippleCotacao = AtualizarCotacao(rippleCotacao);

    extrato = fopen("extrato.bin", "ab");

    if (criptoDesejada == 'B') {
        saldoCripto = VerificaSaldo_bitcoin(cpfDigitado);
        taxa = bitcoin_taxa;
        valorReais = (valorVenda * (1 - bitcoin_taxa)) / bitcoinCotacao;
    } 
    else if (criptoDesejada == 'E') {
        saldoCripto = VerificaSaldo_etherium(cpfDigitado);
        taxa = etherium_taxa;
        valorReais = (valorVenda * (1 - etherium_taxa)) / ethereumCotacao;
    } 
    else if (criptoDesejada == 'R') {
        saldoCripto = VerificaSaldo_ripple(cpfDigitado);
        taxa = ripple_taxa;
        valorReais = (valorVenda * (1 - ripple_taxa)) / rippleCotacao;
    } 
    else {
        printf("Criptomoeda inválida!\n");
        fclose(extrato);
        return 0;
    }

    if (saldoCripto >= valorVenda) {
        printf("\nVocê está prestes a vender %.5f de criptomoeda por R$%.5f\n", valorVenda, valorReais);
        printf("Taxa cobrada: %.2f%%\n", taxa * 100.0);
        printf("Confirma a venda? (S/N): ");
        scanf(" %c", &confirmacao);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        if (confirmacao == 'S') {

            fwrite(&tipoTransacaoCripto, sizeof(char), 1, extrato);
            fwrite(&criptoDesejada, sizeof(char), 1, extrato);
            fwrite(cpfDigitado, sizeof(char), 11, extrato);
            fwrite(&valorVenda, sizeof(float), 1, extrato);
            fwrite(&tm.tm_mday, sizeof(int), 1, extrato);
            fwrite(&tm.tm_mon, sizeof(int), 1, extrato);
            fwrite(&tm.tm_year, sizeof(int), 1, extrato);
            fwrite(&tm.tm_hour, sizeof(int), 1, extrato);
            fwrite(&tm.tm_min, sizeof(int), 1, extrato);
            fwrite(&tm.tm_sec, sizeof(int), 1, extrato);

            fwrite(&tipoTransacaoReais, sizeof(char), 1, extrato);
            fwrite(&moedaReais, sizeof(char), 1, extrato);
            fwrite(cpfDigitado, sizeof(char), 11, extrato);
            fwrite(&valorReais, sizeof(float), 1, extrato);
            fwrite(&tm.tm_mday, sizeof(int), 1, extrato);
            fwrite(&tm.tm_mon, sizeof(int), 1, extrato);
            fwrite(&tm.tm_year, sizeof(int), 1, extrato);
            fwrite(&tm.tm_hour, sizeof(int), 1, extrato);
            fwrite(&tm.tm_min, sizeof(int), 1, extrato);
            fwrite(&tm.tm_sec, sizeof(int), 1, extrato);

            fclose(extrato);
            printf("Venda realizada com sucesso!\n");
        } else {
            printf("Venda cancelada.\n");
        }
    } else {
        printf("Saldo insuficiente de criptomoeda para a venda!\n");
        fclose(extrato);
        return 0;
    }

    return 0;
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
    float valorDeposito, valorSaque, valorCompra, valorVenda;
    char senha[5];
    float bitcoin_preco = 10000.0;
    float ethereum_preco = 500.0;
    float ripple_preco = 1.0;
    float bitcoin_atualizado, ethereum_atualizado, ripple_atualizado;
    srand(time(NULL));
    float saldo_bitcoin, saldo_etherium, saldo_ripple;
    char* saldo;
    char nomeCripto[50];

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
        printf("\t1 - Consultar saldo\n");
        printf("\t2 - Consultar extrato\n");
        printf("\t3 - Depositar\n");
        printf("\t4 - Sacar\n");
        printf("\t5 - Comprar criptomoedas\n");
        printf("\t6 - Vender criptomoedas\n");
        printf("\t7 - Atualizar cotação da criptomoeda\n");
        printf("\t0 - Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                saldo = ConsultarSaldo(cpfDigitado);
                printf("%s", saldo);
                free(saldo);
                break;
            case 2:
                ConsultarExtrato(cpfDigitado);
                break;
            case 3:
                printf("\nDigite o valor que deseja depositar em Reais: ");
                scanf("%f", &valorDeposito);
                if (valorDeposito > 0) {
                    Depositar(valorDeposito, cpfDigitado);
                    printf("Valor depositado!\n");
                }
                break;
            case 4:
                printf("\nDigite o valor que deseja sacar em Reais: ");
                scanf("%f", &valorSaque);
                printf("Digite sua Senha: ");
                scanf("%5s", senhaVerificacao);
                if (ValidaIgualdade(senhaDigitada, senhaVerificacao) == 1) {
                    Sacar(valorSaque, senhaDigitada, cpfDigitado);
                } else {
                    printf("Senha incorreta\n");
                }
                break;
            case 5:
                printf("\nCriptomoedas disponíveis:\n");
                ListarCriptomoedas();

                printf("\nDigite o nome da criptomoeda que deseja comprar: ");
                scanf("%s", nomeCripto);

                printf("Digite o valor que deseja gastar (em Reais): ");
                scanf("%f", &valorCompra);

                CompraCripto(valorCompra, nomeCripto, cpfDigitado);
                break;
            case 6:
                printf("\nCriptomoedas disponíveis para vender\n");
                printf("B -> Bitcoin\n");
                printf("E -> Ethereum\n");
                printf("R -> Ripple\n");

                printf("\nDigite qual criptomoeda deseja vender (B, E ou R): ");
                scanf(" %c", &criptoDesejada);

                printf("\nDigite o valor que deseja vender na criptomoeda escolhida: ");
                scanf("%f", &valorVenda);

                printf("Digite sua Senha: ");
                scanf("%5s", senhaVerificacao);

                if (ValidaIgualdade(senhaDigitada, senhaVerificacao) == 1) {
                    VenderCripto(valorVenda, criptoDesejada, cpfDigitado);
                } else {
                    printf("Senha incorreta\n");
                }
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
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }

    return 0;
}