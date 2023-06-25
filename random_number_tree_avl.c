#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a tree node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to get the height of a node
int getHeight(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to update the height of a node
void updateHeight(TreeNode* node) {
    if (node == NULL) {
        return;
    }
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Function to perform a right rotation
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to get the balance factor of a node
int getBalance(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a node into the AVL tree
TreeNode* insertNode(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    } else {
        // Duplicate keys not allowed
        return root;
    }

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && data < root->left->data) {
        // Left-Left case
        return rightRotate(root);
    }

    if (balance < -1 && data > root->right->data) {
        // Right-Right case
        return leftRotate(root);
    }

    if (balance > 1 && data > root->left->data) {
        // Left-Right case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && data < root->right->data) {
        // Right-Left case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for a node in the AVL tree
TreeNode* searchNode(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
}

// Function to delete a node from the AVL tree
TreeNode* deleteNode(TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL || root->right == NULL) {
            TreeNode* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            TreeNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL) {
        return root;
    }

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        // Left-Left case
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        // Left-Right case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        // Right-Right case
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        // Right-Left case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to print the tree structure with edges
void printTreeStructure(FILE* outputFile, TreeNode* root, int space) {
    if (root == NULL) {
        return;
    }

    int i;
    for (i = 0; i < space; i++) {
        fprintf(outputFile, " ");
    }
    fprintf(outputFile, "|_%d\n", root->data);

    printTreeStructure(outputFile, root->left, space + 4);
    printTreeStructure(outputFile, root->right, space + 4);
}

int main() {
    // Generate random numbers and store them in a file
    FILE* randomFile = fopen("random_numbers.txt", "w");
    if (randomFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int numCount = 10; // Number of random numbers to generate
    srand(time(NULL));
    for (int i = 0; i < numCount; i++) {
        int randomNumber = rand() % 100; // Generate random number between 0 and 99
        fprintf(randomFile, "%d\n", randomNumber);
    }
    fclose(randomFile);

    // Read numbers from the file and construct the AVL tree
    FILE* inputFile = fopen("random_numbers.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    TreeNode* root = NULL;
    int num;
    while (fscanf(inputFile, "%d", &num) != EOF) {
        root = insertNode(root, num);
    }
    fclose(inputFile);

    // Print the original AVL tree structure with edges
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(outputFile, "Original AVL Tree Structure:\n");
    printTreeStructure(outputFile, root, 0);

    // Perform AVL tree operations
    root = rightRotate(root);
    fprintf(outputFile, "\nAVL Tree Structure after Right Rotation:\n");
    printTreeStructure(outputFile, root, 0);

    root = leftRotate(root);
    fprintf(outputFile, "\nAVL Tree Structure after Left Rotation:\n");
    printTreeStructure(outputFile, root, 0);

    // User input for search and deletion
    int searchData;
    printf("Enter a number to search and delete: ");
    scanf("%d", &searchData);

    // Search the number in the tree
    TreeNode* searchResult = searchNode(root, searchData);
    if (searchResult == NULL) {
        printf("Number not found in the AVL tree!\n");
    } else {
        // Delete the number from the tree
        root = deleteNode(root, searchData);

        // Print the updated AVL tree structure with edges
        fprintf(outputFile, "\nUpdated AVL Tree Structure after deletion:\n");
        printTreeStructure(outputFile, root, 0);
    }

    fclose(outputFile);
    printf("Output has been written to the file 'output.txt'.\n");

    return 0;
}
