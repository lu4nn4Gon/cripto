# include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int ValidaIgualdade(char* stringOne, char* stringTwo){
    int i = 0;

    while(stringOne[i] != '\0' && stringTwo[i] != '\0'){

        if (stringOne[i] != stringTwo[i]) {
            return 0;
        } i++;
    }
   return 1; 
    
}

char* Login(char* cpfDigitado, char* senhaDigitada){
    FILE *usuarios;
    int t = 256;
    char linha[t];
    char cpf[12];
    char senha[5];

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
            return "Tem"; 
        }
    }

    fclose(usuarios);
    return "Nao tem"; 
}




int main(void) {
    char cpfDigitado[12];
    char senhaDigitada[5];

    printf("Digite o CPF: ");
    scanf("%11s", cpfDigitado);  
    printf("Digite a senha: ");
    scanf("%5s", senhaDigitada); 

    const char* resultado = Login(cpfDigitado, senhaDigitada);
    printf("%s\n", resultado);

    return 0;
}