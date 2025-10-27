#include <stdio.h>
#include <stdlib.h>

// Node structure to represent a term in a polynomial
typedef struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
} Node;

// Function to create a new term
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new term into the polynomial (maintains sorted order by exponent)
void insertTerm(Node** poly, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    Node* current = *poly;
    Node* prev = NULL;

    // Find the correct position to insert the new term
    while (current != NULL && current->exponent > exp) {
        prev = current;
        current = current->next;
    }

    // If a term with the same exponent exists, add coefficients
    if (current != NULL && current->exponent == exp) {
        current->coefficient += coeff;
        free(newNode); // Free the unused new node
        // If coefficient becomes zero, remove the term (optional, but good practice)
        if (current->coefficient == 0) {
            if (prev == NULL) { // It's the head node
                *poly = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
        }
    } else { // Insert the new term
        if (prev == NULL) { // Insert at the beginning
            newNode->next = *poly;
            *poly = newNode;
        } else { // Insert in the middle or at the end
            newNode->next = current;
            prev->next = newNode;
        }
    }
}

// Function to create a polynomial by taking user input
Node* createPolynomial() {
    Node* poly = NULL;
    int n, coeff, exp;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient for term %d: ", i + 1);
        scanf("%d", &coeff);
        printf("Enter exponent for term %d: ", i + 1);
        scanf("%d", &exp);
        if (coeff != 0) { // Only add non-zero terms
            insertTerm(&poly, coeff, exp);
        }
    }
    return poly;
}

// Function to display a polynomial
void displayPolynomial(Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    Node* temp = poly;
    while (temp != NULL) {
        // Print coefficient and 'x' if exponent is not 0
        if (temp->coefficient != 1 || temp->exponent == 0) {
             printf("%d", temp->coefficient);
        }
       
        if (temp->exponent > 0) {
            printf("x");
            if (temp->exponent > 1) {
                printf("^%d", temp->exponent);
            }
        }

        // Print '+' if there is a next term
        if (temp->next != NULL && temp->next->coefficient > 0) {
            printf(" + ");
        } else if (temp->next != NULL) {
             printf(" "); // For negative coefficients, space is enough
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* p1 = poly1;
    Node* p2 = poly2;

    // Traverse both lists and add terms
    while (p1 != NULL && p2 != NULL) {
        if (p1->exponent > p2->exponent) {
            insertTerm(&result, p1->coefficient, p1->exponent);
            p1 = p1->next;
        } else if (p2->exponent > p1->exponent) {
            insertTerm(&result, p2->coefficient, p2->exponent);
            p2 = p2->next;
        } else { // Exponents are equal
            int sum_coeff = p1->coefficient + p2->coefficient;
            if (sum_coeff != 0) {
                insertTerm(&result, sum_coeff, p1->exponent);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    // Add remaining terms from poly1
    while (p1 != NULL) {
        insertTerm(&result, p1->coefficient, p1->exponent);
        p1 = p1->next;
    }

    // Add remaining terms from poly2
    while (p2 != NULL) {
        insertTerm(&result, p2->coefficient, p2->exponent);
        p2 = p2->next;
    }

    return result;
}

// Function to multiply two polynomials
Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* p1 = poly1;

    if (poly1 == NULL || poly2 == NULL) {
        return NULL;
    }

    // Multiply each term of poly1 with each term of poly2
    while (p1 != NULL) {
        Node* p2 = poly2;
        while (p2 != NULL) {
            int new_coeff = p1->coefficient * p2->coefficient;
            int new_exp = p1->exponent + p2->exponent;
            insertTerm(&result, new_coeff, new_exp);
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    return result;
}

// Function to free the memory used by a polynomial
void freePolynomial(Node** poly) {
    Node* current = *poly;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *poly = NULL;
}

int main() {
    Node *poly1 = NULL, *poly2 = NULL, *sum = NULL, *product = NULL;

    printf("--- Create First Polynomial ---\n");
    poly1 = createPolynomial();
    printf("\nFirst Polynomial: ");
    displayPolynomial(poly1);

    printf("\n--- Create Second Polynomial ---\n");
    poly2 = createPolynomial();
    printf("\nSecond Polynomial: ");
    displayPolynomial(poly2);

    // Polynomial Addition
    printf("\n--- Addition ---\n");
    sum = addPolynomials(poly1, poly2);
    printf("Result of addition: ");
    displayPolynomial(sum);

    // Polynomial Multiplication
    printf("\n--- Multiplication ---\n");
    product = multiplyPolynomials(poly1, poly2);
    printf("Result of multiplication: ");
    displayPolynomial(product);

    // Free all allocated memory
    freePolynomial(&poly1);
    freePolynomial(&poly2);
    freePolynomial(&sum);
    freePolynomial(&product);

    return 0;
}
