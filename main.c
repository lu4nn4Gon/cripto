# include <stdio.h> 
#include <stdlib.h>
#include <string.h>

char *ValidaIgualdade(char* stringOne, char* stringTwo){
    int i = 0;

    while(stringOne[i] != '\0' && stringTwo[i] != '\0'){
    
        if (stringOne[i] != stringTwo[i]) {
            return "Diferentes";
        } i++;
    }
   return "Iguais"; 
    
}

// char Login(char cpf, char senha){
//     FILE *usuarios;
//     char linha[t];
//     char cpf[12], senha[5];

// }


int main(void) {
    // FILE *usuarios;
    // int t = 256;
    // char linha[t];
    // // ler o arquivo txt
    // usuarios = fopen("usuarios.txt", "r");
    // while (!feof(usuarios)){
    //    if (fgets(linha, t, usuarios) != NULL) {
    //         printf("%s", linha);
    //     }
    // }
    // fgets(linha, t, usuarios);
    // fclose(usuarios);

    char stringOne[20];
    char stringTwo[20];

    printf("Digite a primeira frase: ");
    scanf("%s", stringOne);
    printf("Digite a segunda frase: ");
    scanf("%s", stringTwo);

    const char* resultado = ValidaIgualdade(stringOne, stringTwo);
    printf("%s\n", resultado);

    return 0;
}