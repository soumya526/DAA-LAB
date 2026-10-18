#include <stdio.h>
#include <stdlib.h>

int parent[1005], rankDSU[1005], parity[1005];

int find(int x) {
    if (parent[x] != x) {
        int p = parent[x];
        parent[x] = find(p);
        parity[x] ^= parity[p];
    }
    return parent[x];
}

/* Returns 1 if edge is accepted, 0 if rejected */
int addEdge(int u, int v) {
    int ru = find(u), rv = find(v);
    int pu = parity[u], pv = parity[v];

    if (ru == rv)
        return (pu != pv);

    if (rankDSU[ru] < rankDSU[rv]) {
        parent[ru] = rv;
        parity[ru] = pu ^ pv ^ 1;
    } else {
        parent[rv] = ru;
        parity[rv] = pu ^ pv ^ 1;

        if (rankDSU[ru] == rankDSU[rv])
            rankDSU[ru]++;
    }
    return 1;
}

int main() {
    int V, E, u, v;

    printf("Enter vertices and edges: ");
    scanf("%d%d", &V, &E);

    for (int i = 1; i <= V; i++)
        parent[i] = i;

    for (int i = 0; i < E; i++) {
        printf("Enter edge: ");
        scanf("%d%d", &u, &v);

        if (addEdge(u, v))
            printf("Edge (%d,%d) accepted\n", u, v);
        else
            printf("Edge (%d,%d) rejected\n", u, v);
    }

    return 0;
}