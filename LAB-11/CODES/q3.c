#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXL 11

char words[MAXN][MAXL];
int visitedA[MAXN], visitedB[MAXN];
int distA[MAXN], distB[MAXN];

int findWord(char word[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(words[i], word) == 0)
            return i;
    }
    return -1;
}

// Check whether two words differ by exactly one character
int isOneCharDifferent(char a[], char b[])
{
    int count = 0;

    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] != b[i])
            count++;

        if (count > 1)
            return 0;
    }

    return count == 1;
}

// Expand one level of BFS
int bfs(int queue[], int *front, int *rear,
        int visited[], int otherVisited[],
        int dist[], int otherDist[], int n)
{
    int levelSize = *rear - *front;

    for (int k = 0; k < levelSize; k++)
    {
        int u = queue[(*front)++];

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] &&
                isOneCharDifferent(words[u], words[v]))
            {
                visited[v] = 1;
                dist[v] = dist[u] + 1;

                if (otherVisited[v])
                {
                    return dist[v] + otherDist[v];
                }

                queue[(*rear)++] = v;
            }
        }
    }

    return -1;
}

int bidirectionalBFS(int n, int start, int target)
{
    if (start == target)
        return 0;

    int queueA[MAXN], queueB[MAXN];

    int frontA = 0, rearA = 0;
    int frontB = 0, rearB = 0;

    memset(visitedA, 0, sizeof(visitedA));
    memset(visitedB, 0, sizeof(visitedB));

    visitedA[start] = 1;
    visitedB[target] = 1;

    distA[start] = 0;
    distB[target] = 0;

    queueA[rearA++] = start;
    queueB[rearB++] = target;

    while (frontA < rearA && frontB < rearB)
    {
        int ans;

        // Expand the smaller search frontier
        if (rearA - frontA <= rearB - frontB)
        {
            ans = bfs(queueA, &frontA, &rearA,
                      visitedA, visitedB,
                      distA, distB, n);
        }
        else
        {
            ans = bfs(queueB, &frontB, &rearB,
                      visitedB, visitedA,
                      distB, distA, n);
        }

        if (ans != -1)
            return ans;
    }

    return -1;
}

int main()
{
    int n;

    printf("Enter number of dictionary words: ");
    scanf("%d", &n);

    printf("Enter dictionary words:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%10s", words[i]);
    }

    char A[MAXL], B[MAXL];

    printf("Enter starting word: ");
    scanf("%10s", A);

    printf("Enter target word: ");
    scanf("%10s", B);

    // Target must exist in dictionary
    int target = findWord(B, n);

    if (target == -1)
    {
        printf("Transformation not possible: -1\n");
        return 0;
    }

    // Find starting word
    int start = findWord(A, n);

    // If A is not in dictionary, temporarily add it
    if (start == -1)
    {
        start = n;
        strcpy(words[n], A);
        n++;
    }

    if (strlen(A) != strlen(B))
    {
        printf("Invalid input: word lengths must be equal.\n");
        return 0;
    }

    int result = bidirectionalBFS(n, start, target);

    printf("Minimum mutations: %d\n", result);

    return 0;
}
