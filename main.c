#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAXIMO_NUMERO_ESCOLAS 5        // Define o numero maximo de escolas que podem ser registadas
#define MAXIMO_NUMERO_UTILIZADORES 200 // Define o numero maximo de utilizadores que podem ser registados
#define MAXIMO_NUMERO_TRANSACOES 5000  // Define o numero maximo de transacoes que podem ser registadas
#define NOME_FICHEIRO_ESCOLAS "escolas.dat"
#define NOME_FICHEIRO_UTILIZADORES "utilizadores.dat"
#define NOME_FICHEIRO_TRANSACOES "transacoes.dat"

typedef struct // Cria uma STRUCT para armazenar as datas
{
    int dia; // define o campo do dia
    int mes; // define o campo do mês
    int ano; // define o campo do ano
} data;

typedef struct // Cria uma STRUCT para armazenar as horas
{
    int horas;    // define o campo das horas
    int minutos;  // define o campo dos minutos
    int segundos; // define o campo dos segundos
} hora;

typedef struct // Cria uma STRUCT para armazenar os dados das escolas
{
    int id;               // define o campo identificador único
    char nome_escola[80]; // define o campo nome da escola
    char abreviatura[8];  // define o campo abreviatura
    int campus;           // define o campo campus
    char localidade[20];  // define o campo localidade
} t_escola;

typedef struct // Cria uma STRUCT para armazenar os dados de um utilizador
{
    int id;                   // define o campo identificador único
    int id_escola;            // define o campo identificador único da escola
    char nome[80];            // define o campo nome
    int nif;                  // define o campo nif
    char tipo_utilizador[15]; // define o campo tipo de utilizador
    char email[80];           // define o campo email
    float saldo;              // define o campo saldo
} t_utilizador;

typedef struct // Cria uma STRUCT para armazenar os dados das transações
{
    int id;                  // define o campo identificador único
    int id_utilizador;       // define o campo indetificador único do utilizador
    char tipo_transacao[13]; // define o campo tipo de transação
    float valor_transacao;   // define o campo valor da transação
    data data_transacao;     // define o campo data da transação
    hora hora_transacao;     // define o campo hora da transação
} t_transacao;

int menu();              // Apresenta o menu principal
int menu_utilizadores(); // Apresenta as opcoes referentes a consulta de utilizadores
int menu_transacoes();   // Apresenta as opcoes referentes as transacoes
int menu_estatisticas();
int registar_utilizador(t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int nif_utilizador, int num_escolas);            // Regista um novo utilizador
int registar_transacoes(t_transacao v_transacoes[], t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_transacoes); // Regista uma nova transacao
int registar_escola(t_escola v_escolas[], int num_escolas);                                                                                         // Regista uma nova escola
void consultar_utilizadores(t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores);                                             // Apresenta todos os utilizadores
void consultar_escolas(t_escola v_escolas[], int numero_escolas);                                                                                   // Apresenta todas as escolas
int mostrar_utilizador(t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_escolas);                                 // Permite a pesquisa de um utilizador por nif
int procurar_utilizador(t_utilizador v_utilizadores[], int num_utilizadores, int nif_utilizador);                                                   // Verifica se um utilizador e devolve a sua posição no vetor
int escolhe_escola(t_escola v_escolas[], int numero_escolas);                                                                                       // Apresenta as escolas disponiveis para registar o utilizador
void escolhe_utilizador(t_utilizador v_utilizadores[], int num_utilizadores);                                                                       // Apresenta os tipos de utilizadores disponiveis para registar o utilizador
char confirmar_saida();                                                                                                                             // Confirma se o utilizador realmente que fechar o programa
void inicias(char nome_completo[], t_escola v_escolas[], int num_escolas);                                                                          // Retira as inicias do nome completo da escola
int ler_ficheiro_escolas(t_escola v_escolas[]);                                                                                                     // Importa os dados das escolas do ficheiro binario
int ler_ficheiro_utilizadores(t_utilizador v_utilizadores[]);                                                                                       // Importa os dados dos utilizadores do ficheiro binario
int ler_ficheiro_transacoes(t_transacao v_transacoes[]);                                                                                            // Importa os dados das transacoes do ficheiro binario
void gravar_ficheiro(t_escola v_escolas[], int num_escolas);                                                                                        // Grava os dados das escolas no ficheiro binario
void gravar_ficheiro_utilizadores(t_utilizador v_utilizadores[], int num_utilizadores);                                                             // Grava os dados dos utilizadores no ficheiro binario
void gravar_ficheiro_transacoes(t_transacao v_transacoes[], int num_transacoes);                                                                    // Grava os dados das transacoes no ficheiro binario
void tipo_transacao(t_transacao v_transacoes[], int num_transacoes);
void valor_trasacao(t_transacao v_transacoes[], t_utilizador v_utilizadores[], int posicao_utilizador, int num_transacoes);
void valor_trasacao(t_transacao v_transacoes[], t_utilizador v_utilizadores[], int posicao_utilizador, int num_transacoes);
void consultar_transacoes(t_transacao v_transacoes[], int num_transacoes);
void total_escola(t_transacao v_transacoes[], t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_transacoes, int num_escolas);
void percentagem_transacoes(t_transacao v_transacoes[], t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_transacoes, int num_escolas);
void total_transacoes_filtrado(t_transacao v_transacoes[], t_utilizador v_utilizadores[], int num_utilizadores, int num_transacoes);
data procura_data(t_transacao v_transacoes[], int num_transacoes);
void total_por_utilizador(t_transacao v_transacoes[], t_utilizador v_utilizadores[], int num_utilizadores, int num_transacoes, data data1, data data2, int total_pagamentos_utilizado[]);

int main()
{
    char saida;
    int escolas_registadas[4], opcao, numero_escolas = 0, numero_utilizadores = 0, numero_transacoes = 0;
    t_escola escolas[MAXIMO_NUMERO_ESCOLAS];
    t_utilizador utilizadores[MAXIMO_NUMERO_UTILIZADORES];
    t_transacao transacoes[MAXIMO_NUMERO_TRANSACOES];
    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            if (numero_escolas >= MAXIMO_NUMERO_ESCOLAS)
            {
                printf("\nNao e possivel adicionar mais escolas!\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
            else
            {
                numero_escolas = registar_escola(escolas, numero_escolas);
            }
            break;
        case 2:
            if (numero_escolas > 0)
            {
                consultar_escolas(escolas, numero_escolas);
                printf("\n\nFim da lista. Clique enter para continuar.");
                fflush(stdin);
                getchar();
            }
            else
            {
                printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
            break;
        case 3:
            if (numero_escolas > 0)
            {
                if (numero_utilizadores >= MAXIMO_NUMERO_UTILIZADORES)
                {
                    printf("\nNao e possivel adicionar mais utilizadores!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                }
                else
                {
                    numero_utilizadores = registar_utilizador(utilizadores, escolas, numero_utilizadores, 0, numero_escolas);
                    printf("\nUtilizador registado com sucesso!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                }
            }
            else
            {
                printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
            break;
        case 4:
            if (numero_escolas > 0)
            {
                if (numero_utilizadores > 0)
                {
                    switch (menu_utilizadores())
                    {
                    case 1:
                        consultar_utilizadores(utilizadores, escolas, numero_utilizadores);
                        printf("\n\nFim da lista. Clique enter para continuar.");
                        fflush(stdin);
                        getchar();
                        break;
                    case 2:
                        numero_utilizadores = mostrar_utilizador(utilizadores, escolas, numero_utilizadores, numero_escolas);
                        printf("\n\nFim da lista. Clique enter para continuar.");
                        fflush(stdin);
                        getchar();
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    printf("\nNao foram introduzidos alunos!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                }
            }
            else
            {
                printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
            break;
        case 5:
            if (numero_transacoes < MAXIMO_NUMERO_TRANSACOES)
            {
                if (numero_escolas > 0)
                {
                    if (numero_utilizadores > 0)
                    {
                        switch (menu_transacoes())
                        {
                        case 1:
                            numero_transacoes = registar_transacoes(transacoes, utilizadores, escolas, numero_utilizadores, numero_transacoes);
                            break;
                        case 2:
                            consultar_transacoes(transacoes, numero_transacoes);
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        printf("\nNao foram introduzidos alunos!\n\nClique enter para continuar.");
                        fflush(stdin);
                        getchar();
                    }
                }
                else
                {
                    printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                }
            }
            else
            {
                printf("\nNao e possivel adicionar mais transacoes!\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
            break;
        case 6:
            if (numero_transacoes != 0)
            {
                opcao = menu_estatisticas();
                switch (opcao)
                {
                case 1:
                    total_escola(transacoes, utilizadores, escolas, numero_utilizadores, numero_transacoes, numero_escolas);
                    break;
                case 2:
                    percentagem_transacoes(transacoes, utilizadores, escolas, numero_utilizadores, numero_transacoes, numero_escolas);
                    break;
                case 3:
                    total_transacoes_filtrado(transacoes, utilizadores, numero_utilizadores, numero_transacoes);
                    break;
                }
            }
            else
            {
                if (numero_utilizadores == 0)
                {
                    printf("Tem de introduzir utilizadores\n");
                }
                else
                {
                    printf("Tem de introduzir transacoes\n");
                }
            }
            break;
        case 7:
            if (numero_escolas > 0)
            {
                gravar_ficheiro_escolas(escolas, numero_escolas);
                if (numero_utilizadores > 0)
                {
                    gravar_ficheiro_utilizadores(utilizadores, numero_utilizadores);
                    if (numero_transacoes > 0)
                        gravar_ficheiro_transacoes(transacoes, numero_transacoes);
                    else
                    {
                        printf("\nNao foram introduzidas transacoes!\n\nClique enter para continuar.");
                        fflush(stdin);
                        getchar();
                    }
                }
                else
                {
                    printf("\nNao foram introduzidos utilizadores!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                }
            }
            else
            {
                printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
            break;
        case 8:
            if (numero_transacoes == 0)
            {
                numero_transacoes = ler_ficheiro_transacoes(transacoes);
                if (numero_utilizadores == 0)
                {
                    numero_utilizadores = ler_ficheiro_utilizadores(utilizadores);
                    if (numero_escolas == 0)
                    {
                        numero_escolas = ler_ficheiro_escolas(escolas);
                        fflush(stdin);
                        getchar();
                    }
                    else
                    {
                        printf("\nJa estao escolas registadas!\n\nClique enter para continuar.");
                        fflush(stdin);
                        getchar();
                    }
                }
                else
                {
                    printf("\nJa estao utilizadores registados!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                }
            }
            else
            {
                printf("\nJa estao transacoes registadas!\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
            break;
        case 0:
            saida = confirmar_saida();
        default:
            break;
        }
    } while (saida != 'S');
    if (numero_escolas != 0)
        gravar_ficheiro_escolas(escolas, numero_escolas);
    if (numero_utilizadores != 0)
        gravar_ficheiro_utilizadores(utilizadores, numero_utilizadores);
    if (numero_transacoes != 0)
        gravar_ficheiro_transacoes(transacoes, numero_transacoes);
    return 0;
}

void consultar_escolas(t_escola v_escolas[], int num_escolas)
{
    int indice;
    system("cls");
    printf("\nDados das escolas\n");
    printf("Numero\tNome\t\t\t\t\t\t\tAbreviatura\tCampus\t\tLocalidade\n");
    for (indice = 0; indice < num_escolas; indice++)
    {
        printf("%d\t%s\t\t\t%s\t\t%d\t%s\n", v_escolas[indice].id, v_escolas[indice].nome_escola, v_escolas[indice].abreviatura, v_escolas[indice].campus, v_escolas[indice].localidade);
    }
}

int registar_escola(t_escola v_escolas[], int num_escolas)
{
    int opcao;
    v_escolas[num_escolas].id = num_escolas + 1;
    printf("\nRegistar nova escola\n\nNome: ");
    scanf(" %80[^\n]s", &v_escolas[num_escolas].nome_escola);
    inicias(v_escolas[num_escolas].nome_escola, v_escolas, num_escolas);
    do
    {
        printf("\nCampus (1 a 4): ");
        printf("\n\nOpcao: ");
        scanf(" %d", &opcao);
        if (opcao < 1 || opcao > 4)
        {
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while (opcao < 1 || opcao > 4);
    v_escolas[num_escolas].campus = opcao;
    printf("\nLocalidade: ");
    scanf(" %20[^\n]s", &v_escolas[num_escolas].localidade);
    return num_escolas + 1;
}

void inicias(char nome_completo[], t_escola v_escolas[], int num_escolas) // codigo proveniente da ficha 6 ex 6
{
    int tamanho, indice, pos_sigla = 1;
    char abreviatura[8] = {'\o'};
    tamanho = strlen(nome_completo);
    for (indice = 0; indice < tamanho; indice++)
    {
        if (indice == 0)
            abreviatura[0] = toupper(nome_completo[indice]);
        else if ((nome_completo[indice - 1] == ' ' && nome_completo[indice] != ' ') && (nome_completo[indice] != 'd' && (nome_completo[indice + 1] != 'e' || nome_completo[indice + 2] != ' ')))
            if (nome_completo[indice] != 'e' && nome_completo[indice + 1] != ' ')
            {
                abreviatura[pos_sigla] = toupper(nome_completo[indice]);
                pos_sigla++;
            }
    }
    strcpy(v_escolas[num_escolas].abreviatura, abreviatura);
}

int menu_transacoes()
{
    int opcao;
    do
    {
        system("cls");
        printf("\nRegistar/consultar os dados das transacoes:\n");
        printf("\n1 - Criar nova transacao");
        printf("\n2 - Consultar todas as transacoes");
        printf("\n0 - Voltar para o menu principal");
        printf("\n\nOpcao: ");
        scanf(" %d", &opcao);
        if (opcao < 0 || opcao > 2)
        {
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while (opcao < 0 || opcao > 2);
    return opcao;
}

int menu_utilizadores()
{
    int opcao;
    do
    {
        system("cls");
        printf("Consultar dados dos utilizadores\n");
        printf("\n1 - Consultar todos os utilizadores");
        printf("\n2 - Pesquisar utilizador por nif");
        printf("\n0 - Voltar para o menu principal");
        printf("\n\nOpcao: ");
        scanf(" %d", &opcao);
        if (opcao < 0 || opcao > 2)
        {
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while (opcao < 0 || opcao > 2);
    return opcao;
}

int menu()
{
    int opcao;
    do
    {
        system("cls");
        printf("\nMenu de Opcoes\n");
        printf("\n1 - Registar nova escola");
        printf("\n2 - Consultar dados das escolas");
        printf("\n3 - Registar novo utilizador");
        printf("\n4 - Consultar dados dos utilizadores");
        printf("\n5 - Registar/consultar os dados das transacoes");
        printf("\n6 - Estatisticas");
        printf("\n7 - Gravar dados em ficheiro");
        printf("\n8 - Ler dados de ficheiro");
        printf("\n0 - Sair");
        printf("\n\nOpcao: ");
        scanf(" %d", &opcao);
        if (opcao < 0 || opcao > 8)
        {
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while (opcao < 0 || opcao > 8);
    return opcao;
}

char confirmar_saida()
{
    char escolha;
    printf("\nConfirma saida (S/N): ");
    do
    {
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        if (escolha != 'S' && escolha != 'N')
        {
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while (escolha != 'S' && escolha != 'N');
    return escolha;
}

int registar_utilizador(t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int nif_utilizador, int num_escolas)
{
    int utilizador_existe = -1, indice, numero;
    if (nif_utilizador == 0)
    {
        do
        {
            do
            {
                indice = 0;
                printf("\nIntroduzir nif do utilizador: ");
                scanf(" %d", &nif_utilizador);
                numero = nif_utilizador;
                while (numero != 0)
                {
                    numero = numero / 10;
                    indice++;
                }
                if (indice != 9)
                {
                    printf("\nO nif inserido nao tem 9 digitos.\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                }
            } while (indice != 9);

            utilizador_existe = procurar_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);
            if (utilizador_existe == -1)
            {
                v_utilizadores[num_utilizadores].nif = nif_utilizador;
            }
            else
            {
                printf("\nO utilizador com o nif %d ja existe!\n\nClique enter para continuar.", nif_utilizador);
                fflush(stdin);
                getchar();
            }
        } while (utilizador_existe != -1);
    }
    else
    {
        v_utilizadores[num_utilizadores].nif = nif_utilizador;
    }
    v_utilizadores[num_utilizadores].id = num_utilizadores + 1; // adiciona 1 ao ultimo id
    v_utilizadores[num_utilizadores].id_escola = escolhe_escola(v_escolas, num_escolas);
    escolhe_utilizador(v_utilizadores, num_utilizadores);
    v_utilizadores[num_utilizadores].saldo = 0;
    printf("\nNome: ");
    scanf(" %80[^\n]s", v_utilizadores[num_utilizadores].nome);
    printf("Email: ");
    scanf(" %80[^\n]s", v_utilizadores[num_utilizadores].email);
    return num_utilizadores + 1;
}

void escolhe_utilizador(t_utilizador v_utilizadores[], int num_utilizadores)
{
    int opcao;
    char utilizador[15] = {'\o'};
    do
    {
        printf("\nTipo de utilizador:\n\n1- Estudante\n2- Docente\n3- Funcionario\n\nOpcao: ");
        scanf(" %d", &opcao);
        if (opcao < 0 || opcao > 3)
        {
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while (opcao < 0 || opcao > 3);
    switch (opcao)
    {
    case 1:
        strcpy(utilizador, "Estudante");
        break;
    case 2:
        strcpy(utilizador, "Docente");
        break;
    case 3:
        strcpy(utilizador, "Funcionario");
        break;
    default:
        break;
    }
    strcpy(v_utilizadores[num_utilizadores].tipo_utilizador, utilizador);
}

int escolhe_escola(t_escola v_escolas[], int num_escolas)
{
    int opcao, indice;
    do
    {
        printf("\nEscolha a escola\n");
        for (indice = 0; indice < num_escolas; indice++)
        {
            printf("\n%d- %s", indice + 1, v_escolas[indice].abreviatura);
        }
        printf("\n\nOpcao: ");
        scanf(" %d", &opcao);
        if (opcao < 0 || opcao > num_escolas)
        {
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while (opcao < 0 || opcao > num_escolas);
    return opcao;
}

int procurar_utilizador(t_utilizador v_utilizadores[], int num_utilizadores, int nif_utilizador)
{
    int encontrou_utilizador = -1, indice;
    for (indice = 0; indice < num_utilizadores; indice++)
    {
        if (v_utilizadores[indice].nif == nif_utilizador)
        {
            encontrou_utilizador = indice;
        }
    }
    return encontrou_utilizador;
}

void consultar_utilizadores(t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores)
{
    int indice;
    printf("\nDados dos utilizadores\n");
    printf("Numero\tNome\t\t\t\tEscola\tNIF\t\tTipo\t\tE-mail\t\t\tSaldo\n");
    for (indice = 0; indice < num_utilizadores; indice++)
    {
        printf("%d\t%s\t\t\t%s\t%d\t%s\t%s\t%.2f\n", v_utilizadores[indice].id, v_utilizadores[indice].nome, v_escolas[v_utilizadores[indice].id_escola - 1].abreviatura, v_utilizadores[indice].nif, v_utilizadores[indice].tipo_utilizador, v_utilizadores[indice].email, v_utilizadores[indice].saldo);
    }
}

int mostrar_utilizador(t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_escolas)
{
    int encontrou_utilizador, nif_utilizador, indice, numero;
    char opcao;
    do
    {
        do
        {
            indice = 0;
            printf("\nPesquisar utilizador por nif\n\nIntroduzir nif do utilizador: ");
            scanf(" %d", &nif_utilizador);
            numero = nif_utilizador;
            while (numero != 0)
            {
                numero = numero / 10;
                indice++;
            }
            if (indice != 9)
            {
                printf("\nO nif inserido nao tem 9 digitos.\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
        } while (indice != 9);
        encontrou_utilizador = procurar_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);
        if (encontrou_utilizador == -1)
        {
            printf("\nO utilizador com o nif %d nao existe!\nDeseja criar um utilizador com esse nif? (S/N) ", nif_utilizador);
            do
            {
                scanf(" %c", &opcao);
                opcao = toupper(opcao);
                if (opcao != 'S' && opcao != 'N')
                {
                    printf("\nEscolha invalida!");
                    fflush(stdin);
                    getchar();
                }
                else if (opcao == 'S')
                {
                    num_utilizadores = registar_utilizador(v_utilizadores, v_escolas, num_utilizadores, nif_utilizador, num_escolas);
                    encontrou_utilizador = -2;
                }
            } while (opcao != 'S' && opcao != 'N');
        }
        else
        {
            printf("Numero\tNome\t\t\t\tEscola\tNIF\t\tTipo\t\tE-mail\t\t\tSaldo\n%d\t%s\t\t\t%s\t%d\t%s\t%s\t%.2f\n", v_utilizadores[encontrou_utilizador].id, v_utilizadores[encontrou_utilizador].nome, v_escolas[v_utilizadores[encontrou_utilizador].id_escola - 1].abreviatura, v_utilizadores[encontrou_utilizador].nif, v_utilizadores[encontrou_utilizador].tipo_utilizador, v_utilizadores[encontrou_utilizador].email, v_utilizadores[encontrou_utilizador].saldo);
        }
    } while (encontrou_utilizador == -1);
    return num_utilizadores;
}

int ler_ficheiro_escolas(t_escola v_escolas[]) // codigo proveniente da ficha 7 ex 1
{
    int num_escolas = 0, num_escolas_lidas;
    FILE *ficheiro;
    ficheiro = fopen(NOME_FICHEIRO_ESCOLAS, "rb");
    if (ficheiro == NULL)
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", NOME_FICHEIRO_ESCOLAS);
        num_escolas_lidas = 0;
    }
    else
    {
        fread(&num_escolas, sizeof(int), 1, ficheiro);
        num_escolas_lidas = fread(v_escolas, sizeof(t_escola), num_escolas, ficheiro);
        fclose(ficheiro);
        if (num_escolas != num_escolas_lidas)
        {
            printf("\nErro na leitura do ficheiro %s", NOME_FICHEIRO_ESCOLAS);
            num_escolas_lidas = 0;
        }
        else
        {
            printf("\nLeitura dos dados de %d escolas a partir do ficheiro %s feita com sucesso.\n", num_escolas, NOME_FICHEIRO_ESCOLAS);
        }
    }
    num_escolas = num_escolas_lidas;
    return num_escolas;
}

int ler_ficheiro_utilizadores(t_utilizador v_utilizadores[]) // codigo proveniente da ficha 7 ex 1
{
    int num_utilizadores = 0, num_utilizadores_lidos;
    FILE *ficheiro;
    ficheiro = fopen(NOME_FICHEIRO_UTILIZADORES, "rb");
    if (ficheiro == NULL)
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", NOME_FICHEIRO_UTILIZADORES);
        num_utilizadores_lidos = 0;
    }
    else
    {
        fread(&num_utilizadores, sizeof(int), 1, ficheiro);
        num_utilizadores_lidos = fread(v_utilizadores, sizeof(t_utilizador), num_utilizadores, ficheiro);
        fclose(ficheiro);
        if (num_utilizadores != num_utilizadores_lidos)
        {
            printf("\nErro na leitura do ficheiro %s", NOME_FICHEIRO_UTILIZADORES);
            num_utilizadores_lidos = 0;
        }
        else
        {
            printf("\nLeitura dos dados de %d utilizadores a partir do ficheiro %s feita com sucesso.\n", num_utilizadores, NOME_FICHEIRO_UTILIZADORES);
        }
    }
    num_utilizadores = num_utilizadores_lidos;
    return num_utilizadores;
}

int ler_ficheiro_transacoes(t_transacao v_transacoes[]) // codigo proveniente da ficha 7 ex 1
{
    int num_transacoes = 0, num_transacoes_lidas;
    FILE *ficheiro;
    ficheiro = fopen(NOME_FICHEIRO_TRANSACOES, "rb");
    if (ficheiro == NULL)
    {
        printf("\nNao foi possivel abrir o ficheiro %s\n", NOME_FICHEIRO_TRANSACOES);
        num_transacoes_lidas = 0;
    }
    else
    {
        fread(&num_transacoes, sizeof(int), 1, ficheiro);
        num_transacoes_lidas = fread(v_transacoes, sizeof(t_transacao), num_transacoes, ficheiro);
        fclose(ficheiro);
        if (num_transacoes != num_transacoes_lidas)
        {
            printf("\nErro na leitura do ficheiro %s", NOME_FICHEIRO_TRANSACOES);
            num_transacoes_lidas = 0;
        }
        else
        {
            printf("\nLeitura dos dados de %d transacoes a partir do ficheiro %s feita com sucesso.\n", num_transacoes, NOME_FICHEIRO_TRANSACOES);
        }
    }
    num_transacoes = num_transacoes_lidas;
    return num_transacoes;
}

void gravar_ficheiro_escolas(t_escola v_escolas[], int num_escolas) // codigo proveniente da ficha 7 ex 1
{
    FILE *ficheiro;
    ficheiro = fopen(NOME_FICHEIRO_ESCOLAS, "wb");
    if (ficheiro == NULL)
    {
        printf("\nNao foi possivel criar o ficheiro!");
        fflush(stdin);
        getchar();
    }
    else
    {
        fwrite(&num_escolas, sizeof(int), 1, ficheiro);
        fwrite(v_escolas, sizeof(t_escola), num_escolas, ficheiro);
        fclose(ficheiro);
        printf("\nEscrita dos dados de %d escolas no ficheiro %s com sucesso!", num_escolas, NOME_FICHEIRO_ESCOLAS);
    }
}

void gravar_ficheiro_utilizadores(t_utilizador v_utilizadores[], int num_utilizadores) // codigo proveniente da ficha 7 ex 1
{
    FILE *ficheiro;
    ficheiro = fopen(NOME_FICHEIRO_UTILIZADORES, "wb");
    if (ficheiro == NULL)
    {
        printf("\nNao foi possivel criar o ficheiro!");
        fflush(stdin);
        getchar();
    }
    else
    {
        fwrite(&num_utilizadores, sizeof(int), 1, ficheiro);
        fwrite(v_utilizadores, sizeof(t_utilizador), num_utilizadores, ficheiro);
        fclose(ficheiro);
        printf("\nEscrita dos dados de %d utilizadores no ficheiro %s com sucesso!", num_utilizadores, NOME_FICHEIRO_UTILIZADORES);
    }
}

void gravar_ficheiro_transacoes(t_transacao v_transacoes[], int num_transacoes) // codigo proveniente da ficha 7 ex 1
{
    FILE *ficheiro;
    ficheiro = fopen(NOME_FICHEIRO_TRANSACOES, "wb");

    if (ficheiro == NULL)
    {
        printf("\nNao foi possivel criar o ficheiro!");
        fflush(stdin);
        getchar();
    }
    else
    {
        fwrite(&num_transacoes, sizeof(int), 1, ficheiro);
        fwrite(v_transacoes, sizeof(t_transacao), num_transacoes, ficheiro);
        fclose(ficheiro);
        printf("\nEscrita dos dados de %d transacoes no ficheiro %s com sucesso!", num_transacoes, NOME_FICHEIRO_TRANSACOES);
    }
}

int registar_transacoes(t_transacao v_transacoes[], t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_transacoes)
{
    int posicao_utilizador, indice, numero;
    v_transacoes[num_transacoes].id = num_transacoes + 1;
    do
    {
        consultar_utilizadores(v_utilizadores, v_escolas, num_utilizadores);
        do
        {
            indice = 0;
            printf("Insira o NIF do utilizador que esta realizar a operacao\n");
            scanf(" %d", &posicao_utilizador);
            numero = posicao_utilizador;
            while (numero != 0)
            {
                numero = numero / 10;
                indice++;
            }
            if (indice != 9)
            {
                printf("\nO nif inserido nao tem 9 digitos.\n\nClique enter para continuar.");
                fflush(stdin);
                getchar();
            }
        } while (indice != 9);
        posicao_utilizador = procurar_utilizador(v_utilizadores, num_utilizadores, posicao_utilizador);
        if (posicao_utilizador < 0)
        {
            printf("O NIF que inseriu nao e valido. Clique enter para continuar.\n");
            fflush(stdin);
            getchar();
        }
        else
        {
            v_transacoes[num_transacoes].id_utilizador = v_utilizadores[posicao_utilizador].id;
        }
    } while (posicao_utilizador < 0);
    tipo_transacao(v_transacoes, num_transacoes);
    valor_trasacao(v_transacoes, v_utilizadores, posicao_utilizador, num_transacoes);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    v_transacoes[num_transacoes].data_transacao.dia = tm.tm_mday;
    v_transacoes[num_transacoes].data_transacao.mes = tm.tm_mon + 1;
    v_transacoes[num_transacoes].data_transacao.ano = tm.tm_year + 1900;
    v_transacoes[num_transacoes].hora_transacao.segundos = tm.tm_sec;
    v_transacoes[num_transacoes].hora_transacao.minutos = tm.tm_min;
    v_transacoes[num_transacoes].hora_transacao.horas = tm.tm_hour;
    return num_transacoes + 1;
}

void tipo_transacao(t_transacao v_transacoes[], int num_transacoes)
{
    int tipo_transacao;
    do
    {
        printf("Escolha o tipo de transacao:\n1 - Pagamento\n2 - Carregamento\n");
        scanf(" %d", &tipo_transacao);
        if (tipo_transacao < 1 || tipo_transacao > 2)
        {
            printf("Tipo de transacao invalido. Clique enter para continuar.\n");
            fflush(stdin);
            getchar();
        }
    } while (tipo_transacao < 1 || tipo_transacao > 2);
    if (tipo_transacao == 1)
    {
        strcpy(v_transacoes[num_transacoes].tipo_transacao, "Pagamento");
    }
    else
    {
        strcpy(v_transacoes[num_transacoes].tipo_transacao, "Carregamento");
    }
}

void valor_trasacao(t_transacao v_transacoes[], t_utilizador v_utilizadores[], int posicao_utilizador, int num_transacoes)
{
    float saldo;
    if (!strncmp(v_transacoes[num_transacoes].tipo_transacao, "Pagamento", 13))

    {
        do
        {
            printf("Insira o valor do %s\n", v_transacoes[num_transacoes].tipo_transacao);
            scanf(" %f", &v_transacoes[num_transacoes].valor_transacao);
            if (v_transacoes[num_transacoes].valor_transacao < 0)
            {
                printf("Nao e permitido negativos. Clique enter para continuar.\n");
                fflush(stdin);
                getchar();
            }
            else
            {
                saldo = v_utilizadores[posicao_utilizador].saldo;
                if ((saldo - v_transacoes[num_transacoes].valor_transacao) >= 0)
                {
                    v_utilizadores[posicao_utilizador].saldo -= v_transacoes[num_transacoes].valor_transacao;
                }
                else
                {
                    printf("Nao tem saldo suficiente. Clique enter para continuar.\n");
                    fflush(stdin);
                    getchar();
                }
            }
        } while (v_transacoes[num_transacoes].valor_transacao < 0 || (saldo - v_transacoes[num_transacoes].valor_transacao) < 0);
    }
    else
    {
        do
        {
            printf("Insira o valor do %s\n", v_transacoes[num_transacoes].tipo_transacao);
            scanf(" %f", &v_transacoes[num_transacoes].valor_transacao);
            if (v_transacoes[num_transacoes].valor_transacao < 0)
            {
                printf("Nao e permitido negativos. Clique enter para continuar.\n");
                fflush(stdin);
                getchar();
            }
        } while (v_transacoes[num_transacoes].valor_transacao < 0);
        v_utilizadores[posicao_utilizador].saldo += v_transacoes[num_transacoes].valor_transacao;
    }
    printf("%s efetuado com sucesso. Clique enter para continuar.\n", v_transacoes[num_transacoes].tipo_transacao);
    fflush(stdin);
    getchar();
}

void consultar_transacoes(t_transacao v_transacoes[], int num_transacoes)
{
    int indice;
    system("cls");
    printf("\nDados das transacoes\n");
    printf("Numero\tNumero do utilizador\tTipo da transacao\tValor da transacao\tData da transacao\tHora da transacao\n");
    for (indice = 0; indice < num_transacoes; indice++)
    {
        printf("%d\t%d\t\t\t%s\t\t\t%.2f\t\t%d/%d/%d\t\t%d:%d:%d\n", v_transacoes[indice].id, v_transacoes[indice].id_utilizador, v_transacoes[indice].tipo_transacao, v_transacoes[indice].valor_transacao, v_transacoes[indice].data_transacao.ano, v_transacoes[indice].data_transacao.mes, v_transacoes[indice].data_transacao.dia, v_transacoes[indice].hora_transacao.horas, v_transacoes[indice].hora_transacao.minutos, v_transacoes[indice].hora_transacao.segundos);
    }
    printf("\n\nFim da lista. Clique enter para continuar.");
    fflush(stdin);
    getchar();
}

void total_escola(t_transacao v_transacoes[], t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_transacoes, int num_escolas)
{
    int indice1, indice2, indice3;
    float total_faturado[num_escolas];
    for (indice1 = 0; indice1 < num_escolas; ++indice1)
    {
        for (indice2 = 0; indice2 < num_utilizadores; ++indice2)
        {
            if (v_escolas[indice1].id == v_utilizadores[indice2].id_escola)
            {
                for (indice3 = 0; indice3 < num_transacoes; ++indice3)
                {
                    if (v_transacoes[indice3].id_utilizador == v_utilizadores[indice2].id && !strncmp(v_transacoes[indice3].tipo_transacao, "Pagamento", 13))
                    {
                        total_faturado[indice1] += v_transacoes[indice3].valor_transacao;
                    }
                }
            }
        }
    }
    for (indice1 = 0; indice1 < num_escolas; ++indice1)
    {
        printf("A escola %s fez %.2f euros\t", v_escolas[indice1].nome_escola, total_faturado);
    }
    fflush(stdin);
    getchar();
}

void percentagem_transacoes(t_transacao v_transacoes[], t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_transacoes, int num_escolas)
{
    int indice1, indice2, indice3, contador_transacoes[num_escolas];
    float percentagem_transacoes_escola[num_escolas];
    for (indice1 = 0; indice1 < num_escolas; ++indice1)
    {
        for (indice2 = 0; indice2 < num_utilizadores; ++indice2)
        {
            if (v_escolas[indice1].id == v_utilizadores[indice2].id_escola)
            {
                for (indice3 = 0; indice3 < num_transacoes; ++indice3)
                {
                    if (v_transacoes[indice3].id_utilizador == v_utilizadores[indice2].id && !strncmp(v_transacoes[indice3].tipo_transacao, "Pagamento", 13))
                    {
                        contador_transacoes[indice1] += 1;
                    }
                }
            }
        }
    }
    for (indice1 = 0; indice1 < num_escolas; ++indice1)
    {
        percentagem_transacoes_escola[indice1] = (float)(contador_transacoes[indice1] * 100) / num_transacoes;
        printf("A escola %s tem %.2f%% da faturacao\n", v_escolas[indice1].nome_escola, percentagem_transacoes_escola[indice1]);
    }
    fflush(stdin);
    getchar();
}

void total_transacoes_filtrado(t_transacao v_transacoes[], t_utilizador v_utilizadores[], int num_utilizadores, int num_transacoes)
{
    int indice1, indice2, total_pagamentos_utilizado[3];
    data data1, data2;
    printf("Insira o intervalo de tempo que quer analisar\n");
    printf("Data 1:\n");
    data1 = procura_data(v_transacoes, num_transacoes);
    do
    {
        printf("Data 2:\n");
        data2 = procura_data(v_transacoes, num_transacoes);
        if (data1.ano > data2.ano && data1.mes > data2.mes && data1.dia > data2.dia)
        {
            printf("A segunda data nao pode ser mais pequena que a primeira\n");
            consultar_transacoes(v_transacoes, num_transacoes);
        }
    } while (data1.ano > data2.ano && data1.mes > data2.mes && data1.dia > data2.dia);
    total_por_utilizador(v_transacoes, v_utilizadores, num_utilizadores, num_transacoes, data1, data2, total_pagamentos_utilizado);
}

data procura_data(t_transacao v_transacoes[], int num_transacoes)
{
    int indice, valida_data = 0;
    data data;
    do
    {
        printf("Ano:");
        scanf("%d", &data.ano);
        printf("\nMes:");
        scanf("%d", &data.mes);
        printf("\nDia:");
        scanf("%d", &data.dia);

        for (indice = 0; indice < num_transacoes; indice++)
        {
            if (data.ano != v_transacoes[indice].data_transacao.ano && data.mes != v_transacoes[indice].data_transacao.mes && data.dia != v_transacoes[indice].data_transacao.dia)
            {
                valida_data = 1;
            }
        }
        if (valida_data)
        {
            printf("Nao existe nenhuma transacao com essa data\n");
            fflush(stdin);
            getchar();
            consultar_transacoes(v_transacoes, num_transacoes);
        }
    } while (valida_data);
    return data;
}

void total_por_utilizador(t_transacao v_transacoes[], t_utilizador v_utilizadores[], int num_utilizadores, int num_transacoes, data data1, data data2, int total_pagamentos_utilizado[])
{
    int indice1, indice2, indice3;
    char tipo_utilizadores[3][10] = {"Estudante", "Funcionario", "Docente"};
    for (indice1 = 0; indice1 < num_transacoes; ++indice1)
    {
        if ((data1.ano >= v_transacoes[indice1].data_transacao.ano && data1.mes >= v_transacoes[indice1].data_transacao.mes && data1.dia >= v_transacoes[indice1].data_transacao.dia) && (data2.ano <= v_transacoes[indice1].data_transacao.ano && data2.mes <= v_transacoes[indice1].data_transacao.mes && data2.dia <= v_transacoes[indice1].data_transacao.dia))
        {
            for (indice2 = 0; indice2 < num_utilizadores; ++indice2)
            {
                for (indice3 = 0; indice3 < 3; ++indice3)
                {
                    if (!strncmp(v_utilizadores[indice2].tipo_utilizador, tipo_utilizadores[indice3], 10) && !strncmp(v_transacoes[indice1].tipo_transacao, "Pagamento", 13))
                    {
                        total_pagamentos_utilizado[indice3] += 1;
                    }
                }
            }
        }
    }
}

int menu_estatisticas()
{
    int opcao;
    do
    {
        system("cls");
        printf("Menu de Opcoes\n");
        printf("\n1 - Total faturado por escola");
        printf("\n2 - Percentagem de pagamentos por escola");
        printf("\n3 - Total de pagamentos entre duas datas por tipo de utilizador");
        printf("\n0 - Sair");
        printf("\n\nOpcao: ");
        scanf("%d", &opcao);
        fflush(stdin);
        if (opcao < 0 || opcao > 3)
        {
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while (opcao < 0 || opcao > 3);
    return opcao;
}