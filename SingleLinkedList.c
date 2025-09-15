#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Single Linked List structure with head and size
typedef struct Single_LinkedList {
    Node* head;
    int size;
} Single_LinkedList;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the linked list
void initList(Single_LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// Function to insert node at the end
void insertAtEnd(Single_LinkedList* list, int data) {
    Node* newNode = createNode(data);
    
    if (list->head == NULL) {
        list->head = newNode;
        list->size++;
        return;
    }
    
    Node* temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    list->size++;
}

// Function to display the linked list
void displayList(Single_LinkedList* list, const char* message) {
    printf("%s (Size: %d): ", message, list->size);
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

// Function to reverse the linked list
void reverseList(Single_LinkedList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    
    while (current != NULL) {
        // Store the next node
        next = current->next;
        
        // Reverse the link
        current->next = prev;
        
        // Move pointers forward
        prev = current;
        current = next;
    }
    
    // prev becomes the new head
    list->head = prev;
}

// Function to get the length of the list
int getLength(Single_LinkedList* list) {
    return list->size;
}

// Function to free the linked list
void freeList(Single_LinkedList* list) {
    Node* temp;
    while (list->head != NULL) {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    list->size = 0;
}

// Menu-driven input function
void inputList(Single_LinkedList* list) {
    int n, data;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &data);
        insertAtEnd(list, data);
    }
}

int main() {
    Single_LinkedList list;
    int choice;
    
    // Initialize the list
    initList(&list);
    
    printf("=== Linked List Reversal Program ===\n\n");
    
    do {
        printf("\nMenu:\n");
        printf("1. Create/Input linked list\n");
        printf("2. Display current list\n");
        printf("3. Reverse the list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                // Free existing list if any
                freeList(&list);
                initList(&list);
                inputList(&list);
                printf("\nLinked list created successfully!\n");
                displayList(&list, "Current list");
                break;
                
            case 2:
                printf("\n");
                displayList(&list, "Current list");
                printf("Length: %d\n", getLength(&list));
                break;
                
            case 3:
                if (list.head == NULL) {
                    printf("List is empty! Please create a list first.\n");
                    break;
                }
                
                printf("\n=== Reversing Linked List ===\n");
                displayList(&list, "Original list");
                
                reverseList(&list);
                
                displayList(&list, "Reversed list");
                printf("List has been successfully reversed!\n");
                break;
                
            case 4:
                printf("Exiting program...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
    } while (choice != 4);
    
    // Free memory before exit
    freeList(&list);
    
    return 0;
}
