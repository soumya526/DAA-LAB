#include <stdio.h>

#define MAX 10000

int parent[MAX], sz[MAX];
int grid[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (sz[a] < sz[b]) {
        int t = a;
        a = b;
        b = t;
    }

    parent[b] = a;
    sz[a] += sz[b];
    return 1;
}

int main() {
    int R, C, k, r, c, count = 0;

    printf("Enter rows, columns and operations: ");
    scanf("%d%d%d", &R, &C, &k);

    if (R * C > MAX) {
        printf("Grid too large\n");
        return 0;
    }

    for (int i = 0; i < R * C; i++) {
        parent[i] = i;
        sz[i] = 1;
        grid[i] = 0;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < k; i++) {
        scanf("%d%d", &r, &c);  /* 0-based coordinates */

        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid position\n");
            continue;
        }

        int id = r * C + c;

        if (!grid[id]) {
            grid[id] = 1;
            count++;

            for (int j = 0; j < 4; j++) {
                int nr = r + dr[j];
                int nc = c + dc[j];

                if (nr >= 0 && nr < R &&
                    nc >= 0 && nc < C) {
                    int nid = nr * C + nc;

                    if (grid[nid])
                        count -= unite(id, nid);
                }
            }
        }

        printf("%d ", count);
    }

    printf("\n");
    return 0;
}