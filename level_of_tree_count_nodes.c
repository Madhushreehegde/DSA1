#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to perform level-order traversal and count nodes in each level
void levelOrderTraversal(struct Node* root, FILE* outputFile) {
    if (root == NULL)
        return;

    struct Node* queue[100];
    int front = 0, rear = 0;
    int level = 0, count = 0;

    queue[rear++] = root;

    while (front < rear) {
        int nodesInCurrentLevel = rear - front;
        count = 0;

        fprintf(outputFile, "Level %d: ", level);

        while (nodesInCurrentLevel > 0) {
            struct Node* current = queue[front++];
            fprintf(outputFile, "%d ", current->data);
            count++;

            if (current->left != NULL)
                queue[rear++] = current->left;

            if (current->right != NULL)
                queue[rear++] = current->right;

            nodesInCurrentLevel--;
        }

        fprintf(outputFile, "(%d nodes)\n", count);
        level++;
    }
}

// Function to display the binary tree structure in a file
void displayTreeStructure(struct Node* root, int level, FILE* outputFile) {
    if (root == NULL)
        return;

    displayTreeStructure(root->right, level + 1, outputFile);

    for (int i = 0; i < level; i++)
        fprintf(outputFile, "    ");

    fprintf(outputFile, "%d\n", root->data);

    displayTreeStructure(root->left, level + 1, outputFile);
}

int main() {
    // Creating a sample binary tree with random numbers
    struct Node* root = createNode(rand() % 100);

    int numNodes;
    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &numNodes);

    printf("Generating random numbers for tree elements...\n");

    // Inserting random numbers into the tree
    for (int i = 1; i < numNodes; i++) {
        int data = rand() % 100;
        struct Node* current = root;
        struct Node* parent;

        while (current != NULL) {
            parent = current;
            if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        if (data < parent->data)
            parent->left = createNode(data);
        else
            parent->right = createNode(data);
    }

    FILE* outputFile = fopen("tree_structure.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening the output file!");
        exit(1);
    }

    printf("Level-order traversal:\n");
    levelOrderTraversal(root, outputFile);

    printf("Tree Structure is saved in the file 'tree_structure.txt'\n");

    fprintf(outputFile, "Tree Structure:\n");
    displayTreeStructure(root, 0, outputFile);

    fclose(outputFile);

    return 0;
}
