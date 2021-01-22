#include "arq.h"

void Inicializa_DescritorMatriz(InfoMatriz *descritor_Ptr)
{
    descritor_Ptr->linhas = 20;
    descritor_Ptr->colunas = 38;
    descritor_Ptr->total_caracteres = (20 * 39);
}

int **Aloca_Matriz(InfoMatriz *descritor_Ptr)
{
    int **matriz;
    int i;
    matriz = (int **)malloc(descritor_Ptr->linhas * sizeof(int *));
    if (matriz == NULL)
    {
        printf("ERROR::Matriz nao alocada");
    }
    for (i = 0; i < descritor_Ptr->colunas; i++)
    {
        matriz[i] = (int *)malloc(descritor_Ptr->colunas * sizeof(int));
        if (matriz[i] == NULL)
        {
            printf("ERROR::Memoria insuficiente para concluir alocação Dinamica");
        }
    }
    printf("Matriz Alocada com Sucesso!\n");
    return matriz;
}

void Libera_Matriz(int **Matriz, InfoMatriz *descritor_Ptr)
{
    int i;
    {
        for (i = 0; i < descritor_Ptr->linhas; i++)
        {
            free(Matriz[i]);
        }
        free(Matriz);
    }
}

void Preenche_Matriz(FILE *arq_function, int **Matriz, InfoMatriz *descritor_Ptr)
{
    int i, m = 0, n = 0; //M - linhas //N - colunas
    char caractere;
    int valor;
    for (i = 0; i < descritor_Ptr->total_caracteres; i++)
    {
        caractere = getc(arq_function);
        if (caractere == '\n')
        {
            m++;   //Incrementa Linha
            n = 0; //Zera coluna;
        }
        else
        {
            valor = (int)caractere;
            if (valor == '1')
            {
                Matriz[m][n] = 1;
            }
            else
            {
                Matriz[m][n] = 0;
            }
            n++; //Incrementa coluna
        }
    }
}

int Imprime_Matriz(int **Matriz, InfoMatriz *descritor_Ptr)
{
    int i, j;
    for (i = 0; i < descritor_Ptr->linhas; i++)
    {
        for (j = 0; j < descritor_Ptr->colunas; j++)
        {
            printf("%d", Matriz[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int marcar(int **Matriz, InfoMatriz *descritor_Ptr, DescritorPDDE *descritor_pilha)
{
    int i, j, k = 0, label = 2;
    for (i = 0; i < descritor_Ptr->linhas; i++)
    {
        for (j = 0; j < descritor_Ptr->colunas; j++)
        {
            while (k == 0)
            {
                if (Matriz[i][j] == 1)
                {
                    Matriz[i][j] = label;
                    push_stack(descritor_pilha, i, j);
                    rot(Matriz, descritor_pilha, i, j, label);
                    if (descritor_pilha->topo == NULL)
                        label++;
                }
                else if (Matriz[i][j] == label && descritor_pilha->topo != NULL)
                {
                    j = (descritor_pilha->topo)->coord_j;
                    i = (descritor_pilha->topo)->coord_i;
                    rot(Matriz, descritor_pilha, i, j, label);
                    if (descritor_pilha->topo == NULL)
                        label++;
                }
                else if (descritor_pilha->topo == NULL)
                {
                    break;
                }
            }
        }
    }
    return (label - 1);
}

void rot(int **Matriz, DescritorPDDE *descritor_pilha, int i, int j, int label)
{
    if (i < 38 && Matriz[i][j + 1] == 1) //direita
    {
        Matriz[i][j + 1] = label;
        j++;
        push_stack(descritor_pilha, i, j);
    }
    else if (i < 20 && Matriz[i + 1][j] == 1) //abaixo
    {
        Matriz[i + 1][j] = label;
        i++;
        push_stack(descritor_pilha, i, j);
    }
    else if (j != 0 && Matriz[i][j - 1] == 1) //esquerda
    {
        Matriz[i][j - 1] = label;
        j--;
        push_stack(descritor_pilha, i, j);
    }
    else if (i != 0 && Matriz[i - 1][j] == 1) //acima
    {
        Matriz[i - 1][j] = label;
        i--;
        push_stack(descritor_pilha, i, j);
    }
    else //Sem mais Vizinhos
        pop_stack(descritor_pilha);
}

int Maior_objt(int **Matriz, int last_rot)
{
    int i, j, size, k = 0, position;
    int cont = 2, biggest_value = 0;
    int vetor[last_rot - 1];
    int biggest_rot;
    while (cont <= last_rot)
    {
        for (i = 0; i < 20; i++)
        {
            for (j = 0; j < 38; j++)
            {
                if (Matriz[i][j] == cont)
                {
                    size++;
                }
            }
        }
        vetor[k] = size;
        size = 0;
        k++;
        cont++;
    }
    for (k = 0; k < (last_rot - 1); k++)
    {
        if (vetor[k] > biggest_value)
        {
            biggest_value = vetor[k];
            position = k;
        }
    }
    biggest_rot = position + 2;
    Gera_Saida(Matriz, biggest_rot);
    return (biggest_rot);
}

void Gera_Saida(int **Matriz, int biggest_rot)
{
    int i, j;
    FILE *Arq_saida;
    Arq_saida = fopen("saida.txt", "w");
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 38; j++)
        {
            if (Matriz[i][j] != biggest_rot)
            {
                Matriz[i][j] = 0;
            }
            else
            {
                Matriz[i][j] = 1;
            }
            fprintf(Arq_saida, "%d", Matriz[i][j]);
        }
        fprintf(Arq_saida, "\n");
    }
    fclose(Arq_saida);
}

void centroDoObjeto(int **Matriz)
{
    int i, j, n = 1;
    float soma_i = 0.0, soma_j = 0.0, x, y;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 38; j++)
        {
            if (Matriz[i][j] == 1)
            {
                soma_i += i;
                soma_j += j;
                n++;
            }
        }
    }
    n--;
    x = round(soma_i / n);
    y = round(soma_j / n);
    if ((x < 0.0) && (y < 0.0))
    {
        printf("A matriz nao possui nenhum objeto");
        printf("\nCoordenadas Aproximadas do Centro do Objeto:: [%.1f][%.1f]\n", x, y);
    }
    else
    {
        printf("\nCoordenadas Aproximadas do Centro do Objeto:: [%.1f][%.1f]\n", x, y);
    }
}
