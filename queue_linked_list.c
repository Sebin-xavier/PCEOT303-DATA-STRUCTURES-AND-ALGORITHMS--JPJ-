#include <stdio.h>
#include <stdlib.h>

// Node structure for queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure with front, rear and size
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Initialize queue
void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// Check if queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Enqueue element to queue
void enqueue(Queue* queue, int data) {
    Node* newNode = createNode(data);
    
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
    printf("Enqueued %d to queue\n", data);
}

// Dequeue element from queue
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    
    // If queue becomes empty
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    queue->size--;
    printf("Dequeued %d from queue\n", data);
    return data;
}

// Peek at front element
int peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue->front->data;
}

// Display queue
void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("Queue (Size: %d): FRONT -> ", queue->size);
    Node* temp = queue->front;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" <- REAR\n");
}

// Free queue memory
void freeQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
}

int main() {
    Queue queue;
    initQueue(&queue);
    int choice, data;
    
    printf("=== Queue using Linked List ===\n");
    
    do {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter element to enqueue: ");
                scanf("%d", &data);
                enqueue(&queue, data);
                break;
            case 2:
                dequeue(&queue);
                break;
            case 3:
                data = peek(&queue);
                if (data != -1) {
                    printf("Front element: %d\n", data);
                }
                break;
            case 4:
                displayQueue(&queue);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
    
    freeQueue(&queue);
    return 0;
}
