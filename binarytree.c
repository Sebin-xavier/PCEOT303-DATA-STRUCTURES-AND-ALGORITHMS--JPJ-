#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct BST {
    Node* root;
} BST;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
BST* createBST() {
    BST* tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

Node* createTree() {
    int data;
    printf("Enter data (-1 for no node): ");
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    Node* newNode = createNode(data);

    printf("Enter left child for %d:\n", data);
    newNode->left = createTree();

    printf("Enter right child for %d:\n", data);
    newNode->right = createTree();

    return newNode;
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

void findAndPrintLeft(Node* root, int data) {
    if (root == NULL) {
        return;
    }

    // Check if the current node is the one we're looking for
    if (root->data == data) {
        if (root->left != NULL) {
            printf("Left child of %d is: %d\n", data, root->left->data);
        } else {
            printf("Node %d found, but it has no left child.\n", data);
        }
        // We found the node, no need to search further in this branch
        return;
    }

    // Recur on the left and right subtrees
    findAndPrintLeft(root->left, data);
    findAndPrintLeft(root->right, data);
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return NULL;
    }

    // If the data is found, set it to -1
    if (root->data == data) {
        root->data = -1;
    }

    // Recur for left and right subtrees to find all occurrences
    deleteNode(root->left, data);
    deleteNode(root->right, data);

    return root;
}

int main() {
    BST* tree = createBST();
    int choice, element;

    do {
        printf("\n--- Binary Tree Menu ---\n");
        printf("1. Create Tree\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Delete an Element\n");
        printf("6. Find Left Child of an Element\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Create the binary tree:\n");
                tree->root = createTree();
                break;
            case 2:
                if (tree->root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Inorder Traversal: ");
                    inorderTraversal(tree->root);
                    printf("\n");
                }
                break;
            case 3:
                if (tree->root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Preorder Traversal: ");
                    preorderTraversal(tree->root);
                    printf("\n");
                }
                break;
            case 4:
                if (tree->root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Postorder Traversal: ");
                    postorderTraversal(tree->root);
                    printf("\n");
                }
                break;
            case 5:
                if (tree->root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Enter the element to delete: ");
                    scanf("%d", &element);
                    tree->root = deleteNode(tree->root, element);
                    printf("Element %d marked as deleted (set to -1).\n", element);
                }
                break;
            case 6:
                if (tree->root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Enter an element to find its left child: ");
                    scanf("%d", &element);
                    findAndPrintLeft(tree->root, element);
                }
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    // Free allocated memory for the tree structure itself if needed,
    // though a full tree traversal would be needed to free all nodes.
    free(tree);

    return 0;
}

