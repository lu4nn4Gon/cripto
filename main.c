# include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main(void) {
    char cpf[13];
    char senha[11];

    // abre o arquivo chamado usuarios.txt para adição de novo conteúdo
    FILE *usuarios = fopen("usuarios.txt", "a");

    printf("Digite seu CPF (apenas números, sem pontos ou traços): ");
    fgets(cpf, 13 , stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    printf("Digite sua Senha: ");
    fgets(senha, 11 , stdin);
    senha[strcspn(senha, "\n")] = '\0';


    if (senha[0] == '\0'){
        printf("Campo Senha vazio");
    } else if (cpf[0] == '\0') {
        printf("Campo CPF vazio");
    } else {
        // grava no arquivo usuarios.txt
        fprintf(usuarios, "%s - %s\n", cpf, senha);
    }

    fclose(usuarios);

    return 0;
}