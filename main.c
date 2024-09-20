# include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main(void) {
    char nome[30];
    char cpf[12];

    // abre o arquivo chamado usuarios.txt para adição de novo conteúdo
    FILE *usuarios = fopen("usuarios.txt", "a");

    printf("Digite seu nome: ");
    fgets(nome, 30 , stdin);
    nome[strlen(nome) - 1] = '\0';

    printf("Digite seu CPF (apenas números, sem pontos ou traços): ");
    fgets(cpf, 11 , stdin);

    // grava no arquivo usuarios.txt
    fprintf(usuarios, "%s - %s\n", nome, cpf);

    fclose(usuarios);

    printf("\nNome: %s - ", nome);
    printf("CPF: %s\n", cpf);




    return 0;
}