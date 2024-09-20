# include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main(void) {
    char nome[30];
    char cpf[12];

    // abre o arquivo chamado usuarios.txt para adição de novo conteúdo
    FILE *usuarios = fopen("usuarios.txt", "a");

    printf("Digite seu nome: ");
    fgets(nome, 30 , stdin); //captura o nome
    nome[strlen(nome) - 1] = '\0';

    printf("Digite seu CPF (apenas números, sem pontos ou traços): ");
    fgets(cpf, 11 , stdin); //captura o cpf

    // grava no arquivo usuarios.txt
    fprintf(usuarios, "%s - %s\n", nome, cpf);

    //fecha o arquivo criado ou usado
    fclose(usuarios);

    printf("\nNome: %s - ", nome);
    printf("CPF: %s\n", cpf);




    return 0;
}