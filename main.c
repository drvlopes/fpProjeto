#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAXIMO_NUMERO_ESCOLAS 5         // Define o numero maximo de escolas que podem ser registadas
#define MAXIMO_NUMERO_UTILIZADORES 200  // Define o numero maximo de utilizadores que podem ser registados
#define MAXIMO_NUMERO_TRANSACOES 5000   // Define o numero maximo de transacoes que podem ser registadas
#define NOME_FICHEIRO_ESCOLAS "escolas.dat"
#define NOME_FICHEIRO_UTILIZADORES "utilizadores.dat"
#define NOME_FICHEIRO_TRANSACOES "transacoes.dat"

typedef struct{                 // Cria uma STRUCT para armazenar as datas
    int dia;                    // define o campo do dia
    int mes;                    // define o campo do mês
    int ano;                    // define o campo do ano
} data;

typedef struct{                 // Cria uma STRUCT para armazenar as horas
    int horas;                  // define o campo das horas
    int minutos;                // define o campo dos minutos
    int segundos;               // define o campo dos segundos
} hora;

typedef struct{                 // Cria uma STRUCT para armazenar os dados das escolas
    int id;                     // define o campo identificador único
    char nome_escola[80];       // define o campo nome da escola
    char abreviatura[8];        // define o campo abreviatura
    int campus;                 // define o campo campus
    char localidade[20];        // define o campo localidade
} t_escola;

typedef struct{                 // Cria uma STRUCT para armazenar os dados de um utilizador
    int id;                     // define o campo identificador único
    int id_escola;              // define o campo identificador único da escola
    char nome[80];              // define o campo nome
    int nif;                    // define o campo nif
    char tipo_utilizador[11];   // define o campo tipo de utilizador
    char email[80];             // define o campo email
    float saldo;                // define o campo saldo
} t_utilizador;

typedef struct{                 // Cria uma STRUCT para armazenar os dados das transações
    int id;                     // define o campo identificador único
    int id_utilizador;          // define o campo indetificador único do utilizador
    char tipo_transacao[13];    // define o campo tipo de transação
    float valor_trasacao;       // define o campo valor da transação
    data data_transacao;        // define o campo data da transação
    hora hora_transacao;        // define o campo hora da transação
} t_transacao;

int menu(); // Apresenta o menu principal
int menu_utilizadores(); // Apresenta as opcoes referentes a consulta de utilizadores
int menu_transacoes(); // Apresenta as opcoes referentes as transacoes
int registar_utilizador(t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int nif_utilizador, int num_escolas); // Regista um novo utilizador
int registar_transacoes(t_transacao v_transacoes[], t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_transacoes);// Regista uma nova transacao
int registar_escola(t_escola v_escolas[], int num_escolas); // Regista uma nova escola
void consultar_utilizadores(t_utilizador v_utilizadores[],t_escola v_escolas[], int num_utilizadores); // Apresenta todos os utilizadores
void consultar_escolas(t_escola v_escolas[], int numero_escolas); // Apresenta todas as escolas
int mostrar_utilizador(t_utilizador v_utilizadores[],t_escola v_escolas[], int num_utilizadores, int num_escolas); // Permite a pesquisa de um utilizador por nif
int procurar_utilizador(t_utilizador v_utilizadores[],int num_utilizadores ,int nif_utilizador); // Verifica se um utilizador e devolve a sua posição no vetor
int escolhe_escola(t_escola v_escolas[], int numero_escolas); // Apresenta as escolas disponiveis para registar o utilizador
void escolhe_utilizador(t_utilizador v_utilizadores[], int num_utilizadores); // // Apresenta os tipos de utilizadores disponiveis para registar o utilizador
char confirmar_saida(); // Confirma se o utilizador realmente que fechar o programa
void inicias(char nome_completo[], t_escola v_escolas[], int num_escolas); // Retira as inicias do nome completo da escola
int ler_ficheiro_escolas(t_escola v_escolas[]); // Importa os dados das escolas do ficheiro binario
int ler_ficheiro_utilizadores(t_utilizador v_utilizadores[]); // Importa os dados dos utilizadores do ficheiro binario
int ler_ficheiro_transacoes(t_transacao v_transacoes[]); // Importa os dados das transacoes do ficheiro binario
void gravar_ficheiro(t_escola v_escolas[], int num_escolas); // Grava os dados das escolas no ficheiro binario
void gravar_ficheiro_utilizadores(t_utilizador v_utilizadores[], int num_utilizadores); // Grava os dados dos utilizadores no ficheiro binario
void gravar_ficheiro_transacoes(t_transacao v_transacoes[], int num_transacoes); // Grava os dados das transacoes no ficheiro binario

int main(){
    char saida;
    int escolas_registadas[4], opcao, numero_escolas = 0, numero_utilizadores = 0, numero_transacoes = 0;

    t_escola escolas[MAXIMO_NUMERO_ESCOLAS];
    t_utilizador utilizadores[MAXIMO_NUMERO_UTILIZADORES];
    t_transacao transacoes[MAXIMO_NUMERO_TRANSACOES];

    do{
        opcao = menu();
        switch(opcao){
            case 1:
                if(numero_escolas >= MAXIMO_NUMERO_ESCOLAS){
                    printf("\nNao e possivel adicionar mais escolas!\n\nClique enter para continuar.");
                    getchar();
                } else{
                    numero_escolas = registar_escola(escolas, numero_escolas);
                }
                break;
            case 2:
                if(numero_escolas > 0){
                    consultar_escolas(escolas, numero_escolas);
                }
                else{
                    printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                    getchar();
                }
                break;
            case 3:
                if(numero_escolas > 0){
                    if(numero_utilizadores >= MAXIMO_NUMERO_UTILIZADORES){
                        printf("\nNao e possivel adicionar mais utilizadores!\n\nClique enter para continuar.");
                        getchar();
                    } else{
                        numero_utilizadores = registar_utilizador(utilizadores, escolas, numero_utilizadores, 0, numero_escolas);
                    }
                }
                else{
                    printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                    getchar();
                }
                break;
            case 4:
                if(numero_escolas > 0){
                   if(numero_utilizadores > 0){
                        switch(menu_utilizadores()){
                            case 1:
                                consultar_utilizadores(utilizadores, escolas, numero_utilizadores);
                                    printf("\n\nFim da lista. Clique enter para continuar.");
                                    getchar();
                                break;
                            case 2:
                                numero_utilizadores = mostrar_utilizador(utilizadores, escolas, numero_utilizadores, numero_escolas);
                                break;
                            default:
                                break;
                        }
                    }
                    else{
                        printf("\nNao foram introduzidos alunos!\n\nClique enter para continuar.");
                        getchar();
                    }
                }
                else{
                    printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                    getchar();
                }
                break;
            case 5:
                if(numero_transacoes < MAXIMO_NUMERO_TRANSACOES){
                    if(numero_escolas > 0){
                        if(numero_utilizadores > 0){
                            switch(menu_transacoes()){
                            case 1:
                                numero_transacoes = registar_transacoes(transacoes, utilizadores, escolas, numero_utilizadores, numero_transacoes);
                                break;
                            case 2:
                                //consultar_transacoes(transacoes, utilizadores, numero_utilizadores);
                                break;
                            default:
                                break;
                        }
                        }
                        else{
                            printf("\nNao foram introduzidos alunos!\n\nClique enter para continuar.");
                            getchar();
                        }
                    }
                    else{
                        printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                        getchar();
                    }
                }
                else{
                        printf("\nNao e possivel adicionar mais transacoes!\n\nClique enter para continuar.");
                        getchar();
                    }
                break;
            case 7:
                if(numero_escolas > 0){
                    gravar_ficheiro_escolas(escolas, numero_escolas);
                    if(numero_utilizadores > 0){
                        gravar_ficheiro_utilizadores(utilizadores, numero_utilizadores);
                        if(numero_transacoes > 0)
                            gravar_ficheiro_transacoes(transacoes, numero_transacoes);
                        else{
                            printf("\nNao foram introduzidas transacoes!\n\nClique enter para continuar.");
                            getchar();
                        }
                    }
                    else{
                        printf("\nNao foram introduzidos utilizadores!\n\nClique enter para continuar.");
                        getchar();
                    }
                }
                else{
                    printf("\nNao foram introduzidas escolas!\n\nClique enter para continuar.");
                    getchar();
                }
                break;
            case 8:
                if(numero_transacoes == 0){
                    numero_transacoes = ler_ficheiro_transacoes(transacoes);
                    if(numero_utilizadores == 0){
                        numero_utilizadores = ler_ficheiro_utilizadores(utilizadores);
                        if(numero_escolas == 0)
                            numero_escolas = ler_ficheiro_escolas(escolas);
                        else{
                            printf("\nJa estao escolas registadas!\n\nClique enter para continuar.");
                            getchar();
                        }
                    }
                    else{
                            printf("\nJa estao utilizadores registados!\n\nClique enter para continuar.");
                            getchar();
                    }
                }
                else{
                    printf("\nJa estao transacoes registadas!\n\nClique enter para continuar.");
                    getchar();
                }
                break;
            case 0:
                saida = confirmar_saida();
            default:
                break;
        }
    }while(saida != 'S');
        if(numero_escolas != 0)
            gravar_ficheiro_escolas(escolas, numero_escolas);
        if(numero_utilizadores != 0)
            gravar_ficheiro_utilizadores(utilizadores, numero_utilizadores);
        if(numero_transacoes != 0)
            gravar_ficheiro_transacoes(transacoes, numero_transacoes);
    return 0;
}

void consultar_escolas(t_escola v_escolas[], int num_escolas){
    int indice;

    printf("\nDados das escolas\n");
    printf("Numero\tNome\t\t\t\t\t\t\tAbreviatura\tCampus\t\tLocalidade\n");

    for (indice = 0; indice < num_escolas; indice++){
        printf("%d\t%s\t\t\t%s\t\t%d\t%s\n", v_escolas[indice].id, v_escolas[indice].nome_escola, v_escolas[indice].abreviatura, v_escolas[indice].campus, v_escolas[indice].localidade);
    }
}

int registar_escola(t_escola v_escolas[], int num_escolas){
    int opcao;
    v_escolas[num_escolas].id = num_escolas + 1;
    printf("\nRegistar nova escola\n\nNome: ");
    scanf(" %80[^\n]s",&v_escolas[num_escolas].nome_escola);
    inicias(v_escolas[num_escolas].nome_escola, v_escolas, num_escolas);   
    do{
        printf("\nCampus (1 a 4): ");
        printf("\n\nOpcao: ");
        scanf(" %d",&opcao);
        if(opcao < 1 || opcao > 4){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            getchar();
        }
    } while(opcao < 1 || opcao > 4);
    v_escolas[num_escolas].campus = opcao;
    printf("\nLocalidade: ");
    scanf(" %20[^\n]s",&v_escolas[num_escolas].localidade);

    return num_escolas + 1;
}

void inicias(char nome_completo[], t_escola v_escolas[], int num_escolas){
    int tamanho, indice, pos_sigla = 1;
    char abreviatura[8] = {'\o'};
    tamanho = strlen(nome_completo);
    for(indice = 0; indice < tamanho; indice++){
        if (indice == 0)
            abreviatura[0] = toupper(nome_completo[indice]);
        else if ((nome_completo[indice - 1] == ' ' && nome_completo[indice] != ' ') && (nome_completo[indice] != 'd' && (nome_completo[indice + 1] != 'e' || nome_completo[indice + 2] != ' ')))
            if(nome_completo[indice] != 'e' && nome_completo[indice + 1] != ' '){
                abreviatura[pos_sigla] = toupper(nome_completo[indice]);
                pos_sigla++;
            }
    }
    strcpy(v_escolas[num_escolas].abreviatura, abreviatura);
}

int menu_transacoes(){
    int opcao;
    do{
        printf("\nRegistar/consultar os dados das transacoes:\n");
        printf("\n1 - Criar nova transancao");
        printf("\n2 - Consultar todas as transancoes");
        printf("\n0 - Voltar para o menu principal");
        printf("\n\nOpcao: ");
        scanf(" %d",&opcao);
        if(opcao < 0 || opcao > 2){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            getchar();
        }
    } while(opcao < 0 || opcao > 2);
}

int menu_utilizadores(){
    int opcao;

	do{
		printf("Consultar dados dos utilizadores\n");
		printf("\n1 - Consultar todos os utilizadores");
		printf("\n2 - Pesquisar utilizador por nif");
		printf("\n0 - Voltar para o menu principal");
		printf("\n\nOpcao: ");
		scanf(" %d",&opcao);
		if(opcao < 0 || opcao > 2){
			printf("\nOpcao invalida!\n\nClique enter para continuar.");
			getchar();
		}
	} while(opcao < 0 || opcao > 2);

    return opcao;
}

int menu(){
    int opcao;

    do{
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

        scanf(" %d%*c",&opcao);
        if(opcao < 0 || opcao > 8){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            getchar();
        }
    } while(opcao < 0 || opcao > 8);

    return opcao;
}

char confirmar_saida(){
    char escolha;
    printf("\nConfirma saida (S/N): ");
    do{
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        if(escolha != 'S' && escolha != 'N'){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            getchar();
        }
    } while(escolha != 'S' && escolha != 'N');
    return escolha;
}

int registar_utilizador(t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int nif_utilizador, int num_escolas){
    int utilizador_existe = -1;

    if(nif_utilizador == 0){
        do{
            printf("\nIntroduzir nif do utilizador: ");
            scanf(" %d",&nif_utilizador);

            utilizador_existe = procurar_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);

            if(utilizador_existe == -1){
                v_utilizadores[num_utilizadores].nif = nif_utilizador;
            }
            else{
                printf("\nO utilizador com o nif %d ja existe!\n\nClique enter para continuar.", nif_utilizador); 
                getchar();
            }
        } while(utilizador_existe != -1);
    }
    else{
        v_utilizadores[num_utilizadores].nif = nif_utilizador;
    }

    v_utilizadores[num_utilizadores].id = num_utilizadores + 1; //adiciona 1 ao ultimo id
    v_utilizadores[num_utilizadores].id_escola = escolhe_escola(v_escolas, num_escolas);

    escolhe_utilizador(v_utilizadores, num_utilizadores);

    v_utilizadores[num_utilizadores].saldo = 0;

    printf("\nNome: ");
    scanf(" %80[^\n]s", v_utilizadores[num_utilizadores].nome);
    printf("Email: ");
    scanf(" %80[^\n]s", v_utilizadores[num_utilizadores].email);

    return num_utilizadores + 1;
}

void escolhe_utilizador(t_utilizador v_utilizadores[], int num_utilizadores){
    int opcao;
    char utilizador[11];

    do{
        printf("\nTipo de utilizador:\n\n1- Estudante\n2- Docente\n3- Funcionario\n\nOpcao: ");
        scanf(" %d",&opcao);
       if(opcao < 0 || opcao > 3){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            getchar();
        }
    } while(opcao < 0 || opcao > 3);

    switch (opcao){
        case 1:
            strcpy(utilizador, "estudante");
            break;
        case 2:
            strcpy(utilizador, "docente");
            break;
        case 3:
            strcpy(utilizador, "funcionario");
            break;
        default:
            break;
    }
    strcpy(v_utilizadores[num_utilizadores].tipo_utilizador, utilizador);
}

int escolhe_escola(t_escola v_escolas[], int num_escolas){
    int opcao, indice;
    do
    {
        printf("\nEscolha a escola\n");
        for (indice = 0; indice < num_escolas; indice++)
        {
            printf("\n%d- %s", indice + 1, v_escolas[indice].abreviatura);
        }
        printf("\n\nOpcao: ");

        scanf(" %d",&opcao);
       if(opcao < 0 || opcao > num_escolas){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
            getchar();
        }
    } while(opcao < 0 || opcao > num_escolas);
    
    

    return opcao;
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
}

int mostrar_utilizador(t_utilizador v_utilizadores[],t_escola v_escolas[], int num_utilizadores, int num_escolas){
    int encontrou_utilizador, nif_utilizador;
    char opcao;
    do{
        printf("\nPesquisar utilizador por nif\n\nIntroduzir nif do utilizador: ");
        scanf(" %d",&nif_utilizador);
        encontrou_utilizador = procurar_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);
        if(encontrou_utilizador == -1){
            printf("\nO utilizador com o nif %d nao existe!\nDeseja criar um utilizador com esse nif? (S/N) ", nif_utilizador);
            do {
                scanf(" %c", &opcao);
                opcao = toupper(opcao);
                if(opcao != 'S' && opcao != 'N') {
                    printf("\nEscolha invalida!");
                }
                else if( opcao == 'S') {
                    num_utilizadores = registar_utilizador(v_utilizadores, v_escolas, num_utilizadores, nif_utilizador, num_escolas);
                    encontrou_utilizador = -2;
                }
            } while(opcao != 'S' && opcao != 'N');
        }
        else{
            printf("Numero\tNome\t\t\t\tEscola\tNIF\t\tTipo\t\tE-mail\t\t\tSaldo\n%d\t%s\t\t\t%s\t%d\t%s\t%s\t%.2f\n", v_utilizadores[encontrou_utilizador].id, v_utilizadores[encontrou_utilizador].nome,v_escolas[v_utilizadores[encontrou_utilizador].id_escola - 1].abreviatura,v_utilizadores[encontrou_utilizador].nif,v_utilizadores[encontrou_utilizador].tipo_utilizador,v_utilizadores[encontrou_utilizador].email,v_utilizadores[encontrou_utilizador].saldo);
            getchar();
        }
    }while (encontrou_utilizador == -1);
    return num_utilizadores;
}

int registar_transacoes(t_transacao v_transacoes[], t_utilizador v_utilizadores[], t_escola v_escolas[], int num_utilizadores, int num_transacoes){
    int posicao_utilizador, tipo_transacao, transacao, nif_utilizador;

    v_transacoes[num_utilizadores].id = num_transacoes+1;
     do {
        consultar_utilizadores(v_utilizadores, v_escolas, num_utilizadores);
        printf("\nInsira o NIF do utilizador que realizou a operacao");
        scanf(" %d", &nif_utilizador);
         posicao_utilizador = procurar_utilizador(v_utilizadores, num_utilizadores, nif_utilizador);
        if(posicao_utilizador < 0){
            printf("\nO NIF que inseriu nao e valido");
        } else{
            v_transacoes[num_transacoes].id_utilizador = v_utilizadores[posicao_utilizador].id;
        }
    }while(posicao_utilizador < 0);

    do {
        printf("\nEscolha o tipo de transacao:\n1 - Pagamento\n2 - Carragamento");
        scanf(" %d", &tipo_transacao);
        if(tipo_transacao < 1 || tipo_transacao > 2){
            printf("\nOpcao invalida!\n\nClique enter para continuar.");
        }
    } while (tipo_transacao<1 || tipo_transacao>2);
    if(tipo_transacao == 1){
        strcpy(v_transacoes[num_transacoes].tipo_transacao, "Pagamento");

    }else{
        strcpy(v_transacoes[num_transacoes].tipo_transacao, "Carragamento");
    }

    do {
        printf("Insira o valor do %s\n", v_transacoes[num_transacoes].tipo_transacao);
        scanf(" %d", &transacao);
        if (!strncmp(v_transacoes[num_transacoes].tipo_transacao, "Pagamento", 13)) {
            if ((v_utilizadores[posicao_utilizador].saldo - transacao) <= 0) {
                v_utilizadores[posicao_utilizador].saldo -= transacao;
            } else {
                printf("Nao tem saldo suficiente\n");
            }
        } else {
            v_utilizadores[posicao_utilizador].saldo += transacao;
        }
    } while (!strncmp(v_transacoes[num_transacoes].tipo_transacao, "Pagamento", 13) && (v_utilizadores[posicao_utilizador].saldo - transacao) <= 0);
}

int ler_ficheiro_escolas(t_escola v_escolas[]){
    int num_escolas = 0, num_escolas_lidas;
    FILE *ficheiro;

    ficheiro = fopen(NOME_FICHEIRO_ESCOLAS, "rb");

    if(ficheiro == NULL){
        printf("\nNao foi possivel abrir o ficheiro %s\n", NOME_FICHEIRO_ESCOLAS);
    }
    else{
        fread(&num_escolas, sizeof(int),1,ficheiro);
        num_escolas_lidas = fread(v_escolas,sizeof(t_escola),num_escolas,ficheiro);
        fclose(ficheiro);

        if(num_escolas != num_escolas_lidas){
            printf("\nErro na leitura do ficheiro %s", NOME_FICHEIRO_ESCOLAS);
            num_escolas = 0;
        }
        else{
            printf("\nLeitura dos dados de %d escolas a partir do ficheiro %s.\n", num_escolas, NOME_FICHEIRO_ESCOLAS);
        }
    }
    num_escolas = num_escolas_lidas;
    return num_escolas;
}

int ler_ficheiro_utilizadores(t_utilizador v_utilizadores[]){
    int num_utilizadores = 0, num_utilizadores_lidos;
    FILE *ficheiro;

    ficheiro = fopen(NOME_FICHEIRO_UTILIZADORES, "rb");

    if(ficheiro == NULL){
        printf("\nNao foi possivel abrir o ficheiro %s\n", NOME_FICHEIRO_UTILIZADORES);
    }
    else{
        fread(&num_utilizadores, sizeof(int),1,ficheiro);
        num_utilizadores_lidos = fread(v_utilizadores,sizeof(t_utilizador),num_utilizadores,ficheiro);
        fclose(ficheiro);

        if(num_utilizadores != num_utilizadores_lidos){
            printf("\nErro na leitura do ficheiro %s", NOME_FICHEIRO_UTILIZADORES);
            num_utilizadores = 0;
        }
        else{
            printf("\nLeitura dos dados de %d utilizadores a partir do ficheiro %s.\n", num_utilizadores, NOME_FICHEIRO_UTILIZADORES);
        }
    }
    num_utilizadores = num_utilizadores_lidos;
    return num_utilizadores;
}

int ler_ficheiro_transacoes(t_transacao v_transacoes[]){
    int num_transacoes = 0, num_transacoes_lidas;
    FILE *ficheiro;

    ficheiro = fopen(NOME_FICHEIRO_TRANSACOES, "rb");

    if(ficheiro == NULL){
        printf("\nNao foi possivel abrir o ficheiro %s\n", NOME_FICHEIRO_TRANSACOES);
    }
    else{
        fread(&num_transacoes, sizeof(int),1,ficheiro);
        num_transacoes_lidas = fread(v_transacoes,sizeof(t_transacao),num_transacoes,ficheiro);
        fclose(ficheiro);

        if(num_transacoes != num_transacoes_lidas){
            printf("\nErro na leitura do ficheiro %s", NOME_FICHEIRO_TRANSACOES);
            num_transacoes = 0;
        }
        else{
            printf("\nLeitura dos dados de %d transacoes a partir do ficheiro %s.\n", num_transacoes, NOME_FICHEIRO_TRANSACOES);
        }
    }
    num_transacoes = num_transacoes_lidas;
    return num_transacoes;
}

void gravar_ficheiro_escolas(t_escola v_escolas[], int num_escolas){
    FILE *ficheiro;

    ficheiro = fopen(NOME_FICHEIRO_ESCOLAS, "wb");

    if(ficheiro == NULL){
        printf("\nNao foi possivel criar o ficheiro!");
        fflush(stdin);
        getchar();
    }
    else{
        fwrite(&num_escolas,sizeof (int),1,ficheiro);
        fwrite(v_escolas,sizeof(t_escola),num_escolas,ficheiro);
        fclose(ficheiro);
        printf("\nEscrita dos dados de %d escolas no ficheiro %s com sucesso!", num_escolas, NOME_FICHEIRO_ESCOLAS);
    }
}

void gravar_ficheiro_utilizadores(t_utilizador v_utilizadores[], int num_utilizadores){
    FILE *ficheiro;

    ficheiro = fopen(NOME_FICHEIRO_UTILIZADORES, "wb");

    if(ficheiro == NULL){
        printf("\nNao foi possivel criar o ficheiro!");
        fflush(stdin);
        getchar();
    }
    else{
        fwrite(&num_utilizadores,sizeof (int),1,ficheiro);
        fwrite(v_utilizadores,sizeof(t_utilizador),num_utilizadores,ficheiro);
        fclose(ficheiro);
        printf("\nEscrita dos dados de %d utilizadores no ficheiro %s com sucesso!", num_utilizadores, NOME_FICHEIRO_UTILIZADORES);
    }
}

void gravar_ficheiro_transacoes(t_transacao v_transacoes[], int num_transacoes){
    FILE *ficheiro;

    ficheiro = fopen(NOME_FICHEIRO_TRANSACOES, "wb");

    if(ficheiro == NULL){
        printf("\nNao foi possivel criar o ficheiro!");
        fflush(stdin);
        getchar();
    }
    else{
        fwrite(&num_transacoes,sizeof (int),1,ficheiro);
        fwrite(v_transacoes,sizeof(t_transacao),num_transacoes,ficheiro);
        fclose(ficheiro);
        printf("\nEscrita dos dados de %d transacoes no ficheiro %s com sucesso!", num_transacoes, NOME_FICHEIRO_TRANSACOES);
    }
}