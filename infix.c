#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100

typedef struct node {
    char data;
    struct node* next;
}node;

typedef struct {
    node* top;
} stack;

bool isCharacter(char);
bool isoperator(char);
bool ignorable(char);
void init(stack*);
bool isEmptyStack(stack*);
void push(stack*, char);
char pop(stack*);
void display(stack*);
void insertLinkedList(node**, char);
void displayReverseHelper(node*);
int precedenceReturn(char);
bool precedenceOperation(stack*, char*);
void printOutputList(node*);
node* reverseList(node*);

/*main*/

int main(void) {
    char* input = (char*)malloc(sizeof(char) * MAX);
    node* head = NULL;
    stack* s = (stack*)malloc(sizeof(stack));
    node* outputHead = NULL;
    int choice;

    init(s);

    printf("1. Infix to Postfix\n2. Infix to Prefix\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();  // To consume newline after scanf

    switch (choice) {
        case 1: {
            printf("Enter your Equation: ");
            fgets(input, MAX, stdin);

            for (int i = 0; input[i] != '\0'; i++) {
                insertLinkedList(&head, input[i]); 
            }

            free(input); 

            node* temp = head;
            int count = 1;

            printf("SI No.\t\tInput\t\tStack\t\tOutput\t\tOperation\n");

            while (temp->next != NULL) {
                char operation[20];

                //for step and input
                printf("%d.\t\t%c\t\t", count, temp->data);

                //operator check and push into stack
                if (isoperator(temp->data)) {
                    push(s, temp->data);
                    strcpy(operation, "Push()");
                }

                char popped;
                if (precedenceOperation(s, &popped)) {
                    insertLinkedList(&outputHead, popped);
                    strcpy(operation, "Pop()");
                }

                if (temp->data == ')') {
                    while (!isEmptyStack(s)) {
                        char chl = pop(s);
                        if (chl == '(') break; // stop on '('
                        if (chl != '(' && chl != ')') {
                            insertLinkedList(&outputHead, chl);
                            strcpy(operation, "Pop()");
                        }
                    }
                }

                //display stack
                display(s);
                printf("\t\t");

                //if character link into output linked list
                if (isCharacter(temp->data)) {
                    insertLinkedList(&outputHead, temp->data);
                    strcpy(operation, "Print()");
                }

                //output linkedlist print
                node* tempout = outputHead;
                while (tempout != NULL) {
                    printf("%c", tempout->data);
                    tempout = tempout->next;
                }

                //operation print
                printf("\t\t");
                printf("%s", operation);

                count++;
                temp = temp->next;

                printf("\n");
            }

            //final step 
            printf("%d.\t\tempty\t\tempty\t\t", count);

            while (!isEmptyStack(s)) {
                char p = pop(s);
                insertLinkedList(&outputHead, p);
            }

            //error
            printOutputList(outputHead);
            printf("\t\tpop()\n");

            printf("Converted Expression: ");

            node* tempout = outputHead;
            while (tempout != NULL) {
                printf("%c", tempout->data);
                tempout = tempout->next;
            }

            printf("\n");
        } break;

        //ERROR
        case 2: {
            printf("Enter your Equation: ");
            fgets(input, MAX, stdin);

            for (int i = 0; input[i] != '\0'; i++) {
                insertLinkedList(&head, input[i]); 
            }

            free(input); 

            // Step 1: Reverse the infix expression
            head = reverseList(head);

            // Step 2: Swap '(' and ')'
            node* tempSwap = head;
            while (tempSwap != NULL) {
                if (tempSwap->data == '(') {
                    tempSwap->data = ')';
                } else if (tempSwap->data == ')') {
                    tempSwap->data = '(';
                }
                tempSwap = tempSwap->next;
            }

            node* temp = head;
            int count = 1;

            printf("SI No.\t\tInput\t\tStack\t\tOutput\t\tOperation\n");

            while (temp != NULL) {
                char operation[20] = "None";

                printf("%d.\t\t%c\t\t", count, temp->data);

                if (isoperator(temp->data)) {
                    push(s, temp->data);
                    strcpy(operation, "Push()");
                }

                char popped;
                if (precedenceOperation(s, &popped)) {
                    insertLinkedList(&outputHead, popped);
                    strcpy(operation, "Pop()");
                }

                if (temp->data == ')') {
                    while (!isEmptyStack(s)) {
                        char chl = pop(s);
                        if (chl == '(') break;
                        if (chl != '(' && chl != ')') {
                            insertLinkedList(&outputHead, chl);
                            strcpy(operation, "Pop()");
                        }
                    }
                }

                display(s);
                printf("\t\t");

                if (isCharacter(temp->data)) {
                    insertLinkedList(&outputHead, temp->data);
                    strcpy(operation, "Print()");
                }

                node* tempout = outputHead;
                while (tempout != NULL) {
                    printf("%c", tempout->data);
                    tempout = tempout->next;
                }

                printf("\t\t%s\n", operation);

                count++;
                temp = temp->next;
            }

            printf("%d.\t\tempty\t\tempty\t\t", count);

            while (!isEmptyStack(s)) {
                char p = pop(s);
                insertLinkedList(&outputHead, p);
            }

            printOutputList(outputHead);
            printf("\tpop()\n");

    // Final Reverse of output to get prefix
            printf("Converted Expression: ");
            outputHead = reverseList(outputHead);

            node* tempout = outputHead;
            while (tempout != NULL) {
                printf("%c", tempout->data);
                tempout = tempout->next;
            }
            printf("\n");
        } break;

        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}

/*funtions*/

bool isCharacter(char c) {
    return (c > 64 && c < 91) || (c > 96 && c < 123);
}

bool isoperator(char c){
    return (c == '+' || c=='-'|| c=='*'|| c=='/' || c=='^' || c=='(' || c==')');
}

bool ignorable(char c) {
    return c == ' ' || c == '\t';
}

void init(stack* s) {
    s->top = NULL;
}

bool isEmptyStack(stack* s) {
    return s->top == NULL;
}

void push(stack* s, char c) {
    node* newNode = (node*)malloc(sizeof(node));

    newNode->data = c;
    newNode->next = s->top;
    s->top = newNode;
}

char pop(stack* s) {
    if (isEmptyStack(s)) {
        printf("Empty Stack");
    }

    node* temp = s->top;
    char c = temp->data;
    s->top = temp->next;
    free(temp);

    return c;
}

void displayReverseHelper(node* n) {
    if (n == NULL) return;
    displayReverseHelper(n->next);
    printf("%c", n->data);        
}

void display(stack* s) {
    if (isEmptyStack(s)) {
        printf("empty");
        return;
    }
    displayReverseHelper(s->top);
}

void insertLinkedList(node** head, char c) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = c;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int precedenceReturn(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return -1; // For '(', ')', or any non-operator
}


bool precedenceOperation(stack* s, char* c) {
    node* temp1 = s->top;
    if (!temp1 || !temp1->next) return false;

    node* temp2 = temp1->next;

    int prec1 = precedenceReturn(temp1->data);
    int prec2 = precedenceReturn(temp2->data);

    // Skip precedence check if any are parentheses
    if (prec1 == -1 || prec2 == -1) return false;

    if (prec1 == prec2 || prec1 < prec2) {
        *c = temp2->data;
        temp1->next = temp2->next;
        free(temp2);
        return true;
    }

    return false;
}

void printOutputList(node* head) {
    if (head == NULL) {
        printf("empty");
    } else {
        while (head != NULL) {
            printf("%c", head->data);
            head = head->next;
        }
    }
}

node* reverseList(node* head) {
    node* prev = NULL;
    node* current = head;
    node* next = NULL;

    while (current != NULL) {
        next = current->next;    // Save next node
        current->next = prev;    // Reverse current node's pointer
        prev = current;          // Move prev one step ahead
        current = next;          // Move current one step ahead
    }

    return prev; // New head
}