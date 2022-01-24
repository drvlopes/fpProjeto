#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXIMO_NUMERO_ESCOLAS 5
#define MAXIMO_NUMERO_UTILIZADORES 200
#define MAXIMO_NUMERO_TRANSACOES 5000

typedef struct                  // Cria uma STRUCT para armazenar as datas
{
    int dia;                    // define o campo do dia
    int mes;                    // define o campo do mês
    int ano;                    // define o campo do ano
} data;

typedef struct                  // Cria uma STRUCT para armazenar as horas
{
    int horas;                  // define o campo das horas
    int minutos;                // define o campo dos minutos
    int segundos;               // define o campo dos segundos
} hora;

typedef struct                  // Cria uma STRUCT para armazenar os dados das escolas
{
    int id;                     // define o campo identificador único
    char nome_escola[80];       // define o campo nome da escola
    char abreviatura[8];        // define o campo abreviatura
    char campus[10];            // define o campo campus
    char localidade[20];        // define o campo localidade
} t_escola;

typedef struct                  // Cria uma STRUCT para armazenar os dados de um utilizador
{
    int id;                     // define o campo identificador único
    int id_escola;              // define o campo identificador único da escola
    char nome[80];              // define o campo nome
    int nif;                    // define o campo nif
    char tipo_utilizador[10];   // define o campo tipo de utilizador
    char email[80];             // define o campo email
    float saldo;                // define o campo saldo
} t_utilizador;

typedef struct                  // Cria uma STRUCT para armazenar os dados das transações
{
    int id;                     // define o campo identificador único
    int id_utilizador;          // define o campo indetificador único do utilizador
    char tipo_trasacao[13];     // define o campo tipo de transação
    float valor_trasacao;       // define o campo valor da transação
    data data_transacao;        // define o campo data da transação
    hora hora_transacao;        // define o campo hora da transação
} t_transacao;

int menu();
void menu_utilizador(int num_utilizadores);
void menu_transacoes(int num_transacoes);
void menu_estatisticas();
int registo_utilizador(t_utilizador v_utilizadores[], int num_utilizadores);
int procurar_utilizador(t_utilizador v_utilizadores[],int num_utilizadores ,int nif_utilizador);
void consultar_utilizador();
void registar_trasacoes();
void consultar_trasacoes();
void ler_escola();
void escrever_escola();
void ler_utilizadores();
void escrever_utilizadores();
void ler_transacoes();
void escrever_transacoes();
void total_escola();
void percentagem_transacoes();
void total_transacoes_filtrado();
char confirmar_saida();


int main()
{
    char saida;
    int opcao, numero_escolas = 0, numero_utilizadores = 0, numero_trasacoes = 0;

    t_escola escolas[MAXIMO_NUMERO_ESCOLAS];
    t_utilizador utilizadores[MAXIMO_NUMERO_UTILIZADORES];
    t_transacao transacoes[MAXIMO_NUMERO_TRANSACOES];

    do
    {
        system("cls");
        opcao = menu();
        switch(opcao)
        {
            case 1:
                if(numero_utilizadores >= MAXIMO_NUMERO_UTILIZADORES) {
                    printf("\nNão é possivel adicionar mais utilizadores!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                } else{
                    numero_utilizadores = registo_utilizador(utilizadores, numero_utilizadores);
                }
                break;
            case 2:
                menu_utilizador(numero_utilizadores);
                break;
            case 3:
                menu_transacoes(numero_trasacoes);
                break;
            case 4:
                break;
            case 0:
                saida = confirmar_saida();
            default:
                break;
        }
    }while(saida != 'S');

    return 0;
}

int menu()
{
    int opcao;

    do {
        system("cls");
        printf("Menu de Opcoes\n");
        printf("\n1 - Registar nova escola");
        printf("\n1 - Consultar dados das escolas");
        printf("\n3 - Registar novo utilizador");
        printf("\n4 - Consultar dados dos utilizadores");
        printf("\n5 - Registar/consultar os dados das transacoes");
        printf("\n6 - Estatisticas");
        printf("\n7 - Gravar dados em ficheiro");
        printf("\n8 - Ler dados de ficheiro");
        printf("\n0 - Sair");
        printf("\n\nOpcao: ");

        scanf("%d",&opcao);
        fflush(stdin);
        if(opcao < 0 || opcao > 6){
            printf("\nOpcao invalida!");
        }
    } while(opcao < 0 || opcao > 6);

    return opcao;
}

char confirmar_saida()
{
    char escolha;

    printf("\nConfirma saida (S/N): ");

    do {
        scanf(" %c", &escolha);
        fflush(stdin);
        escolha = toupper(escolha);
        if(escolha != 'S' && escolha != 'N'){
            printf("\nEscolha invalida!");
        }

    } while(escolha != 'S' && escolha != 'N');

    return escolha;
}

int registo_utilizador(t_utilizador v_utilizadores[], int num_utilizadores)
{
    int utilizador_existe, nif_utilizador;

    do{
        utilizador_existe = 0;

        printf("\nIntroduzir nif do utilizador: ");
        scanf("%d",&nif_utilizador);
        utilizador_existe = procurar_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);

        if(utilizador_existe != 0){
            v_utilizadores[utilizador_existe].nif = nif_utilizador;
        }
        else{
            printf("\nO utilizador com o nif %d já existe!\n", nif_utilizador);
            fflush(stdin);
            getchar();
        }
    } while(utilizador_existe != 0);

    printf("Nome: ");
    fflush(stdin);
    scanf("%80[^\n]s", v_utilizadores[utilizador_existe].nome);

    return num_utilizadores + 1;
}

int procurar_utilizador(t_utilizador v_utilizadores[],int num_utilizadores ,int nif_utilizador)
{
    int encontrou_utilizador = 0, indice;

    for (indice = 0; indice < num_utilizadores; indice++) {
        if(v_utilizadores[indice].nif == nif_utilizador){
            encontrou_utilizador = indice;
        }
    }

    return encontrou_utilizador;
}