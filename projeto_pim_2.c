/*Bibliotecas*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*Variáveis globais*/
FILE *registroCadastroColaborador;
FILE *registroCadastroCliente;
int contadorCadastroColaboradorEscrita = 0;
int contadorCadastroColaboradorLeitura = 0;
int contadorCadastroClienteEscrita = 0;
int contadorCadastroClienteLeitura = 0;

/*Structs*/
typedef struct colaborador {
    char nome[100], usuario[100], senha[100];
    int grupo;
} colaborador;
colaborador colaboradorNovo[500];

typedef struct colaboradorLogado {
    char nome[100], usuario[100], senha[100];
    int grupo;
}colaboradorLogado;
colaboradorLogado colaboradorLogado1;

typedef struct cliente {
    char nomeRazaoSocial[100];
    char cpfCnpj[100], telefone[100], email[100];
    char dataDeNascimentoFundacao[100];
    char dataContratacao[100], sevicoContratado[100], usuarioAtendimento[100];
} cliente;
cliente clienteNovo[500];

/*Prototipos de Funções*/
void tabulacaoTitulo();
void cadastroColaborador();
void escritaArquivoColaborador();
void leituraArquivoColaborador();
void relatorioCadastroColaboradores();
int login();
int validacaoColaborador(char usuario[], char senha[]);
void cadastroCliente();
void escritaArquivoCliente();
void leituraArquivoCliente();
void relatorioDeClientes();
void relatorioGeralDeClientes();
void relatorioDeClientesPorUsuario();
void validacaoAtendimento();
void usuarioAdmin();
void menuInicial();

/*Funções*/
void tabulacaoTitulo() {
    printf("\n\t\t\t\t\t");
}

void cadastroColaborador() {
    if(colaboradorLogado1.grupo == 2) {
        printf("\nUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        int grupo;
        char nome[100], usuario[100], senha[100], resposta;
        contadorCadastroColaboradorEscrita = 0;

        do {
            system("clear");
            tabulacaoTitulo();
            printf("CADASTRO DE USUARIO\n");
            printf("\nNome: ");
            scanf(" %99[^\n]", nome);
            printf("Usuario: ");
            scanf(" %99[^\n]", usuario);
            printf("Senha: ");
            scanf(" %99[^\n]", senha);
            tabulacaoTitulo();
            printf("GRUPO\nDigite 1 para usuario administrador e 2 para os demais usuarios: ");
            scanf("%d", &grupo);

            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].nome, nome);
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].usuario, usuario);
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].senha, senha);
            colaboradorNovo[contadorCadastroColaboradorEscrita].grupo = grupo;
            contadorCadastroColaboradorEscrita++;

            printf("Deseja cadastrar outro usuario? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("Resposta invalida! Deseja cadastrar outro usuario? ");
                scanf(" %c", &resposta);
            }
        } while (resposta == 's' || resposta == 'S');
        escritaArquivoColaborador();
    }
}

void escritaArquivoColaborador() {
    int contadorEscrita = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "a");
    if (registroCadastroColaborador == NULL) {
        printf("Erro ao abrir/criar o arquivo!");
    }
    else {
        while (contadorEscrita < contadorCadastroColaboradorEscrita) {
            fprintf(registroCadastroColaborador, "%s-%s-%s-%d\n", colaboradorNovo[contadorEscrita].nome, colaboradorNovo[contadorEscrita].usuario, colaboradorNovo[contadorEscrita].senha, colaboradorNovo[contadorEscrita].grupo);
            contadorEscrita++;
        }
    }
    fclose(registroCadastroColaborador);
}

void leituraArquivoColaborador() {
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "r");
    if (registroCadastroColaborador == NULL) {
        printf("Erro ao abrir/criar o arquivo!");
    }
    else {
        contadorCadastroColaboradorLeitura = 0;
        rewind(registroCadastroColaborador);
        while (fscanf(registroCadastroColaborador, " %99[^-]-%99[^-]-%99[^-]-%d", colaboradorNovo[contadorCadastroColaboradorLeitura].nome, colaboradorNovo[contadorCadastroColaboradorLeitura].usuario, colaboradorNovo[contadorCadastroColaboradorLeitura].senha, &colaboradorNovo[contadorCadastroColaboradorLeitura].grupo) != EOF) {
            contadorCadastroColaboradorLeitura++;
        }
    }
    fclose(registroCadastroColaborador);
}

void relatorioCadastroColaboradores() {
    if(colaboradorLogado1.grupo == 2) {
        printf("\nUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        leituraArquivoColaborador();
        int contadorRelatorio = 0;
        char resposta;

        system("clear");
        tabulacaoTitulo();
        printf("RELATORIO DE USUARIOS\n");
        while (contadorRelatorio < contadorCadastroColaboradorLeitura) {
            printf("%s\n", colaboradorNovo[contadorRelatorio].nome);
            contadorRelatorio++;
        }
    }
}

int login() {
    char usuario[100], senha[100], resposta;

    do {
        system("clear");
        tabulacaoTitulo();
        printf("LOGIN\n");
        printf("\n\tUSUARIO: ");
        scanf(" %99[^\n]", usuario);
        printf("\n\tSENHA: ");
        scanf(" %99[^\n]", senha);

        if (validacaoColaborador(usuario, senha) == 0) {
            return 0;
        }
        else {
            system("clear");
            printf("Dados invalidos! Deseja tentar novamente? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                system("clear");
                printf("Resposta invalida! Deseja tentar novamente? ");
                scanf(" %c", &resposta);
            }
        }
    } while (resposta == 's' || resposta == 'S');
}

int validacaoColaborador(char usuario[], char senha[]) {
    leituraArquivoColaborador();
    int contadorValidacao = 0, teste1, teste2, teste3;

    while (contadorValidacao <= contadorCadastroColaboradorLeitura) {
        teste1 = strcmp(usuario, colaboradorNovo[contadorValidacao].usuario);
        teste2 = strcmp(senha, colaboradorNovo[contadorValidacao].senha);
        teste3 = teste1 + teste2;

        if (teste3 == 0) {
            strcpy(colaboradorLogado1.nome, colaboradorNovo[contadorValidacao].nome);
            strcpy(colaboradorLogado1.usuario, colaboradorNovo[contadorValidacao].usuario);
            strcpy(colaboradorLogado1.senha, colaboradorNovo[contadorValidacao].senha);
            colaboradorLogado1.grupo = colaboradorNovo[contadorValidacao].grupo;
            contadorValidacao = contadorCadastroColaboradorLeitura + 1;
            return 0;
        }
        contadorValidacao++;
    }
}

void cadastroCliente() {
    char nomeRazaoSocial[100], cpfCnpj[100], telefone[100], email[100];
    char dataDeNascimentoFundacao[100], dataContratacao[100], sevicoContratado[100];
    char usuarioAtendimento[100];
    char resposta;
    contadorCadastroClienteEscrita = 0;

    do {
        system("clear");
        tabulacaoTitulo();
        printf("CADASTRO DE CLIENTE\n");
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
        strcpy(clienteNovo[contadorCadastroClienteEscrita].usuarioAtendimento, colaboradorLogado1.usuario);
        contadorCadastroClienteEscrita++;

        printf("Deseja cadastrar outro cliente? ");
        scanf(" %c", &resposta);

        while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
            printf("Resposta invalida! Deseja cadastrar outro usuario? ");
            scanf(" %c", &resposta);
        }
    } while (resposta == 's' || resposta == 'S');
    escritaArquivoCliente();
}

void escritaArquivoCliente() {
    int contadorEscrita = 0;
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "a");
    if (registroCadastroCliente == NULL) {
        printf("Erro ao abrir/criar o arquivo!");
    }
    else {
        while(contadorEscrita < contadorCadastroClienteEscrita) {
            fprintf(registroCadastroCliente, "%s-%s-%s-%s-%s-%s-%s-%s\n", clienteNovo[contadorEscrita].nomeRazaoSocial, clienteNovo[contadorEscrita].cpfCnpj, clienteNovo[contadorEscrita].dataDeNascimentoFundacao, clienteNovo[contadorEscrita].telefone, clienteNovo[contadorEscrita].email, clienteNovo[contadorEscrita].dataContratacao, clienteNovo[contadorEscrita].sevicoContratado, clienteNovo[contadorEscrita].usuarioAtendimento);
            contadorEscrita++;
        }
    }
    fclose(registroCadastroCliente);
}

void leituraArquivoCliente() {
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "r");
    if (registroCadastroCliente == NULL) {
        printf("Erro ao abrir/criar arquivo!");
    }
    else {
        contadorCadastroClienteLeitura = 0;
        rewind(registroCadastroCliente);
        while (fscanf(registroCadastroCliente, " %99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^\n]", clienteNovo[contadorCadastroClienteLeitura].nomeRazaoSocial, clienteNovo[contadorCadastroClienteLeitura].cpfCnpj, clienteNovo[contadorCadastroClienteLeitura].dataDeNascimentoFundacao, clienteNovo[contadorCadastroClienteLeitura].telefone, clienteNovo[contadorCadastroClienteLeitura].email, clienteNovo[contadorCadastroClienteLeitura].dataContratacao, clienteNovo[contadorCadastroClienteLeitura].sevicoContratado, clienteNovo[contadorCadastroClienteLeitura].usuarioAtendimento) != EOF) {
            contadorCadastroClienteLeitura++;
        }
    }
    fclose(registroCadastroCliente);
}

void relatorioDeClientes() {
    if(access("arquivoCadastroCliente.txt", F_OK) == -1) {
        printf("\nNenhum cadastro encontrado\n");
    }
    else {
        leituraArquivoCliente();
        leituraArquivoColaborador();

        int contadorRelatorio = 0, teste;

        system("clear");
        tabulacaoTitulo();
        printf("RELATORIO DE CLIENTES\n");

        while(contadorRelatorio < contadorCadastroClienteLeitura) {
            teste = strcmp(colaboradorLogado1.usuario, clienteNovo[contadorRelatorio].usuarioAtendimento);
            if(teste == 0) {
                printf("%s\n", clienteNovo[contadorRelatorio].nomeRazaoSocial);
            }
            contadorRelatorio++;
        }
    }
}

void relatorioGeralDeClientes() {
    if(colaboradorLogado1.grupo == 2) {
        printf("\nUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
            printf("\nNenhum cadastro encontrado\n");
        }
        else {
            leituraArquivoCliente();
            int contadorRelatorio = 0;
            char resposta;

            system("clear");
            tabulacaoTitulo();
            printf("RELATORIO GERAL DE CLIENTES\n");
            while (contadorRelatorio < contadorCadastroClienteLeitura) {
                printf("%s\n", clienteNovo[contadorRelatorio].nomeRazaoSocial);
                contadorRelatorio++;
            }
        }
    }
}

void relatorioDeClientesPorUsuario()
{
    if(colaboradorLogado1.grupo == 2) {
        printf("\nUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
            printf("\nNenhum cadastro encontrado\n");
        }
        else {
            leituraArquivoColaborador();
            leituraArquivoCliente();

            int contadorRelatorio = 0, teste;
            char usuario[100];

            system("clear");
            printf("Informe o usuario: ");
            scanf(" %99[^\n]", usuario);

            tabulacaoTitulo();
            printf("RELATORIO DE CLIENTES POR USUARIO\n\n");
            while (contadorRelatorio < contadorCadastroClienteLeitura) {
                teste = strcmp(usuario, clienteNovo[contadorRelatorio].usuarioAtendimento);
                if (teste == 0) {
                    printf("%s\n", clienteNovo[contadorRelatorio].nomeRazaoSocial);
                }
                contadorRelatorio++;
            }
        }
    }
}

void usuarioAdmin() {
    if (access("arquivoCadastroColaborador.txt", R_OK) == -1) {
        registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "a");
        int grupo;
        char nomeAdmin[100], usuarioAdmin[100], senhaAdmin[100];
        strcpy(nomeAdmin, "admin");
        strcpy(usuarioAdmin, "admin");
        strcpy(senhaAdmin, "admin");
        grupo = 1;

        fprintf(registroCadastroColaborador, "%s-%s-%s-%d\n", nomeAdmin, usuarioAdmin, senhaAdmin, grupo);
        fclose(registroCadastroColaborador);
    }
}

void menuInicial() {
    int opcao;
    char resposta, respostaSaida;
    do {
        system("clear");
        tabulacaoTitulo();
        printf("MENU INICIAL\n");
        printf("\n\n\n-1.Cadastro de usuario\n-2.Relatorio de usuarios\n-3.Cadastro de cliente\n-4.Relatorio de clientes\n-5.Relatorio geral de clientes\n-6.Relatorio de clientes por usuario\n-7.Sair\n\nOpcao: ");
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
            relatorioDeClientes();
            break;

        case 5:
            relatorioGeralDeClientes();
            break;

        case 6:
            relatorioDeClientesPorUsuario();
            break;
        
        case 7:
            printf("Deseja realmente sair?: ");
            scanf(" %c", &resposta);
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
        
        if(opcao != 7) {
            printf("Deseja retornar ao menu inicial? Digite (s) para retornar e (n) para sair: ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("Resposta invalida! Digite (s) para retornar e (n) para sair: ");
                scanf(" %c", &resposta);
            }
        }
        else {
            resposta = 'n';
        }
    } while (resposta == 's' || resposta == 'S');
}

/*Função principal main*/
int main() {

    usuarioAdmin();

    if (login() == 0) {
        menuInicial();
    }

    return 0;
}
