/*Bibliotecas*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*Variáveis globais*/
FILE *registroCadastroColaborador;
FILE *registroCadastroCliente;
int contadorCadastroColaboradorEscrita = 0;
int contadorCadastroColaboradorLeitura = 0;
int contadorCadastroClienteEscrita = 0;
int contadorCadastroClienteLeitura = 0;

/*Structs*/
/*Struct "dataHoje" para armazenar o dados de atualização de data colhidos na função "data"*/
typedef struct dataHoje {
    int dia, mes, ano;
}dataHoje;
dataHoje dataAtualizacao;

/*Struct "colaborador" utilizada para armazenar dados de cadastro de colaboradores digitados pelo usuario antes de passar para o arquivo*/
typedef struct colaborador {
    char nome[100], usuario[100], senha[100];
    int grupo;
} colaborador;
colaborador colaboradorNovo[500];

/*Struct "alterarSenha" utilizada para armazenar dados de alteracao de senha digitados pelo usuario logado antes de passar para o arquivo*/
typedef struct auterarSenha {
    char novaSenhaTeste1[100];
    char novaSenhaTeste2[100];
}auterarSenha;
auterarSenha cadastroNovaSenha;

/*Struct "colaboradorLogado" utilizada para armazenar os dados do colaborador que esta logado no sisteama para trabalharmos
 com gerenciamento de permissões*/
typedef struct colaboradorLogado {
    char nome[100], usuario[100], senha[100];
    int grupo;
}colaboradorLogado;
colaboradorLogado colaboradorLogado1;

/*Struct para cadastro de cliente atendido*/
typedef struct cliente {
    char nomeRazaoSocial[100];
    char email[100];
    char sevicoContratado[100], usuarioAtendimento[100];
    int status;
    long int cnpj, telefone;
    int diaContratacao, mesContratacao, anoContratacao;
    double mensalidade;
} cliente;
cliente clienteNovo[500];

/*Prototipos de Funções*/
/*Funções para facilitar formatação da interface apresentada ao usuario*/
void data();
void tabDois();
void tabQuatro();
void tabCinco();
void tabSeis();
void linhaDuas();
void linhaTres();
void barraDeStatus();
void erroAberturaCriacaoArquivo();
char efetuarOperacaoNovamente(char resposta);
/*Funções para trabalharmos com os dados dos colaboradores*/
void cadastroColaborador();
void alterarSenhaColaborador();
void edicaoArquivoColaborador();
void escritaArquivoColaborador();
void leituraArquivoColaborador();
void relatorioCadastroColaboradores();
int login();
int validacaoColaborador(char usuario[], char senha[]);
/*Funções para trabalharmos com os dados dos clientes atendidos*/
void cadastroCliente();
int validacaoDataContratacao(int diaContratacao, int mesContratacao, int anoContratacao);
void alterarStatusAtendimento();
void edicaoArquivoCliente();
void escritaArquivoCliente();
void leituraArquivoCliente();
void relatorioDeClientes();
void relatorioGeralDeClientes();
void relatorioDeClientesPorUsuario();
void atualizacaoAreceberMesAtual();
void usuarioAdmin();
void manual();
void contatoSuporte();
/*Funções com os menus do programa*/
void menuAjuda();
void menuInicial();

/*Funções*/
/*Função "data" utilizada para atualizar a data atual e armazenar na struct "dataHoje"*/
void data() {
    struct tm *dataAtual;
    time_t segundos;
    time(&segundos);
    dataAtual = localtime(&segundos);

    dataAtualizacao.dia = dataAtual->tm_mday;
    dataAtualizacao.mes = dataAtual->tm_mon+1;
    dataAtualizacao.ano = dataAtual->tm_year+1900;
}

/*Funções "tab..." utilizadas para formatação dos titulos, subtitulos e descrições do programa apresentado ao usuario*/
void tabDois() {
    printf("\t\t");
}

void tabQuatro() {
    printf("\t\t\t\t");
}

void tabCinco() {
    printf("\t\t\t\t\t");
}

void tabSeis() {
    printf("\t\t\t\t\t\t");
}

/*Funções "linha..." utilizadas para formatação de quebra de linha no programa*/
void linhaDuas() {
    printf("\n\n");
}

void linhaTres() {
    printf("\n\n\n");
}

/*Função "barraDeStatus" utilizada para padronizar a barra de status apresentada no programa, utilizando os dados armazenados
 na struct "dataHoje" e os dados da struct "colaboradorLogado"*/
void barraDeStatus() {
    tabDois();
    printf("DATA: %02d/%02d/%04d\tNOME: %s \tUSUARIO: %s\n\n\n", dataAtualizacao.dia, dataAtualizacao.mes, dataAtualizacao.ano, colaboradorLogado1.nome,colaboradorLogado1.usuario);
}

/*Função "erroAberturaCriacaoArquivo" criada para formatar a mensagem de erro padrão apresentada caso o programa nao consiga 
 manipular os arquivos*/
void erroAberturaCriacaoArquivo() {
    system("clear");
    linhaTres();
    tabCinco();
    printf("Erro ao abrir/criar o arquivo!\nPressione qualquer tecla para continuar...");
    getchar();getchar();
}

/*Função "efetuarOperacaoNovamente", criada para teste de resposta fornecida pelo usuario em ações repetitivas no programa*/
char efetuarOperacaoNovamente(char resposta) {
            linhaDuas();
            printf("\tDeseja efetuar a operacao novamente s sim n nao? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("\tResposta invalida! Informe novamene? ");
                scanf(" %c", &resposta);
            }
    return(resposta);
}

/*Função "cadastroColaborador", responsavel pelo cadastro de colaboradores no programa*/
void cadastroColaborador() {
    /*Estrutura if-else onde é testado se o colaborador armazenado na variavel "colaboradorLogado1" da struct "colaboradorLogado" 
    tem permissao para efetuar cadastros*/
    if(colaboradorLogado1.grupo == 2) {
        printf("\tUsuario sem permissao!\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        int grupo;
        char nome[100], usuario[100], senha[100], resposta;
        contadorCadastroColaboradorEscrita = 0;
        /*Estrutura do-while, onde é feita a leitura dos dados de cadastro inseridos pelo usuario e armazenados 
        nas variaveis locais da função*/
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
            /*Apos os dados serem arazenados nas variaveis locais correspondentes serao passados para o vetor "colaboradorNovo" da struct
            "colaborador", o controle das posições é efetuado pela variavel "contadorCadastroColaboradorEscrita"*/
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].nome, nome);
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].usuario, usuario);
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].senha, senha);
            colaboradorNovo[contadorCadastroColaboradorEscrita].grupo = grupo;
            contadorCadastroColaboradorEscrita++;
            /*Utilizacao da função "efetuarOperacaoNovamente", para teste se o colaborador deseja efetuar cadastro novamente, a 
            variavel "resposta" recebe */
            resposta == efetuarOperacaoNovamente(resposta);
        } while (resposta == 's' || resposta == 'S');
        /*Utilização da função "escritaArquivoColaborador" para gravar as informações da struct "colaborador" no arquivo de cadastro 
        de colaboradores*/
        escritaArquivoColaborador();
    }
}

/*Função "alterarSenhaColaborador", criada para edição da senha do colaborador logado no programa*/
void alterarSenhaColaborador() {
    int contadorAlterarSenha = 0;
    int validacao;
    char resposta;
    /*Estrutura do-while responsável por coletar nova senha fornecida pelo usuario, se repete enquanto os dados fornecidos 
    forem invalidos e o usuario escolher tentar novamente*/
    do {
        /*Utilização da função "leituraArquivoColaborador" para atualizarmos o programa com os dados do arquivo de colaboradores
        o que ajudará posteriormente a reescrever o arquivo com os dados da senha do colaborador alterados*/
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
        /*Variavel "validação recebe o teste de igualdade entre senhas armazenadas anteriormente na struct "cadastroNovaSenha"*/
        validacao = strcmp(cadastroNovaSenha.novaSenhaTeste1, cadastroNovaSenha.novaSenhaTeste2);

        if(validacao != 0) {
            linhaDuas();
            printf("\tSenhas divergentes!\n");
            printf("\tDeseja tentar novamente? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("\tResposta invalida! Deseja tentar novamete? ");
                scanf(" %c", &resposta);
            }
        }
        else {
            linhaDuas();
            printf("\tSenha cadastrada com sucesso!\n");
        }
        /*Enquanto o teste apontar senhas divergentes (validação != 0) e o colaborador responder "s" para nova tentativa essa 
        trutura se repetira*/
    } while ((resposta == 's' || resposta == 'S') && validacao != 0);

    /*Estrutura while responsavel por encontrar na struct "colaborador* o colaborador corespondente ao colaborador da struct "colaboradorLogado"
     e efetuar a troca de senha pela senha armazenada na struct "cadastroNovaSenha" caso os usuarios sejam correspondentes*/
    while(contadorAlterarSenha < contadorCadastroColaboradorLeitura) {
        validacao = strcmp(colaboradorLogado1.usuario, colaboradorNovo[contadorAlterarSenha].usuario);
        if(validacao == 0) {
            strcpy(colaboradorNovo[contadorAlterarSenha].senha, cadastroNovaSenha.novaSenhaTeste1); 
            contadorAlterarSenha = contadorCadastroColaboradorLeitura + 1;
        }
        contadorAlterarSenha++;
    }
    /*Utilização da função "edicaoArquivoColaborador" para reescrever o arquivo de cadastro de colaboradores com os dados alterados,
     e caso o colaborador não tenha alterado a senha o mesmo sera reescrito com os dados antigos que foram atualizados no inicio da função*/
    edicaoArquivoColaborador();
}

/*Função "edicaoArquivoColaborador", responsavel por limpar e reescrever o arquivo onde ficam armazenados os cadastros do colaboradores*/
void edicaoArquivoColaborador() {
    int contadorEdicao = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "w");/*Abertura de arquivo de modo que os dados sejam sobrescrito*/
    if (registroCadastroColaborador == NULL) {
        /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
        /*Estrutura while que efetua a escrita no arquivo com o auxilio da variavel global "contadorCadastroColaboradorLeitura" atualizada
         com a quantidade total de usuarios que contem na struct "colaborador" sempre que a função "leituraArquivoColaborador" é executada*/
        while (contadorEdicao < contadorCadastroColaboradorLeitura) {
            fprintf(registroCadastroColaborador, "%s-%s-%s-%d\n", colaboradorNovo[contadorEdicao].nome, colaboradorNovo[contadorEdicao].usuario, colaboradorNovo[contadorEdicao].senha, colaboradorNovo[contadorEdicao].grupo);
            contadorEdicao++;
        }
    }
    fclose(registroCadastroColaborador);
}

/*Função "escritaArquivoColaborador", responsavel por adicionar novos cadastros de colaboradores ao arquivo de colaboradores*/
void escritaArquivoColaborador() {
    int contadorEscrita = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "a");/*Abertura de arquivo de modo que seja adicionado dados*/
    if (registroCadastroColaborador == NULL) {
        /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
        /*Estrutura while que efetua a adição dos dados no arquivo com o auxilio da variavel global "contadorCadastroColaboradorEscrita" atualizada
         com sempre que é feito um novo cadastro*/
        while (contadorEscrita < contadorCadastroColaboradorEscrita) {
            fprintf(registroCadastroColaborador, "%s-%s-%s-%d\n", colaboradorNovo[contadorEscrita].nome, colaboradorNovo[contadorEscrita].usuario, colaboradorNovo[contadorEscrita].senha, colaboradorNovo[contadorEscrita].grupo);
            contadorEscrita++;
        }
    }
    fclose(registroCadastroColaborador);
}

/*Função "leituraArquivoColaborador", responsavel por efetuar a leitura do arquivo de cadastro de colaboradores e assim atualizar o programa com esses dados*/
void leituraArquivoColaborador() {
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "r");/*Abertura de arquivo em modo leitura*/
    if (registroCadastroColaborador == NULL) {
        /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
        contadorCadastroColaboradorLeitura = 0;
        rewind(registroCadastroColaborador);
        /*Estrutura while que efetua a leitura do arquivo de cadastro de colaboradores e atualiza a struct "colaborador"*/
        while (fscanf(registroCadastroColaborador, " %99[^-]-%99[^-]-%99[^-]-%d", colaboradorNovo[contadorCadastroColaboradorLeitura].nome, colaboradorNovo[contadorCadastroColaboradorLeitura].usuario, colaboradorNovo[contadorCadastroColaboradorLeitura].senha, &colaboradorNovo[contadorCadastroColaboradorLeitura].grupo) != EOF) {
            contadorCadastroColaboradorLeitura++;
        }
    }
    fclose(registroCadastroColaborador);
}

/*Função "relatorioCadastroColaboradores", apresenta para o colaborador o relatorio de colaboradores cadastrados*/
void relatorioCadastroColaboradores() {
    /*Estrutura if-else onde é testado se o colaborador armazenado na variavel "colaboradorLogado1" da struct "colaboradorLogado" 
    tem permissao para efetuar cadastros*/
    if(colaboradorLogado1.grupo == 2) {
        printf("\tUsuario sem permissao!\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        /*Utilização da função "leituraArquivoColaborador" para atualizar a struct "colaborador" com os dados de cadastros que contem no arquivo de
         cadastro de colaboradores e posteriormente apresentar*/
        leituraArquivoColaborador();
        int contadorRelatorio = 0;
        char resposta;

        system("clear");
        barraDeStatus();
        tabSeis();
        printf("RELATORIO DE USUARIOS");
        linhaTres();
        /*Estrutura while responsavel por ler os dados da struct "colaborador" e apresentar o relatorio dos mesmos ao usuario*/
        while (contadorRelatorio < contadorCadastroColaboradorLeitura) {
            printf("\tNOME: %s\tUSUARIO: %s\tGRUPO DE PERMISSOES: %d", colaboradorNovo[contadorRelatorio].nome, colaboradorNovo[contadorRelatorio].usuario, colaboradorNovo[contadorRelatorio].grupo);
            linhaDuas();
            contadorRelatorio++;
        }
        linhaDuas();
    }
}

/*Função "login" responsavel por controlar o acesso ao programa*/
int login() {
    char usuario[100], senha[100], resposta;

    /*Estrutura do-while */
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

        /*Estrutura if-else com a função "validacaoColaborador" utilizada para validar se os dados inseridos possuem cadastro
         e controlar o acesso ao sistema*/
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

/*Função "validacaoColaborador" que retorna o resultado do teste de validação dos dados inseridos pelo usuario na função "login"*/
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

/*Função "cadastroCliente" responsavel por armazenar os dados de cadastro de clientes na struct "cliente" e posteriormente
 com a função "escritaArquivoCliente" passar os dados para o arquivo de cadastro de clientes*/
void cadastroCliente() {
    char nomeRazaoSocial[100], email[100];
    char sevicoContratado[100], usuarioAtendimento[100], resposta;
    long int telefone, cnpj;
    int status, diaContratacao, mesContratacao, anoContratacao;
    double mensalidade;
    contadorCadastroClienteEscrita = 0;
    /*Estrutura do-while, onde é feita a leitura dos dados de cadastro inseridos pelo usuario e armazenados nas variaveis locais da função*/
    do {
        system("clear");
        barraDeStatus();
        tabSeis();
        printf("CADASTRO DE CLIENTE");
        linhaTres();
        printf("\tRAZAO SOCIAL: ");
        scanf(" %99[^\n]", nomeRazaoSocial);
        printf("\tCNPJ: ");
        scanf("%ld", &cnpj);
        printf("\tTELEFONE: ");
        scanf("%ld", &telefone);
        printf("\tE-MAIL: ");
        scanf(" %99[^\n]", email);
        printf("\tDATA DE CONTRATACAO: ");
        scanf("%d/%d/%d", &diaContratacao, &mesContratacao, &anoContratacao);
        /*Utilização da estrutura while com a função "validacaoDataContratacao" como parametro. Enquanto o retorno da função "validacaoDataContratacao"
         informar que a data inserida e invalida (retorno != 0)*/
        while(validacaoDataContratacao(diaContratacao, mesContratacao, anoContratacao) != 0) {
            printf("\tData invalida!\n");
            printf("\tDATA DE CONTRATACAO: ");
            scanf("%d/%d/%d", &diaContratacao, &mesContratacao, &anoContratacao);
        }
        printf("\tSERVICO CONTRATADO: ");
        scanf(" %99[^\n]", sevicoContratado);
        printf("\tVALOR MENSAL SERVICO CONTRATADO: R$ ");
        scanf("%lf", &mensalidade);
        printf("\tSTATUS ""1"" EM ANDAMENTO ""2"" FINALIZADO: ");
        scanf("%d", &status);
        /*Apos os dados serem arazenados nas variaveis locais correspondentes serao passados para o vetor "clienteNovo" da struct
         "cliente", o controle das posições é efetuado pela variavel global "contadorCadastroClienteEscrita"*/
        strcpy(clienteNovo[contadorCadastroClienteEscrita].nomeRazaoSocial, nomeRazaoSocial);
        clienteNovo[contadorCadastroClienteEscrita].cnpj = cnpj;
        clienteNovo[contadorCadastroClienteEscrita].telefone = telefone;
        strcpy(clienteNovo[contadorCadastroClienteEscrita].email, email);
        clienteNovo[contadorCadastroClienteEscrita].diaContratacao = diaContratacao;
        clienteNovo[contadorCadastroClienteEscrita].mesContratacao = mesContratacao;
        clienteNovo[contadorCadastroClienteEscrita].anoContratacao = anoContratacao;
        strcpy(clienteNovo[contadorCadastroClienteEscrita].sevicoContratado, sevicoContratado);
        clienteNovo[contadorCadastroClienteEscrita].mensalidade = mensalidade;
        strcpy(clienteNovo[contadorCadastroClienteEscrita].usuarioAtendimento, colaboradorLogado1.usuario);
        clienteNovo[contadorCadastroClienteEscrita].status = status;
        contadorCadastroClienteEscrita++;
        /*Utilizacao da função "efetuarOperacaoNovamente", para teste se o colaborador deseja efetuar cadastro novamente*/
        resposta == efetuarOperacaoNovamente(resposta);
    } while (resposta == 's' || resposta == 'S');
    /*Utilização da função "escritaArquivoColaborador" para gravar as informações da struct "cliente" no arquivo de cadastro 
     de clientes*/
    escritaArquivoCliente();
}

/*Função "validacaoDataContratacao" criada para testar na hora do cadastro do cliente se a data inserida é valida ou nao*/
int validacaoDataContratacao(int diaContratacao, int mesContratacao, int anoContratacao) {
    /*Estrutura if-else para testar a data no seguinte formato dd/mm/aa*/
    if((diaContratacao >= 1 && diaContratacao <= 31) && (mesContratacao == 1 || mesContratacao == 3 || mesContratacao == 5 || mesContratacao == 7 || mesContratacao == 8 || mesContratacao == 10 || mesContratacao == 12) && anoContratacao >= 1) {
        return 0;
    }
    else if((diaContratacao >= 1 && diaContratacao <= 28 || 29) && (mesContratacao == 2) && (anoContratacao >= 1)) {
        return 0;
    }
    else if((diaContratacao >= 1 && diaContratacao <= 30) && (mesContratacao == 4 || mesContratacao == 6 || mesContratacao == 9 || mesContratacao == 11) && (anoContratacao >= 1)) {
        return 0;
    }
    else {
        return 1;/*Caso retorne 1 a data sera invalida*/
    }
}

/*Função criada para edição do status do serviço prestado contratado pelo cliente cadastrado*/
void alterarStatusAtendimento() {
    int contadorAuterarStatus = 0;
    int validacao = 1,status;
    long int cnpj;
    char resposta;
    /*Estrutura do-while responsável por coletar novo status fornecido pelo usuario, se repete enquanto os dados de CNPJ fornecidos 
    forem invalidos e o usuario escolher efetuar a operação novamente*/
    do {
        /*Utilização da função "leituraArquivoColaborador" para atualizarmos o programa com os dados do arquivo de clientes o que
         ajudará posteriormente a reescrever o arquivo com os dados de status de serviço prestado alterados*/
        leituraArquivoCliente();

        system("clear");
        barraDeStatus();
        tabSeis();
        printf("AUTERACAO DE STATUS DE ATENDIMENTO");
        linhaTres();

        do {
            printf("\tINFORME O STATUS 1 EM ANDAMENTO 2 FINALIZADO: ");
            scanf("%d", &status);
            printf("\tINFORME O CNPJ DO CLIENTE: ");
            scanf("%ld", &cnpj);
            /*Estrutura while onde são testados todos os CNPJ para encontrar o CNPJ digitado em meio aos cadastros na struct "cliente"*/
            while(contadorAuterarStatus < contadorCadastroClienteLeitura) {
                if(cnpj == clienteNovo[contadorAuterarStatus].cnpj) {
                    validacao = 0;/*caso seja encontrado */
                    clienteNovo[contadorAuterarStatus].status = status;
                }
                contadorAuterarStatus++;
            }
            if(validacao != 0) {
                printf("\tCNPJ invalido!\n");
            }
        } while(validacao != 0);
        /*Utilizacao da função "efetuarOperacaoNovamente", para teste se o colaborador deseja efetuar edição de outro status*/
        resposta == efetuarOperacaoNovamente(resposta);
    } while (resposta == 's' || resposta == 'S');
    /*Utilização da função "edicaoArquivoCliente" para reescrever o arquivo de cadastro de clientes com os dados alterados*/
    edicaoArquivoCliente();
}

/*Função "edicaoArquivoCliente", responsavel por limpar e reescrever o arquivo onde ficam armazenados os cadastros dos clientes*/
void edicaoArquivoCliente() {
    int contadorEdicao = 0;
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "w");
    if (registroCadastroCliente == NULL) {
         /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
         /*Estrutura while que efetua a escrita no arquivo com o auxilio da variavel global "contadorCadastroClienteLeitura" atualizada
         com a quantidade total de usuarios que contem na struct "colaborador" sempre que a função "leituraArquivoCliente" é executada*/
        while (contadorEdicao < contadorCadastroClienteLeitura) {
            fprintf(registroCadastroCliente, "%s-%ld-%ld-%s-%d-%d-%d-%s-%.2lf-%s-%d\n", clienteNovo[contadorEdicao].nomeRazaoSocial, clienteNovo[contadorEdicao].cnpj, clienteNovo[contadorEdicao].telefone, clienteNovo[contadorEdicao].email, clienteNovo[contadorEdicao].diaContratacao, clienteNovo[contadorEdicao].mesContratacao, clienteNovo[contadorEdicao].anoContratacao, clienteNovo[contadorEdicao].sevicoContratado, clienteNovo[contadorEdicao].mensalidade, clienteNovo[contadorEdicao].usuarioAtendimento, clienteNovo[contadorEdicao].status);
            contadorEdicao++;
        }
    }
    fclose(registroCadastroCliente);
}

/*Função "escritaArquivoCliente", responsavel por adicionar novos cadastros de clientes ao arquivo de clientes*/
void escritaArquivoCliente() {
    int contadorEscrita = 0;
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "a");
    if (registroCadastroCliente == NULL) {
        /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
         /*Estrutura while que efetua a adição dos dados no arquivo com o auxilio da variavel global "contadorCadastroClienteEscrita" atualizada
          sempre que é feito um novo cadastro*/
        while(contadorEscrita < contadorCadastroClienteEscrita) {
            fprintf(registroCadastroCliente, "%s-%ld-%ld-%s-%d-%d-%d-%s-%.2lf-%s-%d\n", clienteNovo[contadorEscrita].nomeRazaoSocial, clienteNovo[contadorEscrita].cnpj, clienteNovo[contadorEscrita].telefone, clienteNovo[contadorEscrita].email, clienteNovo->diaContratacao, clienteNovo->mesContratacao, clienteNovo->anoContratacao, clienteNovo[contadorEscrita].sevicoContratado, clienteNovo[contadorEscrita].mensalidade, clienteNovo[contadorEscrita].usuarioAtendimento, clienteNovo[contadorEscrita].status);
            contadorEscrita++;
        }
    }
    fclose(registroCadastroCliente);
}

/*Função "leituraArquivoCliente", responsavel por efetuar a leitura do arquivo de cadastro de clientes e assim atualizar o programa com esses dados*/
void leituraArquivoCliente() {
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "r");
    if (registroCadastroCliente == NULL) {
         /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
        contadorCadastroClienteLeitura = 0;
        
        rewind(registroCadastroCliente);
         /*Estrutura while que efetua a leitura do arquivo de cadastro de clientes e atualiza a struct "cliente"*/
        while (fscanf(registroCadastroCliente, " %99[^-]-%ld-%ld-%99[^-]-%d-%d-%d-%99[^-]-%lf-%99[^-]-%d", clienteNovo[contadorCadastroClienteLeitura].nomeRazaoSocial, &clienteNovo[contadorCadastroClienteLeitura].cnpj, &clienteNovo[contadorCadastroClienteLeitura].telefone, clienteNovo[contadorCadastroClienteLeitura].email, &clienteNovo[contadorCadastroClienteLeitura].diaContratacao, &clienteNovo[contadorCadastroClienteLeitura].mesContratacao, &clienteNovo[contadorCadastroClienteLeitura].anoContratacao , clienteNovo[contadorCadastroClienteLeitura].sevicoContratado, &clienteNovo[contadorCadastroClienteLeitura].mensalidade,clienteNovo[contadorCadastroClienteLeitura].usuarioAtendimento, &clienteNovo[contadorCadastroClienteLeitura].status) != EOF) {
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
                printf("\tRAZAO SOCIAL: %s\tCNPJ: %ld\n\tTELEFONE: %ld\t\tE-MAIL: %s\n\tDATA DE CONTRATACAO: %d/%d/%d\tSERVICO CONTRATADO: %s\n\tVALOR MENSAL: R$ %.2lf\tUSUARIO RESPONSAVEL: %s\n\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].diaContratacao, clienteNovo[contadorRelatorio].mesContratacao, clienteNovo[contadorRelatorio].anoContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade, clienteNovo[contadorRelatorio].usuarioAtendimento);
                if(clienteNovo[contadorRelatorio].status == 1) {
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
                printf("\tRAZAO SOCIAL: %s\tCNPJ: %ld\n\tTELEFONE: %ld\t\tE-MAIL: %s\n\tDATA DE CONTRATACAO: %d/%d/%d\tSERVICO CONTRATADO: %s\n\tVALOR MENSAL: R$ %.2lf\tUSUARIO RESPONSAVEL: %s\n\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].diaContratacao, clienteNovo[contadorRelatorio].mesContratacao, clienteNovo[contadorRelatorio].anoContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade, clienteNovo[contadorRelatorio].usuarioAtendimento);
                if(clienteNovo[contadorRelatorio].status == 1) {
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
                    printf("\tRAZAO SOCIAL: %s\tCNPJ: %ld\n\tTELEFONE: %ld\t\tE-MAIL: %s\n\tDATA DE CONTRATACAO: %d/%d/%d\tSERVICO CONTRATADO: %s\n\tVALOR MENSAL: R$ %.2lf\tUSUARIO RESPONSAVEL: %s\n\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].diaContratacao, clienteNovo[contadorRelatorio].mesContratacao, clienteNovo[contadorRelatorio].anoContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade, clienteNovo[contadorRelatorio].usuarioAtendimento);
                    if(clienteNovo[contadorRelatorio].status == 1) {
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
        strcpy(nomeAdmin, "USUARIO ADMINISTRADOR");
        strcpy(usuarioAdmin, "admin");
        strcpy(senhaAdmin, "admin");
        grupo = 1;

        fprintf(registroCadastroColaborador, "%s-%s-%s-%d\n", nomeAdmin, usuarioAdmin, senhaAdmin, grupo);
        fclose(registroCadastroColaborador);
    }
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
        printf("\t-1.Cadastro de usuario\n\t-2.Alterar senha\n\t-3.Relatorio de usuarios\n\t-4.Cadastro de cliente\n\t-5.Alterar Status de cliente\n\t-6.Relatorio de clientes\n\t-7.Relatorio geral de clientes\n\t-8.Relatorio de clientes por usuario\n\t-9.Atualizacao a receber mes atual\n\t+10.Ajuda\n\t-11.Sair\n\n\tOpcao: ");
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
            alterarStatusAtendimento();
            break;
        case 6:
            relatorioDeClientes();
            break;
        case 7:
            relatorioGeralDeClientes();
            break;
        case 8:
            relatorioDeClientesPorUsuario();
            break;
        case 9:
            atualizacaoAreceberMesAtual();
            break;
        case 10:
            menuAjuda();
            break;
        case 11:
            printf("\tDeseja realmente sair?: ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("\tResposta invalida! Digite (s) para retornar e (n) para sair: ");
                scanf(" %c", &resposta);
            }

            if(resposta == 'n' || resposta == 'N') {
                menuInicial();
            }
            break;
        default:
            printf("\tOpcao invalida!\n");
            break;
        }
        
        if(opcao != 11) {
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

    data();
    usuarioAdmin();

    if (login() == 0) {
        menuInicial();
    }

    return 0;
}