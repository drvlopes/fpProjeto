#include <stdio.h>

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
} escola;

typedef struct                  // Cria uma STRUCT para armazenar os dados de um utilizador
{
    int id;                     // define o campo identificador único
    int id_escola;              // define o campo identificador único da escola
    char nome[80];              // define o campo nome
    int nif;                    // define o campo nif
    char tipo_utilizador[10];   // define o campo tipo de utilizador
    char email[80];             // define o campo email
    float saldo;                // define o campo saldo
} utilizador;

typedef struct                  // Cria uma STRUCT para armazenar os dados das transações
{
    int id;                     // define o campo identificador único
    int id_utilizador;          // define o campo indetificador único do utilizador
    char tipo_trasacao[13];     // define o campo tipo de transação
    float valor_trasacao;       // define o campo valor da transação
    data data_transacao;        // define o campo data da transação
    hora hora_transacao;        // define o campo hora da transação
} transacao;

void menu();
void menu_utilizador();
void menu_transacoes();
void menu_estatisticas();
void registo_utilizador();
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


int main() {
    printf("Hello world!\n");
    return 0;
}
