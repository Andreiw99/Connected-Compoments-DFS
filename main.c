#include <stdio.h>
#include <stdlib.h>
#include "functii.h"
#include <time.h>
int main()
{
    FILE *out_file=fopen("dataout.txt", "w");
    struct a_graph *graph; // se declara graful
    clock_t start,finish;
    double duration;
    start=clock();
    generate(); // Se genereaza o matrice de adiacenta random
    graph = calloc(1, sizeof(struct a_graph)); // se aloca memorie pt graf
    init_graph_file(graph);
    graph_Dfs(graph,0); // se parcurge plecand de la nodul 0
    int no_comp=1; // se pleaca de la ideea ca are cel putin o componenta conexa
    while(PozZero(graph->no_nodes-1) != 0)    // Daca in vectorul global apare o valoare de 0, inseamna ca s-a gasit
                                                // o alta componenta conexa
    {
        no_comp++;  // numarul de componente conexe creste cu 1
        graph_Dfs(graph,PozZero(graph->no_nodes)); // Se parcurge graful de la nodul corespunzator pozitiei  de unde s-a gasit
                                                       // cifra 0 in vector
    }
    finish=clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("duration: %.3fs ", duration);
    fclose(out_file);
    return 0;

    return 0;
}
