#include <stdio.h>
#include <stdlib.h>

#define MAX 1005

// Structure for adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Adjacency list
struct Node* adj[MAX];

// Initialize graph
void initialize(int V) {
    for(int i = 1; i <= V; i++) {
        adj[i] = NULL;
    }
}

// Add undirected edge
void addEdge(int u, int v) {

    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->vertex = u;
    newNode->next = adj[v];
    adj[v] = newNode;
}

// Multi-Source BFS
void multiSourceBFS(int V, int K, int hubs[],
                    int R, int owner[], int dist[]) {

    int queue[MAX * 2];

    int front = 0, rear = 0;

    // Initialize arrays
    for(int i = 1; i <= V; i++) {
        owner[i] = -1;
        dist[i] = -1;
    }

    // Step 1: Insert all hubs in increasing index order
    for(int i = 1; i <= K; i++) {

        int h = hubs[i];

        owner[h] = i;
        dist[h] = 0;

        queue[rear++] = h;
    }

    // Step 2: Perform Multi-Source BFS
    while(front < rear) {

        int u = queue[front++];

        struct Node* temp = adj[u];

        while(temp != NULL) {

            int v = temp->vertex;

            // Visit only unassigned vertices
            if(owner[v] == -1) {

                owner[v] = owner[u];
                dist[v] = dist[u] + 1;

                queue[rear++] = v;
            }

            temp = temp->next;
        }
    }

    // Step 3: Apply radius constraint
    for(int i = 1; i <= V; i++) {

        if(dist[i] == -1 || dist[i] > R) {

            owner[i] = -1;
            dist[i] = -1;
        }
    }
}

// Main function
int main() {

    int V, E, K, R;

    int hubs[MAX];

    int owner[MAX];
    int dist[MAX];

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    initialize(V);

    printf("Enter undirected edges (u v):\n");

    for(int i = 0; i < E; i++) {

        int u, v;

        scanf("%d %d", &u, &v);

        if(u < 1 || u > V || v < 1 || v > V) {
            printf("Invalid edge!\n");
            return 1;
        }

        addEdge(u, v);
    }

    printf("Enter number of hubs: ");
    scanf("%d", &K);

    printf("Enter hub vertices in index order:\n");

    for(int i = 1; i <= K; i++) {

        scanf("%d", &hubs[i]);

        if(hubs[i] < 1 || hubs[i] > V) {
            printf("Invalid hub!\n");
            return 1;
        }
    }

    printf("Enter radius R: ");
    scanf("%d", &R);

    // Execute Multi-Source BFS
    multiSourceBFS(V, K, hubs, R, owner, dist);

    // Display results
    printf("\nVertex\tOwner\tDistance\n");

    for(int i = 1; i <= V; i++) {

        printf("%d\t%d\t%d\n",
               i, owner[i], dist[i]);
    }

    return 0;
}