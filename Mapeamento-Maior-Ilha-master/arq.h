#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct infomatriz
{
    int linhas;
    int colunas;
    int total_caracteres;
} InfoMatriz;

//Structs Pilha

typedef struct nodo
{
    int coord_i;
    int coord_j;
    struct nodo *acima;
    struct nodo *abaixo;
} Nodo_PDDE;

typedef struct DescritorPDDE
{
    Nodo_PDDE *topo;
} DescritorPDDE;

//Prototipos Pilha
void inicializaPDDE(DescritorPDDE **);
void push_stack(DescritorPDDE *, int i, int j);
void pop_stack(DescritorPDDE *);
void reset_stack(DescritorPDDE *);
void destruct_stack(DescritorPDDE *);

//Prototipos Aplicacao
void Inicializa_DescritorMatriz(InfoMatriz *);
int **Aloca_Matriz(InfoMatriz *);
void Tamanho_Matriz(FILE *, InfoMatriz *);
void Preenche_Matriz(FILE *, int **, InfoMatriz *);
int Imprime_Matriz(int **, InfoMatriz *);
void rot(int **, DescritorPDDE *, int, int, int);
int marcar(int **, InfoMatriz *, DescritorPDDE *);
int Maior_objt(int **, int);
void Gera_Saida(int **Matriz, int biggest_rot);
void centroDoObjeto(int **);
void Libera_Matriz(int **Matriz, InfoMatriz *descritor_Ptr);
