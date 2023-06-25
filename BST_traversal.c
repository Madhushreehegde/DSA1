#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the BST
struct Node* insertNode(struct Node* root, int data) {
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
        fprintf(file, "%d\n", root->data);
        inOrder(root->right, file);
    }
}

// Function to perform pre-order traversal
void preOrder(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d\n", root->data);
        preOrder(root->left, file);
        preOrder(root->right, file);
    }
}

// Function to perform post-order traversal
void postOrder(struct Node* root, FILE* file) {
    if (root != NULL) {
        postOrder(root->left, file);
        postOrder(root->right, file);
        fprintf(file, "%d\n", root->data);
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

// Function to generate random numbers within a range and store them in a file
void generateRandomNumbersToFile(int n, int minValue, int maxValue, const char* filename) {
    // Seed the random number generator with the current time
    srand(time(NULL));

    FILE* file = fopen("INPUT.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        // Generate a random number within the range [minValue, maxValue]
        int randomNumber = (rand() % (maxValue - minValue + 1)) + minValue;
        fprintf(file, "%d\n", randomNumber);
    }

    fclose(file);
    printf("Random numbers generated and stored in %s successfully.\n", filename);
}

int main() {
    int n, minValue, maxValue;
    char filename[100];

    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &n);

    printf("Enter the minimum value: ");
    scanf("%d", &minValue);

    printf("Enter the maximum value: ");
    scanf("%d", &maxValue);



    // Generate random numbers and store them in a file
    generateRandomNumbersToFile(n, minValue, maxValue,"INPUT.txt");

    // Read numbers from the input file
    FILE* inputFile = fopen("INPUT.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    int num;
    struct Node* root = NULL;
    while (fscanf(inputFile, "%d", &num) != EOF) {
        root = insertNode(root, num);
    }

    fclose(inputFile);

    // Perform in-order traversal and generate output file
    FILE* inOrderFile = fopen("inOrder.txt", "w");
    if (inOrderFile == NULL) {
        printf("Failed to create in-order output file.\n");
        return 1;
    }

    inOrder(root, inOrderFile);
    fclose(inOrderFile);

    // Perform pre-order traversal and generate output file
    FILE* preOrderFile = fopen("preOrder.txt", "w");
    if (preOrderFile == NULL) {
        printf("Failed to create pre-order output file.\n");
        return 1;
    }

    preOrder(root, preOrderFile);
    fclose(preOrderFile);

    // Perform post-order traversal and generate output file
    FILE* postOrderFile = fopen("postOrder.txt", "w");
    if (postOrderFile == NULL) {
        printf("Failed to create post-order output file.\n");
        return 1;
    }

    postOrder(root, postOrderFile);
    fclose(postOrderFile);

    printf("created IN-order output file.\n");
    printf("created PRE-order output file.\n");
    printf("created POST-order output file.\n");

    // Free memory by deallocating the BST nodes
    freeTree(root);

    return 0;
}
