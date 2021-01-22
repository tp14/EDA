#include "arq.h"
int main()
{
    FILE *Arquivo_Entrada;
    InfoMatriz DescritorMatriz;
    DescritorPDDE *descritor_pilha = NULL;
    int **Matriz;
    int last_rot;

    Inicializa_DescritorMatriz(&DescritorMatriz);
    Arquivo_Entrada = fopen("entrada.txt", "r"); //Somente Leitura
    Matriz = Aloca_Matriz(&DescritorMatriz);
    Preenche_Matriz(Arquivo_Entrada, Matriz, &DescritorMatriz);
    printf("MATRIZ RETIRADA DO ARQUIVO DE ENTRADA\n");
    printf("--------------------------------------------------------------\n");
    Imprime_Matriz(Matriz, &DescritorMatriz);
    printf("--------------------------------------------------------------\n");
    fclose(Arquivo_Entrada);

    inicializaPDDE(&descritor_pilha);
    last_rot = marcar(Matriz, &DescritorMatriz, descritor_pilha);
    printf("MATRIZ TOTALMENTE ROTULADA\n");
    printf("--------------------------------------------------------------\n");
    destruct_stack(descritor_pilha); //Pilha não será mais necessária, Rotulação ja foi feita;
    Imprime_Matriz(Matriz, &DescritorMatriz);
    Maior_objt(Matriz, last_rot);
    printf("--------------------------------------------------------------\n");
    printf("MATRIZ APENAS COM O MAIOR OBJETO \n(tambem esta no arquivo de saida)\n");
    printf("--------------------------------------------------------------\n");
    Imprime_Matriz(Matriz, &DescritorMatriz);
    printf("O arquivo saida.txt, com a matriz apresentando apenas o maior objeto ja foi gerado!");
    centroDoObjeto(Matriz);
    Libera_Matriz(Matriz, &DescritorMatriz);
    return 0;
}
