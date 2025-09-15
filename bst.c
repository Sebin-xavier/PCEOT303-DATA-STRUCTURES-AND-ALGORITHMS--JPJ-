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
    // If tree is empty, create and return new node
    if (root == NULL) {
        return createNode(data);
    }
    
    // If data is less than root's data, insert in left subtree
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    // If data is greater than root's data, insert in right subtree
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // If data is equal to root's data, don't insert (no duplicates)
    
    return root;
}

// Function to search for an element in BST
struct Node* search(struct Node* root, int key) {
    // Base case: root is null or key is present at root
    if (root == NULL || root->data == key) {
        return root;
    }
    
    // Key is greater than root's key, search in right subtree
    if (key > root->data) {
        return search(root->right, key);
    }
    
    // Key is smaller than root's key, search in left subtree
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
    // Base case: tree is empty
    if (root == NULL) {
        return root;
    }
    
    // If key is smaller than root's key, delete from left subtree
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    // If key is greater than root's key, delete from right subtree
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    // If key is same as root's key, this is the node to be deleted
    else {
        // Node with only one child or no child
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
        
        // Node with two children: Get the inorder successor
        struct Node* temp = findMin(root->right);
        
        // Copy the inorder successor's data to this node
        root->data = temp->data;
        
        // Delete the inorder successor
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

// Function to display BST in preorder traversal
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to display BST in postorder traversal
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Function to display menu
void displayMenu() {
    printf("\n=== Binary Search Tree Operations ===\n");
    printf("1. Insert an element\n");
    printf("2. Delete an element\n");
    printf("3. Search for an element\n");
    printf("4. Display BST (Inorder)\n");
    printf("5. Display BST (Preorder)\n");
    printf("6. Display BST (Postorder)\n");
    printf("7. Create BST from multiple inputs\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

// Function to create BST from multiple inputs
struct Node* createBSTFromInput(struct Node* root) {
    int n, data;
    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);
    
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insert(root, data);
        printf("Inserted %d into BST\n", data);
    }
    
    return root;
}

int main() {
    struct Node* root = NULL;
    int choice, data;
    struct Node* searchResult;
    
    printf("Welcome to Binary Search Tree Program!\n");
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Element %d inserted successfully!\n", data);
                break;
                
            case 2:
                if (root == NULL) {
                    printf("BST is empty! Nothing to delete.\n");
                } else {
                    printf("Enter element to delete: ");
                    scanf("%d", &data);
                    struct Node* temp = search(root, data);
                    if (temp == NULL) {
                        printf("Element %d not found in BST!\n", data);
                    } else {
                        root = deleteNode(root, data);
                        printf("Element %d deleted successfully!\n", data);
                    }
                }
                break;
                
            case 3:
                if (root == NULL) {
                    printf("BST is empty!\n");
                } else {
                    printf("Enter element to search: ");
                    scanf("%d", &data);
                    searchResult = search(root, data);
                    if (searchResult != NULL) {
                        printf("Element %d found in BST!\n", data);
                    } else {
                        printf("Element %d not found in BST!\n", data);
                    }
                }
                break;
                
            case 4:
                if (root == NULL) {
                    printf("BST is empty!\n");
                } else {
                    printf("Inorder traversal (sorted order): ");
                    inorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 5:
                if (root == NULL) {
                    printf("BST is empty!\n");
                } else {
                    printf("Preorder traversal: ");
                    preorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 6:
                if (root == NULL) {
                    printf("BST is empty!\n");
                } else {
                    printf("Postorder traversal: ");
                    postorderTraversal(root);
                    printf("\n");
                }
                break;
                
            case 7:
                root = createBSTFromInput(root);
                printf("BST created successfully!\n");
                break;
                
            case 8:
                printf("Thank you for using BST program!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
