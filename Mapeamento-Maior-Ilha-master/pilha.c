
#include "arq.h"

void inicializaPDDE(DescritorPDDE **descritor_pilha)
{
    *descritor_pilha = (DescritorPDDE *)malloc(sizeof(DescritorPDDE));
    (*descritor_pilha)->topo = NULL;
}

void push_stack(DescritorPDDE *descritor_pilha, int i, int j)
{
    Nodo_PDDE *New_Nodo;
    New_Nodo = (Nodo_PDDE *)malloc(sizeof(Nodo_PDDE));

    if (descritor_pilha->topo == NULL)
    { //Pilha esta vazia
        descritor_pilha->topo = New_Nodo;
        New_Nodo->acima = NULL;
        New_Nodo->abaixo = NULL;
        New_Nodo->coord_i = i;
        New_Nodo->coord_j = j;
    }
    else
    {
        New_Nodo->abaixo = descritor_pilha->topo;
        New_Nodo->acima = NULL;
        New_Nodo->coord_i = i;
        New_Nodo->coord_j = j;
        (descritor_pilha->topo)->acima = New_Nodo;
        descritor_pilha->topo = New_Nodo;
    }
}

void pop_stack(DescritorPDDE *descritor_pilha)
{
    if (descritor_pilha->topo == NULL)
    { //A pilha está Vazia
        printf("\nA pilha esta vazia, nao tem o que retirar!\n");
    }
    Nodo_PDDE *aux;
    aux = (Nodo_PDDE *)malloc(sizeof(Nodo_PDDE));
    if ((descritor_pilha->topo)->abaixo == NULL)
    {
        aux->abaixo = descritor_pilha->topo;
        free(aux->abaixo);
        free(aux);
        descritor_pilha->topo = NULL;
    }
    else
    {
        aux->abaixo = descritor_pilha->topo;
        descritor_pilha->topo = (aux->abaixo)->abaixo;
        (descritor_pilha->topo)->acima = NULL;
        free(aux->abaixo);
        free(aux);
    }
}
void reset_stack(DescritorPDDE *descritor_pilha)
{
    Nodo_PDDE *Aux = NULL;
    if (descritor_pilha->topo == NULL)
    {
        printf("A pilha nao possui elementos, portanto nao pode ser resetada\n\n");
        return;
    }
    else
    {
        Aux = descritor_pilha->topo->abaixo;
        while (Aux != NULL)
        {
            free(descritor_pilha->topo);
            descritor_pilha->topo = Aux;
            Aux = Aux->abaixo;
        }
        free(descritor_pilha->topo);
        descritor_pilha->topo = NULL;
    }
}
void destruct_stack(DescritorPDDE *descritor_pilha)
{
    reset_stack(descritor_pilha);
    free(descritor_pilha);
}
