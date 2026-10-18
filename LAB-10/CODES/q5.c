#include <stdio.h>
#include <stdlib.h>

#define MAX 10005

int parent[MAX], sz[MAX];

typedef struct {
    int root;
    int index;
    int value;
} Item;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
        return;

    if (sz[u] < sz[v]) {
        int t = u;
        u = v;
        v = t;
    }

    parent[v] = u;
    sz[u] += sz[v];
}

int cmpPosition(const void *a, const void *b) {
    const Item *x = a;
    const Item *y = b;

    if (x->root != y->root)
        return x->root - y->root;

    return x->index - y->index;
}

int cmpValue(const void *a, const void *b) {
    const Item *x = a;
    const Item *y = b;

    if (x->root != y->root)
        return x->root - y->root;

    if (x->value < y->value) return -1;
    if (x->value > y->value) return 1;
    return 0;
}

int main() {
    int n, m;
    int A[MAX];
    Item pos[MAX], vals[MAX];
    int answer[MAX];

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        unite(u, v);
    }

    for (int i = 1; i <= n; i++) {
        int r = find(i);

        pos[i - 1].root = r;
        pos[i - 1].index = i;

        vals[i - 1].root = r;
        vals[i - 1].value = A[i];
    }

    qsort(pos, n, sizeof(Item), cmpPosition);
    qsort(vals, n, sizeof(Item), cmpValue);

    for (int i = 0; i < n; i++)
        answer[pos[i].index] = vals[i].value;

    printf("Smallest permutation:\n");

    for (int i = 1; i <= n; i++)
        printf("%d ", answer[i]);

    printf("\n");
    return 0;
}