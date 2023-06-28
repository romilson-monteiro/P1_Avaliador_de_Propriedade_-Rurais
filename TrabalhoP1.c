

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>  
#include <time.h>   //para consiguir usar uma funcao que nos da a data exata em que estamos



//------->>variaveis globais
#define FALSE 1
#define TRUE 3
#define qtd_util 20
char TIPO_Ad[] = "administrador";
char TIPO_Av[] = "avaliador";
char POR_AVAL[]= "Por Avaliar!";
char EM_Aval[]= "Em avaliao!";
char Aval[]= "Avaliado!";
 int DIA;
  int MES;
  int ANO;




//----------------------------Todas as estruturas definidas ----------------------------------------/
//Estrutura de dados dos utilizadores
typedef struct utilizadores{
   char username[20], nome[20], pasword[20];
   char tipo[20]; 

}UTILIZADORES;

//Estrutura de dados para culturas
typedef struct culturas{
    char cultura[20];
}CULTURAS;

//estrutura para estado de avaliações
 typedef struct Estado{
    char avaliacao[15];
 }ESTADO;

 //Estado Avaliado
 typedef struct Avaliado{
   float valor;
   int dia;
   int mes;
   int ano;
   char avaliador[20];
 }AVALIADO;
  


//Estrutura para dados das propriedades
typedef struct proriadades{  
    ESTADO estado;
    CULTURAS cult[20];
    AVALIADO Avaliacao;                                                                                                                                                                                                                   
    int numero;
    char nomeProprietario[20], discricao[50];
    float area;
}PROPRIADADES;


//strutura para listas simples
typedef struct NO {
    PROPRIADADES data;
    struct NO *next;
}LISTA;
LISTA *head = NULL;

//Estructura para Fila
typedef struct queue{
    LISTA *front;
    LISTA *rear;
}FILA;
FILA *fila;



//-----------------------Prototipos de todas as funcoes----------------------------/

//Prototipo de Funcao principl
void Administrador();
void Avaliador();
//prototipos das funçóes
UTILIZADORES ler_daos_util(UTILIZADORES utilizador);
UTILIZADORES autenticador();
PROPRIADADES ler_daos_propr(PROPRIADADES prop);
LISTA *Insirir_propriedades(LISTA *head);
LISTA *Listar_proriadades(LISTA *head);
LISTA *apagar_Popriedade(LISTA *head);
LISTA *Alterar_Dado(LISTA *head, int num);
LISTA *Insirir_propriedade_Fila(LISTA *head, int num);
LISTA *Avaliar(LISTA *head, UTILIZADORES util);
LISTA *Restaurar_Lista(LISTA *head);
//FILA *Restaurar_FILA(FILA *fila);
void Restaurar_FILA();
void Salvar_fila(FILA *fila);
void Salvar_Lista(LISTA *head);
void Pesquisar(LISTA *head, int num);
void Pesquisar_Propri_Por_Nome(LISTA *head, char nome[20]);
void inserir_Utilizador();
void enqueue(PROPRIADADES prop);
void creat_queue();
void Dequeue();
void Listar_Fila();
void Listar_Propri_Por_Aval(LISTA *head);
void Listar_Propri_Aval(LISTA *head);
void Listar_Propri_Aval_Acima_N_VALOR(LISTA *head, float val);
void Listar_Propri_Aval_Por_Utili(LISTA *head, char avaliador[20]);
void Listar_Propri_Aval_Acima_N_VALOR(LISTA *head, float val);
void Relatorio_Propri_Aval(LISTA *head);

void erro();
int menuAdim();
int menuAval();
int menuPrincipal();

//prototipos defuncoes de roda pe e cabecalho
void rodaPe(FILE *out);
void divi(FILE *out);
void cabecalho(FILE *out, int id, char estado[20]);







//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//                                            MAIN
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int main(){
    setlocale(LC_ALL, "Portuguese");
	system("COLOR FC");  
    int op;
    
    creat_queue();
    head = Restaurar_Lista(head);
    Restaurar_FILA();
    system("cls");
    //system("pause");
    
    while (1){
        system("cls");
            op = menuPrincipal();
        switch (op)
        {
        case 1: Administrador();
            break;
        case 2: Avaliador();
            break;
        case 0: exit(EXIT_SUCCESS);
                break;
        default: printf("\nopcao invalida!!"); system("pause");
            break;
        
        }
}

return 0;
}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




//--------------------------------- Todas as funcoes ---------------------------------------------/


//Menu principal de Login
int menuPrincipal(){
    int op;
time_t mytime;       // Para conseguir a data exata
    mytime = time(NULL);
struct tm tm = *localtime(&mytime); 
   DIA = tm.tm_mday;
   MES= (tm.tm_mon + 1);
   ANO = (tm.tm_year + 1900);
    printf("\n==============================================================================================\n");
    printf("\t    BEN VINDO AO AVALIADOR DE PROPRIEDADES\t\t\t[Data: %d/0%d/%d ]", DIA, MES,ANO);
    printf("\n==============================================================================================\n\n\n");
        printf("\t+====================================+\n"); 
        printf("\t|    Escolha uma opcao de login      |\n");
        printf("\t|====================================|\n");
        printf("\t|1 -> Login como Administrador       | \n");
        printf("\t|2 -> Login como Avaliador           |\n");
        printf("\t|0 -> Fechar o progama               |\n");
        printf("\t+------------------------------------+\n");
        printf(" Opcao>> ");
        fflush(stdin);
        scanf ("%d", &op);
    return op;
}


//Menu de utilizador do tipo Adiministrador
int menuAdim(){
    
    int op;

        printf("\n\t\t\t+================================================================+\n");
        printf("\t\t\t|          > > > >   MENU DE ADMINISTRADOR  < < < <              |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t| 1  -> Adicionar um utilizador                                  |\n");
        printf("\t\t\t| 2  -> Incirir propriedades na lista                            |\n");
        printf("\t\t\t| 3  -> Alterar dados de uma propriedade.                        |\n");        
        printf("\t\t\t| 4  -> Apagar uma propriedade.                                  |\n");
        printf("\t\t\t| 5  -> Pesquisar Propriedades pelo identificador.               |\n");
        printf("\t\t\t| 6  -> Pesquisar propriedades por nome do proprietario.         |\n");
        printf("\t\t\t| 7  -> listar todas as propriedades                             |\n");
        printf("\t\t\t| 8  -> listar todas as propriedades por analisar                |\n");
        printf("\t\t\t| 9  -> listar todas propriedades avaliadas.                     |\n");
        printf("\t\t\t| 10 -> listar propriedades com avaliacoes acima de n valor.     |\n");
        printf("\t\t\t| 11 -> listar todas as propriedades avaliadas por um avaliador. |\n");
        printf("\t\t\t| 12 -> Ler relatorios das propriedades avaliadas                |\n");
        printf("\t\t\t| 20 -> guardar e ir para o para o menu principal.               |\n");
        printf("\t\t\t| 0 -> Guardar e sair.                                           |\n");
        printf("\t\t\t| 21  -> sair sem guardar.                                       |\n");
        printf("\t\t\t+----------------------------------------------------------------+\n");
        fflush(stdin);
        printf(" \t\tOpcao>> ");
        scanf ("%d", &op);
    return op;

}

//Menu de Peincipal
int menuAval(){
    int op;
    printf("\n\t\t\t+=====================================+\n");
    printf("\t\t\t|            MENU DE PRINCIPAL          |\n");
    printf("\t\t\t+=======================================+\n");
    printf("\t\t\t| 1 -> Gestao de Animais                |\n");
    printf("\t\t\t| 2 -> Gestao de tratadores             |\n");
    printf("\t\t\t| 3 -> Marcacao/Consultas de VIsitas    |\n");
    printf("\t\t\t| 0 -> Sair                             |\n");
    printf("\t\t\t+---------------------------------------+\n");
    printf(" \t\tOpcao>> ");
    fflush(stdin);
    scanf ("%d", &op);

    return op;
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


//Funcao para administrador onde chama todas as funcoes para realizar tarefas para o administrador
void Administrador(){
int op, op2, nu;
float val;
char nome[20], avaliad[20];
UTILIZADORES Utilizador_Logado;
   

do {
        Utilizador_Logado = autenticador();
        if (strcmp(Utilizador_Logado.tipo, TIPO_Ad) == 0){
        printf ("\nLogin com sucesso!");
        printf ("\nSeja ben vindo %s.\n\n\n.", Utilizador_Logado.nome);
        system("pause");
            do {    system("cls");
                    op = menuAdim();
                    system("cls");

                switch (op){
                    
                    case 1: inserir_Utilizador();
                        break;
                    case 2: head = Insirir_propriedades(head);
                        break;

                    case 3:  fflush(stdin);
                            printf ("\nIdentificador da propriedade: ");
                            scanf("%d", &nu);
                            head = Alterar_Dado(head, nu);
                        break;
                    case 4: head = apagar_Popriedade(head);
                        break;
                   
                    case 5:  
                            fflush(stdin);
                            printf ("\nIdentificador da propriedade <<ID>-");
                            scanf("%d", &nu);
                            Pesquisar(head, nu);
                        break;
                    case 6: printf ("\nPropiatario>>");
                            scanf ("%s", nome);
                            Pesquisar_Propri_Por_Nome(head, nome);
                        break;

                 
                    case 7: head = Listar_proriadades(head);
                        break;
                    case 8: Listar_Propri_Por_Aval(head);
                        break;
                    case 9: Listar_Propri_Aval(head);
                        break;
                    case 10: printf ("\nvalor >>");
                            scanf ("%f", &val);
                            Listar_Propri_Aval_Acima_N_VALOR(head, val);
                        break;
                      case 11:  
                            printf ("\n/------------------Listar propriedades avaliadas por avaliador---------------------/\n\n");
                            printf ("\nAVALIADOR >>: ");
                            fflush(stdin);
                            scanf("%s", avaliad);
                            Listar_Propri_Aval_Por_Utili(head, avaliad);
                        break;    
                    case 12: Relatorio_Propri_Aval(head);
                        break;
                    case 20: Salvar_Lista(head);Salvar_fila(fila);
                        break;
                    case 0: Salvar_Lista(head);Salvar_fila(fila); exit(EXIT_SUCCESS);
                        break;
                    case 21: exit(EXIT_SUCCESS);
                        break;
                    default: printf("\nopcao invalida!!"); system ("pause");
                        break;
                }
            
            } while (op != 20);

    }else if (strcmp(Utilizador_Logado.tipo, TIPO_Av ) == 0){
                printf("\nUtilizador introduzido nao eh um administrador!!!\n");
                }else
                {
                    printf("\nUsername ou password incoreto!!!\n");
            }

    printf ("\nIncira qualquer coisa para continuar ou '20' para voltar au menu anterior!\n-->");
        fflush(stdin);
    scanf ("%d", &op2);
    system("cls");
    } while (op2 != 20 );

}



//Funcao para Avaliador onde encontra todas as operacoes destinadas a um avaliador
void Avaliador(){
    int op, op2, nu;
    UTILIZADORES Utilizador_Logado;

do {
    Utilizador_Logado = autenticador();
    if (strcmp(Utilizador_Logado.tipo, TIPO_Av) == 0){
        printf ("\nLogin com sucesso!");
        printf ("\nSeja ben vindo %s.\n\n\n.", Utilizador_Logado.nome);
        system("pause");
        do {   
                system("cls");
                op = menuAval();
                system("cls");

            switch (op){

                 case 1:  head = Listar_proriadades(head);
                      break;
                case 2:  
                        fflush(stdin);
                        printf ("\nIdentificador da propriedade: ");
                        scanf("%d", &nu);
                        head = Insirir_propriedade_Fila(head, nu); 
                    break;
                case 3: Listar_Fila();
                    break;
                case 4: head = Avaliar(head, Utilizador_Logado);
                    break;
                case 20:  Salvar_Lista(head);Salvar_fila(fila);
                    break;
                case 0:   Salvar_Lista(head);Salvar_fila(fila); exit(EXIT_SUCCESS);
                    break;
                case 10:   exit(EXIT_SUCCESS);
                    break;
                default: printf("\nopcao invalida!!");
                    break;
            }
        
         } while (op != 20);

}else if (strcmp(Utilizador_Logado.tipo, TIPO_Ad ) == 0){
            printf("\nUtilizador introduzido nao eh um avaliador!!\n");
            }else
            {
                printf("\nUsername ou password incoreto!!!\n");
        }

printf ("\nIncira qualquer coisa para continuar ou '20' para voltar au menu anterior!\n-->");
    fflush(stdin);
scanf ("%d", &op2);
system("cls");
   } while (op2 != 20 );

}


//############################################################################################
// Função para chamar cabeçalho
void cabecalho(FILE *out, int id, char estado[20]){
    fprintf(out, "\n\n");
    fprintf(out, "\t\t+===============================================+\n");
    fprintf(out, "\t\tPROPRIEDADE << %s >>\t\tID->[ %d] \n", estado, id);
    fprintf(out, "\t\t+===============================================+\n");
}

void divi(FILE *out){
    fprintf(out, "\t\t+-----------------------------------------------+\n");
}

// Função para chamar rodape
void rodaPe(FILE *out){
    fprintf(out, "\t\t+===============================================+\n");
}


//Funcao para imprimir erro de alocação de memoria
void erro(){
    printf ("Erro na alocacao de memoria!");
        exit(EXIT_FAILURE);
    
    }

//funcao para ler dados de um propriedade
PROPRIADADES ler_daos_propr(PROPRIADADES prop){
        printf ("\n/--------------------->> Incirir propriedade <<-------------------------------/");
        fflush(stdin);
        printf ("\nNome do proprietario>> ");
        gets(prop.nomeProprietario); 
        fflush(stdin);  
        printf ("Area total da em m2 >>");
        scanf ("%f", &prop.area);
        fflush(stdin);
        printf ("Descricao>>");
        gets(prop.discricao);
        fflush(stdin);
        printf ("Incira no maximo 20 cultivas cultiavadas um por um, quando terminar incira digite 0 :\n");
        for (int i = 0; i < 20 ; i++) {   
            
            printf ("--->");
            gets(prop.cult[i].cultura);
            if (strcmp(prop.cult[i].cultura, "0") == 0) break;
        }
return prop;
}

//Funcao para ler dados de um utilizador
UTILIZADORES ler_daos_util( UTILIZADORES utilizador){   
    UTILIZADORES utilizadores[20];
    char *pass1, *pass2, *tipo, *userN;
    int valida;
    FILE *test;

//Testando a abertura do ficheiro 
 if ((test = fopen("Login.dat","r+b")) == NULL) {
            printf("\nNao foi possivel aceder ao base de dados de Login !!!!\n");
            exit(EXIT_FAILURE);
 }

  //Alocação de memoria para pass1, pass2, tipo e nome
 pass1 = (char *) malloc(sizeof(char));
        if (pass1 == NULL) erro();
 pass2 = (char *) malloc(sizeof(char));
        if (pass2 == NULL) erro();
 userN = (char *) malloc(sizeof(char));
        if (pass2 == NULL) erro();
 tipo = (char *) malloc(sizeof(char));
        if (pass2 == NULL) erro();

 printf(" -----> > > > [Cadastro do Utilizador] < < < <-------\n ");
  
        printf("Nome>> ");
        fflush(stdin);
        gets(utilizador.nome);
        while (1){
            fflush(stdin);
            printf("Tipo(administrador/avaliador)>> ");
            scanf("%s", tipo);
                        if (strcmp(tipo, TIPO_Ad) == 0 || strcmp(tipo, TIPO_Av) == 0){
                                strcpy(utilizador.tipo, tipo);
                                break;
                        }else{
                                printf ("\nNao existe esse tipo de utilizador!!!\n");              
                            } 
                free(tipo);
            } 
        //Pedir dados de utilizador
        while (1){
            free(userN);
            printf ("Username >>");
            fflush(stdin);
            gets(userN);
           
            valida = TRUE;;

            rewind(test);
            for (int i = 0; i < qtd_util; i++) {
            fread(utilizadores, sizeof(utilizador), qtd_util, test); // Utilizando estratégia de bloco para verificar o username
                if (strcmp(utilizadores[i].username, userN) == 0 ) {
                    printf ("\nJa existe username '%s'.\n", utilizadores[i].username);
                    valida = FALSE;
                    break;
                 }    
            } 

            if (valida == TRUE){ strcpy(utilizador.username, userN); break;}
            
          
          }
          
          
        
        while (1){
            printf("Insira palavra-passe>> ");
            fflush(stdin);  
            scanf("%s", pass1);      
            printf("Confirme a palavra-passe>> ");
            scanf("%s", pass2);
                    if (strcmp(pass1, pass2) == 0){
                        strcpy (utilizador.pasword, pass1);
                        free(pass1);
                        free(pass2);
                        break;
                    } else{
                            printf ("\nPalavra-passe diferentes!!! \n");

    }
  free(pass1);
 free(pass2);
}
    free(tipo);
    free(userN);               
  
  //  fclose(test);
    return utilizador;
}


// Funcao para incirir utilizadores na Ficheiro de Login
 void inserir_Utilizador(){
    FILE *fp;
    UTILIZADORES User, utilizador;

      
utilizador = ler_daos_util(User);

   
//Gravar o utilizador no Ficheiro binario  
 if ((fp = fopen("Login.dat","a+b")) == NULL) {
            printf("\nNao foi possivel aceder ao base de dados de Login !!\n");
            exit(EXIT_FAILURE);
 }
fwrite(&utilizador, sizeof(utilizador), 1, fp);
  fflush(fp);
  printf("\nutilizador do tipo %s inserido com sucesso!!\n", utilizador.tipo);
system("pause");

 }

// Funcao para fazer Login--------------------------------------------
UTILIZADORES autenticador(){
    FILE *log;

    //Um super utilizador para fazer login pela primeira vez gundo iniciado o progama
    char Superuser[] = "administrador";
    char Password[] = "super";
    char nome[] = "Super Adiministrador";
    char *user,*passw;
    //int tipo;
    UTILIZADORES utilizador, utilizadores[1000];
  
//Alocação de memoria 
 user = (char *) malloc(sizeof(char));
      if (user == NULL) erro();
 passw = (char *) malloc(sizeof(char));
      if (passw == NULL) erro();
    

    printf ("\n\n\n-------------> > > > > Faca o login < < < < < <------------");
    printf ("\nUsername >> ");
    fflush(stdin);
    gets(user);
    fflush(stdin);
    printf ("Pasword >> ");
    gets(passw);
    printf ("------------------------------------------------------------------\n");
    
  

if (strcmp(user, Superuser) == 0 && strcmp(passw, Password) == 0 ){
    strcpy(utilizador.nome, nome);
    strcpy(utilizador.tipo, TIPO_Ad);
    free(user);
    free(passw);
    return utilizador;
  }else { 

    if ((log = fopen("Login.dat", "r+b")) == NULL) {
            printf("\nNão foi possivel aceder ao base de dados de autentificação !!\n");
            exit(EXIT_FAILURE);
    } else{
            rewind(log);
            for (int i = 0; i < qtd_util; i++) {
            fread(utilizadores, sizeof(UTILIZADORES), qtd_util, log); // Utilizando estratégia de bloco para verificar o username e o password.
    

            if (strcmp(utilizadores[i].username, user) == 0 && strcmp(utilizadores[i].pasword, passw) == 0) {
                utilizador = utilizadores[i];  
                free(user);
                free(passw);  
                }
        } 
    fclose(log);
     }
}
            
                free(user);
                free(passw);
    return utilizador;
}
    
//&&&&&&&&&&&&&&&&&&&& LISTAS e Filas   &&&&&&&&&&&&&7

//Fução para Listar todas as propriedades
LISTA  *Listar_proriadades(LISTA *head) {
    LISTA *aux;
    aux = head;

    if (aux == NULL)
    {
       printf("\n A Lista se encontra vazia: ");
    }else{   
    
    printf("\nLista de propriedades: ");

    while(aux != NULL){
        cabecalho (stdout,aux->data.numero, aux->data.estado.avaliacao);
        printf ("\t\t| Propiatario:| %30s  |\n", aux->data.nomeProprietario);
        divi(stdout);
        printf ("\t\t|  Area:      |%30f m2|\n", aux->data.area);
        divi(stdout);
        printf ("\t\t|  Discricao: | %30s  |\n", aux->data.discricao);
        divi (stdout);
        printf ("\t\t|Cultivos da propriadade: |                     |\n");
        printf ("\t\t+-------------------------#                     |\n");
             for (int i = 0; i < 20; i++){
                if (strcmp (aux->data.cult[i].cultura, "0") == 0) break;
                printf("\t\t|%23s\t\t\t|\n", aux->data.cult[i].cultura);
             }   
        divi (stdout);
             
    

    if (strcmp (aux->data.estado.avaliacao, Aval) == 0){
            printf ("\t\t|Avaliado por:|%22s\t\t|\n", aux->data.Avaliacao.avaliador);
            divi (stdout);
            printf ("\t\t|  >> Em      |%23d/%d/%d   |\n", aux->data.Avaliacao.dia, aux->data.Avaliacao.mes,aux->data.Avaliacao.ano);
            divi(stdout);
            printf ("\t\t|  >> Valor:  |%30f £ |\n", aux->data.Avaliacao.valor);
            rodaPe(stdout);
            printf ("\n\n\n");
        }
        
        aux = aux->next; 
   }
    }
    
 
    printf("\n\n");
    system("pause");
    return head;
}

//Função para incirir propriedade na Lista
LISTA *Insirir_propriedades(LISTA *head) {
    LISTA *novo, *aux;
    PROPRIADADES propr, propriedade;
    
    propriedade = ler_daos_propr(propr);
   
    novo = (LISTA*) malloc(sizeof(LISTA));
    novo->data = propriedade;
    novo->next = NULL;
    strcpy(novo->data.estado.avaliacao," ");
    if (head == NULL) {
        head = novo;
        novo->data.numero = 1;
        printf ("ID gerado: %d\n", novo->data.numero);
    } else {
        aux = head;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        novo->data.numero = aux->data.numero + 1;
        aux->next = novo;
    printf ("ID gerado: %d\n", novo->data.numero);
    }
    
    printf("\nPropriedade inserida na Lista das propriedades!!!!\n");
    system("pause");
    return head;
}

//Função para apagar uma propriedade
LISTA *apagar_Popriedade(LISTA *head) {
    LISTA *aux, *prev;
    //PROPRIADADES proprirdade;
    int identif;
    char cond[4];//usa para alojar a resposta do utilizador se quer realmente apagar
    printf("Insira o ID da propriedade a apagar: ");
    scanf("%d", &identif);
    aux = head;
        if (aux->data.numero == identif) {
            printf("\nPretente apagar Propriedade com ID-<<%d>> de %s?(yes/sim or no)", aux->data.numero, aux->data.nomeProprietario);
                while (1){
                                    printf(">");      
                                    scanf ("%s", cond);
                                if (strcmp(cond, "yes") == 0 || strcmp(cond, "sin")== 0)   {
                                            head = head->next;
                                     printf("\nPropriedade [%d] de %s foi apagada com sucesso!", aux->data.numero, aux->data.nomeProprietario);
                                    free(aux);
                                            break;
                                }else if (strcmp(cond, "no") == 0){
                                        printf("\nNão foi apagado nenhuma propriedade.");break;
                                }else{ printf("\nOpcao invalida\n");}


            }
            

            
        } else {
            while (aux != NULL ) {
                
            if (aux->data.numero == identif) {           
             while (1){
                                    printf("\nPretente apagar Propriedade(%d) de %s?(yes/sim or no)", aux->data.numero, aux->data.nomeProprietario);
                                    printf(">");      
                                    scanf ("%s", cond);
                                if (strcmp(cond, "yes") == 0 || strcmp(cond, "sim") == 0) {
                                            prev->next = aux->next;
                                             printf("\nPropriedade [%d] de %s foi apagada com sucesso!", aux->data.numero, aux->data.nomeProprietario);
                                             free(aux);
                                            break;
                                }else if (strcmp(cond, "no") == 0){
                                        printf("\nNão foi apagado nenhuma propriedade.");break;
                                }else{ printf("\nOpcao invalida");}
             }
             }

             prev = aux;
             aux = aux->next;
            

}

}
if (prev->next == NULL)  { printf("\nPropriedade nao encontrada!.");}
system("pause");
 return head;
}
   
//Funcao para pesquisar uma propriedade pelo seu identificador que por acaso é u seu numero
void Pesquisar(LISTA *head, int num){
        LISTA *aux; 
        aux = head;
           if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");

            }else {
                   
                 while (1){
                        
                        if (aux->data.numero == num){
                          cabecalho (stdout,aux->data.numero, aux->data.estado.avaliacao);
                          printf ("\t\t| Propiatario:| %30s  |\n", aux->data.nomeProprietario);
                          printf ("\t\t|  Area:      |%30f   |\n", aux->data.area);
                        printf ("\t\t|  Discricao: | %30s  |\n", aux->data.discricao);
                        divi (stdout);
                        printf ("\t\t|Cultivos da propriadade: |                     |\n");
                        printf ("\t\t+-------------------------#                     |\n");
                            for (int i = 0; i < 20; i++){
                                if (strcmp (aux->data.cult[i].cultura, "0") == 0) break;
                                printf("\t\t|%23s\t\t\t|\n", aux->data.cult[i].cultura);
                            }   
                        divi (stdout);
                            } 
                      while (aux->next != NULL )
                        {
                        aux = aux->next;
                        if (aux->data.numero == num)break;
                        }
                     if(aux->next == NULL ) {printf ("\nPropriedade nao encontrada!!\n");break;}    
                    }
                        
                 }       
                   

   system("pause"); 
 }

void Pesquisar_Propri_Por_Nome(LISTA *head, char nome[20]){
        LISTA *aux; 
        aux = head;
        int valida;
           if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");

            }else {

               while (aux->next != NULL )
                        {                         
                        if (strcmp (aux->data.nomeProprietario, nome) == 0){
   

                 cabecalho(stdout,aux->data.numero, aux->data.estado.avaliacao);
                 printf ("\t\t| Propiatario:| %30s  |\n", aux->data.nomeProprietario);
                 divi(stdout);
                 printf ("\t\t|  Area:      |%30f m2|\n", aux->data.area);
                divi(stdout);
                 printf ("\t\t|  Discricao: | %30s  |\n", aux->data.discricao);
                 rodaPe(stdout);
                            valida = TRUE;
                            } 
                        aux = aux->next;
                        }
                     if(valida != TRUE)printf ("\nPropriedade nao encontrada!!\n");    
            }    
                   

   system("pause"); 
 }
//funcao para alterar dados de uma propriedade dado o identificador
LISTA *Alterar_Dado(LISTA *head, int num){
        LISTA *aux;
        PROPRIADADES prop;
        aux = head;
           if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");

            }else {
                   
                 while (aux->next != NULL ){
                        
                        if (aux->data.numero == num){
                                prop = ler_daos_propr(prop);
                                if (strcmp (aux->data.estado.avaliacao, Aval) == 0){
                                    prop.Avaliacao.valor = aux->data.Avaliacao.valor;
                                    prop.Avaliacao.dia = aux->data.Avaliacao.dia;
                                    prop.Avaliacao.mes = aux->data.Avaliacao.dia;
                                    prop.Avaliacao.ano = aux->data.Avaliacao.ano;
                                }
                                strcpy (prop.estado.avaliacao, aux->data.estado.avaliacao);
                                aux->data = prop;
                                aux->data.numero = num;
                                printf ("\nDados Alterados!\n");
                                if (strcmp (aux->data.estado.avaliacao, Aval) == 0){
                                    prop.Avaliacao.valor = aux->data.Avaliacao.valor;
                                    prop.Avaliacao.dia = aux->data.Avaliacao.dia;
                                    prop.Avaliacao.mes = aux->data.Avaliacao.dia;
                                    prop.Avaliacao.ano = aux->data.Avaliacao.ano;
                                }
                                break;
                            }
                                
                             
                      
                           
                                aux = aux->next;
                            
                                }
                        if(aux == NULL )printf ("\nPropriedade nao encontrada!!\n");    
                        
                        
                 }    
    
    system("pause"); 
    return head;
 }

//Função para salvar a lista num ficheiro binario
void Salvar_Lista(LISTA *head){
    FILE *Propr;
    LISTA *aux;
     if ((Propr = fopen("propriedade.dat","w+b")) == NULL) {    //Usei "w+b" para  apagar o filaue tiver no ficheiro antes de salvar
            printf("\nNao foi possivel aceder ao ficheiro para gravar a lista.!\n");
 }    

    for (aux = head; aux != NULL; aux = aux->next){
            fwrite (&aux->data, sizeof(PROPRIADADES), 1,Propr);
    }
fclose(Propr);
}

//funcao de criar uma fila
void creat_queue(){
fila = (FILA*) malloc(sizeof(FILA));
fila->front = NULL;
fila->rear = NULL;
}

//funcao que vai insirir um no na fila
void enqueue(PROPRIADADES prop){
    LISTA *newNod;
    newNod = (LISTA*) malloc(sizeof(LISTA));
    newNod->data = prop;
    if (fila->front == NULL){
        fila->front = newNod;
        fila->rear = newNod;
        fila->front->next = NULL;
    }else
    {
        fila->rear->next = newNod;
        fila->rear = newNod;
        fila->rear->next = NULL;
    }
}


// funcao que apresenta o primeiro no (valor) na fila
LISTA *Avaliar(LISTA *head, UTILIZADORES util){
    LISTA *aux2;
    aux2 = head;
    //PROPRIADADES prop;
    if (fila->front == NULL){
        printf("\nFila vazia!!!\n\n");
  
    }else{
        
        strcpy(fila->front->data.estado.avaliacao, EM_Aval);
        cabecalho(stdout,fila->front->data.numero, fila->front->data.estado.avaliacao);  
        printf ("\t\t| Propiatario:| %30s  |\n", fila->front->data.nomeProprietario);
        divi(stdout);
        printf ("\t\t|  Area:      |%30f m2|\n", fila->front->data.area);
        divi(stdout);
        printf ("\t\t|  Discricao: | %30s  |\n", fila->front->data.discricao);
        divi (stdout);
        printf ("\t\t|Cultivos da propriadade: |                     |\n");
        printf ("\t\t+-------------------------#                     |\n");
             for (int i = 0; i < 20; i++){
                if (strcmp (fila->front->data.cult[i].cultura, "0") == 0) break;
                printf("\t\t|%23s\t\t\t|\n", fila->front->data.cult[i].cultura);
             }   
        rodaPe(stdout);
        printf("\tAvaliar a propriedade;\n");
        printf("\t\tValor em (£)>> ");
        scanf("%f", &fila->front->data.Avaliacao.valor);
    strcpy(fila->front->data.estado.avaliacao, Aval);
    strcpy(fila->front->data.Avaliacao.avaliador, util.nome);   
    fila->front->data.Avaliacao.dia = DIA;
    fila->front->data.Avaliacao.mes = MES;
    fila->front->data.Avaliacao.ano = ANO;
    printf("\t\tData de avaliacao >> %d/0%d/%d\n", DIA, MES, ANO);
    printf("\t\tAvaliador >> %s\n\n", fila->front->data.Avaliacao.avaliador );

        
    aux2 = head;
while (1)
{      
      if (aux2->data.numero == fila->front->data.numero){
                    aux2->data =  fila->front->data; break;
                            } 
                      while (aux2->next != NULL )
                        {
                        aux2 = aux2->next;
                        if (aux2->data.numero == fila->front->data.numero)break;
                        }
    
}
    fila->front = fila->front->next;
    
}
//free(aux);
system("pause");
return head;

}

//Funcao para listar toda a fila
void Listar_Fila(){
    LISTA *aux;
    aux = fila->front;
    if (fila->front == NULL){
      printf("\nFila vazia");
     } else {
        printf("\n");
        while (aux != NULL)
        {
        cabecalho(stdout,aux->data.numero, aux->data.estado.avaliacao);  
        printf ("\t\t| Propiatario:| %30s  |\n", aux->data.nomeProprietario);
        printf ("\t\t|  Area:      |%30f   |\n", aux->data.area);
        printf ("\t\t|  Discricao: | %30s  |\n", aux->data.discricao);
        divi(stdout);
        printf ("\t\t|Cultivos da propriadade: |                     |\n");
        printf ("\t\t+-------------------------#                     |\n");
             for (int i = 0; i < 20; i++){
                if (strcmp (aux->data.cult[i].cultura, "0") == 0) break;
                printf("\t\t|%23s\t\t\t|\n", aux->data.cult[i].cultura);
             }   
        divi(stdout);
        
        aux = aux->next; 
        }
    }
    system("pause"); 
}

//Funcao que  adiciona uma propriedade na fila
LISTA *Insirir_propriedade_Fila(LISTA *head, int num){

    LISTA *aux;
        aux = head;
           if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");

            }else {                   
                 while (aux != NULL ){
                            if (aux->data.numero == num){
                                if (strcmp(aux->data.estado.avaliacao, Aval) == 0){
                                printf ("A propriedade solicitada ja foi avaliada!!\n");break;
                                }else if (strcmp(aux->data.estado.avaliacao, POR_AVAL) == 0){
                                    printf ("A propriedade solicitada ja esta na fila de espera!!\n");break;
                                }
                                
                               strcpy (aux->data.estado.avaliacao, POR_AVAL); 
                               enqueue(aux->data);
                               printf("\nPropriedade adicionada a fila para avaliacao.\n");
                               break;
                            }
                                
                             
                     
                           
                                aux = aux->next;
                                
                                
                        if(aux == NULL )printf ("\nPropriedade nao encontrada!!\n");  
                    }    
                        
                 }    
    
    system("pause"); 
    return head;
}

//Funcao para restaurar as alteracoes guardadas antes de fechar o progama
LISTA *Restaurar_Lista(LISTA *head){
    PROPRIADADES prop;
    FILE *lista;
    LISTA *novo, *aux;
   

     if ((lista = fopen("propriedade.dat", "rb")) == NULL) { 
            printf("\nNao foi possivel aceder ao ficheiro para restourar a lista.!\n");
 } else{

if (lista != NULL){
      while (fread(&prop, sizeof(PROPRIADADES), 1, lista))
      {
          novo = (LISTA*) malloc(sizeof(LISTA));
    novo->data = prop;
    novo->next = NULL;
    if (head == NULL) {
        head = novo;
    } else {
        aux = head;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = novo;
    }
      }
       }
     }  
fclose(lista);
 printf("\nLista restaurada!!!\n");
 return head;
}


//Esta funcao serve para salvar dados de uma fila quando o usuario sair
void Salvar_fila(FILA *fila){
    FILE *Fila;
    LISTA *aux;
     if ((Fila = fopen("fila.dat","w+b")) == NULL) {    //Usei "w+b" para  apagar o que tiver no ficheiro antes de salvar
            printf("\nNao foi possivel aceder ao ficheiro para gravar a FILA.!\n");
 }    

    for (aux = fila->rear; aux != NULL; aux = aux->next){
            fwrite (&aux->data, sizeof(PROPRIADADES), 1, Fila);
    }
fclose(Fila);
}  
//funcao para restaurar dados guardados de uma fila
void Restaurar_FILA(){
    FILE *Fila;
    PROPRIADADES prop;
    LISTA *newNod;
    fila->front = NULL;
  
     if ((Fila = fopen("fila.dat", "rb")) == NULL) { 
            printf("\nNao foi possivel aceder ao ficheiro para restourar a Fila.!\n");
 } else{

      while (fread(&prop, sizeof(PROPRIADADES), 1, Fila))
      {
    
     newNod = (LISTA*) malloc(sizeof(LISTA));
    newNod->data = prop;
    if (fila->front == NULL){
        fila->front = newNod;
        fila->rear = newNod;
        fila->front->next = NULL;
    }else
    {
        fila->rear->next = newNod;
        fila->rear = newNod;
        fila->rear->next = NULL;
    }
      }
       
     }  
fclose(Fila);
 printf("\nFILArestaurada!!!\n");

}

//listar todas as propriedades por avaliar
void Listar_Propri_Por_Aval(LISTA *head){
        LISTA *aux; 
        aux = head;
           if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");

            }else {
                while(aux != NULL){

                        if (strcmp(aux->data.estado.avaliacao, POR_AVAL) == 0)
                        {
                            
                        
                        
                  cabecalho(stdout,aux->data.numero, aux->data.estado.avaliacao);
                 printf ("\t\t| Propiatario:| %30s  |\n", aux->data.nomeProprietario);
                 divi(stdout);
                 printf ("\t\t|  Area:      |%30f m2|\n", aux->data.area);
                 divi(stdout);
                 printf ("\t\t|  Discricao: | %30s  |\n", aux->data.discricao);
                rodaPe(stdout);
                }    

        
        aux = aux->next; 
   }
 }                
                   

   system("pause"); 
 }

//Funcao para listar todas as propriedades avaliadas
 void Listar_Propri_Aval(LISTA *head){
        LISTA *aux; 
        aux = head;
           if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");

            }else {
                while(aux != NULL){

                        if (strcmp(aux->data.estado.avaliacao, Aval) == 0)
                        {         
                        
           cabecalho(stdout,aux->data.numero, aux->data.estado.avaliacao);  
                printf ("\t\t| Propiatario:| %30s  |\n", aux->data.nomeProprietario);
                divi(stdout);
                printf ("\t\t|  Area:      |%30f m2|\n", aux->data.area);
                divi(stdout);
                printf ("\t\t|  Discricao: | %30s  |\n", aux->data.discricao);
                divi(stdout);
                printf ("\t\t|  >> Valor:  |%30f £ |\n", aux->data.Avaliacao.valor);
                rodaPe(stdout);
                }   
        aux = aux->next; 
   }
 }                
                   

   system("pause"); 
 }

//Funcao para listar todas as propriedades avaliadas com o valor acima d N valor que sera introduzido pelo usuario
void Listar_Propri_Aval_Acima_N_VALOR(LISTA *head, float val){
        LISTA *aux; 
        aux = head;
           if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");

            }else {
                while(aux != NULL){

                        if (strcmp(aux->data.estado.avaliacao, Aval) == 0 && aux->data.Avaliacao.valor > val)
                        {         
                        
                 cabecalho(stdout,aux->data.numero, aux->data.estado.avaliacao);  
                printf ("\t\t| Propiatario:| %30s  |\n", aux->data.nomeProprietario);
                divi(stdout);
                printf ("\t\t|  Area:      |%30f m2|\n", aux->data.area);
                divi(stdout);
                printf ("\t\t|  Discricao: | %30s  |\n", aux->data.discricao);
                divi(stdout);
                printf ("\t\t|  >> Valor:  |%30f  £|\n", aux->data.Avaliacao.valor);
                rodaPe(stdout);
                }   
        aux = aux->next; 
   }
 }                
                   

   system("pause"); 
 }

//Funcao que lista todas as propriadades avaliadas por un determinado utilizador que sera introduzido na linha de comando
 void Listar_Propri_Aval_Por_Utili(LISTA *head, char avaliador[20]){
        LISTA *aux; 
        aux = head;
        int cond;
           if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");
            }else {
                while(aux != NULL){

                        if (strcmp(aux->data.estado.avaliacao, Aval) == 0  && strcmp(aux->data.Avaliacao.avaliador, avaliador) == 0 )  {                  
                printf ("\nListas das propriedades avaliadas pelo <<%s>>\n", avaliador);  
                 cabecalho(stdout,aux->data.numero, aux->data.estado.avaliacao);
                 printf ("\t\t| Propiatario:| %30s  |\n", aux->data.nomeProprietario);
                 divi(stdout);
                 printf ("\t\t|  Area:      |%30f m2|\n", aux->data.area);
                 divi(stdout);
                 printf ("\t\t|  Discricao: | %30s  |\n", aux->data.discricao);
                 divi(stdout);
                 printf ("\t\t|Avaliado por:|%22s\t\t|\n", aux->data.Avaliacao.avaliador);
                divi(stdout);
                printf ("\t\t|  >> Valor:  |%30f £ |\n", aux->data.Avaliacao.valor);
               rodaPe(stdout);
               cond = TRUE;
                }   
        aux = aux->next; 
   }
   if(cond != TRUE)printf ("\nNao existe nenhuma propriedade Avaliada pelo <<%s>>\n", avaliador);
 }                
   system("pause"); 
 }



//Funcao para fazer relatorios das propriedades avaliadas.
void Relatorio_Propri_Aval(LISTA *head){
    FILE *fp;
    LISTA *aux; 
    aux = head;


          if ((fp = fopen("Relatorio.text", "a+")) == NULL){
        printf("Nao foi possivel aceder ao ficheiro para gravar o relatorio das propriedades avaliadas!!!");
    }else if (aux == NULL){
                printf ("\nNao existe nenhuma propriedade na lista!\n");

            }else {

            fprintf(fp,"/------------------<< Lista de todas propriedades avaliadas >>------------------------/");
                while(aux != NULL){
  
        if (strcmp(aux->data.estado.avaliacao, Aval) == 0){
        fprintf (fp,"Propriedade <<<%s>>\n\t\tID->[%d]", aux->data.estado.avaliacao, aux->data.numero);                        
        fprintf (fp, " \t\t%s", aux->data.nomeProprietario);
        fprintf (fp,"\t\t%.3f m2" , aux->data.area);
        fprintf (fp,"\t\t %s", aux->data.discricao);
        fprintf(fp,"\t\t Culturas:\n");
        
        for (int i = 0; i < 20; i++)
        {
            if (strcmp(aux->data.cult[i].cultura, "0") == 0) break;
           
            fprintf(fp,"\t\t\t\t\t\t>%s\n", aux->data.cult[i].cultura);
        }         
        }          
        aux = aux->next;
 }                              
}
   system("pause"); 
    }

