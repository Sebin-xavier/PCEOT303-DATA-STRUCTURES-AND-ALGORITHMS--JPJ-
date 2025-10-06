#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

#define SIZE 40

int pop();
void push(int);

char postfix[SIZE];
int stack[SIZE], top = -1;

int main()
{
    int i, a, b, result, pEval;
    char *token;
    char *saveptr; // Pointer to save the state for strtok_s
    
    printf("\nEnter a postfix expression (with spaces between numbers and operators): ");
    fgets(postfix, SIZE, stdin);  // Read the entire line, allowing multi-digit numbers

    // Use the safer, reentrant strtok_s.
    // The 'saveptr' variable holds the context, making it thread-safe.
    token = strtok_s(postfix, " \n", &saveptr);

    while (token != NULL)
    {
        // Check if the token is a number
        if (isdigit(token[0]))
        {
            push(atoi(token));  // Convert token to an integer and push it to the stack
        }
        else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '^')
        {
            b = pop();
            a = pop();
            
            switch (token[0])
            {
                case '+': result = a + b;
                          break;
                case '-': result = a - b;
                          break;
                case '*': result = a * b;
                          break;
                case '/': result = a / b;
                          break;
                case '^': result = pow(a, b);
                          break;
            }
            
            push(result);
        }
        else 
        {
            printf("Error: Invalid token '%s' in expression.\n", token);
            exit(-1); // Exit on invalid input
        }
        
        // Move to the next token
        token = strtok_s(NULL, " \n", &saveptr);
    }

    pEval = pop();
    
    printf("\nThe postfix evaluation is: %d\n", pEval);
    
    return 0;
}

void push(int n)
{
    if (top < SIZE - 1)
    {
        stack[++top] = n;
    }
    else
    {
        printf("Stack is full!\n");
        exit(-1);
    }
}

int pop()
{
    if (top > -1)
    {
        return stack[top--];
    }
    else
    {
        printf("Stack is empty!\n");
        exit(-1);
    }
}
