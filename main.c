#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
void menu_estatisticas();
int registo_utilizador(t_utilizador v_utilizadores[], int num_utilizadores, int nif_utilizador);
int procurar_utilizador(t_utilizador v_utilizadores[],int num_utilizadores ,int nif_utilizador);
void consultar_utilizadores(t_utilizador v_utilizadores[],t_escola v_escolas[], int num_utilizadores);
int mostrar_utilizador(t_utilizador v_utilizadores[],t_escola v_escolas[], int num_utilizadores);
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


int main(){
    char saida;
    int opcao, numero_escolas = 0, numero_utilizadores = 0, numero_trasacoes = 0;

    t_escola escolas[MAXIMO_NUMERO_ESCOLAS];
    t_utilizador utilizadores[MAXIMO_NUMERO_UTILIZADORES];
    t_transacao transacoes[MAXIMO_NUMERO_TRANSACOES];

    do{
        system("cls");
        opcao = menu();
        switch(opcao){
            case 1:
                strcpy(escolas[0].abreviatura,"ESTG");
                strcpy(escolas[0].campus,"Campus 2");
                escolas[0].id = 1;
                strcpy(escolas[0].localidade,"Leiria");
                strcpy(escolas[0].nome_escola,"Escola Superior de Tecnologia e Gestao");

                strcpy(escolas[1].abreviatura,"ESAD");
                strcpy(escolas[1].campus,"Campus 3");
                escolas[1].id = 2;
                strcpy(escolas[1].localidade,"Caldas da Rainha");
                strcpy(escolas[1].nome_escola,"Escola Superior de Artes e Design");
                printf("teste123");
                numero_escolas = 2;

                utilizadores[0].id = 1;
                utilizadores[0].id_escola = 1;
                strcpy(utilizadores[0].nome, "Diogo Lopes");
                utilizadores[0].nif = 255081103;
                strcpy(utilizadores[0].tipo_utilizador, "Estudante");
                strcpy(utilizadores[0].email, "tbpt30@hotmail.com");
                utilizadores[0].saldo = 10.0;

                numero_utilizadores = 1;

                break;
            case 2:

                break;
            case 3:
                if(numero_utilizadores >= MAXIMO_NUMERO_UTILIZADORES){
                    printf("\nNao e possivel adicionar mais utilizadores!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                } else{
                    numero_utilizadores = registo_utilizador(utilizadores, numero_utilizadores, 0);
                }
                break;
            case 4:
                if(numero_utilizadores > 0){
                    do{
                        system("cls");
                        printf("Consultar dados dos utilizadores\n");
                        printf("\n1 - Consultar todos os utilizadores");
                        printf("\n2 - Pesquisar utilizador por nif");
                        printf("\n0 - Voltar para o menu principal");
                        printf("\n\nOpcao: ");
                        fflush(stdin);
                        scanf(" %d",&opcao);
                        if(opcao < 0 || opcao > 2){
                            printf("\nOpcao invalida!\n\nClique enter para continuar.");
                            fflush(stdin);
                            getchar();
                        }
                    } while(opcao < 0 || opcao > 2);
                    switch (opcao){
                        case 1:
                            consultar_utilizadores(utilizadores, escolas, numero_utilizadores);
                            break;
                        case 2:
                            numero_utilizadores = mostrar_utilizador(utilizadores, escolas, numero_utilizadores);
                            break;
                        default:
                            break;
                    }
                }
                else{
                    printf("\nNao foram introduzidos alunos!\n\nClique enter para continuar.");
                    fflush(stdin);
                    getchar();
                }
                break;
            case 0:
                saida = confirmar_saida();
            default:
                break;
        }
    }while(saida != 'S');
    return 0;
}

int menu(){
    int opcao;

    do{
        system("cls");
        printf("Menu de Opcoes\n");
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

        scanf("%d",&opcao);
        fflush(stdin);
        if(opcao < 0 || opcao > 6){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }
    } while(opcao < 0 || opcao > 6);

    return opcao;
}

char confirmar_saida(){
    char escolha;

    printf("\nConfirma saida (S/N): ");

    do{
        scanf(" %c", &escolha);
        fflush(stdin);
        escolha = toupper(escolha);

        if(escolha != 'S' && escolha != 'N'){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            fflush(stdin);
            getchar();
        }

    } while(escolha != 'S' && escolha != 'N');

    return escolha;
}

int registo_utilizador(t_utilizador v_utilizadores[], int num_utilizadores, int nif_utilizador){
    int utilizador_existe = -1;

    if(nif_utilizador == 0){
        do{

            printf("\nIntroduzir nif do utilizador: ");
            scanf("%d",&nif_utilizador);
            utilizador_existe = procurar_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);

            if(utilizador_existe == -1){
                v_utilizadores[num_utilizadores].nif = nif_utilizador;
            }
            else{
                printf("\nO utilizador com o nif %d ja existe!\n\nClique enter para continuar.", nif_utilizador);
                fflush(stdin);
                getchar();
            }
        } while(utilizador_existe != -1);

    }
    else{
        v_utilizadores[num_utilizadores].nif = nif_utilizador;
    }

    v_utilizadores[num_utilizadores].id = num_utilizadores + 1;
    v_utilizadores[num_utilizadores].id_escola = 1;
    strcpy(v_utilizadores[num_utilizadores].tipo_utilizador, "Estudante");
    v_utilizadores[num_utilizadores].saldo = 0;

    printf("Nome: ");
    fflush(stdin);
    scanf("%80[^\n]s", v_utilizadores[num_utilizadores].nome);

    printf("Email: ");
    fflush(stdin);
    scanf("%80[^\n]s", v_utilizadores[num_utilizadores].email);

    return num_utilizadores + 1;
}

int procurar_utilizador(t_utilizador v_utilizadores[],int num_utilizadores ,int nif_utilizador){
    int encontrou_utilizador = -1, indice;

    for (indice = 0; indice < num_utilizadores; indice++){
        if(v_utilizadores[indice].nif == nif_utilizador){
            encontrou_utilizador = indice;
        }
    }

    return encontrou_utilizador;
}

void consultar_utilizadores(t_utilizador v_utilizadores[],t_escola v_escolas[], int num_utilizadores){
    int indice;

    printf("\nDados dos utilizadores\n");
    printf("Numero\tNome\t\t\t\tEscola\tNIF\t\tTipo\t\tE-mail\t\t\tSaldo\n");

    for (indice = 0; indice < num_utilizadores; indice++){
        printf("%d\t%s\t\t\t%s\t%d\t%s\t%s\t%.2f\n", v_utilizadores[indice].id, v_utilizadores[indice].nome,v_escolas[v_utilizadores[indice].id_escola - 1].abreviatura,v_utilizadores[indice].nif,v_utilizadores[indice].tipo_utilizador,v_utilizadores[indice].email,v_utilizadores[indice].saldo);
    }
    printf("\n\nFim da lista. Clique enter para continuar.");
    fflush(stdin);
    getchar();
}

int mostrar_utilizador(t_utilizador v_utilizadores[],t_escola v_escolas[], int num_utilizadores){
    int encontrou_utilizador, nif_utilizador;
    char opcao;
    do{
        system("cls");
        printf("Pesquisar utilizador por nif\n\nIntroduzir nif do utilizador: ");
        scanf("%d",&nif_utilizador);
        encontrou_utilizador = procurar_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);
        if(encontrou_utilizador == -1){
            printf("\nO utilizador com o nif %d nao existe!\nDeseja criar um utilizador com esse nif? (S/N) ", nif_utilizador);
            do {
                fflush(stdin);
                scanf(" %c", &opcao);
                opcao = toupper(opcao);
                if(opcao != 'S' && opcao != 'N') {
                    printf("\nEscolha invalida!");
                }
                else if( opcao == 'S') {
                    num_utilizadores = registo_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);
                    encontrou_utilizador = -2;
                }
            } while(opcao != 'S' && opcao != 'N');
        }
        else{
            printf("Numero\tNome\t\t\t\tEscola\tNIF\t\tTipo\t\tE-mail\t\t\tSaldo\n%d\t%s\t\t\t%s\t%d\t%s\t%s\t%.2f\n", v_utilizadores[encontrou_utilizador].id, v_utilizadores[encontrou_utilizador].nome,v_escolas[v_utilizadores[encontrou_utilizador].id_escola - 1].abreviatura,v_utilizadores[encontrou_utilizador].nif,v_utilizadores[encontrou_utilizador].tipo_utilizador,v_utilizadores[encontrou_utilizador].email,v_utilizadores[encontrou_utilizador].saldo);
            fflush(stdin);
            getchar();
        }
    }while (encontrou_utilizador == -1);

    return num_utilizadores;
}