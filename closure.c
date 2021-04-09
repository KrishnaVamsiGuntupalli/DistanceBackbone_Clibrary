#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <igraph.h>

typedef struct {
    int vertex;
    int edge_weight;
} weight_t;

typedef struct {
    weight_t **weights
    int length;
    int size;
    int distance;
    char kind[20];
    char algorithm[20];
} point_t

typedef struct {
    point_t **points
    int v_length;
    int v_size;
} graph_t;

typedef struct {
    graph_t **elements;
    int matrix[][];
    int count;
} sparse_t;

void transitive_closure(point_t *p,int D[][]){
    int *D = (int*)malloc(no_of_vertices_size*sizeof(int));
    if (p->algorithm = "dense") {
        return transitive_closure_dense_numpy(D[][]);
    }
    if (p->algorithm = "dijkstra") {
        if (sparse_matrix(D[)[]){
                            sparse_dijkstra();
                            }
                            else {
                            numpy_dikstra();
                            }
                            }
    }
  

void transitive_closure_dense_numpy(point_t *p, int D[][]) {
    int i, j, sum;
    int c =0;
                            int min = 0;
    int D_row = sizeof(D) / sizeof(D[0]);
    int D_column = sizeof(D[0])/sizeof(D[0][0]);
    for (i = 0; i < D_row; i++) {
        for (j = 0; j < D_column; j++) {
                    if (i=j)
                            {
                            sum = sum + D[i][j]
                            }
                            }
                            }
                            if (sum == 0) {
                            printf("Diagonal has to be zero for matrix computation to be correct");
                            }
    for (i = 0; i < D_row; i++) {
        for (j = 0; j < D_column; j++) {
                            if (p->kind == "metric") {
                            int vec[] = D[i][] + D[][j]
                            int s = sizeof vec
                            for (c = 1; c < s; c++)
                                if (min > vec[c])
                                  temp = vec[c];
                            }
                            }
                            }
                            }
                        
void sparse_matrix(int D[][])
{
    count = 0;
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] == 0)
            {
                ++sparse_counter;
            }
        }
    }
    if (sparse_counter > ((m * n) / 2))
    {
                            return 1;
    }
    else
                            return 0;
}
