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

/*main*/

int main(void) {
    char* input = (char*)malloc(sizeof(char) * MAX);
    node* head = NULL;
    stack* s = (stack*)malloc(sizeof(stack));
    node* ouputHead = NULL;

    init(s);

    printf("Enter your Equation: ");
    fgets(input, MAX, stdin);

    for (int i = 0; input[i] != '\0'; i++) {
        insertLinkedList(&head, input[i]); 
    }

    free(input); 

    node* temp = head;
    int count = 1;

    //remaining work
    while (temp->next != NULL) {
        char operation[20];

        //for step and input
        printf("%d.\t%c\t", count, temp->data);

        //operator check and push into stack
        if (isoperator(temp->data)) {
            push(s, temp->data);
            strcpy(operation, "Push()");
        }

        //display stack
        display(s);
        printf("\t");

        //if character link into output linked list
        if (isCharacter(temp->data)) {
            insertLinkedList(&ouputHead, temp->data);
            strcpy(operation, "Print()");
        }

        //output linkedlist print
        node* tempout = ouputHead;
        while (tempout != NULL) {
            printf("%c", tempout->data);
            tempout = tempout->next;
        }

        //operation print
        printf("\t");
        printf("%s", operation);

        count++;
        temp = temp->next;

        printf("\n");
    }

    //final step done
    printf("%d.\tempty\tempty\t", count);

    while (!isEmptyStack(s)) {
        char p = pop(s);

        insertLinkedList(&ouputHead, p);
    }

    node* tempout = ouputHead;

    while (tempout != NULL) {
        printf("%c", tempout->data);
        tempout = tempout->next;
    }
    
    printf("\tpop()");

    printf("\n");

    return 0;
}

/*funtions*/

bool isCharacter(char c) {
    return (c > 64 && c < 91) || (c > 96 && c < 123);
}

bool isoperator(char c){
    return (c == '+' || c=='-'|| c=='*'|| c=='/' || c=='^');
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

void display(stack* s) {
    if(isEmptyStack(s)) {
        printf("empty");
        return;
    }
    node* temp = s->top;
    while(temp) {
        printf("%c", temp ->data);
        temp = temp->next;
    }
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