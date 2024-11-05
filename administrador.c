#include <stdio.h>

int main() {
    FILE *file = fopen("administradores.bin", "wb");
    
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    char cpf1[] = "11122233344";
    char senha1[] = "1234";     
    
    char cpf2[] = "55566677788";
    char senha2[] = "9876";

    // primeiro administrador
    fwrite(cpf1, sizeof(char), 11, file);
    fwrite(senha1, sizeof(char), 4, file);

    // segundo administrador
    fwrite(cpf2, sizeof(char), 11, file);
    fwrite(senha2, sizeof(char), 4, file);

    fclose(file);
    printf("Arquivo administradores.bin criado com sucesso.\n");

    return 0;
}
