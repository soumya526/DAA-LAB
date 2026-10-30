#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000000000LL

// Structure for graph edges
struct Edge {
    int dest;
    int weight;
    struct Edge* next;
};

// Structure for deque
struct Node {
    int vertex;
    int parity;
    long long distance;
    struct Node* next;
};

// Adjacency list
struct Edge* adj[1005];

// Initialize graph
void initialize(int V) {
    for(int i = 1; i <= V; i++) {
        adj[i] = NULL;
    }
}

// Add directed edge
void addEdge(int u, int v, int w) {

    struct Edge* newNode =
        (struct Edge*)malloc(sizeof(struct Edge));

    newNode->dest = v;
    newNode->weight = w;
    newNode->next = adj[u];

    adj[u] = newNode;
}

// Push element at front of deque
void pushFront(struct Node** front, int v,
               int p, long long d) {

    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->vertex = v;
    newNode->parity = p;
    newNode->distance = d;

    newNode->next = *front;
    *front = newNode;
}

// Push element at back of deque
void pushBack(struct Node** front, struct Node** rear,
              int v, int p, long long d) {

    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->vertex = v;
    newNode->parity = p;
    newNode->distance = d;
    newNode->next = NULL;

    if(*rear == NULL) {
        *front = *rear = newNode;
    }
    else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
}

// Remove element from front
struct Node* popFront(struct Node** front,
                      struct Node** rear) {

    if(*front == NULL)
        return NULL;

    struct Node* temp = *front;

    *front = (*front)->next;

    if(*front == NULL)
        *rear = NULL;

    return temp;
}

// 0-1 BFS with parity states
void zeroOneBFS(int V, int S, long long C) {

    long long dist[1005][2];

    for(int i = 1; i <= V; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    struct Node* front = NULL;
    struct Node* rear = NULL;

    // Initially source has even parity
    dist[S][0] = 0;

    pushFront(&front, S, 0, 0);

    // Perform 0-1 BFS
    while(front != NULL) {

        struct Node* current = popFront(&front, &rear);

        int u = current->vertex;
        int parity = current->parity;

        long long d = current->distance;

        free(current);

        // Ignore outdated deque entries
        if(d != dist[u][parity])
            continue;

        // Traverse adjacent vertices
        struct Edge* temp = adj[u];

        while(temp != NULL) {

            int v = temp->dest;
            int w = temp->weight;

            // Update parity
            int newParity = parity ^ w;

            // Calculate new distance
            long long newDist = d + w;

            // Relaxation
            if(newDist < dist[v][newParity]) {

                dist[v][newParity] = newDist;

                if(w == 0) {

                    // Weight 0: Push front
                    pushFront(&front, v,
                              newParity, newDist);

                }
                else {

                    // Weight 1: Push back
                    pushBack(&front, &rear, v,
                             newParity, newDist);
                }
            }

            temp = temp->next;
        }
    }

    // Print final answers
    printf("\nMinimum Effective Costs:\n");

    for(int i = 1; i <= V; i++) {

        if(dist[i][0] == INF &&
           dist[i][1] == INF) {

            printf("Vertex %d: Unreachable\n", i);
        }
        else {

            long long evenCost = dist[i][0];
            long long oddCost = INF;

            if(dist[i][1] != INF) {
                oddCost = dist[i][1] + C;
            }

            long long ans = (evenCost < oddCost) ?
                             evenCost : oddCost;

            printf("Vertex %d: %lld\n", i, ans);
        }
    }
}

// Main function
int main() {

    int V, E, S;
    long long C;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    printf("Enter source vertex: ");
    scanf("%d", &S);

    printf("Enter penalty cost C: ");
    scanf("%lld", &C);

    initialize(V);

    printf("Enter directed edges (u v w):\n");

    for(int i = 0; i < E; i++) {

        int u, v, w;

        scanf("%d %d %d", &u, &v, &w);

        if(u < 1 || u > V || v < 1 || v > V ||
           (w != 0 && w != 1)) {

            printf("Invalid edge input!\n");
            return 1;
        }

        addEdge(u, v, w);
    }

    zeroOneBFS(V, S, C);

    return 0;
}