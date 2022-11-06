/*Bibliotecas*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Variáveis globais*/
FILE *registroCadastroColaborador;
int contadorCadastroEscrita;

/*Structs*/
typedef struct colaborador{
    char nome[100];
    char usuario[100];
    char senha[100];
}colaborador;
colaborador colaboradorNovo[500];

/*Prototipos de Funções*/
void escritaArquivoColaborador();
void cadastroColaborador();

/*Funções*/
void escritaArquivoColaborador() {
    int contadorEscrita = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "a");
    if(registroCadastroColaborador == NULL) {
        printf("Erro ao abrir/criar o arquivo!");
    }
    else{
        while (contadorEscrita < contadorCadastroEscrita) {
            fprintf(registroCadastroColaborador, "%s-%s-%s\n", colaboradorNovo[contadorEscrita].nome, colaboradorNovo[contadorEscrita].usuario, colaboradorNovo[contadorEscrita].senha);
            contadorEscrita++;
        }
    }
    
    fclose(registroCadastroColaborador);
}

void cadastroColaborador() {
    char nome[100], usuario[100], senha[100];
    char resposta;
    int contadorCadastro = 0;

    do {
        printf("\n\t\tCADASTRO DE USUARIO\n");
        printf("Nome: ");
        scanf(" %99[^\n]", nome);
        printf("Usuario: ");
        scanf(" %99[^\n]", usuario);
        printf("Senha: ");
        scanf(" %99[^\n]", senha);

        strcpy(colaboradorNovo[contadorCadastroEscrita].nome, nome);
        strcpy(colaboradorNovo[contadorCadastroEscrita].usuario, usuario);
        strcpy(colaboradorNovo[contadorCadastroEscrita].senha, senha); 
        contadorCadastroEscrita++;

        printf("Deseja cadastrar outro usuario? ");
        scanf(" %c", &resposta);

        while(resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
            printf("Resposta invalida! Deseja cadastrar outro usuario? ");
            scanf(" %c", &resposta);
        }

    }while(resposta == 's' || resposta == 'S');

    escritaArquivoColaborador();
}

int main() {

    cadastroColaborador();

    return 0;
}