#include <stdio.h>

#define MAX 10005
#define MAXE 200005

int parent[MAX], sz[MAX], active[MAX];
long long weight[MAX], sum[MAX];
int head[MAX], to[MAXE], next[MAXE], edgeCount = 0;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void addEdge(int u, int v) {
    to[edgeCount] = v;
    next[edgeCount] = head[u];
    head[u] = edgeCount++;
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

long long getMax(int V) {
    long long best = 0;
    int found = 0;

    for (int i = 1; i <= V; i++) {
        if (active[i] && parent[i] == i) {
            if (!found || sum[i] > best) {
                best = sum[i];
                found = 1;
            }
        }
    }

    return found ? best : 0;
}

int main() {
    int V, E, u, v;
    int P[MAX];
    long long ans[MAX];

    scanf("%d%d", &V, &E);

    for (int i = 1; i <= V; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
        head[i] = -1;
    }

    for (int i = 0; i < E; i++) {
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    for (int i = 0; i < V; i++)
        scanf("%d", &P[i]);

    /* Restore vertices in reverse deletion order */
    for (int i = V - 1; i >= 0; i--) {
        ans[i] = getMax(V);

        int x = P[i];
        active[x] = 1;
        parent[x] = x;
        sz[x] = 1;
        sum[x] = weight[x];

        for (int e = head[x]; e != -1; e = next[e]) {
            int neighbor = to[e];

            if (active[neighbor])
                unite(x, neighbor);
        }
    }

    /* Print answers in original deletion order */
    for (int i = 0; i < V; i++)
        printf("%lld\n", ans[i]);

    return 0;
}