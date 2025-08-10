#include "linkedList.c"
#include <stdio.h>
#include <stdlib.h>

// Function to display the menu
void displayMenu() {
    printf("\n--- Doubly Linked List Menu ---\n");
    printf("1.  Add node at the beginning\n");
    printf("2.  Add node at the end\n");
    printf("3.  Insert node at a specific position\n");
    printf("4.  Delete the first node\n");
    printf("5.  Delete the last node\n");
    printf("6.  Delete node at a specific position\n");
    printf("7.  Print the linked list\n");
    printf("8.  Get the node count\n");
    printf("9.  Delete the entire linked list\n");
    printf("0.  Exit\n");
    printf("---------------------------------\n");
    printf("Enter your choice: ");
}

// Helper function to get integer input safely and clear the input buffer
int getIntegerInput() {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Please enter an integer: ");
        // Clear the input buffer
        while (getchar() != '\n');
    }
    // Clear the rest of the line in case of extra characters like "123xyz"
    while (getchar() != '\n');
    return value;
}

int main() {
    LinkedList* list = createLinkedList();
    if (list == NULL) {
        fprintf(stderr, "FATAL: Could not create linked list. Exiting.\n");
        return 1;
    }

    int choice, data, position;
    Node* newNode = NULL;
    Node* deletedNode = NULL;

    while (1) {
        displayMenu();
        choice = getIntegerInput();

        switch (choice) {
            case 1: // Add at beginning
                printf("Enter data for the new node: ");
                data = getIntegerInput();
                newNode = createNode(data);
                if (newNode) {
                    addNodeAtBeginning(list, newNode);
                    printf("Node with data %d added to the beginning.\n", data);
                } else {
                    printf("Failed to create node.\n");
                }
                break;

            case 2: // Add at end
                printf("Enter data for the new node: ");
                data = getIntegerInput();
                newNode = createNode(data);
                if (newNode) {
                    addNodeAtEnd(list, newNode);
                    printf("Node with data %d added to the end.\n", data);
                } else {
                    printf("Failed to create node.\n");
                }
                break;

            case 3: // Insert at position
                printf("Enter data for the new node: ");
                data = getIntegerInput();
                printf("Enter position to insert at (0-based): ");
                position = getIntegerInput();
                newNode = createNode(data);
                if (newNode) {
                    insertNodeAtPosition(list, newNode, position);
                } else {
                    printf("Failed to create node.\n");
                }
                break;

            case 4: // Delete first
                deletedNode = deleteFirstNode(list);
                if (deletedNode) {
                    printf("Deleted first node with data: %d\n", deletedNode->data);
                    free(deletedNode); // IMPORTANT: Free the memory
                }
                break;

            case 5: // Delete last
                deletedNode = deleteLastNode(list);
                if (deletedNode) {
                    printf("Deleted last node with data: %d\n", deletedNode->data);
                    free(deletedNode); // IMPORTANT: Free the memory
                }
                break;

            case 6: // Delete at position
                printf("Enter position to delete (0-based): ");
                position = getIntegerInput();
                deletedNode = deleteNodeAtPosition(list, position);
                if (deletedNode) {
                    printf("Deleted node at position %d with data: %d\n", position, deletedNode->data);
                    free(deletedNode); // IMPORTANT: Free the memory
                }
                break;

            case 7: // Print list
                printLinkedList(list);
                break;

            case 8: // Get count
                printf("The list has %d nodes.\n", countNodes(list));
                break;

            case 9: // Delete entire list
                printf("Deleting the entire linked list...\n");
                deleteLinkedList(list);
                printf("List deleted. A new empty list has been created.\n");
                // Re-initialize the list pointer to avoid using freed memory
                list = createLinkedList();
                if (list == NULL) {
                    fprintf(stderr, "FATAL: Could not re-create linked list. Exiting.\n");
                    return 1;
                }
                break;

            case 0: // Exit
                printf("Exiting program. Freeing all memory...\n");
                deleteLinkedList(list);
                printf("Cleanup complete. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0; // Should not be reached
}
