/*Bibliotecas*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Variáveis globais*/
FILE *registroCadastroColaborador;
FILE *registroCadastroCliente;
int contadorCadastroColaboradorEscrita = 0;
int contadorCadastroColaboradorLeitura = 0;
int contadorCadastroClienteEscrita = 0;
int contadorCadastroClienteLeitura = 0;

/*Structs*/
typedef struct colaborador{
    char nome[100], usuario[100], senha[100];
}colaborador;
colaborador colaboradorNovo[500];

typedef struct cliente{
    char nomeRazaoSocial[100];
    char cpfCnpj[100], telefone[100], email[100]; 
    char dataDeNascimentoFundacao[100];
    char dataContratacao[100], sevicoContratado[100];
}cliente;
cliente clienteNovo[500];

/*Prototipos de Funções*/
void escritaArquivoColaborador();
void cadastroColaborador();
void leituraArquivoColaborador();
int login();
int validacaoColaborador();
void relatorioCadastroColaboradores();
void escritaArquivoCliente();
void cadastroCliente();
void leituraArquivoCliente();
void relatorioCadastroCliente();
void menuInicial();

/*Funções*/
void escritaArquivoColaborador() {
    int contadorEscrita = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "a");
    if(registroCadastroColaborador == NULL) {
        printf("Erro ao abrir/criar o arquivo!");
    }
    else{
        while (contadorEscrita < contadorCadastroColaboradorEscrita) {
            fprintf(registroCadastroColaborador, "%s-%s-%s\n", colaboradorNovo[contadorEscrita].nome, colaboradorNovo[contadorEscrita].usuario, colaboradorNovo[contadorEscrita].senha);
            contadorEscrita++;
        }
    }
    fclose(registroCadastroColaborador);
}

void cadastroColaborador() {
    char nome[100], usuario[100], senha[100];
    char resposta;
    contadorCadastroColaboradorEscrita = 0;

    do {
        system("clear");
        printf("\n\t\tCADASTRO DE USUARIO\n");
        printf("\nNome: ");
        scanf(" %99[^\n]", nome);
        printf("Usuario: ");
        scanf(" %99[^\n]", usuario);
        printf("Senha: ");
        scanf(" %99[^\n]", senha);

        strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].nome, nome);
        strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].usuario, usuario);
        strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].senha, senha); 
        contadorCadastroColaboradorEscrita++;

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
        contadorCadastroColaboradorLeitura = 0;
        rewind(registroCadastroColaborador);
        while(fscanf(registroCadastroColaborador, " %99[^-]-%99[^-]-%99[^\n]", colaboradorNovo[contadorCadastroColaboradorLeitura].nome, colaboradorNovo[contadorCadastroColaboradorLeitura].usuario, colaboradorNovo[contadorCadastroColaboradorLeitura].senha) != EOF) {
            contadorCadastroColaboradorLeitura++;
        }
    }
    fclose(registroCadastroColaborador);
}

int login() {
    char usuario[100], senha[100], resposta;

    do{
        system("clear");
        printf("\n\t\tLOGIN\n");
        printf("\n\tUSUARIO: ");
        scanf(" %99[^\n]", usuario);
        printf("\n\tSENHA: ");
        scanf(" %99[^\n]", senha);

        if(validacaoColaborador(usuario, senha) == 0) {
            return 0;
        }
        else {
            system("clear");
            printf("Dados invalidos! Deseja tentar novamente? ");
            scanf(" %c", &resposta);
        
            while(resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                system("clear");
                printf("Resposta invalida! Deseja tentar novamente? ");
                scanf(" %c", &resposta);
            }
        }
    }while(resposta == 's' || resposta == 'S');
}

int validacaoColaborador(char usuario[], char senha[]) {
    int contadorValidacao = 0, teste1, teste2, teste3;
    leituraArquivoColaborador();
    
    while(contadorValidacao <= contadorCadastroColaboradorLeitura) {
        teste1 = strcmp(usuario, colaboradorNovo[contadorValidacao].usuario);
        teste2 = strcmp(senha, colaboradorNovo[contadorValidacao].senha);
        teste3 = teste1 + teste2;

        if(teste3 == 0) {
            contadorValidacao = contadorCadastroColaboradorLeitura + 1;
            return 0;
        }
        contadorValidacao++;
    }
}

void relatorioCadastroColaboradores() {
    int contadorRelatorio = 0;
    char resposta;
    leituraArquivoColaborador();

    system("clear");
    printf("\n\t\tRELATORIO DE USUARIOS\n");
    while(contadorRelatorio <= contadorCadastroColaboradorLeitura) {
        printf("%s\n" ,colaboradorNovo[contadorRelatorio].nome);
        contadorRelatorio++;
    }
}

void escritaArquivoCliente() {
    int contadorEscrita = 0;
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "a");
    if(registroCadastroCliente == NULL) {
        printf("Erro ao abrir/criar o arquivo!");
    }
    else {
        fprintf(registroCadastroCliente, "%s-%s-%s-%s-%s-%s-%s\n", clienteNovo[contadorEscrita].nomeRazaoSocial, clienteNovo[contadorEscrita].cpfCnpj, clienteNovo[contadorEscrita].dataDeNascimentoFundacao, clienteNovo[contadorEscrita].telefone, clienteNovo[contadorEscrita].email, clienteNovo[contadorEscrita].dataContratacao, clienteNovo[contadorEscrita].sevicoContratado);
        contadorEscrita++;
    }
    fclose(registroCadastroCliente);
}

void cadastroCliente() {
    char nomeRazaoSocial[100], cpfCnpj[100], telefone[100], email[100]; 
    char dataDeNascimentoFundacao[100], dataContratacao[100], sevicoContratado[100];
    char resposta;
    contadorCadastroClienteEscrita = 0;

    do {
        system("clear");
        printf("\n\t\tCADASTRO DE CLIENTE\n");
        printf("Nome / Razao Social: ");
        scanf(" %99[^\n]", nomeRazaoSocial);
        printf("CPF/CNPJ: ");
        scanf(" %99[^\n]", cpfCnpj);
        printf("Telefone: ");
        scanf(" %99[^\n]", telefone);
        printf("E-mail: ");
        scanf(" %99[^\n]", email);
        printf("Data de nascimento / Fundacao: ");
        scanf(" %99[^\n]", dataDeNascimentoFundacao);
        printf("Data contratacao: ");
        scanf(" %99[^\n]", dataContratacao);
        printf("Servico contratado: ");
        scanf(" %99[^\n]", sevicoContratado);

        strcpy(clienteNovo[contadorCadastroClienteEscrita].nomeRazaoSocial, nomeRazaoSocial);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].cpfCnpj, cpfCnpj);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].telefone, telefone);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].email, email);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].dataDeNascimentoFundacao, dataDeNascimentoFundacao);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].dataContratacao, dataContratacao);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].sevicoContratado, sevicoContratado);
        contadorCadastroClienteEscrita;

        printf("Deseja cadastrar outro cliente? ");
        scanf(" %c", &resposta);

        while(resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
            printf("Resposta invalida! Deseja cadastrar outro usuario? ");
            scanf(" %c", &resposta);
        }
    }while(resposta == 's' || resposta == 'S');
    escritaArquivoCliente();
}

void leituraArquivoCliente() {
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "r");
    if(registroCadastroCliente == NULL) {
        printf("Erro ao abrir/criar arquivo!");
    }
    else {
        contadorCadastroClienteLeitura = 0;
        rewind(registroCadastroCliente);
        while(fscanf(registroCadastroCliente, " %99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^\n]", clienteNovo[contadorCadastroClienteLeitura].nomeRazaoSocial, clienteNovo[contadorCadastroClienteLeitura].cpfCnpj, clienteNovo[contadorCadastroClienteLeitura].dataDeNascimentoFundacao, clienteNovo[contadorCadastroClienteLeitura].telefone, clienteNovo[contadorCadastroClienteLeitura].email, clienteNovo[contadorCadastroClienteLeitura].dataContratacao, clienteNovo[contadorCadastroClienteLeitura].sevicoContratado) != EOF) {
            contadorCadastroClienteLeitura++;
        }
    }
    fclose(registroCadastroCliente);
}

void relatorioCadastroCliente() {
    int contadorRelatorio = 0;
    char resposta;
    leituraArquivoCliente();

    system("clear");
    printf("\n\t\tRELATORIO DE CLIENTES\n");
    while(contadorRelatorio <= contadorCadastroClienteLeitura) {
        printf("%s\n", clienteNovo[contadorRelatorio].nomeRazaoSocial);
        contadorRelatorio++;
    }
}

void menuInicial() {
    int opcao;
    char resposta;
    do {
        system("clear");
        printf("\n\t\tMENU INICIAL\n");
        printf("\n\nUSUARIO\n-1.Cadastro de usuario\n-2.Relatorio de usuarios\n\nCLIENTE\n-3.Cadastro de cliente\n-4.Relatorio de clientes\n\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastroColaborador();
            break;

            case 2:
                relatorioCadastroColaboradores();
            break;

            case 3:
                cadastroCliente();
            break;

            case 4:
                relatorioCadastroCliente();
            break;

            default:

            break;
        }
        printf("Deseja retornar ao menu inicial? Digite (s) para retornar e (n) para sair: ");
        scanf(" %c", &resposta);
        
        while(resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
            printf("Resposta invalida! Digite (s) para retornar e (n) para sair: ");
            scanf(" %c", &resposta);
        }
    }while(resposta == 's' || resposta == 'S');
}

int main() {

    if(login() == 0) {
        menuInicial();
    }
    
    return 0;
}