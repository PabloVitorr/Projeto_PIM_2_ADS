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

typedef struct auterarSenha {
    char novaSenhaTeste1[100];
    char novaSenhaTeste2[100];
}auterarSenha;
auterarSenha cadastroNovaSenha;

typedef struct colaboradorLogado {
    char nome[100], usuario[100], senha[100];
    int grupo;
}colaboradorLogado;
colaboradorLogado colaboradorLogado1;

typedef struct cliente {
    char nomeRazaoSocial[100];
    char cnpj[100], telefone[100], email[100];
    char dataDeNascimentoFundacao[100];
    char dataContratacao[100], sevicoContratado[100], usuarioAtendimento[100];
    int status;
    double mensalidade;
} cliente;
cliente clienteNovo[500];

/*Prototipos de Funções*/
void tabQuatro();
void tabCinco();
void tabSeis();
void linhaDuas();
void linhaTres();
void erroAberturaCriacaoArquivo();
void cadastroColaborador();
void alterarSenhaColaborador();
void edicaoArquivoColaborador();
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
void atualizacaoAreceberMesAtual();
void validacaoAtendimento();
void usuarioAdmin();
void barraDeStatus();
void manual();
void contatoSuporte();
void menuAjuda();
void menuInicial();

/*Funções*/
void tabQuatro() {
    printf("\t\t\t\t");
}

void tabCinco() {
    printf("\t\t\t\t\t");
}

void tabSeis() {
    printf("\t\t\t\t\t\t");
}

void linhaDuas() {
    printf("\n\n");
}

void linhaTres() {
    printf("\n\n\n");
}

void erroAberturaCriacaoArquivo() {
    system("clear");
    linhaTres();
    tabCinco();
    printf("Erro ao abrir/criar o arquivo!");
    getchar();getchar();
}

void cadastroColaborador() {
    if(colaboradorLogado1.grupo == 2) {
        printf("\tUsuario sem permissao!\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        int grupo;
        char nome[100], usuario[100], senha[100], resposta;
        contadorCadastroColaboradorEscrita = 0;

        do {
            system("clear");
            barraDeStatus();
            tabSeis();
            printf("CADASTRO DE USUARIO");
            linhaTres();
            printf("\tNOME: ");
            scanf(" %99[^\n]", nome);
            printf("\tUSUARIO: ");
            scanf(" %99[^\n]", usuario);
            printf("\tSENHA: ");
            scanf(" %99[^\n]", senha);
            printf("\tGRUPO, DIGITE 1 PARA ADMINISTRADOR E 2 PARA DEMAIS USUARIOS: ");
            scanf("%d", &grupo);

            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].nome, nome);
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].usuario, usuario);
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].senha, senha);
            colaboradorNovo[contadorCadastroColaboradorEscrita].grupo = grupo;
            contadorCadastroColaboradorEscrita++;

            linhaDuas();
            printf("\tDeseja cadastrar outro usuario ""s"" sim ""n"" nao? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("\tResposta invalida! Deseja cadastrar outro usuario? ");
                scanf(" %c", &resposta);
            }
        } while (resposta == 's' || resposta == 'S');
        escritaArquivoColaborador();
    }
}

void alterarSenhaColaborador() {
    int contadorAlterarSenha = 0;
    int validacao;
    char resposta;

    do {
        leituraArquivoColaborador();

        system("clear");
        barraDeStatus();
        tabSeis();
        printf("AUTERACAO DE SENHA");
        linhaTres();
        printf("\tDIGITE A NOVA SENHA: ");
        scanf(" %99[^\n]", cadastroNovaSenha.novaSenhaTeste1);
        printf("\tDIGITE NOVAMENTE PARA VALIDACAO: ");
        scanf(" %99[^\n]", cadastroNovaSenha.novaSenhaTeste2);

        validacao = strcmp(cadastroNovaSenha.novaSenhaTeste1, cadastroNovaSenha.novaSenhaTeste2);

        if(validacao != 0) {
            linhaDuas();
            printf("\tSenhas divergentes!\n");
            printf("\tDeseja tentar novamente? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("\tResposta invalida! Deseja cadastrar outro usuario? ");
                scanf(" %c", &resposta);
            }
        }
        else {
            linhaDuas();
            printf("\tSenha cadastrada com sucesso!\n");
        }
    } while ((resposta == 's' || resposta == 'S') && validacao != 0);

    while(contadorAlterarSenha < contadorCadastroColaboradorLeitura) {
        validacao = strcmp(colaboradorLogado1.usuario, colaboradorNovo[contadorAlterarSenha].usuario);
        if(validacao == 0) {
            strcpy(colaboradorNovo[contadorAlterarSenha].senha, cadastroNovaSenha.novaSenhaTeste1); 
            contadorAlterarSenha = contadorCadastroColaboradorLeitura + 1;
        }
        contadorAlterarSenha++;
    }
    edicaoArquivoColaborador();
}

void edicaoArquivoColaborador() {
    int contadorEdicao = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "w");
    if (registroCadastroColaborador == NULL) {
        erroAberturaCriacaoArquivo();
    }
    else {
        while (contadorEdicao < contadorCadastroColaboradorLeitura) {
            fprintf(registroCadastroColaborador, "%s-%s-%s-%d\n", colaboradorNovo[contadorEdicao].nome, colaboradorNovo[contadorEdicao].usuario, colaboradorNovo[contadorEdicao].senha, colaboradorNovo[contadorEdicao].grupo);
            contadorEdicao++;
        }
    }
    fclose(registroCadastroColaborador);
}

void escritaArquivoColaborador() {
    int contadorEscrita = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "a");
    if (registroCadastroColaborador == NULL) {
        erroAberturaCriacaoArquivo();
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
        erroAberturaCriacaoArquivo();
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
        printf("\tUsuario sem permissao!\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        leituraArquivoColaborador();
        int contadorRelatorio = 0;
        char resposta;

        system("clear");
        barraDeStatus();
        tabSeis();
        printf("RELATORIO DE USUARIOS");
        linhaTres();
        while (contadorRelatorio < contadorCadastroColaboradorLeitura) {
            printf("\tNOME: %s\tUSUARIO: %s\tGRUPO DE PERMISSOES: %d", colaboradorNovo[contadorRelatorio].nome, colaboradorNovo[contadorRelatorio].usuario, colaboradorNovo[contadorRelatorio].grupo);
            linhaDuas();
            contadorRelatorio++;
        }
        linhaDuas();
    }
}

int login() {
    char usuario[100], senha[100], resposta;

    do {
        system("clear");
        tabSeis();
        printf("LOGIN");
        linhaTres();
        tabCinco();
        printf("USUARIO: ");
        scanf(" %99[^\n]", usuario);
        linhaDuas();
        tabCinco();
        printf("SENHA: ");
        scanf(" %99[^\n]", senha);

        if (validacaoColaborador(usuario, senha) == 0) {
            return 0;
        }
        else {
            linhaDuas();
            tabQuatro();
            printf("Dados invalidos! Deseja tentar novamente? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                tabQuatro();
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
    char nomeRazaoSocial[100], cnpj[100], telefone[100], email[100];
    char dataDeNascimentoFundacao[100], dataContratacao[100], sevicoContratado[100];
    char usuarioAtendimento[100], resposta;
    int status;
    double mensalidade;
    contadorCadastroClienteEscrita = 0;

    do {
        system("clear");
        barraDeStatus();
        tabSeis();
        printf("CADASTRO DE CLIENTE");
        linhaTres();
        printf("\tRAZAO SOCIAL: ");
        scanf(" %99[^\n]", nomeRazaoSocial);
        printf("\tCNPJ: ");
        scanf(" %99[^\n]", cnpj);
        printf("\tTELEFONE: ");
        scanf(" %99[^\n]", telefone);
        printf("\tE-MAIL: ");
        scanf(" %99[^\n]", email);
        printf("\tDATA DE FUNDACAO: ");
        scanf(" %99[^\n]", dataDeNascimentoFundacao);
        printf("\tDATA DE CONTRATACAO DO SERVICO: ");
        scanf(" %99[^\n]", dataContratacao);
        printf("\tSERVICO CONTRATADO: ");
        scanf(" %99[^\n]", sevicoContratado);
        printf("\tVALOR MENSAL SERVICO CONTRATADO: R$ ");
        scanf("%lf", &mensalidade);
        printf("\tSTATUS ""1"" EM ANDAMENTO ""2"" FINALIZADO: ");
        scanf("%d", &status);

        strcpy(clienteNovo[contadorCadastroClienteEscrita].nomeRazaoSocial, nomeRazaoSocial);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].cnpj, cnpj);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].telefone, telefone);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].email, email);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].dataDeNascimentoFundacao, dataDeNascimentoFundacao);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].dataContratacao, dataContratacao);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].sevicoContratado, sevicoContratado);
        clienteNovo[contadorCadastroClienteEscrita].mensalidade = mensalidade;
        strcpy(clienteNovo[contadorCadastroClienteEscrita].usuarioAtendimento, colaboradorLogado1.usuario);
        clienteNovo[contadorCadastroClienteEscrita].status = status;
        contadorCadastroClienteEscrita++;

        linhaDuas();
        printf("\tDeseja cadastrar outro cliente? ");
        scanf(" %c", &resposta);

        while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
            printf("\tResposta invalida! Deseja cadastrar outro usuario? ");
            scanf(" %c", &resposta);
        }
    } while (resposta == 's' || resposta == 'S');
    escritaArquivoCliente();
}

void escritaArquivoCliente() {
    int contadorEscrita = 0;
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "a");
    if (registroCadastroCliente == NULL) {
        erroAberturaCriacaoArquivo();
    }
    else {
        while(contadorEscrita < contadorCadastroClienteEscrita) {
            fprintf(registroCadastroCliente, "%s-%s-%s-%s-%s-%s-%s-%.2lf-%s-%d\n", clienteNovo[contadorEscrita].nomeRazaoSocial, clienteNovo[contadorEscrita].cnpj, clienteNovo[contadorEscrita].dataDeNascimentoFundacao, clienteNovo[contadorEscrita].telefone, clienteNovo[contadorEscrita].email, clienteNovo[contadorEscrita].dataContratacao, clienteNovo[contadorEscrita].sevicoContratado, clienteNovo[contadorEscrita].mensalidade, clienteNovo[contadorEscrita].usuarioAtendimento, clienteNovo[contadorEscrita].status);
            contadorEscrita++;
        }
    }
    fclose(registroCadastroCliente);
}

void leituraArquivoCliente() {
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "r");
    if (registroCadastroCliente == NULL) {
        erroAberturaCriacaoArquivo();
    }
    else {
        contadorCadastroClienteLeitura = 0;
        
        rewind(registroCadastroCliente);
        while (fscanf(registroCadastroCliente, " %99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^-]-%99[^-]-%lf-%99[^-]-%d", clienteNovo[contadorCadastroClienteLeitura].nomeRazaoSocial, clienteNovo[contadorCadastroClienteLeitura].cnpj, clienteNovo[contadorCadastroClienteLeitura].dataDeNascimentoFundacao, clienteNovo[contadorCadastroClienteLeitura].telefone, clienteNovo[contadorCadastroClienteLeitura].email, clienteNovo[contadorCadastroClienteLeitura].dataContratacao, clienteNovo[contadorCadastroClienteLeitura].sevicoContratado, &clienteNovo[contadorCadastroClienteLeitura].mensalidade,clienteNovo[contadorCadastroClienteLeitura].usuarioAtendimento, &clienteNovo[contadorCadastroClienteLeitura].status) != EOF) {
            contadorCadastroClienteLeitura++;
        }
    }
    fclose(registroCadastroCliente);
}

void relatorioDeClientes() {
    if(access("arquivoCadastroCliente.txt", F_OK) == -1) {
        printf("\n\tNenhum cadastro encontrado\n");
    }
    else {
        leituraArquivoCliente();
        leituraArquivoColaborador();

        int contadorRelatorio = 0, teste;

        system("clear");
        barraDeStatus();
        tabSeis();
        printf("RELATORIO DE CLIENTES");
        linhaTres();

        while(contadorRelatorio < contadorCadastroClienteLeitura) {
            teste = strcmp(colaboradorLogado1.usuario, clienteNovo[contadorRelatorio].usuarioAtendimento);
            if(teste == 0) {
                printf("\tRAZAO SOCIAL: %s\tCNPJ: %s\n\tTELEFONE: %s\t\tE-MAIL %s\n\tDATA DE FUNDACAO: %s\tDATA DE CONTRATACAO: %s\n\tSERVICO CONTRATADO: %s\tVALOR MENSAL: R$ %.2lf\n\tUSUARIO RESPONSAVEL: %s\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].dataDeNascimentoFundacao, clienteNovo[contadorRelatorio].dataContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade, clienteNovo[contadorRelatorio].usuarioAtendimento);
                if(clienteNovo[contadorRelatorio].status == 0) {
                    printf("Em andamento");
                    linhaDuas();
                }
                else {
                    printf("Finalizado");
                    linhaDuas();
                }
            }
            contadorRelatorio++;
        }
    }
}

void relatorioGeralDeClientes() {
    if(colaboradorLogado1.grupo == 2) {
        printf("\n\tUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
            printf("\n\tNenhum cadastro encontrado\n");
        }
        else {
            leituraArquivoCliente();
            int contadorRelatorio = 0;
            char resposta;

            system("clear");
            barraDeStatus();
            tabSeis();
            printf("RELATORIO GERAL DE CLIENTES");
            linhaTres();

            while (contadorRelatorio < contadorCadastroClienteLeitura) {
                printf("\tRAZAO SOCIAL: %s\tCNPJ: %s\n\tTELEFONE: %s\tE-MAIL%s\n\tDATA DE FUNDACAO: %s\tDATA DE CONTRATACAO: %s\n\tSERVICO CONTRATADO: %s\tVALOR MENSAL: R$ %.2lf\n\tUSUARIO RESPONSAVEL: %s\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].dataDeNascimentoFundacao, clienteNovo[contadorRelatorio].dataContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade,clienteNovo[contadorRelatorio].usuarioAtendimento);
                if(clienteNovo[contadorRelatorio].status == 0) {
                    printf("Em andamento");
                    linhaDuas();
                }
                else {
                    printf("Finalizado");
                    linhaDuas();
                }
                contadorRelatorio++;
            }
        }
    }
}

void relatorioDeClientesPorUsuario()
{
    if(colaboradorLogado1.grupo == 2) {
        printf("\n\tUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
            printf("\n\tNenhum cadastro encontrado\n");
        }
        else {
            leituraArquivoColaborador();
            leituraArquivoCliente();

            int contadorRelatorio = 0, teste;
            char usuario[100];

            system("clear");
            barraDeStatus();
            tabSeis();
            printf("RELATORIO DE CLIENTES POR USUARIO");
            linhaTres();
            printf("\tINFORME O USUARIO: ");
            scanf(" %99[^\n]", usuario);
            linhaDuas();

            while (contadorRelatorio < contadorCadastroClienteLeitura) {
                teste = strcmp(usuario, clienteNovo[contadorRelatorio].usuarioAtendimento);
                if (teste == 0) {
                    printf("\tRAZAO SOCIAL: %s\tCNPJ: %s\n\tTELEFONE: %s\tE-MAIL%s\n\tDATA DE FUNDACAO: %s\tDATA DE CONTRATACAO: %s\n\tSERVICO CONTRATADO: %s\tVALOR MENSAL: R$ %.2lf\n\tUSUARIO RESPONSAVEL: %s\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].dataDeNascimentoFundacao, clienteNovo[contadorRelatorio].dataContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade,clienteNovo[contadorRelatorio].usuarioAtendimento);
                    if(clienteNovo[contadorRelatorio].status == 0) {
                        printf("Em andamento");
                        linhaDuas();
                    }
                    else {
                        printf("Finalizado");
                        linhaDuas();
                    }
                }
                contadorRelatorio++;
            }
        }
    }
}

void atualizacaoAreceberMesAtual() {
    if(colaboradorLogado1.grupo == 2) {
        printf("\nUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
            printf("\nNenhum cadastro encontrado\n");
        }
        else {
            leituraArquivoCliente();

            float totalAreceber = 0;
            int contadorRelatorio = 0;

            while(contadorRelatorio < contadorCadastroClienteLeitura) {
                if(clienteNovo[contadorRelatorio].status == 1) {
                    totalAreceber = totalAreceber + clienteNovo[contadorRelatorio].mensalidade;
                }
                contadorRelatorio++;
            }
            system("clear");
            barraDeStatus();
            tabSeis();
            printf("ATUALIZACAO MENSAL A RECEBER");
            linhaDuas();
            tabSeis();
            printf("\tTOTAL: R$ %.2lf", totalAreceber);
            linhaTres();
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

void barraDeStatus() {
    printf("\tNOME: %s \tUSUARIO: %s\n\n\n", colaboradorLogado1.nome,colaboradorLogado1.usuario);
}

void manual() {
    system("clear");
    barraDeStatus();
    linhaDuas();
    printf("\tPressione qualquer teclar para continuar...");
    getchar();getchar();
}

void contatoSuporte() {
    system("clear");
    barraDeStatus();
    tabSeis();
    printf("CONTATOS SUPORTE");
    linhaTres();
    printf("\tE-MAIL: suporte@suporte.com.br\tCHAT: chat.com.br\n");
    printf("\tTELEFONE: (00) 0000-0000\tCELULAR: (00)00000-0000\n");
    linhaDuas();
    printf("\tPressione qualquer tecla para continuar...");
    getchar();getchar();
}

void menuAjuda() {
    int opcao;
    
    system("clear");
    barraDeStatus();
    tabSeis();
    printf("MENU AJUDA");
    linhaTres();
    printf("\t-1.Contato Suporte\n\t-2.Manual de instrucoes\n\n\tOpcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        
        case 1:
            contatoSuporte();
            break;      
        case 2:
            manual();
            break;
        default :
            printf("Opcao invalida!\n");
            break;
    }
}

void menuInicial() {
    int opcao;
    char resposta;
    do {
        system("clear");
        barraDeStatus();
        tabSeis();
        printf("MENU INICIAL");
        linhaTres();
        printf("\t-1.Cadastro de usuario\n\t-2.Alterar senha\n\t-3.Relatorio de usuarios\n\t-4.Cadastro de cliente\n\t-5.Relatorio de clientes\n\t-6.Relatorio geral de clientes\n\t-7.Relatorio de clientes por usuario\n\t-8.Atualizacao a receber mes atual\n\t+9.Ajuda\n\t-10.Sair\n\n\tOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        
        case 1:
            cadastroColaborador();
            break;

        case 2:
            alterarSenhaColaborador();
            break;
        case 3:
            relatorioCadastroColaboradores();
            break;
        case 4:
            cadastroCliente();
            break;
        case 5:
            relatorioDeClientes();
            break;
        case 6:
            relatorioGeralDeClientes();
            break;
        case 7:
            relatorioDeClientesPorUsuario();
            break;
        case 8:
            atualizacaoAreceberMesAtual();
            break;
        case 9:
            menuAjuda();
            break;
        case 10:
            printf("\tDeseja realmente sair?: ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("\tResposta invalida! Digite (s) para retornar e (n) para sair: ");
                scanf(" %c", &resposta);
            }
            break;
        default:
            printf("\tOpcao invalida!\n");
            break;
        }
        
        if(opcao != 10) {
            printf("\tDeseja retornar ao menu inicial? Digite (s) para retornar e (n) para sair: ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("\tResposta invalida! Digite (s) para retornar e (n) para sair: ");
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