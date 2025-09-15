#include <stdio.h>
#include <stdlib.h>

// Structure for BST node
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

// Function to insert an element in BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// Function to search for an element in BST
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    
    if (key > root->data) {
        return search(root->right, key);
    }
    
    return search(root->left, key);
}

// Function to find minimum value node in BST
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete an element from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to display BST in inorder traversal
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Test function to demonstrate BST operations
int main() {
    struct Node* root = NULL;
    
    printf("=== BST Demo Program ===\n\n");
    
    // 1. Create BST by inserting elements
    printf("1. Creating BST with elements: 50, 30, 70, 20, 40, 60, 80\n");
    int elements[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(elements) / sizeof(elements[0]);
    
    for (int i = 0; i < n; i++) {
        root = insert(root, elements[i]);
        printf("   Inserted: %d\n", elements[i]);
    }
    
    printf("\n2. Displaying BST (Inorder - sorted): ");
    inorderTraversal(root);
    printf("\n\n");
    
    // 3. Search operations
    printf("3. Search Operations:\n");
    int searchKeys[] = {40, 25, 80, 100};
    int searchCount = sizeof(searchKeys) / sizeof(searchKeys[0]);
    
    for (int i = 0; i < searchCount; i++) {
        struct Node* result = search(root, searchKeys[i]);
        if (result != NULL) {
            printf("   Element %d: FOUND\n", searchKeys[i]);
        } else {
            printf("   Element %d: NOT FOUND\n", searchKeys[i]);
        }
    }
    
    // 4. Insert new element
    printf("\n4. Inserting new element: 25\n");
    root = insert(root, 25);
    printf("   BST after insertion: ");
    inorderTraversal(root);
    printf("\n\n");
    
    // 5. Delete operations
    printf("5. Delete Operations:\n");
    
    // Delete leaf node
    printf("   Deleting leaf node (25):\n");
    root = deleteNode(root, 25);
    printf("   BST after deletion: ");
    inorderTraversal(root);
    printf("\n");
    
    // Delete node with one child
    printf("   Deleting node with one child (20):\n");
    root = deleteNode(root, 20);
    printf("   BST after deletion: ");
    inorderTraversal(root);
    printf("\n");
    
    // Delete node with two children
    printf("   Deleting node with two children (30):\n");
    root = deleteNode(root, 30);
    printf("   BST after deletion: ");
    inorderTraversal(root);
    printf("\n");
    
    // Delete root node
    printf("   Deleting root node (50):\n");
    root = deleteNode(root, 50);
    printf("   BST after deletion: ");
    inorderTraversal(root);
    printf("\n\n");
    
    printf("=== Demo completed successfully! ===\n");
    
    return 0;
}
