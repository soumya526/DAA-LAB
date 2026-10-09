#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char symbol;
    int freq;
    int minSymbol;
    struct Node *left, *right;
} Node;

Node *heap[MAX * 2];
int heapSize = 0;

char symbols[MAX];
int frequencies[MAX];
int lengths[MAX];
char codes[MAX][MAX];
int n;

/* Create a new Huffman node */
Node *createNode(char symbol, int freq,
                 Node *left, Node *right) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->symbol = symbol;
    node->freq = freq;
    node->left = left;
    node->right = right;

    if (left == NULL && right == NULL)
        node->minSymbol = (unsigned char)symbol;
    else
        node->minSymbol =
            left->minSymbol < right->minSymbol
            ? left->minSymbol : right->minSymbol;

    return node;
}

/* Compare nodes by frequency, then symbol order */
int smaller(Node *a, Node *b) {
    if (a->freq != b->freq)
        return a->freq < b->freq;

    return a->minSymbol < b->minSymbol;
}

/* Insert a node into the min-heap */
void insertHeap(Node *node) {
    int i = ++heapSize;

    while (i > 1 && smaller(node, heap[i / 2])) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = node;
}

/* Remove the node with the minimum frequency */
Node *removeMin() {
    Node *minNode = heap[1];
    Node *last = heap[heapSize--];

    int i = 1, child;

    while (2 * i <= heapSize) {
        child = 2 * i;

        if (child + 1 <= heapSize &&
            smaller(heap[child + 1], heap[child]))
            child++;

        if (smaller(last, heap[child]))
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return minNode;
}

/* Calculate the length of each symbol's Huffman code */
void calculateLengths(Node *root, int depth) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        int i;

        for (i = 0; i < n; i++) {
            if (symbols[i] == root->symbol) {
                lengths[i] = depth;
                break;
            }
        }

        return;
    }

    calculateLengths(root->left, depth + 1);
    calculateLengths(root->right, depth + 1);
}

/* Sort symbols by length, then by symbol */
void sortSymbols() {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (lengths[j] > lengths[j + 1] ||
                (lengths[j] == lengths[j + 1] &&
                 (unsigned char)symbols[j] >
                 (unsigned char)symbols[j + 1])) {

                int tempLen = lengths[j];
                lengths[j] = lengths[j + 1];
                lengths[j + 1] = tempLen;

                char tempSym = symbols[j];
                symbols[j] = symbols[j + 1];
                symbols[j + 1] = tempSym;
            }
        }
    }
}

/* Generate canonical Huffman codes */
void generateCanonicalCodes() {
    unsigned long long code = 0;
    int i, j;

    sortSymbols();

    for (i = 0; i < n; i++) {
        if (i > 0)
            code++;

        if (i > 0)
            code <<= (lengths[i] - lengths[i - 1]);

        for (j = 0; j < lengths[i]; j++) {
            codes[i][j] =
                (code & (1ULL << (lengths[i] - j - 1)))
                ? '1' : '0';
        }

        codes[i][lengths[i]] = '\0';
    }
}

int main() {
    Node *left, *right, *root;
    int i;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    if (n < 1 || n >= MAX) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter symbol and frequency: ");
        scanf(" %c %d", &symbols[i], &frequencies[i]);

        if (frequencies[i] <= 0) {
            printf("Frequency must be positive.\n");
            return 1;
        }

        insertHeap(createNode(symbols[i], frequencies[i],
                              NULL, NULL));
    }

    /* Build the Huffman tree */
    while (heapSize > 1) {
        left = removeMin();
        right = removeMin();

        root = createNode(
            '\0',
            left->freq + right->freq,
            left,
            right
        );

        insertHeap(root);
    }

    root = removeMin();

    calculateLengths(root, 0);

    /* A single symbol is conventionally assigned code 0 */
    if (n == 1)
        lengths[0] = 1;

    generateCanonicalCodes();

    printf("\nCanonical Huffman Codebook:\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    double weightedLength = 0;
    long long totalFrequency = 0;

    for (i = 0; i < n; i++) {
        printf("%c\t%d\t\t%d\t%s\n",
               symbols[i],
               frequencies[i],
               lengths[i],
               codes[i]);

        weightedLength +=
            (double)frequencies[i] * lengths[i];

        totalFrequency += frequencies[i];
    }

    printf("\nWeighted path length = %.0f\n",
           weightedLength);

    printf("Expected code length = %.4f bits/symbol\n",
           weightedLength / totalFrequency);

    return 0;
}