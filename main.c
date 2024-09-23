# include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main(void) {
    FILE *usuarios;
    int t = 256;
    char linha[t];
    // ler o arquivo txt
    usuarios = fopen("usuarios.txt", "r");
    while (!feof(usuarios)){
       if (fgets(linha, t, usuarios) != NULL) {
            printf("%s", linha);
        }
    }
    fgets(linha, t, usuarios);
    fclose(usuarios);

    return 0;
}