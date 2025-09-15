#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

// Helper function to get integer input safely
int getIntegerInput() {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Please enter an integer: ");
        // Clear the input buffer
        while (getchar() != '\n');
    }
    // Clear the rest of the line
    while (getchar() != '\n');
    return value;
}

// Function to swap data between two nodes
void swapNodeData(Node* a, Node* b) {
    if (a == NULL || b == NULL) {
        printf("Error: Cannot swap data of NULL nodes\n");
        return;
    }
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Bubble Sort implementation for double linked list
void bubbleSort(LinkedList* list) {
    if (list == NULL || list->head == NULL || list->size <= 1) {
        printf("List is empty or has only one element - no sorting needed.\n");
        return;
    }
    
    printf("Performing Bubble Sort...\n");
    printf("Original list: ");
    printLinkedList(list);
    
    int swapped;
    Node* ptr1;
    Node* lptr = NULL; // Last sorted position
    
    do {
        swapped = 0;
        ptr1 = list->head;
        
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                swapNodeData(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    
    printf("Sorted list:   ");
    printLinkedList(list);
    printf("Bubble sort completed successfully!\n");
}

// Selection Sort implementation for double linked list
void selectionSort(LinkedList* list) {
    if (list == NULL || list->head == NULL || list->size <= 1) {
        printf("List is empty or has only one element - no sorting needed.\n");
        return;
    }
    
    printf("Performing Selection Sort...\n");
    printf("Original list: ");
    printLinkedList(list);
    
    Node* temp = list->head;
    
    while (temp != NULL) {
        Node* min = temp;
        Node* r = temp->next;
        
        // Find minimum element in remaining unsorted list
        while (r != NULL) {
            if (min->data > r->data) {
                min = r;
            }
            r = r->next;
        }
        
        // Swap data if minimum is not the current element
        if (min != temp) {
            swapNodeData(temp, min);
        }
        
        temp = temp->next;
    }
    
    printf("Sorted list:   ");
    printLinkedList(list);
    printf("Selection sort completed successfully!\n");
}

// Insertion Sort implementation for double linked list
void insertionSort(LinkedList* list) {
    if (list == NULL || list->head == NULL || list->size <= 1) {
        printf("List is empty or has only one element - no sorting needed.\n");
        return;
    }
    
    printf("Performing Insertion Sort...\n");
    printf("Original list: ");
    printLinkedList(list);
    
    Node* current = list->head->next; // Start from second node
    
    while (current != NULL) {
        Node* next = current->next; // Store next node before modification
        int key = current->data;
        Node* pos = current->prev;
        
        // Find the correct position to insert current node's data
        while (pos != NULL && pos->data > key) {
            pos->next->data = pos->data; // Move data forward
            pos = pos->prev;
        }
        
        // Insert the key at the correct position
        if (pos == NULL) {
            list->head->data = key;
        } else {
            pos->next->data = key;
        }
        
        current = next;
    }
    
    printf("Sorted list:   ");
    printLinkedList(list);
    printf("Insertion sort completed successfully!\n");
}

// Function to display sorting menu
void displaySortingMenu() {
    printf("\n=== Double Linked List Sorting Menu ===\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Display current list\n");
    printf("5. Return to main menu\n");
    printf("=========================================\n");
    printf("Enter your choice: ");
}

// Function to handle sorting operations
void performSorting(LinkedList* list) {
    if (list == NULL) {
        printf("Error: List is NULL\n");
        return;
    }
    
    int choice;
    
    while (1) {
        displaySortingMenu();
        choice = getIntegerInput();
        
        switch (choice) {
            case 1:
                bubbleSort(list);
                break;
                
            case 2:
                selectionSort(list);
                break;
                
            case 3:
                insertionSort(list);
                break;
                
            case 4:
                printf("Current list: ");
                printLinkedList(list);
                printf("List size: %d\n", countNodes(list));
                break;
                
            case 5:
                printf("Returning to main menu...\n");
                return;
                
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
                break;
        }
    }
}

// Function to create a sample list for testing
void createSampleList(LinkedList* list) {
    printf("Creating sample list with values: 64, 34, 25, 12, 22, 11, 90\n");
    
    int values[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < size; i++) {
        Node* newNode = createNode(values[i]);
        addNodeAtEnd(list, newNode);
    }
    
    printf("Sample list created: ");
    printLinkedList(list);
}

// Function to input custom list from user
void inputCustomList(LinkedList* list) {
    int n, data;
    printf("Enter number of elements: ");
    n = getIntegerInput();
    
    if (n <= 0) {
        printf("Invalid number of elements!\n");
        return;
    }
    
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        data = getIntegerInput();
        Node* newNode = createNode(data);
        addNodeAtEnd(list, newNode);
    }
    
    printf("Custom list created: ");
    printLinkedList(list);
}

// Function to clear the list
void clearList(LinkedList* list) {
    while (list->head != NULL) {
        Node* deleted = deleteFirstNode(list);
        if (deleted) {
            free(deleted);
        }
    }
    printf("List cleared successfully!\n");
}

// Main menu display
void displayMainMenu() {
    printf("\n=== Double Linked List Sorting Program ===\n");
    printf("1. Create sample list (64, 34, 25, 12, 22, 11, 90)\n");
    printf("2. Create custom list\n");
    printf("3. Display current list\n");
    printf("4. Sort list (opens sorting menu)\n");
    printf("5. Add single element\n");
    printf("6. Clear list\n");
    printf("7. Exit\n");
    printf("==========================================\n");
    printf("Enter your choice: ");
}

int main() {
    LinkedList* list = createLinkedList();
    if (list == NULL) {
        fprintf(stderr, "FATAL: Could not create linked list. Exiting.\n");
        return 1;
    }
    
    int choice, data;
    
    printf("Welcome to Double Linked List Sorting Program!\n");
    printf("This program demonstrates various sorting algorithms on a double linked list.\n");
    
    while (1) {
        displayMainMenu();
        choice = getIntegerInput();
        
        switch (choice) {
            case 1:
                // Clear existing list first
                clearList(list);
                createSampleList(list);
                break;
                
            case 2:
                // Clear existing list first
                clearList(list);
                inputCustomList(list);
                break;
                
            case 3:
                if (list->head == NULL) {
                    printf("List is empty!\n");
                } else {
                    printf("Current list: ");
                    printLinkedList(list);
                    printf("List size: %d\n", countNodes(list));
                }
                break;
                
            case 4:
                if (list->head == NULL) {
                    printf("List is empty! Please create a list first.\n");
                } else {
                    performSorting(list);
                }
                break;
                
            case 5:
                printf("Enter element to add: ");
                data = getIntegerInput();
                Node* newNode = createNode(data);
                addNodeAtEnd(list, newNode);
                printf("Element %d added to the list.\n", data);
                printf("Updated list: ");
                printLinkedList(list);
                break;
                
            case 6:
                clearList(list);
                break;
                
            case 7:
                printf("Exiting program. Cleaning up memory...\n");
                deleteLinkedList(list);
                printf("Cleanup complete. Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please enter a number between 1 and 7.\n");
                break;
        }
    }
    
    return 0;
}
