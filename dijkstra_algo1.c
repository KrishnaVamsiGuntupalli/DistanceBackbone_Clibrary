#include <igraph.h>
#include <stdlib.h>

int vector_tail_cmp(const void *path1, const void *path2) {
    const igraph_vector_t *vec1 = *(const igraph_vector_t**)path1;
    const igraph_vector_t *vec2 = *(const igraph_vector_t**)path2;
    size_t length1 = igraph_vector_size(vec1);
    size_t length2 = igraph_vector_size(vec2);
    int diff;

    while (length1 > 0 && length2 > 0) {
        length1--;
        length2--;
        diff = VECTOR(*vec1)[length1] - VECTOR(*vec2)[length2];
        if (diff != 0) {
            return diff;
        }
    }

    if (length1 == 0 && length2 == 0) {
        return 0;
    } else if (length1 == 0) {
        return -1;
    } else {
        return 1;
    }
}

void check_nrgeo(const igraph_t *graph, igraph_vs_t vs,
                 const igraph_vector_ptr_t *paths,
                 const igraph_vector_t *nrgeo) {
    long int i, n;
    igraph_vector_t nrgeo2, *path;
    igraph_vit_t vit;

    n = igraph_vcount(graph);
    igraph_vector_init(&nrgeo2, n);
    if (igraph_vector_size(nrgeo) != n) {
        printf("nrgeo vector length must be %ld, was %ld", n, igraph_vector_size(nrgeo));
        return;
    }

    n = igraph_vector_ptr_size(paths);
    for (i = 0; i < n; i++) {
        path = VECTOR(*paths)[i];
        if (path == 0) {
            printf("Null path found in result vector at index %ld\n", i);
            return;
        }
        if (igraph_vector_size(path) == 0) {
            printf("Empty path found in result vector at index %ld\n", i);
            return;
        }
        VECTOR(nrgeo2)[(long int)igraph_vector_tail(path)] += 1;
    }

    igraph_vit_create(graph, vs, &vit);
    for (IGRAPH_VIT_RESET(vit); !IGRAPH_VIT_END(vit); IGRAPH_VIT_NEXT(vit)) {
        long int node = IGRAPH_VIT_GET(vit);
        if (VECTOR(*nrgeo)[node] - VECTOR(nrgeo2)[node]) {
            printf("nrgeo[%ld] invalid, observed = %ld, expected = %ld\n",
                   node, (long int)VECTOR(*nrgeo)[node], (long int)VECTOR(nrgeo2)[node]);
        }
    }
    igraph_vit_destroy(&vit);

    igraph_vector_destroy(&nrgeo2);
}

int main() {

    igraph_t g;
    igraph_vector_ptr_t res;
    long int i;

    igraph_real_t weights[] = { 1, 2, 3, 4, 5, 1, 1, 1, 1, 1 };
    igraph_real_t weights2[] = { 0, 2, 1, 0, 5, 2, 1, 1, 0, 2, 2, 8, 1, 1, 3, 1, 1, 4, 2, 1 };
    igraph_real_t dim[] = { 4, 4 };

    igraph_vector_t weights_vec, dim_vec, nrgeo;
    igraph_vs_t vs;

    igraph_vector_init(&nrgeo, 0);


    igraph_ring(&g, 10, IGRAPH_UNDIRECTED, 0, 1);

    igraph_vector_ptr_init(&res, 5);
    igraph_vs_vector_small(&vs, 1, 3, 4, 5, 2, 1,  -1);

    igraph_get_all_shortest_paths_dijkstra(
                &g,
                 &res,  &nrgeo,
                 0,  vs,
                 NULL,  IGRAPH_OUT);
    check_nrgeo(&g, vs, &res, &nrgeo);

    for (i = 0; i < igraph_vector_ptr_size(&res); i++) {
        igraph_vector_print(VECTOR(res)[i]);
        igraph_vector_destroy(VECTOR(res)[i]);
        igraph_free(VECTOR(res)[i]);
        VECTOR(res)[i] = 0;
    }



    igraph_vector_view(&weights_vec, weights, sizeof(weights) / sizeof(igraph_real_t));
    igraph_get_all_shortest_paths_dijkstra(
                &g,
                 &res,  &nrgeo,
                 0,  vs,
                 &weights_vec,  IGRAPH_OUT);
    check_nrgeo(&g, vs, &res, &nrgeo);

    for (i = 0; i < igraph_vector_ptr_size(&res); i++) {
        igraph_vector_print(VECTOR(res)[i]);
        igraph_vector_destroy(VECTOR(res)[i]);
        igraph_free(VECTOR(res)[i]);
        VECTOR(res)[i] = 0;
    }

    igraph_destroy(&g);


    igraph_vector_view(&weights_vec, weights2, sizeof(weights2) / sizeof(igraph_real_t));
    igraph_get_all_shortest_paths_dijkstra(
                &g,
                 &res,  &nrgeo,
                 0,  vs,
                 &weights_vec,  IGRAPH_OUT);

    check_nrgeo(&g, vs, &res, &nrgeo);

    igraph_vector_ptr_sort(&res, vector_tail_cmp);

    for (i = 0; i < igraph_vector_ptr_size(&res); i++) {
        igraph_vector_print(VECTOR(res)[i]);
        igraph_vector_destroy(VECTOR(res)[i]);
        igraph_free(VECTOR(res)[i]);
        VECTOR(res)[i] = 0;
    }

    igraph_vs_destroy(&vs);
    igraph_destroy(&g);

    igraph_vector_view(&dim_vec, dim, sizeof(dim) / sizeof(igraph_real_t));
    igraph_lattice(&g, &dim_vec, 1, 0, 0, 0);
    igraph_vs_vector_small(&vs, 3, 12, 15, -1);
    igraph_vector_init(&weights_vec, 24);
    igraph_vector_fill(&weights_vec, 1);
    VECTOR(weights_vec)[2] = 100;
    VECTOR(weights_vec)[8] = 100;
    igraph_get_all_shortest_paths_dijkstra(
                &g,
                0,  &nrgeo,
                 0,  vs,
                &weights_vec, IGRAPH_OUT);
    igraph_vector_destroy(&weights_vec);
    igraph_vs_destroy(&vs);
    igraph_destroy(&g);

    printf("%ld ", (long int)VECTOR(nrgeo)[3]);
    printf("%ld ", (long int)VECTOR(nrgeo)[12]);
    printf("%ld\n", (long int)VECTOR(nrgeo)[15]);

    igraph_vector_ptr_destroy(&res);
    igraph_vector_destroy(&nrgeo);

    if (!IGRAPH_FINALLY_STACK_EMPTY) {
        return 1;
    }

    return 0;
