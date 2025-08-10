/*Programs to be done  on 8-8-25 and 11-8-25

1. Create  a node of a single linked list.
2. Write function to add a node at the end of the list with a TC of O(1).
3. Write function to insert a node at the begining of the list with a TC of O(1).
4. Write function to insert a node at a particular position.
5. Write function to delete the first node.
6. Write function to delete the last node with one pointer.
7. Write function to delete a node at a particular position.
8. Write function to delete the whole linked list.
9. Write function to print the data in the linked list.
10. Write function to traverse the linked list and count the no of elements (data) in the linked list.*/



#include<stdlib.h>
#include<stdio.h>

/** Creates Doubly Linked List Node 
 * int data
 * next pointer to next node
 * prev pointer to previous node
*/

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

/** Creates Doubly Linked List 
 * `head` pointer to the first node
 * `tail` pointer to the last node
 * `size` to keep track of the number of nodes
*/
typedef struct LinkedList {
    struct Node* head;
    struct Node* tail;
    int size;
} LinkedList;

/**
 * @brief Creates and initializes a new empty linked list.
 * 
 * This function allocates memory for a new LinkedList structure.
 * It initializes the head and tail pointers to NULL and the size to 0.
 * If memory allocation fails, it prints an error message and exits the program.
 * 
 * @return A pointer to the newly created LinkedList. The caller is responsible
 *         for freeing this memory later (e.g., by calling a freeLinkedList function).
 * @note Time Complexity: O(1)
 */
LinkedList* createLinkedList(){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * @brief Creates a new node for a doubly linked list.
 * 
 * This function allocates memory for a new Node and initializes it
 * with the provided data. The `next` and `prev` pointers are set to NULL.
 * If memory allocation fails, it prints an error message and exits the program.
 * 
 * @param data The integer value to be stored in the new node.
 * @return A pointer to the newly created Node.
 * @note Time Complexity: O(1)
 */
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}


/**
 * @brief Adds a new node at the end of the linked list.
 * 
 * This function takes a pointer to the linked list and a new node,
 * and adds the new node at the end of the list. If the list is empty,
 * it sets both head and tail to the new node. Otherwise, it adjusts
 * pointers accordingly.
 * 
 * @param list Pointer to the linked list.
 * @param newNode Pointer to the new node to be added.
 * @note Time Complexity: O(1)
 */
void addNodeAtEnd(LinkedList* list, Node* newNode) {
    if (newNode == NULL) {
        printf("Error: newNode is NULL\n");
        return;
    }
    if (list->head == NULL) { // If the list is empty
        list->head = newNode;
        list->tail = newNode;
    } else { // If the list is not empty
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size++;
}
/**
 * @brief Inserts a new node at the beginning of the linked list.
 * 
 * This function creates a new node with the given data and inserts it
 * at the beginning of the linked list. If the list is empty, it sets both
 * head and tail to the new node. Otherwise, it adjusts pointers accordingly.
 * 
 * @param list Pointer to the linked list.
 * @param data The integer value to be stored in the new node.
 * @note Time Complexity: O(1)
 */
void addNodeAtBeginning(LinkedList* list, Node* newNode) {
    if (newNode == NULL) {
        printf("Error: newNode is NULL\n");
        return;
    }
    if (list->head == NULL) { // If the list is empty
        list->head = newNode;
        list->tail = newNode;
    } else { // If the list is not empty
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    list->size++;
}

/**
 * @brief Inserts a new node at a specific position in the linked list.
 * 
 * This function inserts a new node with the given data at the specified position
 * in the linked list. If the position is 0, it calls addNodeAtBeginning.
 * If the position is equal to the size of the list, it calls addNodeAtEnd.
 * Otherwise, it traverses to the specified position and inserts the new node.
 * 
 * @param list Pointer to the linked list.
 * @param data The integer value to be stored in the new node.
 * @param position The position at which to insert the new node (0-based index).
 * @note Time Complexity: O(n) in worst case, O(1) if inserting at head or tail.
 */
void insertNodeAtPosition(LinkedList* list, Node* newNode, int position) {
    if (newNode == NULL) {
        printf("Error: Cannot insert a NULL node.\n");
        printf("Error: newNode is NULL\n");
    }
    if (position < 0 || position > list->size) {
        printf("Error: Invalid position %d for list of size %d.\n", position, list->size);
        printf("Error: Invalid position\n");
    }

        if (list->head == NULL) { // List is empty
        addNodeAtBeginning(list, newNode);
    } else if (position == list->size) {
        addNodeAtEnd(list, newNode);
    } else {
        Node* current = list->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
    } 
        newNode->next = current->next;
        newNode->prev = current; 
        current->next->prev = newNode;
        current->next = newNode;
        list->size++;
    }
}

/**
 * @brief Deletes the first node from the linked list.
 * @param list Pointer to the linked list.
 * @return Pointer to the deleted node, or NULL if the list is empty.
 */
Node* deleteFirstNode(LinkedList* list) {
    if (list->head == NULL) {
        printf("Error: List is empty, cannot delete first node.\n");
        return NULL;
    }
    Node* temp = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else { // If the list becomes empty
        list->tail = NULL;
    }
    list->size--;
    return temp; // Return the deleted node
}

Node* deleteLastNode(LinkedList* list) {
    if (list->tail == NULL) {
        printf("Error: List is empty, cannot delete last node.\n");
        return NULL;
    }
    Node* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else { // If the list becomes empty
        list->head = NULL;
    }
    list->size--;
    return temp; // Return the deleted node
}

Node* deleteNodeAtPosition(LinkedList* list, int position) {
    if (position < 0 || position >= list->size) {
        printf("Error: Invalid position %d for list of size %d.\n", position, list->size);
        return NULL;
    }
    if (position == 0) {
        return deleteFirstNode(list);
    }
    if (position == list->size - 1) {
        return deleteLastNode(list);
    }
    Node* current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    list->size--;
    return current;
}

void deleteLinkedList(LinkedList* list){
    Node* current = list->head;
    while (current != NULL) {
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(list);
}

void printLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d <->", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int countNodes(LinkedList* list) {
    return list->size;
}

int traverse(LinkedList* list){
    Node* current = list->head;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

