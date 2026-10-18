#include <stdio.h>

#define MAX 10005

int parent[MAX], sz[MAX];
long long weight[MAX], sum[MAX];

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
    sum[u] += sum[v];
}

int main() {
    int V, E, K, u, v;

    scanf("%d%d%d", &V, &E, &K);

    for (int i = 1; i <= V; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
    }

    for (int e = 0; e < E; e++) {
        scanf("%d%d", &u, &v);
        unite(u, v);

        long long best = 0;
        int found = 0;

        for (int i = 1; i <= V; i++) {
            if (parent[i] == i && sz[i] <= K) {
                if (!found || sum[i] > best) {
                    best = sum[i];
                    found = 1;
                }
            }
        }

        if (found)
            printf("%lld\n", best);
        else
            printf("No valid component\n");
    }

    return 0;
}