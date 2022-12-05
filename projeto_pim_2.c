/*Bibliotecas*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*Variáveis globais*/
FILE *registroCadastroColaborador;
FILE *registroCadastroCliente;
FILE *registroManual;
int contadorCadastroColaboradorEscrita = 0;
int contadorCadastroColaboradorLeitura = 0;
int contadorCadastroClienteEscrita = 0;
int contadorCadastroClienteLeitura = 0;

/*Structs*/
/*Struct "dataHoje", criada para armazenar os dados de atualização de data (dia/mes/ano), para serem utilizados no programa*/
typedef struct dataHoje {
    int dia, mes, ano;
}dataHoje;
dataHoje dataAtualizacao;

/*Struct "colaborador", utilizada para armazenar os os dados de cadastro de usuários possibilitando assim ao programa trabalhar com
 esses dados e utilizar o arquivo correspondente somente em momentos necessários para leitura(atualizar a si mesmo) ou escrita (atualizar o arquivo)*/
typedef struct colaborador {
    char nome[100], usuario[100], senha[100];
    int grupo, status;
} colaborador;
colaborador colaboradorNovo[500];

/*Struct "alterarSenha", utilizada para armazenar dados de alteração de senha digitados pelo usuário logado, para que assim o
 programa passe os dados válidos e testados para o arquivo correspondente*/
typedef struct alterarSenha {
    char novaSenhaTeste1[100], novaSenhaTeste2[100];
}alterarSenha;
alterarSenha cadastroNovaSenha;

/*Struct "colaboradorLogado", utilizada para armazenar os dados do usuário que esta logado no programa para possibilitar o gerenciamento de permissões*/
typedef struct colaboradorLogado {
    char nome[100], usuario[100], senha[100];
    int grupo, statusColaborador;
}colaboradorLogado;
colaboradorLogado colaboradorLogado1;

/*Struct "cliente", criada para armazenar dados do cliente atendido e assim possibilitar ao programa trabalhar com os dados e utilizar
 o arquivo correspondente apenas quando necessários para leitura(atualizar a si mesmo) ou escrita (atualizar o arquivo)*/
typedef struct cliente {
    char nomeRazaoSocial[100], cnpj[100], email[100], telefone[100];
    char sevicoContratado[100], usuarioAtendimento[100];
    int diaContratacao, mesContratacao, anoContratacao, status;
    double mensalidade;
} cliente;
cliente clienteNovo[500];

/*Struct "manualUsuario", criada para armazenar o manual de usuario*/
typedef struct manualUsuario {
    char manual[20000];
}manualUsuario;
manualUsuario manualUtilizacaoUsuario;

/*Prototipos de Funções*/
/*Funções para facilitar formatação da interface apresentada ao usuário*/
void data();
void tabDois();
void tabQuatro();
void tabCinco();
void tabSete();
void tabNove();
void linhaDuas();
void linhaTres();
void barraDeStatus();
/*Funções para trabalharmos com os dados dos colaboradores*/
void cadastroColaborador();
void alterarSenhaColaborador();
void alteracaoStatusColaborador();
void edicaoArquivoColaborador();
void escritaArquivoColaborador();
void leituraArquivoColaborador();
void relatorioCadastroColaboradores();
void usuarioAdmin();
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
/*Demais funções*/
void erroAberturaCriacaoArquivo();
char efetuarOperacaoNovamente(char resposta);
void menuAjuda();
void manual();
void leituraArquivoManual();
void contatoSuporte();
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

/*Funções "tab..." utilizadas para formatação dos titulos, subtitulos e descrições do programa apresentados ao usuário*/
void tabDois() {
    printf("\t\t");
}

void tabQuatro() {
    printf("\t\t\t\t");
}

void tabCinco() {
    printf("\t\t\t\t\t");
}

void tabSete() {
    printf("\t\t\t\t\t\t\t");
}

void tabNove() {
    printf("\t\t\t\t\t\t\t\t\t");
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
    tabCinco();
    printf("DATA: %02d/%02d/%04d\tNOME: %s \tUSUARIO: %s\n\n\n", dataAtualizacao.dia, dataAtualizacao.mes, dataAtualizacao.ano, colaboradorLogado1.nome,colaboradorLogado1.usuario);
}

/*Função "cadastroColaborador", responsável pelo processo de cadastro de usuários no programa*/
void cadastroColaborador() {
    /*Estrutura "if-else" onde é testado se o colaborador armazenado na váriavel "colaboradorLogado1" da struct "colaboradorLogado" tem permissão para efetuar cadastros*/
    if(colaboradorLogado1.grupo == 2) {
        printf("\tUsuario sem permissao!\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        int grupo, status;
        char nome[100], usuario[100], senha[100], resposta;
        contadorCadastroColaboradorEscrita = 0;
        /*Estrutura "do-while", onde é feita a leitura dos dados de cadastro inseridos pelo usuário e armazenados nas variáveis locais da função*/
        do {
            system("clear");
            barraDeStatus();
            tabNove();
            printf("CADASTRO DE USUARIO");
            linhaTres();
            printf("\tNOME: ");
            scanf(" %99[^\n]", nome);
            printf("\tUSUARIO: ");
            scanf(" %99[^\n]", usuario);
            printf("\tSENHA: ");
            scanf(" %99[^\n]", senha);
            printf("\tGRUPO, DIGITE (1) PARA ADMINISTRADOR E (2) PARA DEMAIS USUARIOS: ");
            scanf("%d", &grupo);
            printf("\tINFORME O STATUS DO COLABORADOR (1) ATIVO (2) INATIVO: ");
            scanf("%d", &status);
            /*Após os dados serem arazenados nas variáveis locais correspondentes serão passados para a variável "colaboradorNovo" da struct "colaborador"*/
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].nome, nome);
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].usuario, usuario);
            strcpy(colaboradorNovo[contadorCadastroColaboradorEscrita].senha, senha);
            colaboradorNovo[contadorCadastroColaboradorEscrita].grupo = grupo;
            colaboradorNovo[contadorCadastroColaboradorEscrita].status = status;
            contadorCadastroColaboradorEscrita++;
            /*Utilização da função "efetuarOperacaoNovamente", para testar se o usuário deseja efetuar cadastro novamente*/
            resposta = efetuarOperacaoNovamente(resposta);
        } while (resposta == 's' || resposta == 'S');
        /*Utilização da função "escritaArquivoColaborador" para gravar as informações da struct "colaborador" no arquivo de cadastro dos usuários dos colaboradores*/
        escritaArquivoColaborador();
    }
}

/*Função "alterarSenhaColaborador", criada para edição da senha do usuário logado no programa*/
void alterarSenhaColaborador() {
    int contadorAlterarSenha = 0, validacao;
    char resposta;
    /*Estrutura "do-while" responsável por coletar nova senha fornecida pelo usuário, se repete enquanto os dados fornecidos
    forem invalidos e o usuário escolher tentar novamente*/
    do {
        /*Utilização da função "leituraArquivoColaborador" para atualizarmos o programa com os dados do arquivo de usuários dos colaboradores*/
        leituraArquivoColaborador();

        system("clear");
        barraDeStatus();
        tabNove();
        printf("ALTERACAO DE SENHA");
        linhaTres();
        printf("\tDIGITE A NOVA SENHA: ");
        scanf(" %99[^\n]", cadastroNovaSenha.novaSenhaTeste1);
        printf("\tDIGITE NOVAMENTE PARA VALIDACAO: ");
        scanf(" %99[^\n]", cadastroNovaSenha.novaSenhaTeste2);
        /*Variável "validação" recebe o teste de igualdade entre senhas armazenadas anteriormente na variável "cadastroNovaSenha" da struct "alterarSenha"*/
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
        /*Enquanto o teste apontar senhas divergentes (validação != 0) e o usuario responder "s" para nova tentativa essa estrutura se repetira*/
    } while ((resposta == 's' || resposta == 'S') && validacao != 0);

    /*Estrutura "while" responsável por encontrar na struct "colaborador* o usuário corespondente ao usuário da struct "colaboradorLogado"
     e efetuar a troca de senha pela senha armazenada na struct "cadastroNovaSenha" caso os usuários sejam correspondentes*/
    while(contadorAlterarSenha < contadorCadastroColaboradorLeitura) {
        validacao = strcmp(colaboradorLogado1.usuario, colaboradorNovo[contadorAlterarSenha].usuario);
        if(validacao == 0) {
            strcpy(colaboradorNovo[contadorAlterarSenha].senha, cadastroNovaSenha.novaSenhaTeste1);
            contadorAlterarSenha = contadorCadastroColaboradorLeitura + 1;
        }
        contadorAlterarSenha++;
    }
    /*Utilização da função "edicaoArquivoColaborador" para reescrever o arquivo de cadastro de colaboradores com os dados alterados, e caso o
     colaborador não tenha alterado a senha o mesmo sera reescrito com os dados antigos que foram atualizados no inicio da função*/
    edicaoArquivoColaborador();
}

void alteracaoStatusColaborador() {
    if(colaboradorLogado1.grupo == 2) {
        printf("\tUsuario sem permissao!\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        leituraArquivoColaborador();
        int contadorAlterarStatus = 0, validacao = 1, status;
        char usuario[100], resposta;
        /*Estrutura "do-while" responsável por coletar novo status fornecido pelo usuário, se repete enquanto os dados de usuário fornecidos
        forem inválidos e o usuário escolher efetuar a operação novamente*/
        do {
            /*Utilização da função "leituraArquivoColaborador" para atualizar o programa com os dados do arquivo de colaboradores*/

            system("clear");
            barraDeStatus();
            tabNove();
            printf("ALTERACAO DE STATUS DE COLABORADOR");
            linhaTres();

            do {
                printf("\tINFORME O USUARIO: ");
                scanf(" %99[^\n]", usuario);
                printf("\tINFORME O STATUS (1) ATIVO (2) INATIVO: ");
                scanf("%d", &status);
                /*Estrutura "while" onde são testados todos os usuários para encontrar o usuário digitado em meio aos cadastros atualizados da variável "colaboradorNovo" na struct "colaborador"*/
                while(contadorAlterarStatus < contadorCadastroColaboradorLeitura) {
                    if(strcmp(usuario, colaboradorNovo[contadorAlterarStatus].usuario)==0) {
                        colaboradorNovo[contadorAlterarStatus].status = status;
                        validacao = 0;
                    }
                    contadorAlterarStatus++;
                }
                if(validacao != 0) {
                    printf("\tUsuario invalido!\n");
                }
            } while(validacao != 0);
            /*Utilização da função "efetuarOperacaoNovamente", para teste se o usuário deseja efetuar alteração de outro status*/
            resposta = efetuarOperacaoNovamente(resposta);
        } while (resposta == 's' || resposta == 'S');
        /*Utilização da função "edicaoArquivoColaboradores" para reescrever o arquivo de cadastro de colaboradores com os dados alterados*/
        edicaoArquivoColaborador();
    }
}

/*Função "edicaoArquivoColaborador", responsável por limpar e reescrever o arquivo onde ficam armazenados os cadastros dos usuários*/
void edicaoArquivoColaborador() {
    int contadorEdicao = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "w");/*Abertura de arquivo de modo que os dados sejam sobrescritos*/
    if (registroCadastroColaborador == NULL) {
        /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
        /*Estrutura while que efetua a escrita no arquivo com a quantidade total de usuários que contem na variável "colaboradorNovo" da struct "colaborador"*/
        while (contadorEdicao < contadorCadastroColaboradorLeitura) {
            fprintf(registroCadastroColaborador, "%s-%s-%s-%d-%d\n", colaboradorNovo[contadorEdicao].nome, colaboradorNovo[contadorEdicao].usuario, colaboradorNovo[contadorEdicao].senha, colaboradorNovo[contadorEdicao].grupo, colaboradorNovo[contadorEdicao].status);
            contadorEdicao++;
        }
    }
    fclose(registroCadastroColaborador);
}

/*Função "escritaArquivoColaborador", responsável por adicionar novos cadastros de usuários ao arquivo de colaboradores*/
void escritaArquivoColaborador() {
    int contadorEscrita = 0;
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "a");/*Abertura de arquivo de modo que seja adicionado dados*/
    if (registroCadastroColaborador == NULL) {
        /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
        /*Estrutura while que efetua a adição dos dados no arquivo*/
        while (contadorEscrita < contadorCadastroColaboradorEscrita) {
            fprintf(registroCadastroColaborador, "%s-%s-%s-%d-%d\n", colaboradorNovo[contadorEscrita].nome, colaboradorNovo[contadorEscrita].usuario, colaboradorNovo[contadorEscrita].senha, colaboradorNovo[contadorEscrita].grupo, colaboradorNovo[contadorEscrita].status);
            contadorEscrita++;
        }
    }
    fclose(registroCadastroColaborador);
}

/*Função "leituraArquivoColaborador", responsável por efetuar a leitura do arquivo de cadastro de usuários e assim atualizar o programa com esses dados*/
void leituraArquivoColaborador() {
    registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "r");/*Abertura de arquivo em modo leitura*/
    if (registroCadastroColaborador == NULL) {
        /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
        contadorCadastroColaboradorLeitura = 0;
        rewind(registroCadastroColaborador);
        /*Estrutura "while" que efetua a leitura do arquivo de cadastro de usuários e atualiza a struct "colaborador"*/
        while (fscanf(registroCadastroColaborador, " %99[^-]-%99[^-]-%99[^-]-%d-%d", colaboradorNovo[contadorCadastroColaboradorLeitura].nome, colaboradorNovo[contadorCadastroColaboradorLeitura].usuario, colaboradorNovo[contadorCadastroColaboradorLeitura].senha, &colaboradorNovo[contadorCadastroColaboradorLeitura].grupo, &colaboradorNovo[contadorCadastroColaboradorLeitura].status) != EOF) {
            contadorCadastroColaboradorLeitura++;
        }
    }
    fclose(registroCadastroColaborador);
}

/*Função "relatorioCadastroColaboradores", apresenta para o colaborador o relatório de usuários cadastrados*/
void relatorioCadastroColaboradores() {
    /*Estrutura "if-else" onde é testado se o usuário armazenado na variável "colaboradorLogado1" da struct "colaboradorLogado"
    tem permissão para gerar o relatório*/
    if(colaboradorLogado1.grupo == 2) {
        printf("\tUsuario sem permissao!\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        /*Utilização da função "leituraArquivoColaborador" para atualizar a struct "colaborador" com os dados de cadastros que contem no arquivo de
         cadastro de usuários e posteriormente apresentar no relatório*/
        leituraArquivoColaborador();
        int contadorRelatorio = 0;
        char resposta;

        system("clear");
        barraDeStatus();
        tabNove();
        printf("RELATORIO DE USUARIOS");
        linhaTres();
        /*Estrutura "while" responsável por ler os dados da struct "colaborador" e apresentar o relatório dos mesmos ao usuário*/
        while (contadorRelatorio < contadorCadastroColaboradorLeitura) {
            printf("\tNOME: %s\tUSUARIO: %s\tGRUPO DE PERMISSOES: %d\tSTATUS: ", colaboradorNovo[contadorRelatorio].nome, colaboradorNovo[contadorRelatorio].usuario, colaboradorNovo[contadorRelatorio].grupo);
            if(colaboradorNovo[contadorRelatorio].status == 1) {
                printf("Ativo");
                linhaDuas();
            }
            else {
                printf("Inativo");
                linhaDuas();
            }
            contadorRelatorio++;
        }
    }
}

/*Função "usuarioAdmin" reponsável por criar o arquivo de cadastro de colaborador e um usuário admin na primeira vez em que o programa é executado para que seja possível
 acessar o programa para cadastrar os demais usuários*/
void usuarioAdmin() {
    /*Teste efetuado com a função "access" para verificar se ja foi efetuado algum cadastro de cliente e criado o arquivo de cadastro, caso o teste retorne -1 será
     será criado o usuário arquivo de cadastro de usuários e o usuário "admin" sera inserido*/
    if (access("arquivoCadastroColaborador.txt", R_OK) == -1) {
        registroCadastroColaborador = fopen("arquivoCadastroColaborador.txt", "a");
        int grupo,status;
        char nomeAdmin[100], usuarioAdmin[100], senhaAdmin[100];
        strcpy(nomeAdmin, "USUARIO ADMINISTRADOR");
        strcpy(usuarioAdmin, "admin");
        strcpy(senhaAdmin, "admin");
        grupo = 1;
        status = 1;

        fprintf(registroCadastroColaborador, "%s-%s-%s-%d-%d\n", nomeAdmin, usuarioAdmin, senhaAdmin, grupo, status);
        fclose(registroCadastroColaborador);
    }
}

/*Função "login", responsável por controlar o acesso ao programa*/
int login() {
    char usuario[100], senha[100], resposta;

    do {
        system("clear");
        tabNove();
        printf("LOGIN");
        linhaTres();
        tabCinco();
        printf("USUARIO: ");
        scanf(" %99[^\n]", usuario);
        linhaDuas();
        tabCinco();
        printf("SENHA: ");
        scanf(" %99[^\n]", senha);

        /*Estrutura "if-else" com a função "validacaoColaborador" utilizada para validar se os dados inseridos possuem cadastro
         e controlar o acesso ao sistema*/

        if (validacaoColaborador(usuario, senha) == 0) {
            return 0;
        }
        else if (validacaoColaborador(usuario, senha) == 3) {
            linhaDuas();
            tabQuatro();
            printf("Usuario inativo! Deseja tentar novamente? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                tabQuatro();
                printf("Resposta invalida! Deseja tentar novamente? ");
                scanf(" %c", &resposta);
            }
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
    /*A estrutura repetira enquanto os dados forem inválidos e o usuário escolher tentar novamente*/
    } while (resposta == 's' || resposta == 'S');
}

/*Função "validacaoColaborador", que retorna o resultado do teste de validação dos dados inseridos pelo usuário na função "login"*/
int validacaoColaborador(char usuario[], char senha[]) {
    leituraArquivoColaborador();
    int contadorValidacao = 0;

    while (contadorValidacao <= contadorCadastroColaboradorLeitura) {
        if(strcmp(usuario, colaboradorNovo[contadorValidacao].usuario) == 0 && strcmp(senha, colaboradorNovo[contadorValidacao].senha) == 0) {
            if(colaboradorNovo[contadorValidacao].status == 2) {
                return 3;
                contadorValidacao = contadorCadastroColaboradorLeitura + 1;
            }
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

/*Função "cadastroCliente", responsável pelo processo de cadastro de clientes pelo usuário logado*/
void cadastroCliente() {
    char nomeRazaoSocial[100], telefone[100], cnpj[100], email[100];
    char sevicoContratado[100], usuarioAtendimento[100], resposta;
    int status, diaContratacao, mesContratacao, anoContratacao;
    double mensalidade;
    contadorCadastroClienteEscrita = 0;
    /*Estrutura "do-while", onde é feita a leitura dos dados de cadastro inseridos pelo usuário e armazenados nas variáveis locais da função*/
    do {
        system("clear");
        barraDeStatus();
        tabNove();
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
        printf("\tDATA DE CONTRATACAO: ");
        scanf("%d/%d/%d", &diaContratacao, &mesContratacao, &anoContratacao);
        /*Utilização da estrutura "while" com a função "validacaoDataContratacao" como parâmetro. A estrutura repetira enquanto o retorno da função "validacaoDataContratacao"
         informar que a data inserida e inválida (retorno != 0)*/
        while(validacaoDataContratacao(diaContratacao, mesContratacao, anoContratacao) != 0) {
            printf("\tData invalida!\n");
            printf("\tDATA DE CONTRATACAO: ");
            scanf("%d/%d/%d", &diaContratacao, &mesContratacao, &anoContratacao);
        }
        printf("\tSERVICO CONTRATADO: ");
        scanf(" %99[^\n]", sevicoContratado);
        printf("\tVALOR MENSAL SERVICO CONTRATADO: R$ ");
        scanf("%lf", &mensalidade);
        printf("\tSTATUS (1) EM ANDAMENTO (2) FINALIZADO: ");
        scanf("%d", &status);
        /*Apos os dados serem arazenados nas variáveis locais correspondentes serão passados para a variável "clienteNovo" da struct
         "cliente"*/
        strcpy(clienteNovo[contadorCadastroClienteEscrita].nomeRazaoSocial, nomeRazaoSocial);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].cnpj, cnpj);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].telefone, telefone);
        strcpy(clienteNovo[contadorCadastroClienteEscrita].email, email);
        clienteNovo[contadorCadastroClienteEscrita].diaContratacao = diaContratacao;
        clienteNovo[contadorCadastroClienteEscrita].mesContratacao = mesContratacao;
        clienteNovo[contadorCadastroClienteEscrita].anoContratacao = anoContratacao;
        strcpy(clienteNovo[contadorCadastroClienteEscrita].sevicoContratado, sevicoContratado);
        clienteNovo[contadorCadastroClienteEscrita].mensalidade = mensalidade;
        strcpy(clienteNovo[contadorCadastroClienteEscrita].usuarioAtendimento, colaboradorLogado1.usuario);
        clienteNovo[contadorCadastroClienteEscrita].status = status;
        contadorCadastroClienteEscrita++;
        /*Utilização da função "efetuarOperacaoNovamente", para testar se o usuário deseja efetuar cadastro novamente*/
        resposta = efetuarOperacaoNovamente(resposta);
    } while (resposta == 's' || resposta == 'S');
    /*Utilização da função "escritaArquivoColaborador" para gravar as informações da struct "cliente" no arquivo de cadastro
     de clientes*/
    escritaArquivoCliente();
}

/*Função "validacaoDataContratacao", criada para testar na hora do cadastro de cliente se a data inserida pelo usuario é valida ou não*/
int validacaoDataContratacao(int diaContratacao, int mesContratacao, int anoContratacao) {
    /*Estrutura "if-else" para testar a data no seguinte formato dd/mm/aa, dentro dos padrões de quantidade de dias, meses e anos*/
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
        return 1;/*Caso retorne 1 a data sera inválida*/
    }
}

/*Função "alterarStatusAtendimento" criada para edição do status do serviço contratado pelo cliente cadastrado*/
void alterarStatusAtendimento() {
    if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
        printf("\n\tNenhum cadastro encontrado\n");
    }
    else {
        int contadorAlterarStatus = 0, validacao = 1, status;
        char cnpj[100], resposta;
        /*Estrutura "do-while" responsável por coletar novo status fornecido pelo usuário, se repete enquanto os dados de CNPJ fornecidos
        forem inválidos e o usuário escolher efetuar a operação novamente*/
        do {
            /*Utilização da função "leituraArquivoCliente" para atualizar o programa com os dados do arquivo de clientes*/
            leituraArquivoCliente();

            system("clear");
            barraDeStatus();
            tabNove();
            printf("ALTERACAO DE STATUS DE ATENDIMENTO");
            linhaTres();

            do {
                printf("\tINFORME O CNPJ DO CLIENTE: ");
                scanf(" %99[^\n]", cnpj);
                printf("\tINFORME O STATUS 1 EM ANDAMENTO 2 FINALIZADO: ");
                scanf("%d", &status);
                /*Estrutura "while" onde são testados todos os CNPJ para encontrar o CNPJ digitado em meio aos cadastros atualizados da variável "clienteNovo" na struct "cliente"*/
                while(contadorAlterarStatus < contadorCadastroClienteLeitura) {
                    if(strcmp(cnpj,clienteNovo[contadorAlterarStatus].cnpj)==0) {
                        clienteNovo[contadorAlterarStatus].status = status;
                        validacao = 0;
                    }
                    contadorAlterarStatus++;
                }
                if(validacao != 0) {
                    printf("\tCNPJ invalido!\n");
                }
            } while(validacao != 0);
            /*Utilização da função "efetuarOperacaoNovamente", para teste se o usuário deseja efetuar alteração de outro status*/
            resposta = efetuarOperacaoNovamente(resposta);
        } while (resposta == 's' || resposta == 'S');
        /*Utilização da função "edicaoArquivoCliente" para reescrever o arquivo de cadastro de clientes com os dados alterados*/
        edicaoArquivoCliente();
    }
}

/*Função "edicaoArquivoCliente", responsável por limpar e reescrever o arquivo onde ficam armazenados os cadastros dos clientes*/
void edicaoArquivoCliente() {
    int contadorEdicao = 0;
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "w");/*Abertura de arquivo de modo que os dados sejam sobrescritos*/
    if (registroCadastroCliente == NULL) {
         /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
         /*Estrutura "while" que efetua a escrita no arquivo com a quantidade total de clientes que contem na variável "clienteNovo" da struct "cliente"*/
        while (contadorEdicao < contadorCadastroClienteLeitura) {
            fprintf(registroCadastroCliente, "%s-%s-%s-%s-%d-%d-%d-%s-%.2lf-%s-%d\n", clienteNovo[contadorEdicao].nomeRazaoSocial, clienteNovo[contadorEdicao].cnpj, clienteNovo[contadorEdicao].telefone, clienteNovo[contadorEdicao].email, clienteNovo[contadorEdicao].diaContratacao, clienteNovo[contadorEdicao].mesContratacao, clienteNovo[contadorEdicao].anoContratacao, clienteNovo[contadorEdicao].sevicoContratado, clienteNovo[contadorEdicao].mensalidade, clienteNovo[contadorEdicao].usuarioAtendimento, clienteNovo[contadorEdicao].status);
            contadorEdicao++;
        }
    }
    fclose(registroCadastroCliente);
}

/*Função "escritaArquivoCliente", responsável por adicionar novos cadastros de clientes ao arquivo*/
void escritaArquivoCliente() {
    int contadorEscrita = 0;
    registroCadastroCliente = fopen("arquivoCadastroCliente.txt", "a");
    if (registroCadastroCliente == NULL) {
        /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
         /*Estrutura "while" que efetua a adição dos dados da variável "clienteNovo" da struct "cliente" no arquivo*/
        while(contadorEscrita < contadorCadastroClienteEscrita) {
            fprintf(registroCadastroCliente, "%s-%s-%s-%s-%d-%d-%d-%s-%.2lf-%s-%d\n", clienteNovo[contadorEscrita].nomeRazaoSocial, clienteNovo[contadorEscrita].cnpj, clienteNovo[contadorEscrita].telefone, clienteNovo[contadorEscrita].email, clienteNovo->diaContratacao, clienteNovo->mesContratacao, clienteNovo->anoContratacao, clienteNovo[contadorEscrita].sevicoContratado, clienteNovo[contadorEscrita].mensalidade, clienteNovo[contadorEscrita].usuarioAtendimento, clienteNovo[contadorEscrita].status);
            contadorEscrita++;
        }
    }
    fclose(registroCadastroCliente);
}

/*Função "leituraArquivoCliente", responsável por efetuar a leitura do arquivo de cadastro de clientes e assim atualizar o programa com esses dados*/
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
        while (fscanf(registroCadastroCliente, " %99[^-]-%99[^-]-%99[^-]-%99[^-]-%d-%d-%d-%99[^-]-%lf-%99[^-]-%d", clienteNovo[contadorCadastroClienteLeitura].nomeRazaoSocial, clienteNovo[contadorCadastroClienteLeitura].cnpj, clienteNovo[contadorCadastroClienteLeitura].telefone, clienteNovo[contadorCadastroClienteLeitura].email, &clienteNovo[contadorCadastroClienteLeitura].diaContratacao, &clienteNovo[contadorCadastroClienteLeitura].mesContratacao, &clienteNovo[contadorCadastroClienteLeitura].anoContratacao , clienteNovo[contadorCadastroClienteLeitura].sevicoContratado, &clienteNovo[contadorCadastroClienteLeitura].mensalidade,clienteNovo[contadorCadastroClienteLeitura].usuarioAtendimento, &clienteNovo[contadorCadastroClienteLeitura].status) != EOF) {
            contadorCadastroClienteLeitura++;
        }
    }
    fclose(registroCadastroCliente);
}

/*Função "relatorioDeClientes", apresenta para o usuario o relatorio dos clientes atendidos pelo usuario logado*/
void relatorioDeClientes() {
    /*Teste efetuado com a função "access" para verificar se ja foi efetuado algum cadastro de cliente e criado o arquivo de cadastro, caso o teste retorne -1 sera
     informado ao usuario que não foi encontrado nenhum cadastro*/
    if(access("arquivoCadastroCliente.txt", F_OK) == -1) {
        printf("\n\tNenhum cadastro encontrado\n");
    }
    else {
        /*Utilização das funções "leituraArquivoColaborador" e "leituraArquivoCliente" para atualizar as  structs "colaborador" e "cliente" com os dados de cadastros que estão nos arquivos
         correspondentes*/
        leituraArquivoCliente();
        leituraArquivoColaborador();
        int contadorRelatorio = 0, teste;

        system("clear");
        barraDeStatus();
        tabNove();
        printf("RELATORIO DE CLIENTES");
        linhaTres();

         /*Estrutura "while" responsável por ler os dados da struct "colaboradorLogado" e "cliente' e apresentar o relatório dos clintes atendidos pelo usuário logado*/
        while(contadorRelatorio < contadorCadastroClienteLeitura) {
            teste = strcmp(colaboradorLogado1.usuario, clienteNovo[contadorRelatorio].usuarioAtendimento);
            if(teste == 0) {
                printf("\tRAZAO SOCIAL: %s\tCNPJ: %s\n\tTELEFONE: %s\t\tE-MAIL: %s\n\tDATA DE CONTRATACAO: %d/%d/%d\tSERVICO CONTRATADO: %s\n\tVALOR MENSAL: R$ %.2lf\tUSUARIO RESPONSAVEL: %s\n\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].diaContratacao, clienteNovo[contadorRelatorio].mesContratacao, clienteNovo[contadorRelatorio].anoContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade, clienteNovo[contadorRelatorio].usuarioAtendimento);
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

/*Função "relatorioGeralDeClientes", apresenta para o usuário o relatório geral de todos os clientes atendidos pelo colaborador logado e pelos demais colaboradores*/
void relatorioGeralDeClientes() {
    /*Estrutura "if-else" onde é testado se o usuário armazenado na struct "colaboradorLogado" tem permissão para gerar o relatório*/
    if(colaboradorLogado1.grupo == 2) {
        printf("\n\tUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        /*Teste efetuado com a função "access" para verificar se ja foi efetuado algum cadastro de cliente e criado o arquivo de cadastro, caso o teste retorne -1 sera
         informado ao usuário que não foi encontrado nenhum cadastro*/
        if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
            printf("\n\tNenhum cadastro encontrado\n");
        }
        else {
            /*Utilização da função "leituraArquivoCliente" para atualizar a struct "cliente" com os dados de cadastros de clientes e posteriormente apresentar ao usuário*/
            leituraArquivoCliente();
            int contadorRelatorio = 0;
            char resposta;

            system("clear");
            barraDeStatus();
            tabNove();
            printf("RELATORIO GERAL DE CLIENTES");
            linhaTres();
             /*Estrutura "while" responsável por ler os dados da struct "cliente" e apresentar o relatório dos mesmos ao usuário*/
            while (contadorRelatorio < contadorCadastroClienteLeitura) {
                printf("\tRAZAO SOCIAL: %s\tCNPJ: %s\n\tTELEFONE: %s\t\tE-MAIL: %s\n\tDATA DE CONTRATACAO: %d/%d/%d\tSERVICO CONTRATADO: %s\n\tVALOR MENSAL: R$ %.2lf\tUSUARIO RESPONSAVEL: %s\n\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].diaContratacao, clienteNovo[contadorRelatorio].mesContratacao, clienteNovo[contadorRelatorio].anoContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade, clienteNovo[contadorRelatorio].usuarioAtendimento);
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

/*Função "relatorioDeClientesPorUsuario", apresenta ao o usuário o relatório de clientes atendidos com a opção de filtrar o relatório com o usuário desejado*/
void relatorioDeClientesPorUsuario() {
    /*Estrutura "if-else" onde é testado se o colaborador armazenado na struct "colaboradorLogado" tem permissão para gerar o relatório*/
    if(colaboradorLogado1.grupo == 2) {
        printf("\n\tUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        /*Teste efetuado com a função "access" para verificar se ja foi efetuado algum cadastro de cliente e criado o arquivo de cadastro, caso o teste retorne -1 sera
         informado ao usuário que não foi encontrado nenhum cadastro*/
        if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
            printf("\n\tNenhum cadastro encontrado\n");
        }
        else {
            /*Utilização das funções "leituraArquivoColaborador" e "leituraArquivoCliente" para atualizar as  structs "colaborador" e "cliente" com os dados de cadastros correspondentes*/
            leituraArquivoColaborador();
            leituraArquivoCliente();

            int contadorRelatorio = 0, teste;
            char usuario[100];

            system("clear");
            barraDeStatus();
            tabNove();
            printf("RELATORIO DE CLIENTES POR USUARIO");
            linhaTres();
            printf("\tINFORME O USUARIO: ");
            scanf(" %99[^\n]", usuario);
            linhaDuas();
            /*Estrutura "while" responsável por ler os dados da struct "cliente" e comparar como o usuario informado para filtro e apresentar o relatório dos clientes correspondentes*/
            while (contadorRelatorio < contadorCadastroClienteLeitura) {
                teste = strcmp(usuario, clienteNovo[contadorRelatorio].usuarioAtendimento);
                if (teste == 0) {
                    printf("\tRAZAO SOCIAL: %s\tCNPJ: %s\n\tTELEFONE: %s\t\tE-MAIL: %s\n\tDATA DE CONTRATACAO: %d/%d/%d\tSERVICO CONTRATADO: %s\n\tVALOR MENSAL: R$ %.2lf\tUSUARIO RESPONSAVEL: %s\n\tSTATUS: ", clienteNovo[contadorRelatorio].nomeRazaoSocial, clienteNovo[contadorRelatorio].cnpj, clienteNovo[contadorRelatorio].telefone, clienteNovo[contadorRelatorio].email, clienteNovo[contadorRelatorio].diaContratacao, clienteNovo[contadorRelatorio].mesContratacao, clienteNovo[contadorRelatorio].anoContratacao, clienteNovo[contadorRelatorio].sevicoContratado, clienteNovo[contadorRelatorio].mensalidade, clienteNovo[contadorRelatorio].usuarioAtendimento);
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

/*Função "atualizacaoAreceberMesAtual", responsável por gerar o totalizador a receber dos atendimentos em andamento*/
void atualizacaoAreceberMesAtual() {
    /*Estrutura "if-else" onde é testado se o colaborador armazenado na struct "colaboradorLogado" tem permissão para gerar o relatório*/
    if(colaboradorLogado1.grupo == 2) {
        printf("\n\tUsuario sem permissao\n");
    }
    else if(colaboradorLogado1.grupo == 1) {
        /*Teste efetuado com a função "access" para verificar se ja foi efetuado algum cadastro de cliente e criado o arquivo, caso o teste retorne -1 sera
         informado ao usuário que não foi encontrado nenhum cadastro*/
        if (access("arquivoCadastroCliente.txt", F_OK) == -1) {
            printf("\n\tNenhum cadastro encontrado\n");
        }
        else {
            /*Utilização da função "leituraArquivoCliente" para atualizar a struct "cliente" com os dados de cadastros e posteriormente apresentar ao usuário*/
            leituraArquivoCliente();

            float totalAreceber = 0;
            int contadorRelatorio = 0;
            /*Estrutura while responsável por testar se o status do serviço prestado ao cliente encontra-se em andamento (status = 1) e efetuar a soma acumulativa dos valores cobrados com
             todos os clientes que constarem como em andamento*/
            while(contadorRelatorio < contadorCadastroClienteLeitura) {
                if(clienteNovo[contadorRelatorio].status == 1) {
                    totalAreceber = totalAreceber + clienteNovo[contadorRelatorio].mensalidade;
                }
                contadorRelatorio++;
            }
            system("clear");
            barraDeStatus();
            tabNove();
            printf("ATUALIZACAO MENSAL A RECEBER");
            linhaDuas();
            tabNove();
            printf("\tTOTAL: R$ %.2lf", totalAreceber);
            linhaTres();
        }
    }
}

/*Função "erroAberturaCriacaoArquivo" criada para formatar a mensagem de erro padrão apresentada caso o programa não consiga
 manipular os arquivos*/
void erroAberturaCriacaoArquivo() {
    system("clear");
    linhaTres();
    tabCinco();
    printf("\tErro ao abrir/criar o arquivo!\nPressione qualquer tecla para continuar...");
    getchar();getchar();
}

/*Função "efetuarOperacaoNovamente", criada para teste de resposta fornecida pelo usuário em ações repetitivas no programa
onde é necessário questionar se o usuário deseja efetuar operação novamente*/
char efetuarOperacaoNovamente(char resposta) {
            linhaDuas();
            printf("\tDeseja efetuar a operacao novamente (s) sim (n) nao? ");
            scanf(" %c", &resposta);

            while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
                printf("\tResposta invalida! Informe novamene: ");
                scanf(" %c", &resposta);
            }
    return(resposta);
}

/*Função "menuAjuda", apresenta ao usuário o menu com as opções de ajuda (suporte) ao usuário*/
void menuAjuda() {
    int opcao;

    system("clear");
    barraDeStatus();
    tabNove();
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

/*Função "manual", responsável por apresentar o manual de instruções do programa ao usuário logado*/
void manual() {
    system("clear");
    barraDeStatus();
    linhaDuas();
    tabSete();
    leituraArquivoManual();
    printf("%s", manualUtilizacaoUsuario.manual);
    printf("\tPressione qualquer teclar para continuar...");
    getchar();getchar();
}

/*Função "leituraArquivoManual" responsavel por apresentar ao usuario o manual de instruções do programa*/
void leituraArquivoManual() {
    registroManual = fopen("arquivoManualUtilizacaoUsuario.txt", "r");
    if (registroManual == NULL) {
         /*Caso não consiga efetuar a abertura do arquivo, sera executada a função "erroAberturaCriacaoArquivo" para apresentar a mensagem de erro padrão*/
        erroAberturaCriacaoArquivo();
    }
    else {
        rewind(registroManual);
         /*Estrutura "while" que efetua a leitura do arquivo onde esta o manual e atualiza a struct "manualUsuario"*/
        fscanf(registroManual, " %15000[^&]", manualUtilizacaoUsuario.manual) != EOF;
    }
    fclose(registroManual);
}

/*Função "contatoSuporte", responsável por apresentar ao usuário os meios de contato com o suporte do sistema*/
void contatoSuporte() {
    system("clear");
    barraDeStatus();
    tabNove();
    printf("CONTATOS SUPORTE");
    linhaTres();
    printf("\tE-MAIL: suporte@suporte.com.br\tCHAT: chat.com.br\n");
    printf("\tTELEFONE: (00) 0000-0000\tCELULAR: (00)00000-0000\n");
    linhaDuas();
    printf("\tPressione qualquer tecla para continuar...");
    getchar();getchar();
}

/*Função "menuInicial" responsável por apresentar e gerenciar o acesso ao o menu de ações possíveis de serem executadas no programa e receber a opção escolhida pelo usuário logado e executar a função
 necessária para realizar a ação escolhida*/
void menuInicial() {
    int opcao;
    char resposta;
    do {
        system("clear");
        barraDeStatus();
        tabNove();
        printf("MENU INICIAL");
        linhaTres();
        printf("\t-1.Cadastro de usuario\n\t-2.Alterar senha\n\t-3.Alterar status de usuario\n\t-4.Relatorio de usuarios\n\t-5.Cadastro de cliente\n\t-6.Alterar Status de cliente\n\t-7.Relatorio de clientes\n\t-8.Relatorio geral de clientes\n\t-9.Relatorio de clientes por usuario\n\t-10.Atualizacao a receber mes atual\n\t+11.Ajuda\n\t-12.Sair\n\n\tOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            cadastroColaborador();
            break;
        case 2:
            alterarSenhaColaborador();
            break;
        case 3:
            alteracaoStatusColaborador();
            break;
        case 4:
            relatorioCadastroColaboradores();
            break;
        case 5:
            cadastroCliente();
            break;
        case 6:
            alterarStatusAtendimento();
            break;
        case 7:
            relatorioDeClientes();
            break;
        case 8:
            relatorioGeralDeClientes();
            break;
        case 9:
            relatorioDeClientesPorUsuario();
            break;
        case 10:
            atualizacaoAreceberMesAtual();
            break;
        case 11:
            menuAjuda();
            break;
        case 12:
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

        if(opcao != 12) {
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
    /*Execução da função "data" para atualizar sempre que o programa for inicializado*/
    data();
    /*Execução da função "usuarioAdmin" para verificar se ja existe algum usuário cadastrado, caso não tenha sera criado o usuário "admin" para o primeiro acesso */
    usuarioAdmin();

    /*Estrutura "if" que recebe o retorno da função "login", e caso seja igual a 0 (credenciais corretas) direciona para a função "menuInicial")*/
    if (login() == 0) {
        menuInicial();
    }

    return 0;
}