#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a node in the binary search tree
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the BST
struct Node* insertNode(struct Node* root, char data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// Function to perform in-order traversal
void inOrder(struct Node* root, FILE* file) {
    if (root != NULL) {
        inOrder(root->left, file);
        fprintf(file, "%c\n", root->data);
        inOrder(root->right, file);
    }
}

// Function to perform pre-order traversal
void preOrder(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%c\n", root->data);
        preOrder(root->left, file);
        preOrder(root->right, file);
    }
}

// Function to perform post-order traversal
void postOrder(struct Node* root, FILE* file) {
    if (root != NULL) {
        postOrder(root->left, file);
        postOrder(root->right, file);
        fprintf(file, "%c\n", root->data);
    }
}

// Function to deallocate the memory of the BST nodes
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Function to generate random characters within a range and store them in a file
void generateRandomCharsToFile(int n, char minValue, char maxValue, const char* filename) {
    // Seed the random number generator with the current time
    srand(time(NULL));

    FILE* file = fopen("input2.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        // Generate a random character within the range [minValue, maxValue]
        char randomChar = (rand() % (maxValue - minValue + 1)) + minValue;
        fprintf(file, "%c\n", randomChar);
    }

    fclose(file);
    printf("Random characters generated and stored in %s successfully.\n", filename);
}

int main() {
    int n;
    char minValue, maxValue;
    char filename[100];

    printf("Enter the number of random characters to generate: ");
    scanf("%d", &n);

    printf("Enter the minimum value: ");
    scanf(" %c", &minValue);

    printf("Enter the maximum value: ");
    scanf(" %c", &maxValue);


    // Generate random characters and store them in a file
    generateRandomCharsToFile(n, minValue, maxValue, "input2.txt");

    // Read characters from the input file
    FILE* inputFile = fopen("input2.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    char ch;
    struct Node* root = NULL;
    while (fscanf(inputFile, " %c", &ch) != EOF) {
        root = insertNode(root, ch);
    }

    fclose(inputFile);

    // Perform in-order traversal and generate output file
    FILE* inOrderFile = fopen("inOrder1.txt", "w");
    if (inOrderFile == NULL) {
        printf("Failed to create in-order output file.\n");
        return 1;
    }

    inOrder(root, inOrderFile);
    fclose(inOrderFile);

    // Perform pre-order traversal and generate output file
    FILE* preOrderFile = fopen("preOrder1.txt", "w");
    if (preOrderFile == NULL) {
        printf("Failed to create pre-order output file.\n");
        return 1;
    }

    preOrder(root, preOrderFile);
    fclose(preOrderFile);

    // Perform post-order traversal and generate output file
    FILE* postOrderFile = fopen("postOrder1.txt", "w");
    if (postOrderFile == NULL) {
        printf("Failed to create post-order output file.\n");
        return 1;
    }

    postOrder(root, postOrderFile);
    fclose(postOrderFile);

    // Free memory by deallocating the BST nodes
    freeTree(root);

    return 0;
}
