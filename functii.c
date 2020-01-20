#include <stdio.h>
#include <stdlib.h>
#include "functii.h"
#include <time.h>

void generate()
{
    FILE *file=fopen("datain.txt", "w");    // se deschide fisierul datain.txt pentru a scrie in el
    srand(time(NULL));
    int noduri,muchii;
    noduri = rand()%20000;  // se genereaza un numar random de noduri
    muchii = rand()%(noduri*(noduri-1)/2); // se genereaza un numar random de muchii cuprins intre noduri*(noduri-1)/2
                                 // deoarece intr-un graf complet, numarul maxim de muchii este egal cu noduri*(noduri-1)/2

    int x,y;        // x, y sunt nodurile intre care exista o muchie
    fprintf(file, "%d %d\n", noduri, muchii);
    int iterator;
    for(iterator=1;iterator<=muchii;iterator++)
    {
        x = rand()%noduri;
        y = rand()%noduri;
        if(x!=y)                // Nu poate exista muchie pentru un singur nod
            fprintf(file, "%d %d\n", x, y);
        else
            iterator--;
    }
    fclose(file);   // se inchide fisierul datain.txt
}



void set_adj_matrix_value(struct a_graph *graph, int row_index, int column_index, int element_value){       // Se creeaza matricea
    int position;
    position = row_index * graph->no_nodes + column_index;
    *(graph->adj_matrix + position) = element_value;
}


int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index) {      // returneaza valoarea din matrice
    int position;
    if (graph->init == 1){
        position = row_index * graph->no_nodes + column_index;
        return *(graph->adj_matrix + position);
    }else
        return -1;
}

// Se citeste graful

void init_graph_file(struct a_graph *graph){
    FILE *file_in;
    int iterator_rows;
    int aux,temp,muchii;

    file_in = fopen("datain.txt", "r");
    if (file_in == NULL){
        printf("\n File does not exist.");
        fclose(file_in);
        return;
    }
    fscanf(file_in, "%d", &graph->no_nodes);
    fscanf(file_in, "%d", &muchii);
    graph->init = 1;
    graph->adj_matrix = calloc(graph->no_nodes * graph->no_nodes, sizeof(int));


    for (iterator_rows = 0; iterator_rows < muchii; iterator_rows++ ){
            fscanf(file_in, "%d ", &aux);
            fscanf(file_in, "%d ", &temp);
            set_adj_matrix_value(graph, aux, temp, 1);
            set_adj_matrix_value(graph, temp, aux, 1);
        }

    fclose(file_in);
}



void push_begining_list(struct a_list_node *head, int new_element_value){       // Se insereaza un element la inceputul listei
    struct a_list_node *new_element;
    new_element = malloc(sizeof(struct a_list_node));
    new_element->info = new_element_value;
    new_element->next = head->next;
    head->next = new_element;

}

int pop_begining_list(struct a_list_node *head){    // Se elimina un element de la inceputul listei
    struct a_list_node *deleted_element;
    int aux;

    if (head->next != NULL) {
        deleted_element = head->next;
        aux = deleted_element->info;
        head->next = deleted_element->next;
        free(deleted_element);
        return aux;
    }else{
        printf("\n The list is empty");
        return -1; //the list is empty
    }
}


int PozZero(int number)         // Se testeaza daca in vectorul declarat global exista numarul 0 si se returneaza pozitia unde s-a gasit acesta.
                                // Aceasta functie este necesara pentru gasirea componentelor conexe.
{
    int iterator;
    for(iterator=1;iterator<=number;iterator++)
        if(vector[iterator]==0)
            return iterator;
    return 0;
}


void graph_Dfs(struct a_graph *graph, int start_node){      // Se parcurge graful
    FILE *out_file= fopen ("dataout.txt", "a");
    int *visited;
    int column_index;
    int aux;
    int current_node;
    struct a_list_node *head_stack;
    head_stack = calloc(1, sizeof(struct a_list_node));     // Se aloca memorie pentru crearea unei stive
    head_stack->next = NULL;
    visited = calloc((graph->no_nodes), sizeof(int));      // Se aloca memorie pentru crearea unui vector care sa retina prin ce noduri s-a trecut
    push_begining_list(head_stack, start_node);            // Se insereaza in stiva nodul de la care se pleaca cand se parcurge
    visited[start_node] = 1;            // Start_node-ul a fost vizitat
    vector[start_node]=1;
    fprintf(out_file,"Componenta conexa este: ");
    while (head_stack->next != NULL){           // Se parcurge stiva
        current_node = pop_begining_list(head_stack);    // Se sterge primul element din stiva
        fprintf(out_file,"%d ", current_node);
        for(column_index = 0; column_index < graph->no_nodes; column_index++){
            aux = get_adj_matrix_value(graph, current_node, column_index);

            if ( (aux != 0) && ( (visited[column_index]) == 0 )){       // Se testeaza daca in matricea de adiacenta apare 1
                                                                        // si daca nodul respectiv nu a fost vizitat

                push_begining_list(head_stack, column_index);           // in acest caz, nodul respectiv se va pune in stiva
                visited[column_index] = 1;                              // Se marcheaza ca fiind vizitat
                vector[column_index]=1;             // Se va pune in vector pe pozitia valorii nodului numarul 1
            }
        }
    }
    fprintf(out_file,"\n");
    fclose(out_file);
    free(head_stack);
    free(visited);
}

