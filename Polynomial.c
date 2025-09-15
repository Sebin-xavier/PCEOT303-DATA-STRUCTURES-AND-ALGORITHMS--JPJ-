#include <stdio.h>
#include <stdlib.h>

// Node structure for polynomial term
typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

// Polynomial structure with head, tail and size
typedef struct Polynomial {
    Node* head;
    Node* tail;
    int size;
} Polynomial;

// Function to create a new node
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Initialize polynomial
void initPolynomial(Polynomial* poly) {
    poly->head = NULL;
    poly->tail = NULL;
    poly->size = 0;
}

// Efficient addNode function using tail pointer (for sorted input)
void addNode(Polynomial* poly, int coeff, int exp) {
    if (coeff == 0) return; // Don't insert terms with zero coefficient
    
    Node* newNode = createNode(coeff, exp);
    
    // If list is empty
    if (poly->head == NULL) {
        poly->head = poly->tail = newNode;
        poly->size++;
        return;
    }
    
    // Append at the end using tail pointer (O(1) operation)
    poly->tail->next = newNode;
    poly->tail = newNode;
    poly->size++;
}

// Insert term in descending order of exponent with tail optimization
void insertTerm(Polynomial* poly, int coeff, int exp) {
    if (coeff == 0) return; // Don't insert terms with zero coefficient
    
    Node* newNode = createNode(coeff, exp);
    
    // If list is empty
    if (poly->head == NULL) {
        poly->head = poly->tail = newNode;
        poly->size++;
        return;
    }
    
    // Insert at beginning if exp is greater than first term
    if (poly->head->exp < exp) {
        newNode->next = poly->head;
        poly->head = newNode;
        poly->size++;
        return;
    }
    
    // Check if smaller than tail - insert at end (O(1) operation)
    if (poly->tail->exp > exp) {
        poly->tail->next = newNode;
        poly->tail = newNode;
        poly->size++;
        return;
    }
    
    // Check if equal to tail exponent - add coefficients
    if (poly->tail->exp == exp) {
        poly->tail->coeff += coeff;
        free(newNode);
        if (poly->tail->coeff == 0) {
            // Need to find new tail if removing the last node
            if (poly->head == poly->tail) {
                poly->head = poly->tail = NULL;
            } else {
                Node* temp = poly->head;
                while (temp->next != poly->tail) {
                    temp = temp->next;
                }
                temp->next = NULL;
                free(poly->tail);
                poly->tail = temp;
            }
            poly->size--;
        }
        return;
    }
    
    Node* temp = poly->head;
    
    // If exponent matches first term, add coefficients
    if (temp->exp == exp) {
        temp->coeff += coeff;
        free(newNode);
        if (temp->coeff == 0) {
            poly->head = temp->next;
            if (poly->head == NULL) poly->tail = NULL;
            free(temp);
            poly->size--;
        }
        return;
    }
    
    // Find position to insert
    while (temp->next && temp->next->exp > exp) {
        temp = temp->next;
    }
    
    // If exponent matches existing term, add coefficients
    if (temp->next && temp->next->exp == exp) {
        temp->next->coeff += coeff;
        free(newNode);
        if (temp->next->coeff == 0) {
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            if (toDelete == poly->tail) poly->tail = temp;
            free(toDelete);
            poly->size--;
        }
    } else {
        // Insert new term
        newNode->next = temp->next;
        temp->next = newNode;
        if (newNode->next == NULL) poly->tail = newNode; // Update tail if inserting at end
        poly->size++;
    }
}

// Function to input a polynomial
void inputPolynomial(Polynomial* poly, int n) {
    int coeff, exp;
    printf("Enter terms (coefficient exponent):\n");
    for (int i = 0; i < n; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(poly, coeff, exp);
    }
}

// Function to add two polynomials
Polynomial addPolynomials(Polynomial* poly1, Polynomial* poly2) {
    Polynomial result;
    initPolynomial(&result);
    
    Node *p1 = poly1->head, *p2 = poly2->head;
    
    // Traverse both polynomials
    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            insertTerm(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            insertTerm(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        } else {
            // Same exponent, add coefficients
            int sumCoeff = p1->coeff + p2->coeff;
            if (sumCoeff != 0) {
                insertTerm(&result, sumCoeff, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    
    // Add remaining terms from poly1
    while (p1) {
        insertTerm(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }
    
    // Add remaining terms from poly2
    while (p2) {
        insertTerm(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }
    
    return result;
}

// Function to multiply two polynomials
Polynomial multiplyPolynomials(Polynomial* poly1, Polynomial* poly2) {
    Polynomial result;
    initPolynomial(&result);
    
    if (poly1->head == NULL || poly2->head == NULL) {
        return result; // Return empty polynomial if either is empty
    }
    
    Node* p1 = poly1->head;
    
    // For each term in first polynomial
    while (p1) {
        Node* p2 = poly2->head;
        
        // Multiply with each term in second polynomial
        while (p2) {
            int newCoeff = p1->coeff * p2->coeff;
            int newExp = p1->exp + p2->exp;
            
            insertTerm(&result, newCoeff, newExp);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    
    return result;
}

// Function to display a polynomial
void displayPolynomial(Polynomial* poly) {
    if (poly->head == NULL) {
        printf("0\n");
        return;
    }
    
    Node* temp = poly->head;
    int first = 1;
    
    while (temp) {
        if (!first && temp->coeff > 0) {
            printf(" + ");
        } else if (temp->coeff < 0) {
            printf(" - ");
            printf("%dx^%d", abs(temp->coeff), temp->exp);
            temp = temp->next;
            first = 0;
            continue;
        }
        
        if (temp->exp == 0) {
            printf("%d", temp->coeff);
        } else if (temp->exp == 1) {
            if (temp->coeff == 1) printf("x");
            else printf("%dx", temp->coeff);
        } else {
            if (temp->coeff == 1) printf("x^%d", temp->exp);
            else printf("%dx^%d", temp->coeff, temp->exp);
        }
        
        temp = temp->next;
        first = 0;
    }
    printf("\n");
}

// Free the polynomial
void freePolynomial(Polynomial* poly) {
    Node* temp;
    while (poly->head) {
        temp = poly->head;
        poly->head = poly->head->next;
        free(temp);
    }
    poly->tail = NULL;
    poly->size = 0;
}

// Display polynomial info
void displayPolynomialInfo(Polynomial* poly, const char* name) {
    printf("%s (Size: %d): ", name, poly->size);
    displayPolynomial(poly);
}

// Menu-driven input for polynomial
void menuInputPolynomial(Polynomial* poly) {
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    inputPolynomial(poly, n);
}

// Display menu options
void displayMenu() {
    printf("\n=== Polynomial Operations Menu ===\n");
    printf("1. Add two polynomials\n");
    printf("2. Multiply two polynomials\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Polynomial poly1, poly2, result;
    int choice;
    
    // Initialize polynomials
    initPolynomial(&poly1);
    initPolynomial(&poly2);
    initPolynomial(&result);
    
    printf("=== Polynomial Calculator ===\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // Addition
                printf("\nPolynomial Addition\n");
                printf("Enter first polynomial:\n");
                menuInputPolynomial(&poly1);
                printf("Enter second polynomial:\n");
                menuInputPolynomial(&poly2);
                
                // Free previous result
                freePolynomial(&result);
                result = addPolynomials(&poly1, &poly2);
                
                printf("\n=== Addition Results ===\n");
                displayPolynomialInfo(&poly1, "First Polynomial");
                displayPolynomialInfo(&poly2, "Second Polynomial");
                displayPolynomialInfo(&result, "Sum");
                break;
                
            case 2: // Multiplication
                printf("\nPolynomial Multiplication\n");
                printf("Enter first polynomial:\n");
                menuInputPolynomial(&poly1);
                printf("Enter second polynomial:\n");
                menuInputPolynomial(&poly2);
                
                // Free previous result
                freePolynomial(&result);
                result = multiplyPolynomials(&poly1, &poly2);
                
                printf("\n=== Multiplication Results ===\n");
                displayPolynomialInfo(&poly1, "First Polynomial");
                displayPolynomialInfo(&poly2, "Second Polynomial");
                displayPolynomialInfo(&result, "Product");
                break;
                
                
            case 3: // Exit
                printf("Exiting program...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        // Free polynomials for next operation (except result)
        if (choice == 1 || choice == 2) {
            freePolynomial(&poly1);
            freePolynomial(&poly2);
            initPolynomial(&poly1);
            initPolynomial(&poly2);
        }
        
    } while (choice != 3);
    
    // Final cleanup
    freePolynomial(&poly1);
    freePolynomial(&poly2);
    freePolynomial(&result);
    
    return 0;
}
