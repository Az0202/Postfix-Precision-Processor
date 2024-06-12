#include <stdio.h>      // Include standard I/O library for input and output functions
#include <stdlib.h>     // Include standard library for general purposes like dynamic memory allocation, using exit(), etc.
#include <string.h>     // Include string library for string manipulation functions
#include <ctype.h>      // Include ctype library for character type checking

#define MAX_STACK_SIZE 1000000  // Define a constant for the maximum size of the stack

// Define a structure for the stack
typedef struct {
    int items[MAX_STACK_SIZE];  // Array to hold the stack items
    int top;                    // Integer to track the top position in the stack
} Stack;

// Function to initialize the stack
void initStack(Stack *Sptr) {
    Sptr->top = -1;  // Set the top index to -1 indicating the stack is empty
}

// Function to check if the stack is empty
int isEmpty(Stack *Sptr) {
    return Sptr->top == -1;  // Return true if top is -1, false otherwise
}

// Function to check if the stack is full
int isFull(Stack *Sptr) {
    return Sptr->top == MAX_STACK_SIZE - 1;  // Return true if top is at maximum capacity, false otherwise
}

// Function to push an item onto the stack
void push(Stack *Sptr, int item) {
    if (isFull(Sptr)) {  // Check if the stack is full before pushing
        printf("Stack is full\n"); 
        return;  // Return from function if stack is full
    }
    Sptr->items[++Sptr->top] = item;  // Increment top and add new item. increments s->top, then uses the new value of s->top as the index to access the items array, and assigns the value of item to this position in the array. In essence, it's pushing item onto the top of the stack.
}

// Function to pop an item from the stack
int pop(Stack *Sptr) {
    if (isEmpty(Sptr)) {  // Check if the stack is empty before popping
        printf("Stack is empty\n");
        return -1;  // Return -1 if stack is empty
    }
    return Sptr->items[Sptr->top--];  // Return the top item and decrement the top index
}

// Function to peek at the top item of the stack without removing it
int peek(Stack *Sptr) {
    if (isEmpty(Sptr)) {  // Check if the stack is empty
        printf("Stack is empty\n");
        return -1;  // Return -1 if stack is empty
    }
    return Sptr->items[Sptr->top];  // Return the top item without removing it
}

// Function to print stack contents
void printStack(Stack *Sptr) {
    printf("[");
    for (int i = 0; i <= Sptr->top; i++) {  // Iterate through each item in the stack
        printf("%d", Sptr->items[i]);  // Print each item
        if (i < Sptr->top) {
            printf(", ");  // Print comma for separation except after the last item
        }
    }
    printf("]\n");  // Close the bracket and add a newline at the end
}

int isNumber(char * token){
    if (token == NULL) return 0;
    int c = (int)*token;
    if(c >= 48 && c <= 57 || c == 45 && strlen(token) > 1){
        return 1;
    } else {
        return 0;
    }
}

// Function to evaluate the RPN expression
void evaluate(Stack *Sptr, char *token) {
    int number, first, second;
    char *end;
    //printf("%s\n", token);

    number =  atoi(token); // Convert token to integer. 'end' will point to the first non-integer character
    if (!isNumber(token)) {  // Check if token was a number
            switch (token[0]) {  // Switch on the operator
                case '+':  // Handle addition
                    if (Sptr->top < 1) return;  // Check for enough operands
                    first = pop(Sptr);  // Pop operand 1
                   // printf("first: %d\n", first);
                    second = pop(Sptr);  // Pop operand 2
                  //  printf("second: %d\n", second);
                    push(Sptr, second + first);  // Perform operation and push result
                    break;
                case '-':
                    if (Sptr->top < 1) {
                        //printf("Insufficient operands for '-' operation\n");
                        return;
                    }
                    first = pop(Sptr);  // Pop the first operand
                    second = pop(Sptr);  // Pop the second operand
                    push(Sptr, second - first);  // Perform subtraction and push the result
                    break;

                case '*':
                    if (Sptr->top < 1) {
                        //printf("Insufficient operands for '*' operation\n");
                        return;
                    }
                    first = pop(Sptr);  // Pop the first operand
                    second = pop(Sptr);  // Pop the second operand
                    push(Sptr, second * first);  // Perform multiplication and push the result
                    break;

                case '%':
                    if (Sptr->top < 1) {
                        //printf("Insufficient operands for '%%' operation\n");
                        return;
                    }
                    first = pop(Sptr);  // Pop the first operand
                    second = pop(Sptr);  // Pop the second operand
                    if (first == 0) {
                        //printf("Division by zero error\n");
                        return;
                    }
                    push(Sptr, second % first);  // Perform modulo and push the result
                    break;
                default:  // Handle unknown operator
                    //printf("Invalid token: %s\n", token);
                    break;
            }
        
        
    } else {
       // printf("%d\n", number);
   
        push(Sptr, number);  // Push the number onto the stack if token was a number
    }
}


int main() {
    int size_of_input = 10000000; 
    Stack s;
    char *input = (char *) malloc(size_of_input * sizeof(char));
    char *rest = input; 
    char *token;

    initStack(&s);

    int num_read = fread(input, 1, size_of_input, stdin);
    //printf("num_read: %d\n", num_read);
    while (num_read != 0) {
     
           token = strsep(&rest, "  \n");   
           //puts(token); 
           //printf("num_read: %d\n", num_read);
           num_read-=1;
           //printf("token: %s\n", token);

        if (token != NULL  ) {           
                if (isNumber(token) || *token == 0 || !strcmp(token, "-") || !strcmp(token, "+") || !strcmp(token, "*") || !strcmp(token, "/") || !strcmp(token, "%")){
                    evaluate(&s, token);                    
                }else{
                        break;
                }

           }
        }
    //puts("done");
    printStack(&s);
    free(input);
    return 0;
}