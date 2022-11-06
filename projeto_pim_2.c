/*Bibliotecas*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Variáveis globais*/
FILE *registroCadastroColaborador;
int contadorCadastroEscrita = 0;
int contadorCadastroLeitura = 0;

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
void leituraArquivoColaborador();
int login();
int validacaoColaborador();

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

void leituraArquivoColaborador() {
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "r");
    if(registroCadastroColaborador == NULL) {
        printf("Erro ao abrir/criar o arquivo!");
    }
    else {
        contadorCadastroLeitura = 0;
        rewind(registroCadastroColaborador);
        while(fscanf(registroCadastroColaborador, " %99[^-]-%99[^-]-%99[^\n]", colaboradorNovo[contadorCadastroLeitura].nome, colaboradorNovo[contadorCadastroLeitura].usuario, colaboradorNovo[contadorCadastroLeitura].senha) != EOF) {
        contadorCadastroLeitura++;
        }
    }
    fclose(registroCadastroColaborador);

}

int login() {
    char usuario[100], senha[100], resposta;

    do{
        printf("\n\t\tLOGIN\n");
        printf("\n\tUSUARIO: ");
        scanf(" %99[^\n]", usuario);
        printf("\n\tSENHA: ");
        scanf(" %99[^\n]", senha);

        if(validacaoColaborador(usuario, senha) == 0) {
            return 0;
        }
        else {
            printf("Dados invalidos! Deseja tentar novamente? ");
            scanf(" %c", &resposta);
        
            while(resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("Resposta invalida! Deseja tentar novamente? ");
                scanf(" %c", &resposta);
            }
        }

    }while(resposta == 's' || resposta == 'S');
    
}

int validacaoColaborador(char usuario[], char senha[]) {
    int contadorValidacao = 0, teste1, teste2, teste3;
    leituraArquivoColaborador();
    
    while(contadorValidacao <= contadorCadastroLeitura) {
        teste1 = strcmp(usuario, colaboradorNovo[contadorValidacao].usuario);
        teste2 = strcmp(senha, colaboradorNovo[contadorValidacao].senha);
        teste3 = teste1 + teste2;

        if(teste3 == 0) {
            contadorValidacao = contadorCadastroLeitura + 1;
            return 0;
        }
        contadorValidacao++;
    }

}

int main() {

    if(login() == 0) {
        printf("\n\tAcesso permitido.\n");
    }

    /*cadastroColaborador();
    leituraArquivoColaborador();*/

    
    return 0;
}